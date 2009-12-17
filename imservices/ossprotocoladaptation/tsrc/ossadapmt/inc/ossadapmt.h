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
* Description:  ossadapmt.h
*
*/



#ifndef OSSADAPMT_H
#define OSSADAPMT_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <flogger.h>

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// Logging path
_LIT ( KossadapmtLogPath, "\\logs\\testframework\\ossadapmt\\" );
// Log file
_LIT ( KossadapmtLogFile, "ossadapmt.txt" );
_LIT ( KossadapmtLogFileWithTitle, "ossadapmt_[%S].txt" );

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

class Cossadapmt;

enum TSearch 
	{
	ESimpleSearch,
	EMultipleSearch,
	ESearchNoResults,
	ESearchManyResults,
	ESearchBlank,
	ESearchMaxChars,
	ESearchSpecialChars,
	ESearchEmailid,
	ESearchAndAddToIm,
	ESecondSearch,
	EGetSearchKeyEnum,
	EGetSearchKeyLabel,
	EGetSearchKeyEnumNLabel,		
	};

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  Cossadapmt test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS ( Cossadapmt ) : public CScriptBase
	{

public:  // Constructors and destructor

	/**
	* Two-phased constructor.
	*/
	static Cossadapmt* NewL ( CTestModuleIf& aTestModuleIf );

	/**
	* Destructor.
	*/
	virtual ~Cossadapmt();

public: // New functions

	/**
	* ?member_description.
	* @since ?Series60_version
	* @param ?arg1 ?description
	* @return ?description
	*/
	//?type ?member_function( ?type ?arg1 );

public: // Functions from base classes

	/**
	* From CScriptBase Runs a script line.
	* @since ?Series60_version
	* @param aItem Script line containing method name and parameters
	* @return Symbian OS error code
	*/
	virtual TInt RunMethodL ( CStifItemParser& aItem );

protected:  // New functions

	/**
	* ?member_description.
	* @since ?Series60_version
	* @param ?arg1 ?description
	* @return ?description
	*/
	//?type ?member_function( ?type ?arg1 );

protected:  // Functions from base classes

	/**
	* From ?base_class ?member_description
	*/
	//?type ?member_function();

private:

	/**
	* C++ default constructor.
	*/
	Cossadapmt ( CTestModuleIf& aTestModuleIf );

	/**
	* By default Symbian 2nd phase constructor is private.
	*/
	void ConstructL();

	// Prohibit copy constructor if not deriving from CBase.
	// ?classname( const ?classname& );
	// Prohibit assigment operator if not deriving from CBase.
	// ?classname& operator=( const ?classname& );

	/**
	* Frees all resources allocated from test methods.
	* @since ?Series60_version
	*/
	void Delete();

	/**
	* Test methods are listed below.
	*/

	/**
	* Bind test method.
	* @since ?Series60_version
	* @param aItem Script line containing parameters.
	* @return Symbian OS error code.
	*/
	virtual TInt LoginL ( CStifItemParser& aItem );
	virtual TInt Login_InvalidDataL ( CStifItemParser& aItem );
	virtual TInt Login8HrsLogoutL ( CStifItemParser& aItem );
	virtual TInt LoginLogout_LoginLogoutL ( CStifItemParser& aItem );
	/**
	* UnBind test method.
	*/
	virtual TInt UnBindL ( CStifItemParser& aItem );
	/**
	* Fetch contacts method
	*/
	virtual TInt GetContactsL ( CStifItemParser& aItem );

	/**
	* Send message test method.
	*/
	virtual TInt SendMessageL ( CStifItemParser& aItem );
	virtual TInt SendEmptyMessageL ( CStifItemParser& aItem );
	virtual TInt SendTenMessageL ( CStifItemParser& aItem );
	virtual TInt SendTwentyMessageL ( CStifItemParser& aItem );
	virtual TInt SendMessage_MultipleContactsL ( CStifItemParser& aItem );

	/**
	* Receive message test method
	*/
	virtual TInt ReceiveMessageL ( CStifItemParser& aItem );
	virtual TInt ReceiveEmptyMessageL ( CStifItemParser& aItem );
	virtual TInt ReceiveTenMessageL ( CStifItemParser& aItem );
	virtual TInt ReceiveTwentyMessageL ( CStifItemParser& aItem );

	/**
	*contact list manangement test methods
	*/
	virtual TInt AddConatctL ( CStifItemParser& aItem );
	virtual TInt AcceptnotificationRequestL ( CStifItemParser& aItem );
	virtual TInt AddBlankConatctL ( CStifItemParser& aItem );
	virtual TInt AddBlankConatct1L ( CStifItemParser& aItem );
	
    virtual TInt DeleteConatctL ( CStifItemParser& aItem );
    virtual TInt DeleteBlankConatctL ( CStifItemParser& aItem );
   /**
	* Presence publishing test method
	*/
	virtual TInt PublishOwnPresenceL ( CStifItemParser& aItem );
	virtual TInt PublishOwnPresenceEmptyTextL ( CStifItemParser& aItem );
	virtual TInt RejectAddnotificationRequestL ( CStifItemParser& aItem );
	virtual TInt ImOperationsCoverageL ( CStifItemParser& aItem );
	
	virtual TInt SearchL ( CStifItemParser& aItem, TSearch aSearchType );
	virtual TInt SimpleSearchL( CStifItemParser& aItem );
	virtual TInt MultipleSearchL( CStifItemParser& aItem );
	virtual TInt NoResultSearchL( CStifItemParser& aItem );
	virtual TInt ManyResultsSearchL( CStifItemParser& aItem );
	virtual TInt BlankSearchL( CStifItemParser& aItem );
	virtual TInt MaxCharSearchL( CStifItemParser& aItem );
	virtual TInt SpecialCharSearchL( CStifItemParser& aItem );
	virtual TInt SearchEmailIDL( CStifItemParser& aItem );
   	virtual TInt SearchAndAddToIML( CStifItemParser& aItem );
   	virtual TInt SecondSearchL( CStifItemParser& aItem );
   	virtual TInt GetSearchKeyEnumL( CStifItemParser& aItem );
   	virtual TInt GetSearchKeyLabelL( CStifItemParser& aItem );
   	virtual TInt GetSearchKeyEnumNLabelL( CStifItemParser& aItem );
    virtual TInt SetAvtarL( CStifItemParser& aItem );
public:     // Data
	// ?one_line_short_description_of_data
	//?data_declaration;

protected:  // Data
	// ?one_line_short_description_of_data
	//?data_declaration;

private:    // Data

	// ?one_line_short_description_of_data
	//?data_declaration;

	// Reserved pointer for future extension
	//TAny* iReserved;

public:     // Friend classes
	//?friend_class_declaration;

protected:  // Friend classes
	//?friend_class_declaration;

private:    // Friend classes
	//?friend_class_declaration;

	};

class TOssAdapMtLogger
	{

	public: // New functions
		/**
		    * Writes log to log file
		    */
		static void Log ( TRefByValue<const TDesC> aFmt, ... );

	};



#endif      // OSSADAPMT_H

// End of File
