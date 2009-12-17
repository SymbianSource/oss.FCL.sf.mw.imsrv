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
* Description: uscontextobserver.cpp
*
*/

#include "uscontextobserver.h"

#include <ximpidentity.h>
#include <presenceinfofieldvaluetext.h>
#include <presenceinfofieldvalueenum.h>
#include <ximpstatus.h>
#include <ximpcontextstateevent.h>
#include <ximprequestcompleteevent.h>
#include <presentitypresenceevent.h>
#include <presentitygrouplistevent.h>
#include <presentitygroupinfo.h>
#include <presentitygroupcontentevent.h>
#include <presentitygroupmemberinfo.h>
#include <presencegrantrequestlistevent.h>
#include <presenceblocklistevent.h>
#include <presentitypresenceevent.h>
#include <presencewatcherlistevent.h>
#include "ossadapmt.h"
#include <ximpdatasubscriptionstate.h>
#include <presencewatcherinfo.h>
#include "ximpcontextstate.h"
#include <presenceinfo.h>
#include <servicepresenceinfo.h>
#include <devicepresenceinfo.h>
#include <presencegrantrequestinfo.h>
#include <presenceblockinfo.h>
#include <presenceinfofieldcollection.h>
#include <personpresenceinfo.h>
#include <presenceinfofield.h>

#include "imconversationevent.h"
#include <searchevent.h>

#include "imconversationinfo.h"
#include <searchinfo.h>
#include <searchkeysevent.h>
#include <searchkeyinfo.h>

#include <e32math.h>
#include <f32file.h>
#include <utf.h>
// ============================ MEMBER FUNCTIONS ===============================

// CONSTRUCTION
CUSContextObserver* CUSContextObserver::NewLC()
	{
	CUSContextObserver* self = new ( ELeave ) CUSContextObserver();
	CleanupStack::PushL ( self );
	return self;
	}


CUSContextObserver::~CUSContextObserver()
	{
	}


CUSContextObserver::CUSContextObserver()
	{
	}



// ===========================================================================
// PUBLIC FUNCTIONS
// ===========================================================================
//
void CUSContextObserver::WaitOpToCompleteL ( const TXIMPRequestId& aOpToWait )
	{
	iReqToWait = aOpToWait;

	iWait.Start();

	}

/*void CUSContextObserver::WaitCompleteL()
 {
 iWait.AsyncStop();
 }*/

