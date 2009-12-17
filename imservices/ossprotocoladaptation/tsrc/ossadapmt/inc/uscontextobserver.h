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
* Description: uscontextobserver.h
*
*/


#ifndef USCONTEXTOBSERVER_H__
#define USCONTEXTOBSERVER_H__


// INCLUDES
#include <e32base.h>
#include <ximpcontextobserver.h>

_LIT( KAddContactFileName, "c:\\add_contact.txt" );

// CLASS DESCRIPTION

/**
 * Presence context observer for usage scenario tests.
 */

class CUSContextObserver : public CBase,
			public MXIMPContextObserver
	{

	public:
		static CUSContextObserver* CUSContextObserver::NewLC();
		~CUSContextObserver();

	private:
		CUSContextObserver();


	public:

		/**
		 * Method to wait with CActiveSchedulerWait
		 * the given request completion. If request
		 * is completed with error, leaves with failure code.
		 *
		 * NOTE! Only one request can be waited at time.
		 *
		 * @param aReqToWait The request to wait.
		 */
		void WaitOpToCompleteL ( const TXIMPRequestId& aReqToWait );



	private:  //From MXIMPContextObserver

		void HandlePresenceContextEvent ( const MXIMPContext& aContext,
		                                  const MXIMPBase& aEvent );


	private:  //Data

		//OWN: Active scheduler wait for waiting the completion
		CActiveSchedulerWait    iWait;

		//OWN: Request ID identifying request to wait
		TXIMPRequestId    iReqToWait;

		//OWN: Result code from waited request
		TInt    iReqResult;
		TBuf<50>  gid[10];
		TInt   gidcount;

	};



#endif //USCONTEXTOBSERVER_H__


