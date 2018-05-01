//% Qt Stuff
#include <QProcess>
#include <QDateTime>
#include <QDebug>

#include "GarfunkelSystemData.h"
//
//% Our Beloved Siggleton
//
GarfunkelSystemData &GarfunkelSystemData::Instance ()
{
	static GarfunkelSystemData siggleton;
	return siggleton;

}

//
//% Beloved Pointer to Singleton instance of GarfunkelSystemData
//
QPointer<GarfunkelSystemData> GarfunkelSystemData::getInstancePtr ()
{
	GarfunkelSystemData & instance = Instance ();
	return &instance;
}

//
//% Garfunkel System Data Non Singleton Construction
//
GarfunkelSystemData::GarfunkelSystemData ()
{
	_firstConnection = true;
	_connected    	 = false;
	_timerState		 = UnknownTimerState;
	_systemStatus	 = SystemStatusUnknown;
        _opSchedule 	= -1; // Operating Shedule  0: Primary, 1: Secondary
        _makeDownStatus = -1; //% Makedown Active Process: 0: Not Active, 1: Active
        _dispenseActiveState = -1; //% Dispense Active State : 0: Not Active, 1: Active
        _layupModeStatus     = -1; //% Layup Mode Status, 0: layup mode disable, 1: enabled
        _standByModeStatus   = -1;  //% StandBy Mode Status, 0: Disabled, 1:Enabled
        _activeColorStatus   = -1;  //% Active Color Status,  
	//% More like LID/Valve/LED/ etc status
}

//
//% The Destructor!!
//

GarfunkelSystemData::~GarfunkelSystemData ()
{

}



//%====================================================================================
//%
//%  setTimerState
//%
//% \param[in]  SystemData::TimerState
//%
//%====================================================================================
void GarfunkelSystemData::setTimerState(int state)
{
    _timerState = (TimerState) state;
}

//%====================================================================================
//% _kaUpdate
//% Used to HKeep life Update
//% Everytime connection is down, send DU40 command to MCA to bring
//% connection back up!!
//%====================================================================================
void GarfunkelSystemData::_kaUpdate ()
{
   if (!isConnected () )
   {
    //% A repsonse to this command by the MCA means commenction would come up
   	qDebug() << "sending DU40 Command to MCA";
   	toMCACommandDU40();
   }

}

//
//%
//% Check First connection
//
void GarfunkelSystemData::checkFirstConnection()
{
	if (_firstConnection )
	{
		_connected = false;
		//% Now Send DU40 Command
		qDebug() << "Emmitting toMCACommandDU40 ()";
		emit toMCACommandDU40();
		_firstConnection = false;
	}

	//% Connect Now
	connect ( &_kaTimer, SIGNAL(timeout() ), this, SLOT(_kaUpdate()) );
	_kaTimer.start ( 2000);

}

//%======================================================================================
//%
//%   SLOT   setConnectionDown()
//%
//%======================================================================================
void GarfunkelSystemData::setConnectionDown()
{
    //qDebug() << "\n\nSystemData::setConnectionDown()\n\n";
    // Were we previously up?
    if(true == _connected)
    {
        _connected = false;
        // First reset the flag
        //  Then emit AFTER setting the flag. This is because subscribers may call isConnected
        //  before we return from emit().
        emit ioConnectionDown();
    }
    _connected = false;
}
//%======================================================================================
//%
//%   SLOT   setConnectionUp()
//%
//%   DU40 COMMAND from MCA  to  UI
//%
//%   This is a PING from the MCA. 
//%
//%   It is used to notify the UI  that the MCA is now connected and listening.
//%   This is because  _connected flag may have been set false. It would be set false 
//%   because a timeout happened if the MCA crashed. 
//%======================================================================================
void GarfunkelSystemData::setConnectionUp()
{
    qDebug() << "\n\nGarfunkelSystemData::setConnectionUp()\n\n";
    // Were we previously down?
    if(false == _connected)
    {
        qDebug() << "\n\nGarfunkelSystemData::setConnectionUp CONNECTED UP\n\n";
        // First set the flag
        _connected = true;
        //  Then emit AFTER setting the flag. This is because subscribers may call isConnected
        //  before we return from emit().
        emit ioConnectionUp();
    }
    _connected = true;
}

//%======================================================================================
//   isConnected
//
//   Used by UI to verify the MASTER channel has not gone down.
//%======================================================================================
bool  GarfunkelSystemData::isConnected()
{
    return( _connected );
}
//#ifdef HYDRIS_EXAMPLE


