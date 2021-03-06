/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  XIMP Framework's Presence Cache reader and writer Hook implementation.
*
*/


#include "presencedlluids.hrh"
#include "presencecacheclient.h"
#include <ecom/implementationproxy.h>
#include <e32base.h>


// ---------------------------------------------------------------------------
// Key value pair table to identify correct constructor
// function for the requested interface.
// ---------------------------------------------------------------------------
//
const TImplementationProxy ImplementationTable[] =
    {
    IMPLEMENTATION_PROXY_ENTRY( XIMP_ECOM_IMPL_UID_PRESENCE_CACHE_READER,
                                CPresenceCacheClient::CreateReaderL ),
    IMPLEMENTATION_PROXY_ENTRY( XIMP_ECOM_IMPL_UID_PRESENCE_CACHE_WRITER,
                                CPresenceCacheClient::CreateWriterL )
    };


// ---------------------------------------------------------------------------
// Exported function to return the implementation proxy table
// ---------------------------------------------------------------------------
//
EXPORT_C const TImplementationProxy* ImplementationGroupProxy( TInt& aTableCount )
    {
    aTableCount = sizeof( ImplementationTable ) / sizeof( TImplementationProxy );
    return ImplementationTable;
    }

