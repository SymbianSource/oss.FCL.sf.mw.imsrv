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
* Description: Access handler of one network session
*
*/

#ifndef __MOSSPROTOCOLSTATUSOBSERVER_H
#define __MOSSPROTOCOLSTATUSOBSERVER_H


//  INCLUDES
#include    <E32Std.h>

/**
 *  Access handler of one network session
 *
 *  It is used to open/close network session
 *  and register its observers
 *
 */
class MPEngSessionStatusObserver
    {

    public: //

        /**
         *  Handle Session status change
         *
         *  @param new session slot state
         *  @param new session slot event
         */
        virtual void StatusChangedL(/* TPEngNWSessionSlotState aNewState, 
                                TPEngNWSessionSlotEvent aNewEvent*/ ) = 0;


    protected:  //Destructor

        /**
         *  Protected destructor to prohibits deletion trough interface.
         */
        virtual ~MPEngSessionStatusObserver() {};
    };


#endif      //  __MOSSPROTOCOLSTATUSOBSERVER_H

//  End of File



