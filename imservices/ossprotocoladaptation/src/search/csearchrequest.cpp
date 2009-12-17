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
* Description:  Search implementation
*
*/


#include <string.h>
#include <stdlib.h>

#include <ximpprotocolconnectionhost.h>
#include <ximpobjectfactory.h>
#include <searchelement.h>
#include <searchobjectfactory.h>
#include <ximpobjectcollection.h>
#include <searchinfo.h>
#include <searchobjectfactory.h>
#include <protocolsearchdatahost.h>
#include <protocolsearchfeaturedatahost.h>
#include <ximpidentity.h>

#include "stringutils.h"

#include "msg_enums.h"
#include "waittimer.h"
#include "msgliterals.h"
#include "ossprotocoladaptutils.h"
#include "csearchrequest.h"
#include "mossprotocolconnectionmanager.h"
#include "ossprotocolpluginlogger.h"

#include "cossprotocolconnectionmanager.h"


// search  strings  used 
const char* FirstName ="first_name";
const char* LastName ="last_name";
const char* UserId ="user_id";
const char* Jid ="jid";

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CSearchrequest::CSearchrequest
// ---------------------------------------------------------------------------
//
CSearchrequest::CSearchrequest(	MOSSProtocolConnectionManager& aConnMan,
									TXIMPRequestId aRequestId ) :
    CActive( EPriorityNormal ),
    iRequestId( aRequestId ),
    iConnMan( aConnMan )
    {
    LOGGER ( TXT("::CSearchrequest Start") );
    CActiveScheduler::Add( this );
    
    LOGGER ( TXT("::CSearchrequest End") );
    }


// ---------------------------------------------------------------------------
// CSearchrequest::ConstructL
// ---------------------------------------------------------------------------
//
void CSearchrequest::ConstructL()
    {
    LOGGER ( TXT("CSearchrequest::ConstructL Start-End") );
    
	iSearchId=NULL;
    }


// ---------------------------------------------------------------------------
// CSearchrequest::NewLC
// ---------------------------------------------------------------------------
//
CSearchrequest* CSearchrequest::NewLC(
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
    {
    LOGGER ( TXT("CSearchrequest::NewLC Start") );
    
     CSearchrequest* self = new( ELeave ) 
    			CSearchrequest( aConnMan, aRequestId );
    CleanupStack::PushL( self );
    self->ConstructL();
    
    LOGGER ( TXT("CSearchrequest::NewLC End") );
    return self;
    }

// ---------------------------------------------------------------------------
// CSearchrequest::~CSearchrequest
// ---------------------------------------------------------------------------
//
CSearchrequest::~CSearchrequest()
    {
    LOGGER ( TXT("::~CSearchrequest Start") );
    delete iSearchId;
    iSearchId=NULL;
    
	CActive::Cancel();
    
    LOGGER ( TXT("::~CSearchrequest End") );
    }


// ---------------------------------------------------------------------------
// CSearchrequest::DoCancel()
// ---------------------------------------------------------------------------
//
void CSearchrequest::DoCancel()
    {
    LOGGER ( TXT("CSearchrequest::DoCancel Start") );
    LOGGER ( TXT("CSearchrequest::DoCancel End") );
    }


// ---------------------------------------------------------------------------
// CSearchrequest::RunL()
// ---------------------------------------------------------------------------
//
void CSearchrequest::RunL()
	{
	LOGGER ( TXT("CSearchrequest::RunL Start") );
	User::LeaveIfError ( iStatus.Int() );

	int len = MAX_SIZE_DATA;
	char* pResponse = NULL, *pOrigResponse = NULL;;
	char* key = NULL; 

	MXIMPObjectFactory& objFact = iConnMan.HandleToHost().ObjectFactory();
	MSearchObjectFactory& searchObjFact = iConnMan.GetSearchHost().SearchObjectFactory();
	MXIMPIdentity* identity = objFact.NewIdentityLC();
	MXIMPObjectCollection* fieldlist = objFact.NewObjectCollectionLC();

  	TInt datacount = iConnMan.DataHandler().SearchDataCount();
 	
 	while( datacount )
		{
		LOGGER ( TXT("CONTACT NO : %d"), datacount );	
		pOrigResponse =pResponse = iConnMan.DataHandler().ResponseL ( 5 );
		CleanupStack::PushL(pOrigResponse) ;
		MSearchInfo* searchInfo = searchObjFact.NewSearchInfoLC();
		pResponse += sizeof ( message_hdr_resp );
		len = strlen(pResponse) + 1;
		while( !( *(pResponse) == '\0' && *(pResponse + 1) == '\0' ))
			{
			len = strlen(pResponse) + 1;
			key = ( char* ) User::AllocLC(len);
			strcpy(key,pResponse);
			pResponse += len;
			len = strlen(pResponse) + 1;
			if( strcmp(key,FirstName) == 0)
				{
				LOGGER ( TXT("FIRSTNAME :") );
			    ParseAndSetL(pResponse,len,*searchInfo, EFirstName);
				}
			else if( strcmp(key,LastName) == 0 )
				{
				LOGGER ( TXT("LASTNAME :"));
				ParseAndSetL(pResponse,len,*searchInfo, ELastName);
				}
			else if( strcmp(key,Jid) == 0 )
				{
				LOGGER ( TXT("JID :") );
				ParseAndSetL(pResponse,len,*searchInfo, EEmailAddress);
				}
			pResponse += len;
			CleanupStack::PopAndDestroy ();// key			
			}
		fieldlist->AddObjectL ( searchInfo );	
		CleanupStack::Pop();//searchInfo
		CleanupStack::PopAndDestroy(pOrigResponse) ;//pOrigResponse	
		datacount = iConnMan.DataHandler().SearchDataCount();
		}
	iConnMan.DataHandler().ResponseL ( 5 ); // this removes the operation from the array
	identity->SetIdentityL(*iSearchId );
	iConnMan.GetSearchHost().SearchFeatureDataAccess().HandleSearchResultsL ( identity,fieldlist );
	iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KErrNone );
	CleanupStack::Pop ( 2 );//identity,fieldlist
	delete this;

	LOGGER ( TXT("CSearchrequest::RunL End") );
	}

