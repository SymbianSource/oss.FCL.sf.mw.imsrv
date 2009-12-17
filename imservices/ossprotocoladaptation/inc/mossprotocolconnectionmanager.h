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
* Description:  oss protocol plugin connection manager interface
*
*/

#ifndef __MOSSCONNNECTIONMANAGERCONTROL_H__
#define __MOSSCONNNECTIONMANAGERCONTROL_H__


// FORWARD DECLARATIONS

class MXIMPProtocolConnectionHost;
class CXmppParameters;
class CWaitTimer;
class MProtocolImDataHost;
class MProtocolSearchDataHost;
class CSearchKeyStore;
class CAddContactNotificationHandler;
class COSSContactManager;
/**
 * MOSSProtocolConnectionManager
 *
 * Telepathy Plugin Connection Manager's Interface
 *
 */
class MOSSProtocolConnectionManager
    {

public:

    /**
     * ?description
     *
     * access to xmpp settings 
     * @return handle to xmppparameter
     */
	virtual CXmppParameters& XmppParams() = 0;
    /**
     * access to protocol data handler
     * @return protocol data handler
     */
		virtual CWaitTimer& DataHandler() = 0;
    /**
     * access to protocol connection host
     * @return protocol connection host
     */
    virtual MXIMPProtocolConnectionHost& HandleToHost() = 0;
    /**
     * creates datahanlder
     * @return access point
     *
     */    
    virtual void ManufactureDataHandlerL() = 0;
    /**
     * check the data handler creation
     * @return ETrue,if datahandler created,else EFalse
     */ 
        
	virtual TDesC& UserName() = 0;
	/**
	 *
	 * @return Passwor
	 */
	virtual TDesC& Password() = 0;
	/**
	 * @return GroupId
	 */
	virtual TDesC& GroupId() =0 ;
	/**
	 * @return ServiceName
	 */
	virtual const TDesC& ServiceName() = 0;   	
	/**
	 * sets the groupid
	 * @param aGroupId : group id to be set
	 */
	virtual void SetGroupIDL(TDesC& aGroupId) = 0;
	/**
	 * gets the contactmanager
	 * @return iContactManager
	 */
	virtual COSSContactManager& GetContactManager() = 0;
	/**
	 * @return authorised list
	 */
	virtual RArray<HBufC>* PresenceAuthGrantReqList() = 0;
	/**
	 * @return im data host
	 */
	virtual MProtocolImDataHost& GetImHost() = 0;
	/**
	 * @return add notification handler
	 */
	virtual CAddContactNotificationHandler& GetAddNotificationHandler() = 0;
	/**
	 * @return search data host
	 */
	virtual MProtocolSearchDataHost& GetSearchHost() = 0;
	/**
	 * @return search key store
	 */
	virtual CSearchKeyStore& GetSearchKeyStore() = 0;
   
protected:

    /**
     * Protected destructor.
     * Instancies can't be destroyed via this interface.
     */
    virtual ~MOSSProtocolConnectionManager() {}

    };

#endif // __MOSSCONNNECTIONMANAGERCONTROL_H__


