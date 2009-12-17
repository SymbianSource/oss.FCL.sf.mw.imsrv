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
* Description:  Add notification handler
*
*/


#include <ximpprotocolconnectionhost.h>
#include "caddcontactenotificationhandler.h"

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
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "msgliterals.h"

#include "ossprotocoladaptationuids.h"
#include "ossprotocoladaptutils.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAddContactNotificationHandler::CAddContactNotificationHandler
// ---------------------------------------------------------------------------
//
CAddContactNotificationHandler::CAddContactNotificationHandler (
    MOSSProtocolConnectionManager& aConnMan ) :
		CActive ( EPriorityNormal ),
		iConnMan ( aConnMan )
	{
	LOGGER ( TXT ( "CAddContactNotificationHandler::CAddContactNotificationHandler Start" ) );
	CActiveScheduler::Add ( this );

	LOGGER ( TXT ( "CAddContactNotificationHandler::CAddContactNotificationHandler End" ) );
	}


// ---------------------------------------------------------------------------
// CAddContactNotificationHandler::ConstructL
// ---------------------------------------------------------------------------
//
void CAddContactNotificationHandler::ConstructL()
	{
	LOGGER ( TXT ( "CAddContactNotificationHandler::ConstructL Start-End" ) );

	}


// ---------------------------------------------------------------------------
// CAddContactNotificationHandler::NewL
// ---------------------------------------------------------------------------
//
CAddContactNotificationHandler* CAddContactNotificationHandler::NewL (
    MOSSProtocolConnectionManager& aConnMan )
	{
	LOGGER ( TXT ( "CAddContactNotificationHandler::NewL Start" ) );

	CAddContactNotificationHandler* self = new ( ELeave ) CAddContactNotificationHandler ( aConnMan );
	CleanupStack::PushL ( self );
	self->ConstructL();
	CleanupStack::Pop ( self );

	LOGGER ( TXT ( "CAddContactNotificationHandler::NewL End" ) );
	return self;
	}


// ---------------------------------------------------------------------------
// CAddContactNotificationHandler::NewLC
// ---------------------------------------------------------------------------
//
CAddContactNotificationHandler* CAddContactNotificationHandler::NewLC (
    MOSSProtocolConnectionManager& aConnMan )
	{
	LOGGER ( TXT ( "CAddContactNotificationHandler::NewLC Start" ) );

	CAddContactNotificationHandler* self = CAddContactNotificationHandler::NewL ( aConnMan );
	CleanupStack::PushL ( self );

	LOGGER ( TXT ( "CAddContactNotificationHandler::NewLC End" ) );
	return self;
	}

// ---------------------------------------------------------------------------
// CAddContactNotificationHandler::~CAddContactNotificationHandler
// ---------------------------------------------------------------------------
//
CAddContactNotificationHandler::~CAddContactNotificationHandler()
	{
	LOGGER ( TXT ( "::~CAddContactNotificationHandler Start" ) );

	Cancel();

	LOGGER ( TXT ( "::~CAddContactNotificationHandler End" ) );
	}


// ---------------------------------------------------------------------------
// CAddContactNotificationHandler::DoCancel()
// ---------------------------------------------------------------------------
//
void CAddContactNotificationHandler::DoCancel()
	{
	LOGGER ( TXT ( "CAddContactNotificationHandler::DoCancel Start" ) );

	iConnMan.DataHandler().CancelListeningAddNotication();

	LOGGER ( TXT ( "CAddContactNotificationHandler::DoCancel End" ) );
	}

// ---------------------------------------------------------------------------
// CAddContactNotificationHandler::RunL()
// ---------------------------------------------------------------------------
//
void CAddContactNotificationHandler::RunL()
	{
	LOGGER ( TXT ( "CAddContactNotificationHandler::RunL Start" ) );

	// something is coming from the xmpp server
	User::LeaveIfError ( iStatus.Int() );

	ProcessIncomingDataL();
	StartListeningL();

	LOGGER ( TXT ( "CAddContactNotificationHandler::RunL End" ) );
	}

