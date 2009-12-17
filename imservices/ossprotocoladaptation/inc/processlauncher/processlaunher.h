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
* Description:  Offers launching of given process
*
*/



#ifndef __CPROCESSLAUNCHER_H__
#define __CPROCESSLAUNCHER_H__


#include <e32base.h>


/**
*  CProcessLauncher
*  The implementation for launching of  processes
*
*/

class CProcessLauncher : public CActive
	{

	public:  // Constructors and destructor

		/**
		* Two-phased constructor.
		*/
		static CProcessLauncher* NewL ( const TDesC16& aprocessname );

		/**
		* Destructor.
		*/
		~CProcessLauncher();


	public:

		/**
		* Does the launching of given process
		*/
		void LaunchProcessL();


	private:

		/**
		* C++ default constructor.
		* @param aReconnHandler Handler for global reconnect continuation query
		*/
		CProcessLauncher();

		/**
		* By default Symbian 2nd phase constructor is private.
		*/
		void ConstructL ( const TDesC16& aprocessname );


	protected:
		/**
	   	 * @see CActive.
	   	 */
		void DoCancel();

	   /**
		* @see CActive.
		*/
		void RunL();

	   /**
		* @see CActive.
		*/
		TInt RunError ( TInt aError );

	private:  //data
	   /**
		* process launcher
		*/
		RProcess iLauncher;
	   /**
		* name of the process to be launched 
		*/
		HBufC16* iProcessName;
	};

#endif  // __CPROCESSLAUNCHER_H__

// End of File
