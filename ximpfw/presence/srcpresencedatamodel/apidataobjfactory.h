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
* Description:  API data object factory
*
*/



#ifndef M_APIOBJFACTORY_H
#define M_APIOBJFACTORY_H

#include <e32std.h>

class CXIMPApiDataObjBase;


/**
 * ?one_line_short_description
 *
 * ?more_complete_description
 *
 * @lib ?library
 * @since S60 v4.0
 */
class MApiDataObjFactory
    {  
public:
    
    virtual CXIMPApiDataObjBase* NewFromStreamLC( TInt32 aDataObjInterfaceId,
                                                            RReadStream& aStream ) = 0;
    
    };

#endif // M_APIOBJFACTORY_H

