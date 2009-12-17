/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ossadapmtBlocks.cpp
*
*/



// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include "ossadapmt.h"
#include <ximpidentity.h>
#include <ximpclient.h>
#include <ximpcontext.h>
#include <ximpobjectfactory.h>
#include <ximpcontextobserver.h>
#include <ximpcontextstateevent.h>
#include <ximpprotocolinfo.h>
#include <ximpfeatureinfo.h>
#include <ximpserviceinfo.h>
#include "uscontextobserver.h"
#include <presencefeatures.h>
#include <imfeatures.h>
#include <presentitygroups.h>
#include <imconversation.h>
#include <imobjectfactory.h>
#include <imconversationinfo.h>
#include "cuserafter.h"
#include <presencepublishing.h>
#include <presencewatching.h>
#include <presenceinfofilter.h>
#include <presenceinfo.h>
#include <presenceobjectfactory.h>
#include <servicepresenceinfo.h>
#include <personpresenceinfo.h>
#include <presenceinfofield.h>
#include <presenceinfofieldcollection.h>
#include <presenceinfofieldvalueenum.h>
#include <presenceinfofieldvaluetext.h>
#include <presenceinfofieldvaluebinary.h>
#include <presenceauthorization.h>
#include <utf.h>
#include <search.h>
#include <searchfeature.h>
#include <searchobjectfactory.h>
#include <searchelement.h>
//#include "immessageinfoimp.h"
const TInt KProtocolUid = 0x101FB3E7; // 0x10282EE9;
_LIT8( KInstantMessaging, "instant-messaging");

// StatusText attribute value tags
_LIT8( KStatusTextfield, "StatusText");

// Online Status attribute value tags
_LIT8( KOnlineStatusfield, "OnlineStatus" );
_LIT ( KMsgId, "MessageID1" );
_LIT( KContact1, "meco5555@gmail.com");

// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def

// LOCAL CONSTANTS AND MACROS
//const ?type ?constant_var = ?constant;
//#define ?macro_name ?macro_def

// MODULE DATA STRUCTURES
//enum ?declaration
//typedef ?declaration

// LOCAL FUNCTION PROTOTYPES
//?type ?function_name( ?arg_type, ?arg_type );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ?function_name ?description.
// ?description
// Returns: ?value_1: ?description
//          ?value_n: ?description_line1
//                    ?description_line2
// -----------------------------------------------------------------------------
//
/*
?type ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg)  // ?description
    {

    ?code  // ?comment

    // ?comment
    ?code
    }
*/

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Cossadapmt::Delete
// Delete here all resources allocated and opened from test methods.
// Called from destructor.
// -----------------------------------------------------------------------------
//
void Cossadapmt::Delete()
	{

	}

// -----------------------------------------------------------------------------
// Cossadapmt::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::RunMethodL (
    CStifItemParser& aItem )
	{

	static TStifFunctionInfo const KFunctions[] =
		{
		// Copy this line for every implemented function.
		// First string is the function name used in TestScripter script file.
		// Second is the actual implementation member function.
		ENTRY ( "SecondSearchL",Cossadapmt::SecondSearchL ), 
		ENTRY ( "Login", Cossadapmt::LoginL ),
		ENTRY ( "Login_InvalidData", Cossadapmt::Login_InvalidDataL ),
		ENTRY ( "AcceptnotificationRequest", Cossadapmt::AcceptnotificationRequestL ),
		ENTRY ( "Login_Logout_sequential", Cossadapmt::LoginLogout_LoginLogoutL ),
		ENTRY ( "Login_8Hrs_Logout", Cossadapmt::Login8HrsLogoutL ),
		ENTRY ( "Unbind", Cossadapmt::UnBindL ),
		ENTRY ( "GetContacts", Cossadapmt::GetContactsL ),
		ENTRY ( "Add_conatct", Cossadapmt::AddConatctL ),
		ENTRY ( "Add_Blank_Conatct", Cossadapmt::AddBlankConatctL ),
		ENTRY ( "Add_Blank_Conatct1", Cossadapmt::AddBlankConatct1L ),
		ENTRY ( "Delete_conatct", Cossadapmt::DeleteConatctL ),
		ENTRY ( "Delete_Blank_Conatct", Cossadapmt::DeleteBlankConatctL ),
		ENTRY ( "Sendmessage", Cossadapmt::SendMessageL ),
		ENTRY ( "Sendemptymessage", Cossadapmt::SendEmptyMessageL ),
		ENTRY ( "Send_ten_messages", Cossadapmt::SendTenMessageL ),
		ENTRY ( "Send_twenty_messages", Cossadapmt::SendTwentyMessageL ),
		ENTRY ( "Sendmessage_multiplecontacts", Cossadapmt::SendMessage_MultipleContactsL ),
		ENTRY ( "Receivemessage", Cossadapmt::ReceiveMessageL ),
		ENTRY ( "Receiveemptymessage", Cossadapmt::ReceiveEmptyMessageL ),
		ENTRY ( "Receive_ten_messages", Cossadapmt::ReceiveTenMessageL ),
		ENTRY ( "Receive_twenty_message", Cossadapmt::ReceiveTwentyMessageL ),
		ENTRY ( "Publish_ownpresence", Cossadapmt::PublishOwnPresenceL ),
		ENTRY ( "Publish_ownpresence_emptytext", Cossadapmt::PublishOwnPresenceEmptyTextL ),
		ENTRY ( "RejectAddnotificationRequest", Cossadapmt::RejectAddnotificationRequestL ),
		ENTRY ( "ImOperations_Coverage", Cossadapmt::ImOperationsCoverageL ),
		
		ENTRY ( "SimpleSearchL", Cossadapmt::SimpleSearchL ),
		ENTRY ( "MultipleSearchL", Cossadapmt::MultipleSearchL ),
		ENTRY ( "NoResultSearchL", Cossadapmt::NoResultSearchL ),
		ENTRY ( "ManyResultsSearchL", Cossadapmt::ManyResultsSearchL ),
		ENTRY ( "BlankSearchL", Cossadapmt::BlankSearchL ),
		ENTRY ( "MaxCharSearchL", Cossadapmt::MaxCharSearchL ),
		ENTRY ( "SpecialCharSearchL", Cossadapmt::SpecialCharSearchL ),
		ENTRY ( "SearchEmailIDL",Cossadapmt::SearchEmailIDL ),
		ENTRY ( "SearchAndAddToIML",Cossadapmt::SearchAndAddToIML ), 
		ENTRY ( "GetSearchKeyEnumL",Cossadapmt::GetSearchKeyEnumL ), 
		ENTRY ( "GetSearchKeyLabelL",Cossadapmt::GetSearchKeyLabelL ), 
		ENTRY ( "GetSearchKeyEnumNLabelL",Cossadapmt::GetSearchKeyEnumNLabelL ), 
        ENTRY ( "SetAvtar",Cossadapmt::SetAvtarL ), 
		//ADD NEW ENTRY HERE
		// [test cases entries] - Do not remove

		};

	const TInt count = sizeof ( KFunctions ) /
	                   sizeof ( TStifFunctionInfo );

	return RunInternalL ( KFunctions, count, aItem );

	}



// -----------------------------------------------------------------------------
// Cossadapmt::SearchL
// Search test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::SearchL ( CStifItemParser& aItem, TSearch aSearchType )
	{



	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::LoginL() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );

   	
    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;


	MSearchFeature* srFeature = NULL;
	srFeature = MSearchFeature::NewL ( presecenCtx );
//	CleanupStack::PushL( srFeature );
	
	MSearch& srch=srFeature->Search();
	MSearchObjectFactory& searchObjFact=srFeature->SearchObjectFactory();


	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );
	
//------------------------------------------Fetch Start------------------------------------------
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );
	MXIMPIdentity* newGroupId = presecenCtx->ObjectFactory().NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;
	MXIMPIdentity* newmemberId = presecenCtx->ObjectFactory().NewIdentityLC();

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "list" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;


	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );

	CUserAfter::AfterL ( 1000000 );

