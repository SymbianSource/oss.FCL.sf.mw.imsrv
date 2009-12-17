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
* Description:  Implementation for handling presence notification
 *
*/


#include <ximpprotocolconnectionhost.h>
#include "cpresencenotificationhandler.h"
#include "mossprotocolconnectionmanager.h"
#include "ossprotocolpluginlogger.h"
#include "waittimer.h"
#include "cossprotocolconnectionmanager.h"

#include <e32des16.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "msgliterals.h"

#include "ossprotocoladaptationuids.h"
#include "ossprotocoladaptutils.h"

#include<avabilitytext.h>


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CPresenceNotificationHandler::CPresenceNotificationHandler
// ---------------------------------------------------------------------------
//
CPresenceNotificationHandler::CPresenceNotificationHandler (
        MOSSProtocolConnectionManager& aConnMan ) :
        CActive ( EPriorityNormal ),
        iConnMan ( aConnMan )
    {
    LOGGER ( TXT ( "CPresenceNotificationHandler::CPresenceNotificationHandler Start" ) );
    CActiveScheduler::Add ( this );
    LOGGER ( TXT ( "CPresenceNotificationHandler::CPresenceNotificationHandler End" ) );
    }


// ---------------------------------------------------------------------------
// CPresenceNotificationHandler::ConstructL
// ---------------------------------------------------------------------------
//
void CPresenceNotificationHandler::ConstructL()
    {
    LOGGER ( TXT ( "CPresenceNotificationHandler::ConstructL Start-End" ) );
    iPresenceCacheWriter = MPresenceCacheWriter2::CreateWriterL();

    }


// ---------------------------------------------------------------------------
// CPresenceNotificationHandler::NewL
// ---------------------------------------------------------------------------
//
CPresenceNotificationHandler* CPresenceNotificationHandler::NewL (
        MOSSProtocolConnectionManager& aConnMan )
    {
    LOGGER ( TXT ( "CPresenceNotificationHandler::NewL Start" ) );

    CPresenceNotificationHandler* self = new ( ELeave ) CPresenceNotificationHandler ( aConnMan );
    CleanupStack::PushL ( self );
    self->ConstructL();
    CleanupStack::Pop ( self );

    LOGGER ( TXT ( "CPresenceNotificationHandler::NewL End" ) );
    return self;
    }


// ---------------------------------------------------------------------------
// CPresenceNotificationHandler::NewLC
// ---------------------------------------------------------------------------
//
CPresenceNotificationHandler* CPresenceNotificationHandler::NewLC (
        MOSSProtocolConnectionManager& aConnMan )
    {
    LOGGER ( TXT ( "CPresenceNotificationHandler::NewLC Start" ) );

    CPresenceNotificationHandler* self = CPresenceNotificationHandler::NewL ( aConnMan );
    CleanupStack::PushL ( self );

    LOGGER ( TXT ( "CPresenceNotificationHandler::NewLC End" ) );
    return self;
    }

// ---------------------------------------------------------------------------
// CPresenceNotificationHandler::~CPresenceNotificationHandler
// ---------------------------------------------------------------------------
//
CPresenceNotificationHandler::~CPresenceNotificationHandler()
    {
    LOGGER ( TXT ( "::~CPresenceNotificationHandler Start" ) );

    Cancel();
    //
    if ( iPresenceCacheWriter )
        {
        iPresenceCacheWriter->DeleteService( iConnMan.ServiceName() );
        delete iPresenceCacheWriter ;
        }
    LOGGER ( TXT ( "::~CPresenceNotificationHandler End" ) );
    }

// ---------------------------------------------------------------------------
// CPresenceNotificationHandler::DoCancel()
// ---------------------------------------------------------------------------
//
void CPresenceNotificationHandler::DoCancel()
    {
    LOGGER ( TXT ( "CPresenceNotificationHandler::DoCancel Start" ) );

    iConnMan.DataHandler().CancelListeningPres();

    LOGGER ( TXT ( "CPresenceNotificationHandler::DoCancel End" ) );
    }

// ---------------------------------------------------------------------------
// CPresenceNotificationHandler::RunL()
// ---------------------------------------------------------------------------
//
void CPresenceNotificationHandler::RunL()
    {
    LOGGER ( TXT ( "CPresenceNotificationHandler::RunL Start" ) );

    // something is coming from the xmpp server
    User::LeaveIfError ( iStatus.Int() );
    ProcessIncomingDataL();
    StartListeningL();

    LOGGER ( TXT ( "CPresenceNotificationHandler::RunL End" ) );
    }

// ---------------------------------------------------------------------------
// CPresenceNotificationHandler::ProcessIncomingDataL()
// ---------------------------------------------------------------------------
/* This Function is used to convert the received 
 *  presence notification from Isolation Server Message queue 
 *  into the ximpfw data types. and storing the presence information
 *  in to the presence cache ( available in ximpfw ) 
 *  client has to read the presence information from the 
 *  presence cache. when the change in status notification is received
 *  while updating presence cache, client will receive the notification if subscribed.
 */
