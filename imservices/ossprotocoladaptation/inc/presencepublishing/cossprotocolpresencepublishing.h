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
* Description:  IMPS Protocol implementation for Presence Framework
*
*/


#ifndef __COSSSPROTOCOLPRESENCEPUBLISHING_H__
#define __COSSSPROTOCOLPRESENCEPUBLISHING_H__

//  INCLUDES
#include <e32base.h>
#include <ximpcontext.h>
#include <protocolpresencepublishing.h>
#include <ximpprotocolconnection.h>
#include <ximpbase.h>

// FORWARD DECLARATIONS
class MXIMPServiceInfo;
class MOSSProtocolConnectionManager;
class CPresenceNotificationHandler;
class MProtocolPresencePublishing;

/**
 * COssProtocolPresencePublishing
 *
 * Oss Protocol presence publishing Request Handling
 *
 */
class COssProtocolPresencePublishing:
					public CBase,
					public MProtocolPresencePublishing
	{

public:

    static COssProtocolPresencePublishing* NewL(MOSSProtocolConnectionManager& aConnManager);


    ~COssProtocolPresencePublishing();


private:

    COssProtocolPresencePublishing(MOSSProtocolConnectionManager& aConnManager);


    void ConstructL();
                
public:  //from MXIMPBase
	/**
	 * @see MXIMPBase
	 */
	TAny* GetInterface( TInt32 aInterfaceId,
                        TIfGetOps  aOptions );
    /**
	 * @see MXIMPBase
	 */
    const TAny* GetInterface( TInt32 aInterfaceId,
                              TIfGetOps  aOptions ) const;

    /**
	 * @see MXIMPBase
	 */
    TInt32 GetInterfaceId() const;

public:	// From MProtocolPresencePublishing 
	
	/**
	 * @see MProtocolPresencePublishing
	 */
	void DoPublishOwnPresenceL( const MPresenceInfo& aPresence,
                                TXIMPRequestId aReqId );
    /**
	 * @see MProtocolPresencePublishing
	 */
    void DoSubscribeOwnPresenceL( const MPresenceInfoFilter& aPif,
                                  TXIMPRequestId aReqId );
    /**
	 * @see MProtocolPresencePublishing
	 */
    void DoUpdateOwnPresenceSubscriptionPifL( const MPresenceInfoFilter& aPif,
                                           TXIMPRequestId aReqId );
    /**
	 * @see MProtocolPresencePublishing
	 */
    void DoUnsubscribeOwnPresenceL( TXIMPRequestId aReqId );
    
    /**
	 * @see MProtocolPresencePublishing
	 */
    void DoSubscribePresenceWatcherListL( TXIMPRequestId aReqId );

	/**
	 * @see MProtocolPresencePublishing
	 */
    void DoUnsubscribePresenceWatcherListL( TXIMPRequestId aReqId );	

                                                      
private:
	
	/**
     * Request Id from PrFw
     */
	TXIMPRequestId iRequestId;
	
	/**
     * Oss Protocol Plugin Connection Manager
     * Not own.  
     *** Write "Not own" if some other class owns this object.
     */
	MOSSProtocolConnectionManager& iConnMan;
	
	CPresenceNotificationHandler* iNotificationHandler;
					
	};

#endif // __COSSSPROTOCOLPRESENCEPUBLISHING_H__