//%=====================================================================================
//%
//% SLOTS 
//%
//%=====================================================================================

///============================================================================================
//%  SLOT: fromMcaDU40Reply
//% 	If b is true, the connection is up
//%     x: represents status of MCA
//%     x = 0 means BootUp 
//%     x = 1 means Idle/Normal Operations
//%     x = 2 means Diagnostics
//%     x = 3 means Standby
//%     if b is false, then MCA is down and there is no connection
//============================================================================================

void GarfunkelSystemData::fromMcaDU40Reply ( bool b, int x )
{
	if ( x !=_systemStatus )
	{
		emit SystemStatusChanged (x);
		_systemStatus = (GarfunkelSystemData:: SystemStatus )x;
	}
	if (b)
	{
		setConnectionUp ();
	}
	else
	{
		setConnectionDown ();
	}
}




//%============================================================================================
//%
//%   SLOT/function:
//%                 fromUiCommandDU41: DU:41 Signal from UI
//%
//%                 To Request Operating Schedule Status
//%
//%============================================================================================
void GarfunkelSystemData::fromUiCommandDU41 ( )

{
    if(isConnected())
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU41 IS CONNECTED TRYING TO SEND COMMAND" ;
        emit( toMCACommandDU41());
    }
    else
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU41 IS NOT CONNECTED ";
        emit(ioConnectionDown());
    }
}



///============================================================================================
//%  SLOT: fromMcaDU41Reply
//%     If b is true, the connection is up
//%     x: represents status of MCA
//%     x = 0 : Primary Schedule Operation
//%     x = 1 : Secondary Schedule Operation
//%     if b is false, then MCA is down and there is no connection
//============================================================================================

void GarfunkelSystemData::fromMcaDU41Reply ( bool b, int x )
{
    if ( x !=_opSchedule )
    {
        emit garfunkelOpScheduleStatus (x);
        _opSchedule = x;
    }
    if (b)
    {
        setConnectionUp ();
    }
    else
    {
        setConnectionDown ();
    }
}

//%============================================================================================
//%
//%   SLOT/function:
//%                 fromUiCommandDU42: DU:42 Signal from UI
//%
//%                 To Request Makedown Process: Active/Not Active
//%
//%============================================================================================
void GarfunkelSystemData::fromUiCommandDU42 ( )

{
    if(isConnected())
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU42 IS CONNECTED TRYING TO SEND COMMAND" ;
        emit( toMCACommandDU42());
    }
    else
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU42 IS NOT CONNECTED ";
        emit(ioConnectionDown());
    }
}



///============================================================================================
//%  SLOT: fromMcaDU42Reply
//%     If b is true, the connection is up
//%     x: represents Makedown process status of MCA
//%     x = 0 : Not Active
//%     x = 1 : Active
//%     if b is false, then MCA is down and there is no connection
//============================================================================================

void GarfunkelSystemData::fromMcaDU42Reply ( bool b, int x )
{
    if ( x !=_makeDownStatus )
    {
        emit garfunkelMakeDownProcessActive (x);
        _makeDownStatus = x;
    }
    if (b)
    {
        setConnectionUp ();
    }
    else
    {
        setConnectionDown ();
    }
}


//%============================================================================================
//%
//%   SLOT/function:
//%                 fromUiCommandDU43: DU:43 Signal from UI
//%
//%                 To Request Dispense Active: Active/Not Active
//%
//%============================================================================================
void GarfunkelSystemData::fromUiCommandDU43 ( )

{
    if(isConnected())
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU43 IS CONNECTED TRYING TO SEND COMMAND" ;
        emit( toMCACommandDU43());
    }
    else
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU43 IS NOT CONNECTED ";
        emit(ioConnectionDown());
    }
}



///============================================================================================
//%  SLOT: fromMcaDU43Reply
//%     If b is true, the connection is up
//%     x: represents Dispense status of MCA
//%     x = 0 : Not Active
//%     x = 1 : Active
//%     if b is false, then MCA is down and there is no connection
//============================================================================================

void GarfunkelSystemData::fromMcaDU43Reply ( bool b, int x )
{
    if ( x !=_dispenseActiveState )
    {
        emit garfunkelDispenseActive (x);
        _dispenseActiveState = x;
    }
    if (b)
    {
        setConnectionUp ();
    }
    else
    {
        setConnectionDown ();
    }
}



