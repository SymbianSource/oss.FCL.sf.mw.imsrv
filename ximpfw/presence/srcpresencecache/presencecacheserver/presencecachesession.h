/*
* Copyright (c) 2007, 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Header file for Presence Cache Server session
*
*/


#ifndef PRESENCECACHESESSION_H
#define PRESENCECACHESESSION_H

// INCLUDE FILES
#include <e32base.h>

#include "presencecachedefs.h"

/**
 * Presence cache server session class.
 * @ingroup ximpprescacheserver
 * @since S60 v3.2
 */
// FORWARD DECLARATIONS
class CPresenceCacheServer;
class MPresenceInfo;
class MPresenceBuddyInfo;
class CPresenceBuddyInfoListImp;
class CPresenceBuddyInfoImp;
class CCacheSessionActiveHelper;
class CPresenceCacheBuddyStore;

//Include Cache server namespace
using namespace NCacheSrv;

class CPresenceCacheSession : public CSession2
    {
    friend class CCacheSessionActiveHelper;
    public: // Constructors and destructors

        /**
        * Two-phased constructor.
        * @param aServer The server.
        * @return Pointer to created CPresenceCacheSession object.
        */
        static CPresenceCacheSession* NewL( CPresenceCacheServer& aServer );

        /**
        * Two-phased constructor.
        * @param aServer The server.
        * @return Pointer to created CPresenceCacheSession object.
        */
        static CPresenceCacheSession* NewLC( CPresenceCacheServer& aServer );

        /**
        * ~CPresenceCacheSession.
        * Destructor.
        */
        virtual ~CPresenceCacheSession();
        
    public: // Functions from base classes

        /**
        * From CSession
        */
        void ServiceL( const RMessage2& aMessage );
        
    public: // own
        
        /**
        * This is called by some other session to inform this session that given
        * buddy's presence has been changed. The informing session first make
        * sure that this session has subscribed for the changes in given buddy.
        *
        *@param pointer to CPresenceBuddyInfoImp, ownership doesnt transfer.
        */
        void NotifyPresenceChangeL(const CPresenceBuddyInfoImp* aPresenceBuddyInfo);    

    private: // Constructors and destructors

        /**
        * C++ default constructor.
        * @param aServer The server.
        */
        CPresenceCacheSession( CPresenceCacheServer& aServer );

        /**
        * Construct.
        * 2nd phase constructor
        */
        void ConstructL();

    private: // New methods

        /**
        * Packs PresenceInfo object into a data packet.
        * @param aPresInfo PresenceInfo object.
        * @return HBufC* data packet.
        */
        HBufC8* PackPresenceInfoLC(const MPresenceInfo& aPresInfo);
        
        /**
        * Cancels the async request, this is called by docancel of active helper
        */
        void Cancel();
        
        /**
        * Tries writing given buddy to presence cache
        * @param aBuddyPresInfo object to write.
        * @return TInt error code
        */
        TInt TryWriteBuddyToCacheL(MPresenceBuddyInfo* aBuddyPresInfo);
        
        /**
        * Packs services array
        * 
        * @param CArrayFixFlat aArray
        * @return packed object
        */
        //HBufC8* PackServicesL(CArrayFixFlat<TUid>* aArray );
        
        /**
        * Removes all subscriptions stored by this session in iSubscribedStores
        */
        void RemoveMySubscriptions();
        
        /**
        * Notify to subscribers in given buddy store's presence change. This method
        * goes through all subscribed sessions and call their NotifyPresenceChangeL
        * methods. Ownership of store is not transferred.
        * 
        * @param aBuddyStore pointer to changed CPresenceCacheBuddyStore
        */
        void NotifyAllSubscribersL(CPresenceCacheBuddyStore* aBuddyStore);
        
        /**
        * Pack buddy's presence info into descriptor.
        * 
        * @param aBuddyPresInfo buddy's presence info, ownership doesnt transfer
        * @param HBufC8* packed presence info
        */
        HBufC8* PackBuddyPresenceInfoLC(
                                    const CPresenceBuddyInfoImp* aBuddyPresInfo);
        
    
     private: // New Massage processors, these are called to process messages.
        void HandlePrepReadPresenceInfoSyncL(const RMessage2& aMessage );
        
        void HandleWritePresenceInfoSyncL(const RMessage2& aMessage ); 
        
        void HandleGetLastPreparedPacketL( const RMessage2& aMessage );
        
        void HandleGetLastPreparedAsyncPacketL( const RMessage2& aMessage );
        
        void HandleBuddyCountInAllServices(const RMessage2& aMessage ); 
        
        void HandleBuddyCountInService(const RMessage2& aMessage );
        
        void HandleWritePresenceInfoAsyncL(const RMessage2& aMessage );
        
        void HandlePrepReadAllBuddiesPresenceInService(const RMessage2& aMessage );
        
        //void HandleGetAllServicesL(const RMessage2& aMessage );
        
        void HandleGetServiceCount(const RMessage2& aMessage );
        
        void HandleDeleteService(const RMessage2& aMessage );
        
        void HandleCancel(const RMessage2& aMessage );
        
        void HandleDeletePresence(const RMessage2& aMessage );
        
        
        // subscribe notification related
        void HandleSubscribeBuddyPresenceChange(const RMessage2& aMessage );
        
        void HandleUnSubscribeBuddyPresenceChange(const RMessage2& aMessage );
        
        void HandleGetLastNotifiedtPacketL(const RMessage2& aMessage );
        
        void HandleWaitingForNotification(const RMessage2& aMessage );
        
        void HandleCancelWaitingForNotification(const RMessage2& aMessage );
        
    
    private:            
        
        /**
        * Writes Presence info async. to cache, its called on each runl cycle
        * and it takes data to write from member data holders.
        */
        void WritePresenceInfoAsyncL();
        
        /**
        * Reads all buddies presence info in given service. It takes data from 
        * stored message.
        */
        void ReadAllBuddiesPresenceInServiceL();
        
        /**
         * Get Service name from given xsp id
         * 
         * @param aXspId xsp id e.g. ovi:xyz@nokia.com
         * @return ServiceName returned here
         */
        TPtrC GetServiceName(const TDesC& aXspId);
        
        
    private: // Data

        /**
        * iMessage, the message exchange data with the server.
        */
        RMessage2 iMessage;
        
        /**
        * iMessage, the message holder for notification wating.
        * This is always pending when some client subscribe for notifications.
        */
        RMessage2 iMessageForNoti;

        /**
        * iServer, reference to the server.
        */
        CPresenceCacheServer& iServer;
        
        /**
        * Own: used for sync messages
        */
        HBufC8* iDataPack;
        
        /**
        * Own: used for async messages
        */
        HBufC8* iDataPackAsync;
        
        /**
        * Own: used for subscribe notify message
        */
        HBufC8* iDataPackNotifier;
        
        /**
        * Own: used for ansync requests
        */
        NRequest::TOpAsyncCodes iAsyncReq;
        
        /**
        *Own
        */
        CPresenceBuddyInfoListImp* iBuddypresInfoList;
        
        /**
        *
        */
        TInt iLastServiceCount;
        
        
        /**
        *Own
        */
        CCacheSessionActiveHelper* iActiveHelper;
        
        /**
        * Pointers not owned.
        */
        RPointerArray<CPresenceCacheBuddyStore> iSubscribedStores;
        
    };