//------------------------------------------Fetch End------------------------------------------


	MXIMPIdentity* searchId = presecenCtx->ObjectFactory().NewIdentityLC();
    searchId->SetIdentityL(_L("SEARCH"));
    
    MXIMPIdentity* firstId = presecenCtx->ObjectFactory().NewIdentityLC();
    
    
    MSearchElement* srchElement1=searchObjFact.NewSearchElementLC();
    
    
    MXIMPIdentity* secondId = presecenCtx->ObjectFactory().NewIdentityLC();
    
    
    MSearchElement* srchElement2=searchObjFact.NewSearchElementLC();
    
    
    RPointerArray< MSearchElement > searchList;
    CleanupClosePushL( searchList );
    
	switch ( aSearchType ) 
		{
		
		case EGetSearchKeyEnum:
			{
			
			req = srch.GetSearchKeysL();
			eventObserver->WaitOpToCompleteL ( req );
			
			firstId->SetIdentityL(_L("james"));
			srchElement1->SetRequestL( *firstId, EUserFirstName );
			
			searchList.Append(srchElement1);
			
			req=srch.SearchL(*searchId,searchList,10 );				
			break;
			
			}
		
		
		case EGetSearchKeyLabel:
			{
			
			req = srch.GetSearchKeysL();
			eventObserver->WaitOpToCompleteL ( req );
			
			MXIMPIdentity* label = presecenCtx->ObjectFactory().NewIdentityLC();
			label->SetIdentityL( _L( "Family Name" ) );
			
			secondId->SetIdentityL(_L("BOND"));
			
		    srchElement2->SetRequestL( *secondId, *label );
		    
			searchList.Append( srchElement1 );
			searchList.Append( srchElement2 ); 
		    
		    req=srch.SearchL(*searchId,searchList,10 );
		    
		    CleanupStack::PopAndDestroy ();
		    
			break;		
			
			}
		
		
		case EGetSearchKeyEnumNLabel:
			{
			
			req = srch.GetSearchKeysL();
			eventObserver->WaitOpToCompleteL ( req );
			
			
			firstId->SetIdentityL(_L("james"));
			srchElement1->SetRequestL( *firstId, EUserFirstName );
			
			secondId->SetIdentityL(_L("BOND"));
			
			MXIMPIdentity* label = presecenCtx->ObjectFactory().NewIdentityLC();
			label->SetIdentityL( _L( "Family Name" ) );
			
		    srchElement2->SetRequestL( *secondId, *label );
		    
			searchList.Append( srchElement1 );
			searchList.Append( srchElement2 ); 
		    
		    req=srch.SearchL(*searchId,searchList,10 );
		    
		    CleanupStack::PopAndDestroy ();
		    
			break;		
			}
		
		
		case ESimpleSearch :
			{
			
			req = srch.GetSearchKeysL();
			eventObserver->WaitOpToCompleteL ( req );
			
			firstId->SetIdentityL(_L("james"));
			srchElement1->SetRequestL( *firstId, EUserFirstName );
			
			searchList.Append(srchElement1);
			
			req=srch.SearchL(*searchId,searchList,10 );
			
			break;	
			}
		
		
		case EMultipleSearch :
			{
			
			req = srch.GetSearchKeysL();
			eventObserver->WaitOpToCompleteL ( req );
			
			
			firstId->SetIdentityL(_L("james"));
			srchElement1->SetRequestL( *firstId, EUserFirstName );
			
			secondId->SetIdentityL(_L("BOND"));
			
			MXIMPIdentity* label = presecenCtx->ObjectFactory().NewIdentityLC();
			label->SetIdentityL( _L( "Family Name" ) );
			
		    srchElement2->SetRequestL( *secondId, *label );
		    
			searchList.Append( srchElement1 );
			searchList.Append( srchElement2 ); 
		    
		    req=srch.SearchL(*searchId,searchList,10 );
		    
		    CleanupStack::PopAndDestroy ();
		    		
			break;	
			}
		
		
		case ESearchNoResults :
			{
			firstId->SetIdentityL(_L("Santhosh"));
			srchElement1->SetRequestL( *firstId, EUserFirstName );
			
			secondId->SetIdentityL(_L("I C"));
		    srchElement2->SetRequestL( *secondId, EUserLastName );
		    
			searchList.Append( srchElement1 );
			searchList.Append( srchElement2 ); 
		    
		    req=srch.SearchL(*searchId,searchList,10 );
			break;	
			}
	
		
		case ESearchManyResults :
			{
			firstId->SetIdentityL(_L("a"));
			srchElement1->SetRequestL( *firstId, EUserFirstName );
			
			searchList.Append(srchElement1);
			
			req=srch.SearchL(*searchId,searchList,10 );
			
			break;	
			}
		
		
		case ESearchBlank :
			{
			firstId->SetIdentityL(_L(""));
			srchElement1->SetRequestL( *firstId, EUserFirstName );
			
			searchList.Append(srchElement1);
			
			req=srch.SearchL(*searchId,searchList,10 );	
			break;
			}
		
		
		
		case ESearchMaxChars :
			{
			firstId->SetIdentityL( _L( "fbg agh ggd sad ghda gh dhg hgasdg dh jggd gsdg g \
			kjdg g gsd gfhsdg fhasgd hasdh ghfgahfg hgsdg dg gdgsgkj" ) );
			srchElement1->SetRequestL( *firstId, EUserFirstName );
			
			searchList.Append( srchElement1 );
			
			req=srch.SearchL( *searchId,searchList,10 );
			break;	
			}
		
		
		case ESearchSpecialChars :
			{
			firstId->SetIdentityL( _L( "*%#@$%^#%^&^^%)(" ) );
			srchElement1->SetRequestL( *firstId, EUserFirstName );
			
			searchList.Append( srchElement1 );
			
			req=srch.SearchL( *searchId,searchList,10 );
			
			break;	
			}
		case  ESearchEmailid:
			{
			firstId->SetIdentityL( _L( "wordjames@chat.gizmoproject.com" ) );
			srchElement1->SetRequestL( *firstId, EUserFirstName );
			
			searchList.Append( srchElement1 );
			
			req=srch.SearchL( *searchId,searchList,10 );
			break;	
			} 
			
		case  ESearchAndAddToIm:
			{
			firstId->SetIdentityL( _L( "sharath" ) );
			srchElement1->SetRequestL( *firstId, EUserFirstName );
			
			searchList.Append( srchElement1 );
			
			req=srch.SearchL( *searchId,searchList,10 );
			//Wait for search to complete
			eventObserver->WaitOpToCompleteL( req );
			CUserAfter::AfterL ( 5000000 );
			
			//And then call the AddToContactList
			RFs fs;
			RFile file;
			TBuf8<100> buf;
			User::LeaveIfError( fs.Connect() );
			User::LeaveIfError( file.Open( fs, KAddContactFileName, EFileRead ) );
			file.Read( buf );
			file.Close();
			fs.Close();
			TBuf16<100> h_buf;
			CnvUtfConverter::ConvertToUnicodeFromUtf8( h_buf, 
											buf );
//-------------------Adding Contact Start-----------------------------------------			
			
			newmemberId->SetIdentityL ( h_buf );
			
			req = groups.AddPresentityGroupMemberL(
			                    *newGroupId,
			                    *newmemberId,
			                    KNullDesC()) ;	

			//eventObserver->WaitOpToCompleteL ( req );
			//CUserAfter::AfterL ( 5000000 );
			//Wait at the below eventObserver->WaitOpToCompleteL( req );
			
			
//-------------------Adding Contact End-----------------------------------------						
			break;	
			}
		case ESecondSearch:
			{
			
			firstId->SetIdentityL(_L("sharath"));
			srchElement1->SetRequestL( *firstId, EUserFirstName );
			
			searchList.Append(srchElement1);
			
			req=srch.SearchL(*searchId,searchList,10 );
			
			eventObserver->WaitOpToCompleteL( req );
					
			CUserAfter::AfterL(100000);
			searchList.Reset();
			
			//Second Search
			secondId->SetIdentityL(_L("Jeppu"));
			srchElement1->SetRequestL( *secondId, EUserLastName );
			
			searchList.Append(srchElement1);
			
			req=srch.SearchL(*searchId,searchList,10 );
			
			break;
			}
					
		}
    
    CleanupStack::PopAndDestroy (); //newmemberId
	CleanupStack::PopAndDestroy ();//newGroupId
	CleanupStack::PopAndDestroy ();//presenceFeatures
    
	CleanupStack::PopAndDestroy (); //
	CleanupStack::PopAndDestroy ();
	CleanupStack::PopAndDestroy ();
	
	CleanupStack::PopAndDestroy ();
	CleanupStack::PopAndDestroy ();
	
	CleanupStack::PopAndDestroy ();

	eventObserver->WaitOpToCompleteL( req );
	//Unbind the context and wait completion
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end" ) );

//	CleanupStack::PopAndDestroy ();//Search feature plugin 
	CleanupStack::PopAndDestroy ( 3 ); //presecenCtx,eventObserver,ximpClient
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::SearchL() End" ) );
	return KErrNone;

	}
