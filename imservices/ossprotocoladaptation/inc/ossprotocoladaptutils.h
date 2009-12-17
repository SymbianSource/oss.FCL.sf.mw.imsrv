/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Utils for IOSSProtocolAdaptation
*
*/


#ifndef __OSSPROTOCLADAPUTILS_H__
#define __OSSPROTOCLADAPUTILS_H__

//  INCLUDES
#include <e32def.h>
#include <e32cmn.h>

struct charFormatData
    {
    char* data;
    TInt dataSize;//this also includes '/0'.
    };
/**
 *  Utils for OSSProtocolAdaptation modules. 
 */
class OssProtocolAdapUtils   
	{
	public: // new methods
 
    /**
	 * utility method to convert from char to unsigned int 
	 * @param1 pmSrc: source
	 * @return pointer to unsigned int 
	 */		
	 static HBufC16* ConvertCharToTUint16LC( const char *pcSrc);
	 /**
	 * utility method to convert from unsigned int to char
	 * @param1 pmSrc: source
	 * @return structure charFormatData, contains data and size
	 */	
	 static charFormatData ConvertTUint16ToCharLC( const TDesC &aData );
	 /**
      * utility method to convert from tdesc8 to char
      * @param1 aSrc: source
      * @param aDes: destination
      */ 
	 static void ConvertTDesC8toChar(const TDesC8& aSrc, char* aDes); 	 
	};

#endif      // __OSSPROTOCLADAPUTILS_H__

// End of File
