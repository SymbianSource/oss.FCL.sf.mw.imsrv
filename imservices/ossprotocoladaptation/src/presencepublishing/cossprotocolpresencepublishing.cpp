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
* Description:  IMPS Protocol Publishing implementation for Presence Framework
*
*/


#include <badesca.h>

#include <ximpbase.h>
#include <ximpidentity.h>
#include <ximpprotocolconnectionhost.h>

#include "cossprotocolpresencepublishing.h"
#include "ossprotocolpluginlogger.h"
#include "cossprotocolconnectionmanager.h"
//#include "csubscribeownpresencerequest.h"
#include "cpresencenotificationhandler.h"
//#include "cunsubscribeownpresencerequest.h"
#include "cpublishownpresencerequest.h"
//#include "csubscribepresencewatcherlistrequest.h"
//#include "cupdateownpresencesubscriptionpifrequest.h"

#include "ossprotocolpluginpanics.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// COssProtocolPresencePublishing::GetInterface()
// ---------------------------------------------------------------------------
//
TAny* COssProtocolPresencePublishing::GetInterface(
 	TInt32 aInterfaceId,
    TIfGetOps aOptions )
    {
    LOGGER ( TXT("CImpsProtocolPresentityGroups::GetInterface() Start") );
    

    if( aInterfaceId == MProtocolPresencePublishing::KInterfaceId )
        {
        MProtocolPresencePublishing* self = this;
        return self;
        }

    if( aOptions == MXIMPBase::EPanicIfUnknown )
        {
        User::Panic( KOSSProtocolPresencePublishing, KErrExtensionNotSupported );
        }

	LOGGER ( TXT("COssProtocolPresencePublishing::GetInterface() End") );
    return NULL;
    }


// ---------------------------------------------------------------------------
// COssProtocolPresencePublishing::GetInterface()
// ---------------------------------------------------------------------------
//
const TAny* COssProtocolPresencePublishing::GetInterface( 
	TInt32 aInterfaceId,
    TIfGetOps aOptions ) const
    {
    LOGGER ( TXT("CImpsProtocolPresentityGroups::GetInterface() Start") );
    
    if( aInterfaceId == MProtocolPresencePublishing::KInterfaceId )
        {
        const MProtocolPresencePublishing* self = this;
        return self;
        }

    if( aOptions == MXIMPBase::EPanicIfUnknown )
        {
        User::Panic( KOSSProtocolPresencePublishing, KErrExtensionNotSupported );
        }

	LOGGER ( TXT("COssProtocolPresencePublishing::GetInterface() End") );
    return NULL;
    }


// ---------------------------------------------------------------------------
// COssProtocolPresencePublishing::NewInstanceLC()
// ---------------------------------------------------------------------------
//
TInt32 COssProtocolPresencePublishing::GetInterfaceId() const
    {
    LOGGER ( TXT("COssProtocolPresencePublishing::GetInterfaceId() Start-End") );
    return MProtocolPresencePublishing::KInterfaceId;
    }
    
// ---------------------------------------------------------------------------
// COssProtocolPresencePublishing::COssProtocolPresencePublishing()
// ---------------------------------------------------------------------------
//
COssProtocolPresencePublishing::COssProtocolPresencePublishing(
									MOSSProtocolConnectionManager& aConnMan)
:iConnMan(aConnMan)
    {
   	LOGGER ( TXT("Publishing::COssProtocolPresencePublishing() Start") );
   	LOGGER ( TXT("Publishing::COssProtocolPresencePublishing() End") );
    }


// ---------------------------------------------------------------------------
// COssProtocolPresencePublishing::ConstructL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresencePublishing::ConstructL()
    {
    LOGGER ( TXT("COssProtocolPresencePublishing::ConstructL() Start") );    
    
    //iNotificationHandler = CPresenceNotificationHandler::NewL( iConnMan );	
 	
 	                                      
    LOGGER ( TXT("COssProtocolPresencePublishing::ConstructL() End") );
    }


