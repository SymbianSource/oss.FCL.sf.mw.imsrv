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
* Description:  Request for Rejecting add invite to the Network Server.
*
*/


#include <ximpprotocolconnectionhost.h>
#include "cwithdrawpresencegrantfrompresentityrequest.h"
#include "mossprotocolconnectionmanager.h"
#include "ossprotocolpluginlogger.h"
#include <presenceinfo.h>

#include <ximpobjectfactory.h>
#include <ximpobjectcollection.h>
#include <protocolpresentitygroupsdatahost.h>
#include <presentitygroupinfo.h>
#include <presentitygroupmemberinfo.h>
#include <ximpidentity.h>
#include <presenceinfofilter.h>

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
#include "waittimer.h"
#include <ximperrors.hrh>
#include "ossprotocoladaptutils.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CWithdrawPresenceGrantFromPresentityRequest::CWithdrawPresenceGrantFromPresentityRequest
// ---------------------------------------------------------------------------
//
CWithdrawPresenceGrantFromPresentityRequest::CWithdrawPresenceGrantFromPresentityRequest( 
						MOSSProtocolConnectionManager& aConnMan,
						TXIMPRequestId aRequestId ) :
    CActive( EPriorityNormal ),
    iRequestId( aRequestId ),
    iConnMan( aConnMan )
    {
    LOGGER ( TXT("::CWithdrawPresenceGrantFromPresentityRequest Start") );
    CActiveScheduler::Add( this );
    LOGGER ( TXT("::CWithdrawPresenceGrantFromPresentityRequest End") );
    }


// ---------------------------------------------------------------------------
// CWithdrawPresenceGrantFromPresentityRequest::ConstructL
// ---------------------------------------------------------------------------
//
void CWithdrawPresenceGrantFromPresentityRequest::ConstructL()
    {
    LOGGER ( TXT("CWithdrawPresenceGrantFromPresentityRequest::ConstructL Start-End") );
    
    }


// ---------------------------------------------------------------------------
// CWithdrawPresenceGrantFromPresentityRequest::NewL
// ---------------------------------------------------------------------------
//
CWithdrawPresenceGrantFromPresentityRequest* CWithdrawPresenceGrantFromPresentityRequest::NewL(
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
    {
    LOGGER ( TXT("CWithdrawPresenceGrantFromPresentityRequest::NewL Start") );
    
    CWithdrawPresenceGrantFromPresentityRequest* self = 
    				new( ELeave ) CWithdrawPresenceGrantFromPresentityRequest( aConnMan, aRequestId );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    
    LOGGER ( TXT("CWithdrawPresenceGrantFromPresentityRequest::NewL End") );
    return self;
    }


// ---------------------------------------------------------------------------
// CWithdrawPresenceGrantFromPresentityRequest::NewLC
// ---------------------------------------------------------------------------
//
CWithdrawPresenceGrantFromPresentityRequest* CWithdrawPresenceGrantFromPresentityRequest::NewLC(
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
    {
    LOGGER ( TXT("CWithdrawPresenceGrantFromPresentityRequest::NewLC Start") );
    
    CWithdrawPresenceGrantFromPresentityRequest* self = 
    				 CWithdrawPresenceGrantFromPresentityRequest::NewL( aConnMan, aRequestId );
    CleanupStack::PushL( self );
       
    LOGGER ( TXT("CWithdrawPresenceGrantFromPresentityRequest::NewLC End") );
    return self;
    }

// ---------------------------------------------------------------------------
// CWithdrawPresenceGrantFromPresentityRequest::~CWithdrawPresenceGrantFromPresentityRequest
// ---------------------------------------------------------------------------
//
CWithdrawPresenceGrantFromPresentityRequest::~CWithdrawPresenceGrantFromPresentityRequest()
    {
    LOGGER ( TXT("CWithdrawPresenceGrantFromPresentityRequest::~CWithdrawPresenceGrantFromPresentityRequest Start") );
    CActive::Cancel();
    LOGGER ( TXT("CWithdrawPresenceGrantFromPresentityRequest::~CWithdrawPresenceGrantFromPresentityRequest End") );
    }


// ---------------------------------------------------------------------------
// CWithdrawPresenceGrantFromPresentityRequest::DoCancel()
// ---------------------------------------------------------------------------
//
void CWithdrawPresenceGrantFromPresentityRequest::DoCancel()
    {
    LOGGER ( TXT("CWithdrawPresenceGrantFromPresentityRequest::DoCancel Start") );
    
  //  iConnMan.DataHandler().CancelSending( iSendId );
    
    LOGGER ( TXT("CWithdrawPresenceGrantFromPresentityRequest::DoCancel End") );
    }


// ---------------------------------------------------------------------------
// CWithdrawPresenceGrantFromPresentityRequest::RunL()
// ---------------------------------------------------------------------------
//
void CWithdrawPresenceGrantFromPresentityRequest::RunL()
    {
    LOGGER ( TXT("CWithdrawPresenceGrantFromPresentityRequest::RunL Start") );
    
   	message_hdr_resp* msg_struct = NULL;
   	char* pResponse = NULL;  
    TInt error_code(KErrNone);
	User::LeaveIfError( iStatus.Int() );
   
	pResponse = iConnMan.DataHandler().ResponseL( iSendId ); 
	
	msg_struct = ( message_hdr_resp* )pResponse ;
    error_code = msg_struct->error_type;
	if( !( msg_struct->response ) )
	{
	    iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, error_code );
	}
	else
	{
	  iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KErrNone );
	}

	free( pResponse );	
	delete this;
	LOGGER ( TXT("CWithdrawPresenceGrantFromPresentityRequest::RunL End") );
    }


