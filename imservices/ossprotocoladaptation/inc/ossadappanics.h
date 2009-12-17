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
* Description:  oss adapter plugin panics
*
*/

#ifndef __OSSADAPPANICS_H__
#define __OSSADAPPANICS_H__

//  INCLUDES
#include    <e32std.h>

// CONSTANTS
/**
* Oss Adaptation Library panic category.
*/
_LIT ( KOssAdapPanic, "OssAdaptation" );

/**
* OSS Adaptation Library Auth interface
*/

_LIT ( KOssProtocolPresenceAuthorization, "CImpsProtocolPresenceAuthorization" );

/**
* OSS Adaptation Library Publishing panic category
*/

_LIT ( KOssProtocolPresencePublishing, "CImpsProtocolPresencePublishing" );

/**
* Oss adapter Library watching panic category.
*/

_LIT ( KOssProtocolPresenceWatching, "CImpsProtocolPresenceWatching" );

/**
* Oss adapter Library groups panic category.
*/

_LIT ( KOssProtocolPresentityGroups, "CImpsProtocolPresentityGroups" );

/**
* OSS adapter plugin library panic reasons.
*
* Following panic reasons are used in
* oss adapter plugin library panics.
*
* @since 3.0
*/
enum TOssAdapterPluginPanics
	{
	ESesionConsistencyLost                      = 1,
	EOpIdConsistencyLost                        = 2,
	ENoActiveOperations                         = 3,
	EUnknownUnumeration                         = 4,
	EReferenceCountUnderflow                    = 5,
	EIlegalSingletonDeletion                    = 6,
	EUnknowPureData                             = 7,
	EListenerAlreadyActive                      = 8,
	ELogInDataNotValid                          = 9

	};


#endif  //__OSSADAPPANICS_H__

//  End of File