// ---------------------------------------------------------------------------
// COssProtocolPresencePublishing::NewL()
// ---------------------------------------------------------------------------
//
COssProtocolPresencePublishing* COssProtocolPresencePublishing::NewL(  
										MOSSProtocolConnectionManager& aConnMan  )

    {
    LOGGER ( TXT("COssProtocolPresencePublishing::NewL() Start") );

    COssProtocolPresencePublishing* self = 
    				new( ELeave ) COssProtocolPresencePublishing(aConnMan);
    CleanupStack::PushL( self );
    self->ConstructL( );
    CleanupStack::Pop( self );

    LOGGER ( TXT("COssProtocolPresencePublishing::NewL() End") );
    return self;
    }


// ---------------------------------------------------------------------------
// COssProtocolPresencePublishing::~COssProtocolPresencePublishing()
// ---------------------------------------------------------------------------
//
COssProtocolPresencePublishing::~COssProtocolPresencePublishing()
    {
    LOGGER ( TXT("Publishing::~COssProtocolPresencePublishing() Start") );
    
    //delete iNotificationHandler;
    
	LOGGER ( TXT("Publishing::~COssProtocolPresencePublishing() End") );
    }


// ---------------------------------------------------------------------------
// COssProtocolPresencePublishing::DoSubscribeOwnPresenceL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresencePublishing::DoSubscribeOwnPresenceL( 
	const MPresenceInfoFilter& /*aPif*/,
    TXIMPRequestId /*aReqId*/ )
    {
    LOGGER ( TXT("Publishing::DoSubscribeOwnPresenceL() Start") );

	LOGGER ( TXT("Publishing::DoSubscribeOwnPresenceL() End") );
    }



// ---------------------------------------------------------------------------
// COssProtocolPresencePublishing::DoUnsubscribeOwnPresenceL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresencePublishing::DoUnsubscribeOwnPresenceL( 
	TXIMPRequestId /*aReqId*/ )
    {
	LOGGER ( TXT("Publishing::DoUnsubscribeOwnPresenceL() Start") );
	
	LOGGER ( TXT("Publishing::DoUnsubscribeOwnPresenceL() End") );
    }



// ---------------------------------------------------------------------------
// COssProtocolPresencePublishing::DoUpdateOwnPresenceSubscriptionL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresencePublishing::DoUpdateOwnPresenceSubscriptionPifL( 
	const MPresenceInfoFilter& /*aPif*/,
    TXIMPRequestId /*aReqId*/ )
    {
	LOGGER ( TXT("Publishing::DoUpdateOwnPresenceSubscriptionPifL() Start") );
	   
	
	LOGGER ( TXT("Publishing::DoUpdateOwnPresenceSubscriptionPifL() End") );
    }



// ---------------------------------------------------------------------------
// COssProtocolPresencePublishing::DoPublishOwnPresenceL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresencePublishing::DoPublishOwnPresenceL( 
	const MPresenceInfo& aPresence,
    TXIMPRequestId aReqId )
    {
    LOGGER ( TXT("Publishing::DoPublishOwnPresenceL() Start") );
    

 		
 	CPublishOwnPresencerequest* req = 
 	CPublishOwnPresencerequest::NewLC( iConnMan, aReqId );
 	
	
	req->PublishOwnPresenceL(aPresence);
	
	CleanupStack::Pop( req );
	
    LOGGER ( TXT("Publishing::DoPublishOwnPresenceL() End") );
    }

// ---------------------------------------------------------------------------
// COssProtocolPresencePublishing::DoSubscribePresenceWatcherListL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresencePublishing::DoSubscribePresenceWatcherListL( 
	TXIMPRequestId /*aReqId*/ )
	{
	LOGGER ( TXT("Publishing::DoSubscribePresenceWatcherListL() Start") );


	
	LOGGER ( TXT("Publishing::DoSubscribePresenceWatcherListL() End") );
	}


// ---------------------------------------------------------------------------
// COssProtocolPresencePublishing::DoUnsubscribePresenceWatcherListL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresencePublishing::DoUnsubscribePresenceWatcherListL(
	TXIMPRequestId /*aReqId*/ )
	{
	LOGGER ( TXT("Publishing::DoUnsubscribePresenceWatcherListL() Start") );
    
	
	LOGGER ( TXT("Publishing::DoUnsubscribePresenceWatcherListL() End") );
	}




// End of file

