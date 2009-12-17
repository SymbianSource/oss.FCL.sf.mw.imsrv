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
* Description:  oss protocol plugin connection
*
*/

#include "cossprotocolconnection.h"

#include <badesca.h>
#include <ximpcontextclientinfo.h>
#include <ximpprotocolconnectionhost.h>
#include <ximpprotocolconnection.h>
#include <protocolpresencefeatures.h>
#include <ximpbase.h>
#include <ximpidentity.h>
#include <presenceinfo.h>
#include <ximpprotocolconnectionhost.h>
#include <ximpserviceinfo.h>
#include <ximpfeatureinfo.h>

#include "cossprotocolconnectionmanager.h"
#include "cossprotocolpresencefeatures.h"
#include "cossprotocolimfeatures.h"
#include "ossprotocolpluginlogger.h"
#include "cossprotocolloginrequest.h"
#include "mossprotocolconnectionmanager.h"

#include <protocolsearchfeature.h>
#include "cossprotocolsearchfeatures.h"
#include "cossprotocollogoutrequest.h"
#include <ximperrors.hrh>

// ======== COSSProtocolConnection - MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// COSSProtocolConnection::COSSProtocolConnection()
// ---------------------------------------------------------------------------
//
COSSProtocolConnection::COSSProtocolConnection()
	{
	LOGGER ( TXT ( "COSSProtocolConnection::COSSProtocolConnection() Start-End" ) );
	}

