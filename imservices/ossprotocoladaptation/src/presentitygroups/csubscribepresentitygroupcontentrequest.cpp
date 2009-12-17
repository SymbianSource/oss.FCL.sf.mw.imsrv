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
* Description:  Subscribe Presentity Group content request to the Network Server.
*
*/


#include <ximpprotocolconnectionhost.h>
#include "csubscribepresentitygroupcontentrequest.h"
#include "cossprotocolconnectionmanager.h"
#include <ximpobjectfactory.h>
#include <protocolpresencedatahost.h>
#include <presenceobjectfactory.h>
#include <ximpobjectcollection.h>
#include <protocolpresentitygroupsdatahost.h>
#include <presentitygroupinfo.h>
#include <presentitygroupmemberinfo.h>
#include <ximpidentity.h>
#include <ximpdatasubscriptionstate.h>
#include "ossprotocolpluginlogger.h"

#include <glib/gstrfuncs.h>
#include <gtypes.h>
#include <stdlib.h>
#include "stringutils.h"
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <glib/gprintf.h>
#include "msgliterals.h"
#include "msg_enums.h"
#include "ossprotocoladaptutils.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CSubscribePresentityGroupContentRequest::CSubscribePresentityGroupContentRequest()
// ---------------------------------------------------------------------------
//
CSubscribePresentityGroupContentRequest::CSubscribePresentityGroupContentRequest (
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId ) :
		CActive ( EPriorityNormal ),
		iRequestId ( aRequestId ),
		iConnMan ( aConnMan ),
		iListcount ( 0 )
	{
	LOGGER ( TXT ( "::CSubscribePresentityGroupContentRequest Start" ) );
	CActiveScheduler::Add ( this );
	LOGGER ( TXT ( "::CSubscribePresentityGroupContentRequest End" ) );
	}


// ---------------------------------------------------------------------------
// CSubscribePresentityGroupContentRequest::ConstructL()
// ---------------------------------------------------------------------------
//
void CSubscribePresentityGroupContentRequest::ConstructL()
	{
	LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::ConstructL Start-End" ) );
	iGroupName = NULL;
	
	}


