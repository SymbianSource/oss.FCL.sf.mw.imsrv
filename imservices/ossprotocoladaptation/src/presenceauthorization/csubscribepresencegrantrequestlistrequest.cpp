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
* Description:  subscribe to grant presence request list
*
*/


#include <ximpprotocolconnectionhost.h>
#include "csubscribepresencegrantrequestlistrequest.h"
#include "mossprotocolconnectionmanager.h"
#include "ossprotocolpluginlogger.h"
#include <protocolpresenceauthorizationdatahost.h>

#include "cossprotocolconnectionmanager.h"

#include <ximpobjectfactory.h>
#include <ximpobjectcollection.h>
#include <protocolpresentitygroupsdatahost.h>
#include <presentitygroupinfo.h>
#include <presentitygroupmemberinfo.h>
#include <ximpidentity.h>
#include <ximpdatasubscriptionstate.h>


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CSubscribePresenceGrantRequestListRequest::CSubscribePresenceGrantRequestListRequest
// ---------------------------------------------------------------------------
//
CSubscribePresenceGrantRequestListRequest::CSubscribePresenceGrantRequestListRequest( 
												MOSSProtocolConnectionManager& aConnMan,
												TXIMPRequestId aRequestId ) :
    CActive( EPriorityNormal ),
    iRequestId( aRequestId ),
    iConnMan( aConnMan )
    {
    LOGGER ( TXT("::CSubscribePresenceGrantRequestListRequest Start") );
    CActiveScheduler::Add( this );
    LOGGER ( TXT("::CSubscribePresenceGrantRequestListRequest End") );
    }


// ---------------------------------------------------------------------------
// CSubscribePresenceGrantRequestListRequest::ConstructL
// ---------------------------------------------------------------------------
//
void CSubscribePresenceGrantRequestListRequest::ConstructL()
    {
    LOGGER ( TXT("::ConstructL Start") );
	LOGGER ( TXT("::ConstructL End") );
    }


// ---------------------------------------------------------------------------
// CSubscribePresenceGrantRequestListRequest::NewL
// ---------------------------------------------------------------------------
//
CSubscribePresenceGrantRequestListRequest* CSubscribePresenceGrantRequestListRequest::NewL(
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
    {
    LOGGER ( TXT("CSubscribePresenceGrantRequestListRequest::NewL Start") );
    
    CSubscribePresenceGrantRequestListRequest* self = new( ELeave ) 
    		CSubscribePresenceGrantRequestListRequest( aConnMan, aRequestId );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    
    LOGGER ( TXT("CSubscribePresenceGrantRequestListRequest::NewL End") );
    return self;
    }


// ---------------------------------------------------------------------------
// CSubscribePresenceGrantRequestListRequest::NewLC
// ---------------------------------------------------------------------------
//
CSubscribePresenceGrantRequestListRequest* CSubscribePresenceGrantRequestListRequest::NewLC(
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
    {
    LOGGER ( TXT("CSubscribePresenceGrantRequestListRequest::NewLC Start") );
    
    CSubscribePresenceGrantRequestListRequest* self =  
    		CSubscribePresenceGrantRequestListRequest::NewL( aConnMan, aRequestId );
    CleanupStack::PushL( self );
           
    LOGGER ( TXT("CSubscribePresenceGrantRequestListRequest::NewLC End") );
    return self;
    }

// ---------------------------------------------------------------------------
// CSubscribePresenceGrantRequestListRequest::~CSubscribePresenceGrantRequestListRequest
// ---------------------------------------------------------------------------
//
CSubscribePresenceGrantRequestListRequest::~CSubscribePresenceGrantRequestListRequest()
    {
    LOGGER ( TXT("::~CSubscribePresenceGrantRequestListRequest Start") );
    
    CActive::Cancel();
    
    LOGGER ( TXT("::~CSubscribePresenceGrantRequestListRequest End") );
    }


// ---------------------------------------------------------------------------
// CSubscribePresenceGrantRequestListRequest::DoCancel()
// ---------------------------------------------------------------------------
//
void CSubscribePresenceGrantRequestListRequest::DoCancel()
    {
    LOGGER ( TXT("CSubscribePresenceGrantRequestListRequest::DoCancel Start") );
    iConnMan.DataHandler().CancelListeningAddNotication();
    LOGGER ( TXT("CSubscribePresenceGrantRequestListRequest::DoCancel End") );
    }


// ---------------------------------------------------------------------------
// CSubscribePresenceGrantRequestListRequest::RunL()
// ---------------------------------------------------------------------------
//
void CSubscribePresenceGrantRequestListRequest::RunL()
    {
    LOGGER ( TXT("CSubscribePresenceGrantRequestListRequest::RunL Start") );
    
	User::LeaveIfError( iStatus.Int() );
	
	iConnMan.HandleToHost().HandleRequestCompleted( iRequestId, KErrNone);
    
	delete this;
	LOGGER ( TXT("CSubscribePresenceGrantRequestListRequest::RunL End") );
    }


// ---------------------------------------------------------------------------
// CSubscribePresenceGrantRequestListRequest::RunError
// ---------------------------------------------------------------------------
//
TInt CSubscribePresenceGrantRequestListRequest::RunError( TInt  aError )
    {
    LOGGER ( TXT("CSubscribePresenceGrantRequestListRequest::RunError Start") );
    
    iConnMan.HandleToHost().HandleRequestCompleted( iRequestId, aError );
    
    delete this;
	LOGGER ( TXT("CSubscribePresenceGrantRequestListRequest::RunError End") );
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// CSubscribePresenceGrantRequestListRequest::SubscribePresenceGrantRequestListL
// ---------------------------------------------------------------------------
//
void CSubscribePresenceGrantRequestListRequest::SubscribePresenceGrantRequestListL()
    {   
    LOGGER ( TXT("::SubscribePresenceGrantRequestListL Start") );
	// signal the scheduler
	SetActive();
	
	//by default adaptation 1.2 is ready for receiving presence authorisation requests from the server.no need to subscribe for it  
	TRequestStatus *status = &iStatus;
	User::RequestComplete( status, KErrNone);
	
	LOGGER ( TXT("::SubscribePresenceGrantRequestListL End") );
    }

// End of file
