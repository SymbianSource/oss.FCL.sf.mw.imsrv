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
* Description:  Login Request to the Network Server.
*
*/


#include "cossprotocolloginrequest.h"
#include <ximpprotocolconnectionhost.h>
#include "mossprotocolconnectionmanager.h"
#include "ossprotocolpluginlogger.h"
#include "cossprotocolconnection.h"
#include "cossprotocolconnectionmanager.h"
#include <stdlib.h>
#include "stringutils.h"
#include <string.h>
#include "msgliterals.h"
#include "msg_enums.h"
#include "xmppparameters.h"
#include "waittimer.h"
#include <e32math.h>

#include <ximperrors.hrh>

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// COSSProtocolLoginRequest::COSSProtocolLoginRequest()
// ---------------------------------------------------------------------------
//
COSSProtocolLoginRequest::COSSProtocolLoginRequest (
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId ) :
		CActive ( CActive::EPriorityStandard  ),
		iRequestId ( aRequestId ),
		iConnMan ( aConnMan )
	{
	LOGGER ( TXT ( "COSSProtocolLoginRequest::COSSProtocolLoginRequest Start" ) );
	CActiveScheduler::Add ( this );
	LOGGER ( TXT ( "COSSProtocolLoginRequest::COSSProtocolLoginRequest End" ) );
	}

// COSSProtocolLoginRequest::ConstructL()
// ---------------------------------------------------------------------------
//
void COSSProtocolLoginRequest::ConstructL()
	{
	LOGGER ( TXT ( "COSSProtocolLoginRequest::COSSProtocolLoginRequest Start-End" ) );
	LOGGER ( TXT ( "COSSProtocolLoginRequest::COSSProtocolLoginRequest End" ) );
	}


