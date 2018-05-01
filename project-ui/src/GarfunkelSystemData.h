#ifndef GARFUNKEL_SYSTEM_DATA_H
#define GARFUNKEL_SYSTEM_DATA_H

#include  <QtCore>

//
//% GarfunkelSystemData class is the main conatiner class
//% Talking back and forth with the MCA and
//% holding data of information about the 
//% Whole systems: Other Container classes talk to this class
//% to get their information/data
//
class GarfunkelSystemData : public QObject
{
	Q_OBJECT	
    
    public:
    	//
    	//% GarfunkelSystemData class is a Singleton Construction
    	//% Single Instance through out Application life
    	//
    	static GarfunkelSystemData & Instance ();
    	static QPointer<GarfunkelSystemData>  getInstancePtr ();

    	//
    	//% GarfunkelSystemData class Destructor
    	//
        virtual ~ GarfunkelSystemData ();
       
       //% Do we have a connection?
       void checkFirstConnection ();
       
       //% Whats the System Status?
       enum SystemStatus
       {
       	SystemStatusUnknown           = -1,
        SystemStatusIdle,
        SystemStatusDiagnosticsActive,
        SystemStatusSystemError  
       };

       //% LED State
       enum LEDState
       {
       	LEDOff = 0,
       	LEDOn
       };

       //% LID STATE
       enum LidState
       {
       	 Close = 0,
       	 Open
       };

       //%  VALVE SWITCH Status
       enum ValveSwitchStatus
       {
       	 ValveSwitchClose = 0,
       	 ValveSwitchOpen  
       };

       //% ValveToggleState
       enum ValveToggle
       {
       	 ValveToggleOff = 0,
       	 ValveToggleOn 
       };

       //% TimerState
       enum TimerState
       { 
         UnknownTimerState  = -1,    
         DiagTimerState  
      };
       
      //% SystemDiagnostics Status
      enum SystemDiagnostics
      {
      	UnknownDiagnostic = -1,
      	DiagnosticNotEnabled,
      	DiagnosticsEnabled
      };

      //% Measuring Units
      enum UnitOfMeasure
      {
      	Standard = 0,
      	Metric 
      };

      //%% This Class Recives(from UI/MCA) and Emits(to UI/MCA) Signals
      bool isConnected ();

signals:
  	  //% Mostly Signals to the MCA through the CommandThread(Interpreter)
      //
//
      //% UI to MCA SIGNALING DIAGNOSTICS
      void toMCACommandDU40 ();       //% First connection test/Get System Status. Also gets some parameters    
      //% Signals emitted after DU40 Response 
      void SystemStatusChanged (int X);        //% Signal emitted from reply of DU40 Command that New system status detected
      void ioConnectionUp ();                //%sent when MCA has connected again after timing out
      void ioConnectionDown ();              //%sent when MCA has timed out  


 
      void toMCACommandDU41 (); //% To MCA for Command DU41 for Operating Schedule Status
      void toMCACommandDU42 (); //% To MCA for Command DU42 for MakeDown Process Active
      void toMCACommandDU43 (); //% To MCA for Command DU43 for Dispense Active
      void toMCACommandDU44 (); //% To MCA for Command DU44 for Layup Mode Status
      void toMCACommandDU45 (); //% To MCA for Command DU45 for Standby Mode status
      void toMCACommandDU47 (); //% To MCA for Command DU47 for Active Color Status
      //% Signals Emitted after response of Above Commands
      void garfunkelOpScheduleStatus (int X); //Emitted after DU:41 Reply
      void garfunkelMakeDownProcessActive (int X); //Emitted after DU:42 Reply
      void garfunkelDispenseActive (int X); //Emitted after DU:43 Reply
      void garfunkelLayupModeStatus (int X); //Emitted after DU:44 Reply
      void garfunkelStandbyModeStatus (int X);  //%Emitted after DU:45 Reply
      void garfunkelActiveColorStatus (int X);  //% Emiited after DU:47 Reply

      void toMCACommandDU84 (); //% To MCA for DU84 for Garfunkel Software Version Number
      void toMCACommandDU85 (); //% To MCA for DU85 for Smart Simon IO Board DI String
      void toMCACommandDU86 (); //% To MCA for DU86 for Garfunkel IO Board DI string 
      void garfunkelSoftwareVersion (QString gswversion); //% Emit Signal from Reply of DU:84
      void sSimonIOBoardFirmwareVersion (QString ssfversion); //%Emit signal from Reply of DU:85
      void garfunkelIOBoardFirmwareVersion (QString gfwversion); //% Emit Signal from Reply of DU:86
     


      void toMCACommandSU50 ( int X );     //% SIGNAL from this class to MCA to Enable/Disable diagnostic Mode
      void toMCACommandSU51 ( int X, int Y); //% SIGNAL from this class to MCA to activate/Disactivate Diagnostic State for a given product

