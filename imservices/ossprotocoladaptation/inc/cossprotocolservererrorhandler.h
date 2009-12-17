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
* Description:  implementation of server error notification handler
*
*/


#ifndef __COssprotocolServerErrorHandler_H__
#define __COssprotocolServerErrorHandler_H__


//  INCLUDES
#include <e32base.h>
#include <ximpbase.h>

#include <presencecachewriter.h>
#include <presencebuddyinfo.h>

// FORWARD DECLARATIONS

class MOSSProtocolConnectionManager;

/**
 * COssprotocolServerErrorHandler
 *
 * Handles network server intiated errors
 *
 */

class COssprotocolServerErrorHandler: public CActive


	{

	public:

		static COssprotocolServerErrorHandler* NewL (
		    MOSSProtocolConnectionManager& aConnMan
		);

		static COssprotocolServerErrorHandler* NewLC (
		    MOSSProtocolConnectionManager& aConnMan
		);

		virtual ~COssprotocolServerErrorHandler();

	private:

		COssprotocolServerErrorHandler ( MOSSProtocolConnectionManager& aConnMan );
		void ConstructL();

	private: // from CActive

		void DoCancel();
		void RunL();
		TInt RunError ( TInt aError );

	public:
        /**
		 * start listening for server intiated error signals
		 */
		void StartListeningL();
        /**
		 * Handles the recieved error signal
		 */
		void ProcessIncomingDataL();

	private: // data

		/**
		 * Send data request to pure data handler generates the id
		 */
		TInt iSendId;

		/**
		 * Oss Protocol Plugin Connection Manager
		 * Not own.  *** Write "Not own" if some other class owns this object.
		 */
		MOSSProtocolConnectionManager& iConnMan;

	};


#endif // __COssprotocolServerErrorHandler_H__

