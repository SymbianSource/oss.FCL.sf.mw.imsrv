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
* Description:  Oss protocol im conversation 
*
*/

#ifndef COSSPROTOCOLIMCONVERSATION_H__
#define COSSPROTOCOLIMCONVERSATION_H__


#include <e32base.h>
#include <protocolimconversation.h>


class MOSSProtocolConnectionManager;


/**
 * COSSProtocolImConversation
 * implements MProtocolImConversation methods
 * these methods will called by ximp framework 
 */
class COSSProtocolImConversation :   public CBase,
                                        public MProtocolImConversation
    {

public:

    static COSSProtocolImConversation* NewL( MOSSProtocolConnectionManager& aConnManager );
    ~COSSProtocolImConversation();


private:

    COSSProtocolImConversation( MOSSProtocolConnectionManager& aConnManager );
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
                              TIfGetOps aOptions ) const;

	/**
	 * @see MXIMPBase
	 */
    TInt32 GetInterfaceId() const;

public: // From MProtocolImConversation
    /**
	 * @see MProtocolImConversation
	 */
    void DoSendMessageL( 
              const MImConversationInfo& aImMessage,
              TXIMPRequestId aReqId );
    /**
	 * @see MProtocolImConversation
	 */          
    void DoForwardMessageL(
              const MImConversationInfo& aImMessage,
              TXIMPRequestId aReqId);
    /**
	 * @see MProtocolImConversation
	 */
    void DoSendMessageToGroupL( 
    					const MImConversationInfo& aImMessage,
    					const TDesC* aGroupId,TXIMPRequestId aReqId );
	/**
	 * @see MProtocolImConversation
	 */
	TXIMPRequestId DoBlockUsersL(
        		const MDesCArray* aUserIds,
        		TXIMPRequestId aReqId);
	/**
	 * @see MProtocolImConversation
	 */
	TXIMPRequestId DoUnBlockUsersL(
        	const MDesCArray* aUserIds,
        	TXIMPRequestId aReqId );
    /**
	 * @see MProtocolImConversation
	 */
    void DoGetBlockedListRequestL( 
    					const MXIMPIdentity& aImMessageId,
	    				TXIMPRequestId aReqId );	        
	/**
	 * @see MProtocolImConversation
	 */
	void DoGetMessageListL( 
						const MXIMPIdentity& aImMessageId,
	 					const TDesC* aGroupId,
						const TInt aMessageCount,
						TBool aDeliveryReportWanted,
						TXIMPRequestId aReqId);
	/**
	 * @see MProtocolImConversation
	 */
	void DoRejectMessageL( 
						const MXIMPIdentity& aImMessageId,
						const TDesC& aMessageID,
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

#endif // COSSPROTOCOLIMCONVERSATION_H__
