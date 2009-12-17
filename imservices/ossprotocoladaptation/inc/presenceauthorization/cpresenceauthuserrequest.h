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
* Description:  Response to authorization request
*
*/


#ifndef __CPRESENCEAUTHUSERREQUEST_H__
#define __CPRESENCEAUTHUSERREQUEST_H__


//  INCLUDES
#include <e32base.h>
#include <ximpbase.h>


// FORWARD DECLARATIONS
class MOSSProtocolConnectionManager;
class MXIMPIdentity;
class MPresenceInfoFilter;

/**
 * CPresenceAuthUserRequest
 *
 * Issue Accept Response of add notification Request to Network Server
 *
 */
 
 class CPresenceAuthUserRequest: public CActive
                                			   
                                			   
    {

public:

    static CPresenceAuthUserRequest* NewL( 	MOSSProtocolConnectionManager& aConnMan,
    										TXIMPRequestId aRequestId );
    										
    static CPresenceAuthUserRequest* NewLC( MOSSProtocolConnectionManager& aConnMan,
    										TXIMPRequestId aRequestId );
    										
    virtual ~CPresenceAuthUserRequest();

private:

    CPresenceAuthUserRequest( MOSSProtocolConnectionManager& aConnMan,
    										TXIMPRequestId aRequestId  );
    void ConstructL();

private: // from CActive

    void DoCancel();
    void RunL();
    TInt RunError( TInt aError );
    
public:
    
/**
 * Issue Accept Response of add notification Request to Network Server
 * 
 * @param aIdentity: conatct id
 * aPif : presence info filter
 */
   void PresenceAuthUserRequestL(
									const MXIMPIdentity & aIdentity,
									const MPresenceInfoFilter & aPif);
 

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
     * Oss Protocol Plugin Connection Manager
     * Not own.  *** Write "Not own" if some other class owns this object.
     */
    MOSSProtocolConnectionManager& iConnMan;
    
    };


#endif // __CPRESENCEAUTHUSERREQUEST_H__

