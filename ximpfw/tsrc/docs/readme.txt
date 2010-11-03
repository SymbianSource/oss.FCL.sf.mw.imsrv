Conventions for writing test cases and using decorators for them.

-----------------------------------------------------------------------

******************************************
*     WHICH DECORATOR I SHOULD USE       *
******************************************
#1 Do no use static test decorators. Decorators are used dynamically.
  - 1. Ok to use decorator -> Use PRFW_DECORATED_TEST
  - 2. nok to use decorator -> Use PRFW_NOT_DECORATED_TEST


-----------------------------------------------------------------------
****************************************
* HOW TO USE THE TEST CONTEXT WRAPPERS *
****************************************

Relevant files:
testcaseutils/prfwtestcontextwrapper.h
testcaseutils/prfwtestcontextwrappermgr.h
testcaseutils/prfwtestcontextwrapper.cpp
testcaseutils/prfwtestcontextwrappermgr.cpp
   
    >>> Feel free to remove unused stuff or add more! <<<

Main idea: simplify test code by wrapping each testing "context" in one
class which contains:
  - prfw client
  - prfw context (not the same as testing "context")
  - the plugin instance
  - event listener
  - messenger (see below)
  - etc.

For example usage see:
  t_sessionmng
  pr_prfwtestprotocol

Mini how-to:

1. Create wrappers with wrapper manager using CreateWrapperL call.

2. Then access the wrappers using GetWrapper( TInt aIndex ). The caller is
responsible for keeping note of which index is used for what (e.g. in
the case of two connections).

3. Wrapper has methods BindL and UnbindL if you just want to get the
   connection up:

   Somewhere, e.g. Setup method:

    iWrapperMgr = CPrFwTestContextWrapperMgr::NewL();
    iWrapperMgr->CreateWrapperL();
   
   Bind:

    CPrFwTestContextWrapper* wrapper0 = iWrapperMgr->GetWrapperL( 0 );
    wrapper0->BindL( 0 );

    // now you are "connected to network" (=faked by test plugin)

   Unbind:
    
    CPrFwTestContextWrapper* wrapper0 = iWrapperMgr->GetWrapperL( 0 );
    wrapper0->UnbindL();

    // now you are no longer connected. 

   Destructor:
     
    delete iWrapperMgr; 

4. You can access messenger class etc. using the various Get* methods.

    IMPORT_C MXIMPContext* GetContext();
    IMPORT_C CPrFwTestStatusEventListener* GetEventListener();
    IMPORT_C CPrFwTestMessenger* GetMessenger();
    IMPORT_C MXIMPClient* GetClient();
    IMPORT_C RArray<TPrFwTestStatusEventSnapshot>* GetStatusTraits();

5. Other convenience methods are also provided, please see t_sessionmng
   for illustrative code. The below method tests the bind with wait.
   The Assert* methods are used to check if test protocol plugin was
   correctly called.

Setup:

    iWrapperMgr = CPrFwTestContextWrapperMgr::NewL();
    iWrapperMgr->CreateWrapperL();

Teardown:

    delete iWrapperMgr;

void T_SessionMng::T_Simple_Bind_Wait_Unbind_L()
    {
    EUNIT_PRINT( _L("Simple context Bind/Unbind test.") );
    EUNIT_PRINT( _L("Client side waits bind completion before issuing unbind.") );

    CPrFwTestContextWrapper* wrapper = iWrapperMgr->GetWrapperL( 0 );
    MXIMPContext* context = wrapper->GetContext();
    CPrFwTestStatusEventListener* eventListener = wrapper->GetEventListener();
    CPrFwTestMessenger* messenger = wrapper->GetMessenger();
    
    //Do bind, wait and verify events
    wrapper->SetupListenerL( EPrFwTestStatusEvents_BindingOk );
    messenger->SetNoError(); 

    messenger->SetPluginIndex( 0 );
    TUid protocol = { 0x1100ff55 };
    TXIMPRequestId reqId = context->BindToL( 
            protocol,
            _L("www.imps.no/wv"),
            _L("user"),
            _L("password"),
            1 );

    wrapper->WaitRequestAndStackEvents( reqId );
    wrapper->VerifyEventStackL( _L8("Binding single context: ") );

    AssertOpenSession( 0 );

    //Verify features availability
    MXIMPFeatureInfo* ctxFeats = context->GetContextFeaturesLC();
    EUNIT_ASSERT_DESC( ctxFeats->FeatureIds().MdcaCount() > 0, "No features from context" );
    CleanupStack::PopAndDestroy(); //ctxFeats

    //Do unbind, wait and verify events
    wrapper->SetupListenerL( EPrFwTestStatusEvents_UnbindingOk );
    messenger->SetNoError();
    reqId = context->UnbindL();

    wrapper->WaitRequestAndStackEvents( reqId );
    wrapper->VerifyEventStackL( _L8("Unbinding single context: ") );

    AssertCloseSession( 0 );
    AssertPluginDied( 0 );
    }

The Assert* methods can be found from t_sessionmng (they should be moved
elsewhere). See below for messenger functionality.

-----------------------------------------------------------------------
***************************************************
* HOW TO USE THE TEST CASE - PLUGIN COMMUNICATION *
***************************************************

Relevant files:
testcaseutils/prfwtestmessaging.h    - Keys, value enumerations etc.
testcaseutils/prfwtestmessenger.h    - Messenger header (READ THIS)
testcaseutils/prfwtestmessenger.cpp  - Messenger implementation
 
    >>> Feel free to remove unused stuff or add more! <<<

