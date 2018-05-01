#include <iostream>
#include "CommManager.h"
#include "abstractcommandprocessor.h"
#include "GarfunkelCommandProcessor.h"
#include "DBAccess.h"
#include "GarfunkelIPC.h"
#include "IPCCommand.h"
#include "GarfunkelSystemData.h"
#include <sstream>
#include "abstractipcmessage.h"
#include "GarfunkelDB.h"
//#define DEBUG2


//% Note: Changes:
//%             We will use "Ba"  instead of the present "Oa" for AddressInstance,
//%                 i.e B = Address & a = Instance 
//%             As from Feb 02, 2016

//%%=====================================================================================================
//%                 Registered Messages start here!!!
//%=======================================================================================================

//%
//%
//% MCA is Master emitting Diagnostics Completing Signal to UI it Command is SU:51:X:2
//%
//%
SU51Message::SU51Message(GarfunkelIpc* ipc, GarfunkelCommThread* comm) : AbstractIPCMessage(ipc),_comm(comm)
{
}
SU51Message::~SU51Message()
{
}
bool SU51Message::processMessage(IPCCommand& command, std::string& response)
{
    bool retValue = false;
    if(command.IsSUCommand())
    {
        // parse enumeration string
        std::vector<std::string>    myVector = command.GetPayloadList();

        int    xvalue = 0;
        int    yvalue = 0;
        std::string xstring = myVector[0];
        std::stringstream xstrStream(xstring);
        xstrStream >> xvalue;

        std::string ystring = myVector[1];
        std::stringstream ystrStream(ystring);
        ystrStream >> yvalue;

        // emit signal
        emit toUiCommandSU51(xvalue, yvalue);

        // handshake to MCA
        std::string r("Ba:OK:"); //% will instead use "Ba" for AddressInstance, i.e B = Address & a = Instance as from Feb 02, 2016
        response = r;
        return true;
    }
    else if(command.IsDUCommand())
    {
        // THIS IS FOR A DU COMMAND TO FETCH DATA FROM THE UI
//        qDebug() << "SU51Message::processMessage  DUCommand() UNIMPLEMENTED ";
    }
    else
    {
//        qDebug() << "SU51Message::processMessage unknown Command() detected ";
    }
    // CP will send an ERR response for us
    return retValue;
}



//%
//%
//% MCA is Master emitting Diagnostics Completing Signal to UI it Command is SU:65:A:B
//% A: Total Time
//% B: Delay Timer
//%

SU65Message::SU65Message(GarfunkelIpc* ipc, GarfunkelCommThread* comm) : AbstractIPCMessage(ipc),_comm(comm)
{
}
SU65Message::~SU65Message()
{
}
bool SU65Message::processMessage(IPCCommand& command, std::string& response)
{
    bool retValue = false;
    if(command.IsSUCommand())
    {
        // parse enumeration string
        std::vector<std::string>    myVector = command.GetPayloadList();

        int    xvalue = 60;
        int    yvalue = 20;
        std::string xstring = myVector[0];
        std::string ystring = myVector[1];
        std::stringstream xstrStream(xstring);
        xstrStream >> xvalue;
        std::stringstream ystrStream(ystring);
        ystrStream >> yvalue;

        // emit signal
//        qDebug() << "SU65Message::processMessage sending " << xvalue << "  " << yvalue;
        emit toUiCommandSU65( xvalue,yvalue );

        // handshake to MCA
        std::string r("Ba:OK:");
        response = r;
        return true;
    }
    else if(command.IsDUCommand())
    {
        // THIS IS FOR A DU COMMAND TO FETCH DATA FROM THE UI
//        qDebug() << "SU65Message::processMessage  DUCommand() UNIMPLEMENTED ";
    }
    else
    {
//        qDebug() << "SU65Message::processMessage unknown Command() detected ";
    }
    // CP will send an ERR response for us
    return retValue;
}



//%=================================================================================================
//%
//%   MCA sens emits toUiCommandSU52 Signal to UI  with SU52Message 
//%   
//%   Diagnostic Infos/Data to UI MCA to UI Command SU:52:A:B:C:D:E
//%   A: = Total Time
//%   B: = Timer (Range: TBD)
//%   C: = Pressure Switch Status (bool or int?)
//%   D: = Temperature in C
//%   E: = Conductivity in uS/cm
//%
//%=================================================================================================

SU52Message::SU52Message(GarfunkelIpc* ipc, GarfunkelCommThread* comm) : AbstractIPCMessage(ipc),_comm(comm)
{
}
SU52Message::~SU52Message()
{
}
bool SU52Message::processMessage(IPCCommand& command, std::string& response)
{
    bool retValue = false;
    if(command.IsSUCommand())
    {
        // parse enumeration string
        std::vector<std::string>    myVector = command.GetPayloadList();

        int    ttvalue = -1;  //% A
        int    tvalue = -1;   //% B
        int    wpsstatus = -1; //% C
        float  tempvalue = 99999999; //% D
        float  cvalue = 99999999;  //% E

        std::string ttstring = myVector[0];
        std::stringstream ttstrStream(ttstring);
        ttstrStream >> ttvalue;

        std::string tstring = myVector[1];
        std::stringstream tstrStream(tstring);
        tstrStream >> tvalue;

        std::string wpsstatusstring = myVector[2];
        std::stringstream wpsstatusStrStream(wpsstatusstring);
        wpsstatusStrStream >> wpsstatus;

        std::string tempvaluestring = myVector[3];
        std::stringstream tempvalueStrStream(tempvaluestring);
        tempvalueStrStream >> tempvalue;

        std::string cstring = myVector[4];
        std::stringstream cstrStream(cstring);
        cstrStream >> cvalue;

        // emit signal
        emit toUiCommandSU52( ttvalue, tvalue, wpsstatus, tempvalue,  cvalue );

        // handshake to MCA
        std::string r("Ba:OK:");
        response = r;
        return true;
    }
    else if(command.IsDUCommand())
    {
        // THIS IS FOR A DU COMMAND TO FETCH DATA FROM THE UI
        // qDebug() << "SU52Message::processMessage  DUCommand() UNIMPLEMENTED ";
    }
    else
    {
        // qDebug() << "SU52Message::processMessage unknown Command() detected ";
    }
    // CP will send an ERR response for us
    return retValue;
}



//%===================================================================================================================================
//%
//% MCA emits Internal error/Diagnostic Operation Failed  Signal to UI during given saying Operation failed to UI it Command is SU:53:
//% Document shows no X?
//%
//%=====================================================================================================================================
SU53Message::SU53Message(GarfunkelIpc* ipc, GarfunkelCommThread* comm) : AbstractIPCMessage(ipc),_comm(comm)
{
}
SU53Message::~SU53Message()
{
}
bool SU53Message::processMessage(IPCCommand& command, std::string& response)
{
    bool retValue = false;
    if(command.IsSUCommand())
    {
        // parse enumeration string
        std::vector<std::string>    myVector = command.GetPayloadList();
    
        if(myVector.size() == 0)
        {
        // emit internal Error/Operation failed signal
        emit toUiCommandSU53();
        }
        // handshake to MCA
        std::string r("Ba:OK:");
        response = r;
        return true;
    }
    else if(command.IsDUCommand())
    {
        // THIS IS FOR A DU COMMAND TO FETCH DATA FROM THE UI
        qDebug() << "SU53Message::processMessage  DUCommand() UNIMPLEMENTED ";
    }
    else
    {
        qDebug() << "SU53Message::processMessage unknown Command() detected ";
    }
    // CP will send an ERR response for us
    return retValue;
}



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//%static  variables so multiple class instances can share them
//
bool GarfunkelCommandProcessor::_connected = true;
QMutex GarfunkelCommandProcessor::connectionMutex;



