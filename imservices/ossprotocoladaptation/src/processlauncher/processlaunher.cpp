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
* Description:  implementation of launching of process
*
*/


// INCLUDE FILES
#include "processlaunher.h"

#include <e32std.h>
#include "ossprotocolpluginlogger.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CProcessLauncher::CProcessLauncher
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CProcessLauncher::CProcessLauncher() :
		CActive ( EPriorityStandard )
	{
	CActiveScheduler::Add ( this );
	}

// -----------------------------------------------------------------------------
// CProcessLauncher::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CProcessLauncher::ConstructL ( const TDesC16& aprocessname )
	{
	LOGGER ( TXT ( "CProcessLauncher::ConstructL()" ) );
	iProcessName = aprocessname.AllocL();
	}

// -----------------------------------------------------------------------------
// CProcessLauncher::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CProcessLauncher* CProcessLauncher::NewL ( const TDesC16& aprocessname )
	{
	LOGGER ( TXT ( "CProcessLauncher::NewL()" ) );

	CProcessLauncher* self =
	    new ( ELeave ) CProcessLauncher();

	CleanupStack::PushL ( self );
	self->ConstructL ( aprocessname );
	CleanupStack::Pop();

	return self;
	}

// Destructor
CProcessLauncher::~CProcessLauncher()
	{
	Cancel();
	delete iProcessName;
	}


// ---------------------------------------------------------
// CProcessLauncher::DoCancel
//
// ---------------------------------------------------------
//
void CProcessLauncher::DoCancel()
	{
	iLauncher.LogonCancel ( iStatus );

	}

// ---------------------------------------------------------
// CProcessLauncher::RunL
//
// ---------------------------------------------------------
//
void CProcessLauncher::RunL()
	{
	TInt answer ( iStatus.Int() );

	if ( answer != KErrNone )
		{
		LOGGER ( TXT ( "CProcessLauncher::dd terminated with the reason %d" ), answer );

		User::LeaveIfError ( answer );
		}

	Cancel();
	}

// ---------------------------------------------------------
// CProcessLauncher::RunError
//
// ---------------------------------------------------------
//
TInt CProcessLauncher::RunError ( TInt aError )
	{
	if ( IsActive() )
		{
		Cancel();
		}

	return aError;
	}
// ---------------------------------------------------------
// CProcessLauncher::LaunchProcessL
// ---------------------------------------------------------
//
void CProcessLauncher::LaunchProcessL()
	{
	LOGGER ( TXT ( "CProcessLauncher::LaunchProcessL() start" ) );
	TInt result = KErrNotFound;

	result = iLauncher.Create ( *iProcessName, KNullDesC );

	if ( result != KErrNone )
		{
		LOGGER ( TXT ( "CProcessLauncher::launching isoserver is failed with the reason %d" ), result );
		User::Leave ( result );
		}

	// When the launcher exits we'll get the exit code in iStatus
	iStatus = KRequestPending;

	SetActive();

	iLauncher.Logon ( iStatus );

	iLauncher.Resume();

	//iLauncher.Close();
	LOGGER ( TXT ( "CProcessLauncher::LaunchProcessL() End " ) );
	}
	
// End of file