//%============================================================================================
//%
//%   SLOT/function:
//%                 fromUiCommandDU44: DU:44 Signal from UI
//%
//%                 To Request Layup Mode Status: Disabled/Enabled
//%
//%============================================================================================
void GarfunkelSystemData::fromUiCommandDU44 ( )

{
    if(isConnected())
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU44 IS CONNECTED TRYING TO SEND COMMAND" ;
        emit( toMCACommandDU44());
    }
    else
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU44 IS NOT CONNECTED ";
        emit(ioConnectionDown());
    }
}



///============================================================================================
//%  SLOT: fromMcaDU44Reply
//%     If b is true, the connection is up
//%     x: represents Layup Mode Status of MCA
//%     x = 0 : LayUp Mode Disabled
//%     x = 1 : layupMode Enabled
//%     if b is false, then MCA is down and there is no connection
//============================================================================================

void GarfunkelSystemData::fromMcaDU44Reply ( bool b, int x )
{
    if ( x !=_layupModeStatus )
    {
        emit garfunkelLayupModeStatus (x);
        _layupModeStatus = x;
    }
    if (b)
    {
        setConnectionUp ();
    }
    else
    {
        setConnectionDown ();
    }
}



//%============================================================================================
//%
//%   SLOT/function:
//%                 fromUiCommandDU45: DU:45 Signal from UI
//%
//%                 To Request Standby Mode Status: Disabled/Enabled
//%
//%============================================================================================
void GarfunkelSystemData::fromUiCommandDU45 ( )

{
    if(isConnected())
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU45 IS CONNECTED TRYING TO SEND COMMAND" ;
        emit( toMCACommandDU45());
    }
    else
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU45 IS NOT CONNECTED ";
        emit(ioConnectionDown());
    }
}



///============================================================================================
//%  SLOT: fromMcaDU45Reply
//%     If b is true, the connection is up
//%     x: represents Standby Mode Status of MCA
//%     x = 0 : Standby Mode Disabled
//%     x = 1 : Standby Mode Enabled
//%     if b is false, then MCA is down and there is no connection
//============================================================================================

void GarfunkelSystemData::fromMcaDU45Reply ( bool b, int x )
{
    if ( x !=_standByModeStatus )
    {
        emit garfunkelStandbyModeStatus (x);
        _standByModeStatus = x;
    }
    if (b)
    {
        setConnectionUp ();
    }
    else
    {
        setConnectionDown ();
    }
}




//%============================================================================================
//%
//%   SLOT/function:
//%                 fromUiCommandDU47: DU:47 Signal from UI
//%
//%                 To Request Active Color Status: There are Many
//%
//%============================================================================================
void GarfunkelSystemData::fromUiCommandDU47 ( )

{
    if(isConnected())
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU47 IS CONNECTED TRYING TO SEND COMMAND" ;
        emit( toMCACommandDU47());
    }
    else
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU47 IS NOT CONNECTED ";
        emit(ioConnectionDown());
    }
}



///============================================================================================
//%  SLOT: fromMcaDU47Reply
//%     If b is true, the connection is up
//%     x: represents Active Color Status of MCA
//%     x = Active Color Status
//%     Values of X TBD: there are many colors
//%     if b is false, then MCA is down and there is no connection
//============================================================================================

void GarfunkelSystemData::fromMcaDU47Reply ( bool b, int x )
{
    if ( x !=_activeColorStatus )
    {
        emit garfunkelActiveColorStatus (x);
        _activeColorStatus = x;
    }
    if (b)
    {
        setConnectionUp ();
    }
    else
    {
        setConnectionDown ();
    }
}



//%============================================================================================
//%
//%   SLOT/function:
//%                 fromUiCommandDU84: DU:84 Signal from UI
//%
//%                 To Request Garfunkel Software Version Number
//%
//%============================================================================================
void GarfunkelSystemData::fromUiCommandDU84 ( )

{
    if(isConnected())
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU84 IS CONNECTED TRYING TO SEND COMMAND" ;
        emit( toMCACommandDU84());
    }
    else
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU84 IS NOT CONNECTED ";
        emit(ioConnectionDown());
    }
}



///============================================================================================
//%  SLOT: fromMcaDU84Reply
//%     If b is true, the connection is up
//%     str: String represents Garfunkel Software Version Number
//%     str = A.B.C
//%     if b is false, then MCA is down and there is no connection
//============================================================================================

