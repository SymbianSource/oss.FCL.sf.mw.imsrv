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
* Description:  contact manager
*
*/

#include "cosscontactmanager.h"
#include "mossprotocolconnectionmanager.h"

#include <ximpobjectfactory.h>
#include <ximpprotocolconnectionhost.h>
#include <ximpidentity.h>
#include <ximpobjectcollection.h>
#include <presenceobjectfactory.h>
#include <protocolpresencedatahost.h>
#include <protocolpresentitygroupsdatahost.h>
#include <presentitygroupinfo.h>
#include <presentitygroupmemberinfo.h>
#include <presencegrantrequestinfo.h>
#include <protocolpresenceauthorizationdatahost.h>
#include <mpresencebuddyinfo2.h>
#include <presencecachewriter2.h>
#include <avabilitytext.h>
#include "cossprotocolconnectionmanager.h"
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// COSSContactManager::COSSContactManager()
// ---------------------------------------------------------------------------
//
COSSContactManager::COSSContactManager(MOSSProtocolConnectionManager& aConnMan):
    iConnMan ( aConnMan )
	{
	
	}


// ---------------------------------------------------------------------------
// COSSContactManager::ConstructL()
// ---------------------------------------------------------------------------
//
void COSSContactManager::ConstructL()
	{	
	iFetchContactsFirstTime  = EFalse;
	iFetchInvitationsFirstTime = EFalse;	
	}


// ---------------------------------------------------------------------------
// COSSContactManager::NewL()
// ---------------------------------------------------------------------------
//
COSSContactManager* COSSContactManager::NewL(MOSSProtocolConnectionManager& aConnMan)
	{

	COSSContactManager* self = new ( ELeave )COSSContactManager(aConnMan);

	CleanupStack::PushL ( self );

	self->ConstructL();
	CleanupStack::Pop ( self );

	return self;
	}


// ---------------------------------------------------------------------------
// COSSContactManager::~COSSProtocolConnectionManager()
// ---------------------------------------------------------------------------
//
COSSContactManager::~COSSContactManager()
	{	
	iContacts.ResetAndDestroy();
	iInvitationList.ResetAndDestroy();
	}

// ---------------------------------------------------------------------------
// COSSContactManager::IsFetchForFirstTime()
// ---------------------------------------------------------------------------
//  
TBool COSSContactManager::IsFetchContactsFirstTime()
    { 
    return iFetchContactsFirstTime;    
    }

// ---------------------------------------------------------------------------
// COSSContactManager::IsFetchInvitationsForFirstTime()
// ---------------------------------------------------------------------------
//  
TBool COSSContactManager::IsFetchInvitationsForFirstTime()
    { 
    return iFetchInvitationsFirstTime;    
    }

// ---------------------------------------------------------------------------
// COSSContactManager::SetFetchForFirstTime()
// ---------------------------------------------------------------------------
//  
void COSSContactManager::SetFetchContactsFirstTime(TBool aValue)
    { 
    iFetchContactsFirstTime = aValue;    
    }

// ---------------------------------------------------------------------------
// COSSContactManager::SetFetchInvitationsForFirstTime()
// ---------------------------------------------------------------------------
//  
void COSSContactManager::SetFetchInvitationsForFirstTime(TBool aValue)
    { 
    iFetchInvitationsFirstTime = aValue;    
    }

// ---------------------------------------------------------------------------
// COSSContactManager::GetContactsListL()
// ---------------------------------------------------------------------------
//  
RPointerArray<HBufC>& COSSContactManager::GetContactsListL()
    {
    return iContacts;
    }
// ---------------------------------------------------------------------------
// COSSContactManager::GetInvitationListL()
// ---------------------------------------------------------------------------
//  
RPointerArray<HBufC>& COSSContactManager::GetInvitationListL()
    {
    return iInvitationList;
    }

