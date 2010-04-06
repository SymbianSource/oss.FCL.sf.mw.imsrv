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
* Description:  oss protocol plugin im features
*
*/


#include "waittimer.h"
#include "cosssenddataoperation.h"
#include "msgliterals.h"
#include "msg_enums.h"
#include <stdlib.h>
#include "ossprotocloliterals.h"
#include "stringutils.h"
#include "ossadappanics.h"
#include <glib/gprintf.h>
#include <string.h>
#include <sys/msg.h>
#include "ossprotocolpluginlogger.h"
#include <ximpobjectfactory.h>
#include "mossprotocolconnectionmanager.h"
#include "cossprotocolconnectionmanager.h"
#include <ximpprotocolconnectionhost.h>
#include <ximpstatus.h>
#include <math.h>
#include <avabilitytext.h>
#include "ossprotocoladaptutils.h"
// CONSTANTS
const TInt KOpIdInitvalue = 1000;

#define KTimerInterval 50000

#define ONE_K_OPENC_FIX 1020
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CWaitTimer::COSSProtocolImFeatures()
// ---------------------------------------------------------------------------
//
CWaitTimer::CWaitTimer (MOSSProtocolConnectionManager& aConnMan) :
		CActive ( EPriorityHigh ), // Standard priority
		iOpidIterator ( KOpIdInitvalue ), iOpId ( 5 ),iConnMan ( aConnMan ),
		iResponseMsgQCreated(EFalse),iServerDisconnected(EFalse),
		iFetchingStep(EDataFetchingStep1) // -2 for fetching all three  types of contacts
	{
	CActiveScheduler::Add ( this ); // Add to scheduler
	}


// ---------------------------------------------------------------------------
// CWaitTimer::NewL()
// ---------------------------------------------------------------------------
//
CWaitTimer* CWaitTimer::NewL (MOSSProtocolConnectionManager& aConnMan)
	{
	CWaitTimer* self = new ( ELeave ) CWaitTimer (aConnMan);
	CleanupStack::PushL ( self );
	self->ConstructL ();
	CleanupStack::Pop (); // self;
	return self;
	}

// ---------------------------------------------------------------------------
// CWaitTimer::ConstructL()
// ---------------------------------------------------------------------------
//
void CWaitTimer::ConstructL()
	{
	User::LeaveIfError( iTimer.CreateLocal() );
	}

// ---------------------------------------------------------------------------
// CWaitTimer::~CWaitTimer()
// ---------------------------------------------------------------------------
//
CWaitTimer::~CWaitTimer()
	{
	LOGGER ( TXT ( "CWaitTimer::~CWaitTimer  start" ) );
	TInt error = 0;
	MsgQDelete ( REQUEST_QUEUE, &error );
	MsgQDelete ( RESPONSE_QUEUE, &error );
    iIncomingData.ResetAndDestroy();
    iIncomingMsg.ResetAndDestroy();
    iIncomingPres.ResetAndDestroy();
	iIncomingServerError.ResetAndDestroy();	
    iAddNotification.ResetAndDestroy();
	if (iIncReqStatus)
        {
        User::RequestComplete( iIncReqStatus, KErrCancel );
        iIncReqStatus = NULL;
        }
 	if (iIncMsgReqStatus)
        {
        User::RequestComplete( iIncMsgReqStatus, KErrCancel );
        iIncMsgReqStatus = NULL;
        }     
    if (iIncPresReqStatus)
        {
        User::RequestComplete( iIncPresReqStatus, KErrCancel );
        iIncPresReqStatus = NULL;
        }        
    if (iIncAddReqStatus)
        {
        User::RequestComplete( iIncAddReqStatus, KErrCancel );
        iIncAddReqStatus = NULL;
        }        
    CancelContactsChangeListening();
	Cancel (); // Cancel any request, if outstanding
	iTimer.Close (); // Destroy the RTimer object
	iOperations.ResetAndDestroy();
	iSearchElements.ResetAndDestroy(); 
	iContactChangeList.ResetAndDestroy();
	LOGGER ( TXT ( "CWaitTimer::~CWaitTimer  end" ) );
	
	}

// ---------------------------------------------------------------------------
// CWaitTimer::DoCancel()
// ---------------------------------------------------------------------------
//
void CWaitTimer::DoCancel()
	{
	iTimer.Cancel ();
	}

// ----------------------------------------------------------------------------
// CWaitTimer::IncreaseOpId
// ----------------------------------------------------------------------------
void CWaitTimer::IncreaseOpId( )
	{

	iOpId++;

	}


// ----------------------------------------------------------------------------
// CWaitTimer::GetOpId
// ----------------------------------------------------------------------------
TInt CWaitTimer::GetOpId( )
	{

	return iOpId;
	}
// ----------------------------------------------------------------------------
// CWaitTimer::IsFetchingContinue
// ----------------------------------------------------------------------------
TInt CWaitTimer::IsFetchingContinue( )
	{

	return iFetchingContinue;

	}

