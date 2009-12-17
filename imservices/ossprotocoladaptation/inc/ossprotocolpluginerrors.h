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
* Description:  OSs adapter plugin errors
*
*/

#ifndef __OSSPROTOCOLPLUGINERRORS_H__
#define __OSSPROTOCOLPLUGINERRORS_H__

//  INCLUDES
#include    <e32std.h>
/**
* Mapping xmpp protocl errors with ximpfw 
*
*/
/**
 * Xmpp protocol error codes.
 *
 * Xmpp status codes received from network transactions
 * are translated into Xmpp error code range
 * with following mapping:
 * <Xmpp-error-code> = KOssAdapBaseErrorXmppServerResponseBase - <Xmpp-status-code>
 * NOTE!! Mapping algorithm above and error symbols defined
 * below are in sync with algorithm used by the Xmpp protocol.
 */
enum	
    {
    KOssAdapBaseErrorXmppServerResponseBase = -10000,
    KOssAdapBaseErrorXmppServerLoginResponseBase = -11000,
	KOssAdapBaseErrorXmppServerContactResponseBase = -12000,
	KOssAdapBaseErrorXmppServerContactListResponseBase = -13000,
	KOssAdapBaseErrorXmppServerPresenceResponseBase = -14000,
	KOssAdapBaseErrorXmppServerSendMessageResponseBase = -15000,
	KOssAdapBaseErrorXmppServerReceiveMessageResponseBase = -16000,
	KOssAdapBaseErrorXmppServerLogoutResponseBase = -17000,
	KOssAdapBaseErrorMessageQueueResponseBase = -18000,

    KOssAdapErrMsgQueueCreate = KOssAdapBaseErrorMessageQueueResponseBase - 100,
    KOssAdapErrMsgQueueSend = KOssAdapBaseErrorMessageQueueResponseBase - 101,
    
   
    KOssadapErrInvalidSettingsId = KOssAdapBaseErrorXmppServerLoginResponseBase - 800,
    };

#endif  //__OSSPROTOCOLPLUGINERRORS_H__
