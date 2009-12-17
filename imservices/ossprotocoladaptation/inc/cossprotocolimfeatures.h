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
* Description:  oss presence features implementation for XIMP Framework
*
*/


#ifndef __COSSPROTOCOLIMFEATURES_H__
#define __COSSPROTOCOLIMFEATURES_H__

//  INCLUDES
#include <e32base.h>
#include <cprotocolimfeatures.h>
//#include <protocolimgroup.h>
#include <protocolimconversation.h>
#include <protocolpresentitygroups.h>
//#include <protocoliminvitation.h>
//#include <protocolimsearch.h>
#include "cossprotocolconnectionmanager.h"

class COSSProtocolImConversation;
/**
 * COSSProtocolImFeatures
 *
 * OSS Protocol Connection Object. Protocol Connection Object has connection Manager.
 *
 */

class COSSProtocolImFeatures :
			public CProtocolImFeatures
	{

	public:

		static COSSProtocolImFeatures* NewL ( COSSProtocolConnectionManager& aConnMan );


		~COSSProtocolImFeatures();

	private:

		COSSProtocolImFeatures(COSSProtocolConnectionManager& aConnMan );


		void ConstructL ( COSSProtocolConnectionManager& aConnMan );

	public: // from MXIMPBase

		TAny* GetInterface ( TInt32 aInterfaceId,
		                     TIfGetOps  aOptions );

		const TAny* GetInterface ( TInt32 aInterfaceId,
		                           TIfGetOps  aOptions ) const;


		TInt32 GetInterfaceId() const;

	public :// From MProtocolImFeatures

		/**
		 * @see MProtocolImFeatures
		 */
		MProtocolImGroup& ImGroup();
		/**
		 * @see MProtocolImFeatures
		 */
		MProtocolImConversation& ImConversation();
		/**
		 * @see MProtocolImFeatures
		 */
		/**
		 * @see MProtocolImFeatures
		 */
		MProtocolImInvitation& ImInvitation();
		/**
		 * @see MProtocolImFeatures
		 */
		MProtocolImSearch& ImSearch();
		/**
		 * @see MProtocolImFeatures
		 */
		void SetHost(MProtocolImDataHost& aHost );
		
	    TInt SupportedSubInterfaces() const;

	private : //data members
		/**
		* im conversation
		* Own:
		*/
		COSSProtocolImConversation* iImConversation;

		/**
		* Protocol im data hodt
		* Not own:
		*/
		MProtocolImDataHost *iHost ; 
		
		/**
	     * Connection manager
	     * Not own:
	     */
		COSSProtocolConnectionManager &iConnMan ;
	};

#endif //__COSSPROTOCOLIMFEATURES_H__

// end of file