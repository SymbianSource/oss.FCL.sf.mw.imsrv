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
* Description:  server error handler
*
*/


#include <ximpprotocolconnectionhost.h>
#include "cossprotocolservererrorhandler.h"
#include "mossprotocolconnectionmanager.h"
#include "ossprotocolpluginlogger.h"
#include "waittimer.h"
#include "cossprotocolconnectionmanager.h"

#include <ximpobjectfactory.h>
#include <ximpobjectcollection.h>
#include <e32des16.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "msgliterals.h"
#include <gtypes.h>

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// COssprotocolServerErrorHandler::COssprotocolServerErrorHandler
// ---------------------------------------------------------------------------
//
COssprotocolServerErrorHandler::COssprotocolServerErrorHandler (
    MOSSProtocolConnectionManager& aConnMan ) :
		CActive ( EPriorityNormal ),
		iConnMan ( aConnMan )
	{
	LOGGER ( TXT ( "COssprotocolServerErrorHandler::COssprotocolServerErrorHandler Start" ) );
	CActiveScheduler::Add ( this );

	LOGGER ( TXT ( "COssprotocolServerErrorHandler::COssprotocolServerErrorHandler End" ) );
	}


// ---------------------------------------------------------------------------
// COssprotocolServerErrorHandler::ConstructL
// ---------------------------------------------------------------------------
//
void COssprotocolServerErrorHandler::ConstructL()
	{
	LOGGER ( TXT ( "COssprotocolServerErrorHandler::ConstructL Start-End" ) );

	}


// ---------------------------------------------------------------------------
// COssprotocolServerErrorHandler::NewL
// ---------------------------------------------------------------------------
//
COssprotocolServerErrorHandler* COssprotocolServerErrorHandler::NewL (
    MOSSProtocolConnectionManager& aConnMan )
	{
	LOGGER ( TXT ( "COssprotocolServerErrorHandler::NewL Start" ) );

	COssprotocolServerErrorHandler* self = new ( ELeave )
	COssprotocolServerErrorHandler ( aConnMan );
	CleanupStack::PushL ( self );
	self->ConstructL();
	CleanupStack::Pop ( self );

	LOGGER ( TXT ( "COssprotocolServerErrorHandler::NewL End" ) );
	return self;
	}


// ---------------------------------------------------------------------------
// COssprotocolServerErrorHandler::NewLC
// ---------------------------------------------------------------------------
//
COssprotocolServerErrorHandler* COssprotocolServerErrorHandler::NewLC (
    MOSSProtocolConnectionManager& aConnMan )
	{
	LOGGER ( TXT ( "COssprotocolServerErrorHandler::NewLC Start" ) );

	COssprotocolServerErrorHandler* self =
	    COssprotocolServerErrorHandler::NewL ( aConnMan );
	CleanupStack::PushL ( self );

	LOGGER ( TXT ( "COssprotocolServerErrorHandler::NewLC End" ) );
	return self;
	}

// ---------------------------------------------------------------------------
// COssprotocolServerErrorHandler::~COssprotocolServerErrorHandler
// ---------------------------------------------------------------------------
//
COssprotocolServerErrorHandler::~COssprotocolServerErrorHandler()
	{
	LOGGER ( TXT ( "::~COssprotocolServerErrorHandler Start" ) );

	Cancel();

	LOGGER ( TXT ( "::~COssprotocolServerErrorHandler End" ) );
	}


// ---------------------------------------------------------------------------
// COssprotocolServerErrorHandler::DoCancel()
// ---------------------------------------------------------------------------
//
void COssprotocolServerErrorHandler::DoCancel()
	{
	LOGGER ( TXT ( "COssprotocolServerErrorHandler::DoCancel Start" ) );

	iConnMan.DataHandler().CancelListeningServerErrors();

	LOGGER ( TXT ( "COssprotocolServerErrorHandler::DoCancel End" ) );
	}

// ---------------------------------------------------------------------------
// COssprotocolServerErrorHandler::RunL()
// ---------------------------------------------------------------------------
//
void COssprotocolServerErrorHandler::RunL()
	{
	LOGGER ( TXT ( "COssprotocolServerErrorHandler::RunL Start" ) );

	// something is coming from the xmpp server
	User::LeaveIfError ( iStatus.Int() );

	ProcessIncomingDataL();
//	StartListeningL();

	LOGGER ( TXT ( "COssprotocolServerErrorHandler::RunL End" ) );
	}

// ---------------------------------------------------------------------------
// COssprotocolServerErrorHandler::ProcessIncomingDataL()
// ---------------------------------------------------------------------------
//
void COssprotocolServerErrorHandler::ProcessIncomingDataL()
	{
	LOGGER ( TXT ( "COssprotocolServerErrorHandler::ProcessIncomingDataL Start" ) );
	TInt senderidlen = 0;
	TInt messagelen = 0;
	char* sender = NULL;
    char* recvdmessage = NULL;
    guint messagetype = NULL;
    guint time;
    char* pResponse = NULL, *pOrigResponse = NULL;  
	User::LeaveIfError ( iStatus.Int() );
	pOrigResponse = pResponse = iConnMan.DataHandler().ResponseL ( 3 );
	CleanupStack::PushL(pOrigResponse) ;
    //parse message type

	memcpy ( &messagetype, pResponse, sizeof ( guint ) );
	memcpy ( &time, pResponse + sizeof ( guint ), sizeof ( guint ) );
	
	senderidlen = strlen(pResponse + sizeof ( guint ) * 2 );
    sender = ( char* ) User::AllocLC ( senderidlen + 1 );
	memset ( sender, '\0', senderidlen );
	memcpy ( sender, pResponse + sizeof ( guint ) * 2, senderidlen + 1);
	
	messagelen = strlen(pResponse + sizeof ( guint ) * 2 + senderidlen + 1 );
    recvdmessage = ( char* ) User::AllocLC ( messagelen + 1 );
	memset ( recvdmessage, '\0', messagelen );
	memcpy ( recvdmessage, pResponse + sizeof ( guint ) * 2 + 1 +  senderidlen, messagelen + 1 );
	CleanupStack::PopAndDestroy ( recvdmessage );
	CleanupStack::PopAndDestroy ( sender );
	CleanupStack::PopAndDestroy(pOrigResponse) ;//pOrigResponse
	LOGGER ( TXT ( "COssprotocolServerErrorHandler::ProcessIncomingDataL End" ) );
	}


// ---------------------------------------------------------------------------
// COssprotocolServerErrorHandler::RunError
// ---------------------------------------------------------------------------
//
TInt COssprotocolServerErrorHandler::RunError ( TInt  aError )
	{
	LOGGER ( TXT ( "COssprotocolServerErrorHandler::RunError Start %d" ), aError );

	LOGGER ( TXT ( "COssprotocolServerErrorHandler::RunError End" ) );
	return KErrNone;
	}

// ---------------------------------------------------------------------------
// COssprotocolServerErrorHandler::StartListeningL
// ---------------------------------------------------------------------------
//
void COssprotocolServerErrorHandler::StartListeningL()
	{
	LOGGER ( TXT ( "COssprotocolServerErrorHandler::StartListeningL Start" ) );

	if ( ! ( this->IsActive() ) )
		{
		iConnMan.DataHandler().ListenIncomingServerError ( iStatus );
		SetActive();
		}
	LOGGER ( TXT ( "COssprotocolServerErrorHandler::StartListeningL End" ) );
	}

// End of file