// -----------------------------------------------------------------------------
// Cossadapmt::GetSearchKeyEnum
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::GetSearchKeyEnumL( CStifItemParser& aItem )
	{
	return SearchL ( aItem, EGetSearchKeyEnum );	
	}

// -----------------------------------------------------------------------------
// Cossadapmt::GetSearchKeyLabel
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::GetSearchKeyLabelL( CStifItemParser& aItem )
	{
	return SearchL ( aItem, EGetSearchKeyLabel );	
	}

// -----------------------------------------------------------------------------
// Cossadapmt::GetSearchKeyEnumNLabel
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//	
TInt Cossadapmt::GetSearchKeyEnumNLabelL( CStifItemParser& aItem )
	{
	return SearchL ( aItem, EGetSearchKeyEnumNLabel );	
	}

// -----------------------------------------------------------------------------
// Cossadapmt::SearchAndAddToIML
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt Cossadapmt::SecondSearchL( CStifItemParser& aItem )
	{
	return SearchL ( aItem, ESecondSearch );
	}


// -----------------------------------------------------------------------------
// Cossadapmt::SearchAndAddToIML
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt Cossadapmt::SearchAndAddToIML( CStifItemParser& aItem )
	{
	return SearchL ( aItem, ESearchAndAddToIm );
	}

// -----------------------------------------------------------------------------
// Cossadapmt::SimpleSearchL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt Cossadapmt::SimpleSearchL( CStifItemParser& aItem )
	{
	return SearchL ( aItem, ESimpleSearch );
	}
// -----------------------------------------------------------------------------
// Cossadapmt::MultipleSearchL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//	
TInt Cossadapmt::MultipleSearchL( CStifItemParser& aItem )
	{
	return SearchL ( aItem, EMultipleSearch );	
	}
// -----------------------------------------------------------------------------
// Cossadapmt::NoResultSearchL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::NoResultSearchL( CStifItemParser& aItem )
	{
	return SearchL ( aItem, ESearchNoResults );	
	}
// -----------------------------------------------------------------------------
// Cossadapmt::ManyResultsSearchL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::ManyResultsSearchL( CStifItemParser& aItem )
	{
	return SearchL ( aItem, ESearchManyResults );	
	}
// -----------------------------------------------------------------------------
// Cossadapmt::BlankSearchL.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::BlankSearchL( CStifItemParser& aItem )
	{
	return SearchL ( aItem, ESearchBlank );	
	}
// -----------------------------------------------------------------------------
// Cossadapmt::MaxCharSearchL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::MaxCharSearchL( CStifItemParser& aItem )
	{
	return SearchL ( aItem, ESearchMaxChars );	
	}
// -----------------------------------------------------------------------------
// Cossadapmt::SpecialCharSearchL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//	
TInt Cossadapmt::SpecialCharSearchL( CStifItemParser& aItem )
	{
	return SearchL ( aItem, ESearchSpecialChars );	
	}
// -----------------------------------------------------------------------------
// Cossadapmt::SearchEmailIDL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//	
TInt Cossadapmt::SearchEmailIDL( CStifItemParser& aItem )
	{
	return SearchL ( aItem, ESearchEmailid );	
	}
// -----------------------------------------------------------------------------
// Cossadapmt::LoginL
// Login test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::LoginL ( CStifItemParser& aItem )
	{



	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::LoginL() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );


	//Unbind the context and wait completion
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end" ) );

	CleanupStack::PopAndDestroy ( 3 ); //presecenCtx,eventObserver,ximpClient
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::LoginL() End" ) );
	return KErrNone;

	}
// -----------------------------------------------------------------------------
// Cossadapmt::Login_InvalidDataL
// Login test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::Login_InvalidDataL ( CStifItemParser& aItem )
	{



	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::Login_InvalidDataL() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );

	CleanupStack::PopAndDestroy ( 3 ); //presecenCtx,eventObserver,ximpClient
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::Login_InvalidDataL() End" ) );
	return KErrNone;

	}
// -----------------------------------------------------------------------------
// Cossadapmt::Login8HrsLogoutL
// Login test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::Login8HrsLogoutL ( CStifItemParser& aItem )
	{



	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::Login8HrsLogoutL() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );


    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );
	CUserAfter::After8HrsL ();

	//Unbind the context and wait completion
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end" ) );

	CleanupStack::PopAndDestroy ( 3 ); //presecenCtx,eventObserver,ximpClient
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::Login8HrsLogoutL() End" ) );
	return KErrNone;

	}
	
// -----------------------------------------------------------------------------
// Cossadapmt::LoginLogout_LoginLogoutL
// Login test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::LoginLogout_LoginLogoutL ( CStifItemParser& aItem )
	{



	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::LoginLogout_Log() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );
    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called - Sequence 1" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );

	//Unbind the context and wait completion
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end- Sequence 1 complete" ) );
	

/// Login --- Logout  - Sequence 2
	//Bind context to desired presence service
	req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called  - Sequence 2" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );

	//Unbind the context and wait completion
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end - Sequence 2 complete" ) );


	CleanupStack::PopAndDestroy ( 3 ); //presecenCtx,eventObserver,ximpClient
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::LoginLogout_Log() End" ) );
	return KErrNone;

	}
	

// -----------------------------------------------------------------------------
// Cossadapmt::GetContactsL
// Fetch contacts test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::GetContactsL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::GetContactsL() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );
	TOssAdapMtLogger::Log ( _L ( "Loading presence plugin Done" ) );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "list" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );

	
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );

	CUserAfter::AfterL ( 1000000 );
	//Unbind the context and wait completion
	req = presecenCtx->UnbindL();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->UnbindL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end" ) );

	CleanupStack::PopAndDestroy ( 5 );//newGroupId,presenceFeatures,presecenCtx,eventObserver,ximpClient
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::GetContactsL() end" ) );

	return KErrNone;

	}
// -----------------------------------------------------------------------------
// Cossadapmt::AddConatctL
// AddConatctL contacts test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::AddConatctL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::AddContactsL() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );
	TOssAdapMtLogger::Log ( _L ( "Loading presence plugin Done" ) );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;
	MXIMPIdentity* newmemberId = objFactory.NewIdentityLC();

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "list" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    TPtrC               contact;
    
	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );
	aItem.GetNextString ( contact );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );

	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );

	CUserAfter::AfterL ( 1000000 );
	
	 newmemberId->SetIdentityL ( contact );
	
	req = groups.AddPresentityGroupMemberL(
	                    *newGroupId,
	                    *newmemberId,
	                    KNullDesC()) ;	

	eventObserver->WaitOpToCompleteL ( req );
	CUserAfter::AfterL ( 5000000 );
	 CleanupStack::PopAndDestroy();//newmemberId
	//Unbind the context and wait completion
	req = presecenCtx->UnbindL();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->UnbindL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end" ) );

	CleanupStack::PopAndDestroy ( 5 );//newGroupId,presenceFeatures,presecenCtx,eventObserver,ximpClient
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::AddContactsL() end" ) );

	return KErrNone;

	}
// -----------------------------------------------------------------------------
// Cossadapmt::AddBlankConatctL
// AddConatctL contacts test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::AddBlankConatctL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::AddBlankConatctL() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );
	TOssAdapMtLogger::Log ( _L ( "Loading presence plugin Done" ) );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;
	MXIMPIdentity* newmemberId = objFactory.NewIdentityLC();

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "list" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    
	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );

	
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );

	CUserAfter::AfterL ( 1000000 );
	_LIT ( KBlankContact, "" );
	 newmemberId->SetIdentityL ( KBlankContact );
	 
	
	req = groups.AddPresentityGroupMemberL(
	                    *newGroupId,
	                    *newmemberId,
	                    KNullDesC()) ;	

	eventObserver->WaitOpToCompleteL ( req );
	//Unbind the context and wait completion
	req = presecenCtx->UnbindL();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->UnbindL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end" ) );
	CleanupStack::PopAndDestroy();
	CleanupStack::PopAndDestroy ( 5 );//newGroupId,presenceFeatures,presecenCtx,eventObserver,ximpClient
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::AddBlankConatctL() end" ) );

	return KErrNone;

	}