// ---------------------------------------------------------------------------
// COSSProtocolConnection::ConstructL()
// ---------------------------------------------------------------------------
//
void COSSProtocolConnection::ConstructL (
    const MXIMPServiceInfo&  aServiceInfo ,
    const MXIMPContextClientInfo& aClientCtxInfo )
	{
	LOGGER ( TXT ( "COSSProtocolConnection::ConstructL() Start" ) );

	PLUGIN_UNUSED_PARAM ( aClientCtxInfo );
	iConnMan = COSSProtocolConnectionManager::NewL();

	iConnMan->SetConnectionParamsL ( aServiceInfo.UserId(),
	                                 aServiceInfo.Password(),
	                                 aServiceInfo.IapId() );
	iPresFeatures = COSSProtocolPresenceFeatures::NewL ( *iConnMan );
	iImFeatures = COSSProtocolImFeatures::NewL ( *iConnMan );
	iSearchFeatures= COSSProtocolSearchFeature::NewL ( *iConnMan );
	LOGGER ( TXT ( "COSSProtocolConnection::ConstructL() End" ) );
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnection::NewL()
// ---------------------------------------------------------------------------
//
COSSProtocolConnection* COSSProtocolConnection::NewL (
    const MXIMPServiceInfo& aServiceInfo,
    const MXIMPContextClientInfo& aClientCtxInfo )
	{
	LOGGER ( TXT ( "COSSProtocolConnection::NewL() Start" ) );

	COSSProtocolConnection* self = new ( ELeave ) COSSProtocolConnection;
	CleanupStack::PushL ( self );
	self->ConstructL ( aServiceInfo, aClientCtxInfo );
	CleanupStack::Pop ( self );

	LOGGER ( TXT ( "COSSProtocolConnection::NewL() End" ) );
	return self;
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnection::~COSSProtocolConnection()
// ---------------------------------------------------------------------------
//
COSSProtocolConnection::~COSSProtocolConnection()
	{
	LOGGER ( TXT ( "COSSProtocolConnection::~COSSProtocolConnection() Start" ) );

    delete iSearchFeatures;
	delete iConnMan;
	delete iPresFeatures;
	delete iImFeatures;
	LOGGER ( TXT ( "COSSProtocolConnection::~COSSProtocolConnection() End" ) );
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnection::GetInterface()
// ---------------------------------------------------------------------------
//
TAny* COSSProtocolConnection::GetInterface ( TInt32 aInterfaceId,
        TIfGetOps aOptions )
	{
	LOGGER ( TXT ( "COSSProtocolConnection::GetInterface() Start" ) );

	if ( aInterfaceId == MXIMPProtocolConnection::KInterfaceId )
		{
		MXIMPProtocolConnection* self = this;
		return self;
		}

	if ( aOptions == MXIMPBase::EPanicIfUnknown )

		{
		User::Panic ( KOSSProtocolConnection, KErrExtensionNotSupported );
		}

	LOGGER ( TXT ( "COSSProtocolConnection::GetInterface() End" ) );

	return NULL;
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnection::GetInterface() const
// ---------------------------------------------------------------------------
//
const TAny* COSSProtocolConnection::GetInterface ( TInt32 aInterfaceId,
        TIfGetOps aOptions ) const
	{
	LOGGER ( TXT ( "COSSProtocolConnection::GetInterface() const Start" ) );

	if ( aInterfaceId == MXIMPProtocolConnection::KInterfaceId )
		{
		const MXIMPProtocolConnection* self = this;
		return self;
		}

	if ( aOptions == MXIMPBase::EPanicIfUnknown )
		{
		User::Panic ( KOSSProtocolConnection, KErrExtensionNotSupported );
		}

	LOGGER ( TXT ( "COSSProtocolConnection::GetInterface() const End" ) );

	return NULL;
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnection::GetInterfaceId() const
// ---------------------------------------------------------------------------
//
TInt32 COSSProtocolConnection::GetInterfaceId() const
	{
	LOGGER ( TXT ( "COSSProtocolConnection::GetInterfaceId() Start-End" ) );
	return MXIMPProtocolConnection::KInterfaceId;
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnection::PrimeHost()
// ---------------------------------------------------------------------------
//
void COSSProtocolConnection::PrimeHost ( MXIMPProtocolConnectionHost& aHost )
	{
	LOGGER ( TXT ( "COSSProtocolConnection::PrimeHost() Start" ) );

	iConnMan->SetHost ( aHost );

	LOGGER ( TXT ( "COSSProtocolConnection::PrimeHost() Start" ) );
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnection::OpenSessionL()
// ---------------------------------------------------------------------------
//
void COSSProtocolConnection::OpenSessionL (
    const MXIMPContextClientInfo& /*aClientCtxInfo*/,
    TXIMPRequestId aOpId )
	{
	if( iConntectionCreated )
		{
		iConntectionCreated++;
		iConnMan->HandleToHost().HandleRequestCompleted(aOpId,KErrNone);
		}
	else
		{
		LOGGER(TXT("COSSProtocolConnection::OpenSessionL \n"));
		COSSProtocolLoginRequest* req = 
		COSSProtocolLoginRequest::NewLC( *iConnMan, aOpId );

		req->IssueLoginRequestL();
		CleanupStack::Pop( req );	
		iConntectionCreated++;	
		}

	LOGGER ( TXT ( "COSSProtocolConnection::OpenSessionL() End" ) );
	}

// ---------------------------------------------------------------------------
// COSSProtocolConnection::OpenSessionL()
// ---------------------------------------------------------------------------
//
void COSSProtocolConnection::OpenSessionL ( const TInt& aServiceId,
        TXIMPRequestId aReqId )
	{
	LOGGER ( TXT ( "COSSProtocolConnection::OpenSessionLsettingsid \n" ) );
	if( iConntectionCreated )
		{
		iConntectionCreated++;
		iConnMan->HandleToHost().HandleRequestCompleted(aReqId,KErrNone);
		}
	else
		{
		TInt error = iConnMan->SetConnectionParamsL ( aServiceId );
		LOGGER ( TXT ( "COSSProtocolConnection::OpenSessionL settings id is %d" ), aServiceId );

		if( error == KErrNotFound )
			{
			iConnMan->HandleToHost().HandleRequestCompleted(aReqId,KXIMPErrServiceGeneralError);
			}
		else
			{
			COSSProtocolLoginRequest* req =
			COSSProtocolLoginRequest::NewLC ( *iConnMan, aReqId );	
			req->IssueLoginRequestL();
			CleanupStack::Pop ( req );
			iConntectionCreated++;	
			}
		}

	LOGGER ( TXT ( "COSSProtocolConnection::OpenSessionLsettingsid() End" ) );
	}

// ---------------------------------------------------------------------------
// COSSProtocolConnection::OpenSessionL()
// ---------------------------------------------------------------------------
//

void COSSProtocolConnection::OpenSessionL (
    const MXIMPContextClientInfo& /*aContextClient*/,
    const TInt& /*aSettingsId*/,
    TXIMPRequestId /*aReqId*/ )
	{

	}

// ---------------------------------------------------------------------------
// COSSProtocolConnection::CloseSession()
// ---------------------------------------------------------------------------
//
void COSSProtocolConnection::CloseSession (
    const MXIMPContextClientInfo& /*aClientCtxInfo*/,
    TXIMPRequestId aOpId )
	{
	LOGGER ( TXT ( "COSSProtocolConnection::CloseSession() Start" ) );
    iConntectionCreated--;
    
    // if server already disconnected no need to issue logout request
    TBool serverdisconnect = iConnMan->IsServerDisconnect();
    
    if(!iConntectionCreated && !serverdisconnect ) 
		{
		iRequestId = aOpId;
        TRAPD(error,LogoutRequestL(aOpId));
        	if( KErrNone != error )
        	{
			iConnMan->HandleToHost().HandleRequestCompleted(aOpId,error);
			
        	}
		}
	else
		{
		iConnMan->HandleToHost().HandleRequestCompleted(aOpId,KErrNone);
		}
	LOGGER ( TXT ( "COSSProtocolConnection::CloseSession() End" ) );
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnection::ReOpenSessionsL()
// ---------------------------------------------------------------------------
//
void COSSProtocolConnection::ReOpenSessionsL ( TXIMPRequestId /*aOpId*/ )
	{
	LOGGER ( TXT ( "COSSProtocolConnection::ReOpenSessionsL() Start" ) );

	LOGGER ( TXT ( "COSSProtocolConnection::ReOpenSessionsL() End" ) );
	}


// ---------------------------------------------------------------------------
// COSSProtocolConnection::GetSupportedFeaturesL()
// ---------------------------------------------------------------------------
//
void COSSProtocolConnection::GetSupportedFeaturesL ( CDesC8Array& aFeatures ) const
	{
	LOGGER ( TXT ( "COSSProtocolConnection::GetSupportedFeaturesL() Start End" ) );
	// first empty the whole array
	aFeatures.Reset();
	// then add our features there
	// currently we are not doing any negotiation from the server for the supported features.
	// based on our implimentation we are hardcoding these values.
	// actual implimentatiion requires client server negotiation to tackle supported features.
	
	using namespace NXIMPFeature::Presence;
	aFeatures.AppendL( KPublish );
	aFeatures.AppendL( KFetch );
	aFeatures.AppendL( KSubscribe );    
	aFeatures.AppendL( KUnsubscribe );    
	aFeatures.AppendL( KAddContact  );
	aFeatures.AppendL( KDeleteContact  );	
	aFeatures.AppendL( KAvatar  );
	
	using namespace NXIMPFeature::InstantMessage;
	aFeatures.AppendL( KInstantMessage );
	
	using namespace NXIMPFeature::Search;
	aFeatures.AppendL( KSearch );

	LOGGER ( TXT ( "COSSProtocolConnection::GetSupportedFeaturesL" ) );
	}

// ---------------------------------------------------------------------------
// COSSProtocolConnection::ProtocolPresenceFeatures()
// ---------------------------------------------------------------------------
//
MProtocolPresenceFeatures& COSSProtocolConnection::ProtocolPresenceFeatures()
	{
	LOGGER ( TXT ( "COSSProtocolConnection::ProtocolPresenceFeatures() Start " ) );
	return *iPresFeatures;
	}
// ---------------------------------------------------------------------------
// COSSProtocolConnection::ProtocolImFeatures()
// ---------------------------------------------------------------------------
//
/*
CProtocolImFeatures* COSSProtocolConnection::ProtocolImFeatures()
	{
	LOGGER ( TXT ( "COSSProtocolConnection::ProtocolImFeatures() Start " ) );
	return iImFeatures;
	}*/

// ---------------------------------------------------------------------------
// COSSProtocolConnection::ReleaseConnectionL()
// ---------------------------------------------------------------------------
//

void COSSProtocolConnection::ReleaseConnectionL()
	{
	LOGGER ( TXT ( "COSSProtocolConnection::ReleaseConnectionL() Start " ) );
	if( iConnMan )
		{
		iConnMan->ReleaseConnectionL();
		}

	LOGGER ( TXT ( "COSSProtocolConnection::ReleaseConnectionL() End" ) );
	}
// ---------------------------------------------------------------------------
// COSSProtocolConnection::LogoutRequestL()
// ---------------------------------------------------------------------------
//
void COSSProtocolConnection::LogoutRequestL(TXIMPRequestId aOpId)
	{
		COSSProtocolLogoutRequest* req = COSSProtocolLogoutRequest::NewLC ( *iConnMan, aOpId );

		req->IssueLogoutRequestL();

		CleanupStack::Pop ( req );
	
	
	}
// ---------------------------------------------------------------------------
// COSSProtocolConnection::GetProtocolInterface
// ---------------------------------------------------------------------------
//	
	
TAny* COSSProtocolConnection::GetProtocolInterface(TInt aInterfaceId)
	{
	LOGGER ( TXT ( "COSSProtocolConnection::ProtocolImFeatures() Start " ) );
	
	//return iImFeatures->GetInterface(aInterfaceId, MXIMPBase::EPanicIfUnknown );
	
	if(aInterfaceId == CProtocolImFeatures::KInterfaceId)
		{
		return iImFeatures->GetInterface(aInterfaceId, MXIMPBase::EPanicIfUnknown ); 
		}
		
    else if(aInterfaceId == MProtocolSearchFeature::KInterfaceId)
		{
		return  iSearchFeatures->GetInterface(aInterfaceId, MXIMPBase::EPanicIfUnknown ) ;
		}		
	
    return NULL;
	}

