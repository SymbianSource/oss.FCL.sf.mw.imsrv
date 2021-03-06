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
* Description:  Presentity group content unsubscribe operator
 *
*/

#ifndef CPSCOPERATIONUNSUBSCRIBEGROUPCONTENT_H
#define CPSCOPERATIONUNSUBSCRIBEGROUPCONTENT_H


#include <e32base.h>
#include <ximpbase.h>

#include "ximpoperationbase.h"
#include "groupcontentsubscriptionitem.h"
#include "presenceoperationdefs.h"

/**
 * Presence interest registration operation.
 *
 * @lib ximpoperations.lib
 * @since S60 v4.0
 */
class COperationUnsubscribeGroupContent : public CXIMPOperationBase
    {

    public:

        IMPORT_C COperationUnsubscribeGroupContent();

        void ConstructL( const TDesC8& aParamPck );

        ~COperationUnsubscribeGroupContent();


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
         * Group content access.
         */
        CGroupContentSubscriptionItem* iSubItem;

        /**
         * Subscription status
         */
        CGroupContentSubscriptionItem::TSubscriptionStatus iSubscriptionStatus;

        /**
         * Subscribed Group Id
         * Own.
         */
        CXIMPIdentityImp* iGroupId;

    };


#endif // CPSCOPERATIONUNSUBSCRIBEGROUPCONTENT_H
