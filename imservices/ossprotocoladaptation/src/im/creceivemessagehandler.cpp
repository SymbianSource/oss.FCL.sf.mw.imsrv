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
* Description:  implementation of receive message handler
*
*/


#include <ximpprotocolconnectionhost.h>
#include "creceivemessagehandler.h"
#include "mossprotocolconnectionmanager.h"
#include "ossprotocolpluginlogger.h"
#include "waittimer.h"
#include "cossprotocolconnectionmanager.h"
#include <ximpobjectfactory.h>
#include <ximpobjectcollection.h>
#include <protocolpresentitygroupsdatahost.h>
#include <presentitygroupinfo.h>
#include <presentitygroupmemberinfo.h>
#include <ximpidentity.h>
#include <protocolpresencepublishingdatahost.h>
#include <protocolpresencedatahost.h>
#include <presenceobjectfactory.h>
#include <presencegrantrequestinfo.h>
#include <personpresenceinfo.h>
#include <servicepresenceinfo.h>
#include <devicepresenceinfo.h>
#include <presenceinfo.h>
#include <presenceinfofield.h>
#include <presenceinfofieldcollection.h>
#include <presenceinfofieldvalueenum.h>
#include <presenceinfofieldvaluetext.h>
#include <ximpcontext.h>
#include <ximpclient.h>
#include <devicepresenceinfo.h>
#include <protocolpresencewatchingdatahost.h>
#include <presencegrantrequestinfo.h>
#include <protocolpresenceauthorizationdatahost.h>
#include <e32des16.h>
#include <imconversationinfo.h>
#include <imobjectfactory.h>
#include <protocolimdatahost.h>
#include <protocolimconversationdatahost.h>
#include <glib/gprintf.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib/gstrfuncs.h>
#include "ossprotocoladaptutils.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CReceiveMessageHandler::CReceiveMessageHandler
// ---------------------------------------------------------------------------
//
CReceiveMessageHandler::CReceiveMessageHandler (
    MOSSProtocolConnectionManager& aConnMan ) :

		CActive ( EPriorityNormal ),
		iConnMan ( aConnMan )
	{
	LOGGER ( TXT ( "::CReceiveMessageHandler Start" ) );
	CActiveScheduler::Add ( this );

	LOGGER ( TXT ( "::CReceiveMessageHandler End" ) );
	}


// ---------------------------------------------------------------------------
// CReceiveMessageHandler::ConstructL
// ---------------------------------------------------------------------------
//
void CReceiveMessageHandler::ConstructL()
	{
	LOGGER ( TXT ( "CReceiveMessageHandler::ConstructL Start-End" ) );


	}


// ---------------------------------------------------------------------------
// CReceiveMessageHandler::NewL
// ---------------------------------------------------------------------------
//
CReceiveMessageHandler* CReceiveMessageHandler::NewL (
    MOSSProtocolConnectionManager& aConnMan )
	{
	LOGGER ( TXT ( "CReceiveMessageHandler::NewL Start" ) );

	CReceiveMessageHandler* self = new ( ELeave )
	CReceiveMessageHandler ( aConnMan );
	CleanupStack::PushL ( self );
	self->ConstructL();
	CleanupStack::Pop ( self );

	LOGGER ( TXT ( "CReceiveMessageHandler::NewL End" ) );
	return self;
	}



// ---------------------------------------------------------------------------
// CReceiveMessageHandler::~CReceiveMessageHandler
// ---------------------------------------------------------------------------
//
CReceiveMessageHandler::~CReceiveMessageHandler()
	{
	LOGGER ( TXT ( "::~CReceiveMessageHandler Start" ) );

	Cancel();

	LOGGER ( TXT ( "::~CReceiveMessageHandler End" ) );
	}


// ---------------------------------------------------------------------------
// CReceiveMessageHandler::DoCancel()
// ---------------------------------------------------------------------------
//
void CReceiveMessageHandler::DoCancel()
	{
	LOGGER ( TXT ( "CReceiveMessageHandler::DoCancel Start" ) );

	iConnMan.DataHandler().CancelListeningMsg();

	LOGGER ( TXT ( "CReceiveMessageHandler::DoCancel End" ) );
	}