void GarfunkelSystemData::fromMcaDU84Reply ( bool b, QString str)
{
        qDebug() << "Garfunkel Software Version is:\t" << str ;
        emit garfunkelSoftwareVersion (str);

    if (b)
    {
        setConnectionUp ();
    }
    else
    {
        setConnectionDown ();
    }
}



//%============================================================================================
//%
//%   SLOT/function:
//%                 fromUiCommandDU85: DU:85 Signal from UI
//%
//%                 To Request Smart Simon I Board DI String( Firmware Version + Serial Number)
//%
//%============================================================================================
void GarfunkelSystemData::fromUiCommandDU85 ( )

{
    if(isConnected())
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU85 IS CONNECTED TRYING TO SEND COMMAND" ;
        emit( toMCACommandDU85());
    }
    else
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU85 IS NOT CONNECTED ";
        emit(ioConnectionDown());
    }
}



///============================================================================================
//%  SLOT: fromMcaDU85Reply
//%     If b is true, the connection is up
//%     sstr: String represents Smart Simon IO Board DI String
//%     sstr = IOBoard, Rev A.B.C, ZZZZZZZ
//%     if b is false, then MCA is down and there is no connection
//============================================================================================

void GarfunkelSystemData::fromMcaDU85Reply ( bool b, QString sstr)
{
        qDebug() << "Smart Simon IO Board DI String is:\t" << sstr; 
        emit sSimonIOBoardFirmwareVersion (sstr);

    if (b)
    {
        setConnectionUp ();
    }
    else
    {
        setConnectionDown ();
    }
}



//%============================================================================================
//%
//%   SLOT/function:
//%                 fromUiCommandDU86: DU:86 Signal from UI
//%
//%                 To Request  Garfunkel I Board DI String( Firmware Version + Serial Number)
//%
//%============================================================================================
void GarfunkelSystemData::fromUiCommandDU86 ( )

{
    if(isConnected())
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU86 IS CONNECTED TRYING TO SEND COMMAND" ;
        emit( toMCACommandDU86());
    }
    else
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandDU86 IS NOT CONNECTED ";
        emit(ioConnectionDown());
    }
}



///============================================================================================
//%  SLOT: fromMcaDU86Reply
//%     If b is true, the connection is up
//%     sstr: String represents Garfunkel IO Board DI String
//%     sstr = IOBoard, Rev A.B.C, ZZZZZZZ
//%     if b is false, then MCA is down and there is no connection
//============================================================================================

void GarfunkelSystemData::fromMcaDU86Reply ( bool b, QString gstr)
{
        qDebug() << "Garfunkel IO Board DI String is:\t" << gstr; 
        emit garfunkelIOBoardFirmwareVersion (gstr);

    if (b)
    {
        setConnectionUp ();
    }
    else
    {
        setConnectionDown ();
    }
}


//%============================================================================================
//%
//%   SLOT fromUiCommandSU50 receiving Signal from UI
//%
//%   Enable diagnostics mode for next SU51 command.
//%
//%============================================================================================
void GarfunkelSystemData::fromUiCommandSU50(int x)
{
    if(isConnected())
    {
	//qDebug() << "GarfunkelSystemData::fromUiCommandSU50 IS CONNECTED TRYING TO SEND COMMAND x = " << x;
        emit(toMCACommandSU50(x));
    }
    else
    {
        qDebug() << "GarfunkelSystemData::fromUiCommandSU50 IS NOT CONNECTED ";
        emit(toUiSU50Error(0));
        emit(ioConnectionDown());
    }
}


//%============================================================================================
//%
//%   SLOT fromUiCommandSU51 : Receives SU51:X:Y Command Signal from UI
//%
//%   This command is for Activating/DeActivating diagnostics operations
//%
//%============================================================================================
void GarfunkelSystemData::fromUiCommandSU51(int x,int y)
{
    if(isConnected())
    {
       qDebug() << " GarfunkelSystemData::fromUiCommandSU51 IS CONNECTED TRYING TO SEND COMMAND x = " << x  << " y = "  << y;
        emit(toMCACommandSU51(x,y));
    }
    else
    {
        qDebug() << " GarfunkelSystemData::fromUiCommandSU51 IS NOT CONNECTED ";
        emit(toUiSU51Error(1));  //% Use Unspecified Error for now
        emit(ioConnectionDown());
    }
}



