/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Event interface for Search results.
*
*/

#ifndef MSEARCHEVENT_H
#define MSEARCHEVENT_H

#include <ximpbase.h>
#include <searchmanagementifids.hrh>

class MSearchInfo;
class MXIMPIdentity;

/**
 * Event interface for search content.
 *
 * This interface is implemented by the Search Feature Plugin 
 * This event notifies clients 
 * when Search result is received from protocol.
 * 
 * @ingroup searchmanagementapi
 */
class MSearchEvent : public MXIMPBase
    {
public:
    /** Interface ID for the MSearchEvent. */
    enum { KInterfaceId = SEARCH_IF_ID_SEARCH_EVENT };


protected:

    /**
     * Protected destructor.
     * Object instancies can't be deleted via this interface.
     */
    virtual inline ~MSearchEvent() {};


public: 

	
    /**
     * returns the count of the searched results.
     *
     * @return The count of count of the searched results.
     */
    virtual TInt SearchResultCount() const = 0;
    
    
    /**
     * Gets the searched result by index.
     *
     * @param [in] aIndex
     *        The index of the search.
     *
     * @return The searched result from given index.
     */
    virtual const MSearchInfo& SearchResult( TInt aIndex ) const = 0;
    
    
    /**
     * returns the serachid
     *
     * @return The serach id fro which result has come.
     */
    virtual const MXIMPIdentity& SearchId() const = 0;
	

    };


#endif // MSEARCHEVENT_H


