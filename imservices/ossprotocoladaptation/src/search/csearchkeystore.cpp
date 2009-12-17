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
* Description:  This class handles dynamic search label-key pair storing.
*
*/


#include "csearchkeystore.h"
#include "ossprotocolpluginlogger.h"

/*!	/file
*	/brief Implimentation of interfaces defined in csearchkeystore.h
*/

/*!	/brief documented in the header file
*/
CSearchKeyStore* CSearchKeyStore::NewL() 
	{
	LOGGER ( TXT("::CSearchKeyStore NewL Start") );		
	
	CSearchKeyStore* self = new ( ELeave ) CSearchKeyStore;
	
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	
	
	LOGGER ( TXT("::CSearchKeyStore NewL End") );		
	return self;
	
	}

/*!	/brief documented in the header file
*/	
CSearchKeyStore::CSearchKeyStore()	
	{
		
	}	

/*!	/brief documented in the header file
*/
CSearchKeyStore::~CSearchKeyStore()
	{
	LOGGER ( TXT("::CSearchKeyStore ~CSearchKeyStore Start") );	
		
	//Close the hash map
	//<todo> any leaks here?
	iEnumLabels.Close();
	
	//<todo> any leaks here?
	//Close the hash map
	iSupportedLabels.Close();

	
	//reset and destroy
	iNotSupportedLabels.ResetAndDestroy();
	
	delete iLabelKeyHashRep;
	
	LOGGER ( TXT("::CSearchKeyStore ~CSearchKeyStore End") );		
	}
	
/*!	/brief documented in the header file
*/
void CSearchKeyStore::MapLabelsToEnumL( RPointerArray<TDesC>& aLabels )
	{
	LOGGER ( TXT("::CSearchKeyStore MapLabelsToEnum Start") );	
	
	RArray<TBool> enumBool;
	//TO avoid excessive computation, we mark enumBool[i] if 
	//a label is already attched to that enum
	for ( TInt i = 0; i < iEnumLabels.Count(); i++ )
		{
		//unmark all of it
		enumBool.Append( 0 );
		}
		
	for ( TInt i = 0; i < aLabels.Count(); i++ )
		{
		//Boolean to say if the label we are matching is supported
		TBool supported = EFalse;
		
		//Iterate thru the hash table of cenrep labels
		THashMapIter<TInt, TPtr16> iter( iEnumLabels );
		//Initialize to 0
		TInt j = 0;
		//Loop till thr is a key
		while( NULL != iter.NextKey() )
			{
			//Check if a label has been assigned to the enum
			if ( enumBool[j] )
				{
				j++;
				continue;
				}
			//If not
			//Get the possible labels for this enum from cen rep
			TPtr16 bufPtr = *(iter.CurrentValue());
			
			TBuf<1024> buf;
			//LC is not leaving/cleanup
			//It converts the aLabels to lower case 
			buf.CopyLC( *( aLabels[i] ) );
			
			//Match if the current label from isoserver is in the enum labels
			TInt match = bufPtr.Find( buf );
			
			if ( KErrNotFound != match )
				{
				//If a match is found, mark the corresponding enum 
				enumBool[j]	= 1;			
				TSearchKey enumvalue = ( TSearchKey )*( iter.CurrentKey() );
				//Add to supported labels hash key and label
				iSupportedLabels.InsertL( enumvalue, 
							aLabels[i]->AllocL()->Des() );
				//Set the flag as supported, so that it is not added in
				//not supported label
				supported = ETrue;
				//Break from the loop
				//Get next label try to match to the cen rep labels(supported enums)
				break;
				}			
			//update the enum index tracker		
			j++;
			}
		//If the label has not matched to any of the supported enum labels
		//add that to not supported list
		if ( EFalse == supported ) 
			{
			//Add to not supported labels				
			iNotSupportedLabels.Append( ( aLabels[i]->AllocL() ) );		
			}
			
		
		}
		
	LOGGER ( TXT("::CSearchKeyStore MapLabelsToEnum End") );		
	}

/*!	/brief documented in the header file
*/	
HBufC* CSearchKeyStore::GetLabelFromEnumL( TSearchKey aEnum )
	{
	LOGGER ( TXT("::CSearchKeyStore GetLabelFromEnum Start") );	
	
	TPtr* buf = NULL;
	//Find if the labels corresponding to enum is there
	//and return the alloced label.
	//Ownership is transfered to the callee
	buf = iSupportedLabels.Find( aEnum );
	if ( buf )	
		{
		return buf->AllocL();
		}
		
	LOGGER ( TXT("::CSearchKeyStore GetLabelFromEnum End") );
		
	return NULL;
	
	}

/*!	/brief documented in the header file
*/	
void CSearchKeyStore::ConstructL()	
	{
	LOGGER ( TXT("::CSearchKeyStore ConstructL Start") );
	
	iLabelKeyHashRep = CRepository::NewL( KLabelKeyStoreHash );
	TBuf<1024> buf;
	
	//Read all the labels supported for localization from cen rep
	//and have a map for the enum and search field
	for ( TInt i = 0; i < NO_OF_KEYS_SUPPORTED; i++ ) 
		{
		iLabelKeyHashRep->Get( ( TSearchKey )( i ), buf );
		iEnumLabels.InsertL( ( TSearchKey )( EUserFirstName + i ), buf.AllocL()->Des() );
		}
		
	LOGGER ( TXT("::CSearchKeyStore ConstructL End") );	
	}
/*!	/brief Get the supported enums
*	/return An array of pointers to the supported enums
*/
RPointerArray<TSearchKey> CSearchKeyStore::GetSupportedEnums()
	{
	LOGGER ( TXT("::CSearchKeyStore GetSupportedEnums Start") );
	
	RPointerArray<TSearchKey> supportedEnums;
	THashMapIter<TInt, TPtr16> iter( iSupportedLabels );
	
	while ( NULL != iter.NextKey() )
		{
		
		supportedEnums.Append( ( TSearchKey* )iter.CurrentKey() );
		
		}
		
	LOGGER ( TXT("::CSearchKeyStore GetSupportedEnums End") );
	
	return supportedEnums;
		
	}

/*!	/brief This function returns a handle to the array of not
*	supported label strings. Not supported here means that
*	there are no logical strings in UI for these labels
*	/return const handle to not supported strings
*/

const RPointerArray<TDesC> CSearchKeyStore::GetNotSupportedLabels()
	{
	LOGGER ( TXT("::CSearchKeyStore GetNotSupportedLabels Start") );
	
	return iNotSupportedLabels;		
	}
//End of file
