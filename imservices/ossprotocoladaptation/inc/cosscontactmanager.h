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

#ifndef __COSSCONTACTMANAGER_H__
#define __COSSCONTACTMANAGER_H__

#include <e32base.h>


class MOSSProtocolConnectionManager;
/**
 * COSSContactManager
 *
 */
NONSHARABLE_CLASS ( COSSContactManager ) : public CBase       
    {

    public:

        static COSSContactManager* NewL(MOSSProtocolConnectionManager& aConnMan);
        ~COSSContactManager();


    private:

        COSSContactManager(MOSSProtocolConnectionManager& aConnMan);
        void ConstructL();
        
    public:
        /**
         *  get iFetchContactsFirstTime         
         */
        TBool IsFetchContactsFirstTime();
        /**
         *  iFetchInvitationsFirstTime         
         */
        TBool IsFetchInvitationsForFirstTime();
        /**
         *  Set iFetchContactsFirstTime 
         *  @param value to be set
         */
        void SetFetchContactsFirstTime(TBool aValue);
        /**
         *  Set iFetchInvitationsFirstTime
         *  @param value to be set
         */
        void SetFetchInvitationsForFirstTime(TBool aValue);
        /**
         *  Get reference to iContacts 
         *  @param iContacts
         */
        RPointerArray<HBufC>& GetContactsListL();

        /**
         *  Get reference to iInvitationList 
         *  @param return iInvitationList
         */
        RPointerArray<HBufC>& GetInvitationListL();
        /**
         *  give list of invitations to ximp fw and client side ui
         *  
         */
        void ReturnInvitationListL();
        /**
         *  give list of current member and remote pending contacts to ximp fw and client side ui
         *  
         */
        void ReturnContactsListL();
        /**
         *  remove a contact from the local copy of iContacts 
         *  @param aContactName to be removed
         */
        void RemoveContactFromLocalL(const TDesC& aContactName);
        /**
         *  add a contact to the local copy of iContacts 
         *  @param aContactName to be added
         */
        void AddContactToLocalL(const TDesC& aContactName);        
        /**
         *  remove a invitation from the local copy of iInvitationList 
         *  @param aContactName to be removed from the invitation list
         */
        void RemoveInvitationFromLocalL(const TDesC& aContactName);
        
    private:
        
        /**
         * Oss Protocol Plugin Contact Manager
         * Not own.  *** Write "Not own" if some other class owns this object.
         */
        MOSSProtocolConnectionManager& iConnMan;
        
        /**
         * stores if fetching contacts for the first time value
         * Own
         */
        TBool iFetchContactsFirstTime ;
        /**
         * stores if fetching invitations for the first time value
         * Own
         */
        TBool iFetchInvitationsFirstTime ;
        /**
         * current contacts. to maintain local copy of current contacts
         * own
         */
        RPointerArray<HBufC>   iContacts;

        /**
         * local copy of pending contacts or invitations
         * own
         */
        RPointerArray<HBufC>  iInvitationList;        
        
    };

#endif // __COSSCONTACTMANAGER_H__

// End of File