//%=================================================================================================
//%
//%   GarfunkelCommandProcessor CONSTRUCTOR
//%                
//%=================================================================================================
GarfunkelCommandProcessor::GarfunkelCommandProcessor(GarfunkelIpc* ipc, CommManager::MCACommType commtype, GarfunkelCommThread* parent) 
    : _parent(parent), _ipc(ipc), _commtype(commtype)
{
    _ACK.push_back((char)0x6);
    _NACK.push_back((char)0x15);

    // The GarfunkelIpc class needs to do callbacks to this class but was created before us so we
    // need to set a pointer to us before trying to process commands.
    _ipc->setCommandProcessor(this);
    _setLoopCount(500);
    _setSleepFactor(50000);
    _connected = true;

    initializeCommandProcessor("", ""); // sets instance address from Database
}

//%=================================================================================================
//%
//%    \brief      GarfunkelCommandProcessor DESTRUCTOR
//%
//%=================================================================================================
GarfunkelCommandProcessor::~GarfunkelCommandProcessor()
{
}
        
//=================================================================================================
//!
//!    \brief      isMaster 
//!     Used mostly internally to determine connections. Server mode means the MCA is the master and 
//!     the UI is the slave. Client mode means the MCA is the slave and the UI is the master. So
//!     client mode is used to initiate commands to the MCA. Server mode is used to receive commands and
//!     alarms and notifications from the MCA.
//!                
//!    \param[in]  None
//!                
//!    \param[out] None
//!                
//!    \return     True if acting as a server to MCA commands. False is acting as a client.
//!                
//!    \throw      None
//=================================================================================================
bool GarfunkelCommandProcessor::isMaster()
{ 
    if(CommManager::MCA_MASTER == _commtype)
    {
        return( true );
    }
    else
    {
        return( false );
    }
}
//=================================================================================================
//!
//!    \brief    initializeCommandProcessor()
//!                
//!    \param[in]  None
//!                
//!    \param[out] None
//!                
//!    \return     None
//!                
//!    \throw      None
//%
//=================================================================================================
int GarfunkelCommandProcessor::initializeCommandProcessor(const std::string &  database, const std::string & databaseItem)
{
  

    boost::shared_ptr< AbstractIPCMessage > su51Message(new SU51Message(_ipc, _parent) );
    SU51Message* su51msg = (SU51Message*)su51Message.get();

    boost::shared_ptr< AbstractIPCMessage > su65Message(new SU65Message(_ipc, _parent) );
    SU65Message* su65msg = (SU65Message*)su65Message.get();

    boost::shared_ptr< AbstractIPCMessage > su52Message(new SU52Message(_ipc, _parent) );
    SU52Message* su52msg = (SU52Message*)su52Message.get();

    boost::shared_ptr< AbstractIPCMessage > su53Message(new SU53Message(_ipc, _parent) );
    SU53Message* su53msg = (SU53Message*)su53Message.get();


      Q_UNUSED(database); // for now
      Q_UNUSED(databaseItem);

  
    QPointer<GarfunkelSystemData> systemdata  = GarfunkelSystemData::getInstancePtr();

    if(isMaster())
    {
        //
        //                     *** INCOMING SIGNALS FROM UI ***
        //
        //% GarfunkelSystemData Model sends us signals, then we send SU or DU  commands to MCA, return response signal to SystemData
        //
        connect(this,SIGNAL(setConnectionUp()), systemdata, SLOT(setConnectionUp()),Qt::QueuedConnection); 
        connect(this,SIGNAL(setConnectionDown()), systemdata, SLOT(setConnectionDown()),Qt::QueuedConnection); 
        connect(systemdata,SIGNAL(toMCACommandDU40()), this, SLOT(toMCACommandDU40()),Qt::QueuedConnection);
        connect(systemdata,SIGNAL(toMCACommandDU41()), this, SLOT(toMCACommandDU41()),Qt::QueuedConnection);
        connect(systemdata,SIGNAL(toMCACommandDU42()), this, SLOT(toMCACommandDU42()),Qt::QueuedConnection);
        connect(systemdata,SIGNAL(toMCACommandDU43()), this, SLOT(toMCACommandDU43()),Qt::QueuedConnection);
        connect(systemdata,SIGNAL(toMCACommandDU44()), this, SLOT(toMCACommandDU44()),Qt::QueuedConnection);
        connect(systemdata,SIGNAL(toMCACommandDU45()), this, SLOT(toMCACommandDU45()),Qt::QueuedConnection);
        connect(systemdata,SIGNAL(toMCACommandDU47()), this, SLOT(toMCACommandDU47()),Qt::QueuedConnection);
        connect(systemdata,SIGNAL(toMCACommandDU84()), this, SLOT(toMCACommandDU84()),Qt::QueuedConnection);
        connect(systemdata,SIGNAL(toMCACommandDU85()), this, SLOT(toMCACommandDU85()),Qt::QueuedConnection);
        connect(systemdata,SIGNAL(toMCACommandDU86()), this, SLOT(toMCACommandDU86()),Qt::QueuedConnection);

        connect(systemdata,SIGNAL(toMCACommandSU50(int)), this, SLOT(toMCACommandSU50(int)),Qt::QueuedConnection);
        connect(systemdata,SIGNAL(toMCACommandSU51(int, int)), this, SLOT(toMCACommandSU51(int, int)),Qt::QueuedConnection);


#ifdef ABORT
        connect(systemdata,SIGNAL(abortIPC()), this, SLOT(abortIPC()),Qt::QueuedConnection);
#endif

        //                     *** OUTGOING RESPONSE SIGNALS TO UI ***
        //
        //
        // Synchronous REPLY's  in the MASTER thread. This will BYPASS the command processor.  
        // CP is only used in the SLAVE SERVER thread for incoming from MCA->UI messages 
        // when we dont yet know what the message type is.
        //
	connect(this,SIGNAL(fromMcaDU40Reply(bool,int)), systemdata, SLOT(fromMcaDU40Reply(bool,int)),Qt::QueuedConnection);
    connect(this,SIGNAL(fromMcaDU41Reply(bool,int)), systemdata, SLOT(fromMcaDU41Reply(bool,int)),Qt::QueuedConnection);
    connect(this,SIGNAL(fromMcaDU42Reply(bool,int)), systemdata, SLOT(fromMcaDU42Reply(bool,int)),Qt::QueuedConnection);
    connect(this,SIGNAL(fromMcaDU43Reply(bool,int)), systemdata, SLOT(fromMcaDU43Reply(bool,int)),Qt::QueuedConnection);
    connect(this,SIGNAL(fromMcaDU44Reply(bool,int)), systemdata, SLOT(fromMcaDU44Reply(bool,int)),Qt::QueuedConnection);
    connect(this,SIGNAL(fromMcaDU45Reply(bool,int)), systemdata, SLOT(fromMcaDU45Reply(bool,int)),Qt::QueuedConnection);
    connect(this,SIGNAL(fromMcaDU47Reply(bool,int)), systemdata, SLOT(fromMcaDU47Reply(bool,int)),Qt::QueuedConnection);
    connect(this,SIGNAL(fromMcaDU84Reply(bool,QString)), systemdata, SLOT(fromMcaDU84Reply(bool,QString)),Qt::QueuedConnection);
    connect(this,SIGNAL(fromMcaDU85Reply(bool,QString)), systemdata, SLOT(fromMcaDU85Reply(bool,QString)),Qt::QueuedConnection);
    connect(this,SIGNAL(fromMcaDU86Reply(bool,QString)), systemdata, SLOT(fromMcaDU86Reply(bool,QString)),Qt::QueuedConnection);

    connect(this,SIGNAL(fromMcaSU50ReplyOK(int)), systemdata, SLOT(fromMcaSU50ReplyOK(int)),Qt::QueuedConnection);
    connect(this,SIGNAL(fromMcaSU51ReplyOK(int)), systemdata, SLOT(fromMcaSU51ReplyOK(int)),Qt::QueuedConnection);
    connect(this,SIGNAL(fromMcaSU50Error(int)), systemdata, SLOT(fromMcaSU50Error(int)),Qt::QueuedConnection);
    connect(this,SIGNAL(fromMcaSU51Error(int)), systemdata, SLOT(fromMcaSU51Error(int)),Qt::QueuedConnection);
  

    }
    else   //% It is not Master
    {
        //%
        //%                     *** OUTGOING ORIGINATING SIGNALS TO UI ***
        //%
        //% MCA sends us SU or DU  commands, we signal model, respond to MCA
        connect(this,SIGNAL(setConnectionUp()), systemdata, SLOT(setConnectionUp()),Qt::QueuedConnection); 
        connect(this,SIGNAL(setConnectionDown()), systemdata, SLOT(setConnectionDown()),Qt::QueuedConnection);
        
        //% pass SU51 message to UI directly
        connect(su51msg,SIGNAL(toUiCommandSU51(int,int)), systemdata, SLOT(toUiCommandSU51(int,int)),Qt::QueuedConnection); 
        connect(su65msg,SIGNAL(toUiCommandSU65(int,int)), systemdata, SLOT(toUiCommandSU65(int,int)),Qt::QueuedConnection);
        connect(su52msg,SIGNAL(toUiCommandSU52(int,int,int,float, float)), systemdata, SLOT(toUiCommandSU52(int,int,int, float, float)),Qt::QueuedConnection);
        connect(su53msg,SIGNAL(toUiCommandSU53()), systemdata, SLOT(toUiCommandSU53()),Qt::QueuedConnection); 

    }   

    //%
    //% Register commands used to support System Data
    //%

    addCommand(std::string("SU:51"), su51Message);
    addCommand(std::string("SU:65"), su65Message);
    addCommand(std::string("SU:52"), su52Message);
    addCommand(std::string("SU:53"), su53Message);

    //initializeMasterKeepAlive();
    return(0);
}
#ifdef ABORT
//%=================================================================================================
//
//  abortIPC
//
//  This executes on the MASTER thread.  It exits the master threads event loop, and it tells
//  the SLAVE  thread  to abort.
//
//=================================================================================================
void GarfunkelCommandProcessor::abortIPC()
{
    _comm->setAbort(true); // slave thread will die when it sees this
    // Kill master thread 
    _comm->exit(1); // Tells the thread's event loop to exit with a return code.
}
#endif


