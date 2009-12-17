/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  IMplementaion for publising own presence
*
*/


#include <ximpprotocolconnectionhost.h>
#include "cpublishownpresencerequest.h"
#include "mossprotocolconnectionmanager.h"
#include "ossprotocolpluginlogger.h"
#include "waittimer.h"

#include "cossprotocolconnectionmanager.h"

#include <ximpobjectfactory.h>
#include <ximpobjectcollection.h>
#include <protocolpresencepublishingdatahost.h>

#include <presentitygroupinfo.h>
#include <presenceinfofieldvaluetext.h>
#include <presenceinfofieldvalueenum.h>
#include <presentitygroupmemberinfo.h>
#include <ximpidentity.h>
#include <presenceinfo.h>
#include <personpresenceinfo.h>
#include <servicepresenceinfo.h>
#include <devicepresenceinfo.h>
#include <presenceinfofield.h>
#include <presenceinfofieldcollection.h>
#include <presenceinfofieldvaluebinary.h>

#include <stdlib.h>
#include "stringutils.h"
#include <string.h>
#include "msgliterals.h"
#include "msg_enums.h"
#include "xmppparameters.h"
#include "waittimer.h"
#include <e32math.h>
#include "ossprotocoladaptutils.h"
#include <avabilitytext.h>

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CPublishOwnPresencerequest::CPublishOwnPresencerequest
// ---------------------------------------------------------------------------
//
CPublishOwnPresencerequest::CPublishOwnPresencerequest( 
									MOSSProtocolConnectionManager& aConnMan,
									TXIMPRequestId aRequestId ) :
    CActive( EPriorityNormal ),
    iRequestId( aRequestId ),
    iConnMan( aConnMan )
    {
    LOGGER ( TXT("::CPublishOwnPresencerequest Start") );
    CActiveScheduler::Add( this );
    
    LOGGER ( TXT("::CPublishOwnPresencerequest End") );
    }


// ---------------------------------------------------------------------------
// CPublishOwnPresencerequest::ConstructL
// ---------------------------------------------------------------------------
//
void CPublishOwnPresencerequest::ConstructL()
    {
    LOGGER ( TXT("CPublishOwnPresencerequest::ConstructL Start-End") );
    
	
    }


// ---------------------------------------------------------------------------
// CPublishOwnPresencerequest::NewL
// ---------------------------------------------------------------------------
//
CPublishOwnPresencerequest* CPublishOwnPresencerequest::NewL(
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
    {
    LOGGER ( TXT("CPublishOwnPresencerequest::NewL Start") );
    
    CPublishOwnPresencerequest* self = new( ELeave ) 
    			CPublishOwnPresencerequest( aConnMan, aRequestId );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    
    LOGGER ( TXT("CPublishOwnPresencerequest::NewL End") );
    return self;
    }


// ---------------------------------------------------------------------------
// CPublishOwnPresencerequest::NewLC
// ---------------------------------------------------------------------------
//
CPublishOwnPresencerequest* CPublishOwnPresencerequest::NewLC(
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
    {
    LOGGER ( TXT("CPublishOwnPresencerequest::NewLC Start") );
    
    CPublishOwnPresencerequest* self = 
    					CPublishOwnPresencerequest::NewL(aConnMan, aRequestId);
    CleanupStack::PushL( self );
    
    LOGGER ( TXT("CPublishOwnPresencerequest::NewLC End") );
    return self;
    }

// ---------------------------------------------------------------------------
// CPublishOwnPresencerequest::~CPublishOwnPresencerequest
// ---------------------------------------------------------------------------
//
CPublishOwnPresencerequest::~CPublishOwnPresencerequest()
    {
    LOGGER ( TXT("::~CPublishOwnPresencerequest Start") );
    
	CActive::Cancel();
    
    delete iOwnPresenceInfo;
    iOwnPresenceInfo = NULL;
    LOGGER ( TXT("::~CPublishOwnPresencerequest End") );
    }


// ---------------------------------------------------------------------------
// CPublishOwnPresencerequest::DoCancel()
// ---------------------------------------------------------------------------
//
void CPublishOwnPresencerequest::DoCancel()
    {
    LOGGER ( TXT("CPublishOwnPresencerequest::DoCancel Start") );
    
  //  iConnMan.DataHandler().CancelSending( iSendId );
    
    LOGGER ( TXT("CPublishOwnPresencerequest::DoCancel End") );
    }


// ---------------------------------------------------------------------------
// CPublishOwnPresencerequest::RunL()
// ---------------------------------------------------------------------------
//
void CPublishOwnPresencerequest::RunL()
    {
    LOGGER ( TXT("CPublishOwnPresencerequest::RunL Start") );
	message_hdr_resp* msg_struct = NULL;
	User::LeaveIfError ( iStatus.Int() );
    char* pResponse = NULL;  
	pResponse = iConnMan.DataHandler().ResponseL ( iSendId );

	msg_struct = ( message_hdr_resp* )pResponse ;
	if( !( msg_struct->response ) )
		{
		switch( msg_struct->error_type )
			{

			default:  //for all other error codes like ssl related are mapped to general error
			iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KXIMPErrServiceGeneralError );
			break;       
			}	
		}
	else
		{
		if( iOwnPresenceInfo )
			{
			// set or clear avatar
			MPresenceCacheWriter2* presenceCacheWriter = MPresenceCacheWriter2::CreateWriterL();
			TInt cacheerror = presenceCacheWriter->WritePresenceL( iOwnPresenceInfo );
			User::LeaveIfError ( cacheerror);
			delete iOwnPresenceInfo ;
			iOwnPresenceInfo = NULL;
			delete presenceCacheWriter;	
			}
		iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KErrNone );
		}

	free( pResponse );

	delete this;

	LOGGER ( TXT("CPublishOwnPresencerequest::RunL End") );
    }


