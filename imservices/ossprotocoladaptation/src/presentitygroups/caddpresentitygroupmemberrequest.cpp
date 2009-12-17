/*
* Copyright (c) 2007-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Add Presentity Group Member Request to the Network Server.
*
*/


#include <ximpprotocolconnectionhost.h>
#include "caddpresentitygroupmemberrequest.h"
#include "cossprotocolconnectionmanager.h"
#include "ossprotocolpluginlogger.h"

#include <ximpobjectfactory.h>
#include <protocolpresencedatahost.h>
#include <presenceobjectfactory.h>
#include <ximpobjectcollection.h>
#include <protocolpresentitygroupsdatahost.h>
#include <presentitygroupinfo.h>
#include <presentitygroupmemberinfo.h>
#include <ximpidentity.h>

#include <glib/gstrfuncs.h>
#include <gtypes.h>
#include <stdlib.h>
#include "stringutils.h"
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <glib/gprintf.h>
#include "msgliterals.h"
#include "msg_enums.h"
#include "ossprotocoladaptutils.h"
#include <avabilitytext.h>

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAddPresentityGroupMemberRequest::CAddPresentityGroupMemberRequest
// ---------------------------------------------------------------------------
//
CAddPresentityGroupMemberRequest::CAddPresentityGroupMemberRequest( 
						MOSSProtocolConnectionManager& aConnMan,
						TXIMPRequestId aRequestId ) :
    CActive( EPriorityNormal ),
    iRequestId( aRequestId ),
    iConnMan( aConnMan )
    {
    LOGGER ( TXT("::CAddPresentityGroupMemberRequest Start") );
    CActiveScheduler::Add( this );
    
    LOGGER ( TXT("::CAddPresentityGroupMemberRequest End") );
    }


// ---------------------------------------------------------------------------
// CAddPresentityGroupMemberRequest::ConstructL
// ---------------------------------------------------------------------------
//
void CAddPresentityGroupMemberRequest::ConstructL()
    {
    
    LOGGER ( TXT("CAddPresentityGroupMemberRequest::ConstructL Start-End") );
    iContactId = NULL;
    }





// ---------------------------------------------------------------------------
// CAddPresentityGroupMemberRequest::NewLC
// ---------------------------------------------------------------------------
//
CAddPresentityGroupMemberRequest* CAddPresentityGroupMemberRequest::NewLC(
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
    {
    LOGGER ( TXT("CAddPresentityGroupMemberRequest::NewLC Start") );
    
    CAddPresentityGroupMemberRequest* self = new( ELeave ) 
    			CAddPresentityGroupMemberRequest( aConnMan, aRequestId );
    CleanupStack::PushL( self );
    self->ConstructL();
     
    LOGGER ( TXT("CAddPresentityGroupMemberRequest::NewLC End") );
    return self;
    }

// ---------------------------------------------------------------------------
// CAddPresentityGroupMemberRequest::~CAddPresentityGroupMemberRequest
// ---------------------------------------------------------------------------
//
CAddPresentityGroupMemberRequest::~CAddPresentityGroupMemberRequest()
    {
    LOGGER ( TXT("::~CAddPresentityGroupMemberRequest Start") );
   
	CActive::Cancel();
	if(iContactId)
	    {
	    delete iContactId;
	    }
    LOGGER ( TXT("::~CAddPresentityGroupMemberRequest End") );
    }


// ---------------------------------------------------------------------------
// CAddPresentityGroupMemberRequest::DoCancel()
// ---------------------------------------------------------------------------
//
void CAddPresentityGroupMemberRequest::DoCancel()
    {
    LOGGER ( TXT("CAddPresentityGroupMemberRequest::DoCancel Start") );
   
    LOGGER ( TXT("CAddPresentityGroupMemberRequest::DoCancel End") );
    }


// ---------------------------------------------------------------------------
// CAddPresentityGroupMemberRequest::RunL()
// ---------------------------------------------------------------------------
//
void CAddPresentityGroupMemberRequest::RunL()
    {
    LOGGER ( TXT("CAddPresentityGroupMemberRequest::RunL Start") );
    message_hdr_resp* msg_struct = NULL;
    char* pResponse = NULL;  
	User::LeaveIfError( iStatus.Int() );
   
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
    //set presence as pending for the added contact
    MPresenceBuddyInfo2* buddyPresInfo = MPresenceBuddyInfo2::NewLC();

    MPresenceCacheWriter2* presenceCacheWriter = MPresenceCacheWriter2::CreateWriterL();
    CleanupDeletePushL(presenceCacheWriter);
    HBufC* name = HBufC::NewLC( iContactId->Length() + iConnMan.ServiceName().Length() + KColon().Length() );
    TPtr namePtr( name->Des() );
    namePtr.Zero();
    namePtr.Append(iConnMan.ServiceName() ); // prepend service name
    namePtr.Append(KColon);
    namePtr.Append(iContactId->Des() );
    buddyPresInfo->SetIdentityL(namePtr);
    LOGGER ( TXT ( "CPresenceNotificationHandler::ProcessIncomingDataL  :ContactName:%S " ), iContactId ); 
   
    buddyPresInfo->SetAnyFieldL(KExtensionKey,KPendingRequestExtensionValue());
    CleanupStack::PopAndDestroy(1);//name

    // Writing into Presence Cache
    TInt cacheerror = presenceCacheWriter->WritePresenceL(buddyPresInfo);
    User::LeaveIfError ( cacheerror);
    CleanupStack::PopAndDestroy(2);//presenceCacheWriter,buddyPresInfo
    
	iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KErrNone );
	}
	free( pResponse );
	delete this;
	LOGGER ( TXT("CAddPresentityGroupMemberRequest::RunL End") );
    }


