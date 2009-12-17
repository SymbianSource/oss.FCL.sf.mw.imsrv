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
* Description:  handles synchronisation of contacts 
*
*/


#ifndef __CCONTACTSYNCHANDLER_H__
#define __CCONTACTSYNCHANDLER_H__


//  INCLUDES
#include <e32base.h>
#include <ximpbase.h>

#include <presencecachewriter.h>
#include <presencebuddyinfo.h>

// FORWARD DECLARATIONS

class MOSSProtocolConnectionManager;

/**
 * CContactSyncHandler
 *
 * handles synchronisation of contacts from Network Server
 *
 */

class CContactSyncHandler: public CActive


	{

	public:

		static CContactSyncHandler* NewL ( MOSSProtocolConnectionManager& aConnMan );
	
		virtual ~CContactSyncHandler();

	private:

		CContactSyncHandler ( MOSSProtocolConnectionManager& aConnMan );

	private: // from CActive

		void DoCancel();
		void RunL();
		TInt RunError ( TInt aError );

	public:
        
        /**
		 *  keep on listening for events
		 */
		void StartListening();
         
      	/**
		 *  Processes the data from server and sends to ximpfw
		 */ 
		void ProcessAndSendL();

	private: // data

		/**
		 * Oss Protocol Plugin Connection Manager
		 * Not own. 
		 */
		MOSSProtocolConnectionManager& iConnMan;

	};


#endif // __CCONTACTSYNCHANDLER_H__