// -----------------------------------------------------------------------------
// Cossadapmt::AddBlankConatct1L
// AddConatctL contacts test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::AddBlankConatct1L ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::AddBlankConatctL() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );
	TOssAdapMtLogger::Log ( _L ( "Loading presence plugin Done" ) );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;
	MXIMPIdentity* newmemberId = objFactory.NewIdentityLC();

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "list" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    
	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );

	
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );

	CUserAfter::AfterL ( 1000000 );
	_LIT ( KBlankContact, "" );
	 newmemberId->SetIdentityL ( KBlankContact );
	
	req = groups.AddPresentityGroupMemberL(
	                    *newGroupId,
	                    *newmemberId,
	                    KNullDesC()) ;	

	eventObserver->WaitOpToCompleteL ( req );
	CleanupStack::PopAndDestroy();  //newmemberId
	//Unbind the context and wait completion
	req = presecenCtx->UnbindL();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->UnbindL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end" ) );

	CleanupStack::PopAndDestroy ( 5 );//newGroupId,presenceFeatures,presecenCtx,eventObserver,ximpClient
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::AddBlankConatctL() end" ) );

	return KErrNone;

	}	
// -----------------------------------------------------------------------------
// Cossadapmt::DeleteConatctL
// DeleteConatctL contacts test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::DeleteConatctL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::DeleteConatctL() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );
	TOssAdapMtLogger::Log ( _L ( "Loading presence plugin Done" ) );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;
	MXIMPIdentity* newmemberId = objFactory.NewIdentityLC();

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "list" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    TPtrC               contact;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );
	aItem.GetNextString ( contact );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );

	
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );

	CUserAfter::AfterL ( 1000000 );
	
	newmemberId->SetIdentityL ( contact );
	
	req = groups.RemovePresentityGroupMemberL(
	                    *newGroupId,
	                    *newmemberId) ;	

	eventObserver->WaitOpToCompleteL ( req );
	CleanupStack::PopAndDestroy();//newmemberId
	//Unbind the context and wait completion
	req = presecenCtx->UnbindL();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->UnbindL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end" ) );

	CleanupStack::PopAndDestroy ( 5 );//newGroupId,presenceFeatures,presecenCtx,eventObserver,ximpClient
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::DeleteConatctL() end" ) );

	return KErrNone;

	}
// -----------------------------------------------------------------------------
// Cossadapmt::DeleteBlankConatctL
// DeleteConatctL contacts test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::DeleteBlankConatctL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::DeleteBlankConatctL() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );
	TOssAdapMtLogger::Log ( _L ( "Loading presence plugin Done" ) );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;
	MXIMPIdentity* newmemberId = objFactory.NewIdentityLC();

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "list" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );

	
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );

	CUserAfter::AfterL ( 1000000 );
	_LIT ( KBlankContact, "" );
	newmemberId->SetIdentityL (KBlankContact);
	
	req = groups.RemovePresentityGroupMemberL(
	                    *newGroupId,
	                    *newmemberId) ;	

	eventObserver->WaitOpToCompleteL ( req );
	CleanupStack::PopAndDestroy();  //newmemberId	
	//Unbind the context and wait completion
	req = presecenCtx->UnbindL();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->UnbindL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end" ) );

	CleanupStack::PopAndDestroy ( 5 );//newGroupId,presenceFeatures,presecenCtx,eventObserver,ximpClient
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::DeleteBlankConatctL() end" ) );

	return KErrNone;

	}
// -----------------------------------------------------------------------------
// Cossadapmt::UnBindL
// UnBind test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::UnBindL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::UnBindL() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
                     
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );


	//Unbind the context and wait completion
	req = presecenCtx->UnbindL();
	eventObserver->WaitOpToCompleteL( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end" ) );


	CleanupStack::Pop ( 3 ); //presecenCtx,eventObserver,ximpClient
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::UnBindL() End" ) );
	return KErrNone;


	}

// -----------------------------------------------------------------------------
// Cossadapmt::SendMessageL
// SendMessage test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::SendMessageL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::SendMessageL() start" ) );
	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );
	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();
	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	//Bind context to desired presence service
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    TPtrC               message;
    TPtrC               recipient;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );
	aItem.GetNextString ( message );
	aItem.GetNextString ( recipient );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called\n" ) );
	eventObserver->WaitOpToCompleteL ( req );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
   CleanupStack::PopAndDestroy(2); //newGroupId,presenceFeatures

	CUserAfter::AfterL ( 1000000 );
	//Bind context to desired presence service
	MImFeatures* imFeatures = NULL;
	imFeatures = MImFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( imFeatures );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imFeatures created\n" ) );
	MImConversation& imconversation = imFeatures->ImConversation();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imconversation created\n" ) );
	MImConversationInfo *aImMessage = NULL;
	aImMessage = imFeatures->ImObjectFactory().NewImConversationInfoLC();
	MXIMPIdentity* identity = objFactory.NewIdentityLC();
	identity->SetIdentityL ( KMsgId );
	aImMessage->SetMessageIdL ( identity );
	aImMessage->SetTextMessageL ( message );
	CDesCArrayFlat* aRecipients = new ( ELeave ) CDesCArrayFlat ( 2 );
	CleanupStack::PushL ( aRecipients );  
	aRecipients->AppendL ( recipient );//userid's
	aImMessage->SetRecipientL ( aRecipients );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::before sendmessage called\n" ) );

	req = imconversation.SendMessageL ( *aImMessage );
	eventObserver->WaitOpToCompleteL ( req );
	CleanupStack::Pop ( 3 );//identity,aRecipients,aImMessage
	//Unbind the context and wait completion
	CUserAfter::AfterL ( 2000000 );
  	req = presecenCtx->UnbindL();
  	eventObserver->WaitOpToCompleteL( req );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::message sent\n " ) );
	CleanupStack::PopAndDestroy(4); //imFeatures,presecenCtx,eventObserver,ximpClient,
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::SendMessageL() end" ) );

	return KErrNone;

	}
// -----------------------------------------------------------------------------
// Cossadapmt::SendEmptyMessageL
// SendMessage test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::SendEmptyMessageL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::SendEmptyMessageL() start" ) );
	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );
	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();
	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	//Bind context to desired presence service
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    TPtrC               recipient;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );
	aItem.GetNextString ( recipient );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called\n" ) );
	eventObserver->WaitOpToCompleteL ( req );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "" );
	_LIT ( KEmptyMessage, "" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
   CleanupStack::PopAndDestroy(2); //newGroupId,presenceFeatures

	CUserAfter::AfterL ( 1000000 );
	//Bind context to desired presence service
	MImFeatures* imFeatures = NULL;
	imFeatures = MImFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( imFeatures );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imFeatures created\n" ) );
	MImConversation& imconversation = imFeatures->ImConversation();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imconversation created\n" ) );
	MImConversationInfo *aImMessage = NULL;
	aImMessage = imFeatures->ImObjectFactory().NewImConversationInfoLC();
	MXIMPIdentity* identity = objFactory.NewIdentityLC();
	identity->SetIdentityL ( KMsgId );
	aImMessage->SetMessageIdL ( identity );
	aImMessage->SetTextMessageL ( KEmptyMessage );
	CDesCArrayFlat* aRecipients = new ( ELeave ) CDesCArrayFlat ( 2 );
	CleanupStack::PushL ( aRecipients );  
	aRecipients->AppendL ( recipient );//userid's
	aImMessage->SetRecipientL ( aRecipients );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::before sendmessage called\n" ) );

	req = imconversation.SendMessageL ( *aImMessage );
	eventObserver->WaitOpToCompleteL ( req );
	CleanupStack::Pop ( 3 );//identity,aRecipients,aImMessage
	//Unbind the context and wait completion
  	req = presecenCtx->UnbindL();
  	eventObserver->WaitOpToCompleteL( req );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::message sent\n " ) );
	CleanupStack::PopAndDestroy(4); //imFeatures,presecenCtx,eventObserver,ximpClient,
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::SendEmptyMessageL() end" ) );

	return KErrNone;

	}	

