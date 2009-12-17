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
* Description:  Send message Request to the Network Server
*
*/

#include "cosssendmessagerequest.h"
#include <ximpprotocolconnectionhost.h>
#include "cossprotocolconnectionmanager.h"
#include <ximpobjectfactory.h>
#include <ximpobjectcollection.h>
#include <protocolpresentitygroupsdatahost.h>
#include <presenceobjectfactory.h>
#include <presentitygroupinfo.h>
#include <presentitygroupmemberinfo.h>
#include <ximpidentity.h>
#include <ximpdatasubscriptionstate.h>
#include <protocolpresencedatahost.h>
#include "ossprotocolpluginlogger.h"
#include "ossprotocloliterals.h"
#include <stdlib.h>
#include "stringutils.h"
#include <string.h>
#include "msgliterals.h"
#include "msg_enums.h"
#include <badesca.h>

#include<imconversationinfo.h>
#include<imerrors.hrh>
#include "ossprotocoladaptutils.h"

/**
* operations state enums variables 
*/

enum ImStates
	{
	RecipientOffline = 1,
	SenderBlocked = 3,
	NotSupported = 5,
	  
	// add if  required
	};
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// COSSSendMessageRequest::COSSSendMessageRequest()
// ---------------------------------------------------------------------------
//
COSSSendMessageRequest::COSSSendMessageRequest (
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId ) :

		CActive ( EPriorityNormal ),
		iRequestId ( aRequestId ),
		iConnMan ( aConnMan )
	{
	LOGGER ( TXT ( "COSSSendMessageRequest::COSSSendMessageRequest Start" ) );
	CActiveScheduler::Add ( this );

	LOGGER ( TXT ( "COSSSendMessageRequest::COSSSendMessageRequest End" ) );
	}


// ---------------------------------------------------------------------------
// COSSSendMessageRequest::ConstructL()
// ---------------------------------------------------------------------------
//
void COSSSendMessageRequest::ConstructL()
	{
	LOGGER ( TXT ( "COSSSendMessageRequest::ConstructL Start-End" ) );


	}


// ---------------------------------------------------------------------------
// COSSSendMessageRequest::NewL()
// ---------------------------------------------------------------------------
//
COSSSendMessageRequest* COSSSendMessageRequest::NewL (
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
	{
	LOGGER ( TXT ( "COSSSendMessageRequest::NewL Start" ) );

	COSSSendMessageRequest* self = new ( ELeave )
	COSSSendMessageRequest ( aConnMan, aRequestId );
	CleanupStack::PushL ( self );
	self->ConstructL();
	CleanupStack::Pop ( self );

	LOGGER ( TXT ( "COSSSendMessageRequest::NewL End" ) );
	return self;
	}


// ---------------------------------------------------------------------------
// COSSSendMessageRequest::NewLC()
// ---------------------------------------------------------------------------
//
COSSSendMessageRequest* COSSSendMessageRequest::NewLC (
    MOSSProtocolConnectionManager& aConnMan,
    TXIMPRequestId aRequestId )
	{
	LOGGER ( TXT ( "COSSSendMessageRequest::NewLC Start" ) );

	COSSSendMessageRequest* self =
	    COSSSendMessageRequest::NewL ( aConnMan, aRequestId );
	CleanupStack::PushL ( self );

	LOGGER ( TXT ( "COSSSendMessageRequest::NewLC End" ) );
	return self;
	}

// ---------------------------------------------------------------------------
// COSSSendMessageRequest::~COSSSendMessageRequest()
// ---------------------------------------------------------------------------
//
COSSSendMessageRequest::~COSSSendMessageRequest()
	{
	LOGGER ( TXT ( "COSSSendMessageRequest::~COSSSendMessageRequest Start" ) );
	LOGGER ( TXT ( "COSSSendMessageRequest::~COSSSendMessageRequest End" ) );
	}


// ---------------------------------------------------------------------------
// COSSSendMessageRequest::DoCancel()
// ---------------------------------------------------------------------------
//
void COSSSendMessageRequest::DoCancel()
	{
	}


// ---------------------------------------------------------------------------
// COSSSendMessageRequest::RunL()
// ---------------------------------------------------------------------------
//
void COSSSendMessageRequest::RunL()
	{
	LOGGER ( TXT ( "COSSSendMessageRequest::RunL start" ) );
	message_hdr_resp* msg_struct = NULL;
	User::LeaveIfError ( iStatus.Int() );
    char* pResponse = NULL;  
	pResponse = iConnMan.DataHandler().ResponseL ( iSendId );

	msg_struct = ( message_hdr_resp* )pResponse ;
	if( !( msg_struct->response ) )
	{
		switch( msg_struct->error_type )
		{
	
		case RecipientOffline: //The username or password was invalid. 
			   iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KImApiErrRecipientNotLogged );
		       break;
		case SenderBlocked: //The username or password was invalid. 
			   iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KImApiErrSenderBlocked );
		       break;
		case NotSupported: //The username or password was invalid. 
			   iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KImErrServiceRequestTypeNotSupported );
		       break;
		default:  //for all other error codes like ssl related are mapped to general error
			   iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KImErrServiceGeneralError );
		       break;       
		}	
	}
	else
	{
	  iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, KErrNone );
	}

	free( pResponse );

	delete this;

	LOGGER ( TXT ( "COSSSendMessageRequest::RunL End" ) );
	}


