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
* Description:   	Header file for stringutils
*
*/

#ifndef __STRINGUTILS_H__
#define __STRINGUTILS_H__

/** @file stringutils.h
 * stringutils is a DLL that exports some set of genaralized APIs using which 
 * user can convert the SYMBIAN descriptors to standard C character/wide-character
 * strings and vice-versa
 */

//Symbian Headers
#include <e32cmn.h>
#include <wchar.h>

/**
  * Aliases : Cconverting HBufC variants to char/wchar_t strings involves
  * similiar procedure to that of converting TBufC variants to  char/wchar_t strings.
  * Hence HBufC to char/wchar_t conversion Apis are aliased to their corresponding TBufC 
  * counterparts
  */


/**
  * Alias to the function tbufC16towchar
  */
#define hbufC16towchar	tbufC16towchar
/**
  * Alias to the function tbufC16tochar
  */
#define hbufC16tochar	tbufC16tochar
/**
  * Alias to the function tbufC8towchar
  */
#define hbufC8towchar	tbufC8towchar
/**
  * Alias to the function tbufC8tochar
  */
#define hbufC8tochar	tbufC8tochar

		
//Function prototypes

/** Functions to convert SYMBIAN descriptors to C character and
  * Wide-Character strings 
  */

/**
  * This Api converts the tbuf16 to a wide-character string
  * @param aArg TDes object
  * @return	a pointer to a wide-character string
  */
IMPORT_C wchar_t* tbuf16towchar(TDes& aArg);

/**
  * This Api converts the tbuf8 to a character string
  * @param aArg TDes8 object
  * @return	a pointer to a character string
  */
IMPORT_C char* tbuf8tochar(TDes8& aArg);

/**
  * This Api converts the tbuf16 to a character string. It is user
  * responsibality to allocate a required size of char object. Api may
  * resulting in crash, if the destination object size is smaller than
  * that of the source.
  * @param 		aSrc TDes16 object
  * @param 		aDes character pointer, to which the resultant string will be copied.
  * @return		returns an integer value.
  * @return		Api returns -1 in case of any error.
  */
IMPORT_C int tbuf16tochar(TDes& aSrc, char* aDes);
	
/**
  * This Api converts the tbuf8 to a wide-character string. It is user
  * responsibality to allocate a required size of wide-char object. Api	may
  * resulting in crash, if the destination object size is smaller than that 
  * of the source.
  * @param 		aSrc TDes8 object
  * @param 		aDes wide-character pointer, to which the resultant string will be copied.
  * @return		returns an integer value.
  * @return		Api returns -1 in case of any error.
  */
IMPORT_C int tbuf8towchar(TDes8& aSrc, wchar_t* aDes);
	
/**
  * This Api converts the tbuf16 to a wide-character string. It is user
  * responsibality to allocate a required size of wide-char object. Api may
  * resulting in crash, if the destination object size is smaller than
  * that of the source.
  * @param 		aSrc TDes16 object
  * @param 		aDes wide-character pointer, to which the resultant string will be copied.
  * @return		none
  */
IMPORT_C void tbufC16towchar(TDesC& aSrc ,wchar_t* aDes);

  
 /**
  * This Api converts the tbufC8 to a character string. It is user 
  * responsibality to allocate a required size of wide-char object. Api may
  * resulting in crash, if the destination object size is smaller than
  * that of the source.
  * @param 		aSrc TDesC8 object
  * @param 		aDes character pointer, to which the resultant string will be copied.
  * @return		none
  */
  
IMPORT_C void tbufC8tochar(TDesC8& aSrc, char* aDes);

/**
  * This Api converts the TBufC16 to a character string. It is user
  *	responsibality to allocate a required size of wide-char object. Api may
  * resulting in crash, if the destination object size is smaller than
  * that of the source.
  * @param 		aSrc TDesC object
  * @param 		aDes character pointer, to which the resultant string will be copied.
  * @return		returns an integer value.
  * @return		Api returns -1 in case of any error.
  */
IMPORT_C int tbufC16tochar(TDesC& aSrc, char* aDes);
	
	
/**
  * This Api converts the TBufC8 to a wide-character string. It is user 
  * responsibality to allocate a required size of wide-char object. Api may
  * resulting in crash, if the destination object size is smaller than
  * that of the source.
  *	@param 		aSrc TDesC8 object
  * @param 		aDes wide-character pointer, to which the resultant string will be copied.
  *	@return		returns an integer value.
  * @return		Api returns -1 in case of any error.
  */