// ---------------------------------------------------------------------------
// CAddPresentityGroupMemberRequest::RunError
// ---------------------------------------------------------------------------
//
TInt CAddPresentityGroupMemberRequest::RunError( TInt  aError )
    {
    LOGGER ( TXT("CAddPresentityGroupMemberRequest::RunError Start") );
    
    iConnMan.HandleToHost().HandleRequestCompleted( iRequestId, aError );
    delete this;
    
	LOGGER ( TXT("CAddPresentityGroupMemberRequest::RunError End") );
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// CAddPresentityGroupMemberRequest::AddPresentityGroupMemberL
// ---------------------------------------------------------------------------
//
void CAddPresentityGroupMemberRequest::AddPresentityGroupMemberL(
    const MXIMPIdentity& /*aGroupId*/,
    const MXIMPIdentity& aMemberId,
    const TDesC16& aMemberDisplayName)
    {   
    LOGGER ( TXT("CAddPresentityGroupMemberRequest::AddPresentityGroupMemberL Start") );
    if(iContactId)
        {
        delete iContactId;
        iContactId = NULL;
        }
    iContactId = aMemberId.Identity().AllocL();
  	char *smsg = NULL;
	int totalLen = 0;
    message_hdr_req msgHdr = {0,};
    msgHdr.message_type = EAdd_Contact_Request;	

	TInt headerLength = sizeof( message_hdr_req );
	totalLen += headerLength;

	// adding add contact
	charFormatData  memberIdentityData  = OssProtocolAdapUtils::ConvertTUint16ToCharLC( aMemberId.Identity() );
    char* memberIdentity  = memberIdentityData.data;    
	TInt memberIdLength = memberIdentityData.dataSize;
    totalLen += memberIdLength;
    
    charFormatData displayNameData = OssProtocolAdapUtils::ConvertTUint16ToCharLC( aMemberDisplayName ); 
    char* displayName = displayNameData.data;   	 	
	TInt displayNameLength = displayNameData.dataSize;    
    totalLen += displayNameLength;
    
	if ( totalLen > MAX_MSG_SIZE ) 
		{
		User::Leave(KErrArgument);		
		}
    
    //after getting size now allocate memory.
    smsg = ( char* ) User::AllocLC(totalLen);
    memset ( smsg, '\0', totalLen );
    
    memcpy( smsg, &msgHdr, sizeof( message_hdr_req ) ); //header
    memcpy( smsg + headerLength , memberIdentity , memberIdLength ); //id
    memcpy( smsg + headerLength + memberIdLength + 1 , displayName , displayNameLength ); //display name
        
	iSendId = iConnMan.DataHandler().SendDataL ( iStatus, smsg, totalLen );
    
    // signal the scheduler
	SetActive();

	CleanupStack::PopAndDestroy ( 3 );//smsg, memberIdentity, displayName. 
	
	LOGGER ( TXT("CAddPresentityGroupMemberRequest::AddPresentityGroupMemberL End") );
    }


// End of file