//%
//%  SLOT toMCACommandDU40 ()
//%  Checks Current Status of the MCA/ Connection
//%*****************************************************************
void GarfunkelCommandProcessor::toMCACommandDU40()
{
    // tune loops so timeout is short
    int loops = _loopcount;
    _setLoopCount(20);

    int status = -1;
    std::string messagebuffer = "Ba:DU:40:"; // starts out as a address+payload, gets converted to an ESP string
    createESPString(messagebuffer);
    _ipc->sendStringMessage(messagebuffer);
    // NOW BLOCK WAITING FOR ACK/NAK AND RESPONSE
    std::string response("");
     //  qDebug() << "GarfunkelCommandProcessor::toMCACommandDU40 WAITING FOR RESPONSE";
    bool ackvalue = _rcvAll(response);
    if(ackvalue)
    {
        qDebug() << "fromMcaDU40Reply DU 40 OK";
        emit(fromMcaDU40Reply(true,status));
    }
    else
    {
        qDebug() << "fromMcaDU40Reply timeout";
        emit(fromMcaDU40Reply(false,status));
    }

   // qDebug() << "GarfunkelCommandProcessor::toMCACommandDU40 GOT RESPONSE" << response.c_str();
    int errno;
    bool valid_response = _parseResponse(response,errno);
    if(valid_response)
    {
        if(_getXresponse(status,response))
        {
            qDebug() << "fromMcaDU40Reply DU 40 OK, STATUS =" << status;
            if(status!=-1)
            	emit(fromMcaDU40Reply(true,status));
            else
            	emit(fromMcaDU40Reply(false,status));
        }
    }
    else
    {
        // We set false to indicate we failed
        // status is still -1 at this point
//        qDebug() << "fromMcaDU40Reply timeout";
        emit(fromMcaDU40Reply(false,status));
    }
    // restore loop count
    _setLoopCount(loops);
}



//%
//%  SLOT toMCACommandDU41 ()
//%  Requests Operating Schedule States
//%*****************************************************************
void GarfunkelCommandProcessor::toMCACommandDU41()
{
    //% tune loops so timeout is short
    int loops = _loopcount;
    _setLoopCount(20);

    int status = -1;
    std::string messagebuffer = "Ba:DU:41:"; 
    createESPString(messagebuffer);
    _ipc->sendStringMessage(messagebuffer);
    // NOW BLOCK WAITING FOR ACK/NAK AND RESPONSE
    std::string response("");
     //  qDebug() << "GarfunkelCommandProcessor::toMCACommandDU41 WAITING FOR RESPONSE";
    bool ackvalue = _rcvAll(response);
    if(ackvalue)
    {
        qDebug() << "fromMcaDU41Reply DU 41 OK";
        emit(fromMcaDU41Reply(true,status));
    }
    else
    {
        qDebug() << "fromMcaDU41Reply timeout";
        emit(fromMcaDU41Reply(false,status));
    }

   // qDebug() << "GarfunkelCommandProcessor::toMCACommandDU41 GOT RESPONSE" << response.c_str();
    int errno;
    bool valid_response = _parseResponse(response,errno);
    if(valid_response)
    {
        if(_getXresponse(status,response))
        {
            qDebug() << "fromMcaDU41Reply DU 41 OK, STATUS =" << status;
            if(status!=-1)
                emit(fromMcaDU41Reply(true,status));
            else
                emit(fromMcaDU41Reply(false,status));
        }
    }
    else
    {
        // We set false to indicate we failed
        // status is still -1 at this point
        // qDebug() << "fromMcaDU41Reply timeout";
         emit(fromMcaDU41Reply(false,status));
    }
    // restore loop count
    _setLoopCount(loops);
}