IMPORT_C int tbufC8towchar(TDesC8& aSrc, wchar_t* aDes);


/**
  * Functions to convert C character and
  * Wide-Character strings to SYMBIAN descriptors 
  */

/**
  * This Api converts the wide-char to a TBuf16. It is user responsibality 
  * to allocate a required size of TBuf16 object. Api may	resulting in crash,
  * if the destination object size is smaller than	that of the source.
  * @param 		aSrc wide-character pointer.
  * @param 		aDes TBuf16 object, to which the resultant string will be copied.
  * @return		none
  */
IMPORT_C void wchartotbuf16(const wchar_t *aSrc, TDes16& aDes);
	

 /**
  * This Api converts the char to a TBuf16. It is user responsibality 
  * to allocate a required size of TBuf16 object. Api may	resulting in crash,
  * if the destination object size is smaller than	that of the source.
  * @param 		aSrc character pointer.
  * @param 		aDes TBuf16 object, to which the resultant string will be copied.
  * @return		returns an integer value.
  * @return		Api returns -1 in case of any error.
  */
IMPORT_C int chartotbuf16(const char* aSrc, TDes16& aDes);
	
/**
  * This Api converts the wide-char string to a TBuf8. It is user 
  * responsibality to allocate a required size of TBuf8 object. Api may
  *	resulting in crash, if the destination object size is smaller than
  * that of the source.
  * @param 		aSrc 	wide-character pointer.
  * @param 		aDes	TBuf8 object, to which the resultant string will be copied.
  * @return		returns an integer value.
  * @return		Api returns -1 in case of any error.
  */
IMPORT_C int wchartotbuf8(const wchar_t* aSrc, TDes8& aDes);


 /*
  * This Api converts the character string to a TBuf8. It is user 
  *	responsibality to allocate a required size of TBuf8 object. Api may	
  * resulting in crash, if the destination object size is smaller than
  * that of the source.
  * @param 		aSrc character pointer.
  * @param 		aDes TBuf8 object, to which the resultant string will be copied.
  *	@return		none
  */
IMPORT_C void chartotbuf8(const char* aSrc, TDes8& aDes);


 /**
  * This Api converts the wide-char to a HBufC16. It is user responsibality 
  * to allocate a required size of HBufC16 object. Api may resulting in crash,
  * if the destination object size is smaller than	that of the source.
  * @param 		aSrc wide-character pointer.
  * @param 		aDes HBufC16 object, to which the resultant string will be copied.
  * @return		none
  */
IMPORT_C void wchartohbufc16(const wchar_t* aSrc, HBufC16& aDes);
	

 /**
  * This Api converts the char to a HBufC16. It is user responsibality 
  * to allocate a required size of HBufC16 object. Api may resulting in crash,
  * if the destination object size is smaller than	that of the source.
  * @param 		aSrc character pointer.
  * @param 		aDes HBufC16 object, to which the resultant string will be copied.
  * @return		returns an integer value.
  * @return		Api returns -1 in case of any error.
  */
IMPORT_C int chartohbufc16(const char* aSrc, HBufC16& aDes);
	
/**
  * This Api converts the wide-char to a HBufC8. It is user responsibality 
  * to allocate a required size of HBufC8 object. Api may resulting in crash,
  * if the destination object size is smaller than	that of the source.
  * @param 		aSrc wide-character pointer.
  * @param 		aDes HBufC8 object, to which the resultant string will be copied.
  * @return		returns an integer value.
  * @return		Api returns -1 in case of any error.
  */
IMPORT_C int wchartohbufc8(const wchar_t* aSrc, HBufC8& aDes);

  
 /*
  * This Api converts the char to a HBufC8. It is user responsibality 
  * to allocate a required size of HBufC8 object. Api may resulting in crash,
  * if the destination object size is smaller than	that of the source.
  * @param 		aSrc character pointer.
  * @param 		aDes HBufC8 object, to which the resultant string will be copied.
  * @return		none
  */
IMPORT_C void chartohbufc8(const char* aSrc, HBufC8& aDes);


	
#endif //__STRINGUTILS_H__