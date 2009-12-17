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

//For malloc
#include <stdlib.h>
//For protocol connection host
#include <ximpprotocolconnectionhost.h>
//For Connection manager
#include "cossprotocolconnectionmanager.h"
#include "csearchgetsearchkeys.h"
#include "msg_enums.h"

#include "ossprotocolpluginlogger.h"
//For Converting C style string to S60 style HBufC
#include "ossprotocoladaptutils.h"
//For open c string functions
#include <string.h>

#include <searchkeyinfo.h>

#include <searchobjectfactory.h>
#include <ximpobjectcollection.h>
#include <protocolsearchdatahost.h>
#include <protocolsearchfeaturedatahost.h>
#include <ximpobjectfactory.h>

/*!	/brief Documented in header file
*/
CSearchGetSearchKeys* CSearchGetSearchKeys::NewL( 
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
	{
	LOGGER ( TXT("::CSearchGetSearchKeys NewL Start") );
	
	CSearchGetSearchKeys* self = new ( ELeave ) CSearchGetSearchKeys( 
				aConnMan, aRequestId );
	
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	
	LOGGER ( TXT("::CSearchGetSearchKeys NewL End") );
	return self;		
	}
	

/*!	/brief Documented in header file
*/
CSearchGetSearchKeys::CSearchGetSearchKeys( 
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )	: 	CActive ( EPriorityNormal ),
		iRequestId ( aRequestId ),
		iConnMan ( aConnMan )
	{
	
	LOGGER ( TXT("::CSearchGetSearchKeys Start") );
	
    CActiveScheduler::Add( this );
    
    LOGGER ( TXT("::CSearchGetSearchKeys End") );
    
	}

/*!	/brief Documented in header file
*/	
CSearchGetSearchKeys::~CSearchGetSearchKeys()
	{
		
	}

/*!	/brief Documented in header file
*/	
void CSearchGetSearchKeys::DoCancel()
	{
		
	}

/*!	/brief Documented in header file
*/	
void CSearchGetSearchKeys::RunL()
	{
	LOGGER( TXT( "CSearchGetSearchKeys::RunL start" ) );
	
	User::LeaveIfError( iStatus.Int() );
	message_hdr_resp* msg_resp = NULL;
	
	char* response = NULL;
	CSearchKeyStore& keyStore = iConnMan.GetSearchKeyStore();
	
	response = iConnMan.DataHandler().ResponseL( iSendId );
	
	msg_resp = ( message_hdr_resp* ) response;
	
	if ( !msg_resp->response ) 
		{
		if ( msg_resp->error_type )
			{
			//Complete the request with an error				
			iConnMan.HandleToHost().HandleRequestCompleted( iRequestId, 
							KErrNotSupported );
			}
		}
	else 
		{
		
		{
		//This part reads all the possible labels from cen rep and tries to 
		//match the search labels got to those.. If match found search labels 
		//are assigned appropriate Enum values
		TInt index = sizeof( message_hdr_resp );
		char* keyStr = NULL;
		RPointerArray<TDesC> keyList;
		TInt len = 0;
		
		while( !( *( response + index ) == '\0'
					 && *( response + index + 1 ) == '\0' ) )
			{
			len = strlen( response + index ) + 1;
			keyStr = ( char* ) User::AllocLC( len );
			strcpy ( keyStr, response + index );
			index += len;
			
			HBufC* key = OssProtocolAdapUtils::ConvertCharToTUint16LC( keyStr );
			keyList.Append( key );
			CleanupStack::Pop(); //key
			CleanupStack::PopAndDestroy(); //keyStr
			}
		
		keyStore.MapLabelsToEnumL( keyList );
		}
		//Send all the labels to XIMP/UI
		MXIMPObjectFactory& objFact = iConnMan.HandleToHost().ObjectFactory();
		MSearchObjectFactory& searchObjFact = iConnMan.GetSearchHost().SearchObjectFactory();
		MXIMPObjectCollection* labelArray = objFact.NewObjectCollectionLC();
		
		RPointerArray<TSearchKey> lablEnum = keyStore.GetSupportedEnums();
		
		for ( TInt i = 0; i < lablEnum.Count(); i++ )
			{
			MSearchKeyInfo* srchKey = searchObjFact.NewSearchKeyInfoLC();
			srchKey->SetType( EKey );
			srchKey->SetKey((TSearchKey) *( lablEnum[i] ) );
			labelArray->AddObjectL( srchKey );//ownership transfered
			CleanupStack::Pop(); //srchKey
			}
		
		RPointerArray<TDesC> label = keyStore.GetNotSupportedLabels();
		
		for ( TInt i = 0; i < label.Count(); i++ )
			{
			MSearchKeyInfo* srchLabel = searchObjFact.NewSearchKeyInfoLC();
			srchLabel->SetType( ELabel );
			srchLabel->SetLabelL( *( label[i] ) );
			labelArray->AddObjectL( srchLabel );//ownership transfered
			CleanupStack::Pop(); //srchLabel
			}

		
		iConnMan.GetSearchHost().SearchFeatureDataAccess().HandleSearchKeysL ( 
							 labelArray );//ownership transfered
		iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KErrNone );
		
		CleanupStack::Pop( ); //labelArray
		}
	
	free( response );
	
	LOGGER( TXT( "CSearchGetSearchKeys::RunL end" ) );
	delete this;
	
	}

/*!	/brief Documented in header file
*/	
TInt CSearchGetSearchKeys::RunError( TInt aError )
	{
	LOGGER( TXT( "CSearchGetSearchKeys::RunError start" ) );	
	
	iConnMan.HandleToHost().HandleRequestCompleted( iRequestId, aError );
	
	LOGGER( TXT( "CSearchGetSearchKeys::RunError end" ) );
	
	return 0;
	}

/*!	/brief Documented in header file
*/	
void CSearchGetSearchKeys::ConstructL()
	{
			
	}

/*!	/brief Documented in header file
*/	
void CSearchGetSearchKeys::GetSearchKeysL()
	{
	LOGGER ( TXT("::CSearchGetSearchKeys GetSearchKeysL Start") );
	
	TInt len = sizeof ( message_hdr_req );
	message_hdr_req* msgHdr = ( message_hdr_req* ) User::AllocLC( len );
	
	msgHdr->message_type = ESearch_Get_Keys;
	
	iSendId = iConnMan.DataHandler().SendDataL( iStatus, ( char* )msgHdr, 
					len );
	
	SetActive();
	
	CleanupStack::PopAndDestroy ( 1 );//msgHdr	
	
	LOGGER ( TXT("::CSearchGetSearchKeys GetSearchKeysL End") );
	}
	
// End of file