// ---------------------------------------------------------------------------
// CWithdrawPresenceGrantFromPresentityRequest::RunError
// ---------------------------------------------------------------------------
//
TInt CWithdrawPresenceGrantFromPresentityRequest::RunError( TInt  aError )
    {
    LOGGER ( TXT("CWithdrawPresenceGrantFromPresentityRequest::RunError Start") );
    
    iConnMan.HandleToHost().HandleRequestCompleted( iRequestId, aError );
    
    delete this;
	LOGGER ( TXT("CWithdrawPresenceGrantFromPresentityRequest::RunError End") );
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// CWithdrawPresenceGrantFromPresentityRequest::WithdrawPresenceGrantFromPresentityL
// ---------------------------------------------------------------------------
//
void CWithdrawPresenceGrantFromPresentityRequest::WithdrawPresenceGrantFromPresentityL(
													const MXIMPIdentity& aIdentity)
    {   
    LOGGER ( TXT("CWithdrawPresenceGrantFromPresentityRequest::WithdrawPresenceGrantFromPresentity Start") );
   	char *smsg 		= NULL;
	char *tmpmsg 	= NULL;	
	int userLen 	= 0;
	int totalLen	= 0;

    message_hdr_req msgHdr 	= {0,};
	msgHdr.message_type 	= EReject_Contact_Request ;
    
    TInt headerLength = sizeof( message_hdr_req );
	totalLen += headerLength;
	// adding add contact
	charFormatData tmpmsgData = OssProtocolAdapUtils::ConvertTUint16ToCharLC( aIdentity.Identity() );
    tmpmsg 	= tmpmsgData.data;
    userLen = tmpmsgData.dataSize;	
	totalLen += userLen;
	 
	 if ( totalLen > MAX_MSG_SIZE ) 
    	{
		User::Leave(KErrArgument);		
    	}
    	
    smsg = ( char* ) User::AllocLC(totalLen);
    memcpy( smsg, &msgHdr, headerLength );
	memcpy ( smsg + headerLength, tmpmsg, userLen );
    
	iSendId = iConnMan.DataHandler().SendDataL ( iStatus, smsg, totalLen );

	// signal the scheduler
	SetActive();

	CleanupStack::PopAndDestroy ( 2 );//smsg, tmpmsg. 	
	
	LOGGER ( TXT("CWithdrawPresenceGrantFromPresentityRequest::WithdrawPresenceGrantFromPresentity End") );
    }



// End of file