// -----------------------------------------------------------------------------
// CWaitTimer::SendDataL()
// -----------------------------------------------------------------------------
//
TInt CWaitTimer::SendDataL ( TRequestStatus& aStatus, char* msg, TInt nBytes )
	{
	int result;
	int err = 0;
	int timeout = NO_WAIT;
	LOGGER ( TXT ( "CWaitTimer::SendData  start" ) );
	// allocate slot in array by adding NULL pointer and removing it
	iOperations.AppendL ( NULL );
	iOperations.Remove ( iOperations.Count() - 1 );
	COssSendDataOperation* operation =
	    COssSendDataOperation::NewLC();
	operation->SetIds ( iOpId, iOpidIterator++ );
	iOperations.Append ( operation );
	CleanupStack::Pop ( operation ); // operation
	// now it is safe to set request status
	operation->SetRequestStatus ( aStatus );
	aStatus = KRequestPending;
	/* Try to Create queueOne
	*/
    message_hdr_req* msgHdr = ( message_hdr_req* ) msg;
    result = MsgQCreate ( REQUEST_QUEUE, MAX_MSG_Q_SIZE , MSG_Q_FIFO, &err );
    User::LeaveIfError ( result );
    /* Send Message to queueOne */
    if ( msgHdr->message_type == EUpdateOwnAvtar )
        {
        TInt header_size = sizeof( message_hdr_req );
        char* one_pdu = ( char* ) User::AllocLC ( ONE_K_OPENC_FIX );
        //run a loop for rest of the data and keep track of the case of nBytes being 
        //multiple of 1020 - sizeof(msghdr) and it being not
        //Amount of payload that can be sent
        TInt single_read = ONE_K_OPENC_FIX - header_size;
        //Data recieved from PublishOwnPresenceL has message header at begining
        TInt actual_data = nBytes - header_size;
        //No of packets needed to send the image data
        TInt total_packets = (TInt)ceil( ( double ) ( actual_data ) / single_read );
        //This offset moves thru the msg pointer
        TInt navigate_offset = header_size;
        message_hdr_req msg_hdr;
        memset( (void*)&msg_hdr, '\0', header_size );
        msg_hdr.message_type = EUpdateOwnAvtar;
        for ( TInt i = 0; i < total_packets; i++ )
            {
            //till the last packet size_tobe_sent will be ONE_K_OPENC_FIX
            //last packet data is actual_data % single_read if less than single_read else ONE_K_OPENC_FIX
            TInt size_tobe_sent = ( i < total_packets - 1 ) ? ONE_K_OPENC_FIX : 
            ( actual_data % single_read ? 
                actual_data % single_read  + header_size : ONE_K_OPENC_FIX );

            if ( i < total_packets - 1 )
                {
                msg_hdr.continue_flag = 1;
                }
            else 
                {
                msg_hdr.continue_flag = 0;
                }

            //memcpy ( msg + header_size , msg + navigate_offset, size_tobe_sent - header_size );
            memcpy( one_pdu , &msg_hdr, header_size );
            memcpy( one_pdu + header_size, msg + navigate_offset, size_tobe_sent - header_size );
            result = MsgQSend ( REQUEST_QUEUE, one_pdu, size_tobe_sent, 
                    MSG_PRI_NORMAL, timeout, &err );
            User::LeaveIfError ( result );
            navigate_offset += single_read;
            }
        CleanupStack::PopAndDestroy( one_pdu );
        one_pdu = NULL;
        }
    else
        {
        result = MsgQSend ( REQUEST_QUEUE, msg, nBytes, MSG_PRI_NORMAL, timeout, &err );

        User::LeaveIfError ( result );
        }
	LOGGER ( TXT ( "CWaitTimer::SendData  end" ) );

	return iOpId;

	}
// -----------------------------------------------------------------------------
// CWaitTimer::ListenConatcsChange()  //contacts
// -----------------------------------------------------------------------------
//
void CWaitTimer::ListenContactsChange ( TRequestStatus& aStatus )
	{
	LOGGER ( TXT ( "CWaitTimer::ListenContactsChange Start" ) );

	if ( !iContactsChangeStatus )
		{
		iContactsChangeStatus = &aStatus;
		aStatus = KRequestPending;
		}
	LOGGER ( TXT ( "CWaitTimer::ListenContactsChange End" ) );	
	}

// -----------------------------------------------------------------------------
// CWaitTimer::CancelListening()
// -----------------------------------------------------------------------------
//
void CWaitTimer::CancelContactsChangeListening()
	{
	LOGGER ( TXT ( "CWaitTimer::CancelContactsChangeListening Start" ) );

	if ( iContactsChangeStatus )
		{
		User::RequestComplete ( iContactsChangeStatus, KErrCancel );
		iContactsChangeStatus = NULL;
		}

	LOGGER ( TXT ( "CWaitTimer::CancelContactsChangeListening End" ) );
	}


