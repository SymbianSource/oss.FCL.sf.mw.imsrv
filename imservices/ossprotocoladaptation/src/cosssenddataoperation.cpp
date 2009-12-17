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
* Description: cosssenddataoperation.cpp
*
*/

//  INCLUDES
#include    <e32std.h>

#include    "cosssenddataoperation.h"
#include    "ossprotocolpluginlogger.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// COssSendDataOperation::COssSendDataOperation()
// ---------------------------------------------------------------------------
//
COssSendDataOperation::COssSendDataOperation () 
						: iOpId ( KErrNone )
		{
		iData = NULL;
		LOGGER ( TXT ( "COssSendDataOperation::COssSendDataOperation Start End" ) );
		}
// ---------------------------------------------------------------------------
// COssSendDataOperation::~COssSendDataOperation()
// ---------------------------------------------------------------------------
//
COssSendDataOperation::~COssSendDataOperation () 
		{
		LOGGER ( TXT ( "COssSendDataOperation::~COssSendDataOperation Start" ) );
		delete iData;

		if ( iStatus )
			{
			User::RequestComplete ( iStatus, KErrCancel );
			}

		LOGGER ( TXT ( "COssSendDataOperation::~COssSendDataOperation End" ) );
		}

// ---------------------------------------------------------------------------
// COssSendDataOperation::SetIds()
// ---------------------------------------------------------------------------
//
void COssSendDataOperation::SetIds ( TInt aOperationId, TInt aLogId )
		{
		LOGGER ( TXT ( "COssSendDataOperation::SetIds Start" ) );
		iOpId = aOperationId;
		iLogId = aLogId;
		LOGGER ( TXT ( "COssSendDataOperation::SetIds End" ) );
		}
	
	
// ---------------------------------------------------------------------------
// COssSendDataOperation::SetRequestStatus()
// ---------------------------------------------------------------------------
//
void COssSendDataOperation::SetRequestStatus ( TRequestStatus& aStatus )
		{
		LOGGER ( TXT ( "COssSendDataOperation::SetRequestStatus Start" ) );
		iStatus = &aStatus;
		LOGGER ( TXT ( "COssSendDataOperation::SetRequestStatus End" ) );
		} 
	
// ---------------------------------------------------------------------------
// COssSendDataOperation::Status()
// ---------------------------------------------------------------------------
//
TRequestStatus* COssSendDataOperation::Status()
		{
		LOGGER ( TXT ( "COssSendDataOperation::Status Start-End" ) );
		return iStatus;
		}

// ---------------------------------------------------------------------------
// COssSendDataOperation::OperationId()
// ---------------------------------------------------------------------------
//
TInt COssSendDataOperation::OperationId() const
		{
		LOGGER ( TXT ( "COssSendDataOperation::OperationId Start-End" ) );
		return iOpId;
		}
// ---------------------------------------------------------------------------
// COssSendDataOperation::NewLC()
// ---------------------------------------------------------------------------
//
 COssSendDataOperation* COssSendDataOperation::NewLC()
	{
	LOGGER ( TXT ( "COssSendDataOperation::NewLC Start-End" ) );
	COssSendDataOperation* self = new ( ELeave )
	COssSendDataOperation();

	CleanupStack::PushL ( self );
	LOGGER ( TXT ( "COssSendDataOperation::NewLC End" ) );
	return self;
	}

// ---------------------------------------------------------------------------
// COssSendDataOperation::CompletedOperation()
// ---------------------------------------------------------------------------
//
 void COssSendDataOperation::CompletedOperation ( TInt aCode )
	{
	LOGGER ( TXT ( "COssSendDataOperation::CompletedOperation Start :id:%d,code:%d" ),
	         iOpId,
	         aCode );

	if ( !iStatus )
		{
		LOGGER ( TXT ( "COssSendDataOperation::CompletedOperation:!!Double Completion!!!" ) );
		return;
		}

	User::RequestComplete ( iStatus, aCode );

	iStatus = NULL;
	}

// ---------------------------------------------------------------------------
// COssSendDataOperation::SetResponse()
// ---------------------------------------------------------------------------
 void COssSendDataOperation::SetResponse ( char* aBuff )
	{
	LOGGER ( TXT ( "CPEngPureDataHandler::SetResponse - id:  %d" ), iOpId );
	delete iData;
	iData = aBuff;
	LOGGER ( TXT ( "COssSendDataOperation::SetResponse End" ) );
	}

// ---------------------------------------------------------------------------
// COssSendDataOperation::Response()
// ---------------------------------------------------------------------------
//
 char* COssSendDataOperation::Response()
	{
	LOGGER ( TXT ( "CPEngPureDataHandler::Response Start" ) );
	char* b = iData;
	iData = NULL;
	LOGGER ( TXT ( "CPEngPureDataHandler::Response End" ) );
	return b;
	}


// End of File
