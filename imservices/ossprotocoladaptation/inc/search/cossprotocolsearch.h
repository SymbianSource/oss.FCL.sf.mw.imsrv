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
* Description:  Oss protocol search 
*
*/

#ifndef COSSPROTOCOLSEARCH_H__
#define COSSPROTOCOLSEARCH_H__


#include <e32base.h>
#include <protocolsearch.h>


class MOSSProtocolConnectionManager;


/**
 * COSSProtocolSearch
 * implementation of MProtocolSearch methods.
 * these methods will called by search feature plugin
 */
class COSSProtocolSearch :   public CBase,
                             public MProtocolSearch
    {

	public:

	    static COSSProtocolSearch* NewL( MOSSProtocolConnectionManager& aConnManager );
	    
	    ~COSSProtocolSearch();


	private:

	    COSSProtocolSearch( MOSSProtocolConnectionManager& aConnManager );
	    void ConstructL();

	public:  //from MXIMPBase

	   /**
		*  @see MXIMPBase
		*/
	    TAny* GetInterface( TInt32 aInterfaceId,
	                        TIfGetOps  aOptions );
	   /**
		*  @see MXIMPBase
		*/
	    const TAny* GetInterface( TInt32 aInterfaceId,
	                              TIfGetOps aOptions ) const;
	   /**
		*  @see MXIMPBase
		*/
	    TInt32 GetInterfaceId() const;

	public: // From MProtocolSearch
	    
	   /**
		*  @see MProtocolSearch
		*/
	    void DoSearchL( const MXIMPIdentity& aSearchId,
						const RPointerArray< MSearchElement >& aObjs,
		                TInt  aSearchLimit,
		        		TXIMPRequestId aReqId );
	   /**
		*  @see MProtocolSearch
		*/        		
		void DoGetSearchKeysL( TXIMPRequestId aReqId );
	   
	private:    // data members
	    /**
	     * Oss Protocol Plugin Connection Manager
	     *   Not own. 
	     */
	    MOSSProtocolConnectionManager& iConnMan;

    };

#endif // COSSPROTOCOLSEARCH_H__