//%
//%  SLOT toMCACommandDU42 ()
//%  Requests Makedown Process Active
//%*****************************************************************
void GarfunkelCommandProcessor::toMCACommandDU42()
{
    //% tune loops so timeout is short
    int loops = _loopcount;
    _setLoopCount(20);

    int status = -1;
    std::string messagebuffer = "Ba:DU:42:"; 
    createESPString(messagebuffer);
    _ipc->sendStringMessage(messagebuffer);
    // NOW BLOCK WAITING FOR ACK/NAK AND RESPONSE
    std::string response("");
     //  qDebug() << "GarfunkelCommandProcessor::toMCACommandDU42 WAITING FOR RESPONSE";
    bool ackvalue = _rcvAll(response);
    if(ackvalue)
    {
        qDebug() << "fromMcaDU42Reply DU 42 OK";
        emit(fromMcaDU42Reply(true,status));
    }
    else
    {
        qDebug() << "fromMcaDU42Reply timeout";
        emit(fromMcaDU42Reply(false,status));
    }

   // qDebug() << "GarfunkelCommandProcessor::toMCACommandDU42 GOT RESPONSE" << response.c_str();
    int errno;
    bool valid_response = _parseResponse(response,errno);
    if(valid_response)
    {
        if(_getXresponse(status,response))
        {
            qDebug() << "fromMcaDU42Reply DU 42 OK, STATUS =" << status;
            if(status!=-1)
                emit(fromMcaDU42Reply(true,status));
            else
                emit(fromMcaDU42Reply(false,status));
        }
    }
    else
    {
        // We set false to indicate we failed
        // status is still -1 at this point
        // qDebug() << "fromMcaDU42Reply timeout";
         emit(fromMcaDU42Reply(false,status));
    }
    // restore loop count
    _setLoopCount(loops);
}


//%
//%  SLOT toMCACommandDU43 ()
//%  Requests Dispense Process Active
//%*****************************************************************
void GarfunkelCommandProcessor::toMCACommandDU43()
{
    //% tune loops so timeout is short
    int loops = _loopcount;
    _setLoopCount(20);

    int status = -1;
    std::string messagebuffer = "Ba:DU:43:"; 
    createESPString(messagebuffer);
    _ipc->sendStringMessage(messagebuffer);
    // NOW BLOCK WAITING FOR ACK/NAK AND RESPONSE
    std::string response("");
     //  qDebug() << "GarfunkelCommandProcessor::toMCACommandDU43 WAITING FOR RESPONSE";
    bool ackvalue = _rcvAll(response);
    if(ackvalue)
    {
        qDebug() << "fromMcaDU43Reply DU 43 OK";
        emit(fromMcaDU43Reply(true,status));
    }
    else
    {
        qDebug() << "fromMcaDU43Reply timeout";
        emit(fromMcaDU43Reply(false,status));
    }

   // qDebug() << "GarfunkelCommandProcessor::toMCACommandDU43 GOT RESPONSE" << response.c_str();
    int errno;
    bool valid_response = _parseResponse(response,errno);
    if(valid_response)
    {
        if(_getXresponse(status,response))
        {
            qDebug() << "fromMcaDU43Reply DU 43 OK, STATUS =" << status;
            if(status!=-1)
                emit(fromMcaDU43Reply(true,status));
            else
                emit(fromMcaDU43Reply(false,status));
        }
    }
    else
    {
        // We set false to indicate we failed
        // status is still -1 at this point
        // qDebug() << "fromMcaDU43Reply timeout";
         emit(fromMcaDU43Reply(false,status));
    }
    // restore loop count
    _setLoopCount(loops);
}


//%
//%  SLOT toMCACommandDU44 ()
//%  Requests Layup Mode Status
//%*****************************************************************
void GarfunkelCommandProcessor::toMCACommandDU44()
{
    //% tune loops so timeout is short
    int loops = _loopcount;
    _setLoopCount(20);

    int status = -1;
    std::string messagebuffer = "Ba:DU:44:"; 
    createESPString(messagebuffer);
    _ipc->sendStringMessage(messagebuffer);
    // NOW BLOCK WAITING FOR ACK/NAK AND RESPONSE
    std::string response("");
     //  qDebug() << "GarfunkelCommandProcessor::toMCACommandDU44 WAITING FOR RESPONSE";
    bool ackvalue = _rcvAll(response);
    if(ackvalue)
    {
        qDebug() << "fromMcaDU44Reply DU 44 OK";
        emit(fromMcaDU44Reply(true,status));
    }
    else
    {
        qDebug() << "fromMcaDU44Reply timeout";
        emit(fromMcaDU44Reply(false,status));
    }

   // qDebug() << "GarfunkelCommandProcessor::toMCACommandDU44 GOT RESPONSE" << response.c_str();
    int errno;
    bool valid_response = _parseResponse(response,errno);
    if(valid_response)
    {
        if(_getXresponse(status,response))
        {
            qDebug() << "fromMcaDU44Reply DU 44 OK, STATUS =" << status;
            if(status!=-1)
                emit(fromMcaDU44Reply(true,status));
            else
                emit(fromMcaDU44Reply(false,status));
        }
    }
    else
    {
        // We set false to indicate we failed
        // status is still -1 at this point
        // qDebug() << "fromMcaDU44Reply timeout";
         emit(fromMcaDU44Reply(false,status));
    }
    // restore loop count
    _setLoopCount(loops);
}



//%
//%  SLOT toMCACommandDU45 ()
//%  Requests Standby Mode Status
//%*****************************************************************
void GarfunkelCommandProcessor::toMCACommandDU45()
{
    //% tune loops so timeout is short
    int loops = _loopcount;
    _setLoopCount(20);

    int status = -1;
    std::string messagebuffer = "Ba:DU:45:"; 
    createESPString(messagebuffer);
    _ipc->sendStringMessage(messagebuffer);
    // NOW BLOCK WAITING FOR ACK/NAK AND RESPONSE
    std::string response("");
     //  qDebug() << "GarfunkelCommandProcessor::toMCACommandDU45 WAITING FOR RESPONSE";
    bool ackvalue = _rcvAll(response);
    if(ackvalue)
    {
        qDebug() << "fromMcaDU45Reply DU 45 OK";
        emit(fromMcaDU45Reply(true,status));
    }
    else
    {
        qDebug() << "fromMcaDU45Reply timeout";
        emit(fromMcaDU45Reply(false,status));
    }

   // qDebug() << "GarfunkelCommandProcessor::toMCACommandDU45 GOT RESPONSE" << response.c_str();
    int errno;
    bool valid_response = _parseResponse(response,errno);
    if(valid_response)
    {
        if(_getXresponse(status,response))
        {
            qDebug() << "fromMcaDU45Reply DU 45 OK, STATUS =" << status;
            if(status!=-1)
                emit(fromMcaDU45Reply(true,status));
            else
                emit(fromMcaDU45Reply(false,status));
        }
    }
    else
    {
        // We set false to indicate we failed
        // status is still -1 at this point
        // qDebug() << "fromMcaDU45Reply timeout";
         emit(fromMcaDU45Reply(false,status));
    }
    // restore loop count
    _setLoopCount(loops);
}



