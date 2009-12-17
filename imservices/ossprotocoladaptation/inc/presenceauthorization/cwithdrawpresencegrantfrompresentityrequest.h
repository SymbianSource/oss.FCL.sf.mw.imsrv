/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __CWITHDRAWPRESENCEGRANTFROMPRESENTITYREQUEST_H__
#define __CWITHDRAWPRESENCEGRANTFROMPRESENTITYREQUEST_H__


//  INCLUDES
#include <e32base.h>
#include <ximpbase.h>


// FORWARD DECLARATIONS
class MOSSProtocolConnectionManager;
class MXIMPIdentity;
class MPresenceInfoFilter;

/**
 * CWithdrawPresenceGrantFromPresentityRequest
 *
 * Issue Rejecting Response of add notification Request to Network Server
 *
 */
 
 class CWithdrawPresenceGrantFromPresentityRequest: public CActive
                                			   
                                			   
    {

public:

    static CWithdrawPresenceGrantFromPresentityRequest* NewL( 	MOSSProtocolConnectionManager& aConnMan,
    										TXIMPRequestId aRequestId );
    										
    static CWithdrawPresenceGrantFromPresentityRequest* NewLC( MOSSProtocolConnectionManager& aConnMan,
    										TXIMPRequestId aRequestId );
    										
    virtual ~CWithdrawPresenceGrantFromPresentityRequest();

private:

    CWithdrawPresenceGrantFromPresentityRequest( MOSSProtocolConnectionManager& aConnMan,
    										TXIMPRequestId aRequestId  );
    void ConstructL();
	
private: // from CActive

    void DoCancel();
    void RunL();
    TInt RunError( TInt aError );
    
public:
    
	/**
	* Send Rejecting Response of add notification Request to Network Server
	*  @param aPresentityId: conatct id
	*/
    void WithdrawPresenceGrantFromPresentityL(
     const MXIMPIdentity& aPresentityId);
 

private: // data

    /**
     * Request Id from PrFw
     */
    
    TXIMPRequestId iRequestId;
 
    /**
     * Send data request to wait timer generates the id
     */
    TInt iSendId;
    
    /**
     * Oss Protocol Plugin Connection Manager
     * Not own.  *** Write "Not own" if some other class owns this object.
     */
    MOSSProtocolConnectionManager& iConnMan;
    
    };


#endif // __CWITHDRAWPRESENCEGRANTFROMPRESENTITYREQUEST_H__

