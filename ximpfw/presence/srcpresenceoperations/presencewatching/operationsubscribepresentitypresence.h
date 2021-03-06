/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: implementation of COperationSubscribePresentityPresence
 *
*/

#ifndef CPSCOPERATIONSUBSCRIBEPRESENTITYPRESENCE_H
#define CPSCOPERATIONSUBSCRIBEPRESENTITYPRESENCE_H


#include <e32base.h>
#include <ximpbase.h>

#include "ximpoperationbase.h"
#include "presentitypresencesubscriptionitem.h"

class CPresenceInfoFilterImp;

/**
 * Presence interest registration operation.
 *
 * @lib ximpoperations.lib
 * @since S60 v4.0
 */
class COperationSubscribePresentityPresence : public CXIMPOperationBase
    {

    public:

        IMPORT_C COperationSubscribePresentityPresence();

        void ConstructL( const TDesC8& aParamPck );

        ~COperationSubscribePresentityPresence();


    public: // from CXIMPOperationBase

        void ProcessL();

        void RequestCompletedL();

        TInt Type() const;

    private: // Helper methods

        /**
         * Synthesise event after completion
         */
        void SynthesiseEventL();

    private: // data
        
        /**
         * Presence info filter having new presence info filter for context.
         * Own.
         */
        CPresenceInfoFilterImp* iMergedPif;
        
        /**
         * Presentity subscription item
         * Own.
         */
        CPresentityPresenceSubscriptionItem* iSubItem;
        
        /**
         * Presentity address
         * Own.
         */
        CXIMPIdentityImp* iIdentity;
        
        /**
         * Filter
         * Own.
         */
        CPresenceInfoFilterImp* iPif;
        
        /**
         * Subscription status
         */
        CPresentityPresenceSubscriptionItem::TSubscriptionStatus iSubscriptionStatus;
        
        /**
         * Don't force event.
         */
        TBool iDoNotForce;
    };


#endif // CPSCOPERATIONSUBSCRIBEPRESENTITYPRESENCE_H