// ---------------------------------------------------------------------------
// COSSProtocolLoginRequest::NewL()
// ---------------------------------------------------------------------------
//
COSSProtocolLoginRequest* COSSProtocolLoginRequest::NewL (
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
	{
	LOGGER ( TXT ( "COSSProtocolLoginRequest::NewL Start" ) );

	COSSProtocolLoginRequest* self =
	    new ( ELeave ) COSSProtocolLoginRequest ( aConnMan, aRequestId );
	CleanupStack::PushL ( self );
	self->ConstructL();
	CleanupStack::Pop ( self );

	LOGGER ( TXT ( "COSSProtocolLoginRequest::NewL End" ) );
	return self;
	}


// ---------------------------------------------------------------------------
// COSSProtocolLoginRequest::NewLC()
// ---------------------------------------------------------------------------
//
COSSProtocolLoginRequest* COSSProtocolLoginRequest::NewLC (
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
	{
	LOGGER ( TXT ( "COSSProtocolLoginRequest::NewLC Start" ) );

	COSSProtocolLoginRequest* self =
	    COSSProtocolLoginRequest::NewL ( aConnMan, aRequestId );
	CleanupStack::PushL ( self );

	LOGGER ( TXT ( "COSSProtocolLoginRequest::NewLC End" ) );
	return self;
	}

// ---------------------------------------------------------------------------
// COSSProtocolLoginRequest::~COSSProtocolLoginRequest()
// ---------------------------------------------------------------------------
//
COSSProtocolLoginRequest::~COSSProtocolLoginRequest()
	{
	LOGGER ( TXT ( "::~COSSProtocolLoginRequest Start-End" ) );
	Cancel();
	if( iUserName )
	    {
	    delete iUserName;
	    }

	LOGGER ( TXT ( "::~COSSProtocolLoginRequest End\n" ) );
	}


// ---------------------------------------------------------------------------
// COSSProtocolLoginRequest::DoCancel()
// ---------------------------------------------------------------------------
//
void COSSProtocolLoginRequest::DoCancel()
	{
	}


// ---------------------------------------------------------------------------
// COSSProtocolLoginRequest::RunL()
// ---------------------------------------------------------------------------
//
void COSSProtocolLoginRequest::RunL()
	{
	LOGGER ( TXT ( "COSSProtocolLoginRequest::RunL Start" ) );
	message_hdr_resp* msg_struct = NULL;
	User::LeaveIfError ( iStatus.Int() );
    char* pResponse = NULL;  
	pResponse = iConnMan.DataHandler().ResponseL ( iSendId );

	msg_struct = ( message_hdr_resp* )pResponse ;
	if( !( msg_struct->response ) )
	{
		switch( msg_struct->error_type )
		{
		case ELOGIN_NETWORK_ERROR:
		    LOGGER ( TXT ( "COSSProtocolLoginRequest::RunL ELOGIN_NETWORK_ERROR" ) );
		case ELOGIN_NONE_SPECIFIED:
		    //XImpfw is not giving any error code for canceling accespoint so we are using KErrDisconnected
		    //once error code is provided by ximpfw we can remove 
		    LOGGER ( TXT ( "COSSProtocolLoginRequest::RunL ELOGIN_NONE_SPECIFIED" ) );
		    iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KErrDisconnected );
		    break;
		case ELOGIN_AUTHENTICATION: //The username or password was invalid. 
		    LOGGER ( TXT ( "COSSProtocolLoginRequest::RunL ELOGIN_AUTHENTICATION" ) );
			   iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KXIMPErrServiceAuthenticationFailed );
		       break;
		default:  //for all other error codes like ssl related are mapped to general error ELOGIN_AUTHORIZATION
                LOGGER ( TXT ( "COSSProtocolLoginRequest::RunL defualt" ) );
			   iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KXIMPErrServiceGeneralError );
		       break;       
		}	
	}
	else
	    {
	    iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KErrNone );
	    MPresenceBuddyInfo2* buddyPresInfo = MPresenceBuddyInfo2::NewLC();
	    MPresenceCacheWriter2* presenceCacheWriter = MPresenceCacheWriter2::CreateWriterL();
	    HBufC* userName = HBufC::NewLC( iUserName->Length() + iConnMan.ServiceName().Length() + KColon().Length() );     
	    TPtr namePtr( userName->Des() );
	    namePtr.Zero();
	    namePtr.Append(iConnMan.ServiceName()); // prepend service name
	    namePtr.Append(KColon);
	    namePtr.Append(iUserName->Des() );
	    buddyPresInfo->SetIdentityL(namePtr);
	    LOGGER ( TXT ( "COSSProtocolLoginRequest::owndata:%S " ), userName ); 
	    CleanupStack::PopAndDestroy();//userName      
	    _LIT(KAvailable,"available");//since not getting the own status from downlayer.here 
	    _LIT(KStatusTest,"Online");//is hardcoded once logged in is successfully
	    HBufC16 *message = KAvailable().AllocLC();      
	    buddyPresInfo->SetAvailabilityL( MPresenceBuddyInfo2::EAvailable,*message);                 
	    HBufC16 *statusmessage = KStatusTest().AllocLC();
	    buddyPresInfo->SetStatusMessageL(*statusmessage);

	    TInt cacheerror = presenceCacheWriter->WritePresenceL(buddyPresInfo);
	    User::LeaveIfError ( cacheerror);
	    CleanupStack::PopAndDestroy ( 3 ); //buddyPresInfo, message ,statusmessage
	    delete presenceCacheWriter ;
	    }
	   
	    
	free( pResponse );
	delete this;

	LOGGER ( TXT ( "COSSProtocolLoginRequest::RunL End" ) );

	}


// ---------------------------------------------------------------------------
// COSSProtocolLoginRequest::RunError()
// ---------------------------------------------------------------------------
//
TInt COSSProtocolLoginRequest::RunError ( TInt  aError )
	{
	LOGGER ( TXT ( "COSSProtocolLoginRequest::RunError Start" ) );

	iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, aError );

	delete this;
	LOGGER ( TXT ( "COSSProtocolLoginRequest::RunError End" ) );
	return KErrNone;
	}


