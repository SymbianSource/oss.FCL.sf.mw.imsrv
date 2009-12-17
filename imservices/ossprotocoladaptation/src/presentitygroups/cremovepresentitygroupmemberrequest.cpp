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
* Description:  Remove presentity group member request to the network server
*
*/


#include <ximpprotocolconnectionhost.h>
#include "cremovepresentitygroupmemberrequest.h"
#include "mossprotocolconnectionmanager.h"
#include "cossprotocolconnectionmanager.h"
#include "ossprotocolpluginlogger.h"

#include <ximpobjectfactory.h>
#include <protocolpresencedatahost.h>
#include <ximpobjectcollection.h>
#include <protocolpresentitygroupsdatahost.h>
#include <presentitygroupinfo.h>
#include <presentitygroupmemberinfo.h>
#include <ximpidentity.h>
#include <ximpdatasubscriptionstate.h>

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

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CRemovePresentityGroupMemberRequest::CRemovePresentityGroupMemberRequest
// ---------------------------------------------------------------------------
//
CRemovePresentityGroupMemberRequest::CRemovePresentityGroupMemberRequest( 
					MOSSProtocolConnectionManager& aConnMan,
					TXIMPRequestId aRequestId ) :
    CActive( EPriorityNormal ),
    iRequestId( aRequestId ),
    iConnMan( aConnMan )
    {
    LOGGER ( TXT("::CRemovePresentityGroupMemberRequest Start") );
    CActiveScheduler::Add( this );
    
    LOGGER ( TXT("::CRemovePresentityGroupMemberRequest End") );
    }


// ---------------------------------------------------------------------------
// CRemovePresentityGroupMemberRequest::ConstructL
// ---------------------------------------------------------------------------
//
void CRemovePresentityGroupMemberRequest::ConstructL()
    {
    LOGGER ( TXT("CRemovePresentityGroupMemberRequest::ConstructL Start") );
    iUserId = NULL;
	LOGGER ( TXT("CRemovePresentityGroupMemberRequest::ConstructL End") );
    }



// ---------------------------------------------------------------------------
// CRemovePresentityGroupMemberRequest::NewLC
// ---------------------------------------------------------------------------
//
CRemovePresentityGroupMemberRequest* CRemovePresentityGroupMemberRequest::NewLC(
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
    {
    LOGGER ( TXT("CRemovePresentityGroupMemberRequest::NewLC Start") );
    
    CRemovePresentityGroupMemberRequest* self = new( ELeave ) 
    			CRemovePresentityGroupMemberRequest( aConnMan, aRequestId );
    CleanupStack::PushL( self );
    self->ConstructL();
  
       
    LOGGER ( TXT("CRemovePresentityGroupMemberRequest::NewLC End") );
    return self;
    }

// ---------------------------------------------------------------------------
// CRemovePresentityGroupMemberRequest::~CRemovePresentityGroupMemberRequest
// ---------------------------------------------------------------------------
//
CRemovePresentityGroupMemberRequest::~CRemovePresentityGroupMemberRequest()
    {
    LOGGER ( TXT("::~CRemovePresentityGroupMemberRequest Start") );
   
	CActive::Cancel();
    delete iUserId;
    LOGGER ( TXT("::~CRemovePresentityGroupMemberRequest End") );
    }


// ---------------------------------------------------------------------------
// CRemovePresentityGroupMemberRequest::DoCancel()
// ---------------------------------------------------------------------------
//
void CRemovePresentityGroupMemberRequest::DoCancel()
    {
    LOGGER ( TXT("CRemovePresentityGroupMemberRequest::DoCancel Start") );
  
    LOGGER ( TXT("CRemovePresentityGroupMemberRequest::DoCancel End") );
    }


// ---------------------------------------------------------------------------
// CRemovePresentityGroupMemberRequest::RunL()
// ---------------------------------------------------------------------------
//
void CRemovePresentityGroupMemberRequest::RunL()
    {
    LOGGER ( TXT("CRemovePresentityGroupMemberRequest::RunL Start") );
    message_hdr_resp* msg_struct = NULL;
    char* pResponse = NULL;  
	User::LeaveIfError( iStatus.Int() );
   
	pResponse = iConnMan.DataHandler().ResponseL ( iSendId );
	
	msg_struct = ( message_hdr_resp* )pResponse ;
	if( !( msg_struct->response ))
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
         if( iUserId )
             {
             HBufC* sxpId = HBufC::NewLC( iConnMan.ServiceName().Length() + iUserId->Length() +1 );
             TPtr sxpIdPtr( sxpId->Des() );
        
             sxpIdPtr.Zero();
             sxpIdPtr.Append( iConnMan.ServiceName() );
             sxpIdPtr.Append(KColon);
             sxpIdPtr.Append( *iUserId );
             MPresenceCacheWriter2* presenceCacheWriter = MPresenceCacheWriter2::CreateWriterL();
             TInt cacheerror = presenceCacheWriter->DeletePresenceL( sxpIdPtr );
             User::LeaveIfError ( cacheerror);
             CleanupStack::PopAndDestroy(); // sxpId
             delete presenceCacheWriter;
             presenceCacheWriter = NULL;
             delete iUserId;
             iUserId = NULL;
             }
         iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KErrNone );
        }

	free( pResponse );
	delete this;
	LOGGER ( TXT("CRemovePresentityGroupMemberRequest::RunL End") );
    }


// ---------------------------------------------------------------------------
// CRemovePresentityGroupMemberRequest::RunError
// ---------------------------------------------------------------------------
//
TInt CRemovePresentityGroupMemberRequest::RunError( TInt  aError )
    {
    LOGGER ( TXT("CRemovePresentityGroupMemberRequest::RunError Start") );
    
    iConnMan.HandleToHost().HandleRequestCompleted( iRequestId, aError );
    
    delete this;
	LOGGER ( TXT("CRemovePresentityGroupMemberRequest::RunError End") );
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// CRemovePresentityGroupMemberRequest::RemovePresentityGroupMemberL
// ---------------------------------------------------------------------------
//
void CRemovePresentityGroupMemberRequest::RemovePresentityGroupMemberL(
    const MXIMPIdentity& /*aGroupId*/,
    const MXIMPIdentity& aMemberId)
    {   
   
    LOGGER ( TXT("CRemovePresentityGroupMemberRequest::RemovePresentityGroupMemberL Start") );

	int userLen=0;
	int totalLen = 0;
	iUserId = aMemberId.Identity().AllocL();

	message_hdr_req msgHdr = {0,};	
    msgHdr.message_type = EDelete_Contact_Request;	
    
    TInt headerLength = sizeof( message_hdr_req );
	totalLen += headerLength;
	
	// adding add contact
	charFormatData tmpmsgData = OssProtocolAdapUtils::ConvertTUint16ToCharLC ( aMemberId.Identity() );
    char *tmpmsg = tmpmsgData.data;
    userLen = tmpmsgData.dataSize;
	totalLen += userLen;
	 
	User::LeaveIfError ( totalLen > MAX_MSG_SIZE );

	//now allocate memory.
	char* smsg = ( char* ) User::AllocLC( totalLen );
	memcpy( smsg, &msgHdr, headerLength );
	memcpy ( smsg + headerLength, tmpmsg, userLen );
  
	iSendId = iConnMan.DataHandler().SendDataL ( iStatus, smsg, totalLen );

	// signal the scheduler
	SetActive();

	CleanupStack::PopAndDestroy ( 2 );//smsg, tmpmsg.
  	
	LOGGER ( TXT("::RemovePresentityGroupMemberL End") );
    }


// End of file