// ===========================================================================
// FROM MXIMPContextObserver
// ===========================================================================
//
void CUSContextObserver::HandlePresenceContextEvent (
    const MXIMPContext& /*aContext*/,
    const MXIMPBase& aEvent )
	{

	TOssAdapMtLogger::Log ( _L ( "HandlePresenceContextEvent called" ) );

	TInt32 eventId = aEvent.GetInterfaceId();

	switch ( aEvent.GetInterfaceId() )
		{
			_LIT ( KDir, "EVENT_LOG" );  // here we hv to write a folder name in wch we want to create log file
			_LIT ( KFile, "event.txt" );          //here we hv to write a file name in wch we want to log default path is  " c:/Logs/"

		case MXIMPRequestCompleteEvent::KInterfaceId:
				{
				TOssAdapMtLogger::Log ( _L ( "CUSContextObserver::MXIMPRequestCompleteEvent() start" ) );

				const MXIMPRequestCompleteEvent* complEvent =
				    TXIMPGetInterface< const MXIMPRequestCompleteEvent >::From ( aEvent,
				            MXIMPBase::EPanicIfUnknown );

				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "*************BEGIN******************" ) );
				_LIT ( KMsg, "Recvd RequestCompleteEvent " );         // here we hv to write message or text wch we want to write in log file
				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, KMsg );

				if ( iWait.IsStarted() && ( complEvent->RequestId() == iReqToWait ) )
					{
					iReqResult = complEvent->CompletionResult().ResultCode();
					RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "Error code for the request is %d " ), iReqResult );
					iWait.AsyncStop();
					}

				TOssAdapMtLogger::Log ( _L ( "CUSContextObserver::MXIMPRequestCompleteEvent() end" ) );

				break;
				}

		case MXIMPContextStateEvent::KInterfaceId:
				{
				const MXIMPContextStateEvent* ctxtStateEvent =
				    TXIMPGetInterface< const MXIMPContextStateEvent >::From ( aEvent,
				            MXIMPBase::EPanicIfUnknown );
				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "*************BEGIN******************" ) );
				_LIT ( KMsg, "Recvd PresenceContextStateEvent " );         // here we hv to write message or text wch we want to write in log file
				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, KMsg );
				const MXIMPStatus* fwStatus = ctxtStateEvent->StateChangeReason();
				const MXIMPContextState& cState = ctxtStateEvent->ContextState();
				MXIMPContextState::TState state = cState.ContextState();
				break;
				}

		case MPresentityGroupListEvent::KInterfaceId:
				{
				const MPresentityGroupListEvent* groupListEvent =
				    TXIMPGetInterface< const MPresentityGroupListEvent >::From ( aEvent,
				            MXIMPBase::EPanicIfUnknown );

				TBuf<100> sdstate;
				TBuf<100> ssstate;
				_LIT ( Kna, "   Susbcription state is unavailable" );
				_LIT ( Kava, "   Susbcription state is available" );
				_LIT ( KDef, "   Susbcription state is ERROR" );

				const  MXIMPDataSubscriptionState&  dstate = groupListEvent->DataSubscriptionState();

				switch ( dstate.SubscriptionState() )
					{

					case 0:
						ssstate.Copy ( Kna );
						break;

					case 1:
						ssstate.Copy ( Kava );
						break;

					default:
						ssstate.Copy ( KDef );
						break;
					}

				_LIT ( Kdna, "   Data state is unavailable" );

				_LIT ( Kdava, "   Data state is available" );
				_LIT ( KdDef, "   Data state is ERROR" );


				switch ( dstate.SubscriptionState() )
					{

					case 0:
						sdstate.Copy ( Kdna );
						break;

					case 1:
						sdstate.Copy ( Kdava );
						break;

					default:
						sdstate.Copy ( KdDef );
						break;
					}

				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "*************BEGIN******************" ) );

				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "Recvd PresentityGroupListEvent New:%d, Updt:%d, Disappeared:%d, Current:%d, SubscrState:%d, DataState:%d" ), groupListEvent->NewGroupsCount(), groupListEvent->UpdatedGroupsCount(), groupListEvent->DisappearedGroupsCount(), groupListEvent->CurrentGroupsCount(), dstate.SubscriptionState(), dstate.DataState() );//KMsg);
				RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, sdstate );
				RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, ssstate );
				break;
				}


		case MPresentityGroupContentEvent::KInterfaceId:
				{
				const MPresentityGroupContentEvent* groupContentEvent =
				    TXIMPGetInterface< const MPresentityGroupContentEvent >::From ( aEvent,
				            MXIMPBase::EPanicIfUnknown );
				TBuf<100> sdstate;
				TBuf<100> ssstate;
				_LIT ( Kna, "   Susbcription state is unavailable" );
				_LIT ( Kava, "   Susbcription state is available" );
				_LIT ( KDef, "   Susbcription state is ERROR" );

				const MXIMPDataSubscriptionState&  dstate = groupContentEvent->DataSubscriptionState();

				switch ( dstate.SubscriptionState() )
					{

					case 0:
						ssstate.Copy ( Kna );
						break;

					case 1:
						ssstate.Copy ( Kava );
						break;

					default:
						ssstate.Copy ( KDef );
						break;
					}

				_LIT ( Kdna, "   Data state is unavailable" );

				_LIT ( Kdava, "   Data state is available" );
				_LIT ( KdDef, "   Data state is ERROR" );


				switch ( dstate.SubscriptionState() )
					{

					case 0:
						sdstate.Copy ( Kdna );
						break;

					case 1:
						sdstate.Copy ( Kdava );
						break;

					default:
						sdstate.Copy ( KdDef );
						break;
					}


				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "*************BEGIN******************" ) );

				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "Recvd PresentityGroupContentEvent New:%d, Updt:%d, Disappeared:%d, Current:%d, SubscrState:%d, DataState:%d" ), groupContentEvent->NewMembersCount(), groupContentEvent->UpdatedMembersCount(), groupContentEvent->DisappearedMembersCount(), groupContentEvent->CurrentMembersCount(), dstate.SubscriptionState(), dstate.DataState() );
				RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, sdstate );
				RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, ssstate );
				RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, groupContentEvent->GroupId().Identity() );
				// print the list contents

				for ( TInt i = 0; i < groupContentEvent->CurrentMembersCount(); i++ )
					{
					const MPresentityGroupMemberInfo& gi = groupContentEvent->CurrentMember ( i );

					RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "Id and displayname for cur group member %d X" ), i );
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, gi.GroupMemberId().Identity() );
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, gi.GroupMemberDisplayName() );
//     EUNIT_ASSERT_EQUALS_DESC( gi.GroupMemberId().Identity(), iContactid[i], "contact id's does'nt match");
//     EUNIT_ASSERT_EQUALS_DESC( gi.GroupMemberDisplayName(), iNickname[i], "contact nickname  does'nt match");

					}

				// print the list contents
				for ( TInt i = 0; i < groupContentEvent->NewMembersCount(); i++ )
					{
					const MPresentityGroupMemberInfo& gi = groupContentEvent->NewMember ( i );


					RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "Id and displayname for new group member %d X" ), i );
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, gi.GroupMemberId().Identity() );
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, gi.GroupMemberDisplayName() );
//     EUNIT_ASSERT_EQUALS_DESC( gi.GroupMemberId().Identity(), iContactid[i], "contact id's does'nt match");
//     EUNIT_ASSERT_EQUALS_DESC( gi.GroupMemberDisplayName(), iNickname[i], "contact nickname  does'nt match");
					}


				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "*************END*******************" ) );

				break;
				}

		case MPresenceGrantRequestListEvent::KInterfaceId:
				{
				const MPresenceGrantRequestListEvent* grantreqEvent =
				    TXIMPGetInterface< const MPresenceGrantRequestListEvent >::From ( aEvent,
				            MXIMPBase::EPanicIfUnknown );
				TBuf<100> sdstate;
				TBuf<100> ssstate;
				_LIT ( Kna, "   Susbcription state is unavailable" );
				_LIT ( Kava, "   Susbcription state is available" );
				_LIT ( KDef, "   Susbcription state is ERROR" );

				const  MXIMPDataSubscriptionState&  dstate = grantreqEvent->DataSubscriptionState();

				switch ( dstate.SubscriptionState() )
					{

					case 0:
						ssstate.Copy ( Kna );
						break;

					case 1:
						ssstate.Copy ( Kava );
						break;

					default:
						ssstate.Copy ( KDef );
						break;
					}

				_LIT ( Kdna, "   Data state is unavailable" );

				_LIT ( Kdava, "   Data state is available" );
				_LIT ( KdDef, "   Data state is ERROR" );


				switch ( dstate.SubscriptionState() )
					{

					case 0:
						sdstate.Copy ( Kdna );
						break;

					case 1:
						sdstate.Copy ( Kdava );
						break;

					default:
						sdstate.Copy ( KdDef );
						break;
					}

				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "*************BEGIN******************" ) );

				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "Recvd Presentity Grant event" ) );
				RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, sdstate );
				RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, ssstate );

				TInt index = grantreqEvent->NewRequestsCount();

				for ( TInt i = 0; i < index; i++ )
					{
					const MPresenceGrantRequestInfo& grantinfo = grantreqEvent->NewRequest ( i );

					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, grantinfo.RequestorId().Identity() );
					const TDesC16 dispname = grantinfo.RequestorDisplayName();
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, dispname );
					}

				index = grantreqEvent->CurrentRequestsCount();

				for ( TInt i = 0; i < index; i++ )
					{
					const MPresenceGrantRequestInfo& grantinfo = grantreqEvent->CurrentRequest ( i );

					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, grantinfo.RequestorId().Identity() );
					const TDesC16 dispname = grantinfo.RequestorDisplayName();
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, dispname );
					}

				break;
				}

		case MPresenceBlockListEvent::KInterfaceId:
				{
				const MPresenceBlockListEvent* blockListEvent =
				    TXIMPGetInterface< const MPresenceBlockListEvent >::From ( aEvent,
				            MXIMPBase::EPanicIfUnknown );
				TBuf<100> sdstate;
				TBuf<100> ssstate;
				_LIT ( Kna, "   Susbcription state is unavailable" );
				_LIT ( Kava, "   Susbcription state is available" );
				_LIT ( KDef, "   Susbcription state is ERROR" );

				const  MXIMPDataSubscriptionState&  dstate = blockListEvent->DataSubscriptionState();

				switch ( dstate.SubscriptionState() )
					{

					case 0:
						ssstate.Copy ( Kna );
						break;

					case 1:
						ssstate.Copy ( Kava );
						break;

					default:
						ssstate.Copy ( KDef );
						break;
					}

				_LIT ( Kdna, "   Data state is unavailable" );

				_LIT ( Kdava, "   Data state is available" );
				_LIT ( KdDef, "   Data state is ERROR" );


				switch ( dstate.SubscriptionState() )
					{

					case 0:
						sdstate.Copy ( Kdna );
						break;

					case 1:
						sdstate.Copy ( Kdava );
						break;

					default:
						sdstate.Copy ( KdDef );
						break;
					}

				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "*************BEGIN******************" ) );

				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "Recvd Presentity Grant event" ) );
				RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, sdstate );
				RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, ssstate );

				TInt index = blockListEvent->NewBlocksCount();

				for ( TInt i = 0; i < index; i++ )
					{
					const MPresenceBlockInfo& blockinfo = blockListEvent->NewBlock ( i );

					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, blockinfo.BlockedEntityId().Identity() );
					const TDesC16& dispname = blockinfo.BlockedEntityDisplayName();
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, dispname );
					}

				index = blockListEvent->CurrentBlocksCount();

				for ( TInt i = 0; i < index; i++ )
					{
					const MPresenceBlockInfo& blockinfo = blockListEvent->CurrentBlock ( i );

					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, blockinfo.BlockedEntityId().Identity() );
					const TDesC16& dispname = blockinfo.BlockedEntityDisplayName();
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, dispname );
					}

				break;
				}

		case MPresentityPresenceEvent::KInterfaceId:
				{
				const MPresentityPresenceEvent* PresentityPresenceEvent =
				    TXIMPGetInterface< const MPresentityPresenceEvent >::From ( aEvent,
				            MXIMPBase::EPanicIfUnknown );
				TBuf<100> sdstate;
				TBuf<100> ssstate;
				_LIT ( Kna, "   Susbcription state is unavailable" );
				_LIT ( Kava, "   Susbcription state is available" );
				_LIT ( KDef, "   Susbcription state is ERROR" );

				const  MXIMPDataSubscriptionState&  dstate = PresentityPresenceEvent->DataSubscriptionState();

				switch ( dstate.SubscriptionState() )
					{

					case 0:
						ssstate.Copy ( Kna );
						break;

					case 1:
						ssstate.Copy ( Kava );
						break;

					default:
						ssstate.Copy ( KDef );
						break;
					}

				_LIT ( Kdna, "   Data state is unavailable" );

				_LIT ( Kdava, "   Data state is available" );
				_LIT ( KdDef, "   Data state is ERROR" );


				switch ( dstate.SubscriptionState() )
					{

					case 0:
						sdstate.Copy ( Kdna );
						break;

					case 1:
						sdstate.Copy ( Kdava );
						break;

					default:
						sdstate.Copy ( KdDef );
						break;
					}

				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "*************BEGIN******************" ) );

				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "Recvd Presentity PresenceEvent" ) );
				RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, sdstate );
				RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, ssstate );

				RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, PresentityPresenceEvent->PresentityId().Identity() );

				const MPresenceInfo& pi = PresentityPresenceEvent->SubscribedPresence();
				const MPersonPresenceInfo* ppi =  pi.PersonPresence();
				const MPresenceInfoFieldCollection& presinf = ppi->Fields();
				TInt index = presinf.FieldCount();
				// const MXIMPBase base;

				for ( TInt i = 0; i < index; i++ )
					{
					const MPresenceInfoField& infofield = presinf.FieldAt ( i );
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, infofield.FieldType() );
					const MPresenceInfoFieldValueText* PresentityPresencestatus =
					    TXIMPGetInterface< const MPresenceInfoFieldValueText >::From ( infofield.FieldValue(),
					            MXIMPBase::EPanicIfUnknown );
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, PresentityPresencestatus->TextValue() );
					//          EUNIT_ASSERT_EQUALS_DESC(PresentityPresencestatus->TextValue(), iPersonpresattributes[i], "statustext does'nt match");
					}

				index = pi.ServicePresenceCount();

				for ( TInt i = 0; i < index; i++ )
					{
					const MServicePresenceInfo& servicePresinfo = pi.ServicePresenceAt ( i );
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, servicePresinfo.ServiceType() );
//            EUNIT_ASSERT_EQUALS_DESC(servicePresinfo.ServiceType(), servctype, "service does'nt match");
					const MPresenceInfoFieldCollection& fields = servicePresinfo.Fields();

					for ( TInt j = 0; j < fields.FieldCount(); j++ )
						{
						const MPresenceInfoField& infofield = fields.FieldAt ( j );
						RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, infofield.FieldType() );
						const MPresenceInfoFieldValueText* Presenceavailability =
						    TXIMPGetInterface< const MPresenceInfoFieldValueText >::From ( infofield.FieldValue(),
						            MXIMPBase::EPanicIfUnknown );