//%
//%  SLOT toMCACommandDU47 ()
//%  Requests Active Color Status
//%*****************************************************************
void GarfunkelCommandProcessor::toMCACommandDU47()
{
    //% tune loops so timeout is short
    int loops = _loopcount;
    _setLoopCount(20);

    int status = -1;
    std::string messagebuffer = "Ba:DU:47:"; 
    createESPString(messagebuffer);
    _ipc->sendStringMessage(messagebuffer);
    // NOW BLOCK WAITING FOR ACK/NAK AND RESPONSE
    std::string response("");
     //  qDebug() << "GarfunkelCommandProcessor::toMCACommandDU47 WAITING FOR RESPONSE";
    bool ackvalue = _rcvAll(response);
    if(ackvalue)
    {
        qDebug() << "fromMcaDU47Reply DU 47 OK";
        emit(fromMcaDU47Reply(true,status));
    }
    else
    {
        qDebug() << "fromMcaDU47Reply timeout";
        emit(fromMcaDU47Reply(false,status));
    }

   // qDebug() << "GarfunkelCommandProcessor::toMCACommandDU47 GOT RESPONSE" << response.c_str();
    int errno;
    bool valid_response = _parseResponse(response,errno);
    if(valid_response)
    {
        if(_getXresponse(status,response))
        {
            qDebug() << "fromMcaDU47Reply DU 47 OK, STATUS =" << status;
            if(status!=-1)
                emit(fromMcaDU47Reply(true,status));
            else
                emit(fromMcaDU47Reply(false,status));
        }
    }
    else
    {
        // We set false to indicate we failed
        // status is still -1 at this point
        // qDebug() << "fromMcaDU47Reply timeout";
         emit(fromMcaDU47Reply(false,status));
    }
    // restore loop count
    _setLoopCount(loops);
}









//%
//%  SLOT toMCACommandDU84 ()
//%  Checks Garfunkel Software version Number/Connection
//%*************************************************************

void GarfunkelCommandProcessor::toMCACommandDU84 ()
{
    //%clear old response
    std::string oldResponse("");
    bool ackval = _rcvAll(oldResponse);
    if(ackval)
    {
    //       qDebug() << "fromMcaDU84Reply DU84 OK";
    }
    else
    {
    //       qDebug() << "fromMcaDU84Reply timeout";
    }

    //% Begin with address as a address+payload, and later convert it to an ESP string
    std::string messagebuffer = "Ba:DU:84:"; 
    createESPString(messagebuffer);
    _ipc->sendStringMessage(messagebuffer);
    //%NOW BLOCK WAITING FOR ACK/NAK AND RESPONSE
    std::string response("");
    //qDebug() << "GarfunkelCommandProcessor::toMCACommandDU84 WAITING FOR RESPONSE";
    bool ackvalue = _rcvAll(response);
    if(ackvalue)
    {
    //       qDebug() << "fromMcaDU84Reply DU84 OK";
    }
    else
    {
    //       qDebug() << "fromMcaDU84Reply timeout";
    }

    //      qDebug() << "GarfunkelCommandProcessor::toMCACommandDU84 GOT RESPONSE" << response.c_str();
    Q_UNUSED(ackvalue);
    int errno;
    std::string result;
    bool valid_response = _parseResponse(response,errno);
    if(valid_response)
    {
        if(_getStringResponse(result,response))
        {
        QString qresponse(result.c_str());
        // qDebug() << "fromMcaDU84Reply DU84 qresponse="<<qresponse;
         emit(fromMcaDU84Reply(true,qresponse));
        }
    }
    else
    {
        // We set false to indicate we failed
        // status is still -1 at this point
        //  qDebug() << "fromMcaDU84Reply timeout";
        QString qresponse("No Connect");
        emit(fromMcaDU84Reply(false,qresponse));
    }
}


//%
//%  SLOT toMCACommandDU85 ()
//%  Returns Smart Simon IO Board DI String/Connection
//%*************************************************************

void GarfunkelCommandProcessor::toMCACommandDU85 ()
{
    //%clear old response
    std::string oldResponse("");
    bool ackval = _rcvAll(oldResponse);
    if(ackval)
    {
    //       qDebug() << "fromMcaDU85Reply DU85 OK";
    }
    else
    {
    //       qDebug() << "fromMcaDU85Reply timeout";
    }

    //% Begin with address as a address+payload, and later convert it to an ESP string
    std::string messagebuffer = "Ba:DU:85:"; 
    createESPString(messagebuffer);
    _ipc->sendStringMessage(messagebuffer);
    //%NOW BLOCK WAITING FOR ACK/NAK AND RESPONSE
    std::string response("");
    //qDebug() << "GarfunkelCommandProcessor::toMCACommandDU85 WAITING FOR RESPONSE";
    bool ackvalue = _rcvAll(response);
    if(ackvalue)
    {
    //       qDebug() << "fromMcaDU85Reply DU85 OK";
    }
    else
    {
    //       qDebug() << "fromMcaDU85Reply timeout";
    }

    //      qDebug() << "GarfunkelCommandProcessor::toMCACommandDU85 GOT RESPONSE" << response.c_str();
    Q_UNUSED(ackvalue);
    int errno;
    std::string result;
    bool valid_response = _parseResponse(response,errno);
    if(valid_response)
    {
        if(_getStringResponse(result,response))
        {
        QString qresponse(result.c_str());
        // qDebug() << "fromMcaDU85Reply DU85 qresponse="<<qresponse;
         emit(fromMcaDU85Reply(true,qresponse));
        }
    }
    else
    {
        // We set false to indicate we failed
        // status is still -1 at this point
        //  qDebug() << "fromMcaDU85Reply timeout";
        QString qresponse("No Connect");
        emit(fromMcaDU85Reply(false,qresponse));
    }
}




//%
//%  SLOT toMCACommandDU86 ()
//%  Returns Garfunkel IO Board DI String/Connection
//%*************************************************************