      //% Signal sent by this class to Others/UI in response MCA reply
      void toUiSU50Reply (int X );   //% Signal SU50 Reply from MCA
      void toUiSU51Reply (int X);   //% Signal SU51 Reply from MCA
      void toUiSU50Error (int X);  //% Signal Error from MCA if SU50 Command Failed
      void toUiSU51Error (int X);  //% Signal Error from MCA if SU51 Command Failed

      void diagOpComplete ();    //% Signal sent to other model in responses to from MCA SU51:X:Y = 2 that diagnostic is complete
      void diagDelayTimerEvent(int a, int b);   //% MCA sends Total Timer(a) & Delay timer(b) values during diag in an SU:65:A:B
      void internalErrorEvent (); //% signal sent by this class in response to toUiCommandSU53 internal error in diagnostics SU:53:X

      void diagDataUpdated (int a, int b, int c, float d, float e); //% Signal sent to UI in response to toUiCommandSU52
/*    
       
      //% Response to successfull SU commands
      void diagnosticsStarting ();  //% Signal sent by this class in response to reply fromMcaSU50ReplyOkay from SU:50:X
      void diagnosticsStoping ();   //% Signal sent by this class in response to reply fromMcaSU50ReplyOkay from SU:50:X
      void opComplete(int,int,int, int, int, int); //% response to SU:52 of diagnostic Operation complete

      
*/
      //
      //% SLOTS TO RECEIVE & SEND SIGNALS
      //
public slots:
	 
      void _kaUpdate ();
	  
      //% Testing: connection with MCA
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
      //% Requests from UI to this class
      void fromUiCommandSU50 ( int x ); //% Enable/Disabled Diagnostic ReQuest Signal from UI request to this class
      void fromUiCommandSU51 ( int x, int y); //% Activate/Disactivate Diagnostic Request Signal from UI to this class for a particular product

      //% SLOTS/functions which Send the Signals to MCA
      void fromUiCommandDU41 (); //% To MCA for Command DU42 for Operating Schedule Status
      void fromUiCommandDU42 (); //% To MCA for Command DU42 for MakeDown Process Active
      void fromUiCommandDU43 (); //% To MCA for Command DU43 for Dispense Active
      void fromUiCommandDU44 (); //% To MCA for Command DU44 for Layup Mode Status
      void fromUiCommandDU45 (); //% To MCA for Command DU42 for Standby Mode status
      void fromUiCommandDU47 (); //% To MCA for Command DU42 for Active Color Status

      void fromUiCommandDU84 (); //% To MCA for DU84 for Garfunkel Software Version Number
      void fromUiCommandDU85 (); //% To MCA for DU85 for Smart Simon IO Board DI String
      void fromUiCommandDU86 (); //% To MCA for DU86 for Garfunkel IO Board DI string 

      //% this class to UI
      //% Never Sends Enable/Disable Diagnostic to UI?
      //% void toUiCommandSU50 ( int x); //% from this class to UI command SU:50:X 
      void toUiCommandSU51 ( int X, int Y); //%  from this class to UI command SU:51:X:Y ( Y = 2, emit diagnostic completion signal)
      void toUiCommandSU65 ( int A, int B ); //% Total Time/Delay Timer Information sent to UI through this class from MCA Command SU:65:A:B, A:Total Time, B:Delay Timer

      void toUiCommandSU52 ( int A, int B, int C, float D, float E); //% Total Time/Timer/Pressure SwitchStatus/Temperature/Conductivity: Diagnostic Info sent to UI from this class
      void toUiCommandSU53 (); //% Internal Error During Diganostics This message means Diagnostics or related Operation failed/ Reset State SU53 ( No X in document)

      //% From MCA replies Okay/Error
      void fromMcaSU50ReplyOK ( int X ); //% MCA SU50 Reply is OK
      void fromMcaSU51ReplyOK ( int X ); //% MCA SU51 reply OK     
      void fromMcaSU50Error ( int X); //% MCA SU50 Reply Error
      void fromMcaSU51Error ( int X); //% MCA SU51 reply Error 

      //% Lets Know the Timer State
      void setTimerState ( int X );
      
      //
      //% Connection up or Down
      void setConnectionUp ();
      void setConnectionDown ();


//% Now Gimme some Privacy
private:

	    GarfunkelSystemData (); //Ofcourse fails Big time! Such a construction for a Singleton NOT POSSIBLE!
 
      //% for Time Countdaown
      QTimer     _kaTimer;
      bool       _connected; //% True means MCA us connected
      bool 		 _firstConnection; //% True means we have never sent a connection to MCA
      TimerState _timerState;

      SystemStatus    _systemStatus;

      int _opSchedule ; // Operating Shedule  0: Primary, 1: Secondary
      int _makeDownStatus ; //% Makedown Active Process: 0: Not Active, 1: Active
      int _dispenseActiveState; //% Dispense Active State : 0: Not Active, 1: Active
      int _layupModeStatus; //% Layup Mode Status, 0: layup mode disable, 1: enabled
      int _standByModeStatus;  //% StandBy Mode Status, 0: Disabled, 1:Enabled
      int _activeColorStatus;  //% Active Color Status,  

};

#endif //GARFUNKEL_SYSTEM_DATA_H
