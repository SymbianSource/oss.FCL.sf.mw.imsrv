/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Oss Protocol search implementation
*
*/

#include <ximpbase.h>
#include <ximpidentity.h>
#include <ximpprotocolconnectionhost.h>
#include <searchelement.h>

#include "cossprotocolsearch.h"
#include "cossprotocolconnectionmanager.h"
#include "csearchrequest.h"
#include "mossprotocolconnectionmanager.h"
#include "ossprotocolpluginlogger.h"
#include "ossprotocolpluginpanics.h"

#include "csearchgetsearchkeys.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// COSSProtocolSearch::GetInterface()
// ---------------------------------------------------------------------------
//
TAny* COSSProtocolSearch::GetInterface ( TInt32 aInterfaceId,
        TIfGetOps aOptions )
	{
	LOGGER ( TXT ( "COSSProtocolSearch::GetInterface() Start" ) );
	 
	MProtocolSearch* self= NULL;
	if ( aInterfaceId == MProtocolSearch::KInterfaceId )
		{
	     self = this ;
		}
	else
		{
		if (aOptions == MXIMPBase::EPanicIfUnknown )

			{
			User::Panic ( _L("serach"), KErrExtensionNotSupported );
			}
		}

	

	LOGGER ( TXT ( "COSSProtocolSearch::GetInterface() End" ) );

	return self;
	}


// ---------------------------------------------------------------------------
// COSSProtocolSearch::GetInterface()
// ---------------------------------------------------------------------------
//
const TAny* COSSProtocolSearch::GetInterface ( TInt32 aInterfaceId,
        TIfGetOps aOptions ) const
	{
	LOGGER ( TXT ( "COSSProtocolSearch::GetInterface() Start" ) );
	 
	const MProtocolSearch* self= NULL;
	if ( aInterfaceId == MProtocolSearch::KInterfaceId )
		{
	     self = this ;
		}
	else
		{
		if (aOptions == MXIMPBase::EPanicIfUnknown )

			{
			User::Panic ( _L("serach"), KErrExtensionNotSupported );
			}
		}

	LOGGER ( TXT ( "COSSProtocolSearch::GetInterface() End" ) );

	return self;
	}


// ---------------------------------------------------------------------------
// COSSProtocolSearch::GetInterfaceId()
// ---------------------------------------------------------------------------
//
TInt32 COSSProtocolSearch::GetInterfaceId() const
	{
	LOGGER ( TXT ( "COSSProtocolSearch::GetInterfaceId() Start-End" ) );
	return MProtocolSearch::KInterfaceId;
	}


// ---------------------------------------------------------------------------
// COSSProtocolSearch::COSSProtocolSearch()
// ---------------------------------------------------------------------------
//
COSSProtocolSearch::COSSProtocolSearch (
    MOSSProtocolConnectionManager& aConnMan )
		: iConnMan ( aConnMan )
	{
	LOGGER ( TXT ( "Groups::COSSProtocolSearch() Start-End" ) );
	}


// ---------------------------------------------------------------------------
// COSSProtocolSearch::ConstructL()
// ---------------------------------------------------------------------------
//
void COSSProtocolSearch::ConstructL()
	{
	LOGGER ( TXT ( "COSSProtocolSearch::ConstructL() Start" ) );
	LOGGER ( TXT ( "COSSProtocolSearch::ConstructL() End" ) );
	}


// ---------------------------------------------------------------------------
// COSSProtocolSearch::NewL()
// ---------------------------------------------------------------------------
//
COSSProtocolSearch* COSSProtocolSearch::NewL (
    MOSSProtocolConnectionManager& aConnMan )
	{
	LOGGER ( TXT ( "COSSProtocolSearch::NewL() Start" ) );

	COSSProtocolSearch* self =
	    new ( ELeave ) COSSProtocolSearch ( aConnMan );
	CleanupStack::PushL ( self );
	self->ConstructL( );
	CleanupStack::Pop ( self );

	LOGGER ( TXT ( "COSSProtocolSearch::NewL() End" ) );
	return self;
	}


// ---------------------------------------------------------------------------
// COSSProtocolSearch::~COSSProtocolSearch()
// ---------------------------------------------------------------------------
//
COSSProtocolSearch::~COSSProtocolSearch()
	{
	LOGGER ( TXT ( "COSSProtocolSearch::~COSSProtocolSearch() Start" ) );

	LOGGER ( TXT ( "COSSProtocolSearch::~COSSProtocolSearch() End" ) );
	}



// ---------------------------------------------------------------------------
// COSSProtocolSearch::DoSearchL()
// ---------------------------------------------------------------------------
//
void COSSProtocolSearch::DoSearchL( const  MXIMPIdentity& aSearchId,
    							    const  RPointerArray< MSearchElement >& aObjs,
                                    TInt   aSearchLimit,
                                    TXIMPRequestId  aReqId )
   {
   LOGGER ( TXT ( "COSSProtocolSearch::DoSearchL() Start" ) );
   
   CSearchrequest* req = CSearchrequest::NewLC ( iConnMan, aReqId );
   req->SearchL(aSearchId,aObjs,aSearchLimit); 
   
   CleanupStack::Pop ( req ); // req is deleted by itself once it completes the operation

   LOGGER ( TXT ( "COSSProtocolSearch::DoSearchL() End" ) );
   }
                               		   

// ---------------------------------------------------------------------------
// COSSProtocolSearch::DoSearchL()
// ---------------------------------------------------------------------------
//
void COSSProtocolSearch::DoGetSearchKeysL( TXIMPRequestId aReqId )
   {
   LOGGER ( TXT ( "COSSProtocolSearch::DoSearchL() Start" ) );
   //Shoudl be changed to NewLC
   CSearchGetSearchKeys* req = CSearchGetSearchKeys::NewL ( 
   								iConnMan, aReqId );
  // req->SearchL(aSearchId,aObjs,aSearchLimit); 
  
   req->GetSearchKeysL();
   
   //CleanupStack::Pop ( req ); // req is deleted by itself once it completes the operation

   LOGGER ( TXT ( "COSSProtocolSearch::DoSearchL() End" ) );
   }
// End of file