For example usage see:
  t_sessionmng
  t_presencemng
  pr_prfwtestprotocol

The idea is:
  - there's publish & subscribe facility to send messages from
    test code to plugin
  - test protocol reads the message and changes its behaviour
    accordingly, e.g. doing a leave on next HandleRequestCompleted

More details:

(prfwtestmessaging.h)

* TPrFwTestPropertyKeys determines the keys.
  You can add more messages here.

* TPrFwTestPropertyValues determines certain pre-defined values,
  e.g. EPrFwPrtValSessionLostReconnect (which is used to cause the
  plugin to signal a "session lost, try to reconnect" to the 
  Presence Framework.

* TPrFwTestMsg is the protocol message. It consists of the key specifier
  and the value to be set. Currently only integer parameters are
  supported.

* Each CPrFwTestMessenger takes an index into the constructor. This is
  needed to create a two-way communications channel from the test case
  to plugin and vice versa.

* Creation of messenger is handled by the wrapper (which is created via
  wrapper manager).

* MINIMAL USAGE:
 
  * To set "happy path", no errors will be artificially caused:
    SetNoError()

  * To make next operation fail with some error code: 
    SetError( TInt aErrorCOde )

  * To make next operation leave:
    SetLeave( TInt aLeaveCode )

  * Call HandleLeaveL in the test protocol plugin to automatically
    leave, if leave was requested. (So you don't have to do 
    "GetValueFor.. if (leave){User::Leave..")

  * To set a boolean-valued (1 or 0) key, use SetBoolean. Read with
    GetBoolean. These are used to signal the calling of some method,
    and to read whether the method was called or not.

  * For generic stuff use SetValueFor and GetValueFor.

NOTES:

If you add more keys, BE SURE TO RESET THEM IN THE MESSENGER
CONSTRUCTION. 

If you use multiple messengers, use different indexes!!!

Please see t_sessionmng and t_presencemng for details.

-----------------------------------------------------------------------
********************************************
* HOW TO USE THE EVENT LISTENER CLASS      *
********************************************

There are 2 event listener classes implemented:
CPrFwTestListener
CPrFwTestStatusEventListener

The context wrapper has support for the CPrFwTestStatusEventListener.
See the description there.

CPrFwTestListener is the one which is more commonly used in the test cases.
This listener supports creating exact events to be accepted by the test case,
including the data inside the events, so use this class to verify the data.
The event with the expected data can be send to the test protocol using
the filetool, see below.

The usage of the listener is fairly simple:

    // create the listener since not created by the wrapper
    CPrFwTestListener* listener2 = CPrFwTestListener::NewL( context );
    CleanupStack::PushL( listener2 );

    // initialize it to accept new events
    listener2->Reset();

    // create the event which is expected, here the RequestCompleteEvent
    // RequestID is not checked in the assertion! 
    TXIMPRequestId reqIdDummy;
    CXIMPRequestCompleteEventImp* evReqComplete =
                    CXIMPRequestCompleteEventImp::NewLC( reqIdDummy );
                    
    // add the created event to the listener, ownership is transfered
    listener2->ExpectL( evReqComplete );
    CleanupStack::Pop( evReqComplete );

    // call the desired XIMPFW method 
    TXIMPRequestId reqId = presPub->SubscribePresenceWatcherListL();

    // Wait for events on the request
    // Assertion is done based on the content on the event by comparing
    // the received event with the expected one.
    EUNIT_ASSERT_DESC( KErrNone == listener2->WaitAndAssertL(), "Subscribe failed" );
    
    // clean it up
    CleanupStack::PopAndDestroy( listener2 );

-----------------------------------------------------------------------
********************************************
* HOW TO USE THE PSEUDO-IPC FILETOOL CLASS *
********************************************

The FileTool writes given serialized objects to a directory. It can also
internalize them. Thus with FileTool you can check whether the presence
data you put into the framework goes through OK.

Server could also be used, and in a perfect world such a thing would
have been written with big smiles, but in reality it would take much
much longer to create and debug than this kind of FileTool, so here's
FileTool!

Relevant files:
testcaseutils/prfwtestfiletool.h
testcaseutils/prfwtestfiletool.cpp

As of now, the FileTool is not yet integrated to any tests.

FileTool API:

Let's say you choose to use index 0. If you have two connections or
such, then you would create two FileTools with indexes 0 and 1,
respectively.

Wipe old stuff away, destroy the directory, etc.:
  - CleanL( 0 )

Create the new directory:
  - PrepareL( 0 ) 

Store an object:
  - StoreL( 0, externalizedObjectAsTDesC8 )

Get number of objects stored:
  - numObjects = NumObjectsL( 0 )

Restore an object:
  - i is a looping from 0..NumObjectsL( 0 )-1.
  - CXIMPApiEventBase* restored = RestoreLC( 0, i );
  - For example in this way you can check the whole directory.

After the object is restored, compare in test code side to that which it
SHOULD HAVE been.

-----------------------------------------------------------------------
********************************************
* HOW TO USE THE "ROBUSTNESS HELPERS"      *
********************************************

It's good to kill the servers and removing all temporary FileTool files
when starting a test case. This ensures that there are no unexpected
messages, events or state lingering in the server.

1. Add to MMP file:

  #include "..\..\tsrcutils\processmaster\pm.h"

If your stuff is not in internal\tsrc, then view the pm.h contents and
adapt it.

2. Add to test case:

  #include "prfwtestrobustnesstools.h"

3. Add to test case SetupL as the first line:

  PrfwTestRobustness::DoPreCleaning();

