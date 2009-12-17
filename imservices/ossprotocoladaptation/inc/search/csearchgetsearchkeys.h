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


/*!	\def To avoid multiple inclusions
*/
#ifndef C_SEARCHGETSEARCHKEYS_H
#define C_SEARCHGETSEARCHKEYS_H

#include <e32base.h>
#include <e32cmn.h>
#include <ximpbase.h>
#include "mossprotocolconnectionmanager.h"

/*!	\file 
*	\brief Interfaces for the get search key request
*/


/*!	\class CSearchGetSearchKeys csearchgetsearchkeys.h
*	\brief This class derived from CActive impliments a request
*	for the get search keys
*/
class CSearchGetSearchKeys : public CActive
	{
	
	public:
	
	/*!	\fn
	*	\brief static function to create a new object of this class
	*/
	static CSearchGetSearchKeys* NewL( 
		    MOSSProtocolConnectionManager& aConnMan,
		    TXIMPRequestId aRequestId );
	
	
	/*!	\fn
	*	\brief Default Constructor for this class
	*/
	CSearchGetSearchKeys( 
		    MOSSProtocolConnectionManager& aConnMan,
		    TXIMPRequestId aRequestId  );
	
	/*!	\fn
	*	\brief destructor
	*/
	~CSearchGetSearchKeys();
	
	
	/*!	\brief Function to issue a request, in this case 
	*	it is geting search keys
	*/
	void GetSearchKeysL();
	
	
	protected:
	
	/*!	\fn
	*	\brief Called when a cancel is done on the active object
	*/
	void DoCancel();
	
	/*!	\fn
	*	\brief Called when the request submitted by this object 
	*	is completed
	*/
	void RunL();
	
	/*!	\fn
	*	\brief Called when the RunL leaves
	*/
	TInt RunError( TInt aError );
	
	
	
	private:
	
	/*!	\fn
	*	\brief 2nd phase constructor for this class
	*/
	void ConstructL();
	
	/*!	\var Data Id generated for the request
	*/
	TInt iSendId;
	
	
	/*!	\var TXIMPRequestId Request Id
	*	
	*/
	TXIMPRequestId iRequestId;
	
	/*!	\var iConnMan handle to connection manager
	*	This variable is not owned by this class
	*/
	MOSSProtocolConnectionManager& iConnMan;
	
	};


#endif //C_SEARCHGETSEARCHKEYS_H