// -----------------------------------------------------------------------------
// CWaitTimer::ListenIncomingData()  //contacts
// -----------------------------------------------------------------------------
//
void CWaitTimer::ListenIncomingData ( TRequestStatus& aStatus )
	{
	LOGGER ( TXT ( "CWaitTimer::ListenIncomingData Start" ) );

	if ( !iIncReqStatus )
		{
		iIncReqStatus = &aStatus;
		aStatus = KRequestPending;
		}
	}

// -----------------------------------------------------------------------------
// CWaitTimer::IncomingDataCount()  //contacts
// -----------------------------------------------------------------------------
//
TInt CWaitTimer::IncomingDataCount()
	{
	LOGGER ( TXT ( "CWaitTimer::IncomingDataCount Start" ) );

	return iIncomingData.Count();
	}
// -----------------------------------------------------------------------------
// CWaitTimer::SearchDataCount()  //Searched data
// -----------------------------------------------------------------------------
//
TInt CWaitTimer::SearchDataCount()
	{
	return iSearchElements.Count();
	}
// -----------------------------------------------------------------------------
// CWaitTimer::ContactsChangeResponseCount()  //Searched data
// -----------------------------------------------------------------------------
//
TInt CWaitTimer::ContactsChangeResponseCount()
	{
	return iContactChangeList.Count();
	}	
// -----------------------------------------------------------------------------
// CWaitTimer::CancelListening()
// -----------------------------------------------------------------------------
//
void CWaitTimer::CancelListening()
	{
	LOGGER ( TXT ( "CWaitTimer::CancelListening Start" ) );

	if ( iIncReqStatus )
		{
		User::RequestComplete ( iIncReqStatus, KErrCancel );
		iIncReqStatus = NULL;
		}

	LOGGER ( TXT ( "CWaitTimer::CancelListening End" ) );
	}

// -----------------------------------------------------------------------------
// CWaitTimer::ListenIncomingMsg()  // messages
// -----------------------------------------------------------------------------
//
TInt CWaitTimer::ListenIncomingMsg ( TRequestStatus& aStatus )
	{
	LOGGER ( TXT ( "CWaitTimer::ListenIncomingMsg Start" ) );

	if ( !iIncMsgReqStatus )
		{
		iIncMsgReqStatus = &aStatus;
		aStatus = KRequestPending;
		}

	LOGGER ( TXT ( "CWaitTimer::ListenIncomingMsg End Count is %d" ), iIncomingMsg.Count() );

	return iIncomingMsg.Count();
	}

// -----------------------------------------------------------------------------
// CWaitTimer::ListenIncomingPresenceL()  // presence notifications
// -----------------------------------------------------------------------------
//
TInt CWaitTimer::ListenIncomingPresence ( TRequestStatus& aStatus )
	{
	LOGGER ( TXT ( "CWaitTimer::ListenIncomingPresence Start" ) );

	if ( !iIncPresReqStatus )
		{
		iIncPresReqStatus = &aStatus;
		aStatus = KRequestPending;
		}

	LOGGER ( TXT ( "CWaitTimer::ListenIncomingPresence End Count is %d" ), iIncomingPres.Count() );

	return iIncomingPres.Count();
	}
// -----------------------------------------------------------------------------
// CWaitTimer::ListenAddNotification()  // Add contact notifications
// -----------------------------------------------------------------------------
//
TInt CWaitTimer::ListenAddNotification ( TRequestStatus& aStatus )
	{
	LOGGER ( TXT ( "CWaitTimer::ListenAddNotification Start" ) );

	if ( !iIncAddReqStatus )
		{
		iIncAddReqStatus = &aStatus;
		aStatus = KRequestPending;
		}

	LOGGER ( TXT ( "CWaitTimer::ListenAddNotification End Count is %d" ), iAddNotification.Count() );

	return iAddNotification.Count();
	}	
// -----------------------------------------------------------------------------
// CWaitTimer::ListenIncomingServerError()  // presence notifications
// -----------------------------------------------------------------------------
//
TInt CWaitTimer::ListenIncomingServerError ( TRequestStatus& aStatus )
	{
	LOGGER ( TXT ( "CWaitTimer::ListenIncomingServerError Start" ) );

	if ( !iIncErrorReqStatus )
		{
		iIncErrorReqStatus = &aStatus;
		aStatus = KRequestPending;
		}

	LOGGER ( TXT ( "CWaitTimer::ListenIncomingServerError End Count is %d" ), iIncomingServerError.Count() );

	return iIncomingServerError.Count();
	}
// CWaitTimer::CancelListeningMsg()
// -----------------------------------------------------------------------------
//
void CWaitTimer::CancelListeningMsg()
	{
	LOGGER ( TXT ( "CWaitTimer::CancelListening Start" ) );

	if ( iIncMsgReqStatus )
		{
		User::RequestComplete ( iIncMsgReqStatus, KErrCancel );
		iIncMsgReqStatus = NULL;
		}

	LOGGER ( TXT ( "CWaitTimer::CancelListening End" ) );
	}