void CPresenceNotificationHandler::ProcessIncomingDataL()
    {	
    LOGGER ( TXT ( "CPresenceNotificationHandler::ProcessIncomingDataL Start" ) );

    char* pResponse = NULL, *pOrigResponse = NULL;  
    pOrigResponse = pResponse = iConnMan.DataHandler().ResponseL ( 2 );// 2 is to differentiate presence notification from server initiated request
    CleanupStack::PushL(pOrigResponse) ; 	
    MPresenceBuddyInfo2* buddyPresInfo = MPresenceBuddyInfo2::NewLC();

    // pResponse contians "<MsgHdr>ContactId/0AvailabilityStatus/0StatusMessage".
    pResponse += sizeof ( message_hdr_resp ); // Skipping Message Header

    ///////// Geting Contact-id from message queue
    char* contactid = pResponse; // contactid
    HBufC16 *contactName = OssProtocolAdapUtils::ConvertCharToTUint16LC( contactid );   
    HBufC* name = HBufC::NewLC( contactName->Length() + iConnMan.ServiceName().Length() + KColon().Length() );
    TPtr namePtr( name->Des() );
    namePtr.Zero();
    namePtr.Append(iConnMan.ServiceName() ); // prepend service name
    namePtr.Append(KColon);
    namePtr.Append(contactName->Des() );
    buddyPresInfo->SetIdentityL(namePtr);
    LOGGER ( TXT ( "CPresenceNotificationHandler::ProcessIncomingDataL  :ContactName:%S " ), contactName );	
    CleanupStack::PopAndDestroy();//name
    CleanupStack::PopAndDestroy();//contactName

    ///////// End Getting Contact-id 

    int toklength = strlen(pResponse) + 1 ; // finding length of contactid + '/0' 
    pResponse += toklength;	  // skipping the contactid

    ///////// Getting availibility text
    char* availability = pResponse;	  // availability text
    HBufC16 *message = OssProtocolAdapUtils::ConvertCharToTUint16LC( availability );	    
    switch (*(pResponse))
        {
        case 'd': //compares the first char of "dnd"
            {
            buddyPresInfo->SetAvailabilityL( MPresenceBuddyInfo2::EBusy,KDndState); 
            break;
	        }
        case 'b':
            {
            buddyPresInfo->SetAvailabilityL( MPresenceBuddyInfo2::EBusy,*message); 
            break;
            }
        case 'o':  //compares the first char of "offline"
            {
            buddyPresInfo->SetAvailabilityL( MPresenceBuddyInfo2::ENotAvailable,*message);            
            break;
            }
        case 'a':  ////compares the first char of "away" and "available"
            {
            if ('v' == *(pResponse + 1))
                {
                buddyPresInfo->SetAvailabilityL( MPresenceBuddyInfo2::EAvailable,*message);                 
                } 
            else 
                {
                // EAway  - is not available in  presence cache
                buddyPresInfo->SetAvailabilityL( MPresenceBuddyInfo2::EBusy,*message);              	              
                }
            break;
            }
        case 'x':  
            {
            buddyPresInfo->SetAvailabilityL( MPresenceBuddyInfo2::EBusy,KAwayState ); 
            break;
            }
        case 'h':  
            {
            buddyPresInfo->SetAvailabilityL( MPresenceBuddyInfo2::EUnknownAvailability,KInvisibleState ); 
            break;
            }
        default:
            buddyPresInfo->SetAvailabilityL( MPresenceBuddyInfo2::EUnknownAvailability,*message);
            break;
        }
    CleanupStack::PopAndDestroy( message );
    ///////// End getting availability message

    toklength = strlen(pResponse) + 1; // finding length of availability text + '/0'
    pResponse += toklength;		// skipping availability text 

    ///////// Getting status message if exists
    if(toklength >1)
        {
        char* statustext = pResponse;		
        HBufC16 *statusmessage = OssProtocolAdapUtils::ConvertCharToTUint16LC( statustext );
        buddyPresInfo->SetStatusMessageL(*statusmessage);
        CleanupStack::PopAndDestroy( statusmessage );
        }	
    ///////// End Getting status message

    // Writing into Presence Cache
    TInt cacheerror = iPresenceCacheWriter->WritePresenceL(buddyPresInfo);
    User::LeaveIfError ( cacheerror);
    // End
    CleanupStack::PopAndDestroy ( 1 ); //buddyPresInfo	
    CleanupStack::PopAndDestroy(pOrigResponse) ;//pOrigResponse
    LOGGER ( TXT ( "CPresenceNotificationHandler::ProcessIncomingDataL End" ) );
    }


// ---------------------------------------------------------------------------
// CPresenceNotificationHandler::RunError
// ---------------------------------------------------------------------------
//
TInt CPresenceNotificationHandler::RunError ( TInt  aError )
    {
    LOGGER ( TXT ( "CPresenceNotificationHandler::RunError Start %d" ), aError );

    LOGGER ( TXT ( "CPresenceNotificationHandler::RunError End" ) );
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// CPresenceNotificationHandler::StartListeningL
// ---------------------------------------------------------------------------
//
void CPresenceNotificationHandler::StartListeningL()
    {
    LOGGER ( TXT ( "CPresenceNotificationHandler::StartListeningL Start" ) );

    if ( ! ( this->IsActive() ) )
        {
        iConnMan.DataHandler().ListenIncomingPresence ( iStatus );
        SetActive();
        }
    LOGGER ( TXT ( "CPresenceNotificationHandler::StartListeningL End" ) );
    }

// End of file
