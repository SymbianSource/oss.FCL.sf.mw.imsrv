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


#ifndef __COSSPROTOCOLPRESENCERFEATURES_H__
#define __COSSPROTOCOLPRESENCERFEATURES_H__

//  INCLUDES
#include <e32base.h>
#include <protocolpresencefeatures.h>
#include <protocolpresencewatching.h>
#include <protocolpresencepublishing.h>
#include <protocolpresentitygroups.h>
#include <protocolpresenceauthorization.h>
#include "cossprotocolconnectionmanager.h"
class COSSProtocolPresentityGroups;
class COSSProtocolpresentitygroups;
class COssProtocolPresencePublishing;
class COssProtocolPresenceAuthorization;
/**
 * COSSProtocolPresenceFeatures
 *
 * COSSProtocolPresenceFeatures provide
 * access following feature specific sub-interfaces:
 * - MProtocolPresenceWatching
 * - MProtocolPresencePublishing
 * - MProtocolPresentityGroups
 * - MProtocolPresenceAuthorization
 *
 */
class COSSProtocolPresenceFeatures :
                   public CBase,
                   public MProtocolPresenceFeatures
    {
    	
    public:
    
    	static COSSProtocolPresenceFeatures* NewL( COSSProtocolConnectionManager& aConnMan );


    	~COSSProtocolPresenceFeatures();

	private:

    	COSSProtocolPresenceFeatures();


    	void ConstructL( COSSProtocolConnectionManager& aConnMan );
    
    public: // from MXIMPBase
        /**
		 * @see MXIMPBase
		 */
    	TAny* GetInterface( TInt32 aInterfaceId,
                        TIfGetOps  aOptions );
        /**
		 * @see MXIMPBase
		 */
    	const TAny* GetInterface( TInt32 aInterfaceId,
                              TIfGetOps  aOptions ) const;

        /**
		 * @see MXIMPBase
		 */
    	TInt32 GetInterfaceId() const;
    
    public : // From MProtocolPresenceFeatures
    
	    /**
		 * @see MProtocolPresenceFeatures
		 */
	    MProtocolPresenceWatching& PresenceWatching();
	    /**
		 * @see MProtocolPresenceFeatures
		 */
	    MProtocolPresencePublishing& PresencePublishing();
	    /**
		 * @see MProtocolPresenceFeatures
		 */
	    MProtocolPresentityGroups& PresentityGroups();
	    /**
		 * @see MProtocolPresenceFeatures
		 */
	    MProtocolPresenceAuthorization& PresenceAuthorization();
    
    private : //data members
	   	 /**
	     * presentity group
	     * Own 
	     */   
	    COSSProtocolpresentitygroups*	iPresentityGroups;
	   	 /**
	     * presence publishing
	     * Own 
	     */  
	   	COssProtocolPresencePublishing* iPresencePublishing;
	  	 /**
	     * presence authorisation
	     * Own 
	     */  
	  	COssProtocolPresenceAuthorization* iAuthrozation;

		};

#endif //__COSSPROTOCOLPRESENCERFEATURES_H__

// end of file