// -----------------------------------------------------------------------------
// CWaitTimer::CancelListeningPres()
// -----------------------------------------------------------------------------
//
void CWaitTimer::CancelListeningPres()
	{
	LOGGER ( TXT ( "CWaitTimer::CancelListeningPres Start" ) );

	if ( iIncPresReqStatus )
		{
		User::RequestComplete ( iIncPresReqStatus, KErrCancel );
		iIncPresReqStatus = NULL;
		}

	LOGGER ( TXT ( "CWaitTimer::CancelListeningPres End" ) );
	}
// -----------------------------------------------------------------------------
// CWaitTimer::CancelListeningAddNotication()
// -----------------------------------------------------------------------------
//
void CWaitTimer::CancelListeningAddNotication()
	{
	LOGGER ( TXT ( "CWaitTimer::CancelListeningAddNotication Start" ) );

	if ( iIncAddReqStatus )
		{
		User::RequestComplete ( iIncAddReqStatus, KErrCancel );
		iIncAddReqStatus = NULL;
		}

	LOGGER ( TXT ( "CWaitTimer::CancelListeningAddNotication End" ) );
	}
// -----------------------------------------------------------------------------
// CWaitTimer::CancelListeningServerErrors()
// -----------------------------------------------------------------------------
//
void CWaitTimer::CancelListeningServerErrors()
	{
	LOGGER ( TXT ( "CWaitTimer::CancelListeningServerErrors Start" ) );

	if ( iIncErrorReqStatus )
		{
		User::RequestComplete ( iIncErrorReqStatus, KErrCancel );
		iIncErrorReqStatus = NULL;
		}

	LOGGER ( TXT ( "CWaitTimer::CancelListeningServerErrors End" ) );
	}

// -----------------------------------------------------------------------------
// CWaitTimer::StartListeningL()
// -----------------------------------------------------------------------------
//

void CWaitTimer::StartListeningL()
	{
	LOGGER ( TXT ( "CWaitTimer::StartListening Start" ) );
//	Cancel (); // Cancel any request, just to be sure
//	iProperty.Subscribe(iStatus);
	iTimer.After ( iStatus, KTimerInterval );
	SetActive (); // Tell scheduler a request is active
	LOGGER ( TXT ( "CWaitTimer::StartListening End" ) );

	}

// -----------------------------------------------------------------------------
// CWaitTimer::RunL()
// -----------------------------------------------------------------------------
//