// ---------------------------------------------------------------------------
// CSubscribePresentityGroupContentRequest::NewL
// ---------------------------------------------------------------------------
//
CSubscribePresentityGroupContentRequest* CSubscribePresentityGroupContentRequest::NewL (
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
	{
	LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::NewL Start" ) );

	CSubscribePresentityGroupContentRequest* self = new ( ELeave )
	CSubscribePresentityGroupContentRequest ( aConnMan, aRequestId );
	CleanupStack::PushL ( self );
	self->ConstructL();
	CleanupStack::Pop ( self );

	LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::NewL End" ) );
	return self;
	}


// ---------------------------------------------------------------------------
// CSubscribePresentityGroupContentRequest::NewLC()
// ---------------------------------------------------------------------------
//
CSubscribePresentityGroupContentRequest* CSubscribePresentityGroupContentRequest::NewLC (
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
	{
	LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::NewLC Start" ) );

	CSubscribePresentityGroupContentRequest* self =
	    CSubscribePresentityGroupContentRequest::NewL ( aConnMan, aRequestId );
	CleanupStack::PushL ( self );

	LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::NewLC End" ) );
	return self;
	}

// ---------------------------------------------------------------------------
// CSubscribePresentityGroupContentRequest::~CSubscribePresentityGroupContentRequest()
// ---------------------------------------------------------------------------
//
CSubscribePresentityGroupContentRequest::~CSubscribePresentityGroupContentRequest()
	{
	LOGGER ( TXT ( "::~CSubscribePresentityGroupContentRequest Start" ) );
	delete iGroupName;
	iGroupName = NULL;
    Cancel();
    //iContacts.ResetAndDestroy();
	LOGGER ( TXT ( "::~CSubscribePresentityGroupContentRequest End" ) );
	}


// ---------------------------------------------------------------------------
// CSubscribePresentityGroupContentRequest::DoCancel()
// ---------------------------------------------------------------------------
//
void CSubscribePresentityGroupContentRequest::DoCancel()
	{
	LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::DoCancel Start" ) );
	iConnMan.DataHandler().CancelListening();
	LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::DoCancel End" ) );
	}

// ---------------------------------------------------------------------------
// CSubscribePresentityGroupContentRequest::RunL()
// ---------------------------------------------------------------------------
//
void CSubscribePresentityGroupContentRequest::RunL()
	{
	LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::RunL Start" ) );
	User::LeaveIfError( iStatus.Int() );
    TRAPD( error, ProcessIncomingDataL( ) );
    if ( error != KErrNone )
		{
		Cancel();
		}

	LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::RunL End" ) );
	}


// ---------------------------------------------------------------------------
// CSubscribePresentityGroupContentRequest::RunError
// ---------------------------------------------------------------------------
//
TInt CSubscribePresentityGroupContentRequest::RunError ( TInt  aError )
	{
	LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::RunError Start" ) );

	iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, aError );

	delete this;
	LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::RunError End" ) );
	return KErrNone;
	}

// ---------------------------------------------------------------------------
// CSubscribePresentityGroupContentRequest::SubscribePresentityGroupContentL
// ---------------------------------------------------------------------------
//
void CSubscribePresentityGroupContentRequest::SubscribePresentityGroupContentL (
    const MXIMPIdentity& aIdentity )
    {
    LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::SubscribePresentityGroupContentL Start" ) );
    if(iGroupName)
        {
        delete iGroupName;
        iGroupName = NULL;
        }
    iGroupName = aIdentity.Identity().AllocL();
    iConnMan.SetGroupIDL( *iGroupName ); // this groupname is used by contactsync class for synchronisation

    if(iConnMan.DataHandler().IsFetchContactsCompleted())
        {
        ProcessIncomingDataL( );
        }
    else
        {
        if ( ! ( this->IsActive() ) )
            {
            iConnMan.DataHandler().ListenIncomingData ( iStatus );
            SetActive();
            }
        }


    LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::SubscribePresentityGroupContentL End" ) );
    }


// ---------------------------------------------------------------------------
// CSubscribePresentityGroupContentRequest::ProcessIncomingDataL()
// ---------------------------------------------------------------------------
//
void CSubscribePresentityGroupContentRequest::ProcessIncomingDataL()
	{
	LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::ProcessIncomingDataL Start" ) );

	PopulateDataL();

	MXIMPObjectFactory& prfwObjFact = iConnMan.HandleToHost().ObjectFactory();

	MPresenceObjectFactory& prObjFact =
	iConnMan.HandleToHost().ProtocolPresenceDataHost().PresenceObjectFactory();

	MXIMPIdentity* contactIdentity = NULL;
	MPresentityGroupMemberInfo* groupMemberInfo = NULL;
	MXIMPObjectCollection* listOfContacts = prfwObjFact.NewObjectCollectionLC();
	
	//get the ref to contacts which was already stored in PopulateDataL
	RPointerArray<HBufC>& contacts =  iConnMan.GetContactManager().GetContactsListL();	

	for(TInt i = 0;i<contacts.Count();i++)
		{
		contactIdentity = prfwObjFact.NewIdentityLC();
		groupMemberInfo = prObjFact.NewPresentityGroupMemberInfoLC();
		contactIdentity->SetIdentityL ( *(contacts[ i ] ));
		groupMemberInfo->SetGroupMemberIdL ( contactIdentity );
		groupMemberInfo->SetGroupMemberDisplayNameL ( *(contacts[ i ] ) );
		listOfContacts->AddObjectL ( groupMemberInfo );	
		CleanupStack::Pop ( 2 );//groupMemberInfo, contactIdentity		

		}

	MXIMPIdentity* groupIdentity = prfwObjFact.NewIdentityLC();

	groupIdentity->SetIdentityL ( *iGroupName );

	iConnMan.HandleToHost().ProtocolPresenceDataHost().GroupsDataHost().HandlePresentityGroupContentL (
	groupIdentity, listOfContacts );
	iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KErrNone );
	CleanupStack::Pop ( 2 );//groupIdentity,listOfContacts 

	delete this;

	LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::ProcessIncomingDataL End" ) );

	}

// ---------------------------------------------------------------------------
// CSubscribePresentityGroupContentRequest::PopulateDataL
// ---------------------------------------------------------------------------
//
void CSubscribePresentityGroupContentRequest::PopulateDataL()
	{
	LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::PopulateDataL Start" ) );
	
	int len = MAX_SIZE_DATA;    
    char* pResponse = NULL, *pOrigResponse = NULL;  
    
 	TInt datacount = iConnMan.DataHandler().IncomingDataCount();
 	//to keep the local copy of contacts in adaptation till logout
 	RPointerArray<HBufC>& contacts = iConnMan.GetContactManager().GetContactsListL(); 
 	
 	while( datacount )
		{
		// get the incoming response from the server with transaction id equals zero
		pOrigResponse = pResponse = iConnMan.DataHandler().ResponseL ( 0 );
		CleanupStack::PushL(pOrigResponse) ;
		if( pResponse )
			{
			pResponse += sizeof ( message_hdr_resp );
		
			while(1)
				{
				len = strlen(pResponse) + 1;
				if (1 == len)
					{
					break;
					}
				char* contact = pResponse;	
				pResponse += len;
			
				HBufC16 *contactName = OssProtocolAdapUtils::ConvertCharToTUint16LC( contact );				
				contacts.AppendL(contactName);
				LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::PopulateDataL:ContactName:%S " ), contactName );
				CleanupStack::Pop ( contactName );				
				}	
			}

		CleanupStack::PopAndDestroy(pOrigResponse) ;//pOrigResponse
		
		datacount = iConnMan.DataHandler().IncomingDataCount();
		}

	LOGGER ( TXT ( "CSubscribePresentityGroupContentRequest::PopulateDataL End" ) );
	}



// End of file