// ---------------------------------------------------------------------------
// COSSProtocolLoginRequest::IssueLoginRequestL()
// ---------------------------------------------------------------------------
//
void COSSProtocolLoginRequest::IssueLoginRequestL()
	{
	LOGGER ( TXT ( "COSSProtocolLoginRequest::IssueLoginRequestL Start" ) );

	char *smsg = NULL;
	char *tmpmsg = NULL;
	message_hdr_req msgHdr = {0,};
	int userLen = 0;
	int totalLen = 0;
	int err = 0;

	smsg = ( char* ) User::AllocLC(MAX_MSG_SIZE);

	tmpmsg = ( char* ) User::AllocLC(MAX_MSG_SIZE);

	HBufC* buffer = HBufC::NewLC ( MAX_MSG_SIZE );
	TPtr bufferPtr ( buffer->Des() );
	bufferPtr.Zero();
	memset ( smsg, '\0', MAX_MSG_SIZE );
	memset ( tmpmsg, '\0', MAX_MSG_SIZE );

	msgHdr.message_type = ELogin_Request;
	iConnMan.DataHandler().IncreaseOpId();
	TInt Opid = iConnMan.DataHandler().GetOpId();
	msgHdr.request_id = Opid;
	memcpy ( smsg, &msgHdr, sizeof ( message_hdr_req ) );
	totalLen += sizeof ( message_hdr_req );
	bufferPtr.Zero();

	if ( iConnMan.UserName().Length() == 0 && iConnMan.Password().Length() == 0 ) //if username and pwd are not passed from client.read default settings
		{
		bufferPtr.Append ( iConnMan.XmppParams().UserName() );
		iUserName = bufferPtr.AllocL();
		LOGGER ( TXT ( "COSSProtocolLoginRequest::UserName:%S " ), & ( iConnMan.XmppParams().UserName() ) );
		memset ( tmpmsg, '\0', MAX_MSG_SIZE );
		err = tbufC16tochar ( bufferPtr, tmpmsg );
		if( -1 == err)
		{
		iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, err );
		}
		userLen = strlen ( tmpmsg ) + 1; //for '\0'
		memcpy ( smsg + totalLen, tmpmsg, userLen );
		totalLen += userLen;

		bufferPtr.Zero();
		bufferPtr.Append ( iConnMan.XmppParams().Passwd() );
		memset ( tmpmsg, '\0', MAX_MSG_SIZE );
		err = tbufC16tochar ( bufferPtr, tmpmsg );
		userLen = strlen ( tmpmsg ) + 1; //for '\0'
		memcpy ( smsg + totalLen, tmpmsg, userLen );
		totalLen += userLen;
		}
	else
		{
		iUserName =  iConnMan.UserName().AllocL();
		bufferPtr.Append ( iConnMan.UserName() );
		LOGGER ( TXT ( "COSSProtocolLoginRequest::UserName:%S " ), & ( iConnMan.UserName() ) );
		memset ( tmpmsg, '\0', MAX_MSG_SIZE );
		err = tbufC16tochar ( bufferPtr, tmpmsg );
		userLen = strlen ( tmpmsg ) + 1; //for '\0'
		memcpy ( smsg + totalLen, tmpmsg, userLen );
		totalLen += userLen;

		bufferPtr.Zero();
		bufferPtr.Append ( iConnMan.Password() );
		memset ( tmpmsg, '\0', MAX_MSG_SIZE );
		err = tbufC16tochar ( bufferPtr, tmpmsg );
		userLen = strlen ( tmpmsg ) + 1; //for '\0'
		memcpy ( smsg + totalLen, tmpmsg, userLen );
		totalLen += userLen;

		}

	bufferPtr.Zero();

	bufferPtr.Append ( iConnMan.XmppParams().ServerAddress() );
	LOGGER ( TXT ( "COSSProtocolLoginRequest::RunL:ServerAddress:%S " ), & ( iConnMan.XmppParams().ServerAddress() ) );
	memset ( tmpmsg, '\0', MAX_MSG_SIZE );
	err = tbufC16tochar ( bufferPtr, tmpmsg );
	userLen = strlen ( tmpmsg ) + 1; //for '\0'
	memcpy ( smsg + totalLen, tmpmsg, userLen );
	totalLen += userLen;

	//resource
	bufferPtr.Zero();
    bufferPtr.Append ( 	GenResourceId(iConnMan.XmppParams().Resource()) );
	memset ( tmpmsg, '\0', MAX_MSG_SIZE );
	err = tbufC16tochar ( bufferPtr, tmpmsg );
	userLen = strlen ( tmpmsg ) + 1; //for '\0'
	memcpy ( smsg + totalLen, tmpmsg, userLen );
	totalLen += userLen;

	//ssl
	bufferPtr.Zero();
	bufferPtr.AppendNum ( iConnMan.XmppParams().Ssl() );
	memset ( tmpmsg, '\0', MAX_MSG_SIZE );
	err = tbufC16tochar ( bufferPtr, tmpmsg );
	userLen = strlen ( tmpmsg ) + 1; //for '\0'
	memcpy ( smsg + totalLen, tmpmsg, userLen );
	totalLen += userLen;

	//ServerPort
	bufferPtr.Zero();
	bufferPtr.AppendNum ( iConnMan.XmppParams().ServerPort() );
	memset ( tmpmsg, '\0', MAX_MSG_SIZE );
	err = tbufC16tochar ( bufferPtr, tmpmsg );
	userLen = strlen ( tmpmsg ) + 1; //for '\0'
	memcpy ( smsg + totalLen, tmpmsg, userLen );
	totalLen += userLen;

	//IapId
	bufferPtr.Zero();
	bufferPtr.AppendNum ( iConnMan.XmppParams().IapId() );
	memset ( tmpmsg, '\0', MAX_MSG_SIZE );
	err = tbufC16tochar ( bufferPtr, tmpmsg );
	userLen = strlen ( tmpmsg ) + 1; //for '\0'
	memcpy ( smsg + totalLen, tmpmsg, userLen );
	totalLen += userLen;
	
	//connmgr_bus
	bufferPtr.Zero();
	bufferPtr.Append ( iConnMan.XmppParams().ConnMgrBus() );
	memset ( tmpmsg, '\0', MAX_MSG_SIZE );
	err = tbufC16tochar ( bufferPtr, tmpmsg );
	userLen = strlen ( tmpmsg ) + 1; //for '\0'
	memcpy ( smsg + totalLen, tmpmsg, userLen );
	totalLen += userLen;
	
	//connmgr_path
	bufferPtr.Zero();
	bufferPtr.Append ( iConnMan.XmppParams().ConnMgrPath() );
	memset ( tmpmsg, '\0', MAX_MSG_SIZE );
	err = tbufC16tochar ( bufferPtr, tmpmsg );
	userLen = strlen ( tmpmsg ) + 1; //for '\0'
	memcpy ( smsg + totalLen, tmpmsg, userLen );
	totalLen += userLen;
	
	//protocol
	bufferPtr.Zero();
	bufferPtr.Append ( iConnMan.XmppParams().Protocol() );
	memset ( tmpmsg, '\0', MAX_MSG_SIZE );
	err = tbufC16tochar ( bufferPtr, tmpmsg );
	userLen = strlen ( tmpmsg ) + 1; //for '\0'
	memcpy ( smsg + totalLen, tmpmsg, userLen );
	totalLen += userLen;