void CWaitTimer::RunL()
	{

	int timeout = IPC_NOWAIT; //TIME_OUT;
	int err = 0;
	int status = 0;
	int size_msg = sizeof ( message_hdr_resp );
	TBool msgreadcontinue = EFalse;
	message_hdr_resp* msg_struct = NULL;
	char* rmsg = NULL;
	
	if( !iResponseMsgQCreated )
		{
		status = MsgQCreate ( RESPONSE_QUEUE, MAX_MSG_Q_SIZE, MSG_Q_FIFO, &err );
		iResponseMsgQCreated = ETrue;
		}

	if(-1 == status)
		{
		LOGGER ( TXT ( "CWaitTimer::leave " ) );  
		User::Leave( status );
		}	
    do
       {
        rmsg = ( char* ) User::AllocLC ( MAX_MSG_SIZE );

	  // Receive Message from queueTwo
    
        status = MsgQReceive ( RESPONSE_QUEUE, rmsg, MAX_MSG_SIZE, timeout, &err );
        User::LeaveIfError ( err );
        //size should be atleast size of message_hdr_resp
        if( -1 == status )
            {
		    CleanupStack::PopAndDestroy ( rmsg );
		    }

        if ( status >= size_msg )
  		    {
  		    LOGGER ( TXT ( "CWaitTimer::MsgQReceive responce recvd" ) );
		    msg_struct = ( message_hdr_resp* )rmsg ;
		    LOGGER ( TXT ( "CWaitTimer::data recvd of type %d" ), msg_struct->hdr_req.message_type );
		
		    switch( msg_struct->hdr_req.message_type )
			      {
			      TInt operationindex;
		          case EText_Message_Receive:
				      {
				      LOGGER ( TXT ( "CWaitTimer::EText_Message_Receive" ) );
				      // complete prfw request
				      iIncomingMsg.AppendL ( rmsg );
				      if ( iIncMsgReqStatus )
				          {
				          User::RequestComplete ( iIncMsgReqStatus, KErrNone );
				          iIncMsgReqStatus = NULL;
				          }
				      CleanupStack::Pop( rmsg );
				      break;
				      }
		          case EPresenceNotification:
		              {

        			  LOGGER ( TXT ( "CWaitTimer::EPresence_Notification_Received" ) );
            	      // complete prfw request
            		  //	iIncomingPres.AppendL ( rmsg );
            		  iIncomingPres.Insert (rmsg,0);
            		  if ( iIncPresReqStatus )
            		      {
            		      User::RequestComplete ( iIncPresReqStatus, KErrNone );
            		      iIncPresReqStatus = NULL;
            		      }
            		  CleanupStack::Pop( rmsg );
            		  break;
		              }
		          case ETrying_To_Add_Contact_Publish:
		              {
		              LOGGER ( TXT ( "CWaitTimer::ETrying_To_Add_Contact" ) );
		              // complete prfw request
		              iAddNotification.AppendL ( rmsg );
		              if ( iIncAddReqStatus )
		                  {
		                  User::RequestComplete ( iIncAddReqStatus, KErrNone );
		                  iIncAddReqStatus = NULL;
		                  }
		              CleanupStack::Pop( rmsg );
		              break;
		              }
		        case ESubscribe_Remote_Pending:
		        case ETrying_To_Add_Contact_Known:
		            {
		            LOGGER ( TXT ( "CWaitTimer::Sync of contacts state" ) );
		            iContactChangeList.Append(rmsg);
		            if ( iContactsChangeStatus )
		                {
		                User::RequestComplete ( iContactsChangeStatus, KErrNone );
		                iContactsChangeStatus = NULL;
		                }
		            CleanupStack::Pop( rmsg );
		            break;    
		            }

		        case ESubscribe_RP_Accepted:
		            {
		            CleanupStack::PopAndDestroy( rmsg );
		            break;    
		            }
		       case EPublish_RP_Accepted:
		            {
		            CleanupStack::PopAndDestroy( rmsg );
		            break;
		            }	   
		        case EPublish_Removed_Or_Rejected:
		            {
		            LOGGER ( TXT ( "CWaitTimer::Sync of contacts state" ) );
		            iContactChangeList.Append(rmsg);
		            if ( iContactsChangeStatus )
		                {
		                User::RequestComplete ( iContactsChangeStatus, KErrNone );
		                iContactsChangeStatus = NULL;
		                }
		            CleanupStack::Pop( rmsg );
		            break;    
		            }
		          case ESubscribe_Removed_Or_Rejected:
		              {
		              LOGGER ( TXT ( "CWaitTimer::Sync of contacts state" ) );
		              iContactChangeList.Append(rmsg);
		              if ( iContactsChangeStatus )
		                  {
		                  User::RequestComplete ( iContactsChangeStatus, KErrNone );
		                  iContactsChangeStatus = NULL;
		                  }
		              CleanupStack::Pop( rmsg );
		              break;	
		              }
    			case ECurrent_Member_Contacts:
    				{
    				iFetchingContinue = EFalse;
    				// complete ximpfw request
    				iIncomingData.AppendL ( rmsg );
    				if(msg_struct->continue_flag == 1)
    					{
    					iFetchingContinue = ETrue;
    					}
    				else
    					{
    					iFetchingStep++ ;	// move to next step
    					}
					
    				if ( iIncReqStatus && iFetchingStep == EDataFetchComplete )// complete request only if step is 1
    					{
    					User::RequestComplete ( iIncReqStatus, KErrNone );
    					iIncReqStatus = NULL;
    					}
    				CleanupStack::Pop( rmsg );	
    				break;	
    				}
    			case ELocal_Pending_Contacts:
    				{
    				LOGGER ( TXT ( "CWaitTimer::ELocal_Pending_Contacts" ) );
                    // complete prfw request
    				iAddNotification.AppendL ( rmsg );  
    				if ( iIncAddReqStatus )
    				    {
                        LOGGER ( TXT ( "CWaitTimer::ELocal_Pending_Contacts" ) );			                    
                        User::RequestComplete ( iIncAddReqStatus, KErrNone );
                        iIncAddReqStatus = NULL;
                        }
                    CleanupStack::Pop( rmsg );                
    				break;	
    				}
    			case ERemote_Pending_Contacts:
        			{
        			LOGGER ( TXT ( "CWaitTimer::ECurrent_Member_Contacts" ) );
        			iFetchingContinue = EFalse;
        			// complete ximpfw request
        			iIncomingData.AppendL ( rmsg );
        			PendingPresenceContactsL(rmsg);
        			if(msg_struct->continue_flag == 1)
        				{
        				iFetchingContinue = ETrue;
        				}
        			else
        				{
        				iFetchingStep++ ;	// move next step
        				}	
        			if ( iIncReqStatus && iFetchingStep == EDataFetchComplete) // complete request only if step is 1
        				{
        				User::RequestComplete ( iIncReqStatus, KErrNone );
        				iIncReqStatus = NULL;
        				}
        			CleanupStack::Pop( rmsg );
        			break;
        			}
    			case ESend_Error:
    				{
    				LOGGER ( TXT ( "CWaitTimer::ESend_Error" ) );
    				// complete ximpfw request
    				iIncomingServerError.AppendL ( rmsg );
    				if ( iIncErrorReqStatus )
    					{
    					User::RequestComplete ( iIncErrorReqStatus, KErrNone );
    					iIncErrorReqStatus = NULL;
    					}
    				CleanupStack::Pop( rmsg );
    				break;
    				}
    				
    			case EUserEndGprs: 
    			    LOGGER ( TXT ( "CWaitTimer::EUserCancelAccessPoint start" ) );
    			    
    			case EServer_DisConnect_Request:
    				{
    				iServerDisconnected = ETrue;
    				LOGGER ( TXT ( "CWaitTimer::EServer_DisConnect_Request start" ) );
    				CancelListeningMsg();
    				CancelListening();
    				CancelListeningPres();
    				CancelListeningAddNotication();
    				CancelListeningServerErrors();
                    CancelContactsChangeListening();
                
    				MXIMPObjectFactory& prfwObjFact = iConnMan.HandleToHost().ObjectFactory();
    				MXIMPStatus* status = prfwObjFact.NewStatusLC();// status
    				status->SetResultCode( KErrDisconnected );
    				iConnMan.HandleToHost().HandleConnectionTerminated( status );
 					//IssueReleaseRequestL();//Release the connection
    				CleanupStack::PopAndDestroy(); // status
    				CleanupStack::Pop( rmsg );
    				LOGGER ( TXT ( "CWaitTimer::EServer_DisConnect_Request end" ) );
    				break;
    				}
    			case ESearch_State_Finished:
    				{
                    LOGGER ( TXT ( "CWaitTimer::ESearch_State_Finished" ) );
    				operationindex = ( FindOperationL ( iOpId, &COssSendDataOperation::OperationId ) );
    
    				if ( operationindex != KErrNotFound )
    					{
    					LOGGER ( TXT ( "CWaitTimer::FindOperationL found" ) );
    					iOperations[ operationindex ]->SetResponse ( rmsg ); //ownership of rmsg is transferred
    					iOperations[ operationindex ]->CompletedOperation ( KErrNone );
    					}
    				CleanupStack::Pop( rmsg );	
    				break;	
    				}
    			case ESearch:
    				{
    				LOGGER ( TXT ( "CWaitTimer::ESearch" ) );
    				if ( msg_struct->response != 0 ) 
    					{
    					LOGGER ( TXT ( "CWaitTimer::ESearch : Result" ) );
                        char* pResponse = ( char* ) User::AllocLC ( status );
    					memset ( pResponse, '\0', status );
                        memcpy ( pResponse, rmsg, status );
    					iSearchElements.AppendL ( pResponse );
    				    CleanupStack::Pop( pResponse );
    		            CleanupStack::PopAndDestroy( rmsg );
    					}
    				else
    					{
    					LOGGER ( TXT ( "CWaitTimer::ESearch: ERROR !!" ) );
    					operationindex = ( FindOperationL ( iOpId, &COssSendDataOperation::OperationId ) );
    					iOperations[ operationindex ]->SetResponse ( rmsg ); //ownership of rmsg is transferred
    				    iOperations[ operationindex ]->CompletedOperation ( KErrNotSupported );// for all errors
    				    CleanupStack::Pop( rmsg );
    				    // send  not supported, since the error mapping is  not done 	
    					}	
    				break;
    				}
    			case ESearch_Get_Keys:
    				{
    				
    				LOGGER ( TXT ( "CWaitTimer::ESearch_Get_Keys" ) );
    				operationindex = ( FindOperationL ( iOpId, &COssSendDataOperation::OperationId ) );
    
    				if ( operationindex != KErrNotFound )
    					{
    					LOGGER ( TXT ( "CWaitTimer::FindOperationL found" ) );
    					iOperations[ operationindex ]->SetResponse ( rmsg ); //ownership of rmsg is transferred
    					iOperations[ operationindex ]->CompletedOperation ( KErrNone );
    					}
    				CleanupStack::Pop( rmsg );
    				LOGGER ( TXT ( "CWaitTimer::ESearch_Get_Keys end" ) );
    				break;
    				}
    			case ESearch_State_During :
    				{
    				LOGGER ( TXT ( "CWaitTimer::ESearch_State_During" ) );
    				iSearchElements.ResetAndDestroy();
    				CleanupStack::PopAndDestroy( rmsg );
    				LOGGER ( TXT ( "CWaitTimer::ESearch_State_During end" ) );
    				break;	
    				}
			case EUpdateOwnAvtar :	
			    {
                LOGGER ( TXT ( "CWaitTimer::EUpdateOwnAvtar" ) );
                operationindex = ( FindOperationL ( iOpId, &COssSendDataOperation::OperationId ) );

                if ( operationindex != KErrNotFound )
                    {
                    LOGGER ( TXT ( "CWaitTimer::FindOperationL found" ) );

                    iOperations[ operationindex ]->SetResponse ( rmsg ); //ownership of rmsg is transferred
                    iOperations[ operationindex ]->CompletedOperation ( KErrNone );
                    }
                CleanupStack::Pop( rmsg );
                break;
			    }
    			default:
    					{
    					LOGGER ( TXT ( "CWaitTimer::default start" ) );
    					operationindex = ( FindOperationL ( iOpId, &COssSendDataOperation::OperationId ) );
    
    					if ( operationindex != KErrNotFound )
    						{
    						LOGGER ( TXT ( "CWaitTimer::FindOperationL found" ) );
    
    						iOperations[ operationindex ]->SetResponse ( rmsg ); //ownership of rmsg is transferred
    						iOperations[ operationindex ]->CompletedOperation ( KErrNone );
    						}
    					CleanupStack::Pop( rmsg );
    					LOGGER ( TXT ( "CWaitTimer::default end" ) );
    					break;
    					}
			      }

		    TInt pendingMsgCount = MsgQCheck(RESPONSE_QUEUE, &err );
		    if( pendingMsgCount > 0)
		        {
		        msgreadcontinue = ETrue;
		        }
		    else 
		        {
		        msgreadcontinue = EFalse;
		        }
		    LOGGER ( TXT ( "CWaitTimer::pendingMsgCount is %d" ), pendingMsgCount );   
  		    }
       }while( msgreadcontinue );
		/*
		// there is no pending message in msgqueue,
		// set active and subscribe for incomming queue message
		iProperty.Subscribe(iStatus);
		SetActive(); // Tell scheduler a request is active	*/
		
		iTimer.After( iStatus, KTimerInterval );
		SetActive();
	}