// -----------------------------------------------------------------------------
// Cossadapmt::SendTenMessageL
// SendMessage test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::SendTenMessageL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::SendTenMessageL() start" ) );
	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );
	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();
	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	//Bind context to desired presence service
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    TPtrC               message;
    TPtrC               recipient;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );
	aItem.GetNextString ( message );
	aItem.GetNextString ( recipient );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called\n" ) );
	eventObserver->WaitOpToCompleteL ( req );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
    CleanupStack::PopAndDestroy(2); //newGroupId,presenceFeatures

	CUserAfter::AfterL ( 1000000 );
	//Bind context to desired presence service
	MImFeatures* imFeatures = NULL;
	imFeatures = MImFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( imFeatures );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imFeatures created\n" ) );
	MImConversation& imconversation = imFeatures->ImConversation();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imconversation created\n" ) );
	MImConversationInfo *aImMessage = NULL;
	aImMessage = imFeatures->ImObjectFactory().NewImConversationInfoLC();
	MXIMPIdentity* identity = objFactory.NewIdentityLC();
	identity->SetIdentityL ( KMsgId );
	aImMessage->SetMessageIdL ( identity );
	aImMessage->SetTextMessageL ( message );
	CDesCArrayFlat* aRecipients = new ( ELeave ) CDesCArrayFlat ( 2 );
	CleanupStack::PushL ( aRecipients );  
	aRecipients->AppendL ( recipient ); //userid's
	aImMessage->SetRecipientL ( aRecipients );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::before sendmessage called\n" ) );

	for ( TInt i = 0;i < 10;i++ )
		{
		req = imconversation.SendMessageL ( *aImMessage );
		eventObserver->WaitOpToCompleteL ( req );

		}
	CleanupStack::Pop ( 3 );//identity,aRecipients,aImMessage

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::message sent\n " ) );
    //Unbind the context and wait completion
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
	CleanupStack::PopAndDestroy(4); //imFeatures,presecenCtx,eventObserver,ximpClient,
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::SendTenMessageL() end" ) );

	return KErrNone;

	}

// -----------------------------------------------------------------------------
// Cossadapmt::SendTwentyMessageL
// SendMessage test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::SendTwentyMessageL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::SendTwentyMessageL() start" ) );
	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );
	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();
	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	//Bind context to desired presence service
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    TPtrC               message;
    TPtrC               recipient;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );
	aItem.GetNextString ( message );
	aItem.GetNextString ( recipient );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called\n" ) );
	eventObserver->WaitOpToCompleteL ( req );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
   CleanupStack::PopAndDestroy(2); //newGroupId,presenceFeatures

	CUserAfter::AfterL ( 1000000 );
	//Bind context to desired presence service
	MImFeatures* imFeatures = NULL;
	imFeatures = MImFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( imFeatures );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imFeatures created\n" ) );
	MImConversation& imconversation = imFeatures->ImConversation();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imconversation created\n" ) );
	MImConversationInfo *aImMessage = NULL;
	aImMessage = imFeatures->ImObjectFactory().NewImConversationInfoLC();
	MXIMPIdentity* identity = objFactory.NewIdentityLC();
	identity->SetIdentityL ( KMsgId );
	aImMessage->SetMessageIdL ( identity );
	aImMessage->SetTextMessageL ( message );
	CDesCArrayFlat* aRecipients = new ( ELeave ) CDesCArrayFlat ( 2 );
	CleanupStack::PushL ( aRecipients );  //userid's
	aRecipients->AppendL ( recipient );
	aImMessage->SetRecipientL ( aRecipients );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::before sendmessage called\n" ) );

	for ( TInt i = 0;i < 20;i++ )
		{
		req = imconversation.SendMessageL ( *aImMessage );
		eventObserver->WaitOpToCompleteL ( req );

		}
	CleanupStack::Pop ( 3 );//identity,aRecipients,aImMessage

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::message sent\n " ) );
    //Unbind the context and wait completion
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
	CleanupStack::PopAndDestroy(4); //imFeatures,presecenCtx,eventObserver,ximpClient,
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::SendTwentyMessageL() end" ) );

	return KErrNone;

	}

// -----------------------------------------------------------------------------
// Cossadapmt::SendMessage_MultipleContactsL
// SendMessage test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::SendMessage_MultipleContactsL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::SendMessage_MultipleContactsL() start" ) );
	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );
	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();
	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	//Bind context to desired presence service
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );

    //read data from cfg file
	TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    TPtrC               message;
    TPtrC               recipient;
    TPtrC               recipient1;
    TPtrC               recipient2;
    TPtrC               recipient3;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );
	aItem.GetNextString ( message );
	aItem.GetNextString ( recipient );
	aItem.GetNextString ( recipient1 );
	aItem.GetNextString ( recipient2 );
	aItem.GetNextString ( recipient3 );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called\n" ) );
	eventObserver->WaitOpToCompleteL ( req );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
    CleanupStack::PopAndDestroy(2); //newGroupId,presenceFeatures

	CUserAfter::AfterL ( 1000000 );
	//Bind context to desired presence service
	MImFeatures* imFeatures = NULL;
	imFeatures = MImFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( imFeatures );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imFeatures created\n" ) );
	MImConversation& imconversation = imFeatures->ImConversation();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imconversation created\n" ) );
	MImConversationInfo *aImMessage = NULL;
	aImMessage = imFeatures->ImObjectFactory().NewImConversationInfoLC();
	MXIMPIdentity* identity = objFactory.NewIdentityLC();
	identity->SetIdentityL ( KMsgId );
	aImMessage->SetMessageIdL ( identity );
	aImMessage->SetTextMessageL ( message );
	CDesCArrayFlat* aRecipients = new ( ELeave ) CDesCArrayFlat ( 2 );
	CleanupStack::PushL ( aRecipients ); 
	aRecipients->AppendL ( recipient );  //userid's
	aRecipients->AppendL ( recipient1 );
	aRecipients->AppendL ( recipient2 );
	aRecipients->AppendL ( recipient3 );

	aImMessage->SetRecipientL ( aRecipients );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::before sendmessage called\n" ) );

	req = imconversation.SendMessageL ( *aImMessage );
	eventObserver->WaitOpToCompleteL ( req );
	CleanupStack::Pop ( 3 );//identity,aRecipients,aImMessage
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::message sent\n " ) );
	CUserAfter::AfterL ( 1000000 );

	//Unbind the context and wait completion
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
	CleanupStack::PopAndDestroy(4); //imFeatures,presecenCtx,eventObserver,ximpClient,
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::SendMessage_MultipleContactsL() end" ) );

	return KErrNone;

	}

// -----------------------------------------------------------------------------
// Cossadapmt::ReceiveMessageL
// SendMessage test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::ReceiveMessageL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ReceiveMessageL() start" ) );
	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );
	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();
	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	//Bind context to desired presence service
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    TPtrC               message;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );
	aItem.GetNextString ( message );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called\n" ) );
	eventObserver->WaitOpToCompleteL ( req );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
   CleanupStack::PopAndDestroy(2); //newGroupId,presenceFeatures

	CUserAfter::AfterL ( 1000000 );
	//Bind context to desired presence service
	MImFeatures* imFeatures = NULL;
	imFeatures = MImFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( imFeatures );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imFeatures created\n" ) );
	MImConversation& imconversation = imFeatures->ImConversation();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imconversation created\n" ) );
	MImConversationInfo *aImMessage = NULL;
	aImMessage = imFeatures->ImObjectFactory().NewImConversationInfoLC();
	MXIMPIdentity* identity = objFactory.NewIdentityLC();
	identity->SetIdentityL ( KMsgId );
	aImMessage->SetMessageIdL ( identity );
	aImMessage->SetTextMessageL ( message );
	CDesCArrayFlat* aRecipients = new ( ELeave ) CDesCArrayFlat ( 1 );
	CleanupStack::PushL ( aRecipients );  
	aRecipients->AppendL ( username );  //userid of own
	aImMessage->SetRecipientL ( aRecipients );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::before sendmessage called\n" ) );
    //send message is to own
	req = imconversation.SendMessageL ( *aImMessage );
	eventObserver->WaitOpToCompleteL ( req );
	CleanupStack::Pop ( 3 );//identity,aRecipients,aImMessage
	//send message to other guy
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::message sent\n " ) );
	//Unbind the context and wait completion
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
	CleanupStack::PopAndDestroy(4); //imFeatures,presecenCtx,eventObserver,ximpClient,
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ReceiveMessageL() start" ) );

	return KErrNone;

	}
