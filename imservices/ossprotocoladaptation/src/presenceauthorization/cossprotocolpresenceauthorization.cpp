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
* Description:  Oss Protocol implementation for Presence Framework
*
*/


#include <badesca.h>

#include <ximpbase.h>
#include <ximpidentity.h>
#include <ximpprotocolconnectionhost.h>

#include "cossprotocolpresenceauthorization.h"
#include "ossprotocolpluginlogger.h"
#include "cossprotocolconnectionmanager.h"

#include "csubscribepresencegrantrequestlistrequest.h"
#include "ossprotocolpluginpanics.h"
#include "cpresenceauthuserrequest.h"
#include "cwithdrawpresencegrantfrompresentityrequest.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CImpsConnection::GetInterface()
// ---------------------------------------------------------------------------
//
TAny* COssProtocolPresenceAuthorization::GetInterface( TInt32 aInterfaceId,
                                TIfGetOps aOptions )
    {
    LOGGER ( TXT("COssProtocolPresenceAuthorization::GetInterface() Start") );
    if( aInterfaceId == MProtocolPresenceAuthorization::KInterfaceId )
        {
        MProtocolPresenceAuthorization* self = this;
        return self;
        }

    if( aOptions == MXIMPBase::EPanicIfUnknown ) 
        {
        User::Panic( KOSSProtocolPresenceAuthorization, KErrExtensionNotSupported );
        }
	LOGGER ( TXT("COssProtocolPresenceAuthorization::GetInterface() End") );
    return NULL;
    }


// ---------------------------------------------------------------------------
// CImpsConnection::GetInterface()
// ---------------------------------------------------------------------------
//
const TAny* COssProtocolPresenceAuthorization::GetInterface( TInt32 aInterfaceId,
                                      TIfGetOps aOptions ) const
    {
    LOGGER ( TXT("COssProtocolPresenceAuthorization::GetInterface() Start") );
    if( aInterfaceId == MProtocolPresenceAuthorization::KInterfaceId )
        {
        const MProtocolPresenceAuthorization* self = this;
        return self;
        }

    if( aOptions == MXIMPBase::EPanicIfUnknown ) 
        {
        User::Panic( KOSSProtocolPresenceAuthorization, KErrExtensionNotSupported );
        }
	LOGGER ( TXT("COssProtocolPresenceAuthorization::GetInterface() End") );
    return NULL;
    }


// ---------------------------------------------------------------------------
// CImpsConnection::NewInstanceLC()
// ---------------------------------------------------------------------------
//
TInt32 COssProtocolPresenceAuthorization::GetInterfaceId() const
    {
    LOGGER ( TXT("COssProtocolPresenceAuthorization::GetInterfaceId() Start-End") );
    return MProtocolPresenceAuthorization::KInterfaceId;
    }



// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::COssProtocolPresenceAuthorization()
// ---------------------------------------------------------------------------
//
COssProtocolPresenceAuthorization::COssProtocolPresenceAuthorization(
									MOSSProtocolConnectionManager& aConnMan)
	:iConnMan(aConnMan)
    {
   	LOGGER ( TXT("::COssProtocolPresenceAuthorization() Start-End") );
    }


// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::ConstructL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresenceAuthorization::ConstructL()
    {
    LOGGER ( TXT("COssProtocolPresenceAuthorization::ConstructL() Start") );                                    
    LOGGER ( TXT("COssProtocolPresenceAuthorization::ConstructL() End") );
    }


// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::NewL()
// ---------------------------------------------------------------------------
//
COssProtocolPresenceAuthorization* COssProtocolPresenceAuthorization::NewL( 
						MOSSProtocolConnectionManager& aConnMan )
    {
    LOGGER ( TXT("COssProtocolPresenceAuthorization::NewL() Start") );

    COssProtocolPresenceAuthorization* self = 
    					new( ELeave ) COssProtocolPresenceAuthorization( aConnMan);
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    LOGGER ( TXT("COssProtocolPresenceAuthorization::NewL() End") );
    return self;
    }


// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::~COssProtocolPresenceAuthorization()
// ---------------------------------------------------------------------------
//
COssProtocolPresenceAuthorization::~COssProtocolPresenceAuthorization()
    {
    LOGGER ( TXT("Authorization::~COssProtocolPresenceAuthorization() Start") );
    
        
	LOGGER ( TXT("Authorization::~COssProtocolPresenceAuthorization() End") );
    }


// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::DoUnsubscribePresenceWatcherListL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresenceAuthorization::DoSubscribePresenceGrantRequestListL( 
			TXIMPRequestId aReqId )
    {
    LOGGER ( TXT("Authorization::DoSubscribePresenceGrantRequestListL() Start") );
    if( ! iConnMan.GetContactManager().IsFetchInvitationsForFirstTime() )
        {
        iConnMan.GetContactManager().SetFetchInvitationsForFirstTime(ETrue);
        CreateDataHandlerL();

        iConnMan.GetAddNotificationHandler().StartListeningL();
        iConnMan.HandleToHost().HandleRequestCompleted( aReqId, KErrNone );
        }	
	else
	    {
	    iConnMan.GetContactManager().ReturnInvitationListL();
	    iConnMan.HandleToHost().HandleRequestCompleted ( aReqId, KErrNone );
	    }
    
    LOGGER ( TXT("Authorization::DoSubscribePresenceGrantRequestListL() End") );
    }

// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::DoUnsubscribePresenceWatcherListL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresenceAuthorization::DoUnsubscribePresenceGrantRequestListL( 
			TXIMPRequestId aReqId )
    {
    LOGGER ( TXT("Authorization::DoUnsubscribePresenceGrantRequestListL() Start") );
  
    // complete the request successfully
    iConnMan.HandleToHost().HandleRequestCompleted( aReqId, KErrNone );
    	
    LOGGER ( TXT("Authorization::DoUnsubscribePresenceGrantRequestListL() End") );
    }

// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::DoGrantPresenceForPresentityL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresenceAuthorization::DoGrantPresenceForPresentityL( 
												const MXIMPIdentity& aIdentity,
                                                const MPresenceInfoFilter& aPif,
                                                TXIMPRequestId aReqId )
    {
    LOGGER ( TXT("Authorization::DoGrantPresenceForPresentityL() Start") );
	CreateDataHandlerL();
 		
 	CPresenceAuthUserRequest* req = 
 	CPresenceAuthUserRequest::NewLC( iConnMan, aReqId );
 	
 	
	req->PresenceAuthUserRequestL(aIdentity,aPif);
	
	CleanupStack::Pop( req );
    LOGGER ( TXT("Authorization::DoGrantPresenceForPresentityL() End") );
    }

// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::DoUpdateGrantPresenceForPresentityL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresenceAuthorization::DoUpdatePresenceGrantPifForPresentityL( 
											const MXIMPIdentity&/*aIdentity*/,
                                            const MPresenceInfoFilter &/*aPif*/,
                                            TXIMPRequestId /*aReqId*/ )
    {
    LOGGER ( TXT("Authorization::DoUpdatePresenceGrantPifForPresentityL() Start") );
    LOGGER ( TXT("Authorization::DoUpdatePresenceGrantPifForPresentityL() End") );
    }

// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::DoUpdateGrantPresenceForPresentityGroupMembersL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresenceAuthorization::DoWithdrawPresenceGrantFromPresentityL( 
											const MXIMPIdentity &aIdentity,
                                            TXIMPRequestId aReqId )
    {
    LOGGER ( TXT("Authorization::DoWithdrawPresenceGrantFromPresentityL() Start") );
    CreateDataHandlerL();
 		
 	CWithdrawPresenceGrantFromPresentityRequest* req = 
 	CWithdrawPresenceGrantFromPresentityRequest::NewLC( iConnMan, aReqId );
 	
 	
	req->WithdrawPresenceGrantFromPresentityL( aIdentity );
	
	CleanupStack::Pop( req );

    
    LOGGER ( TXT("Authorization::DoWithdrawPresenceGrantFromPresentityL() End") );
    }

// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::DoGrantPresenceForPresentityGroupMembersL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresenceAuthorization::DoGrantPresenceForPresentityGroupMembersL( 
											const  MXIMPIdentity&/*aIdentity*/,
                                            const MPresenceInfoFilter& /*aPif*/,
                                            TXIMPRequestId /*aReqId*/ )
    {
    LOGGER ( TXT("Authorization::DoGrantPresenceForPresentityGroupMembersL() Start") );
    
    LOGGER ( TXT("Authorization::DoGrantPresenceForPresentityGroupMembersL() End") );
    }

// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::DoUpdateGrantPresenceForPresentityGroupMembersL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresenceAuthorization::DoUpdatePresenceGrantPifForPresentityGroupMembersL( 
											const MXIMPIdentity&/*aIdentity*/,
                                            const MPresenceInfoFilter&/*aPif*/,
                                            TXIMPRequestId /*aReqId*/ )
    {
    LOGGER ( TXT("DoUpdatePresenceGrantPifForPresentityGroupMembersL() Start") );
    
    LOGGER ( TXT("DoUpdatePresenceGrantPifForPresentityGroupMembersL() End") );
    }


// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::DoUpdateGrantPresenceForPresentityGroupMembersL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresenceAuthorization::DoWithdrawPresenceGrantFromPresentityGroupMembersL( 
											const MXIMPIdentity&/*aIdentity*/,
											TXIMPRequestId /*aReqId*/ )
    {
    LOGGER ( TXT("DoWithdrawPresenceGrantFromPresentityGroupMembersL() Start") );
    
    LOGGER ( TXT("DoWithdrawPresenceGrantFromPresentityGroupMembersL() End") );
    }

// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::DoGrantPresenceForEveryoneL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresenceAuthorization::DoGrantPresenceForEveryoneL( 
											const MPresenceInfoFilter& /*aPif*/,
 											TXIMPRequestId /*aReqId*/ )
	{
	LOGGER ( TXT("Authorization::DoGrantPresenceForEveryoneL() Start") );
	
    LOGGER ( TXT("Authorization::DoGrantPresenceForEveryoneL() End") );
	}

// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::DoUpdatePresenceGrantPifForEveryoneL()
// ---------------------------------------------------------------------------
//											 
void COssProtocolPresenceAuthorization::DoUpdatePresenceGrantPifForEveryoneL(
											const MPresenceInfoFilter& /*aPif*/,
						                    TXIMPRequestId /*aReqId*/ )
	{
	LOGGER ( TXT("Authorization::DoUpdatePresenceGrantPifForEveryoneL() Start") );
	
    LOGGER ( TXT("Authorization::DoUpdatePresenceGrantPifForEveryoneL() End") );
	}

// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::DoWithdrawPresenceGrantFromEveryoneL()
// ---------------------------------------------------------------------------
//                  
void COssProtocolPresenceAuthorization::DoWithdrawPresenceGrantFromEveryoneL( 
						TXIMPRequestId /*aReqId*/ )
	{
	LOGGER ( TXT("Authorization::DoWithdrawPresenceGrantFromEveryoneL() Start") );
	
    LOGGER ( TXT("Authorization::DoWithdrawPresenceGrantFromEveryoneL() End") );
	} 
	
// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::DoSubscribePresenceBlockListL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresenceAuthorization::DoSubscribePresenceBlockListL( 
						TXIMPRequestId /*aReqId*/ )
    {
    LOGGER ( TXT("Authorization::DoSubscribePresenceBlockListL() Start") );
    
    LOGGER ( TXT("Authorization::DoSubscribePresenceBlockListL() End") );
    }
    

// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::DoUnsubscribePresenceBlockListL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresenceAuthorization::DoUnsubscribePresenceBlockListL( 
				TXIMPRequestId /*aReqId*/ )
    {
    LOGGER ( TXT("Authorization::DoUnsubscribePresenceBlockListL() Start") );
    LOGGER ( TXT("Authorization::DoUnsubscribePresenceBlockListL() End") );
    }


// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::DoBlockPresenceForPresentityL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresenceAuthorization::DoBlockPresenceForPresentityL( 
											const MXIMPIdentity& /*aPresentityId*/,
											TXIMPRequestId /*aReqId*/ )
    {
    LOGGER ( TXT("Authorization::DoBlockPresenceForPresentityL() Start") );
    
    LOGGER ( TXT("Authorization::DoBlockPresenceForPresentityL() End") );
    }

// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::DoCancelPresenceBlockFromPresentityL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresenceAuthorization::DoCancelPresenceBlockFromPresentityL( 
											const MXIMPIdentity& /*aPresentityId*/,
											TXIMPRequestId /*aReqId*/ )
    {
    LOGGER ( TXT("Authorization::DoCancelPresenceBlockFromPresentityL() Start") );
  
    LOGGER ( TXT("Authorization::DoCancelPresenceBlockFromPresentityL() End") );
    }

// ---------------------------------------------------------------------------
// COssProtocolPresenceAuthorization::CreateDataHandlerL()
// ---------------------------------------------------------------------------
//
void COssProtocolPresenceAuthorization::CreateDataHandlerL()
	{
	LOGGER ( TXT("Authorization::CreateDataHandler() Start"));
	iConnMan.ManufactureDataHandlerL();		
	LOGGER ( TXT("Authorization::CreateDataHandler() End"));
	}
	

// End of file