void GarfunkelCommandProcessor::toMCACommandDU86 ()
{
    //%clear old response
    std::string oldResponse("");
    bool ackval = _rcvAll(oldResponse);
    if(ackval)
    {
    //       qDebug() << "fromMcaDU85Reply DU85 OK";
    }
    else
    {
    //       qDebug() << "fromMcaDU85Reply timeout";
    }

    //% Begin with address as a address+payload, and later convert it to an ESP string
    std::string messagebuffer = "Ba:DU:86:"; 
    createESPString(messagebuffer);
    _ipc->sendStringMessage(messagebuffer);
    //%NOW BLOCK WAITING FOR ACK/NAK AND RESPONSE
    std::string response("");
    //qDebug() << "GarfunkelCommandProcessor::toMCACommandDU86 WAITING FOR RESPONSE";
    bool ackvalue = _rcvAll(response);
    if(ackvalue)
    {
    //       qDebug() << "fromMcaDU86Reply DU86 OK";
    }
    else
    {
    //       qDebug() << "fromMcaDU86Reply timeout";
    }

    //      qDebug() << "GarfunkelCommandProcessor::toMCACommandDU86 GOT RESPONSE" << response.c_str();
    Q_UNUSED(ackvalue);
    int errno;
    std::string result;
    bool valid_response = _parseResponse(response,errno);
    if(valid_response)
    {
        if(_getStringResponse(result,response))
        {
        QString qresponse(result.c_str());
        // qDebug() << "fromMcaDU86Reply DU86 qresponse="<<qresponse;
         emit(fromMcaDU86Reply(true,qresponse));
        }
    }
    else
    {
        // We set false to indicate we failed
        // status is still -1 at this point
        //  qDebug() << "fromMcaDU86Reply timeout";
        QString qresponse("No Connect");
        emit(fromMcaDU86Reply(false,qresponse));
    }
}