// -----------------------------------------------------------------------------
// Cossadapmt::ReceiveEmptyMessageL
// SendMessage test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::ReceiveEmptyMessageL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ReceiveEmptyMessageL() start" ) );
	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );
	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();
	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	//Bind context to desired presence service
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called\n" ) );
	eventObserver->WaitOpToCompleteL ( req );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "" );
	_LIT ( KEmptyMessage, "" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
   CleanupStack::PopAndDestroy(2); //newGroupId,presenceFeatures

	CUserAfter::AfterL ( 1000000 );
	//Bind context to desired presence service
	MImFeatures* imFeatures = NULL;
	imFeatures = MImFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( imFeatures );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imFeatures created\n" ) );
	MImConversation& imconversation = imFeatures->ImConversation();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imconversation created\n" ) );
	MImConversationInfo *aImMessage = NULL;
	aImMessage = imFeatures->ImObjectFactory().NewImConversationInfoLC();
	MXIMPIdentity* identity = objFactory.NewIdentityLC();
	identity->SetIdentityL ( KMsgId );
	aImMessage->SetMessageIdL ( identity );
	aImMessage->SetTextMessageL ( KEmptyMessage );
	CDesCArrayFlat* aRecipients = new ( ELeave ) CDesCArrayFlat ( 1 );
	CleanupStack::PushL ( aRecipients );  
	aRecipients->AppendL ( username );  //userid of own
	aImMessage->SetRecipientL ( aRecipients );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::before sendmessage called\n" ) );
    //send message is to own
	req = imconversation.SendMessageL ( *aImMessage );
	eventObserver->WaitOpToCompleteL ( req );
	CleanupStack::Pop ( 3 );//identity,aRecipients,aImMessage
	//send message to other guy
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::message sent\n " ) );
	//Unbind the context and wait completion
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
	CleanupStack::PopAndDestroy(4); //imFeatures,presecenCtx,eventObserver,ximpClient,
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ReceiveEmptyMessageL() start" ) );

	return KErrNone;

	}

// -----------------------------------------------------------------------------
// Cossadapmt::ReceiveTenMessageL
// SendMessage test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::ReceiveTenMessageL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ReceiveTenMessageL() start" ) );
	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );
	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();
	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	//Bind context to desired presence service
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    TPtrC               message;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );
	aItem.GetNextString ( message );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called\n" ) );
	eventObserver->WaitOpToCompleteL ( req );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
    CleanupStack::PopAndDestroy(2); //newGroupId,presenceFeatures

	CUserAfter::AfterL ( 1000000 );
	//Bind context to desired presence service
	MImFeatures* imFeatures = NULL;
	imFeatures = MImFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( imFeatures );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imFeatures created\n" ) );
	MImConversation& imconversation = imFeatures->ImConversation();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imconversation created\n" ) );
	MImConversationInfo *aImMessage = NULL;
	aImMessage = imFeatures->ImObjectFactory().NewImConversationInfoLC();
	MXIMPIdentity* identity = objFactory.NewIdentityLC();
	identity->SetIdentityL ( KMsgId );
	aImMessage->SetMessageIdL ( identity );
	aImMessage->SetTextMessageL ( message );
	CDesCArrayFlat* aRecipients = new ( ELeave ) CDesCArrayFlat ( 2 );
	CleanupStack::PushL ( aRecipients );  
	aRecipients->AppendL ( username );  //userid of own
	aImMessage->SetRecipientL ( aRecipients );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::before sendmessage called\n" ) );

	for ( TInt i = 0;i < 10;i++ )
		{
		req = imconversation.SendMessageL ( *aImMessage );
		eventObserver->WaitOpToCompleteL ( req );

		}
	CleanupStack::Pop ( 3 );//identity,aRecipients,aImMessage

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::message sent\n " ) );
    //Unbind the context and wait completion
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
	CleanupStack::PopAndDestroy(4); //imFeatures,presecenCtx,eventObserver,ximpClient,
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ReceiveTenMessageL() end" ) );

	return KErrNone;

	}

// -----------------------------------------------------------------------------
// Cossadapmt::ReceiveTwentyMessageL
// SendMessage test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::ReceiveTwentyMessageL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ReceiveTwentyMessageL() start" ) );
	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );
	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();
	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	//Bind context to desired presence service
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    TPtrC               message;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );
	aItem.GetNextString ( message );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called\n" ) );
	eventObserver->WaitOpToCompleteL ( req );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
   CleanupStack::PopAndDestroy(2); //newGroupId,presenceFeatures

	CUserAfter::AfterL ( 1000000 );
	//Bind context to desired presence service
	MImFeatures* imFeatures = NULL;
	imFeatures = MImFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( imFeatures );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imFeatures created\n" ) );
	MImConversation& imconversation = imFeatures->ImConversation();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imconversation created\n" ) );
	MImConversationInfo *aImMessage = NULL;
	aImMessage = imFeatures->ImObjectFactory().NewImConversationInfoLC();
	MXIMPIdentity* identity = objFactory.NewIdentityLC();
	identity->SetIdentityL ( KMsgId );
	aImMessage->SetMessageIdL ( identity );
	aImMessage->SetTextMessageL ( message );
	CDesCArrayFlat* aRecipients = new ( ELeave ) CDesCArrayFlat ( 2 );
	CleanupStack::PushL ( aRecipients );  
	aRecipients->AppendL ( username ); //userid's of own
	aImMessage->SetRecipientL ( aRecipients );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::before sendmessage called\n" ) );

	for ( TInt i = 0;i < 20;i++ )
		{
		req = imconversation.SendMessageL ( *aImMessage );
		eventObserver->WaitOpToCompleteL ( req );
		}
	CleanupStack::Pop ( 3 );//identity,aRecipients,aImMessage

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::message sent\n " ) );
    //Unbind the context and wait completion
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
	CleanupStack::PopAndDestroy(4); //imFeatures,presecenCtx,eventObserver,ximpClient,
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ReceiveTwentyMessageL() end" ) );

	return KErrNone;

	}


// -----------------------------------------------------------------------------
// Cossadapmt::PublishOwnPresenceL
// Login test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::PublishOwnPresenceL ( CStifItemParser& aItem )
	{



	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::PublishOwnPresenceL() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );

	MPresenceFeatures* presenceFeatures = NULL;
    presenceFeatures = MPresenceFeatures::NewL(presecenCtx); 
    CleanupDeletePushL( presenceFeatures );


    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    TInt               availability;
    TPtrC               statustext;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );
	aItem.GetNextInt ( availability );
	aItem.GetNextString ( statustext );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );
    // Take handles to object factory and publish interface
    MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
    MPresencePublishing& publisher = presenceFeatures->PresencePublishing();
    //Fill presence doc with presence components and attributes
    MPresenceInfo* myPresence = presenceFeatures->PresenceObjectFactory().NewPresenceInfoLC();//1
    MServicePresenceInfo* myServicePresence = presenceFeatures->PresenceObjectFactory().NewServicePresenceInfoLC();//2
    myServicePresence->SetServiceTypeL( NPresenceInfo::NServiceType::KInstantMessaging );
    //MPresenceInfoFieldCollection& attributeFields = myServicePresence->Fields();

    MPersonPresenceInfo *PersonPresence = presenceFeatures->PresenceObjectFactory().NewPersonPresenceInfoLC();
    MPresenceInfoFieldCollection& attributeFields = PersonPresence->Fields();
    
    MPresenceInfoField* infoField = presenceFeatures->PresenceObjectFactory().NewInfoFieldLC();//3

    // "availability" attribute
    MPresenceInfoFieldValueEnum* availabilityField = presenceFeatures->PresenceObjectFactory().NewEnumInfoFieldLC();//4
    availabilityField->SetValueL( availability ); 
    infoField->SetFieldTypeL( NPresenceInfo::NFieldType::KAvailability ); 
    infoField->SetFieldValue( availabilityField );
    CleanupStack::Pop(); // availabilityField

    attributeFields.AddOrReplaceFieldL(infoField );
    //TInt count = serviceFields.FieldCount();
    CleanupStack::Pop(); // infoField
    
    //status text
    infoField = presenceFeatures->PresenceObjectFactory().NewInfoFieldLC();//7
    MPresenceInfoFieldValueText* statustextField = presenceFeatures->PresenceObjectFactory().NewTextInfoFieldLC();//8
    statustextField->SetTextValueL( statustext ); // some status text
    infoField->SetFieldTypeL( KStatusTextfield );
    infoField->SetFieldValue( statustextField );
    CleanupStack::Pop(); // statustextField
    attributeFields.AddOrReplaceFieldL( infoField );
    CleanupStack::Pop(); // infoField
    
      
     //online status
    
    infoField = presenceFeatures->PresenceObjectFactory().NewInfoFieldLC();//7
    MPresenceInfoFieldValueText* onlineField = presenceFeatures->PresenceObjectFactory().NewTextInfoFieldLC();//8
    onlineField->SetTextValueL( _L("T" ) ); // some status text
    infoField->SetFieldTypeL( KOnlineStatusfield );
    infoField->SetFieldValue( onlineField );
    CleanupStack::Pop(); // devmodelField
    attributeFields.AddOrReplaceFieldL( infoField );
    CleanupStack::Pop(); // infoField
     
        
    myPresence->AddServicePresenceL( myServicePresence );
    myPresence->SetPersonPresenceL(PersonPresence);
    TInt count = attributeFields.FieldCount();
    CleanupStack::Pop(2); // myServicePresence,PersonPresence

    	
    //publish the presence
    req = publisher.PublishOwnPresenceL( *myPresence );

    // wait completion
    eventObserver->WaitOpToCompleteL( req );
    CleanupStack::PopAndDestroy(1); // myPresence
        
    CUserAfter::AfterL ( 1000000 );
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end" ) );

	CleanupStack::PopAndDestroy ( 4 ); //presenceFeatures,presecenCtx,eventObserver,ximpClient
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::PublishOwnPresenceL() End" ) );
	return KErrNone;

	}
