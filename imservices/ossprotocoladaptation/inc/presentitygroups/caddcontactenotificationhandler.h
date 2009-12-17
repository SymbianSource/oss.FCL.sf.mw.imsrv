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
* Description:  implementation of add notification handler
*
*/


#ifndef __CADDCONTACTNOTIFICATIONHANDLER_H__
#define __CADDCONTACTNOTIFICATIONHANDLER_H__


//  INCLUDES
#include <e32base.h>
#include <ximpbase.h>

#include <presencecachewriter.h>
#include <presencebuddyinfo.h>

// FORWARD DECLARATIONS

class MOSSProtocolConnectionManager;

/**
 * CAddContactNotificationHandler
 *
 * Handles add notifications recieved from the network server
 *
 */

class CAddContactNotificationHandler: public CActive


	{

	public:

		static CAddContactNotificationHandler* NewL (
		    MOSSProtocolConnectionManager& aConnMan
		);

		static CAddContactNotificationHandler* NewLC (
		    MOSSProtocolConnectionManager& aConnMan
		);

		virtual ~CAddContactNotificationHandler();

	private:

		CAddContactNotificationHandler ( MOSSProtocolConnectionManager& aConnMan );
		void ConstructL();

	private: // from CActive

		void DoCancel();
		void RunL();
		TInt RunError ( TInt aError );

	public:
       /**
     	* Start listening for the add notifications
     	*/
		void StartListeningL();
        /**
     	* Process the recieved add notifications
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


#endif // __CADDCONTACTNOTIFICATIONHANDLER_H__