//=================================================================================================
//!
//!    \brief    ExecuteESPCommand()
//!
//!    \param[in]  command
//!
//!    \param[out] output
//!
//!    \return     bool  
//!
//!    \throw      None
//=================================================================================================
bool
GarfunkelCommandProcessor::ExecuteESPCommand(std::string& command, std::string& output)
{
    bool             retValue = false;
    IPCCommand       cmd(command);
    std::string      response("");
//#define DEBUGESP
//    std::cout << command << std::endl;
//#define PRINT_MESSAGE_CONTENTS
#ifdef PRINT_MESSAGE_CONTENTS
    std::cout << "Full Command: " << cmd.GetFullCommand() << std::endl;
    std::cout << "Address: " << cmd.GetAddress() << std::endl;
    std::cout << "Instance: " << cmd.GetInstance() << std::endl;
    std::cout << "Address & instance: " << cmd.GetAddressAndInstance() << std::endl;

    std::cout << "Command & Sub Command: " << cmd.GetCommandAndSubCommand() << std::endl;
    std::cout << "Command: " << cmd.GetCommand() << std::endl;
    std::cout << "Sub Command: " << cmd.GetSubCommand() << std::endl;
    std::cout << "Payload: " << cmd.GetPayload() << std::endl;
    std::cout << "Address Valid: " << cmd.IsAddressValid(_addressInstance) << std::endl;
#endif
    try
    {
        retValue = false;
        response = "";
        if (0 == cmd.IsAddressValid(_addressInstance))
        {
            boost::shared_ptr< AbstractIPCMessage > msg;
            std::map<std::string, boost::shared_ptr< AbstractIPCMessage > >::iterator    foundCmd;
             
            foundCmd = _commandMap.find(cmd.GetCommandAndSubCommand());       
            if(NULL != foundCmd->second && foundCmd != _commandMap.end())
            {     
                msg = foundCmd->second;
                if(msg.get() != NULL)
                {
                    _setConnected(true);
                    // TBD DU vs SU?????  Not here. Message itself can choose?
                    response = "";
                    if (True == (msg->processMessage(cmd, response))) 
                    {
#ifdef DEBUGESP
                        std::cout  << "CP RESPONSE = " << response << std::endl;
#endif
                        retValue = True;
                    }
                    else
                    {
                        std::cout  << "MESSAGE FAILED";
                    }
                }
            }
            else
            {
#ifdef DEBUGESP
std::cout << std::endl;
std::cout << "[GarfunkelCommandProcessor] Command Not Found -- Command: " << cmd.GetCommandAndSubCommand() << std::endl;                
std::cout << std::endl;
#endif
            }
        }
        else
        {
#ifdef DEBUGESP
            std::cout << "Address instance not valid" << std::endl;
            std::cout << "s/b " << _addressInstance << std::endl;
            std::cout << "is  " <<   cmd.GetAddress() << cmd.GetInstance() << std::endl;
#endif
        }
    }
    catch(std::exception & e)
    {
        std::cout << "Error retrieve message to process: " << e.what() << std::endl;
    }
   
    if (False == retValue || response.length() <= 0)
    {
#ifdef DEBUGESP
std::cout << std::endl;
std::cout << "FALSE [  GarfunkelCommandProcessor] invalid message -- return value: " << retValue << " response: " << response << " length: " << response.length() << std::endl;
std::cout << std::endl;
#endif
        output = cmd.GetAddressAndInstance() + ":ERR1:";
        ecolab::ESP::ESPStringCreate    createString;
        createString.ConvertToESPString(output);
        retValue = True;    
    }
    else
    {
        //output = cmd.GetAddressAndInstance() + response;
        output =  response;
        createESPString(output);
        // Now send to GarfunkelIpc to send the message
#ifdef DEBUGESP
        std::cout << std::endl;
        std::cout << "RESPONDING WITH: " << output << std::endl;
        std::cout << std::endl;
#endif
        _ipc->sendStringMessage(output);
    }
    return retValue;
}
//=================================================================================================
//!   createESPString
//=================================================================================================
bool
GarfunkelCommandProcessor::createESPString(std::string& dataToConvert)
{
    ecolab::ESP::ESPStringCreate    createString;

    return createString.ConvertToESPString(dataToConvert);
}
//=================================================================================================
//!   _parseResponse
//=================================================================================================
bool
GarfunkelCommandProcessor::_parseResponse(std::string& res, int& errno)
{
//        qDebug() << "GarfunkelCommandProcessor::_parseResponse PARSING RESPONSE= ";

    errno = 0;
    int len = res.length();
    if(len > 0)
    {
        if(res.compare(0, 1, _ACK) != 0)
        {
//            qDebug() << "ACK FAILED "; 
            return(false);
        }
        res.erase(0, 1);
        // search response for "ERR1". if found the response is not valid
        QString target(res.c_str());
        QString substr1("ERR1");
        QString substr11("ERR11");
        QString substr12("ERR12");
        if(target.contains(substr12))
        {
            qDebug() << "RESPONSE ERR12";
            errno = 12;
            return(false);
        }
        if(target.contains(substr11))
        {
            qDebug() << "RESPONSE ERR11";
            errno = 11;
            return(false);
        }
        if(target.contains(substr1))
        {
            qDebug() << "RESPONSE ERR1";
            errno = 1;
            return(false);
        }
        bool rv = convertESPString(res);
        if(rv)
        {
            int sz = res.size();
//            qDebug() << "sz = " << sz;
            const char * s = res.c_str();

//            QString rr(s);
//            qDebug() << "res = " << rr;

//            GarfunkelIpc::printMessage("GarfunkelCommandProcessor::_parseResponse",res);
            // Now that we have a string like "0a:0:"  we need to convert it to :0:
            // For now just strip off the first two characters
            std::string dest;
            for(int i = 2; i < sz; i++)
            {
                const char c = *(s+i);
                dest.append(1,c);
            }
            res.clear();
            res.assign(dest);
//            qDebug() << "BOOLEAN rv = " << rv;
            return( rv );
        }
        else
        {
            errno = -2;
#ifdef DEBUG
            qDebug() << "convertESPString FAILED "; 
#endif
            return(false);
        }
    }
    else
    {
            errno = -1;
#ifdef DEBUG
            qDebug() << "RESPONSE IS ZERO LENGTH";
#endif
    }
    return(false);
}
//=================================================================================================
//!   convertESPString
//=================================================================================================
bool
GarfunkelCommandProcessor::convertESPString(std::string& dataToConvert)
{
    ecolab::ESP::ESPStringCreate    convertString;
    return convertString.ConvertFromESPString(dataToConvert);
}
//=================================================================================================
//!
//!    \brief      _rcvAll
//!
//!    Called by commands going to MCA. Receives ACK and response message.
//!
//!    \param[in]  None
//!
//!    \param[out] msg   contains the message if return value is true.
//!
//!    \return     bool  true  if a message received. Caller must verify contents is ACK and
//!                            properly formatted response (with wrapper).
//!                      false if timed out with no packet received.
//!
//!    \throw      None
//=================================================================================================
bool
GarfunkelCommandProcessor::_rcvAll(std::string& msg)
{
    QElapsedTimer timer;
    int lapse_available = 0;
    int lapse_received = 0;

    std::string accum;
    unsigned char values[] = { 0x04 };
    std::string eot;
    eot.append(reinterpret_cast<const char *>(values), 1); // append 1 character to eot

#ifdef DEBUG
    qDebug() << "------------------------------------------------- AVAIL 1 " << QTime::currentTime().toString("ss.zzz");
#endif
    timer.start();
    for(int i = 0; i < _loopcount; i++)
    {
        bool avail = _ipc->isMessageAvailable();
        if(avail)
        {
            lapse_available = timer.elapsed();
#ifdef DEBUG
       qDebug() << "------------------------------------------------- AVAIL NOW " << QTime::currentTime().toString("ss.zzz");
#endif
#ifdef DEBUG
//qDebug() << "MESSAGE AVAILABLE";
#endif
            // get some bytes from the
            std::string part;
#ifdef DEBUG
       qDebug() << "------------------------------------------------- RCVING MSG " << QTime::currentTime().toString("ss.zzz");
#endif
            _ipc->receiveStringMessage(part);
#ifdef DEBUG
//qDebug() << "GOT MESSAGE ";
#endif
            accum += part;
            size_t found = accum.find(eot);
            if(found)
            {
#ifdef DEBUG
//qDebug() << "FOUND EOT ";
#endif
                // We have a fully formed response message
                msg.assign(accum);
            lapse_received = timer.elapsed();
#ifdef DEBUG
       qDebug() << "------------------------------------------------- Time to message availability took" << lapse_available << "milliseconds";
       qDebug() << "------------------------------------------------- Time to message received took" << lapse_received << "milliseconds";
#endif
                return true;
            }
        }
        usleep(_sleep_factor);
    }
    return false;
}
#ifdef IGNORE
//=================================================================================================
//!
//!   _getBitfieldResponse
//!
//!   Commands that take one bitfield argument (such as DU26) call this to extract the argument.
//!
//!    \param[in]  A string of the form ":11011101:".
//!
//=================================================================================================
bool 
GarfunkelCommandProcessor::_getBitfieldResponse(unsigned long& bits, std::string& response)
{
    // strip leading and trailing colons
    int len = response.size();
    if(len >= 3)
    {
        std::string bitstring("");
        const char* s = response.c_str();
        for(int i = 1; i < (len-1) ; i++)
        {
            char c = *(s+i);
            bitstring.append(1, c );
        }
//        qDebug() << "VALID STRIPPED RESPONSE STRING = " << bitstring.c_str();

        const std::bitset<16> mybits(bitstring);
        bits = mybits.to_ulong();
        return true;
    }
    else
    {
//        qDebug() << "RESPONSE STRING TOO SHORT FOR _getBitfieldResponse";
        return false;
    }
}
#endif
//=================================================================================================
//!
//!   _getXresponse
//!
//!   Commands that take one arguments (such as DU24) call this to extract the argument.
//!
//!    \param[in]  A string of the form ":123:".
//!
//=================================================================================================
bool 
GarfunkelCommandProcessor::_getXresponse(int& x, std::string& response)
{
//    qDebug() << "response = " << response.c_str();
    // strip leading and trailing colons
    int len = response.size();
    if(len >= 3)
    {
        std::string t("");
        const char* s = response.c_str();
        for(int i = 1; i < (len-1) ; i++)
        {
            char c = *(s+i);
            t.append(1, c );
        }
//        qDebug() << "VALID STRIPPED RESPONSE STRING = " << t.c_str();

        // response is X 

        bool ok;
        QString qresponse(t.c_str());
        x = qresponse.toInt(&ok,10);
        if(ok)
        {
//            qDebug() << "  GOT X = " << x ;
            return true;
        }
        else
        {
            qDebug() << "  INVALID STRING, CANNOT CONVERT TO INTEGER, got STR="<<ok;;
            return false;
        }
    }
    else
    {
        qDebug() << "RESPONSE STRING TOO SHORT FOR _getXresponse";
        return false;
    }
}
//=================================================================================================
//!
//!   _getStringResponse
//!
//!   Commands that take two arguments (such as DU20) call this to extract the arguments.
//!
//!    \param[in]  A string of the form ":Aqualogic,rev A.B.C,ZZZZZ:".
//!
//=================================================================================================
bool 
GarfunkelCommandProcessor::_getStringResponse(std::string& result, std::string& response)
{
    int len = response.size();
    if(len >= 3)
    {
        // strips leading and trailing colon from string
        const char* s = response.c_str();
        for(int i = 1; i < (len-1) ; i++)
        {
            char c = *(s+i);
            result.append(1, c );
        }
        return true;
    }
    else
    {
        qDebug() << "_getStringResponse: RESPONSE STRING TOO SHORT FOR DU";
        return false;
    }
}
//=================================================================================================
//!
//!   _getXYresponse
//!
//!   Commands that take two arguments (such as DU20) call this to extract the arguments.
//!
//!    \param[in]  A string of the form ""123:476:".
//!
//=================================================================================================
bool GarfunkelCommandProcessor::_getXYresponse(int& x, int& y, std::string& response)
{
    // strip leading and trailing colons
    int len = response.size();
    if(len >= 5)
    {
        std::string t("");
        const char* s = response.c_str();
        for(int i = 1; i < (len-1) ; i++)
        {
            char c = *(s+i);
            t.append(1, c );
        }
//        qDebug() << "VALID STRIPPED RESPONSE STRING = " << t.c_str();

        // response is X:Y so split the string

        QString qresponse(t.c_str());
//        qDebug() << " fromStdString is " << qresponse;
        QStringList list = qresponse.split(":");
//        qDebug() << "list size = " << list.size();

        // Convert the X.Y values

        x = list[0].toInt();
        y = list[1].toInt();
//        qDebug() << " DU GOT X= " << x << "  Y= " << y;
        return true;
    }
    else
    {
        qDebug() << "RESPONSE STRING TOO SHORT FOR DU";
        return false;
    }
}
//=================================================================================================
//!
//!   setConnected()
//!
//!   Only transmit CHANGES  in connected state
//=================================================================================================
void GarfunkelCommandProcessor::_setConnected(bool b)
{
    QMutexLocker lock(&connectionMutex);
    if(true == b)
    {
        if(!_connected )
        {
            _connected = true;
            qDebug() << "GarfunkelCommandProcessor::_setConnected:  EMITTING setConnectionUp";
            emit setConnectionUp();
        }
    }
    else
    {
        if(_connected )
        {
            _connected = false;
            qDebug() << "GarfunkelCommandProcessor::_setConnected:  EMITTING setConnectionDown";
            emit setConnectionDown();
        }
    }
}
//=================================================================================================
//!
//!   _setConnectionDown()
//!
//!   Private method to set condition and send public signal.
//=================================================================================================
void GarfunkelCommandProcessor::_setConnectionDown()
{
    _setConnected(false);
    emit setConnectionDown();
}

