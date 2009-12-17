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
* Description:  oss presence features implementation for XIMP Framework
*
*/

#include "cossprotocolpresencefeatures.h"
#include <protocolpresentitygroups.h>
#include <protocolpresencepublishing.h>
#include <protocolpresenceauthorization.h>
#include <badesca.h>
#include "cossprotocolpresentitygroups.h"
#include "ossprotocolpluginlogger.h"
#include "cossprotocolpresencepublishing.h"
#include "cossprotocolpresenceauthorization.h"

_LIT ( KOSSProtocolPresenceFeatures, "COSSProtocolPresenceFeatures" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// COSSProtocolConnection::COSSProtocolPresenceFeatures()
// ---------------------------------------------------------------------------
//
COSSProtocolPresenceFeatures::COSSProtocolPresenceFeatures()
	{
	}

// ---------------------------------------------------------------------------
// COSSProtocolPresenceFeatures::ConstructL()
// ---------------------------------------------------------------------------
//
void COSSProtocolPresenceFeatures::ConstructL (
    COSSProtocolConnectionManager& aConnMan )
	{
	iPresentityGroups = COSSProtocolpresentitygroups::NewL ( aConnMan );
	iPresencePublishing = COssProtocolPresencePublishing::NewL ( aConnMan );
	iAuthrozation = COssProtocolPresenceAuthorization::NewL ( aConnMan );
	}

// ---------------------------------------------------------------------------
// COSSProtocolPresenceFeatures::NewL()
// ---------------------------------------------------------------------------
//
COSSProtocolPresenceFeatures* COSSProtocolPresenceFeatures::NewL (
    COSSProtocolConnectionManager& aConnMan )
	{

	COSSProtocolPresenceFeatures* self = new ( ELeave ) COSSProtocolPresenceFeatures;
	CleanupStack::PushL ( self );
	self->ConstructL ( aConnMan );
	CleanupStack::Pop ( self );

	return self;
	}

// ---------------------------------------------------------------------------
// COSSProtocolPresenceFeatures::~COSSProtocolPresenceFeatures()
// ---------------------------------------------------------------------------
//
COSSProtocolPresenceFeatures::~COSSProtocolPresenceFeatures()
	{
	delete iPresentityGroups;
	delete iPresencePublishing;
	delete iAuthrozation;
	}


// ---------------------------------------------------------------------------
// COSSProtocolPresenceFeatures::GetInterface()
// ---------------------------------------------------------------------------
//
TAny* COSSProtocolPresenceFeatures::GetInterface ( TInt32 aInterfaceId,
        TIfGetOps aOptions )
	{
	if ( aInterfaceId == MProtocolPresenceFeatures::KInterfaceId )
		{
		MProtocolPresenceFeatures* self = this;
		return self;
		}

	if ( aOptions == MXIMPBase::EPanicIfUnknown )

		{
		User::Panic ( KOSSProtocolPresenceFeatures, KErrExtensionNotSupported );
		}

	return NULL;
	}


// ---------------------------------------------------------------------------
// COSSProtocolPresenceFeatures::GetInterface()
// ---------------------------------------------------------------------------
//
const TAny* COSSProtocolPresenceFeatures::GetInterface ( TInt32 aInterfaceId,
        TIfGetOps aOptions ) const
	{

	if ( aInterfaceId == MProtocolPresenceFeatures::KInterfaceId )
		{
		const MProtocolPresenceFeatures* self = this;
		return self;
		}

	if ( aOptions == MXIMPBase::EPanicIfUnknown )
		{
		User::Panic ( KOSSProtocolPresenceFeatures, KErrExtensionNotSupported );
		}

	return NULL;
	}


// ---------------------------------------------------------------------------
// COSSProtocolPresenceFeatures::GetInterfaceId()
// ---------------------------------------------------------------------------
//
TInt32 COSSProtocolPresenceFeatures::GetInterfaceId() const
	{
	return MProtocolPresenceFeatures::KInterfaceId;
	}

// ---------------------------------------------------------------------------
// COSSProtocolPresenceFeatures::PresenceWatching()
// ---------------------------------------------------------------------------
//
MProtocolPresenceWatching& COSSProtocolPresenceFeatures::PresenceWatching()
	{
	MProtocolPresenceWatching* dummyWatch = NULL;
	return *dummyWatch;
	}

// ---------------------------------------------------------------------------
// COSSProtocolPresenceFeatures::PresencePublishing()
// ---------------------------------------------------------------------------
//
MProtocolPresencePublishing& COSSProtocolPresenceFeatures::PresencePublishing()
	{
	return	*iPresencePublishing;
	}

// ---------------------------------------------------------------------------
// COSSProtocolPresenceFeatures::PresentityGroups()
// ---------------------------------------------------------------------------
//
MProtocolPresentityGroups& COSSProtocolPresenceFeatures::PresentityGroups()
	{
	return *iPresentityGroups;
	}

// ---------------------------------------------------------------------------
// COSSProtocolPresenceFeatures::PresenceAuthorization()
// ---------------------------------------------------------------------------
//
MProtocolPresenceAuthorization& COSSProtocolPresenceFeatures::PresenceAuthorization()
	{
	return *iAuthrozation;
	}

// End of file







