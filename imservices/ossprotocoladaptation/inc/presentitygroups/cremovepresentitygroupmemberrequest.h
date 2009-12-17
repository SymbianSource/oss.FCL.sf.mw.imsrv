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
* Description:  Remove presentity group member request
*
*/


#ifndef __CREMOVEPRESENTITYGROUPMEMBERREQUEST_H__
#define __CREMOVEPRESENTITYGROUPMEMBERREQUEST_H__


//  INCLUDES
#include <e32base.h>
#include <ximpbase.h>


// FORWARD DECLARATIONS
class MOSSProtocolConnectionManager;
class MXIMPIdentity;


/**
 * CRemovePresentityGroupMemberRequest
 *
 * Issue Remove Presentity Group Member Request to Network Server
 *
 */
 
 class CRemovePresentityGroupMemberRequest: public CActive
                                			   
                                			   
    {

public:

    
    										
    static CRemovePresentityGroupMemberRequest* NewLC( 
    										MOSSProtocolConnectionManager& aConnMan,
    										TXIMPRequestId aRequestId );
    										
    virtual ~CRemovePresentityGroupMemberRequest();

private:

    CRemovePresentityGroupMemberRequest( 
    										MOSSProtocolConnectionManager& aConnMan,
    										TXIMPRequestId aRequestId  );
    void ConstructL();
   
private: // from CActive

    void DoCancel();
    /*
     * RunL() function also deletes the request object once the activity is done
     *
     */
    void RunL();
    TInt RunError( TInt aError );
    
public:
   	 /**
      * Remove presentity group member from the list
      * @param aGroupId group identity
      * @param aGroupId group member identity
      */  
   void RemovePresentityGroupMemberL(const MXIMPIdentity& aGroupId,
   									 const MXIMPIdentity& aMemberId);
 
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
    
    // owns : userid id to delete
    HBufC* iUserId;
    
    };


#endif // __CREMOVEPRESENTITYGROUPMEMBERREQUEST_H__

