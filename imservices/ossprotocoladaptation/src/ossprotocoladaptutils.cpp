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
* Description:  Utils for OSSProtocolAdaptation modules.
*
*/


// INCLUDES
#include "ossprotocoladaptutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escapeutils.h"
#include "stringutils.h"
  

// ---------------------------------------------------------------------------
// OssProtocolAdapUtils::OssProtocolAdapUtils::ConvertCharToTUint16L
// ---------------------------------------------------------------------------
//
HBufC16* OssProtocolAdapUtils::ConvertCharToTUint16LC( const char *pcSrc )
	{
	TUint8* scr = (TUint8*)pcSrc;
	TPtrC8 ptr;
	ptr.Set(scr);
	HBufC16* buf = EscapeUtils::ConvertToUnicodeFromUtf8L(ptr);
	CleanupStack::PushL(buf);
	return buf;	
	}
	

// ---------------------------------------------------------------------------
// OssProtocolAdapUtils::OssProtocolAdapUtils::ConvertTUint16ToCharL
// ---------------------------------------------------------------------------
//	
charFormatData OssProtocolAdapUtils::ConvertTUint16ToCharLC( const TDesC &aData )
	{
	HBufC8 * data = EscapeUtils::ConvertFromUnicodeToUtf8L( aData );
	CleanupStack::PushL(data);
	
	TPtr8 ptr = data->Des();
	TInt length = ptr.Length();
	
	//allocate new contiguous buffer as returned buffer may be fragmented.	
	HBufC8* newBuf = HBufC8::NewLC( length + 1 );//+1 space for '\0'
	TPtr8 newBufPtr = newBuf->Des();
	newBufPtr.Copy(ptr);
	
	char* chPtrTemp = ( char* )newBufPtr.PtrZ(); 
	char* chPtr = (char*) User::AllocL( length + 1 );
	strcpy( chPtr , chPtrTemp );
	
	CleanupStack::PopAndDestroy( 2 );//newBuf,data.
	
	charFormatData charData ;
	charData.data = chPtr;
	charData.dataSize = length + 1; //+1 space for '\0'
	
	CleanupStack::PushL(chPtr);
	return charData;
	}
// ---------------------------------------------------------------------------
// OssProtocolAdapUtils::ConvertTDesC8toChar
// ---------------------------------------------------------------------------
//
void OssProtocolAdapUtils::ConvertTDesC8toChar(const TDesC8& aSrc, char* aDes)
{
    char *temp = (char*)aSrc.Ptr();
    const TInt size = aSrc.Length();
    *(temp + size) = '\0';
    memcpy( aDes, temp, size );
}

// End of file
