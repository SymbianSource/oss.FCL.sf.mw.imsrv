/*
* Copyright (c) 2007-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: Send data operation holder
*
*/

#ifndef __COSSSENDDATAOPERATION_H__
#define __COSSSENDDATAOPERATION_H__

//  INCLUDES
#include    <e32std.h>
#include    "ossprotocolpluginlogger.h"
#include 	<e32base.h>


/**
 * COssSendDataOperation:
 * Send data operation holder
 *
 */
NONSHARABLE_CLASS ( COssSendDataOperation ) :
		public CBase
	{

public:
	
	static  COssSendDataOperation* NewLC();

	 /**
	 *  Default constructor
	 */
	 COssSendDataOperation();
		
	/**
	 *  Destructor
	 */
	 ~COssSendDataOperation();


public: // new function of the class


	/**
	 * Set ids, operation and log id
	 */
	 void SetIds ( TInt aOperationId, TInt aLogId );
	
	/**
	 * Set request status
	 */
	 void SetRequestStatus ( TRequestStatus& aStatus );
	

	/**
	 * request status of this operation
	 * @return Trequest status of this operation
	 */
	 TRequestStatus* Status();
	
	/**
	 * Get Ids
	 *
	 * @return operation Id
	 */
	 TInt OperationId() const;
	
	/**
	 * Complete operation
	 *
	 * @param aCode complete code
	 */
	 void CompletedOperation ( TInt aCode );

	/**
	 * Set response buffer
	 * Owner ship is transfered
	 * @param aBuff response buffer
	 */
	 void SetResponse ( char* aBuff );

	/**
	 * Response buffer,
	 * owner ship is transfered
	 * @return transfer buffer
	 */
	 char* Response();

private: // Public data

	/**
	 * Status of the operation
	 */
	TRequestStatus*     iStatus;

	/**
	 * Operation Id
	 * OWN
	 */
	TInt                iOpId;

	/**
	 * Response buffer
	 * OWN
	 */
	char*             iData;
	/**
	 * Id used for logs writting
	 * OWN
	 */
	TInt                iLogId;
	};



#endif      // __COSSSENDDATAOPERATION_H__

// End of File