bool GarfunkelCommandProcessor::_isConnected()
{
    QMutexLocker lock(&connectionMutex);
    if(true == _connected)
    {
        return true;
    }
    else
    {
        return false;
    }
}



//=================================================================================================
//%
//%   MCA: SLOT toMCACommandSU50() // Enable/Disable Diagnostics
//%                
//=================================================================================================
void  GarfunkelCommandProcessor::toMCACommandSU50(int x)
{
    if(!_isConnected())
    {
       emit(fromMcaSU50Error(0)); // 0 = Communications I/O is down
       return;
    }
    QString buf("Ba:SU:50:");
    QString xstr;   
    std::stringstream ssx;
    ssx << x;
    std::string sx = ssx.str();
    std::string messagebuffer = "Ba:SU:50:" + sx + ":";
    createESPString(messagebuffer);
    _ipc->sendStringMessage(messagebuffer);
    std::string response(""); // NOW BLOCK WAITING FOR ACK/NAK AND RESPONSE
    bool ackvalue = _rcvAll(response);
    if(ackvalue)
    {
        int errno;
        bool valid_response = _parseResponse(response,errno);
        _setConnected(true); 
        if(!valid_response)
        {
            emit(fromMcaSU50Error(1)); // 1 =  "ERR1"  unpecified returned from MCA
            return;
        }
        else
        {
            emit fromMcaSU50ReplyOK(x); //% Gives you back x means no ERROR from MCA
                                        //% x = 1 : Means Enabling Diagnostics Mode Successful
                                        //% x = 0 : Means Disable Diagnotics Mode Sucessful
            return;                 
        }
    }
    else
    {
        _setConnected(false); 
    }
}


//=================================================================================================
//%
//%    \brief    SLOT toMCACommandSU51( int x, int y)
//%
//%    Inputs:   X current Diagnostics State, Y for activate or disactivate
//%
//%    Output: Nothing
//%
//%    Returns: Nothing  
//%
//%    Throws: Nothing     
//=================================================================================================
void GarfunkelCommandProcessor::toMCACommandSU51(int x, int y)
{

   qDebug() << "SU51 trying isConnected at " << QTime::currentTime().toString("ss.zzz") << " x= "  << x << " y= " << y ;
    if(!_isConnected())
    {
      // qDebug() << "SU51 Communications I/O is down, returning fromMcaSU51Error(2) SHOULD NOT HAPPEN";
       emit(fromMcaSU51Error(2)); //% We decide that When SU51Erro(2) It means( my interpretation, to avoid conflict with SU50Error(1) )  Communications I/O is down
       return;
    }
    //qDebug() << "toMCACommandSU51: here";
    QString buf("Ba:SU:51:");
    QString xstr;  //% Valve Type
    QString ystr;  //% Activate/DeActivate Valve
    switch(x)
    {
        case 0:
            qDebug() << "SU51 Command S Product Valve";
            break;
        case 1:

            qDebug() << "SU51 Command P Product Valve";
            break;
        case 2:
            qDebug() << "SU51 Command Aquanomics dilution water Inlet";
            break;
        case 3:
            qDebug() << "SU51 Command O1 Valve";
            break;
        case 4:
            qDebug() << "SU51 Command O2 Valve";
            break;
        case 5:
            qDebug() << "SU51 Command O1 Drain Valve";
            break;


        default:
            return;
    }

    std::stringstream ssx;
    std::stringstream ssy;
    ssx << x;
    ssy << y;
    std::string sx = ssx.str();
    std::string sy = ssy.str();
    std::string messagebuffer = "Ba:SU:51:" + sx + ":" + sy + ":" ;
    createESPString(messagebuffer);
#ifdef DEBUG2
    qDebug() << "toMCACommandSU51: After createESPString ";
    QString n = messagebuffer.c_str();
    qDebug() << "SENT  in SU51 " << n;
#endif
    // Now send to AqualogicIPC to send the message
//    qDebug() << "toMCACommandSU51: Sending message";
    _ipc->sendStringMessage(messagebuffer);
//    qDebug() << "toMCACommandSU51: Sending message done";

    // NOW BLOCK WAITING FOR ACK/NAK AND RESPONSE
    std::string response("");
#ifdef DEBUG2
qDebug() << "------------------------------------------------- RCVING MSG 1" << QTime::currentTime().toString("ss.zzz");
#endif
    bool ackvalue = _rcvAll(response);
#ifdef DEBUG2
       qDebug() << "------------------------------------------------- RCVING MSG 2" << QTime::currentTime().toString("ss.zzz");
#endif
    if(ackvalue)
    {
        int  errno;
        bool valid_response = _parseResponse(response, errno);
#ifdef DEBUG2
       qDebug() << "------------------------------------------------- RCVING MSG 3" << QTime::currentTime().toString("ss.zzz");
#endif
        if(!valid_response)
        {
//            qDebug() << "INVALID RESPONSE STRING IN SU53";
            emit(fromMcaSU51Error(3)); // //% We decide that When SU51Erro(3)  3 =  "ERR1" ( Again, my interpretation)  returned from MCA
            return;
        }
        else
        {
#ifdef DEBUG2
            qDebug() << "GOOD RESPONSE STRING IN SU51";
#endif
// It doesnt make any sense to replyOK if not valid response       if(!valid_response)
            emit fromMcaSU51ReplyOK(0);  //% We decide that When SU51ReplyOK(0) then We are Good! 
            return;
        }
    }
    else
    {
//        qDebug() << "GarfunkelCommandProcessor::toMCACommandSU51: RECEIVE FAILED SO SET CONNECTION DOWN()";
        _setConnected(false);
    }
}