// -----------------------------------------------------------------------------
// CWaitTimer::PendingPresenceContactsL()
// -----------------------------------------------------------------------------
//
void CWaitTimer::PendingPresenceContactsL(char* aRmessage)
    {
    char* prmsg = NULL;
    prmsg = aRmessage;
    HBufC16 *contactName = NULL;
    HBufC* name = NULL;
    int len = 0;
    if( aRmessage )
        {
        prmsg += sizeof ( message_hdr_resp );
        MPresenceBuddyInfo2* buddyPresInfo = MPresenceBuddyInfo2::NewLC();
   
        MPresenceCacheWriter2* presenceCacheWriter = MPresenceCacheWriter2::CreateWriterL();
        CleanupDeletePushL(presenceCacheWriter);
        while(1)
            {
            len = strlen(prmsg) + 1;
            if (1 == len)
                {
                break;
                }
            char* contact = prmsg;  
            prmsg += len;

            contactName = OssProtocolAdapUtils::ConvertCharToTUint16LC( contact );
            LOGGER ( TXT ( "CWaitTimer::PendingPresenceContacts:ContactName:%S " ), contactName );

            //  contacts.AppendL(contactName);
            name = HBufC::NewLC( contactName->Length() + iConnMan.ServiceName().Length() + KColon().Length() );
            TPtr namePtr( name->Des() );
            namePtr.Zero();
            namePtr.Append(iConnMan.ServiceName() ); // prepend service name
            namePtr.Append(KColon);
            namePtr.Append(contactName->Des() );
            buddyPresInfo->SetIdentityL(namePtr);
            LOGGER ( TXT ( "CPresenceNotificationHandler::ProcessIncomingDataL  :ContactName:%S " ), contactName ); 
    
            buddyPresInfo->SetAnyFieldL(KExtensionKey,KPendingRequestExtensionValue());
            CleanupStack::PopAndDestroy(2);//name,contactName
            name = NULL;
            contactName = NULL;
            // Writing into Presence Cache
            TInt cacheerror = presenceCacheWriter->WritePresenceL(buddyPresInfo);
            User::LeaveIfError ( cacheerror);
           
            } 
        CleanupStack::PopAndDestroy(2);//presenceCacheWriter,buddyPresInfo

        }
    }
