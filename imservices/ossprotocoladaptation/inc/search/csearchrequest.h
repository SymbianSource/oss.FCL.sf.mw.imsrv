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


#ifndef __CSEARCHREQUEST_H__
#define __CSEARCHREQUEST_H__


//  INCLUDES
#include <e32base.h>
#include <ximpbase.h>

#include <searchinfo.h>

// FORWARD DECLARATIONS
class MOSSProtocolConnectionManager;
class MSearchElement;
class MXIMPIdentity;

/**
 * CSearchrequest
 *
 * Issue Search Request to Network Server
 *
 */
 
class CSearchrequest: public CActive
                                			   
                                			   
	{

	public:
	    										
	    static CSearchrequest* NewLC( MOSSProtocolConnectionManager& aConnMan,
	    										TXIMPRequestId aRequestId );
	    										
	    virtual ~CSearchrequest();

	private:

	    CSearchrequest( MOSSProtocolConnectionManager& aConnMan,
	    										TXIMPRequestId aRequestId  );
	    void ConstructL();

	private: // from CActive

	    void DoCancel();
	    void RunL();
	    TInt RunError( TInt aError );
	 
	 private : 
	 	/**
	     * parse the data
	     * @param aResponse: response contains searched data 
	     * @param alen: length
	     * @param aSearchInfo: search info
	     * @param aKeytype: search key type
	     */
	    void ParseAndSetL(char* aResponse, TInt alen, MSearchInfo& aSearchInfo, TInfoType aKeytype);   
	    
	public:
	    /**
	     * Issue search request to network server
	     * @param aSearchId: search id
	     * @param aObjs: array of search elements
	     * @param aSearchLimit: search limit
	     */
	  	void SearchL(const MXIMPIdentity& aSearchId,const  RPointerArray< MSearchElement >& aObjs,TInt aSearchLimit);

	private: // data

	    /**
	     * Request Id 
	     */
	    TXIMPRequestId iRequestId;
	    
	    /**
	     * Send data request to pure data handler generates the id
	     */
	    TInt iSendId;
		/**
	     * Search Id 
	     */   
	   	HBufC16*                  iSearchId;
	    /**
	     * Oss Protocol Plugin Connection Manager
	     * Not own.  *** Write "Not own" if some other class owns this object.
	     */
	    MOSSProtocolConnectionManager& iConnMan;
	    
	};


#endif // __CSEARCHREQUEST_H__

