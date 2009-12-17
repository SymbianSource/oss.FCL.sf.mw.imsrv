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


#ifndef __CPUBLISHOWNPRESENCEREQUEST_H__
#define __CPUBLISHOWNPRESENCEREQUEST_H__


//  INCLUDES
#include <e32base.h>
#include <ximpbase.h>


// FORWARD DECLARATIONS
class MOSSProtocolConnectionManager;
class MPresenceInfo;
class MPresenceBuddyInfo2;

/**
 * CPublishOwnPresencerequest
 *
 * Publishes own presence 
 *
 */
 
 class CPublishOwnPresencerequest: public CActive
                                			   
                                			   
    {

public:

    static CPublishOwnPresencerequest* NewL( 
    										MOSSProtocolConnectionManager& aConnMan,
    										TXIMPRequestId aRequestId );
    										
    static CPublishOwnPresencerequest* NewLC( 
    										MOSSProtocolConnectionManager& aConnMan,
    										TXIMPRequestId aRequestId );
    										
    virtual ~CPublishOwnPresencerequest();

private:

    CPublishOwnPresencerequest( 
    										MOSSProtocolConnectionManager& aConnMan,
    										TXIMPRequestId aRequestId  );
    void ConstructL();

private: // from CActive

    void DoCancel();
    void RunL();
    TInt RunError( TInt aError );
    
public:
   /**
 	* CPublishOwnPresencerequest
	*
	* Publishes update own presence to network server
	*
	*/ 
   void PublishOwnPresenceL(const MPresenceInfo& aPresence);
   
 
private: // data

    /**
     * Request Id from ximpfw
     */
    
    TXIMPRequestId iRequestId;
    
    /**
     * Send data request to pure data handler generates the id
     */
    TInt iSendId;
	    
    
    /**
     * Imps Protocol Plugin Connection Manager
     * Not own.  *** Write "Not own" if some other class owns this object.
     */
    MOSSProtocolConnectionManager& iConnMan;
    
    //owns : own presence info
    MPresenceBuddyInfo2* iOwnPresenceInfo;
     
    };


#endif // __CPUBLISHOWNPRESENCEREQUEST_H__

