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
* Description:  subscribing to get add notifications
*
*/


#ifndef __CSUBSCRIBEPRESENCEGRANTREQUESTLISTREQUEST_H__
#define __CSUBSCRIBEPRESENCEGRANTREQUESTLISTREQUEST_H__


//  INCLUDES
#include <e32base.h>
#include <ximpbase.h>


// FORWARD DECLARATIONS
class MOSSProtocolConnectionManager;
class MXIMPIdentity;

/**
 * CSubscribePresenceGrantRequestListRequest
 *
 * subscribing from ximpfw to grant presence 
 */
 
 class CSubscribePresenceGrantRequestListRequest: public CActive
                                			   
                                			   
    {

public:

    static CSubscribePresenceGrantRequestListRequest* NewL( 
    										MOSSProtocolConnectionManager& aConnMan,
    										TXIMPRequestId aRequestId );
    										
    static CSubscribePresenceGrantRequestListRequest* NewLC( 
    										MOSSProtocolConnectionManager& aConnMan,
    										TXIMPRequestId aRequestId );
    										
    virtual ~CSubscribePresenceGrantRequestListRequest();

private:

    CSubscribePresenceGrantRequestListRequest( 
    										MOSSProtocolConnectionManager& aConnMan,
    										TXIMPRequestId aRequestId  );
    void ConstructL();

private: // from CActive

    void DoCancel();
    void RunL();
    TInt RunError( TInt aError );
    
public:
    
   void SubscribePresenceGrantRequestListL();
 

private: // data

    /**
     * Request Id from ximpFw
     */
    
    TXIMPRequestId iRequestId;
    
    /**
     * Oss Protocol Plugin Connection Manager
     * Not own.  *** Write "Not own" if some other class owns this object.
     */
    MOSSProtocolConnectionManager& iConnMan;
    
    };


#endif // __CSUBSCRIBEPRESENCEGRANTREQUESTLISTREQUEST_H__