// -----------------------------------------------------------------------------
// CWaitTimer::ResponseL()
// -----------------------------------------------------------------------------
//

char* CWaitTimer::ResponseL ( TInt aTransId )
	{
	
	if ( aTransId == 0 )   // for contact list
		{
		if ( iIncomingData.Count() == 0 )
			{
			User::Leave ( KErrNotFound );
			}

		// take first one from the array
		char* buff = iIncomingData[ 0 ];

		iIncomingData.Remove ( 0 );
		iIncomingData.Compress();
		return buff;
		}

	if ( aTransId == 1 )     //for receive message
		{
		if ( iIncomingMsg.Count() == 0 )
			{
			User::Leave ( KErrNotFound );
			}

		// take first one from the array
		char* buff = iIncomingMsg[ 0 ];

		iIncomingMsg.Remove ( 0 );

		return buff;
		}
	if ( aTransId == 2 )     //for presence notifications
		{
		TInt pCount = iIncomingPres.Count();
		
		if ( pCount == 0 )
			{
			User::Leave ( KErrNotFound );
			}

		// take first one from the array
		char* buff = iIncomingPres[ pCount-1 ];

		iIncomingPres.Remove ( pCount-1 );
		iIncomingPres.Compress();
		return buff;
		}
	if ( aTransId == 3 )     //for send error
		{
		if ( iIncomingServerError.Count() == 0 )
			{
			User::Leave ( KErrNotFound );
			}

		// take first one from the array
		char* buff = iIncomingServerError[ 0 ];

		iIncomingServerError.Remove ( 0 );

		return buff;
		}
	if ( aTransId == 4 )     //for Add notifications
		{
		if ( iAddNotification.Count() == 0 )
			{
			User::Leave ( KErrNotFound );
			}

		// take first one from the array
		char* buff = iAddNotification[ 0 ];

		iAddNotification.Remove ( 0 );

		return buff;
		}			
	if( aTransId == 5 )	 // search results 
		{
	    // take first one from the array
	    char*  buff=NULL;
	    
		if ( iSearchElements.Count() != 0 )
			{
		    buff = iSearchElements[ 0 ];
			iSearchElements.Remove ( 0 );
			iSearchElements.Compress();
			}
       	else 
	        {
	       	TInt x ( FindOperationL ( 6, &COssSendDataOperation::OperationId ) );
			if( x != -1)
				{	// is operation completed?
				TRequestStatus* status = iOperations[ x ]->Status();

				if ( status && ( *status == KRequestPending ) )
					{
					User::Leave ( KErrNotReady );
					}
				delete iOperations[ x ];
				iOperations.Remove ( x );
				}
	
	        }
	
		return buff; // return the  buffer 	
		}
	if ( aTransId == 200 )     //for contact sync
		{
		if ( iContactChangeList.Count() == 0 )
			{
			User::Leave ( KErrNotFound );
			}

		// take first one from the array
		char* buff = iContactChangeList[ 0 ];

		iContactChangeList.Remove ( 0 );
        iContactChangeList.Compress();
		return buff;
		}			
	// try to find operation
	TInt x ( FindOperationL ( aTransId, &COssSendDataOperation::OperationId ) );

	// is operation completed?
	TRequestStatus* status = iOperations[ x ]->Status();

	if ( status && ( *status == KRequestPending ) )
		{
		User::Leave ( KErrNotReady );
		}

	char* buff = iOperations[ x ]->Response();

	delete iOperations[ x ];
	iOperations.Remove ( x );
	return buff;
	}