/**
* This class is used by CPresenceCacheSession for dividing long running async.
* tasks into smaller units. The CPresenceCacheSession itself was not made 
* active, since that results in c++ ambiguousness problems in CPresenceCacheSession
* because of inheriting twice from CBase.
*  
* @since S60 v3.2
*/    
class CCacheSessionActiveHelper : public CActive
	{
	public: // public functions
	
	    /**
        * Default 1st phase factory method.
        * Creates an instance of CCacheSessionActiveHelper
        *
        * @return created instance of the CCacheSessionActiveHelper
        */
        static CCacheSessionActiveHelper* NewL(CPresenceCacheSession* aSession );
        
        /**
        * Destructor
        */
        ~CCacheSessionActiveHelper( );
        
        /**
        * Active object start
        */
		void Start();
	
	private: // private functions
        
        /**
        * Constructor
        */
        CCacheSessionActiveHelper(CPresenceCacheSession* aSession);

        /**
        * Active object RunL
        */
		void RunL();
		
        /**
        * Active object DoCancel
        */
		void DoCancel();
		
        /**
        * ConstructL
        */
		void ConstructL();
		
		
        /**
        * pointer to CPresenceCacheSession doesnt own
        */
		CPresenceCacheSession* iCacheSession;
			
	};
    
#endif // PRESENCECACHESESSION_H

// End of File