//%============================================================================================
//%
//%  SLOT  toUiCommandSU51 Receiving Signal from from MCA
//%
//%   This command is sent from MCA to UI  with Y = 2 for operation completion of a diagnostic.
//%
//%============================================================================================
 void GarfunkelSystemData::toUiCommandSU51 ( int x, int y)
 {
      qDebug() << "GarfunkelSystemData::toUiCommandSU51 x= " << x << " y = " << y ;
            if(y == 2)
            {
                emit(diagOpComplete() ); //% Inform DiagContext we received SU:51:X:Y=2 meanning diagnostic Operation is Done!!
            }

 }



//%============================================================================================
//%
//%  SLOT  toUiCommandSU65 Receiving Total Time & Delay Time Signal from from MCA
//%
//%   This command is sent from MCA to UI from MCA for Total Time & Delay timer for diagnostic.
//%   SU:65:A:B, A = Total Time
//%              B = Delay Timer
//%============================================================================================
 void GarfunkelSystemData::toUiCommandSU65 ( int a, int b)  
 {

 	switch( _timerState)
 	{
 		case DiagTimerState:
 		   {
   			qDebug() << "GarfunkelSystemData::toUiCommandSU65 a= " << a << " b= " << b ;        
            emit ( diagDelayTimerEvent(a, b) );//% Signal UI of Total Timer & Delay Timer values received from MCA SU:65:A:B
           } 
        break;

        case UnknownTimerState:   
          qDebug() <<  "GarfunkelSystemData::toUiCommandSU65 UnknownTimerState";  
        default:
        
        break;  
	}
 }



//%======================================================================================
//%
//%   SLOT   toUiCommandSU52
//%   Receives Diagnostic Updated Data from MCA and sents Data to UI
//%
//======================================================================================
void GarfunkelSystemData::toUiCommandSU52(int a, int b, int c, float d, float e)
{
    //qDebug() << " GarfunkelSystemData::toUiCommandSU52) a = " << a << " b = " << b << " c = " << c <<" d = "<< d <<" e ="<< e;
    emit diagDataUpdated (a, b, c, d, e );
}


//%======================================================================================
//%
//%   SLOT   toUiCommandSU53 Receiving  Internal Error /Diagnostic Failed Operation n sending it to UI
//%          Command is SU:53 in documentation ( No X, correct?)
//%
//%======================================================================================
void GarfunkelSystemData::toUiCommandSU53()
{
    //qDebug() << "GarfunkelSystemData::toUiCommandSU53  ERROR"  ;
    emit internalErrorEvent();
}



//%======================================================================================
//%
//%   SLOT   fromMcaSU50ReplyOK()
//%
//%======================================================================================
void GarfunkelSystemData::fromMcaSU50ReplyOK(int z)
{
    if(1 == z) //% Returns z = 1, I sent Enable Diagnostics from UI using fromUiCommandSU50(1)
    {
        //qDebug() << "GarfunkelSystemData::fromMcaSU50ReplyOK z = " << z;
        _timerState = DiagTimerState;
        emit toUiSU50Reply(z); //%Signal to Enable Entire Diagnostic Operation
    }
    else
    {
        _timerState = UnknownTimerState;
    }
}


//%======================================================================================
//%
//%   SLOT   fromMcaSU51ReplyOK()
//%
//%======================================================================================
void GarfunkelSystemData::fromMcaSU51ReplyOK(int z)
{
    //qDebug() << "GarfunkelSystemData::fromMcaSU51ReplyOK z = " << z;
    emit toUiSU51Reply(z); //% Signal to Start Valve Diagnostic Operation
}


//%======================================================================================
//%
//%   SLOT   fromMcaSU50Error(int)
//%
//%======================================================================================
void GarfunkelSystemData::fromMcaSU50Error(int x)
{
    //Q_UNUSED(x); //% Neglecting SU50 Error for Now!!
    //qDebug() << "GarfunkelSystemData::fromMcaSU50Error(int x):  SEE fromMcaSU50Error = " << x;
    emit toUiSU50Error(x);
}


//%======================================================================================
//%
//%   SLOT   fromMcaSU51Error(int)
//%
//%======================================================================================
void GarfunkelSystemData::fromMcaSU51Error(int x)
{
    //qDebug() << "GarfunkelSystemData::fromMcaSU51Error(int x):  SEE fromMcaSU51Error = " << x;
    emit toUiSU51Error(x);
}








