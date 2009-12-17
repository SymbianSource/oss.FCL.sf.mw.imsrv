/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Source file for stringutils
*
*/


// GCCE header
//#ifdef __GCCE__
//#include <staticlibinit_gcce.h>
//#endif //__GCCE__

//System headers
#include <string.h>
#include <stdlib.h>

//User-definied headers
#include "stringutils.h"


EXPORT_C wchar_t* tbuf16towchar(TDes& aArg)
{
	return (wchar_t*)aArg.PtrZ();
}
	
EXPORT_C char* tbuf8tochar(TDes8& aArg)
{
	return (char*)aArg.PtrZ();
}

EXPORT_C int tbuf16tochar(TDes& aSrc, char* aDes)
{
	const TUint16 *wideString = aSrc.PtrZ();
	
	TInt ret = wcstombs(aDes, (const wchar_t*)wideString, KMaxFileName );
	
	return ret;
}

EXPORT_C int tbuf8towchar(TDes8& aSrc  ,wchar_t* aDes)
{
	const char *charString = (const char*)aSrc.PtrZ();
	
	TInt ret = mbstowcs(aDes, charString, KMaxFileName );
	
	return ret;
}
	
	
EXPORT_C void tbufC16towchar(TDesC& aSrc ,wchar_t *aDes)
{
	wchar_t *temp = (wchar_t*)aSrc.Ptr();
	const TInt size = aSrc.Size();
	*(temp + size/2 ) = L'\0';
	wcscpy(aDes, temp);
}

EXPORT_C void tbufC8tochar(TDesC8& aSrc, char* aDes)
{
	char *temp = (char*)aSrc.Ptr();
	const TInt size = aSrc.Length();
	*(temp + size) = '\0';
	strcpy(aDes, temp);
}
	
EXPORT_C int tbufC16tochar(TDesC& aSrc, char* aDes)
{
	TUint16* wideString = (TUint16*)aSrc.Ptr();
	const TInt size = aSrc.Length();
	*(wideString + size) = L'\0';
	
	
	TInt ret = wcstombs(aDes, (const wchar_t*)wideString, size*2 );
	return ret;	
}


EXPORT_C int tbufC8towchar(TDesC8& aSrc, wchar_t* aDes)
{
	TUint8* charString = (TUint8*)aSrc.Ptr();
	const TInt size = aSrc.Length();
	*(charString + size) = '\0';
	
	TInt ret = mbstowcs(aDes, (const char*)charString, KMaxFileName );
	return ret;
}

EXPORT_C void wchartotbuf16(const wchar_t *aSrc, TDes16 &aDes)
{
	aDes = (const TUint16*)aSrc;
}

EXPORT_C  int chartotbuf16(const char *aSrc, TDes16 &aDes)
{
	int len = strlen(aSrc);
	wchar_t *buf = new wchar_t[len];
	
	TInt ret = mbstowcs(buf, (const char*)aSrc, len + 1 );
	
	if( ret != -1)
		aDes = (const TUint16*)buf;
	
	delete buf;
	return ret;
}

EXPORT_C int wchartotbuf8(const wchar_t *aSrc, TDes8 &aDes)
{
	int len = wcslen(aSrc);
	char *buf = new char[len];
	
	TInt ret = wcstombs(buf, (const wchar_t*)aSrc, len + 1);
	
	if( ret != -1)
		aDes = (const TUint8*)buf;
	
	delete buf;
	return ret;
}
	
EXPORT_C  void chartotbuf8 (const char *aSrc, TDes8 &aDes)
{
	aDes = (const TUint8*)aSrc;
}

EXPORT_C  void wchartohbufc16 (const wchar_t* aSrc ,HBufC16& aDes )
{
	aDes = (const TUint16*)aSrc;		
}
	
EXPORT_C int chartohbufc16(const char* aSrc, HBufC16& aDes)
{	
	int len = strlen(aSrc);
	wchar_t *buf = new wchar_t[len];
	
	TInt ret = mbstowcs(buf, (const char*)aSrc, len + 1);
	
	if( ret != -1)
		aDes = (const TUint16*)buf;
	
	delete buf;
	return ret;
}
	
EXPORT_C void chartohbufc8(const char* aSrc, HBufC8& aDes)
{
	aDes = (const TUint8*)aSrc;
}
	
EXPORT_C int wchartohbufc8(const wchar_t* aSrc, HBufC8& aDes)
{
	int len = wcslen(aSrc);
	char *buf = new char[len];
	
	TInt ret = wcstombs(buf, aSrc, len + 1 );
	
	if( ret != -1)
		aDes = (const TUint8*)buf;
	
	delete buf;
	return ret;
}


	
// End of file
