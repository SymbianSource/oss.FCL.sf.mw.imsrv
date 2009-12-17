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
* Description:  oss plugin implementation for XIMP Framework
*
*/


#ifndef __COSSPROTOCOLCONNECTION_H__
#define __COSSPROTOCOLCONNECTION_H__

//#include "OSSProtocloLiterals.h"

#include <e32base.h>
#include <e32def.h>
#include <e32std.h>
#include <ximpprotocolconnectionhost.h>
#include <ximpprotocolconnection.h>


// FORWARD DECLARATIONS

class MXIMPServiceInfo;

class MXIMPContextClientInfo;

class MXIMPProtocolConnection;

class COSSProtocolConnectionManager;

class COSSProtocolLogoutRequest;

class COSSProtocolLoginRequest;

class COSSProtocolPresenceFeatures;

class COSSProtocolImFeatures;
class COSSProtocolSearchFeature;
/**
 * COSSProtocolConnection
 *
 * OSS Protocol Connection Object. Protocol Connection Object has connection Manager.
 *
 *
 *
 */

class COSSProtocolConnection :
			public CBase,
			public MXIMPProtocolConnection
	{

	public:

		static COSSProtocolConnection* NewL ( const MXIMPServiceInfo& aServiceInfo,
		                                      const MXIMPContextClientInfo& aClientCtxInfo );


		~COSSProtocolConnection();
		
		
			
		void ReleaseConnectionL();


	private:

		COSSProtocolConnection();


		void ConstructL ( const MXIMPServiceInfo& aServiceInfo,
		                  const MXIMPContextClientInfo& aClientCtxInfo );


	public: // from MXIMPBase

		/**
		 * @see MXIMPProtocolConnection
		 */
		TAny* GetInterface ( TInt32 aInterfaceId,
		                     TIfGetOps  aOptions );
		/**
		 * @see MXIMPProtocolConnection
		 */
		const TAny* GetInterface ( TInt32 aInterfaceId,
		                           TIfGetOps  aOptions ) const;
		/**
		 * @see MXIMPProtocolConnection
		 */
		TInt32 GetInterfaceId() const;
		
	
	public: // from MXIMPProtocolConnection

		/**
		 * @see MXIMPProtocolConnection
		 */
		void PrimeHost ( MXIMPProtocolConnectionHost& aHost );

		/**
		 * @see MXIMPProtocolConnection
		 */		void OpenSessionL ( const MXIMPContextClientInfo& aClientCtxInfo,
		                    TXIMPRequestId aOpId );
        
        /**
		 * @see MXIMPProtocolConnection
		 */
		void OpenSessionL ( const TInt& aSettingsId,
		                    TXIMPRequestId aReqId );
	
		/**
		 * @see MXIMPProtocolConnection
		 */
		void OpenSessionL (
		    const MXIMPContextClientInfo& aContextClient,
		    const TInt& aSettingsId,
		    TXIMPRequestId aReqId );
        
        /**
		 * @see MXIMPProtocolConnection
		 */
		void CloseSession ( const MXIMPContextClientInfo& aClientCtxInfo,
		                    TXIMPRequestId aOpId );
		
		/**
		 * @see MXIMPProtocolConnection
		 */
		void LogoutRequestL(TXIMPRequestId aOpId);
        
        /**
		 * @see MXIMPProtocolConnection
		 */ 
		void ReOpenSessionsL ( TXIMPRequestId aReqId );
        
        /**
		 * @see MXIMPProtocolConnection
		 */
		void GetSupportedFeaturesL ( CDesC8Array& aFeatures ) const;
        
        /**
		 * @see MXIMPProtocolConnection
		 */
		MProtocolPresenceFeatures& ProtocolPresenceFeatures();

        /**
		 * @see MXIMPProtocolConnection
		 */
		TAny* GetProtocolInterface(TInt aInterfaceId);


	private:    // data members
		/**
	     * Connection manager
	     * OWN:
	     */
		COSSProtocolConnectionManager* iConnMan;
		/**
	     * Presence features
	     * OWN:
	     */
		COSSProtocolPresenceFeatures* iPresFeatures;
		/**
		 * Im features
		 * OWN:
		 */
		COSSProtocolImFeatures* iImFeatures;
		/**
		 * Search features
		 * OWN:
		 */
		COSSProtocolSearchFeature*  iSearchFeatures;
		/**
		 * Request id
		 * OWN:
		 */
		TXIMPRequestId iRequestId;
    	/**
		 * Stores connection count
		 * OWN:
		 */
        TInt iConntectionCreated;


	};


#endif // __COSSPROTOCOLCONNECTION_H__
