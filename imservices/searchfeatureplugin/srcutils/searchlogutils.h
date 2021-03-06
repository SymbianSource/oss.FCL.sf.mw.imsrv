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
* Description:  Log util header
*
*/



#ifndef SEARCHLOGUTILS_H
#define SEARCHLOGUTILS_H

//  INCLUDES
#include <e32std.h>
#include <flogger.h>


/**
*  Debug log writer
*  
*  
*/
class XSearchLogger
    {
    public: // New functions
        
        /**
        * Writes log to log file
        * @param 
        * @return 
        */
	    static void Log(TRefByValue<const TDesC> aFmt,...);


    };

#endif      // SEARCHLOGUTILS_H
           
// End of File