// ---------------------------------------------------------------------------
// CReceiveMessageHandler::RunL()
// ---------------------------------------------------------------------------
//
void CReceiveMessageHandler::RunL()
	{
	LOGGER ( TXT ( "CReceiveMessageHandler::RunL Start" ) );

	// something is coming from the xmpp server
	User::LeaveIfError ( iStatus.Int() );
	
	TRAPD( error, ProcessIncomingDataL() );
    if ( error != KErrNone )
    {
    	Cancel();
    }
   
    // start listening again for next incoming message
	StartListeningL();

	LOGGER ( TXT ( "CReceiveMessageHandler::RunL End" ) );
	}

// ---------------------------------------------------------------------------
// CReceiveMessageHandler::ProcessIncomingDataL()
// ---------------------------------------------------------------------------
//
void CReceiveMessageHandler::ProcessIncomingDataL()
	{
	LOGGER ( TXT ( "CReceiveMessageHandler::ProcessIncomingDataL Start" ) );
	
	char* pResponse = iConnMan.DataHandler().ResponseL ( 1 );
	CleanupStack::PushL( pResponse );
	
	//-----Response format--------
	//|------|------/0|-------/0|
	//|header|sender/0|message/0|
	
	//parse sender.
	char* sender = pResponse + sizeof( message_hdr_resp );
	HBufC16 *sendername = OssProtocolAdapUtils::ConvertCharToTUint16LC(sender); 
	
	//parse message.
	char* recvdmessage = pResponse + sizeof( message_hdr_resp ) + strlen(sender) + 1;
    HBufC16 *message = OssProtocolAdapUtils::ConvertCharToTUint16LC(recvdmessage);
		
	MXIMPObjectFactory& objFact = iConnMan.HandleToHost().ObjectFactory();
	MImObjectFactory& imObjFact = iConnMan.GetImHost().ImObjectFactory();
	MXIMPIdentity* identity = objFact.NewIdentityLC();
	MImConversationInfo* convinfo = imObjFact.NewImConversationInfoLC();
	
	identity->SetIdentityL ( *sendername );
	convinfo->SetMessageIdL ( identity );
	convinfo->SetTextMessageL ( *message );   //SetTextMessageL(const TDesC16& aMessage )
	iConnMan.GetImHost().ConversationDataHost().HandleNewTextMessageL ( convinfo );
	
	CleanupStack::Pop( 2 ); //convinfo,identity
	CleanupStack::PopAndDestroy( 3 ); //message,sendername,pResponse. 
	
	LOGGER ( TXT ( "CReceiveMessageHandler::ProcessIncomingDataL End" ) );
	}


// ---------------------------------------------------------------------------
// CReceiveMessageHandler::RunError
// ---------------------------------------------------------------------------
//
TInt CReceiveMessageHandler::RunError ( TInt  aError )
	{
	LOGGER ( TXT ( "CReceiveMessageHandler::RunError Start %d" ), aError );

	// restart listening incoming data
	iConnMan.DataHandler().ListenIncomingMsg ( iStatus );
	SetActive();

	LOGGER ( TXT ( "CReceiveMessageHandler::RunError End" ) );
	return KErrNone;
	}

// ---------------------------------------------------------------------------
// CReceiveMessageHandler::StartListeningL
// ---------------------------------------------------------------------------
//
void CReceiveMessageHandler::StartListeningL()
	{
	LOGGER ( TXT ( "CReceiveMessageHandler::StartListeningL Start" ) );

	// Ready to receive notification from the server
	TInt count = 0;

	// signal the scheduler

	if ( ! ( this->IsActive() ) )
		{
		count = iConnMan.DataHandler().ListenIncomingMsg ( iStatus );
		SetActive();
		}

	for ( TInt x ( 0 ) ;  x < count ; ++x )
		{
		ProcessIncomingDataL();
		}

	LOGGER ( TXT ( "CReceiveMessageHandler::StartListeningL End" ) );
	}



// End of file
