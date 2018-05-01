#ifndef GARFUNKEL_COMMAND_PROCESSOR_H
#define GARFUNKEL_COMMAND_PROCESSOR_H

#include <map>
#include <string>

#include "abstractcommandprocessor.h"
#include "CommManager.h"
#include <QMutex>
#include <QVector>
//#include "GarfunkelDB.h"

// Forward Declarations
class GarfunkelIpc;
class GarfunkelCommThread;


//% Note: Changes:
//%             We will use "Ba"  instead of the present "Oa" for AddressInstance,
//%                 i.e B = Address & a = Instance 
//%             As from Feb 02, 2016


//%=================================================================================================
//%   MCA  Registered Messages Begin Here!!
//%=================================================================================================


//=================================================================================================
//%
//%    Signal SU51Message sent to UI when Diagnostics is Complete SU:51:X:Y2
//%
//=================================================================================================
class SU51Message : public AbstractIPCMessage
{
    Q_OBJECT

    public:
    SU51Message(GarfunkelIpc* ipc, GarfunkelCommThread* comm);
    virtual ~SU51Message();

    virtual bool processMessage(IPCCommand& command, std::string& response);

    signals:
    void toUiCommandSU51 (int X, int Y);

    protected:

    private:
    GarfunkelCommThread* _comm;
};




//%%=================================================================================================
//%
//%    to UI SU65Message  SU:65:A:B , A: for Total Time, B: Delay Timer
//%
//%%=================================================================================================
class SU65Message : public AbstractIPCMessage
{
    Q_OBJECT

    public:
    SU65Message(GarfunkelIpc* ipc, GarfunkelCommThread* comm);
    virtual ~SU65Message();

    virtual bool processMessage(IPCCommand& command, std::string& response);

    signals:
    void toUiCommandSU65 (int A, int B); // X

    protected:

    private:
    GarfunkelCommThread* _comm;
};



//%=================================================================================================
//%
//%   to UI  SU52Message 
//%   
//%   Diagnostic Infos/Data to UI MCA to UI Command SU:52:A:B:C:D:E
//%   A: = Total Time
//%   B: = Timer (Range: TBD)
//%   C: = Pressure Switch Status (bool or int?)
//%   D: = Temperature in C
//%   E: = Conductivity in uS/cm
//%
//%=================================================================================================
class SU52Message : public AbstractIPCMessage
{
    Q_OBJECT

    public:
    SU52Message(GarfunkelIpc* ipc, GarfunkelCommThread* comm);
    virtual ~SU52Message();

    virtual bool processMessage(IPCCommand& command, std::string& response);

    signals:
    void toUiCommandSU52(int, int, int, float, float); // A,B,C,D,E

    protected:

    private:
    GarfunkelCommThread* _comm;
};




//%=================================================================================================
//%
//%    to UI SU53Message Internal Error/Diagnostic Operation Failed Message
//%
//%=================================================================================================
class SU53Message : public AbstractIPCMessage
{
    Q_OBJECT

    public:
    SU53Message(GarfunkelIpc* ipc, GarfunkelCommThread* comm);
    virtual ~SU53Message();

    virtual bool processMessage(IPCCommand& command, std::string& response);

    signals:
    void toUiCommandSU53(); //%  No Message Indicating Operation failed, not reset State

    protected:

    private:
    GarfunkelCommThread* _comm;
};





//=================================================================================================
//!
//!    GarfunkelCommandProcessor
//!
//=================================================================================================
class GarfunkelCommandProcessor : public AbstractCommandProcessor
{

    Q_OBJECT

    public:
        static QMutex connectionMutex;
        GarfunkelCommandProcessor (GarfunkelIpc* ipc, CommManager::MCACommType commtype, GarfunkelCommThread* parent);
        virtual ~GarfunkelCommandProcessor ();
        
        // This method contacts DB and sets instance address
        // Override because  application specific methods.
        virtual int initializeCommandProcessor (const std::string& database, const std::string& databaseItem);
        bool ExecuteESPCommand (std::string& command, std::string& output);
        bool isMaster ();
        bool convertESPString (std::string&);
        bool createESPString (std::string&);
        void initializeMasterKeepAlive ();
    
    signals:
        void setConnectionUp ();
        void setConnectionDown ();
    //=============================================================
    //
    // Support for MASTER CHANNEL SU COMMUNICATIONS
    //
    //=============================================================
    signals:
            //
            //%SU commands originating from MCA
            //

            //
            //% ReplyOK returned to the UI
            //
            void fromMcaSU50ReplyOK ( int X);
            void fromMcaSU51ReplyOK ( int X);