// ---------------------------------------------------------------------------
// COSSSendMessageRequest::RunError()
// ---------------------------------------------------------------------------
//
TInt COSSSendMessageRequest::RunError ( TInt  aError )
	{
	LOGGER ( TXT ( "COSSSendMessageRequest::RunError Start" ) );

	iConnMan.HandleToHost().HandleRequestCompleted ( iRequestId, aError );

	delete this;
	LOGGER ( TXT ( "COSSSendMessageRequest::RunError End" ) );
	return KErrNone;
	}

// ---------------------------------------------------------------------------
// COSSSendMessageRequest::SendMessageL()
// ---------------------------------------------------------------------------
//
void COSSSendMessageRequest::SendMessageL ( const MImConversationInfo& aImMessage )
	{
	LOGGER ( TXT ( "COSSSendMessageRequest::SendMessageL Start" ) );

	TPtrC16 message = aImMessage.TextMessage();
	const MDesCArray& recipients = aImMessage.RecipientL();

	int userLen = 0;
	int totalLen = 0;

	message_hdr_req msgHdr = {0,};
	msgHdr.message_type = ESend_Request; 
	totalLen += sizeof ( message_hdr_req );

	RArray<charFormatData> recipientArray;	
	for ( TInt i = 0; i < recipients.MdcaCount(); i++ )
		{
		TPtrC16 recipientsPtr = recipients.MdcaPoint( i );
		charFormatData recipient = OssProtocolAdapUtils::ConvertTUint16ToCharLC( recipientsPtr );
        recipientArray.AppendL( recipient );//will get it back when writting to final buffer.
	    userLen = recipient.dataSize;
		totalLen += userLen;
		}
	totalLen++;
	
	charFormatData charData = OssProtocolAdapUtils::ConvertTUint16ToCharLC( message );
    char* msg = charData.data;
	userLen = charData.dataSize;
	totalLen += userLen;
	
	User::LeaveIfError ( totalLen > MAX_MSG_SIZE );
	
	char* outMessage = ( char* ) User::AllocLC( totalLen );
	memset( outMessage , '\0' ,  totalLen );

    userLen  = 0;
	totalLen = 0;
	totalLen += sizeof ( message_hdr_req );
	

	memcpy( outMessage , &msgHdr , totalLen ); //copy header.
	
	//now copy recipients one by one.
	TInt recipientCount = recipientArray.Count();
	for( TInt count = 0 ; count < recipientCount ; count++)
		{
		charFormatData receiver = recipientArray[count];
		userLen = receiver.dataSize;		
		memcpy( outMessage + totalLen , receiver.data , userLen );	
		totalLen += userLen;
		}
		
	totalLen++;	
	userLen = charData.dataSize;	
	memcpy ( outMessage + totalLen , msg , userLen );
 
	totalLen += userLen;
	iSendId = iConnMan.DataHandler().SendDataL ( iStatus, outMessage, totalLen );

	// signal the scheduler
	SetActive();
	CleanupStack::PopAndDestroy( recipientCount + 2 );//outMessage,msg,
	recipientArray.Close();  
	
	LOGGER ( TXT ( "COSSSendMessageRequest::SendMessageL End" ) );
	}

// End of file
