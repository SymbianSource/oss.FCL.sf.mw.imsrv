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
* Description:  Oss protocol presentity groups implementation
*
*/

#include <ximpbase.h>
#include <ximpidentity.h>
#include <ximpprotocolconnectionhost.h>
#include "cossprotocolpresentitygroups.h"
#include "csubscribepresentitygroupcontentrequest.h"

#include "cossprotocolconnectionmanager.h"
#include "mossprotocolconnectionmanager.h"
#include "ossprotocolpluginlogger.h"
#include "ossprotocolpluginpanics.h"
#include "ossprotocolpluginlogger.h"
#include "caddpresentitygroupmemberrequest.h" // add conatct request
#include "cremovepresentitygroupmemberrequest.h" // remove contact req.
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::GetInterface()
// ---------------------------------------------------------------------------
//
TAny* COSSProtocolpresentitygroups::GetInterface ( TInt32 aInterfaceId,
        TIfGetOps aOptions )
	{
	LOGGER ( TXT ( "COSSProtocolpresentitygroups::GetInterface() Start" ) );

	if ( aInterfaceId == MProtocolPresentityGroups::KInterfaceId )
		{
		MProtocolPresentityGroups* self = this;
		return self;
		}

	if ( aOptions == MXIMPBase::EPanicIfUnknown )

		{
		User::Panic ( KOSSProtocolPresentityGroups, KErrExtensionNotSupported );
		}

	LOGGER ( TXT ( "COSSProtocolpresentitygroups::GetInterface() End" ) );

	return NULL;
	}


// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::GetInterface()
// ---------------------------------------------------------------------------
//
const TAny* COSSProtocolpresentitygroups::GetInterface ( TInt32 aInterfaceId,
        TIfGetOps aOptions ) const
	{
	LOGGER ( TXT ( "COSSProtocolpresentitygroups::GetInterface() Start" ) );

	if ( aInterfaceId == MProtocolPresentityGroups::KInterfaceId )
		{
		const MProtocolPresentityGroups* self = this;
		return self;
		}

	if ( aOptions == MXIMPBase::EPanicIfUnknown )

		{
		User::Panic ( KOSSProtocolPresentityGroups, KErrExtensionNotSupported );
		}

	LOGGER ( TXT ( "COSSProtocolpresentitygroups::GetInterface() End" ) );

	return NULL;
	}


// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::GetInterfaceId()
// ---------------------------------------------------------------------------
//
TInt32 COSSProtocolpresentitygroups::GetInterfaceId() const
	{
	LOGGER ( TXT ( "COSSProtocolpresentitygroups::GetInterfaceId() Start-End" ) );
	return MProtocolPresentityGroups::KInterfaceId;
	}


// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::COSSProtocolpresentitygroups()
// ---------------------------------------------------------------------------
//
COSSProtocolpresentitygroups::COSSProtocolpresentitygroups (
    MOSSProtocolConnectionManager& aConnMan )
		: iConnMan ( aConnMan )
	{
	LOGGER ( TXT ( "Groups::COSSProtocolpresentitygroups() Start-End" ) );
	}


// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::ConstructL()
// ---------------------------------------------------------------------------
//
void COSSProtocolpresentitygroups::ConstructL()
	{
	LOGGER ( TXT ( "COSSProtocolpresentitygroups::ConstructL() Start" ) );
	LOGGER ( TXT ( "COSSProtocolpresentitygroups::ConstructL() End" ) );
	}


// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::NewL()
// ---------------------------------------------------------------------------
//
COSSProtocolpresentitygroups* COSSProtocolpresentitygroups::NewL (
    MOSSProtocolConnectionManager& aConnMan )
	{
	LOGGER ( TXT ( "COSSProtocolpresentitygroups::NewL() Start" ) );

	COSSProtocolpresentitygroups* self =
	    new ( ELeave ) COSSProtocolpresentitygroups ( aConnMan );
	CleanupStack::PushL ( self );
	self->ConstructL( );
	CleanupStack::Pop ( self );

	LOGGER ( TXT ( "COSSProtocolpresentitygroups::NewL() End" ) );
	return self;
	}


// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::~COSSProtocolpresentitygroups()
// ---------------------------------------------------------------------------
//
COSSProtocolpresentitygroups::~COSSProtocolpresentitygroups()
	{
	LOGGER ( TXT ( "Groups::~COSSProtocolpresentitygroups() Start" ) );


	LOGGER ( TXT ( "Groups::~COSSProtocolpresentitygroups() End" ) );
	}



// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::DoSubscribePresentityGroupListL()
// ---------------------------------------------------------------------------
//
void COSSProtocolpresentitygroups::DoSubscribePresentityGroupListL (
    TXIMPRequestId /*aReqId */)
	{
     // not supported
	}


// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::DoUnsubscribePresentityGroupListL()
// ---------------------------------------------------------------------------
//
void COSSProtocolpresentitygroups::DoUnsubscribePresentityGroupListL (
    TXIMPRequestId /*aReqId*/ )
	{
     //not supported
	}


// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::DoCreatePresentityGroupL()
// ---------------------------------------------------------------------------
//
void COSSProtocolpresentitygroups::DoCreatePresentityGroupL (
    const MXIMPIdentity& /*aIdentity*/,
    const TDesC16& /*aDisplayName*/,
    TXIMPRequestId /*aReqId*/ )
	{
	LOGGER ( TXT ( "Groups::DoCreatePresentityGroupL() Start" ) );
    //not supported

	LOGGER ( TXT ( "Groups::DoCreatePresentityGroupL() End" ) );
	}

// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::DoDeletePresentityGroupL()
// ---------------------------------------------------------------------------
//
void COSSProtocolpresentitygroups::DoDeletePresentityGroupL (
    const MXIMPIdentity& /*Identity*/,
    TXIMPRequestId /*aReqId*/ )
	{
	LOGGER ( TXT ( "Groups::DoDeletePresentityGroupL() Start" ) );
    //not supported

	LOGGER ( TXT ( "Groups::DoDeletePresentityGroupL() End" ) );
	}

// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::DoUpdatePresentityGroupDisplayNameL()
// ---------------------------------------------------------------------------
//
void COSSProtocolpresentitygroups::DoUpdatePresentityGroupDisplayNameL (
    const MXIMPIdentity& /*aIdentity*/,
    const TDesC16& /*aDisplayName*/,
    TXIMPRequestId /*aReqId*/ )
	{
	LOGGER ( TXT ( "Groups::DoUpdatePresentityGroupDisplayNameL() Start" ) );
     
	LOGGER ( TXT ( "Groups::DoUpdatePresentityGroupDisplayNameL() End" ) );
	}

// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::DoSubscribePresentityGroupContentL()
// ---------------------------------------------------------------------------
//
void COSSProtocolpresentitygroups::DoSubscribePresentityGroupContentL (
    const MXIMPIdentity& aGroupId,
    TXIMPRequestId aReqId )
    {
    
    LOGGER ( TXT ( "Groups::DoSubscribePresentityGroupContentL() Start" ) );
    if( ! iConnMan.GetContactManager().IsFetchContactsFirstTime())
        {
        iConnMan.GetContactManager().SetFetchContactsFirstTime(ETrue);
        CreateDataHandlerL();
        CSubscribePresentityGroupContentRequest* req =
        CSubscribePresentityGroupContentRequest::NewLC ( iConnMan, aReqId );
        req->SubscribePresentityGroupContentL ( aGroupId );
        CleanupStack::Pop ( req );
        }
    //keep a locol copy of the contacts and return to ximp fw
    else
        {
        iConnMan.GetContactManager().ReturnContactsListL();
        iConnMan.HandleToHost().HandleRequestCompleted ( aReqId, KErrNone );
        }        
    LOGGER ( TXT ( "Groups::DoSubscribePresentityGroupContentL() End" ) );
	}

// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::DoUnsubscribePresentityGroupContentL()
// ---------------------------------------------------------------------------
//
void COSSProtocolpresentitygroups::DoUnsubscribePresentityGroupContentL (
    const MXIMPIdentity& /*aGroupId*/,
    TXIMPRequestId aReqId )
	{
	LOGGER ( TXT ( "Groups::DoUnsubscribePresentityGroupContentL() Start" ) );

	// just complete the request to PrFw Successfully

	iConnMan.HandleToHost().HandleRequestCompleted ( aReqId, KErrNone );

	LOGGER ( TXT ( "Groups::DoUnsubscribePresentityGroupContentL() End" ) );
	}

// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::DoAddPresentityGroupMemberL()
// ---------------------------------------------------------------------------
//
void COSSProtocolpresentitygroups::DoAddPresentityGroupMemberL (
    const MXIMPIdentity& aGroupId,
    const MXIMPIdentity& aMemberId,
    const TDesC16& aMemberDisplayName,
    TXIMPRequestId aReqId )
	{
	LOGGER ( TXT ( "Groups::DoAddPresentityGroupMemberL() Start" ) );
	
	CAddPresentityGroupMemberRequest* addreq =
				 CAddPresentityGroupMemberRequest::NewLC(iConnMan, aReqId );
				 
	addreq->AddPresentityGroupMemberL(aGroupId,aMemberId,aMemberDisplayName);
	
	CleanupStack::Pop ( addreq );
	
	LOGGER ( TXT ( "Groups::DoAddPresentityGroupMemberL() End" ) );
	}

// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::DoRemovePresentityGroupMemberL()
// ---------------------------------------------------------------------------
//
void COSSProtocolpresentitygroups::DoRemovePresentityGroupMemberL (
    const MXIMPIdentity& aGroupId,
    const MXIMPIdentity& aMemberId,
    TXIMPRequestId aReqId )
	{
	LOGGER ( TXT ( "Groups::DoRemovePresentityGroupMemberL() Start" ) ) ;
	CRemovePresentityGroupMemberRequest* removereq =
				 CRemovePresentityGroupMemberRequest::NewLC(iConnMan, aReqId );
				 
	removereq->RemovePresentityGroupMemberL(aGroupId,aMemberId);
	
	CleanupStack::Pop ( removereq );
	LOGGER ( TXT ( "Groups::DoRemovePresentityGroupMemberL() End" ) );
	}

// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::DoUpdatePresentityGroupMemberDisplayNameL()
// ---------------------------------------------------------------------------
//
void COSSProtocolpresentitygroups::DoUpdatePresentityGroupMemberDisplayNameL (
    const MXIMPIdentity& /*aGroupId*/,
    const MXIMPIdentity& /*aMemberId*/,
    const TDesC16& /*aMemberDisplayName*/,
    TXIMPRequestId /*aReqId*/ )
	{
	LOGGER ( TXT ( "Groups::DoUpdatePresentityGroupMemberDisplayNameL() Start" ) );
	LOGGER ( TXT ( "Groups::DoUpdatePresentityGroupMemberDisplayNameL() End" ) );
	}

// ---------------------------------------------------------------------------
// COSSProtocolpresentitygroups::CreateDataHandler()
// ---------------------------------------------------------------------------
//
void COSSProtocolpresentitygroups::CreateDataHandlerL()
	{
	LOGGER ( TXT ( "COSSProtocolpresentitygroups::CreateDataHandler() Start" ) );

	iConnMan.ManufactureDataHandlerL();

	LOGGER ( TXT ( "COSSProtocolpresentitygroups::CreateDataHandler() End" ) );
	}

// End of file