// -----------------------------------------------------------------------------
// Cossadapmt::PublishOwnPresenceEmptyTextL
// Login test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::PublishOwnPresenceEmptyTextL ( CStifItemParser& aItem )
	{



	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::PublishOwnPresenceEmptyTextL() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );

	MPresenceFeatures* presenceFeatures = NULL;
    presenceFeatures = MPresenceFeatures::NewL(presecenCtx); 
    CleanupDeletePushL( presenceFeatures );


    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    TInt               availability;

	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );
	aItem.GetNextInt ( availability );
	_LIT ( KBlankStatusText, "" );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );
    // Take handles to object factory and publish interface
    MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
    MPresencePublishing& publisher = presenceFeatures->PresencePublishing();
    //Fill presence doc with presence components and attributes
    MPresenceInfo* myPresence = presenceFeatures->PresenceObjectFactory().NewPresenceInfoLC();//1
    MServicePresenceInfo* myServicePresence = presenceFeatures->PresenceObjectFactory().NewServicePresenceInfoLC();//2
    myServicePresence->SetServiceTypeL( NPresenceInfo::NServiceType::KInstantMessaging );
    //MPresenceInfoFieldCollection& attributeFields = myServicePresence->Fields();

    MPersonPresenceInfo *PersonPresence = presenceFeatures->PresenceObjectFactory().NewPersonPresenceInfoLC();
    MPresenceInfoFieldCollection& attributeFields = PersonPresence->Fields();
    
    MPresenceInfoField* infoField = presenceFeatures->PresenceObjectFactory().NewInfoFieldLC();//3

    // "availability" attribute
    MPresenceInfoFieldValueEnum* availabilityField = presenceFeatures->PresenceObjectFactory().NewEnumInfoFieldLC();//4
    availabilityField->SetValueL( availability ); 
    infoField->SetFieldTypeL( NPresenceInfo::NFieldType::KAvailability ); 
    infoField->SetFieldValue( availabilityField );
    CleanupStack::Pop(); // availabilityField

    attributeFields.AddOrReplaceFieldL(infoField );
    //TInt count = serviceFields.FieldCount();
    CleanupStack::Pop(); // infoField
    
    //status text
    infoField = presenceFeatures->PresenceObjectFactory().NewInfoFieldLC();//7
    MPresenceInfoFieldValueText* statustextField = presenceFeatures->PresenceObjectFactory().NewTextInfoFieldLC();//8
    statustextField->SetTextValueL( KBlankStatusText ); // some status text
    infoField->SetFieldTypeL( KStatusTextfield );
    infoField->SetFieldValue( statustextField );
    CleanupStack::Pop(); // statustextField
    attributeFields.AddOrReplaceFieldL( infoField );
    CleanupStack::Pop(); // infoField
    
      
     //online status
    
    infoField = presenceFeatures->PresenceObjectFactory().NewInfoFieldLC();//7
    MPresenceInfoFieldValueText* onlineField = presenceFeatures->PresenceObjectFactory().NewTextInfoFieldLC();//8
    onlineField->SetTextValueL( _L("T" ) ); // some status text
    infoField->SetFieldTypeL( KOnlineStatusfield );
    infoField->SetFieldValue( onlineField );
    CleanupStack::Pop(); // devmodelField
    attributeFields.AddOrReplaceFieldL( infoField );
    CleanupStack::Pop(); // infoField
     
        
    myPresence->AddServicePresenceL( myServicePresence );
    myPresence->SetPersonPresenceL(PersonPresence);
    TInt count = attributeFields.FieldCount();
    CleanupStack::Pop(2); // myServicePresence,PersonPresence

    	
    //publish the presence
    req = publisher.PublishOwnPresenceL( *myPresence );

    // wait completion
    eventObserver->WaitOpToCompleteL( req );
    CleanupStack::PopAndDestroy(1); // myPresence
        
    CUserAfter::AfterL ( 1000000 );
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end" ) );

	CleanupStack::PopAndDestroy ( 4 ); //presenceFeatures,presecenCtx,eventObserver,ximpClient
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::PublishOwnPresenceEmptyTextL() End" ) );
	return KErrNone;

	}
TInt Cossadapmt::AcceptnotificationRequestL ( CStifItemParser& aItem )
	{
	
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::AcceptAddnotificationRequestL() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );
	TOssAdapMtLogger::Log ( _L ( "Loading presence plugin Done" ) );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;
    MPresenceAuthorization& authorization = presenceFeatures->PresenceAuthorization();
    MPresenceInfoFilter* infoFilt = presenceFeatures->PresenceObjectFactory().NewPresenceInfoFilterLC();
   
    infoFilt->AcceptPersonFilterL( NPresenceInfo::NFieldType::KAcceptAll );

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "list" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    
	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );
    req = authorization.SubscribePresenceGrantRequestListL();
    
    // wait completion
    
    eventObserver->WaitOpToCompleteL( req );

    CUserAfter::AfterL( 1000000 );
	
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );

	CUserAfter::AfterL ( 5000000 );

    MXIMPIdentity* testContactId = objFactory.NewIdentityLC();
    testContactId->SetIdentityL( KContact1 );
    req = authorization.GrantPresenceForPresentityL(*testContactId ,*infoFilt );
      
    // wait completion
    eventObserver->WaitOpToCompleteL( req );
    

	 CleanupStack::PopAndDestroy();//testContactId
	//Unbind the context and wait completion
	req = presecenCtx->UnbindL();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->UnbindL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end" ) );

	CleanupStack::PopAndDestroy ( 6 );//newGroupId,presenceFeatures,presecenCtx,eventObserver,ximpClient,infoFilt
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::AcceptAddnotificationRequestL() end" ) );

	return KErrNone;
	}


// -----------------------------------------------------------------------------
// Cossadapmt::RejectAddnotificationRequestL
// AddConatctL contacts test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::RejectAddnotificationRequestL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::RejectAddnotificationRequestL() start" ) );

	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );
	TOssAdapMtLogger::Log ( _L ( "Loading presence plugin Done" ) );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;
    MPresenceAuthorization& authorization = presenceFeatures->PresenceAuthorization();
    MPresenceInfoFilter* infoFilt = presenceFeatures->PresenceObjectFactory().NewPresenceInfoFilterLC();
     
     infoFilt->AcceptPersonFilterL( NPresenceInfo::NFieldType::KAcceptAll );

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "list" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    
	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );

	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
	//Wait with CActiveSchedulerWait the binding to complete
	//If binding fails, it is handled with leave
	eventObserver->WaitOpToCompleteL ( req );
    req = authorization.SubscribePresenceGrantRequestListL();
    
    // wait completion
    
    eventObserver->WaitOpToCompleteL( req );

    CUserAfter::AfterL( 1000000 );
	
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
	CUserAfter::AfterL ( 5000000 );

    MXIMPIdentity* testContactId = objFactory.NewIdentityLC();
    testContactId->SetIdentityL( KContact1 );
    req = authorization.WithdrawPresenceGrantFromPresentityL(*testContactId);
      
    // wait completion
    eventObserver->WaitOpToCompleteL( req );
    
    CUserAfter::AfterL( 1000000 );

	 CleanupStack::PopAndDestroy();//testContactId
	//Unbind the context and wait completion
	req = presecenCtx->UnbindL();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->UnbindL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end" ) );

	CleanupStack::PopAndDestroy ( 6 );//infoFilt,newGroupId,presenceFeatures,presecenCtx,eventObserver,ximpClient
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::RejectAddnotificationRequestL() end" ) );

	return KErrNone;

	}