// ---------------------------------------------------------------------------
// CPublishOwnPresencerequest::RunError
// ---------------------------------------------------------------------------
//
TInt CPublishOwnPresencerequest::RunError( TInt  aError )
    {
    LOGGER ( TXT("CPublishOwnPresencerequest::RunError Start") );
    
    iConnMan.HandleToHost().HandleRequestCompleted( iRequestId, aError );
    
    delete this;
	LOGGER ( TXT("CPublishOwnPresencerequest::RunError End") );
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// CPublishOwnPresencerequest::PublishOwnPresenceL
// ---------------------------------------------------------------------------
//
void CPublishOwnPresencerequest::PublishOwnPresenceL(const MPresenceInfo& aPresence)
    {   
    LOGGER ( TXT("CPublishOwnPresencerequest::PublishOwnPresenceL Start") );
	char *smsg = NULL;
	char *tmpmsg = NULL;
	message_hdr_req msgHdr = {0,};

	int err = 0;
	int userLen = 0;
	int totalLen = 0;
    const MPersonPresenceInfo* personPresence = aPresence.PersonPresence();
    const MPresenceInfoFieldCollection& presenceFields = personPresence->Fields();
    const MPresenceInfoField& presenceField = presenceFields.FieldAt( 0 );
    //updating own avtar
    if( !(presenceField.FieldType().Compare( NPresenceInfo::NFieldType::KAvatar )) )
        {
        int messagelength = 0;
        const MPresenceInfoFieldValueBinary* avtarfield = 
        TXIMPGetInterface< const MPresenceInfoFieldValueBinary >::From(
                presenceField.FieldValue(),
                MXIMPBase::EPanicIfUnknown );
        if( !(avtarfield->MimeType().Length() ))   //clear avatar
            {
            // now manufacture the message for the clear avtar
            msgHdr.message_type = EClearOwnAvatar;
            messagelength = sizeof( message_hdr_req );
            smsg = ( char* ) User::AllocLC ( messagelength );
            memset ( smsg, '\0', messagelength );
            memcpy( smsg, &msgHdr, messagelength );//copies message header
            iSendId = iConnMan.DataHandler().SendDataL ( iStatus, smsg, messagelength );
            SetActive();// signal the scheduler
            CleanupStack::PopAndDestroy ( 1 ); //smsg
            }
        else     //set or update avatar
            {
            // now manufacture the message for the avtar
            msgHdr.message_type = EUpdateOwnAvtar;
            messagelength = sizeof( message_hdr_req ) + avtarfield->MimeType().Length() + avtarfield->BinaryValue().Length()+2; // 2 for '\0' 's
            smsg = ( char* ) User::AllocLC ( messagelength );
            tmpmsg = ( char* ) User::AllocLC ( messagelength );
            memset ( smsg, '\0', messagelength );
            memset ( tmpmsg, '\0', messagelength );
            if( messagelength > (MAX_MSG_SIZE - totalLen) )
                msgHdr.continue_flag = 1;
            memcpy( smsg, &msgHdr, sizeof( message_hdr_req ) );//copies message header
            totalLen += sizeof( message_hdr_req );
            OssProtocolAdapUtils::ConvertTDesC8toChar( avtarfield->MimeType(),tmpmsg);
            userLen = avtarfield->MimeType().Length(); 
            memcpy( smsg + totalLen, tmpmsg, userLen );//copies mimetype
            totalLen += userLen + 1; // for '\0'
            memset ( tmpmsg, '\0', messagelength );
            OssProtocolAdapUtils::ConvertTDesC8toChar( avtarfield->BinaryValue(),tmpmsg);
            userLen = avtarfield->BinaryValue().Length();
            memcpy( smsg + totalLen, tmpmsg, userLen );//copies avtar
            totalLen += userLen + 1;
            iSendId = iConnMan.DataHandler().SendDataL ( iStatus, smsg, totalLen );
            SetActive();// signal the scheduler
            CleanupStack::PopAndDestroy ( 2 ); //tmpmsg,smsg
            }
		iOwnPresenceInfo = MPresenceBuddyInfo2::NewL();
		if( iOwnPresenceInfo )
			{
			TPtrC ownUserPtr = iConnMan.UserName(); 
			HBufC* xspId = NULL;
			if( ownUserPtr.Length() )
				{
				xspId = HBufC::NewLC( ownUserPtr.Length() + iConnMan.ServiceName().Length() + KColon().Length() );
				TPtr xspIdPtr( xspId->Des() );
				xspIdPtr.Zero();
				xspIdPtr.Append(iConnMan.ServiceName() ); // prepend service name
				xspIdPtr.Append(KColon);
				xspIdPtr.Append( ownUserPtr );
				iOwnPresenceInfo->SetIdentityL(xspIdPtr);
				CleanupStack::PopAndDestroy(xspId); //xspId	
				}
			else
				{
				TPtrC xmppOwnId = iConnMan.XmppParams().UserName();
				xspId = HBufC::NewLC( xmppOwnId.Length() + iConnMan.ServiceName().Length() + KColon().Length() );
				TPtr xspIdPtr( xspId->Des() );
				xspIdPtr.Zero();
				xspIdPtr.Append(iConnMan.ServiceName() ); // prepend service name
				xspIdPtr.Append(KColon);
				xspIdPtr.Append( xmppOwnId );
				iOwnPresenceInfo->SetIdentityL(xspIdPtr);
				CleanupStack::PopAndDestroy(xspId); //xspId		
				}
			iOwnPresenceInfo->SetAvatarL( avtarfield->BinaryValue() );
			
			TInt fieldCount = presenceFields.FieldCount();  
        	for( TInt i = 1; i < fieldCount; i++ ) // zero index is for avatar 
	            {
	            const MPresenceInfoField& presenceField = presenceFields.FieldAt( i );
	            TBuf8<32> temp = presenceField.FieldType();
	            if( !( presenceField.FieldType().Compare( NPresenceInfo::NFieldType::KAvailabilityEnum )) )
	                {
	                const MPresenceInfoFieldValueEnum* availability = 
               		TXIMPGetInterface< const MPresenceInfoFieldValueEnum >::From( 
                        presenceField.FieldValue(),
                        MXIMPBase::EPanicIfUnknown );
                    MPresenceBuddyInfo2::TAvailabilityValues availabe = MPresenceBuddyInfo2::EUnknownAvailability;
                    switch (availability->Value())
                        {
                        case NPresenceInfo::EAvailable :
                            {
                            availabe = MPresenceBuddyInfo2::EAvailable;
                            iOwnPresenceInfo->SetAvailabilityL( availabe ,KNullDesC );
                            break;
                            }

                        case NPresenceInfo::EBusy :
                            {
                            availabe = MPresenceBuddyInfo2::EBusy;
                            iOwnPresenceInfo->SetAvailabilityL( availabe ,KNullDesC );
                            break;
                            }

                        case NPresenceInfo::EHidden :
                            {
                            availabe = MPresenceBuddyInfo2::EAvailable;
                            iOwnPresenceInfo->SetAvailabilityL( availabe ,KNullDesC );
                            break;
                            }

                        case NPresenceInfo::EDoNotDisturb:
                            {
                            availabe = MPresenceBuddyInfo2::EBusy;
                            iOwnPresenceInfo->SetAvailabilityL( availabe,KDndState);
                            break;
                            }
                            
                        case NPresenceInfo::EAway:
                            {
                            availabe = MPresenceBuddyInfo2::EBusy;
                            iOwnPresenceInfo->SetAvailabilityL( availabe,KAwayState);
                            break;
                            }
                            
                        case NPresenceInfo::ENotAvailable:
                            {
                            availabe = MPresenceBuddyInfo2::ENotAvailable;
                            iOwnPresenceInfo->SetAvailabilityL( availabe ,KNullDesC );
                            break;
                            }
                            
                        default:
                            break;  
                        }
	                }
				else if( !(presenceField.FieldType().Compare( NPresenceInfo::NFieldType::KStatusMessage )) )
	                {
	                const MPresenceInfoFieldValueText* statustext = 
	                TXIMPGetInterface< const MPresenceInfoFieldValueText >::From(
	                        presenceField.FieldValue(),
	                        MXIMPBase::EPanicIfUnknown );
	                // now manufacture the message for the status text
	                if( statustext && statustext->TextValue().Length() )
						{
						iOwnPresenceInfo->SetStatusMessageL(  statustext->TextValue() );
						}
	               
	                }        
            	}
			
			}
        }
    else  //for update presence
        {
        TInt fieldCount = presenceFields.FieldCount(); 
        char* availablty = ( char* ) User::AllocLC ( MAX_MSG_SIZE );
        smsg = ( char* ) User::AllocLC ( MAX_MSG_SIZE );
        tmpmsg = ( char* ) User::AllocLC ( MAX_MSG_SIZE );
        msgHdr.message_type = EUpdateOwnPresence;
        memset ( smsg, '\0', MAX_MSG_SIZE );
        memset ( tmpmsg, '\0', MAX_MSG_SIZE );
        memset ( availablty, '\0', MAX_MSG_SIZE );
        memcpy( smsg, &msgHdr, sizeof( message_hdr_req ) );
        totalLen += sizeof( message_hdr_req );
    // updating availability
    const MPersonPresenceInfo* personPresence = aPresence.PersonPresence();
    const MPresenceInfoFieldCollection& presenceFields = personPresence->Fields();
    //TInt fieldCount = presenceFields.FieldCount();   
        for( TInt i = 0; i < fieldCount; i++ )
            {
            const MPresenceInfoField& presenceField = presenceFields.FieldAt( i );
            TBuf8<32> temp = presenceField.FieldType();
            LOGGER ( TXT( "ExtractPersonPresenceAttributes:%S "),&presenceField.FieldType());
 		
              if( !( presenceField.FieldType().Compare( NPresenceInfo::NFieldType::KAvailabilityEnum )) )
                {
                const MPresenceInfoFieldValueEnum* availability = 
                TXIMPGetInterface< const MPresenceInfoFieldValueEnum >::From( 
                        presenceField.FieldValue(),
                        MXIMPBase::EPanicIfUnknown );
                 if ( availability->Value() == NPresenceInfo::EAvailable )
                    {
                    char* temp = "avaliable";
                    strcpy(availablty,temp); 
                    userLen = strlen( availablty );  
                    memcpy( smsg + totalLen, availablty, userLen );
                    totalLen += userLen + 1;     
                    }
                 else if ( availability->Value() == NPresenceInfo::EBusy )
                    {
                    char* temp = "dnd";
                    strcpy(availablty,temp);
                    userLen = strlen( availablty );  
                    memcpy( smsg + totalLen, availablty, userLen );
                    totalLen += userLen + 1;     
                    }   
                 else if(availability->Value() == NPresenceInfo::EAway) 
                    {		
                    char* temp = "away";
                    strcpy(availablty,temp);
                    userLen = strlen( availablty );  
                    memcpy( smsg + totalLen, availablty, userLen );
                    totalLen += userLen + 1;    
    				}
                 else if(availability->Value() == NPresenceInfo::EHidden) 
                    {       
                     char* temp = "hidden";
                     strcpy(availablty,temp);
                     userLen = strlen( availablty );  
                     memcpy( smsg + totalLen, availablty, userLen );
                     totalLen += userLen + 1;    
                    }
                 else if(availability->Value() == NPresenceInfo::ENotAvailable) 
                    {       
                     char* temp = "offline";
                     strcpy(availablty,temp);
                     userLen = strlen( availablty );  
                     memcpy( smsg + totalLen, availablty, userLen );
                     totalLen += userLen + 1;    
                    }
                 
          }
    //updating status text
    
         if( !(presenceField.FieldType().Compare( NPresenceInfo::NFieldType::KStatusMessage )) )
                {
                const MPresenceInfoFieldValueText* statustext = 
                TXIMPGetInterface< const MPresenceInfoFieldValueText >::From(
                        presenceField.FieldValue(),
                        MXIMPBase::EPanicIfUnknown );
                // now manufacture the message for the status text
                if( statustext && statustext->TextValue().Length() )
                    {
		                TPtrC bufferPtr (  statustext->TextValue() );
		                err = tbufC16tochar ( bufferPtr, tmpmsg );
		                if( KErrNotFound == err)
		                    {
		                    iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, err );
		                    }
		                userLen = strlen ( tmpmsg ) + 1; //for '\0'
		             }
                memcpy( smsg + totalLen, tmpmsg, userLen );
                totalLen += userLen + 1;
                }        
            }
        iSendId = iConnMan.DataHandler().SendDataL ( iStatus, smsg, totalLen );        
        SetActive();// signal the scheduler
        CleanupStack::PopAndDestroy ( 3 ); //tmpmsg,smsg,availability
        }
    LOGGER ( TXT("CPublishOwnPresencerequest::PublishOwnPresenceL End") );
    }
    

// End of file
