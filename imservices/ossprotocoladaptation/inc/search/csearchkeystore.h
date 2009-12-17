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


/*!	/def To avoid multiple inclusions
*/
#ifndef C_SEARCHKEYSTORE_H
#define C_SEARCHKEYSTORE_H

//For CBase
#include <e32base.h>
//For RHashMap
#include <e32hashtab.h>
//For TDesC
#include <e32cmn.h>
//For CRepository
#include <centralrepository.h>
//For TSearchKey
#include <searchelement.h>

/*!	/file 	
*	Interfaces for CSearchKeyStore class
*/


/*!	/var KLabelKeyStoreHash Uid to access central repository
*/
const TUid KLabelKeyStoreHash = { 0x200195A9 };
/*!	/def Total no. of keys that the UI supports( for localization )
*/
#define NO_OF_KEYS_SUPPORTED 13


/*!	/class CSearchKeyStore csearchkeystore.h
*
*	/brief This class stores the localizable search labels, and maps
*	the labels got from get search keys to enums( Localizable ) and 
*	strings( non localizable ). 
*
*	/brief Background : The search key labels from server are not standardized.
*	So gizmo can give for 'First Name' a label 'First' and gtalk can give it as
*	'Name'. We will have possible values for 'First Name' in cen rep. And 
*	whenever a get search keys done and labels got, we wil try to map those
*	to enums('Name', 'First' for EFirstName). If for 'first name' the label
*	for some xyz server is 'Given' then it is non localizable. And wil be 
*	sent to UI as a string
*/
class CSearchKeyStore : public CBase
	{
	
	public : 
		/*!	/fn
		*	/brief Static function that creates a new object
		*	of type CSearchKeyStore
		*/
		static CSearchKeyStore* NewL();
		
		/*!	/fn
		*	/brief constructor for the CSearchKeyStore class
		*/
		CSearchKeyStore();	
		
		/*!	/fn
		*	/brief destructor for the CSearchKeyStore class
		*/
		virtual ~CSearchKeyStore();
		
		/*!	/fn
		*	/brief Maps the labels from server got by making a get 
		*	search keys request to server. Those are mapped to localizable
		*	enums and non localizable strings
		*
		*	/param aLabels Labels to be classified
		*/
		void MapLabelsToEnumL( RPointerArray<TDesC>& aLabels );
		
		/*!	/fn
		*	/brief Gets the label (for server) for the given enum(search field)
		*
		*	/param aEnum search field
		*	/return HBufC* string corresponding to the enum. The ownership of
		*	returned pointer is transfered to callee.
		*/
		HBufC* GetLabelFromEnumL( TSearchKey aEnum );
		
		/*!	/brief This function returns an array of pointers to the
		*	supported keys( Supported labels are the labels that have 
		*	support in the UI for logical strings)
		*
		*	/return an array of pointers to enums
		*/	
		RPointerArray<TSearchKey>	GetSupportedEnums();
		
				
		/*!	/brief This function returns a handle to the array of not
		*	supported label strings. Not supported here means that
		*	there are no logical strings in UI for these labels
		*
		*	/return const handle to not supported strings
		*/

		const RPointerArray<TDesC> GetNotSupportedLabels();
		
	private:
		
		/*!	/fn
		*	/brief ConstructL reads labels from the cen rep
		*	and maps them to enums
		*/
		void ConstructL();
		
		/*!	/var iLabelKeyHashRep Handle to cen rep
		*/
		CRepository* iLabelKeyHashRep;//owned
		
		/*!	/var iEnumLabels maps the labels to enums
		*/
		RHashMap<TInt, TPtr16> iEnumLabels;//owned
		
		/*!	/var iNotSupportedLabels Has the labels that can not
		*	be localized.
		*/
		RPointerArray<TDesC> iNotSupportedLabels;//owned
		
		/*!	/var iSupportedLabels Hash Map of the search labels and
		*	to search field enums
		*/
		RHashMap<TInt, TPtr16> iSupportedLabels;//owned

	};



#endif //C_SEARCHKEYSTORE_H