// ---------------------------------------------------------------------------
// COSSContactManager::ReturnContactsListL()
// ---------------------------------------------------------------------------
//  
void COSSContactManager::ReturnInvitationListL()
    {
    MXIMPObjectFactory& prfwObjFact = iConnMan.HandleToHost().ObjectFactory();

    MPresenceObjectFactory& prObjFact = iConnMan.HandleToHost().ProtocolPresenceDataHost().PresenceObjectFactory();

    MXIMPIdentity* AuthReqIdentity = NULL ;
    MPresenceGrantRequestInfo* presenceGrant = NULL;

    MXIMPObjectCollection* listOfInvitations =  prfwObjFact.NewObjectCollectionLC();
    
    for ( TInt i = 0; i<iInvitationList.Count(); i++ )
        {
        presenceGrant = prObjFact.NewPresenceGrantRequestInfoLC();//1
        AuthReqIdentity = prfwObjFact.NewIdentityLC();//2
        AuthReqIdentity->SetIdentityL(*(iInvitationList[ i ] ));
        iInvitationList[i]->Des().Fold();
        presenceGrant->SetRequestorIdL(AuthReqIdentity);
        listOfInvitations->AddObjectL( presenceGrant );
        CleanupStack::Pop ( 2 );//presenceGrant, AuthReqIdentity      
        }
    
    iConnMan.HandleToHost().ProtocolPresenceDataHost().AuthorizationDataHost().HandlePresenceGrantRequestListL( listOfInvitations );
    CleanupStack::Pop ( 1 );//listOfInvitations
    }

// ---------------------------------------------------------------------------
// COSSContactManager::ReturnContactsListL()
// ---------------------------------------------------------------------------
//  
void COSSContactManager::ReturnContactsListL()
    {
    MXIMPObjectFactory& prfwObjFact = iConnMan.HandleToHost().ObjectFactory();

    MPresenceObjectFactory& prObjFact = iConnMan.HandleToHost().ProtocolPresenceDataHost().PresenceObjectFactory();

    MXIMPIdentity* contactIdentity = NULL;
    MPresentityGroupMemberInfo* groupMemberInfo = NULL;

    MXIMPObjectCollection* listOfContacts =  prfwObjFact.NewObjectCollectionLC();
    for(TInt i = 0;i<iContacts.Count();i++)
        {
        contactIdentity = prfwObjFact.NewIdentityLC();
        groupMemberInfo = prObjFact.NewPresentityGroupMemberInfoLC();
        contactIdentity->SetIdentityL ( *(iContacts[ i ] ));
        groupMemberInfo->SetGroupMemberIdL ( contactIdentity );
        groupMemberInfo->SetGroupMemberDisplayNameL ( *(iContacts[ i ] ) );
        listOfContacts->AddObjectL ( groupMemberInfo ); 
        CleanupStack::Pop ( 2 );//groupMemberInfo, contactIdentity
        }
    MXIMPIdentity* groupIdentity = prfwObjFact.NewIdentityLC();    
    groupIdentity->SetIdentityL ( iConnMan.GroupId() );    
    iConnMan.HandleToHost().ProtocolPresenceDataHost().GroupsDataHost().HandlePresentityGroupContentL ( groupIdentity, listOfContacts );
    CleanupStack::Pop ( 2 );//groupIdentity,listOfContacts 
    }

// ---------------------------------------------------------------------------
// COSSContactManager::RemoveContactFromLocalL()
// ---------------------------------------------------------------------------
//  
void COSSContactManager::RemoveContactFromLocalL(const TDesC& aContactName)
    {
    HBufC* contactName = aContactName.AllocLC();
    MXIMPObjectFactory& ximpObjFact = iConnMan.HandleToHost().ObjectFactory();
    MXIMPIdentity* contactIdentity = ximpObjFact.NewIdentityLC();
    MXIMPIdentity* groupIdentity = ximpObjFact.NewIdentityLC();    
    groupIdentity->SetIdentityL ( iConnMan.GroupId());
    contactIdentity->SetIdentityL(*contactName);
    //removing from the local copy of the contacts
    for(TInt i = 0; i<iContacts.Count(); i++)
        {                    
        if (!contactName->Compare(*(iContacts[i])))
            {                                                
            iContacts.Remove( i );
            //give info after removing. to ximp fw and client
            iConnMan.HandleToHost().ProtocolPresenceDataHost().GroupsDataHost().HandlePresentityGroupMemberRemovedL ( groupIdentity, contactIdentity );
            break;
            }
        }
    CleanupStack::Pop( 2 ); // contactIdentity , groupIdentity
    CleanupStack::PopAndDestroy( 1 ); //contactName
    }

