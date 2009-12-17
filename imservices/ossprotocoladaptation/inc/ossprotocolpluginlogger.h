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
* Description:  Logger implementation
*
*/


#ifndef __TLOGGER_H__
#define __TLOGGER_H__

//  INCLUDES
#include <e32std.h>

//#ifdef _DEBUG
#define ENABLE_DEBUG_LOGS
//#endif

/**   
* Usage of Log MACRO'S
* _LIT( KExample, "Example" );
*  TXT(s) _L(s)	
*  LOGGER(TXT("Some text.") );
*  LOGGER(TXT("Some text: %d"), 100 );
*  LOGGER(TXT("Some text: %S"), &KExample );
*/

_LIT( KTAdaptDebugOutputDir, "os" );
_LIT( KTAdaptDebugOutputFileName, "ossadapt.txt" );
const TInt KTAdaptMaxLogLineLength = 250 ;
//#ifdef _DEBUG

#define TXT(s) _L(s)
#define LOGGER TLogger::WriteLog
#define PLUGIN_UNUSED_PARAM(p) (void) p
//#endif

/**
 * OSS Protocol Adaptation logger.
 */
class TLogger
    {
    public: //Logging functions
		static void WriteLog( TRefByValue<const TDesC> aFmt,... );
    private: //Prohibited construtor / destructor
        TLogger();
        ~TLogger();
    };
#endif  //__TLOGGER_H__

// End of File