// ---------------------------------------------------------------------------
// CAddContactNotificationHandler::ProcessIncomingDataL()
// ---------------------------------------------------------------------------
/* This Function is used to convert the received 
*  presence notification from Isolation Server Message queue 
*  into the ximpfw data types. and storing the presence information
*  in to the presence cache ( available in ximpfw ) 
*  client has to read the presence information from the 
*  presence cache. when the change in status notification is received
*  while updating presence cache, client will receive the notification if subscribed.
*/	
void CAddContactNotificationHandler::ProcessIncomingDataL()
	{	
	LOGGER ( TXT ( "CAddContactNotificationHandler::ProcessIncomingDataL Start" ) );
    char* pResponse = NULL, *pOrigResponse = NULL;  
    TInt len = 0;
	pOrigResponse = pResponse = iConnMan.DataHandler().ResponseL ( 4 );
	CleanupStack::PushL(pOrigResponse) ;
	RPointerArray<HBufC>& invitations =  iConnMan.GetContactManager().GetInvitationListL();   
	if( pResponse )
	 {
	 	pResponse += sizeof ( message_hdr_resp );
	 	while(1)
        {
        len = strlen(pResponse) + 1;
        if (1 == len)
            {
            break;
            }
		HBufC16*  AuthreqId = OssProtocolAdapUtils::ConvertCharToTUint16LC( pResponse );
		pResponse += len;
		TInt len1 = AuthreqId->Length();
        MXIMPObjectFactory& ObjFact = iConnMan.HandleToHost().ObjectFactory();
    	MPresenceObjectFactory& prfwObjFact = iConnMan.HandleToHost().ProtocolPresenceDataHost().PresenceObjectFactory();
    	
    	invitations.AppendL( AuthreqId );
    	MPresenceGrantRequestInfo* presenceGrant;
    	presenceGrant = prfwObjFact.NewPresenceGrantRequestInfoLC();//1
    	MXIMPIdentity* AuthReqIdentity;
    	AuthReqIdentity = ObjFact.NewIdentityLC();//2
    	AuthReqIdentity->SetIdentityL(*AuthreqId);
	    AuthreqId->Des().Fold();
	    presenceGrant->SetRequestorIdL(AuthReqIdentity);  
    	iConnMan.HandleToHost().ProtocolPresenceDataHost().AuthorizationDataHost().HandlePresenceGrantRequestReceivedL (presenceGrant); 
    	TInt count = iConnMan.PresenceAuthGrantReqList()->Count();
    	iConnMan.PresenceAuthGrantReqList()->Append(*AuthreqId);
    	count = iConnMan.PresenceAuthGrantReqList()->Count();
    	CleanupStack::Pop(2);   //AuthReqIdentity,presenceGrant
		CleanupStack::Pop ( 1 );//AuthreqId
        }
	 }
    CleanupStack::PopAndDestroy ( 1 );//pOrigResponse
	LOGGER ( TXT ( "CAddContactNotificationHandler::ProcessIncomingDataL End" ) );
	}


// ---------------------------------------------------------------------------
// CAddContactNotificationHandler::RunError
// ---------------------------------------------------------------------------
//
TInt CAddContactNotificationHandler::RunError ( TInt  aError )
	{
	LOGGER ( TXT ( "CAddContactNotificationHandler::RunError Start %d" ), aError );

	LOGGER ( TXT ( "CAddContactNotificationHandler::RunError End" ) );
	return KErrNone;
	}

// ---------------------------------------------------------------------------
// CAddContactNotificationHandler::StartListeningL
// ---------------------------------------------------------------------------
//
void CAddContactNotificationHandler::StartListeningL()
	{
	LOGGER ( TXT ( "CAddContactNotificationHandler::StartListeningL Start" ) );

	if ( ! ( this->IsActive() ) )
		{
		iConnMan.DataHandler().ListenAddNotification ( iStatus );
		SetActive();
		}
	LOGGER ( TXT ( "CAddContactNotificationHandler::StartListeningL End" ) );
	}

// End of file
