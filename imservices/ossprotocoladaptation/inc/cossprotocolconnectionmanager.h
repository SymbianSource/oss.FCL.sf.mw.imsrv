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
* Description:  connection manager
*
*/

#ifndef __COSSPROTOCOLCONNECTIONMANAGER_H__
#define __COSSPROTOCOLCONNECTIONMANAGER_H__

//  INCLUDES
#include <e32base.h>
#include <flogger.h>
#include <ximpstatus.h>
#include "mossprotocolconnectionmanager.h"
#include "waittimer.h"
#include "cpresencenotificationhandler.h"
#include "creceivemessagehandler.h"
#include "cossprotocolservererrorhandler.h"
#include "caddcontactenotificationhandler.h"
#include "cosscontactmanager.h"
#include "msg_enums.h"
#include <ximperrors.hrh>
#include "csearchkeystore.h"

// FORWARD DECLARATIONS

class MXIMPServiceInfo;

class MXIMPProtocolConnectionHost;

class MOSSProtocolConnectionManager;

class CXmppParameters;

class CWaitTimer;
class MProtocolImDataHost ;
class MProtocolSearchDataHost;
class CContactSyncHandler;

_LIT(KColon,":");

/**
 * COSSProtocolConnectionManager
 *
 * Every XIMPFW-OSS Connection has Connection Manager Object.
 *
 *
 */
NONSHARABLE_CLASS ( COSSProtocolConnectionManager ) : public CBase,
		public MOSSProtocolConnectionManager
		// implement session status observer callback
	{

public:

	static COSSProtocolConnectionManager* NewL();
	virtual ~COSSProtocolConnectionManager();


private:

	COSSProtocolConnectionManager();
	void ConstructL();


public: // From MOSSProtocolConnectionManager
	
    /**
	 * @see MOSSProtocolConnectionManager
	 */
	CXmppParameters& XmppParams();
	
	/**
	 * @see MOSSProtocolConnectionManager
	 */
	CWaitTimer& DataHandler();
	
	/**
	 * @see MOSSProtocolConnectionManager
	 */
	MXIMPProtocolConnectionHost& HandleToHost();
	
	/**
	 * @see MOSSProtocolConnectionManager
	 */
	void ManufactureDataHandlerL() ;
	
	/**
	 * @see MOSSProtocolConnectionManager
	 */
	RArray< HBufC >* PresenceAuthGrantReqList();
	
public: // new methods

	/**
     * set protocol connection host
     * @param aHost protocol connection host
     */
	void SetHost ( MXIMPProtocolConnectionHost& aHost );

	/**
     * set connection parameters
     * @param aUserName user account
     * @param aPassword password
     * @param aServiceId ,service id
     */
	void SetConnectionParamsL ( const TDesC& aUserName,
	                            const TDesC& aPassword,
	                            const TInt32 aServiceId );

	 /**
	  * set connection parameters
	  * @param aServiceId, service id
	  * @param aReadNedded, EFalse if need not to red from xmpp settings
	  * @return error if any
	  */
	TInt SetConnectionParamsL ( const TUint32 aServiceId, TBool aReadNeeded = ETrue );
	
	
	/**
     * set protocol im data host
     * @param aHost protocol im data host
     */
	void SetImHost(MProtocolImDataHost& aHost);
	
	/**
     * Get protocol im data host
     * @param aHost protocol im data host
     */
	MProtocolImDataHost& GetImHost() ;
	
	/**
	 * Get add notification handler
	 * @param iAddnotificationhandler 
	 */
	CAddContactNotificationHandler& GetAddNotificationHandler();
	/**
     * set protocol search data host
     * @param aHost protocol search data host
     */
	void SetSearchHost(MProtocolSearchDataHost& aHost);
	
	/**
     * Get protocol search data host
     * @param aHost protocol search data host
     */
	MProtocolSearchDataHost& GetSearchHost() ;
	
	/**
	 * Release Connection
	 *  send killing request to isoserver
	 */
	void ReleaseConnectionL();
	

	/**
	 *  return ETrue if server disconnect has happen
	 */
	TBool IsServerDisconnect();
	
	/*!	/brief Gets a handle to search key store
	 *	/return A handle to search key store
	 */
	CSearchKeyStore& GetSearchKeyStore();
		    
public:

    /**
	 *  Get id
	 *  @return id
	 */
	TInt32 IapId();
	
	/**
	 *  Get username
	 *  @return username
	 */
	TDesC& UserName();
	
	/**
	 *  Get password
	 *  @return password
	 */
	TDesC& Password();
	
	/**
	 *  Get groupid
	 *  @return groupid
	 */
	TDesC& GroupId();
	/**
	 *  Get service name
	 *  @return servicename
	 */
	const TDesC& ServiceName();   	
	/**
	 *  Set group id
	 *  @param group id
	 */
	void SetGroupIDL(TDesC& aGroupId);
	
	/**
	 * gets the contactmanager
	 * @return iContactManager
	 */
	COSSContactManager& GetContactManager();
	
	
private: // data
    
    /**
	 * Stores settings
	 * Own
	 */
	CXmppParameters* iXmppParams;
	
	/**
	 * REF: protocol connection host
	 */
	MXIMPProtocolConnectionHost* iHostHandle;
	
	/**
	 * Server address:
	 * Own
	 */
	HBufC* iServerAddress;
	
	/**
	 * UserName:
	 * Own
	 */
	HBufC* iUserName;
	
	/**
	 * UserName:
	 * Own
	 */
	HBufC* iPassword;
	
	/**
	 * Group id:
	 * Own
	 */
	HBufC* iGroupId;
	
	/**
	 * wait scheduler:
	 * Own
	 */
	CActiveSchedulerWait* iWaitScheduler;
	
	/**
	 * wait timer:
	 * Own
	 */
	CWaitTimer* iTimer;
	
	/**
	 * Presence notifier:
	 * Own
	 */
	CPresenceNotificationHandler* iNotifier;
	
	/**
	 * Recieve message handler:
	 * Own
	 */
	CReceiveMessageHandler* iRecvHandler;
	
	/**
	 * Server intiated error hanlder:
	 * Own
	 */
	COssprotocolServerErrorHandler* iServerErrorHandler;
	
	/**
	 * Add notifications handler
	 * Own
	 */
	CAddContactNotificationHandler* iAddNotificationHanlder;
	
	/**
	 * Contact synchronisation handler:
	 * Own
	 */
	CContactSyncHandler*    iContactSyncHandler;
	
	/**
	 * stores data handler readyness value
	 * Own
	 */
	TBool iIsDataHandlerReady; 
	
	/**
	 * Search key store
	 * Own
	 */
	CSearchKeyStore* iSearchKeyStore;
	
	/**
	 * Protocol im data host
	 * Doesn't own
	 */
	MProtocolImDataHost *iHost ; 
	
	/**
	 * Protocl search data host
	 * Doesn't own
	 */
	MProtocolSearchDataHost *iSearchHost ; 
	
	/**
	 * local contact manager
	 * own
	 */
	COSSContactManager* iContactManager;
	/**
	 * service name for presence cache updation
	 * Own
	 */
	HBufC* iServiceName;	
public:	
    /**
	 * Presence authorisation grant list
	 * Doesn't own
	 */
	RArray< HBufC > iPresenceAuthGrantReqList;
	
	
	};


#endif // __COSSPROTOCOLCONNECTIONMANAGER_H__