//               EUNIT_ASSERT_EQUALS_DESC(Presenceavailability->TextValue(), _L("OPEN") , "Comm capability  does'nt match");
						RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, Presenceavailability->TextValue() );
						}
					}

				index = pi.DevicePresenceCount();

				for ( TInt i = 0; i < index; i++ )
					{
					const MDevicePresenceInfo& DevicePresinfo = pi.DevicePresenceAt ( i );
					const TPtrC8 devicename = DevicePresinfo.DeviceName();
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, DevicePresinfo.DeviceName() );
					const MPresenceInfoFieldCollection& fields = DevicePresinfo.Fields();
					TInt fieldcount = fields.FieldCount();

					for ( TInt j = 0; j < fieldcount; j++ )
						{
						const MPresenceInfoField& infofield = fields.FieldAt ( j );
						const TDesC8* fieldtype = & ( infofield.FieldType() );
						RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, *fieldtype );
						const MXIMPBase& base = infofield.FieldValue();
						const MPresenceInfoFieldValueText* Presentityvalue =
						    TXIMPGetInterface< const MPresenceInfoFieldValueText >::From ( infofield.FieldValue(),
						            MXIMPBase::EPanicIfUnknown );

						RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, Presentityvalue->TextValue() );
//               EUNIT_ASSERT_EQUALS_DESC(Presentityvalue->TextValue(), clienttype, "Clienttype does'nt match");
						}


					}

				_LIT ( KMsg, " presentity presence event  is getting " );         // here we hv to write message or text wch we want to write in log file

				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, KMsg );
				break;
				}

		case MPresenceWatcherListEvent::KInterfaceId:
				{
				const MPresenceWatcherListEvent* watcherListEvent =
				    TXIMPGetInterface< const MPresenceWatcherListEvent >::From ( aEvent,
				            MXIMPBase::EPanicIfUnknown );
				TBuf<100> sdstate;
				TBuf<100> ssstate;
			
				const  MXIMPDataSubscriptionState&  dstate = watcherListEvent->DataSubscriptionState();

				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "Recvd watcher event" ) );
				// print the list contents

				for ( TInt i = 0; i < watcherListEvent->CurrentWatchersCount(); i++ )
					{
					const MPresenceWatcherInfo& gi = watcherListEvent->CurrentWatcher ( i );

					gid[i].Copy ( gi.WatcherId().Identity() );
					RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "Id and displayname for cur watcher group %d X" ), i );
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, gi.WatcherId().Identity() );
//             EUNIT_ASSERT_EQUALS_DESC(gi.WatcherId().Identity(), KContact1, "watcher does'nt match");
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, gi.WatcherDisplayName() );
					//  EUNIT_ASSERT_EQUALS_DESC(gi.WatcherDisplayName(), KNickname1, "Devicename does'nt match");
					}

				gidcount = watcherListEvent->CurrentWatchersCount();

				// print the list contents

				for ( TInt i = 0; i < watcherListEvent->NewWatchersCount(); i++ )
					{
					const MPresenceWatcherInfo& gi = watcherListEvent->NewWatcher ( i );
					gid[i].Copy ( gi.WatcherId().Identity() );
					RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "Id and displayname for new group %d X" ), i );
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, gi.WatcherId().Identity() );
//             EUNIT_ASSERT_EQUALS_DESC(gi.WatcherId().Identity(), KContact1, "watcher does'nt match");
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, gi.WatcherDisplayName() );
					// EUNIT_ASSERT_EQUALS_DESC(gi.WatcherDisplayName(), KNickname1, "Devicename does'nt match");
					}

				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "*************END*******************" ) );

				gidcount = watcherListEvent->NewWatchersCount();

				break;
				}

		case MImConversationEvent::KInterfaceId:
				{
				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "Recvd conversation event" ) );

				const MImConversationEvent* convEvent =
				    TXIMPGetInterface< const MImConversationEvent >::From
				    ( aEvent, MXIMPBase::EPanicIfUnknown );
				TInt count = convEvent->NewTextMessageCount();
				const MImConversationInfo& convInfo = convEvent->NewTextMessage ( 0 );
				const MXIMPIdentity& identity = convInfo.MessageId();
				const TDesC16& msg = convInfo.TextMessage();
				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "message is" ) );
				RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, convInfo.TextMessage() );
				RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, convInfo.MessageId().Identity() );

				/*  const MDesCArray& array= convInfo.RecipientL();
				  TPtrC sender=array.MdcaPoint(0);*/
				break;
				}
		case MSearchEvent::KInterfaceId:
				{
				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "search event"));
				const MSearchEvent* srchEvent = 
				TXIMPGetInterface< const MSearchEvent >::From
										(aEvent, MXIMPBase::EPanicIfUnknown);	
				TInt count=	srchEvent->SearchResultCount();
				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend,_L("result count  :%d "),count);
				RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, srchEvent->SearchId().Identity() );
				
				TInt64 radn;
				TInt random = Math::Rand( radn );
				
				for(TInt i=0;i<count;++i)
					{
					const MSearchInfo& info=srchEvent->SearchResult(i);
					RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend,_L("Result No:%d "),i);
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, info.GetFieldInfo(EFirstName) );
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, info.GetFieldInfo(ELastName) );
					RFileLogger::Write ( KDir, KFile, EFileLoggingModeAppend, info.GetFieldInfo(EEmailAddress) );
					//take a random contact
					if ( i == random % count ) 
						{
						
						RFs fs;
						RFile file;
						TBuf8<100> buf;
						User::LeaveIfError( fs.Connect() );
						User::LeaveIfError( file.Replace( fs, 
									KAddContactFileName, EFileWrite ) );
									
						CnvUtfConverter::ConvertFromUnicodeToUtf8( buf, 
											info.GetFieldInfo(EEmailAddress) ); 
						file.Write( buf );
						file.Close();
						fs.Close();
							
						}
					}
				RFileLogger::WriteFormat ( KDir, KFile, EFileLoggingModeAppend, _L ( "search event processed"));	
				break;	
				}
				
		case MSearchKeysEvent::KInterfaceId:
            {
            const MSearchKeysEvent* srchEvent = 
                        TXIMPGetInterface< const MSearchKeysEvent >::From
                                                (aEvent, MXIMPBase::EPanicIfUnknown);
            TInt count= srchEvent->InfoCount();
            
            for(TInt a=0; a < count; a++)
                {
                const MSearchKeyInfo& keyInfo=srchEvent->SearchKeyInfo( a);
                switch(keyInfo.Type())
                    {
                    case EKey:
                        {
                        TInt key= keyInfo.Key();
                        }
                        break;
                       
                    case ELabel:
                        {
                        TPtrC label = keyInfo.Label();
                        break;
                        }
                	}
                 }
            
            break;
            }
		
		default:
				{
				break;
				}
		}
	}


// end of file






