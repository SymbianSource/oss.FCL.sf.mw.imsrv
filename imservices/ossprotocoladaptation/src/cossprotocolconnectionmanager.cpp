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

#include "cossprotocolconnectionmanager.h"
#include "cossprotocolservererrorhandler.h"
#include "ccontactsynchandler.h"
#include <e32std.h>
#include <e32base.h>
#include <ximpobjectfactory.h>
#include <ximpprotocolconnectionhost.h>
#include <ximpstatus.h>
#include "xmppservicesettingsapi.h"
#include "xmppparams.h" //from xmppsettingsapi

#include "xmppsettingsfetcher.h"
#include "xmppparameters.h"
#include "waittimer.h"

#include <spsettings.h>
#include <spentry.h>
#include <spproperty.h>

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::COSSProtocolConnectionManager()
// ---------------------------------------------------------------------------
//
COSSProtocolConnectionManager::COSSProtocolConnectionManager()
	{
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::ConstructL()
// ---------------------------------------------------------------------------
//
void COSSProtocolConnectionManager::ConstructL()
	{
	iXmppParams = CXmppParameters::NewL();
	iTimer = CWaitTimer::NewL (*this);
	iTimer->StartListeningL();  //start listening message queue updation
	iNotifier = CPresenceNotificationHandler::NewL ( *this );
	iNotifier->StartListeningL();  //start listening presence notifications
	iSearchKeyStore = CSearchKeyStore::NewL();
	iContactManager = COSSContactManager::NewL( *this );
	
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::NewL()
// ---------------------------------------------------------------------------
//
COSSProtocolConnectionManager* COSSProtocolConnectionManager::NewL()
	{

	COSSProtocolConnectionManager* self = new ( ELeave )
									      COSSProtocolConnectionManager();

	CleanupStack::PushL ( self );

	self->ConstructL();
	CleanupStack::Pop ( self );

	return self;
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::~COSSProtocolConnectionManager()
// ---------------------------------------------------------------------------
//
COSSProtocolConnectionManager::~COSSProtocolConnectionManager()
	{
	delete iXmppParams;
	delete iNotifier;
	delete iRecvHandler;
	delete iServerErrorHandler;
	delete iAddNotificationHanlder;
	delete iContactSyncHandler;
	delete iUserName;
	delete iPassword;
	delete iTimer;
	delete iGroupId;
	delete iContactManager;
	delete iSearchKeyStore;
	if(iServiceName)
	    {
	    delete iServiceName;
	    }
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::Username
// ---------------------------------------------------------------------------
//
TDesC& COSSProtocolConnectionManager::UserName()
	{
	return *iUserName;
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::Password
// ---------------------------------------------------------------------------
//
TDesC& COSSProtocolConnectionManager::Password()
	{
	return *iPassword;
	}

// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::GroupID
// ---------------------------------------------------------------------------
//
TDesC& COSSProtocolConnectionManager::GroupId()
	{
	return *iGroupId;
	}

// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::GroupID
// ---------------------------------------------------------------------------
//
void COSSProtocolConnectionManager::SetGroupIDL(TDesC& aGroupId)
	{
	HBufC* tmpId = aGroupId.AllocL();
	delete iGroupId;
	iGroupId=NULL;
	iGroupId = tmpId ;
	}

// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::XmppParams
// ---------------------------------------------------------------------------
//
CXmppParameters& COSSProtocolConnectionManager::XmppParams()
	{
	return *iXmppParams;
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::DataHandler()
// ---------------------------------------------------------------------------
//
CWaitTimer& COSSProtocolConnectionManager::DataHandler()
	{
	return *iTimer;
	}

// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::HandleToHost()
// ---------------------------------------------------------------------------
//
MXIMPProtocolConnectionHost& COSSProtocolConnectionManager::HandleToHost()
	{
	return *iHostHandle;
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::SetHost()
// ---------------------------------------------------------------------------
//
void COSSProtocolConnectionManager::SetHost ( MXIMPProtocolConnectionHost& aHost )
	{
	iHostHandle = &aHost;
	}

// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::SetConnectionParamsL()
// ---------------------------------------------------------------------------
//
void COSSProtocolConnectionManager::SetConnectionParamsL ( const TDesC& aUserName,
        const TDesC& aPassword,
        const TInt32 aServiceId )
	{

	// first store the login parameters

	HBufC* tmpBuf = aUserName.AllocL();
	delete iUserName;
	iUserName = tmpBuf;

	tmpBuf = aPassword.AllocL();
	delete iPassword;
	iPassword = tmpBuf;

	SetConnectionParamsL( aServiceId, EFalse );
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::ManufactureDataHandlerL()
// ---------------------------------------------------------------------------
//
void COSSProtocolConnectionManager::ManufactureDataHandlerL()
	{
	if(!iIsDataHandlerReady)
		{
		iRecvHandler = CReceiveMessageHandler::NewL ( *this );
		iRecvHandler->StartListeningL();//start listening incoming messages
		iServerErrorHandler = COssprotocolServerErrorHandler::NewL ( *this );
		iServerErrorHandler->StartListeningL();//start listening incoming messages
		iAddNotificationHanlder = CAddContactNotificationHandler::NewL ( *this );
		iContactSyncHandler = CContactSyncHandler::NewL(*this);
		iContactSyncHandler->StartListening(); // listening for contacts changes
		iIsDataHandlerReady = ETrue;
		}
	}

// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::SetConnectionParamsL
// ---------------------------------------------------------------------------
//
TInt COSSProtocolConnectionManager::SetConnectionParamsL ( const TUint32 aServiceId , TBool aReadNeeded /* = ETrue*/ )
	{
		// Get the service setting id and service name	
	TInt error = KErrNone;
	
	CSPSettings* settings = CSPSettings::NewLC();
	
	if(aReadNeeded)
		{
		TInt settingsId = 0; 
		CSPProperty* property = CSPProperty::NewLC();
		settings->FindPropertyL( aServiceId,
		               			 ESubPropertyIMSettingsId,
		                		*property );    
		if ( property )
			{
			property->GetValue( settingsId );
			}
		// read settings

		error = CXmppSettingsFetcher::ReadSettingsL ( settingsId, *iXmppParams ); //settings id is used to read settings

		CleanupStack::PopAndDestroy(); // property

		}
	// read service name 	
	CSPEntry* entry = CSPEntry::NewLC();
    settings->FindEntryL( aServiceId, *entry ) ;
    
    // set the service name to presence cache updater
    if(iServiceName)
        {
        delete iServiceName;
        iServiceName = NULL;
        }
    iServiceName = entry->GetServiceName().AllocL();
    CleanupStack::PopAndDestroy(2); // entry, settings
    
	return error;
	}
// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::PresenceAuthGrantReqList()
// ---------------------------------------------------------------------------
//	
RArray< HBufC >* COSSProtocolConnectionManager::PresenceAuthGrantReqList()
	{
	return &iPresenceAuthGrantReqList;
	}

// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::ReleaseConnectionL()
// ---------------------------------------------------------------------------
//	
void COSSProtocolConnectionManager::ReleaseConnectionL()
	{
	if( iTimer )
		{
		iTimer->IssueReleaseRequestL();	
		}
	}

// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::IsServerDisconnect()
// ---------------------------------------------------------------------------
//	
TBool COSSProtocolConnectionManager::IsServerDisconnect()
	{
	return iTimer->IsServerDisconnect();	
	}
// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::SetImHost
// ---------------------------------------------------------------------------
//	
	
void COSSProtocolConnectionManager::SetImHost(MProtocolImDataHost& aHost)
	{
	iHost = &aHost ;
	}	
// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::GetImHost()
// ---------------------------------------------------------------------------
//
MProtocolImDataHost& COSSProtocolConnectionManager::GetImHost()
	{
	return *iHost;
	}

// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::GetAddNotificationHandler()
// ---------------------------------------------------------------------------
//
CAddContactNotificationHandler& COSSProtocolConnectionManager::GetAddNotificationHandler()
    {
    return *iAddNotificationHanlder;
    }
// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::SetSearchHost
// ---------------------------------------------------------------------------
//		
void COSSProtocolConnectionManager::SetSearchHost(MProtocolSearchDataHost& aSearchHost)
	{
	iSearchHost = &aSearchHost ;
	}	
// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::GetSearchHost()
// ---------------------------------------------------------------------------
//	
MProtocolSearchDataHost& COSSProtocolConnectionManager::GetSearchHost()
	{
	return *iSearchHost;
	}
// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::GetSearchKeyStore()
// ---------------------------------------------------------------------------
//	
CSearchKeyStore& COSSProtocolConnectionManager::GetSearchKeyStore()
	{
	return *iSearchKeyStore;		
	}

// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::GetContactManager()
// ---------------------------------------------------------------------------
//
COSSContactManager& COSSProtocolConnectionManager::GetContactManager()
    {
    return *iContactManager;
    }
// ---------------------------------------------------------------------------
// COSSProtocolConnectionManager::ServiceName()
// ---------------------------------------------------------------------------
//
const TDesC& COSSProtocolConnectionManager::ServiceName()
    {
    return *iServiceName;
    }
// End of File


