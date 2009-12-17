/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Header for Waittimer.h.
*
*/

#ifndef WAITTIMER_H
#define WAITTIMER_H

#include <e32base.h> // For CActive, link against: euser.lib
#include <e32std.h>  // For RTimer, link against: euser.lib
#include <e32property.h>
// FORWARD DECLARATIONS

class COssSendDataOperation;
class COSSProtocolConnectionManager;
class MOSSProtocolConnectionManager;
class MXIMPProtocolConnectionHost;

enum TDataFetchSteps
	{
	EDataFetchingStep1 = -1, // three	
	EDataFetchingStep2 ,	 // -1
//	EDataFetchingStep3,		//  0
	EDataFetchComplete		// 1 done
	};

/**
 * CWaitTimer implementation.
 * Responsible for sending filled message queue and
 * reading response message queue when it is updated
 * keep track of updation of message queue
 */
class CWaitTimer : public CActive
	{

	public:
		// Cancel and destroy
		~CWaitTimer();

		// Two-phased constructor.
		static CWaitTimer* NewL (MOSSProtocolConnectionManager& aConnMan);


	public: // New functions
		/**
		 *  Function for making the initial request
		 */
		TInt SendDataL ( TRequestStatus& aStatus, char* msg, TInt nBytes );
        /**
		 *  Get response data based on the transaction id
		 */
		char* ResponseL ( TInt aTransId );
		/**
		 *  start listening on the queue to keep track of the queue updation
		 */
		void StartListeningL();
		/**
		 *  Increase operation id
		 */
		void IncreaseOpId();
		/**
		 *  Get operation id
		 */
		TInt GetOpId();
		/**
		 *  Listen Incoming data
		 */

		void ListenIncomingData ( TRequestStatus& aStatus );

		/**
		 *  Listen Incoming data count
		 */

		TInt IncomingDataCount();
		/**
		 *  Returns searched data count
		 */	
		TInt SearchDataCount();
		
		/**
		 *  Returns ContactsChange Response Count
		 */	
		TInt ContactsChangeResponseCount();
		
		/** 
		 *Listen Incoming message
     	 */
		TInt ListenIncomingMsg ( TRequestStatus& aStatus );
		/**
		 *  Cancel incoming data listening
		 */
		void CancelListening();

		/**
		 *  Listen Incoming message listening
		 */
		void CancelListeningMsg();
		/**
		 * returns fetchingcontinue flag
		 */
        TBool IsFetchingContinue();

		/**
		 *  Listen Incoming Presence notifications
         */
		TInt ListenIncomingPresence ( TRequestStatus& aStatus );
		/**
		 *  Cancel Incoming presence listening
		 */
		void CancelListeningPres();
		/**
		 *  Listen Incoming Added contact notifications
         */
		TInt ListenAddNotification ( TRequestStatus& aStatus );
		/**
		 *  Cancel listening Incoming Added contact notifications
		 */
		void CancelListeningAddNotication();
		/**
		 *  Listen Incoming network server Error notifications
         */
		TInt ListenIncomingServerError ( TRequestStatus& aStatus );
		/**
		 *  Cancel Incoming server error listening
		 */
		void CancelListeningServerErrors();
		
		/**
		 *  issue the releasing reuest and exit
		 */
		void IssueReleaseRequestL();
		
		/**
		 *  return ETrue if server disconnect has happen
		 */
		TBool IsServerDisconnect();
		/**
		 *  Listen any contacts change events
         */
		void ListenContactsChange( TRequestStatus& aStatus );
		
		/**
		 *  Cancel any contacts change events listening
		 */
		void CancelContactsChangeListening();
		/**
		 *  ETrue.if fetching contacts is completed
		 */
		TBool IsFetchContactsCompleted();
		
	private:
		/**
		 *  C++ constructor
		 */
		CWaitTimer ( MOSSProtocolConnectionManager& aConnMan );

		/**
		 *  Second-phase constructor
		 */
		void ConstructL();

	private: // From CActive
	
		/**
		 *  Handles recieved message queue data.
		 */
		void RunL();

		/**
		 *  How to cancel me
		 */
		void DoCancel();
		/**
		 * Override to handle leaves from RunL(). Default implementation causes
		 * the active scheduler to panic.
		 */
		TInt RunError ( TInt aError );

	private: // new private functions

		/**
		 *  Find operationl
		 *
		 *  @return index in array
		 */
		TInt FindOperation ( TInt aOpId, TInt ( COssSendDataOperation:: *aIdFunc ) () const ) const;
		TInt FindOperationL ( TInt aOpId, TInt ( COssSendDataOperation:: *aIdFunc ) () const ) const;
		/**
		 * set presence as pending into the presence cache
		 * for the remote pending contacts
		 * @param armsg: message to parse to get remote contacts
		 */
		void PendingPresenceContactsL(char* aRmessage);      
	private:
	    /**
		 *  State of the active object
		 */
		TInt iState;  
		/**
		 *  Request status
		 */
		TRequestStatus*             iStatus1;
		/**
		 *  Send data operations
		 * Own
		 * Elements OWNed
		 */
		RPointerArray<COssSendDataOperation>   iOperations;
		/**
		 *  Logs Id iteration
		 */
		TInt                                    iOpidIterator;
		/**
		 *  Id iteration
		 */
		TInt                                    iOpId;

		/**
		 *  Max number of active requests
		 */
		TInt                                    iMaxActive;

		/**
		 *  Incoming data queue
		 *  OWN
		 */
		RPointerArray<char>                   iIncomingData;
		/**
		 *  Incoming message queue
		 *  OWN
		 */
		RPointerArray<char>                   iIncomingMsg;
		/**
		 *  Incoming presence information queue
		 *  OWN
		 */
		RPointerArray<char>                   iIncomingPres;
		/**
		 *  Incoming server error queue
		 *  OWN
		 */
		RPointerArray<char>                   iIncomingServerError;
		/**
		 *  Incoming add notifications queue
		 *  OWN
		 */
		RPointerArray<char>                   iAddNotification;
		/**
		 *  Incoming search elements queue
		 *  OWN
		 */
		RPointerArray<char>                   iSearchElements;
		/**
		 *  Incoming conatct change queue
		 *  OWN
		 */
		RPointerArray<char>                   iContactChangeList;
		/**
		 *  data Request Status
		 *  OWN
		 */
		TRequestStatus*       iIncReqStatus;
		/**
		 *   Message Request Status
		 *  OWN
		 */
		TRequestStatus*       iIncMsgReqStatus;
		/**
		 *  Presence Request Status
		 *  OWN
		 */
		TRequestStatus*       iIncPresReqStatus;
		/**
		 *  Error Request Status
		 *  OWN
		 */
		TRequestStatus*       iIncErrorReqStatus;
		/**
		 *  Add Request Status
		 *  OWN
		 */
		TRequestStatus*       iIncAddReqStatus;
		/**
		 *  Contacts Change Request Status
		 *  OWN
		 */
		TRequestStatus*       iContactsChangeStatus;
		
		/**
		 *  Id which is used to do logs more human readable
		 *  OWN
		 */
		TInt                                    iConnectionLogsId;
		
	    
        /**
		 *  flag for checking fetching is done
		 */
	    TBool                                iFetchingContinue;	
	    
	    /**
		 *  connection manager
		 */
		MOSSProtocolConnectionManager& iConnMan;
		/**
		 *  Flag to denote whether Msg Queue was created
		 * this will help us in reusing the created msgqueue
		 */
		TBool 									iResponseMsgQCreated ;
		/**
		 *  ETrue if server disconnect has happen 
		 */
		TBool iServerDisconnected;
		/**
		 *  timer to trigger message queue uptation checking
		 */
		RTimer iTimer;
		/**
		 *  stores fetching steps
		 */ 
		TInt iFetchingStep;
	};

#endif // WAITTIMER_H