// ---------------------------------------------------------------------------
// COSSContactManager::AddContactToLocalL()
// ---------------------------------------------------------------------------
//  
void COSSContactManager::AddContactToLocalL(const TDesC& aContactName)
    {    
    HBufC* contactName = aContactName.AllocLC();
    MXIMPObjectFactory& ximpObjFact = iConnMan.HandleToHost().ObjectFactory();
    MXIMPIdentity* contactIdentity = ximpObjFact.NewIdentityLC();
    MXIMPIdentity* groupIdentity = ximpObjFact.NewIdentityLC();    
    groupIdentity->SetIdentityL ( iConnMan.GroupId());
    contactIdentity->SetIdentityL(*contactName);    
    iContacts.AppendL(contactName);
    groupIdentity->SetIdentityL ( iConnMan.GroupId());
    contactIdentity->SetIdentityL(*contactName);
    MPresentityGroupMemberInfo* groupMemberInfo = iConnMan.HandleToHost().ProtocolPresenceDataHost().PresenceObjectFactory().NewPresentityGroupMemberInfoLC();   
    groupMemberInfo->SetGroupMemberIdL ( contactIdentity );
    groupMemberInfo->SetGroupMemberDisplayNameL ( *contactName );                
    iConnMan.HandleToHost().ProtocolPresenceDataHost().GroupsDataHost().HandlePresentityGroupMemberAddedL ( groupIdentity, groupMemberInfo );    

    //set presence as pending for the added contact
    MPresenceBuddyInfo2* buddyPresInfo = MPresenceBuddyInfo2::NewLC();
   
    MPresenceCacheWriter2* presenceCacheWriter = MPresenceCacheWriter2::CreateWriterL();
    CleanupDeletePushL(presenceCacheWriter);
    HBufC* name = HBufC::NewLC( aContactName.Length() + iConnMan.ServiceName().Length() + KColon().Length() );
    TPtr namePtr( name->Des() );
    namePtr.Zero();
    namePtr.Append(iConnMan.ServiceName() ); // prepend service name
    namePtr.Append(KColon);
    namePtr.Append(aContactName );
    buddyPresInfo->SetIdentityL(namePtr);
    buddyPresInfo->SetAnyFieldL(KExtensionKey,KPendingRequestExtensionValue());
    CleanupStack::PopAndDestroy(1);//name

    // Writing into Presence Cache
    TInt cacheerror = presenceCacheWriter->WritePresenceL(buddyPresInfo);
    User::LeaveIfError ( cacheerror);
    CleanupStack::PopAndDestroy(2);//presenceCacheWriter,buddyPresInfo
    CleanupStack::Pop( 4 ); // contactName, contactIdentity , groupIdentity , groupMemberInfo    
    }

// ---------------------------------------------------------------------------
// COSSContactManager::RemoveInvitationFromLocalL()
// ---------------------------------------------------------------------------
//  
void COSSContactManager::RemoveInvitationFromLocalL(const TDesC& aContactName)
    {
    MXIMPObjectFactory& ObjFact = iConnMan.HandleToHost().ObjectFactory();
    MPresenceObjectFactory& prfwObjFact = iConnMan.HandleToHost().ProtocolPresenceDataHost().PresenceObjectFactory();
    MXIMPIdentity* authReqIdentity = ObjFact.NewIdentityLC();//1
    if( authReqIdentity )
        {
        authReqIdentity->SetIdentityL(aContactName);   
        for(TInt i = 0; i<iInvitationList.Count(); i++)
            {
            HBufC* findInvitation = iInvitationList[i];
            if ( findInvitation && !aContactName.Compare( *findInvitation) )
                {                                                
                iInvitationList.Remove( i ); 
                delete findInvitation;
                findInvitation = NULL;
                iInvitationList.Compress();
                iConnMan.HandleToHost().ProtocolPresenceDataHost().AuthorizationDataHost().HandlePresenceGrantRequestObsoletedL(authReqIdentity);
                CleanupStack::Pop();   //AuthReqIdentity
                return;
                }
            }          
        CleanupStack::PopAndDestroy();   //AuthReqIdentity
        }
    }
// End of File


