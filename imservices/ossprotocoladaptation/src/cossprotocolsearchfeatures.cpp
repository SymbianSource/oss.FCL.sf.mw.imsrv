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
* Description:  oss protocol plugin search features
*
*/

#include "cossprotocolsearchfeatures.h"
#include <badesca.h>
#include "cossprotocolsearch.h"
#include "ossprotocolpluginlogger.h"

_LIT ( KOSSProtocolSearchFeatures, "COSSProtocolSearchFeature" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// COSSProtocolConnection::COSSProtocolSearchFeature()
// ---------------------------------------------------------------------------
//
COSSProtocolSearchFeature::COSSProtocolSearchFeature(COSSProtocolConnectionManager& aConnMan) : iConnMan (aConnMan)
	{
	}

// ---------------------------------------------------------------------------
// COSSProtocolSearchFeature::ConstructL()
// ---------------------------------------------------------------------------
//
void COSSProtocolSearchFeature::ConstructL (
    COSSProtocolConnectionManager& aConnMan )
	{
	iSearch = COSSProtocolSearch::NewL ( aConnMan );
	}

// ---------------------------------------------------------------------------
// COSSProtocolSearchFeature::NewL()
// ---------------------------------------------------------------------------
//
COSSProtocolSearchFeature* COSSProtocolSearchFeature::NewL (
    COSSProtocolConnectionManager& aConnMan )
	{

	COSSProtocolSearchFeature* self = new ( ELeave ) COSSProtocolSearchFeature(aConnMan);
	CleanupStack::PushL ( self );
	self->ConstructL ( aConnMan );
	CleanupStack::Pop ( self );

	return self;
	}

// ---------------------------------------------------------------------------
// COSSProtocolSearchFeature::~COSSProtocolSearchFeature()
// ---------------------------------------------------------------------------
//
COSSProtocolSearchFeature::~COSSProtocolSearchFeature()
	{
	delete iSearch;
	}


// ---------------------------------------------------------------------------
// COSSProtocolSearchFeature::GetInterface()
// ---------------------------------------------------------------------------
//
TAny* COSSProtocolSearchFeature::GetInterface ( TInt32 aInterfaceId,
        TIfGetOps aOptions )
	{
	MProtocolSearchFeature* self = NULL;
	if ( aInterfaceId == MProtocolSearchFeature::KInterfaceId )
		{
	    self = this;
		}
    else
	   {
	   if ( aOptions == MXIMPBase::EPanicIfUnknown )

			{
			User::Panic ( KOSSProtocolSearchFeatures, KErrExtensionNotSupported );
			}	
	   }

	return self;
	}
	
// ---------------------------------------------------------------------------
// COSSProtocolSearchFeature::SetHost
// ---------------------------------------------------------------------------
//

void COSSProtocolSearchFeature::SetHost(MProtocolSearchDataHost& aSearchHost )
	{
	iConnMan.SetSearchHost(aSearchHost) ; // set this in connection manager.
	}

// ---------------------------------------------------------------------------
// COSSProtocolSearchFeature::GetInterface()
// ---------------------------------------------------------------------------
//
const TAny* COSSProtocolSearchFeature::GetInterface ( TInt32 aInterfaceId,
        TIfGetOps aOptions ) const
	{
 
	const MProtocolSearchFeature* self = NULL;
	if ( aInterfaceId == MProtocolSearchFeature::KInterfaceId )
		{
	    self = this;
		}
    else
	   {
	   if ( aOptions == MXIMPBase::EPanicIfUnknown )

			{
			User::Panic ( KOSSProtocolSearchFeatures, KErrExtensionNotSupported );
			}	
	   }

	return self;
	}


// ---------------------------------------------------------------------------
// COSSProtocolSearchFeature::GetInterfaceId() const
// ---------------------------------------------------------------------------
//
TInt32 COSSProtocolSearchFeature::GetInterfaceId() const
	{
	return MProtocolSearchFeature::KInterfaceId;
	}


// ---------------------------------------------------------------------------
// COSSProtocolSearchFeature::search()
// ---------------------------------------------------------------------------
//
MProtocolSearch& COSSProtocolSearchFeature::Search()
	{
	return *iSearch;
	}

	
// End of file