#ifdef __WINSCW__
	//ProxyServer
	bufferPtr.Zero();
	bufferPtr.Append ( iConnMan.XmppParams().ProxyServer() );
	memset ( tmpmsg, '\0', MAX_MSG_SIZE );
	err = tbufC16tochar ( bufferPtr, tmpmsg );
	userLen = strlen ( tmpmsg ) + 1; //for '\0'
	memcpy ( smsg + totalLen, tmpmsg, userLen );
	totalLen += userLen;

	//ProxyPort
	bufferPtr.Zero();
	bufferPtr.AppendNum ( iConnMan.XmppParams().ProxyPort() );
	memset ( tmpmsg, '\0', MAX_MSG_SIZE );
	err = tbufC16tochar ( bufferPtr, tmpmsg );
	userLen = strlen ( tmpmsg ) + 1; //for '\0'
	memcpy ( smsg + totalLen, tmpmsg, userLen );
	totalLen += userLen;
#endif


	iSendId = iConnMan.DataHandler().SendDataL ( iStatus, smsg, totalLen );

	// signal the scheduler
	SetActive();
	CleanupStack::PopAndDestroy (buffer);
	CleanupStack::PopAndDestroy (tmpmsg);
	CleanupStack::PopAndDestroy (smsg);
	LOGGER ( TXT ( "COSSProtocolConnection::OpenSessionL() End" ) );
	}
// ---------------------------------------------------------------------------
// COSSProtocolLoginRequest::GenResourceId()
// ---------------------------------------------------------------------------
//
TPtrC COSSProtocolLoginRequest::GenResourceId( const TDesC& aResourceId )
    {
    	TBuf<KImpsMaxResourceIdLen> tempRId = aResourceId;
        //initialise client id
	    iResourceId.SetLength(0);
	    
	    //generate Resourse here
	    iResourceId.Append(tempRId);
		    
	    TTime time;
		time.HomeTime();
		TInt64 seed = time.Int64();
	    
	    TInt i = Math::Rand( seed );

		iResourceId.AppendFormat( _L("%d"), i);
	
		return iResourceId;
     }  

// End of file
