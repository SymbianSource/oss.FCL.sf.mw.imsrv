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
* Description:  handles synchronisation of contacts
*
*/


#include <ximpprotocolconnectionhost.h>

#include <ximpobjectfactory.h>
#include <protocolpresentitygroupsdatahost.h>
#include <presentitygroupinfo.h>
#include <presentitygroupmemberinfo.h>
#include <ximpidentity.h>
#include <protocolpresencedatahost.h>
#include <presenceobjectfactory.h>

#include <ximpcontext.h>

#include <devicepresenceinfo.h>

#include <e32des16.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "msgliterals.h"

#include "ccontactsynchandler.h"

#include "mossprotocolconnectionmanager.h"
#include "ossprotocolpluginlogger.h"
#include "waittimer.h"
#include "cossprotocolconnectionmanager.h"
#include "ossprotocoladaptationuids.h"
#include "ossprotocoladaptutils.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CContactSyncHandler::CContactSyncHandler
// ---------------------------------------------------------------------------
//
CContactSyncHandler::CContactSyncHandler (
    MOSSProtocolConnectionManager& aConnMan ) :
		CActive ( EPriorityNormal ),
		iConnMan ( aConnMan )
	{
	LOGGER ( TXT ( "CContactSyncHandler::CContactSyncHandler Start" ) );
	CActiveScheduler::Add ( this );

	LOGGER ( TXT ( "CContactSyncHandler::CContactSyncHandler End" ) );
	}


// ---------------------------------------------------------------------------
// CContactSyncHandler::NewL
// ---------------------------------------------------------------------------
//
CContactSyncHandler* CContactSyncHandler::NewL (
    MOSSProtocolConnectionManager& aConnMan )
	{
	LOGGER ( TXT ( "CContactSyncHandler::NewL Start" ) );

	CContactSyncHandler* self = new ( ELeave ) CContactSyncHandler ( aConnMan );

	LOGGER ( TXT ( "CContactSyncHandler::NewL End" ) );
	return self;
	}


// ---------------------------------------------------------------------------
// CContactSyncHandler::~CContactSyncHandler
// ---------------------------------------------------------------------------
//
CContactSyncHandler::~CContactSyncHandler()
	{
	LOGGER ( TXT ( "::~CContactSyncHandler Start" ) );

	Cancel();

	LOGGER ( TXT ( "::~CContactSyncHandler End" ) );
	}


// ---------------------------------------------------------------------------
// CContactSyncHandler::DoCancel()
// ---------------------------------------------------------------------------
//
void CContactSyncHandler::DoCancel()
	{
	LOGGER ( TXT ( "CContactSyncHandler::DoCancel Start" ) );

	iConnMan.DataHandler().CancelContactsChangeListening();

	LOGGER ( TXT ( "CContactSyncHandler::DoCancel End" ) );
	}

// ---------------------------------------------------------------------------
// CContactSyncHandler::RunL()
// ---------------------------------------------------------------------------
//
void CContactSyncHandler::RunL()
	{
	LOGGER ( TXT ( "CContactSyncHandler::RunL Start" ) );

	// something is coming from the xmpp server
	User::LeaveIfError ( iStatus.Int() );

	ProcessAndSendL();
	StartListening();

	LOGGER ( TXT ( "CContactSyncHandler::RunL End" ) );
	}

// ---------------------------------------------------------------------------
// CContactSyncHandler::ProcessAndSendL()
// ---------------------------------------------------------------------------
	
void CContactSyncHandler::ProcessAndSendL()
	{	
	LOGGER ( TXT ( "CContactSyncHandler::ProcessIncomingDataL Start" ) );
    char* pResponse = NULL, *pOrigResponse = NULL;  
    message_hdr_resp* msg_struct = NULL;
    
    while( iConnMan.DataHandler().ContactsChangeResponseCount() ) // process all responses
    	{
    	pOrigResponse = pResponse = iConnMan.DataHandler().ResponseL (200 );
		CleanupStack::PushL(pOrigResponse) ;
	
	 	msg_struct = ( message_hdr_resp* )pResponse;
	 	
		char* contact= pResponse + sizeof ( message_hdr_resp );
		HBufC16* contactName = OssProtocolAdapUtils::ConvertCharToTUint16LC( contact );
		switch ( msg_struct->hdr_req.message_type )
			{
            case ESubscribe_Remote_Pending:
                {                
                break;
                }
            case ETrying_To_Add_Contact_Known:
                {
                iConnMan.GetContactManager().AddContactToLocalL(*contactName);               
                iConnMan.GetContactManager().RemoveInvitationFromLocalL(*contactName);
                break;
                }
            case ESubscribe_RP_Accepted:
                {                
                break;
                }
            case EPublish_RP_Accepted:
                {                
                break;
                }            
            case ESubscribe_Removed_Or_Rejected:
                {
                //removing from the local copy of the contacts
                iConnMan.GetContactManager().RemoveContactFromLocalL(*contactName);                                     
                break;                                              	
                }           
            case EPublish_Removed_Or_Rejected:
                {
                iConnMan.GetContactManager().RemoveInvitationFromLocalL(*contactName);                    
                break;     
                }
            }        
        CleanupStack::PopAndDestroy ( 2 );//pOrigResponse, contactName 
    	}    
	LOGGER ( TXT ( "CContactSyncHandler::ProcessIncomingDataL End" ) );
	}


// ---------------------------------------------------------------------------
// CContactSyncHandler::RunError
// ---------------------------------------------------------------------------
//
TInt CContactSyncHandler::RunError ( TInt  aError )
	{
	LOGGER ( TXT ( "CContactSyncHandler::RunError Start %d" ), aError );

	LOGGER ( TXT ( "CContactSyncHandler::RunError End" ) );
	return KErrNone;
	}

// ---------------------------------------------------------------------------
// CContactSyncHandler::StartListeningL
// ---------------------------------------------------------------------------
//
void CContactSyncHandler::StartListening()
	{
	LOGGER ( TXT ( "CContactSyncHandler::StartListeningL Start" ) );

	if ( ! ( this->IsActive() ) )
		{
		iConnMan.DataHandler().ListenContactsChange( iStatus );
		SetActive();
		}
	LOGGER ( TXT ( "CContactSyncHandler::StartListeningL End" ) );
	}

// End of file
