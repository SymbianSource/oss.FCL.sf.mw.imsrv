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
* Description:  Add presentity group member request
*
*/


#ifndef __CADDPRESENTITYGROUPMEMBERREQUEST_H__
#define __CADDPRESENTITYGROUPMEMBERREQUEST_H__


//  INCLUDES
#include <e32base.h>
#include <ximpbase.h>


// FORWARD DECLARATIONS
class MOSSProtocolConnectionManager;
class MXIMPIdentity;

/**
 * CAddPresentityGroupMemberRequest
 *
 * Issue Add Presentity Group Member Request to Network Server
 *
 */
 
 class CAddPresentityGroupMemberRequest: public CActive
                                			   
                                			   
    {

public:

    										
    static CAddPresentityGroupMemberRequest* NewLC( 
    										MOSSProtocolConnectionManager& aConnMan,
    										TXIMPRequestId aRequestId );
    										
    virtual ~CAddPresentityGroupMemberRequest();

private:

    CAddPresentityGroupMemberRequest( 
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
      * Add contact to the list
      * @param aGroupId group identity
      * @param aMemberId conatct identity
      * @param aMemberDisplayName contact displayname
      */
   	void AddPresentityGroupMemberL(	const MXIMPIdentity& aGroupId,
									const MXIMPIdentity& aMemberId,
								    const TDesC16& aMemberDisplayName );
 

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
    
    /*
     * Stores contactid
     * Own
     */
    HBufC* iContactId;
    };


#endif // __CADDPRESENTITYGROUPMEMBERREQUEST_H__