// -----------------------------------------------------------------------------
// Cossadapmt::ImOperationsCoverageL
// ImOperationsCoverageL test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::ImOperationsCoverageL ( CStifItemParser& aItem )
	{

	//Initialize XIMP client
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ImOperationsCoverageL() start" ) );
	MXIMPClient* ximpClient = MXIMPClient::NewClientL();
	CleanupDeletePushL ( ximpClient );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );
	//Create new sink to receive presence context events
	CUSContextObserver* eventObserver = CUSContextObserver::NewLC();
	//Create new presence context
	MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
	//Bind context to desired presence service
	presecenCtx->RegisterObserverL ( *eventObserver );
	MPresenceFeatures* presenceFeatures = NULL;
	presenceFeatures = MPresenceFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( presenceFeatures );

    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
	TInt                serviceId;
    TPtrC               message;
    TPtrC               contact;
	aItem.GetNextString ( username );
	aItem.GetNextString ( password );
	aItem.GetNextInt ( serviceId );
	aItem.GetNextString ( message );
	aItem.GetNextString ( contact );
	TUid protocolUid = TUid::Uid ( KProtocolUid );

	//Bind context to desired presence service
	TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
	                     username,
	                     password,
	                     serviceId );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called\n" ) );
	eventObserver->WaitOpToCompleteL ( req );
	MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
	MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
	MPresentityGroups& groups = presenceFeatures->PresentityGroups() ;

	TOssAdapMtLogger::Log ( _L ( "presentity groups object created" ) );
	_LIT ( KDummyListId, "" );
	HBufC16* iListId;
	iListId = KDummyListId().AllocL();
	iListId->Des().Fold();
	newGroupId->SetIdentityL ( *iListId );
	delete iListId;
	iListId = NULL;
	req = groups.SubscribePresentityGroupContentL ( *newGroupId );

	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::groups.SubscribePresentityGroupListL() called" ) );

	eventObserver->WaitOpToCompleteL ( req );
   CleanupStack::PopAndDestroy(2); //newGroupId,presenceFeatures

	CUserAfter::AfterL ( 1000000 );
	//Bind context to desired presence service
	MImFeatures* imFeatures = NULL;
	imFeatures = MImFeatures::NewL ( presecenCtx );
	CleanupDeletePushL ( imFeatures );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imFeatures created\n" ) );
	MImConversation& imconversation = imFeatures->ImConversation();
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::imconversation created\n" ) );
	MImConversationInfo *aImMessage = NULL;
	aImMessage = imFeatures->ImObjectFactory().NewImConversationInfoLC();
	MXIMPIdentity* identity = objFactory.NewIdentityLC();
	identity->SetIdentityL ( KMsgId );
	aImMessage->SetMessageIdL ( identity );
	aImMessage->SetTextMessageL ( message );
	CDesCArrayFlat* aRecipients = new ( ELeave ) CDesCArrayFlat ( 1 );
	CleanupStack::PushL ( aRecipients );  
	aRecipients->AppendL ( username );  //userid of own
	aImMessage->SetRecipientL ( aRecipients );
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::before sendmessage called\n" ) );
    //send message is to own
	req = imconversation.SendMessageL ( *aImMessage );
	eventObserver->WaitOpToCompleteL ( req );
	CleanupStack::Pop ( 3 );//identity,aRecipients,aImMessage
	//send message to other guy
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::message sent\n " ) );
	//Unbind the context and wait completion
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
	CleanupStack::PopAndDestroy(4); //imFeatures,presecenCtx,eventObserver,ximpClient,
	TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ImOperationsCoverageL() start" ) );

	return KErrNone;

	}		
// -----------------------------------------------------------------------------
// Cossadapmt::SetAvtarL
// Login test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cossadapmt::SetAvtarL ( CStifItemParser& aItem )
    {



    //Initialize XIMP client
    TOssAdapMtLogger::Log ( _L ( "Cossadapmt::SetAvtarL() start" ) );

    MXIMPClient* ximpClient = MXIMPClient::NewClientL();
    CleanupDeletePushL ( ximpClient );
    TOssAdapMtLogger::Log ( _L ( "Cossadapmt::MXIMPClient::NewClientL() start" ) );

    //Create new sink to receive presence context events
    CUSContextObserver* eventObserver = CUSContextObserver::NewLC();

    //Create new presence context
    MXIMPContext* presecenCtx = ximpClient->NewPresenceContextLC();
    TOssAdapMtLogger::Log ( _L ( "Cossadapmt::ximpClient->NewPresenceContextLC() called" ) );
    presecenCtx->RegisterObserverL ( *eventObserver );

    MPresenceFeatures* presenceFeatures = NULL;
    presenceFeatures = MPresenceFeatures::NewL(presecenCtx); 
    CleanupDeletePushL( presenceFeatures );


    //read data from cfg file
    TPtrC               username;
    TPtrC               password;
    TInt                serviceId;
    TPtrC               filename;
    aItem.GetNextString ( username );
    aItem.GetNextString ( password );
    aItem.GetNextInt ( serviceId );
    aItem.GetNextString ( filename );
    TUid protocolUid = TUid::Uid ( KProtocolUid );
    
    //Bind context to desired presence service
    TXIMPRequestId req = presecenCtx->BindToL ( protocolUid,
                         username,
                         password,
                         serviceId );
    TOssAdapMtLogger::Log ( _L ( "Cossadapmt::presecenCtx->BindToL() called" ) );
    //Wait with CActiveSchedulerWait the binding to complete
    //If binding fails, it is handled with leave
    eventObserver->WaitOpToCompleteL ( req );
    // Take handles to object factory and publish interface
    // Take handles to object factory and publish interface
    presenceFeatures = MPresenceFeatures::NewL(presecenCtx); 
    MXIMPObjectFactory& objFactory = presecenCtx->ObjectFactory();
   
    MXIMPIdentity* newGroupId = objFactory.NewIdentityLC();
    MXIMPIdentity* newmemberId = objFactory.NewIdentityLC();

    CleanupDeletePushL( presenceFeatures );

    MPresencePublishing& publisher = presenceFeatures->PresencePublishing();
  
    //Fill presence doc with presence components and attributes
    MPresenceInfo* myPresence = presenceFeatures->PresenceObjectFactory().NewPresenceInfoLC();//1
    MPersonPresenceInfo *PersonPresence = presenceFeatures->PresenceObjectFactory().NewPersonPresenceInfoLC();
    MPresenceInfoFieldCollection& attributeFields = PersonPresence->Fields();
  
    MPresenceInfoField* infoField = presenceFeatures->PresenceObjectFactory().NewInfoFieldLC();//3

   //based on the state conver it to  ximpfw status.
 

    // "availability" attribute
    MPresenceInfoFieldValueBinary* avatarField = presenceFeatures->PresenceObjectFactory().NewBinaryInfoFieldLC();//4
    //avatarField->SetBinaryValueL(*(aImageLoader->GetContentData()));
    _LIT8(KMimeType,"image/gif");
    TBufC8<20> mimetype(KMimeType);

    avatarField->SetMimeTypeL(mimetype.Des());
   RFile file;
   RFs iFs;
   User::LeaveIfError( iFs.Connect() );
   User::LeaveIfError( file.Open( iFs, _L("c:\\index.gif"), EFileRead ) );
   CleanupClosePushL( file );
        
    // Get file size
    TInt fileSize = 0;
    User::LeaveIfError( file.Size( fileSize ) );
    
    // Check file size, if bigger than max transaction content -> leave
  /*  if ( fileSize >
        iImpsFactory.CreateImClientL()->MaxTransactionContentLengthL() )
        {
        User::Leave( KErrOverflow );
        }*/
        
    // Get file content
    HBufC8* Content = HBufC8::NewL( fileSize );
    TPtr8 ptr( Content->Des() );
    User::LeaveIfError( file.Read( ptr, fileSize ) );
    
    avatarField->SetBinaryValueL(*Content);
    infoField->SetFieldTypeL( NPresenceInfo::NFieldType::KAvatar ); 
    infoField->SetFieldValue( avatarField );
    CleanupStack::Pop(); // availabilityField

    attributeFields.AddOrReplaceFieldL(infoField );
 
    CleanupStack::Pop(); // infoField
                  
    myPresence->SetPersonPresenceL(PersonPresence);
    CleanupStack::Pop(1); // PersonPresence

    req = publisher.PublishOwnPresenceL( *myPresence );

    // wait completion
    eventObserver->WaitOpToCompleteL( req );
    CleanupStack::PopAndDestroy(1); // myPresence
        
    req = presecenCtx->UnbindL();
    eventObserver->WaitOpToCompleteL( req );
    TOssAdapMtLogger::Log ( _L ( "Cossadapmt::WaitOpToCompleteL() end" ) );

    CleanupStack::PopAndDestroy ( 4 ); //presenceFeatures,presecenCtx,eventObserver,ximpClient
    TOssAdapMtLogger::Log ( _L ( "Cossadapmt::SetAvtarL() End" ) );
    return KErrNone;

    }
//  [End of File] - Do not remove
