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


#ifndef __COSSPROTOCLPRESENCEAUTHORISATION_H_
#define __COSSPROTOCLPRESENCEAUTHORISATION_H_


//  INCLUDES
#include <e32base.h>
#include <ximpcontext.h>
#include <protocolpresenceauthorization.h>
#include <ximpprotocolconnection.h>



// FORWARD DECLARATIONS

class MXIMPServiceInfo;
class MOSSProtocolConnectionManager;


/**
 * COssProtocolPresenceAuthorization
 *
 * Oss Protocol Authorization Request Handling
 *
 */
 
class COssProtocolPresenceAuthorization:
					public CBase,
					public MProtocolPresenceAuthorization					
	{
public:

    static COssProtocolPresenceAuthorization* NewL(MOSSProtocolConnectionManager& aConnManager);


    ~COssProtocolPresenceAuthorization();


private:

    COssProtocolPresenceAuthorization(MOSSProtocolConnectionManager& aConnManager);


    void ConstructL();

public: // from MXIMPBase 

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

public: //from MProtocolPresenceAuthorization

	/**
	 * @see MProtocolPresenceAuthorization
	 */
    void DoSubscribePresenceGrantRequestListL(
                    TXIMPRequestId aReqId );
    /**
	 * @see MProtocolPresenceAuthorization
	 */
    void DoUnsubscribePresenceGrantRequestListL(
                    TXIMPRequestId aReqId );

public: // Granting presence information access to single presentities
    
    /**
	 * @see MProtocolPresenceAuthorization
	 */
    void DoGrantPresenceForPresentityL(
                    const MXIMPIdentity& aPresentityId,
                    const MPresenceInfoFilter& aPif,
                    TXIMPRequestId aReqId );
    /**
	 * @see MProtocolPresenceAuthorization
	 */
    void DoUpdatePresenceGrantPifForPresentityL(
                    const MXIMPIdentity& aPresentityId,
                    const MPresenceInfoFilter& aPif,
                    TXIMPRequestId aReqId );
   	/**
	 * @see MProtocolPresenceAuthorization
	 */
    void DoWithdrawPresenceGrantFromPresentityL(
                    const MXIMPIdentity& aPresentityId,
                    TXIMPRequestId aReqId );

public: // Granting presence information access to presentity group members

    /**
	 * @see MProtocolPresenceAuthorization
	 */
    void DoGrantPresenceForPresentityGroupMembersL(
                    const MXIMPIdentity& aGroupId,
                    const MPresenceInfoFilter& aPif,
                    TXIMPRequestId aReqId );
    /**
	 * @see MProtocolPresenceAuthorization
	 */
    void DoUpdatePresenceGrantPifForPresentityGroupMembersL(
                    const MXIMPIdentity& aGroupId,
                    const MPresenceInfoFilter& aPif,
                    TXIMPRequestId aReqId );
    /**
	 * @see MProtocolPresenceAuthorization
	 */
    void DoWithdrawPresenceGrantFromPresentityGroupMembersL(
                    const MXIMPIdentity& aGroupId,
                    TXIMPRequestId aReqId );

public: // Granting presence information access to everyone
    
    /**
	 * @see MProtocolPresenceAuthorization
	 */
    void DoGrantPresenceForEveryoneL(
                    const MPresenceInfoFilter& aPif,
                    TXIMPRequestId aReqId );
    
    /**
	 * @see MProtocolPresenceAuthorization
	 */
    void DoUpdatePresenceGrantPifForEveryoneL(
                    const MPresenceInfoFilter& aPif,
                    TXIMPRequestId aReqId );
    
    /**
	 * @see MProtocolPresenceAuthorization
	 */
    void DoWithdrawPresenceGrantFromEveryoneL(
                    TXIMPRequestId aReqId );
public: // Subscribe presence block list
    
    /**
	 * @see MProtocolPresenceAuthorization
	 */
    void DoSubscribePresenceBlockListL(
                    TXIMPRequestId aReqId );


    /**
	 * @see MProtocolPresenceAuthorization
	 */
    void DoUnsubscribePresenceBlockListL(
                    TXIMPRequestId aReqId );

public: // Blocking presence information access from single presentities
    
    /**
	 * @see MProtocolPresenceAuthorization
	 */
    void DoBlockPresenceForPresentityL(
                    const MXIMPIdentity& aPresentityId,
                    TXIMPRequestId aReqId );
    
    /**
	 * @see MProtocolPresenceAuthorization
	 */
    void DoCancelPresenceBlockFromPresentityL(
                    const MXIMPIdentity& aPresentityId,
                    TXIMPRequestId aReqId );

	
public: 

	/**
     * Creates data handler
     */
	void CreateDataHandlerL();
	
private:
	
	/**
     * Request Id from ximpfw
     */
	TXIMPRequestId iRequestId;
	
	
	/**
     * Oss Protocol Plugin Connection Manager
     * Not own.  *** Write "Not own" if some other class owns this object.
     */
	MOSSProtocolConnectionManager& iConnMan;	
	
	
	
	};

#endif // __COSSPROTOCLPRESENCEAUTHORISATION_H_