// ---------------------------------------------------------------------------
// CSearchrequest::RunError
// ---------------------------------------------------------------------------
//
TInt CSearchrequest::RunError( TInt  aError )
    {
    LOGGER ( TXT("CSearchrequest::RunError : %d  Start"), aError );
    
    iConnMan.HandleToHost().HandleRequestCompleted( iRequestId, aError );
    TRAP_IGNORE(iConnMan.DataHandler().ResponseL ( 5 ));	 // this removes the operation from the array
    delete this;
	LOGGER ( TXT("CSearchrequest::RunError End") );
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// CSearchrequest::SearchL
// ---------------------------------------------------------------------------
//
void CSearchrequest::SearchL( const MXIMPIdentity& aSearchId,
							  const RPointerArray< MSearchElement >& aObjs,
							  TInt  /*aSearchLimit*/)
	{
    LOGGER ( TXT("CSearchrequest::SearchL Start") );
    char *smsg = NULL;
	char *tmpmsg = NULL;
	message_hdr_req msgHdr = {0,};
	int userLen = 0;
	int totalLen = 0;
	smsg = ( char* ) User::AllocLC(MAX_MSG_SIZE);
	memset ( smsg, '\0', MAX_MSG_SIZE );
	msgHdr.message_type = ESearch;
	memcpy ( smsg, &msgHdr, sizeof ( message_hdr_req ) );
	
	HBufC* keyStr = NULL;//HBufC::NewL( 1024 );
	
	CSearchKeyStore& keyStore = iConnMan.GetSearchKeyStore();
	
	totalLen += sizeof( message_hdr_req );

	TInt elementCount=aObjs.Count();	
	
	for (TInt i=0; i< elementCount; ++i)
		{
		const MSearchElement* searchElement = aObjs[i];
		
			switch( searchElement->GetSearchKey() )
			{
			case EUserFirstName:
				{
				keyStr = keyStore.GetLabelFromEnumL( EUserFirstName );
				
				break;	
				}
	            
			case EUser:
				{
				keyStr = keyStore.GetLabelFromEnumL( EUser );
				
				break;	
				}
	            
			case EUserLastName:
				{
				keyStr = keyStore.GetLabelFromEnumL( EUserLastName );
				
				break;	
				}
				
			case EUserMiddleName:
				{
				keyStr = keyStore.GetLabelFromEnumL( EUserMiddleName );
				
				break;	
				}
				
			case EUserFullName:
				{
				keyStr = keyStore.GetLabelFromEnumL( EUserFullName );
				
				break;	
				}
				
			case EUserCountry:
				{
				keyStr = keyStore.GetLabelFromEnumL( EUserCountry );
				
				break;	
				}
				
			case EUserCity:
				{
				keyStr = keyStore.GetLabelFromEnumL( EUserCity );
				
				break;	
				}
				
			case EBirthday:
				{
				keyStr = keyStore.GetLabelFromEnumL( EBirthday );
				
				break;	
				}
				
			case EState:
				{
				keyStr = keyStore.GetLabelFromEnumL( EState );
				
				break;	
				}
				
			case EUserEmailAddress:
				{
				keyStr = keyStore.GetLabelFromEnumL( EUserEmailAddress );
				
				break;	
				}
				
			case EUserNickName:
				{
				keyStr = keyStore.GetLabelFromEnumL( EUserNickName );
				
				break;	
				}
				
			case EOrganisation:
				{
				keyStr = keyStore.GetLabelFromEnumL( EOrganisation );
				
				break;	
				}
				
			case EOrganisationUnit:
				{
				keyStr = keyStore.GetLabelFromEnumL( EOrganisationUnit );
				
				break;	
				}
	            
			case  EReadLabel: 
				{
				//If key is not supported(case of not localized string)
				keyStr = searchElement->GetSearchLabel().Identity().AllocL();
				
				break;	
				}
			default:
				{
				//If any other case just continue with next one
				continue;					
				}
			}	
		
		if ( NULL == keyStr )
			{
			continue;	
			}
		//Add key
		CleanupStack::PushL( keyStr );
		
		charFormatData tmpmsgData = OssProtocolAdapUtils::ConvertTUint16ToCharLC( *keyStr );
	    tmpmsg = tmpmsgData.data;
	    userLen = tmpmsgData.dataSize;
			 
		 if ( totalLen + userLen > MAX_MSG_SIZE ) 
		    	{
				User::Leave(KErrArgument);		
		    	}

		memcpy ( smsg + totalLen, tmpmsg, userLen );

    	totalLen += userLen;
		
		//Add value
		
			
		
		charFormatData tmpmsgDataValue = OssProtocolAdapUtils::ConvertTUint16ToCharLC( 
					searchElement->GetSearchId().Identity() );
					
	    tmpmsg = tmpmsgDataValue.data;
	    userLen = tmpmsgDataValue.dataSize;
			 
		 if ( totalLen + userLen > MAX_MSG_SIZE ) 
		    	{
				User::Leave(KErrArgument);		
		    	}

		memcpy ( smsg + totalLen, tmpmsg, userLen );

    	totalLen += userLen;
    	
    	CleanupStack::PopAndDestroy ( 3 );//For keyStr, tmpmsgData, tmpmsgDataValue
    	
		} // end  : for loop
	iSendId = iConnMan.DataHandler().SendDataL ( iStatus, smsg, totalLen++ );

	delete iSearchId;	
	iSearchId=NULL;
    iSearchId=aSearchId.Identity().AllocL();
	// signal the scheduler
	SetActive();
	CleanupStack::PopAndDestroy ( 1 );//smsg
	LOGGER ( TXT("CSearchrequest::SearchL End") );
		
	}
	
// ---------------------------------------------------------------------------
// CSearchrequest::SearchUtil
// ---------------------------------------------------------------------------
//
void CSearchrequest::ParseAndSetL(char* aResponse, TInt /*alen*/, MSearchInfo& aSearchInfo, TInfoType aKeytype) 
	{
    char* keyvalue =  aResponse;
	HBufC16* key_value = OssProtocolAdapUtils::ConvertCharToTUint16LC( keyvalue );
	aSearchInfo.SetFieldInfoL(*key_value,aKeytype);
	CleanupStack::PopAndDestroy( key_value );
	}
	
// End of file