            //
            // Errors returned to the UI
            //
            void fromMcaSU50Error ( int X);
            void fromMcaSU51Error ( int X);
            //
            //%DU commands originating from MCA
            //
            //void fromMcaDU40Reply (bool,int); //% MCA Reply for DU40 command requesting for State Status/connection Up/Down
            //%  MCA DU Replies:
            void fromMcaDU40Reply (bool, int); //% reply from DU40 command to MCA for connectivity/ System Status
            void fromMcaDU41Reply (bool, int); //% Reply from MCA for Command DU41 for Operating Schedule Status
            void fromMcaDU42Reply (bool, int); //% Reply from MCA for Command DU42 for MakeDown Process Active
            void fromMcaDU43Reply (bool, int); //% Reply from MCA for Command DU43 for Dispense Active
            void fromMcaDU44Reply (bool, int); //% Reply from MCA for Command DU44 for Layup Mode Status
            void fromMcaDU45Reply (bool, int); //% Reply from MCA for Command DU45 for Standby Mode status
            void fromMcaDU47Reply (bool, int); //% Reply from MCA for Command DU47 for Active Color Status

            void fromMcaDU84Reply(bool, QString); //% Reply from MCA for Command DU84 for Garfunkel Software Version Number
            void fromMcaDU85Reply(bool, QString); //% Reply from MCA for Command DU85 for Smart Simon IO Board DI String
            void fromMcaDU86Reply(bool, QString); //% Reply from MCA for Command DU86 for Garfunkel IO Board DI string

            //
            // These slots get called via a queued signal from the UI to ask for data. 
            // The reply of the PDU's causes a signal of the form GarfunkelCommandProcessor::fromMcaYYXXReply
            // to slot GarfunkelSystemData::fromMcaYYXXReply().
            //
    public slots:
    
#ifdef ABORT
            void abortIPC ();
#endif
            //Recieving Signals from GarfunkelSystemData class
         	void toMCACommandDU40 (); //% TO MCA for DU40 command requesting for State Status/connection Up/Down
            void toMCACommandDU41 (); //% To MCA for Command DU41 for Operating Schedule Status
            void toMCACommandDU42 (); //% To MCA for Command DU42 for MakeDown Process Active
            void toMCACommandDU43 (); //% To MCA for Command DU43 for Dispense Active
            void toMCACommandDU44 (); //% To MCA for Command DU44 for Layup Mode Status
            void toMCACommandDU45 (); //% To MCA for Command DU45 for Standby Mode status
            void toMCACommandDU47 (); //% To MCA for Command DU47 for Active Color Status

            void toMCACommandDU84 (); //% To MCA for DU84 for Garfunkel Software Version Number
            void toMCACommandDU85 (); //% To MCA for DU85 for Smart Simon IO Board DI String
            void toMCACommandDU86 (); //% To MCA for DU86 for Garfunkel IO Board DI string 

            void toMCACommandSU50 (int X );  //% SIGNAL from SystemData class to MCA of SU50 Command to Enable/Disable diagnostic Mode
            void toMCACommandSU51 (int X, int Y); //% SIGNAL from SystemData class to MCA of SU51 Command to Activate/Disactivate Diagnostic State for a given product 

    //=============================================================
    //
    // General helper methods
    //
    //=============================================================
    protected:
          bool _getBitfieldResponse (long unsigned int&, std::string&);
          bool _getXresponse (int& x, std::string& response);
          bool _getXYresponse (int& x, int& y, std::string& response);
          bool _getStringResponse (std::string& result, std::string& response);
          bool _isConnected ();
          void _setConnected (bool b);
          void _setConnectionDown (); // All  methods can call this, it handles details of signaling UI

    //=============================================================
    //
    // Private elements
    //
    //=============================================================
    private:
          void                     _setLoopCount (int x) { _loopcount = x; }
          void                     _setSleepFactor (int x) { _sleep_factor = x; }
          bool                     _parseResponse (std::string& res, int&);
          bool                     _rcvAll (std::string& msg);
          int                      _loopcount;    // for _recvAll timing
          int                      _sleep_factor; // for _recvAll timing
          GarfunkelCommThread*           _parent;
          GarfunkelIpc*                  _ipc;
          CommManager::MCACommType _commtype;
          std::string              _ACK;
          std::string              _NACK;
          bool                     _diTimerScheduled;
          QTimer                   _diTimer;
          static bool              _connected; // this flag is used to keep the GUI  responsive  without suffering long timeouts
};    

#endif //GARFUNKEL_COMMAND_PROCESSOR_H