// -----------------------------------------------------------------------------
// CWaitTimer::RunError()
// -----------------------------------------------------------------------------
//

TInt CWaitTimer::RunError ( TInt aError )
	{
	return aError;
	}

// =============================================================================
// =============== New private Functions of the base class =====================
// =============================================================================

// -----------------------------------------------------------------------------
// CWaitTimer::FindOperation()
// Find operation in array
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CWaitTimer::FindOperation (
    TInt aOpId,
    TInt ( COssSendDataOperation:: *aIdFunc ) () const ) const
	{
	LOGGER ( TXT ( "CWaitTimer::FindOperation Start" ) );
	TInt count ( iOperations.Count() );

	for ( TInt x ( 0 ) ; x < count ; ++x )
		{
		if ( aOpId == ( ( *iOperations[ x ] ).*aIdFunc ) () )
			{
			LOGGER ( TXT ( "CWaitTimer::FindOperation Returns %d" ), x );
			return x;
			}
		}

	LOGGER ( TXT ( "CWaitTimer::FindOperation End" ) );

	return KErrNotFound;
	}

// -----------------------------------------------------------------------------
// CWaitTimer::FindOperationL()
// Find operation in array, leave if not found
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CWaitTimer::FindOperationL (
    TInt aOpId,
    TInt ( COssSendDataOperation:: *aIdFunc ) () const ) const
	{
	LOGGER ( TXT ( "CWaitTimer::FindOperation Start" ) );
	TInt x ( FindOperation ( aOpId, aIdFunc ) );

	LOGGER ( TXT ( "CWaitTimer::FindOperation End Returns %d" ), x );

	return x;
	}

// -----------------------------------------------------------------------------
// CWaitTimer::IssueReleaseRequestL()
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CWaitTimer::IssueReleaseRequestL()
	{
	LOGGER ( TXT ( "CWaitTimer::IssueReleaseRequestL Start" ) );
	int err = 0;
	int timeout = NO_WAIT;
	message_hdr_req *msgHdr = NULL;
	msgHdr = ( message_hdr_req* ) User::AllocLC(sizeof ( message_hdr_req ));
	memset ( msgHdr, '\0', sizeof ( message_hdr_req ) );
	msgHdr->message_type = EKill_Process;
	
	TInt nBytes = sizeof ( message_hdr_req );

	MsgQCreate ( REQUEST_QUEUE, MAX_MSG_Q_SIZE , MSG_Q_FIFO, &err );
	
	MsgQSend ( REQUEST_QUEUE, ( char* ) msgHdr , nBytes, MSG_PRI_NORMAL, timeout, &err );
	
	CleanupStack::PopAndDestroy ( msgHdr );
	
	LOGGER ( TXT ( "CWaitTimer::IssueReleaseRequestL end" ) );

	}
// ---------------------------------------------------------------------------
// CWaitTimer::IsServerDisconnect()
// ---------------------------------------------------------------------------
//	
TBool CWaitTimer::IsServerDisconnect()
	{
	return iServerDisconnected;	
	}
// ---------------------------------------------------------------------------
// CWaitTimer::IsFetchContactsCompleted()
// ---------------------------------------------------------------------------
//  
TBool CWaitTimer::IsFetchContactsCompleted()
    {
    if(iFetchingStep == EDataFetchComplete)
        {
        return ETrue;
        }
    return EFalse;
    }

	
// End of file
