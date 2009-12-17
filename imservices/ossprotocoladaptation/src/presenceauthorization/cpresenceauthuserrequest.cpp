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
* Description:  Request for accepting add invite to the Network Server.
*
*/


#include <ximpprotocolconnectionhost.h>
#include "cpresenceauthuserrequest.h"
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
// CPresenceAuthUserRequest::CPresenceAuthUserRequest
// ---------------------------------------------------------------------------
//
CPresenceAuthUserRequest::CPresenceAuthUserRequest( 
						MOSSProtocolConnectionManager& aConnMan,
						TXIMPRequestId aRequestId ) :
    CActive( EPriorityNormal ),
    iRequestId( aRequestId ),
    iConnMan( aConnMan )
    {
    LOGGER ( TXT("::CPresenceAuthUserRequest Start") );
    CActiveScheduler::Add( this );
    LOGGER ( TXT("::CPresenceAuthUserRequest End") );
    }


// ---------------------------------------------------------------------------
// CPresenceAuthUserRequest::ConstructL
// ---------------------------------------------------------------------------
//
void CPresenceAuthUserRequest::ConstructL()
    {
    LOGGER ( TXT("CPresenceAuthUserRequest::ConstructL Start-End") );
    
    }


// ---------------------------------------------------------------------------
// CPresenceAuthUserRequest::NewL
// ---------------------------------------------------------------------------
//
CPresenceAuthUserRequest* CPresenceAuthUserRequest::NewL(
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
    {
    LOGGER ( TXT("CPresenceAuthUserRequest::NewL Start") );
    
    CPresenceAuthUserRequest* self = 
    				new( ELeave ) CPresenceAuthUserRequest( aConnMan, aRequestId );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    
    LOGGER ( TXT("CPresenceAuthUserRequest::NewL End") );
    return self;
    }


// ---------------------------------------------------------------------------
// CPresenceAuthUserRequest::NewLC
// ---------------------------------------------------------------------------
//
CPresenceAuthUserRequest* CPresenceAuthUserRequest::NewLC(
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
    {
    LOGGER ( TXT("CPresenceAuthUserRequest::NewLC Start") );
    
    CPresenceAuthUserRequest* self = 
    				 CPresenceAuthUserRequest::NewL( aConnMan, aRequestId );
    CleanupStack::PushL( self );
       
    LOGGER ( TXT("CPresenceAuthUserRequest::NewLC End") );
    return self;
    }

// ---------------------------------------------------------------------------
// CPresenceAuthUserRequest::~CPresenceAuthUserRequest
// ---------------------------------------------------------------------------
//
CPresenceAuthUserRequest::~CPresenceAuthUserRequest()
    {
    LOGGER ( TXT("CPresenceAuthUserRequest::~CPresenceAuthUserRequest Start") );

    CActive::Cancel();
    LOGGER ( TXT("CPresenceAuthUserRequest::~CPresenceAuthUserRequest End") );
    }


// ---------------------------------------------------------------------------
// CPresenceAuthUserRequest::DoCancel()
// ---------------------------------------------------------------------------
//
void CPresenceAuthUserRequest::DoCancel()
    {
    LOGGER ( TXT("CPresenceAuthUserRequest::DoCancel Start") );
    }


// ---------------------------------------------------------------------------
// CPresenceAuthUserRequest::RunL()
// ---------------------------------------------------------------------------
//
void CPresenceAuthUserRequest::RunL()
    {
    LOGGER ( TXT("CPresenceAuthUserRequest::RunL Start") );
    
   	message_hdr_resp* msg_struct = NULL;
	User::LeaveIfError( iStatus.Int() );
    char* pResponse = NULL;  
	pResponse = iConnMan.DataHandler().ResponseL( iSendId ); 
	
	msg_struct = ( message_hdr_resp* )pResponse ;

	if( !( msg_struct->response ) )
	{
		//for all other error codes like ssl related are mapped to general error
	  iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KXIMPErrServiceGeneralError );
	}
	else
	{
	  iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KErrNone );
	}
	free(pResponse);
	delete this;
	LOGGER ( TXT("CPresenceAuthUserRequest::RunL End") );
    }


// ---------------------------------------------------------------------------
// CPresenceAuthUserRequest::RunError
// ---------------------------------------------------------------------------
//
TInt CPresenceAuthUserRequest::RunError( TInt  aError )
    {
    LOGGER ( TXT("CPresenceAuthUserRequest::RunError Start") );
    
    iConnMan.HandleToHost().HandleRequestCompleted( iRequestId, aError );
    
    delete this;
	LOGGER ( TXT("CPresenceAuthUserRequest::RunError End") );
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// CPresenceAuthUserRequest::PresenceAuthUserRequest
// ---------------------------------------------------------------------------
//
void CPresenceAuthUserRequest::PresenceAuthUserRequestL(	
									const MXIMPIdentity & aIdentity,
                                    const MPresenceInfoFilter &/*aPif*/ )
    {   
    LOGGER ( TXT("CPresenceAuthUserRequest::PresenceAuthUserRequest Start") );

	char *smsg = NULL;
	int totalLen = 0;
	
    message_hdr_req msgHdr = {0,};
	msgHdr.message_type = EAccept_Contact_Request ;
	TInt headerSize = sizeof( message_hdr_req ) ;

	charFormatData tmpmsgData = OssProtocolAdapUtils::ConvertTUint16ToCharLC( aIdentity.Identity() );
	char* tmpmsg = tmpmsgData.data;
	TInt  tmpmsgLength = tmpmsgData.dataSize;	
	totalLen = headerSize + tmpmsgLength;
	 
	smsg = ( char* ) User::AllocLC(totalLen);
	memcpy( smsg, &msgHdr, headerSize );
	memcpy ( smsg + headerSize, tmpmsg, tmpmsgLength );
	
	iSendId = iConnMan.DataHandler().SendDataL ( iStatus, smsg, totalLen );

	// signal the scheduler
	SetActive();

	CleanupStack::PopAndDestroy ( 2 );	//smsg, tmpmsg.
	LOGGER ( TXT("CPresenceAuthUserRequest::PresenceAuthUserRequest End") );
    }


// End of file
