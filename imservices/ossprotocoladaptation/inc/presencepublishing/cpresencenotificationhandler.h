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
* Description:  implementation of presence notification handler
*
*/


#ifndef __CPRESENCENOTIFICATIONHANDLER_H__
#define __CPRESENCENOTIFICATIONHANDLER_H__


//  INCLUDES
#include <e32base.h>
#include <ximpbase.h>

#include <presencecachewriter2.h>
#include <mpresencebuddyinfo2.h>

// FORWARD DECLARATIONS

class MOSSProtocolConnectionManager;

/**
 * CPresenceNotificationHandler
 *
 * Handles presnce notifications recieved from the server
 * and updates presence cache 
 */

class CPresenceNotificationHandler: public CActive


	{

	public:

		static CPresenceNotificationHandler* NewL (
		    MOSSProtocolConnectionManager& aConnMan
		);

		static CPresenceNotificationHandler* NewLC (
		    MOSSProtocolConnectionManager& aConnMan
		);

		virtual ~CPresenceNotificationHandler();

	private:

		CPresenceNotificationHandler ( MOSSProtocolConnectionManager& aConnMan );
		void ConstructL();

	private: // from CActive

		void DoCancel();
		void RunL();
		TInt RunError ( TInt aError );

	public:
        /**
		 * Start listening presence from the server
		 */
		void StartListeningL();
        /**
		 * Process the recieved presence from the server
		 */
		void ProcessIncomingDataL();
		
	private: // data

		/**
		 * Send data request to pure data handler generates the id
		 */
		TInt iSendId;
        /**
		 * Presence cache writer
		 * Own
		 */
		MPresenceCacheWriter2* iPresenceCacheWriter;

		/**
		 * Oss Protocol Plugin Connection Manager
		 * Not own.  *** Write "Not own" if some other class owns this object.
		 */
		MOSSProtocolConnectionManager& iConnMan;
		
	};


#endif // __CPRESENCENOTIFICATIONHANDLER_H__

