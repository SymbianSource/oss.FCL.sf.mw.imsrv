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
* Description:  Oss Protocol presentity groups
*
*/

#ifndef COSSPROTOCOLPRESENTITYGROUPS_H__
#define COSSPROTOCOLPRESENTITYGROUPS_H__


#include <e32base.h>
#include <protocolpresentitygroups.h>


class MOSSProtocolConnectionManager;


/**
 * COSSProtocolpresentitygroups
 *
 * implementation of MProtocolPresentityGroups methods.
 * these methods will called by ximp framework 
 *
 */
class COSSProtocolpresentitygroups :   public CBase,
                                        public MProtocolPresentityGroups
    {

public:

    static COSSProtocolpresentitygroups* NewL( MOSSProtocolConnectionManager& aConnManager );
    ~COSSProtocolpresentitygroups();


private:

    COSSProtocolpresentitygroups( MOSSProtocolConnectionManager& aConnManager );
    void ConstructL();

public:  // from MXIMPBase

    /**
	 * @see MXIMPBase
	 */
    TAny* GetInterface( TInt32 aInterfaceId,
                        TIfGetOps  aOptions );
	/**
	 * @see MXIMPBase
	 */
    const TAny* GetInterface( TInt32 aInterfaceId,
                              TIfGetOps aOptions ) const;
	/**
	 * @see MXIMPBase
	 */
    TInt32 GetInterfaceId() const;

public: //From MProtocolPresentityGroups
    /**
	 * @see MProtocolPresentityGroups
	 */
    void DoSubscribePresentityGroupListL(
                    TXIMPRequestId aReqId );
    /**
	 * @see MProtocolPresentityGroups
	 */
    void DoUnsubscribePresentityGroupListL(
                    TXIMPRequestId aReqId );

public: // Manage presentity groups
    /**
	 * @see MProtocolPresentityGroups
	 */
    void DoCreatePresentityGroupL(
                    const MXIMPIdentity& aGroupId,
                    const TDesC16& aDisplayName,
                    TXIMPRequestId aReqId );
    /**
	 * @see MProtocolPresentityGroups
	 */
    void DoDeletePresentityGroupL(
                    const MXIMPIdentity& aGroupId,
                    TXIMPRequestId aReqId );
    /**
	 * @see MProtocolPresentityGroups
	 */
    void DoUpdatePresentityGroupDisplayNameL(
                    const MXIMPIdentity& aGroupId,
                    const TDesC16& aDisplayName,
                    TXIMPRequestId aReqId );

public: // Subscribe presentity group content
    /**
	 * @see MProtocolPresentityGroups
	 */
    void DoSubscribePresentityGroupContentL(
                    const MXIMPIdentity& aGroupId,
                    TXIMPRequestId aReqId );
    /**
	 * @see MProtocolPresentityGroups
	 */
   void DoUnsubscribePresentityGroupContentL(
                    const MXIMPIdentity& aGroupId,
                    TXIMPRequestId aReqId );

public: // Manage presentity group members
    /**
	 * @see MProtocolPresentityGroups
	 */
    void DoAddPresentityGroupMemberL(
                    const MXIMPIdentity& aGroupId,
                    const MXIMPIdentity& aMemberId,
                    const TDesC16& aMemberDisplayName,
                    TXIMPRequestId aReqId );
    /**
	 * @see MProtocolPresentityGroups
	 */
    void DoRemovePresentityGroupMemberL(
                    const MXIMPIdentity& aGroupId,
                    const MXIMPIdentity& aMemberId,
                    TXIMPRequestId aReqId );
    /**
	 * @see MProtocolPresentityGroups
	 */
    void DoUpdatePresentityGroupMemberDisplayNameL(
                    const MXIMPIdentity& aGroupId,
                    const MXIMPIdentity& aMemberId,
                    const TDesC16& aMemberDisplayName,
                    TXIMPRequestId aReqId );

private:
	/**
     * Creates data handler
     */
	void CreateDataHandlerL();
	
private:    // data members
    
    /**
     * Oss Protocol Plugin Connection Manager
     * Not own.  *** Write "Not own" if some other class owns this object.
     */
    MOSSProtocolConnectionManager& iConnMan;

    };

#endif // COSSPROTOCOLPRESENTITYGROUPS_H__
