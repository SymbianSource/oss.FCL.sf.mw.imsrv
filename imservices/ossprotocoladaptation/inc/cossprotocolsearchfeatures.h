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
* Description:  oss search features implementation for XIMP Framework
*
*/


#ifndef __COSSPROTOCOLSEARCHFEATURE_H__
#define __COSSPROTOCOLSEARCHFEATURE_H__

//  INCLUDES
#include <e32base.h>
#include <protocolsearchfeature.h>
#include <protocolsearch.h>
#include "cossprotocolconnectionmanager.h"


class COSSProtocolSearch;

/**
 * COSSProtocolSearchFeature
 * Provides access to subinterface MProtocolSearch 
 * and sets the search data host
 *
 */

class COSSProtocolSearchFeature : public CBase,
								  public MProtocolSearchFeature

	{

	public:

		static COSSProtocolSearchFeature* NewL ( COSSProtocolConnectionManager& aConnMan );


		~COSSProtocolSearchFeature();

	private:

		COSSProtocolSearchFeature(COSSProtocolConnectionManager& aConnMan );


		void ConstructL ( COSSProtocolConnectionManager& aConnMan );

	public: // from MXIMPBase

		TAny* GetInterface ( TInt32 aInterfaceId,
		                     TIfGetOps  aOptions );

		const TAny* GetInterface ( TInt32 aInterfaceId,
		                           TIfGetOps  aOptions ) const;


		TInt32 GetInterfaceId() const;

	public :  	// From MProtocolSearchFeature.for comments,see MProtocolSearchFeature

	   /**
		*  @see MProtocolSearchFeature
		*/
		MProtocolSearch& Search();
	   /**
		*  @see MProtocolSearchFeature
		*/
		void SetHost(MProtocolSearchDataHost& aSearchHost );

	private : //data members
       /**
		* search 
		* owned 
		*/
		COSSProtocolSearch* iSearch;
		
	   /**
	    * connection manager
		* not  owned 
		*/
		COSSProtocolConnectionManager &iConnMan ;
	};

#endif //__COSSPROTOCOLSEARCHFEATURE_H__

// end of file