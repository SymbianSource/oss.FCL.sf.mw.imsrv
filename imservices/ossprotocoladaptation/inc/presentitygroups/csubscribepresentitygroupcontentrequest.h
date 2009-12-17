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
* Description:  Subscribe Presentity Group Content Request
*
*/


#ifndef __CSUBSCRIBEPRESENTITYGROUPCONTENTREQUEST_H__
#define __CSUBSCRIBEPRESENTITYGROUPCONTENTREQUEST_H__


//  INCLUDES
#include <e32base.h>
#include <ximpbase.h>
#include <e32des16.h>
#include "ossprotocloliterals.h"
// FORWARD DECLARATIONS

class MOSSProtocolConnectionManager;

class MXIMPIdentity;

/**
 * CSubscribePresentityGroupContentRequest
 *
 * Fetches the contacts and update to ximp fw
 *
 */

class CSubscribePresentityGroupContentRequest: public CActive


	{

	public:

		static CSubscribePresentityGroupContentRequest* NewL (
		    MOSSProtocolConnectionManager& aConnMan,
		    TXIMPRequestId aRequestId );

		static CSubscribePresentityGroupContentRequest* NewLC (
		    MOSSProtocolConnectionManager& aConnMan,
		    TXIMPRequestId aRequestId );

		virtual ~CSubscribePresentityGroupContentRequest();

	private:

		CSubscribePresentityGroupContentRequest (
		    MOSSProtocolConnectionManager& aConnMan,
		    TXIMPRequestId aRequestId  );
		void ConstructL();
        /**
		 * IssueRequest
		 */
		void IssueRequest();
		/**
		 * populate data
		 */
		void PopulateDataL();
		
	private: // from CActive

		void DoCancel();
		/*
		 * RunL() function also deletes the request object once the activity is done
		 *
		 */
		void RunL();
		TInt RunError ( TInt aError );

	public:
		/**
		 * subscribe to get group members of the list
		 * @param aGroupId group identity
		 */
		void SubscribePresentityGroupContentL (
		    const MXIMPIdentity& aGroupId );
		
	public:
	

		/**
		 * parse the data and update the data cache of ximp.send event back to ximp
		 */

		void ProcessIncomingDataL();

	private: // data

		/**
		 * Request Id from ximpfw
		 */

		TXIMPRequestId iRequestId;

		/**
		 * Send data request to pure data handler generates the id
		 */
		TInt iSendId;
	
		/**
		 * Array of conatcts
		 * Own
		 */
		//RPointerArray<HBufC>                   iContacts;
		/**
		 * Oss Protocol Plugin Connection Manager
		 * Not own.  *** Write "Not own" if some other class owns this object.
		 */
		MOSSProtocolConnectionManager& iConnMan;

		/*
		 * Stores groupname
		 * Own
		 */
		HBufC* iGroupName;
		/*
		 * Listcount
		 */
		TInt iListcount;
	};


#endif // __CSUBSCRIBEPRESENTITYGROUPCONTENTREQUEST_H__

