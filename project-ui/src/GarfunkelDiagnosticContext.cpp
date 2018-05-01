#include <QDebug>
#include <QtGui>
#include <QtDeclarative>

//Include Custom Classes
#include "GarfunkelDiagnosticContext.h"
#include "GarfunkelDB.h"
#include "garfunkelresourcestrings.h"

#include "GarfunkelSystemData.h"

//% DataBase talk Constructors :
GarfunkelDiagnosticContext::GarfunkelDiagnosticContext ( GarfunkelDB *gdb, GarfunkelLocalizationMgr2 *GarfunkelLM, QDeclarativeContext *gcontext, QObject *parent) :
  QObject (parent),                                                     
 _gDB (gdb),
 _GarfunkelLM (GarfunkelLM), 
 _context (gcontext) 
 
{

   //% Now Initialize Stuff Here!!

//}

//% Constructors: Talk to GarfunkelSystemData only
//GarfunkelDiagnosticContext::GarfunkelDiagnosticContext (QDeclarativeContext *context, QObject *parent) :
//                                                         _context (context), QObject (parent)
//{

    //% Now Initialize Stuff Here!!
    _blank = "";
    _diagInit();  //% initialise diagnostics!

}

GarfunkelDiagnosticContext::~GarfunkelDiagnosticContext()
{
    //%Empty Destructor
}


//% Init communication of this class & GarfunkelSystemData  class
void GarfunkelDiagnosticContext::_diagInit()
{

	GarfunkelSystemData *sdo = GarfunkelSystemData::getInstancePtr();
 
    //% get Signals from GarfunkelSystemData; Testing!
    connect(sdo, SIGNAL(toUiSU50Reply(int)), this, SLOT(diagOpStarted(int)),Qt::UniqueConnection );
    connect(sdo, SIGNAL(toUiSU50Error(int)), this, SLOT(diagOpFailed(int)),Qt::UniqueConnection );
    connect(sdo, SIGNAL(toUiSU51Reply(int)), this, SLOT(valveDiagOpStarted(int)),Qt::UniqueConnection );
    connect(sdo, SIGNAL(toUiSU51Error(int)), this, SLOT(diagOpFailed(int)),Qt::UniqueConnection );
   
    //% Get Delay Timer/ Total Time from MCA
    connect(sdo, SIGNAL(diagDelayTimerEvent(int,int)), this, SLOT(diagOperationTimer(int,int)),Qt::UniqueConnection );
    //% get Test Results command from MCA through GarfunkelSystemData
    //% Total Time, Timer, Pressure Switch Status, Temperature(F), Conductivity(uSiemens) 
    connect(sdo, SIGNAL(diagDataUpdated(int,int, int, float,float )), this, SLOT(diagDataUpdated(int,int, int, float,float)),Qt::UniqueConnection );
    connect(sdo, SIGNAL(diagOpComplete()), this, SLOT(diagOpComplete()),Qt::UniqueConnection );
    
    connect(sdo, SIGNAL(internalErrorEvent()), this, SLOT(internalErrorEvent()));

    //%  exchange signals within self
    connect(this, SIGNAL(diagnosticsTestRequestChanged()), this, SLOT(diagnosticsTestRequestChangedHandler()),Qt::UniqueConnection ); //% Handles Diagnostic test Request
    connect(this, SIGNAL(valveDiagTestRequestChanged()), this, SLOT(valveDiagTestRequestChangedHandler()),Qt::UniqueConnection ); //% Handles Valve Diagnostic Test Request

    //% No need for strings communication now!
    //connect(_AquanomicsLM, SIGNAL(localizedStringsChanged()), this, SLOT(_stringInit()));
  
    _key1Enabled   = true;
    _key2Enabled   = true;
    _key3Enabled   = true;
    _key4Enabled   = true;


    _isInternalErrorActive  = false;
    _valveDiagMode          = false;

    _diagMode               = false; 

    _diagnosticsTestStartFlag = false; //Request Diagnostics Start Only when in Diagnostic Mode

    _valveDiagTestStartFlag      = false; //% Request Valve Test Start Only when in Diagnostic Mode  
   
    //_isDiagnosticTest        = false; //% Will Change Buttons once we start Diagnostics
    _isValveTest             = false; //% Will change Buttons Once we start valve Diagostics Test
    //
    //% Buttons Take their Normal Images
    //
    _button1String = "";
    _button2String = "";
    _button3String = "";
    _button4String = "";
 
    //
    //% Values/Strings to Display
    //
    _valveId    = -1; //% set to undefined Valve Type
    _valveWaterTemp = 32; //% st to larg number for now
    _valveWaterConductivity = 00; //% set to large value
    _totalTime  = 0; //% defualt is 10 secs
    _valveDelayTimer  = 0; //%Sent every second to UI by MCA
    _valveTotalTime  = 0; //% defualt is 10 secs
    _valveTimer      = -1; //%Sent every second to UI from MCA
    _valveWaterPressureSS = -1; //% sent to UI from MCA
     
    //% Initialise strings from ResourceStrings( either file or DB)!
    _stringInit(); 

    //% Set Initials
    setValveTestString (_blank);
    setValveStateString (_dbValveCLOSEStateString); //% Valves are closed Untill you Request Open
    
    setValveWaterTempPrefixString (_dbTempSuffixString);
    setValveWaterTempSuffixString (_dbTempSuffixString);

    setValveWaterConductivityPrefixString (_dbConductivityPrefixString);
    setValveWaterConductivitySuffixString (_dbConductivitySuffixString);

    setValveTimePrefixString (_dbTimePrefixString);
    setValveTimeSuffixString (_dbTimeSuffixString);

    //% At The Begining Of Diagnotcis Mode
    //We have to be able to still select What kind of Diagnostics 
    //% So Keys are as they are supposed to be
    setButtonOneString(_dbHomeString); 
    setButtonTwoString(_dbBackString);
    setButtonThreeString(_dbPressOnString); // Use to Enable Diagnostics
    setButtonFourString(_dbHelpString);
     
    /*
    _keyUpEnabled  = true;
    _keyDownEnabled = true;
    _keyLeftEnabled = true;
    _keyRightEnabled = true;
    _keyEnterEnabled = true;
    */
}

//%=============================================================================
//%
//%  SLOT  _stringInit ()
//%         Initialised all strings displayed in screen during Diagnostic Operation Complete
//%         infuture will be initialised from Resource Strings
//%
//%=============================================================================
 void GarfunkelDiagnosticContext::_stringInit()
 {
   //Initalised ll strings to use
   //% This shoukd be done from the LocalizationManagger from Database or Flat file
   //% for empty strings
    _dbTestPassedString       = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::Passed); // "Passed";
    _dbTestFailedString       = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::Failed); // "Failed";
    _dbTestInProgressString   = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::InProgress);  //"In Progress";
    _dbTestFailedStringReason = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::ProtocolError);//"Protocol Error" //SU:53 Error";
    _dbErrorString            = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::InternalError); //"Internal Error"; 
    
    _dbButtonOffString        = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::Off);  // "Off"; database localized label for OFF button
    _dbButtonOnString         = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::On); //"On";   // database localized label for ON button

    _dbValveIdString          = " "; // Default Valve ID = -1 //Need String to Int conversion
    _dbTempString        = "00"; 
    _dbTempPrefixString  = " ";
    _dbTempSuffixString  = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::F); //"F";  

    _dbConductivity        = "00"; 
    _dbConductivityPrefixString = " "; // database localized label in front of time value
    _dbConductivitySuffixString = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::Us) + "/" +_GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::Cm); //"uS/cm";

    _dbTimerString           = "00"; //%Default Delay Timer from DataBase?
    _dbTTimeString           = "00"; //%Default Total Time from DataBase?
    _dbTimePrefixString         = " "; // database localized label in front of time value
    _dbTimeSuffixString         = " "; // database localized units label (like 'seconds') after time value

    _dbValveOPENStateString     = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::Open); //"Open";
    _dbValveCLOSEStateString    = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::Close); //"Close";
    _dbTestString               = " "; 
    _dbToggleStatusString       = " ";
    _dbIOFailedString           = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::IoError); //"IO Error";
    _dbDiagOpeFailedString      = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::InternalError); //"Internal Error";
    _dbValveDiagFailedString    = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::ProtocolError); //"SU51: ERROR";

    
    _dbPressOffString           = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::Off); //"Off"; 
    _dbPressOnString            = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::On);// "On";  
    _dbHomeString               = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::Home); //"Home"; 
    _dbBackString               = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::Back); //"Back"; //% Press Back
    _dbHelpString               = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::Help); //"Help"; //% Press Help
    _fString                    = _dbTestFailedString + "/" + _dbTestFailedStringReason;
    _dbPressCANCELString        = _GarfunkelLM->GetTMLanguageStringByID(GarfunkelResourceStrings::Cancel); //"Cancel"; //% Press CANCEL to stop test

 }


//%=============================================================================
//%
//%  SLOT  diagOpFailed if:
//%         SU50 REPLY to UI with ERROR  //i.e Unable to Enable Diagnostics( 0 = No I/O Connection
//%                                                                          1 =  ERR1 Unspecified )
//%         SU51 RREPLY to UI with ERROR // i.e Unable to request Diagnostics Operation (2 = No I/O Connection
//%                                                                                     (3 = "ERR1" from MCA )
//%         Note: keys are enabled/disabled in diagnosticTestRequestChangedHandler & valveTestRequestChangedHandler 
//%=============================================================================
void GarfunkelDiagnosticContext::diagOpFailed(int z)
{
    qDebug() << "GarfunkelDiagnosticContext::diagOpFailed() z ="<<z;
    // Terrible Error!!!
    _valveDiagTestStartFlag = false;  // set again to true from UI so we can re-run diagnostics
    _diagMode = true;  // But you are still in diagnostic Mode!!!
     _valveDiagMode = true; // You are also still in Valve Diagnostic Mode!!
     //% Diagnostic  test
    switch(z)
    {
        case 0: //% Meaning toUiSU50Error(0)  SU50 No I/O Connection
     
            qDebug() << "SU50Error(0). NO I/O Connection, Re-Enable ALL Diagnostics Mode";
            //% Retry Enabling Diagnostics Mode again 
            //% These F1-F4 Button Strings are Images in Actual Sense
            setButtonOneString(_dbHomeString); 
            setButtonTwoString(_dbBackString);
            setButtonThreeString(_blank);
            setButtonFourString(_dbHelpString);
           
            setKey1Enabled(true);
            setKey2Enabled(true);
            setKey3Enabled(false); //useless key
            setKey4Enabled(true);    
            break; 

        case 1: //% Meaning toUiSU50Error(1)  SU50  ERR1 Unspecified from MCA  
            
            qDebug() << "SU50 ERR1. Unspecified ERROR, Re-Enable ALL Diagnostics Mode";
            //% Retry Enabling Diagnostics Mode again 
            //% These F1-F4 Button Strings are Images in Actual Sense
            setButtonOneString(_dbHomeString); 
            setButtonTwoString(_dbBackString);
            setButtonThreeString(_blank);
            setButtonFourString(_dbHelpString);
           
            setKey1Enabled(true);
            setKey2Enabled(true);
            setKey3Enabled(false); // useless Key
            setKey4Enabled(true);
            break; 

        case 2: //% Meaning toUiSU51Error(2)  SU51,  No I/O Connection
            
            qDebug() << "Probably Connection down, Re-enable PressOnButton Valve Diagnostics Test"; 
            setValveTestString (_dbIOFailedString); //set up error or connection down
            setValveStateString (_dbValveCLOSEStateString);
            setIsValveTest(false); //% Valve Diagnostic Test Failed//Allow for Reanabling with same F3 key       
            //% keys left Enabled to restarrt Diagnostics except help key, just to make it different while in Valve Diagnostics
            //% Retry Enabling Diagnostics Mode again 
            //% These F1-F4 Button Strings are Images in Actual Sense
            setButtonOneString(_blank); 
            setButtonTwoString(_blank);
            setButtonThreeString(_dbPressOnString);
            setButtonFourString(_blank); //% No Need for this Key as will be Use to Stop test Once Valve Diagnostics Test is Enabled
           
            setKey1Enabled(false);
            setKey2Enabled(false);
            setKey3Enabled(true);
            break; 

        case 3: //% Meaning toUiSU51Error(3)  SU51,  ERR1 Unspecified Error from MCA  
        
            qDebug() << "SU51:ERR1, Re-enable PressOnButton Valve Diagnostics Test"; 
            setValveTestString (_dbValveDiagFailedString); //set up error or connection down
            setValveStateString (_dbValveCLOSEStateString);
            //% keys left Enabled to restarrt Diagnostics except help key, just to make it different while in Valve Diagnostics
            //% Retry Enabling Diagnostics Mode again 
            setIsValveTest(false); //% Valve Diagnostic Test Failed//Allow for Reanabling with same F3 key       
           
           
            // THE CORRECT THING TO DO!!!
            //% These F1-F4 Button Strings are Images in Actual Sense
            setButtonOneString(_blank); 
            setButtonTwoString(_dbBackString);
            setButtonThreeString(_dbPressOnString);
            setButtonFourString(_blank); //% No Need for this Key as will be Use to Stop test Once Valve Diagnostics Test is Enabled
           
            setKey1Enabled(false);
            setKey2Enabled(true);
            setKey3Enabled(true);

            
            
            /*
            //% THE FALSE THING TO DO
              setButtonOneString(_dbHomeString); 
              setButtonTwoString(_dbBackString);
              setButtonThreeString(_dbPressOnString);
              //setButtonFourString(_blank); //% No Need for this Key as will be Use to Stop test Once Valve Diagnostics Test is Enabled
              setKey1Enabled(true);
              setKey2Enabled(true);
              setKey3Enabled(true);
            */ 
            break; 
    }


  
}

//%=============================================================================
//%
//%  SLOT   diagOpComplete
//%         SU51 from MCA  with Y == 2  Causes Diagnostic Operation Complete
//%
//%=============================================================================
void GarfunkelDiagnosticContext::diagOpComplete()
{
    qDebug() << "GarfunkelDiagnosticContext::diagOpComplete()";

    _valveDiagTestStartFlag = false; 
    //_isDiagnosticTest        = false;
    _isValveTest             = false;
 
    if(_isInternalErrorActive==true) //% SU53Error Internal Error
    {
        setValveTestString(_fString);
        setValveStateString (_dbValveOPENStateString);
    }
    else {
        setValveTestString(_dbTestPassedString);
        setValveStateString (_dbValveCLOSEStateString);
        }
        //% These F1-F4 Button Strings are Images in Actual Sense
        setButtonOneString(_blank); 
        setButtonTwoString(_dbBackString);
        setButtonThreeString(_dbPressOnString);
        setButtonFourString(_blank);
        //setIsValveTest (false); //can't we do it from the screen?

        qDebug() << "Setting Keys F2-F3 Enabled";
        //% Test Complete Re-enable all Keys
        setKey1Enabled(false);
        setKey2Enabled(true);
        setKey3Enabled(true);
        setKey4Enabled(false); // Really need help here?
        _isInternalErrorActive = false;

}


//%=============================================================================
//%
//%  SLOT   diagOpStarted Started
//%         SU50 REPLY from MCA  with z == 1,  which is Enabled Diagnostics from UI through: fromUiCommandSU50(1)
//%         Note: keys are enabled/disabled in diagnosticsTestRequestChangedHandler ()
//%=============================================================================
void GarfunkelDiagnosticContext::diagOpStarted(int z)
{
    qDebug() << "GarfunkelDiagnosticContext::diagOpStarted()";

        
        switch(z)
        {
             case 0: //% We are in Disabled Dignostics Mode, Return Bottons to we can Enable Diagnostics again 
                 // Reply from MCA: toUiSU50Reply(0) ==  0 =  MCA gave back same Disable Diagnostics We requested
                qDebug() << "GarfunkelDiagnosticContext::diagOpEnded ()";
                // set up  Back to press ON or Enable Diagnostics Mode
                //setIsDiagnosticTest(false); can't we do it from screen?     
                // Dianostics Mode Can be Re-enabled
                setKey1Enabled(true);
                setKey2Enabled(true);
                setKey3Enabled(false);
                //% These F1-F4 Button Strings are Images in Actual Sense
                setButtonOneString(_dbHomeString); 
                setButtonTwoString(_dbBackString);
                setButtonThreeString(_blank);

                qDebug() << "We are in Disabled Diagnostic Mode, Go Back to Enable Diagnostic Mode";
                break;

            case 1:  //% We are in Enabled Diagnostics Mode
                    // Reply from MCA: toUiSU50Reply(1) ==  1 = MCA Gave Back What I asked, so good!!

                // set up to Disabled Diagnostics Mode with either HOME/BACK   
                //setIsDiagnosticTest(true); can't we do it from screen? 
                //Enable All keys to Disable Diagnostic Mode
                setKey1Enabled(true);
                setKey2Enabled(true);
                setKey3Enabled(false); //% Useless button for now!!

                //% These F1-F4 Button Strings are Images in Actual Sense
                setButtonOneString(_dbHomeString); 
                setButtonTwoString(_dbBackString);
                setButtonThreeString(_blank);

                qDebug() << "We are in Enabled Diagnostic Mode";
                break;

        }
}


//%=============================================================================
//%
//%  SLOT    valveDiagOpStartedStarted
//%          SU51 REPLY from MCA :t oUiSU51Reply  with z == 0   
//%          which is Enabled Diagnostics from UI through: fromUiCommandSU51(1)
//%          Note: keys are enabled/disabled in valveDiagTestRequestChangedHandler 
//%=============================================================================
void GarfunkelDiagnosticContext::valveDiagOpStarted(int z)
{
    //qDebug() << "GarfunkelDiagnosticContext::valveDiagOpStarted() with z = " << z;
    
    
    if(true ==_diagMode) //Enabled Valve Diagnostics Only when in Diagnostics Mode
      {
         //% ow should the keys look like in Diagnostic Mode
        setIsValveTest (true); //can't we do it from the screen?
        setKey3Enabled(false); // Disable the key once diagnostic request is made

        if( true == _valveDiagTestStartFlag )
        {   
            
            if ( z == 0) 
            {
                //setIsValveTest (true); //can't we do it from the screen?
                qDebug() << "GarfunkelDiagnosticContext::valveDiagOpStarted() with z = " << z;


                 //% If Lid is Opened while Valve Diagnostic Operation is Ongoing!
                 if(_isInternalErrorActive==true) //% SU53Error Internal Error
                {
                    setValveTestString(_fString);
                    setValveStateString (_dbValveOPENStateString);

                    //% Set Up the keys to be able to Disable entire Diagnostics( Valves Diagnostics Operation & Diagnotiscs Mode)
                    setButtonOneString(_blank); 
                    setButtonTwoString(_dbBackString);  
                    setButtonThreeString(_blank);             
                    setButtonFourString(_blank);
                    //Lock all Keys Once Test Starts and Except F2 to go back!
                    setKey1Enabled(false);
                    setKey2Enabled(true);
                    //setKey3Enabled(false);
                    setKey4Enabled(false);
                    
                }
                else {

                        //% We are in Valve Diagnostics Test In Process
                        setValveTestString  (_dbTestInProgressString);
                        setValveStateString (_dbValveOPENStateString);
                          //% We have to select What kind of Diagnostics and then Select What Kind of Values so
                        //%Set up to Press OFF/CANCEL
                        setButtonOneString(_blank); 
                        setButtonTwoString(_blank);  
                        setButtonThreeString(_dbPressOffString);             
                        setButtonFourString(_blank);
                        //setButtonFourString(_dbPressOffString);
                        
                        //Lock all Keys Once Test Starts and Only Allow F4 to Stop Test
                        setKey1Enabled(false);
                        setKey2Enabled(false);
                        //setKey3Enabled(false);
                        setKey4Enabled(false);

                        _isInternalErrorActive = false;
                    } 
                //% We are in Valve Diagnostics Mode Enable Using same key to Switch Off Diagnotics

                //Inside here you have the 
                //% 1) Delay State (Waiting for CountDown Delay Timer to reach e.g 10s)
                //% 2) In Valve Test Operation
                //% 3) End of Operation
            }

        }

    }else //% Disable ALL keys? If you are not in Diagnostic Mode?
     {
        //% You shouldn't be able to do anything
        qDebug() << "Not inside Diagnostic Mode";
     }

}


 //%=========================================================================================
 //%
 //%    SLOT TO HANDLE Valve  Dignostic Test Request
 //%    valveDiagTestRequestChangedHandler ( )
 //%==========================================================================================
 void GarfunkelDiagnosticContext::valveDiagTestRequestChangedHandler ( )
 {
    if( true ==_diagMode )

       {

        if(true == _valveDiagTestStartFlag )
            {


            _valveDiagMode = true;
            _isValveTest = true;

            qDebug() << "GarfunkelDiagnosticContext::valveDiagTestRequestChangedHandler TRUE";
            //PumpInfoModel& pim = PumpInfoModel::Instance();
            //int pumpId = pim.currentIndex();

            //% How do I get Valve ID from UI now? 
            GarfunkelSystemData& sdo = GarfunkelSystemData::Instance();
        
            //% Switch to the correct Valve ID
            switch(_valveId)
            {
                case 0: //%S Product Valve
                    sdo.fromUiCommandSU51(0, 1); //% Activate Diagnostic Operation = 1 (SU:51:0: 1)
                    break;

                case 1: //% P Product Valve
                    sdo.fromUiCommandSU51(1, 1); //% Activate Diagnostic Operation = 1 (SU:51:1: 1)
                    break; 

                case 2: //%Aquanomics Dilution Water Inlet
                    sdo.fromUiCommandSU51(2, 1); //% Activate Diagnostic Operation = 1 (SU:51:2: 1)
                    break;

                case 3: //% O1 Valve
                    sdo.fromUiCommandSU51(3, 1); //% Activate Diagnostic Operation = 1 (SU:51:3: 1)
                    break;

                case 4: //% O2 Valve
                    sdo.fromUiCommandSU51(4, 1); //% Activate Diagnostic Operation = 1 (SU:51:4: 1)
                    break;

                case 5: //%Drain Valve
                    sdo.fromUiCommandSU51(5, 1); //% Activate Diagnostic Operation = 1 (SU:51:5: 1)
                    break; 
            }
        
        }
        else
        {

            _valveDiagMode = true;
            _isValveTest = true;        
            qDebug() << "GarfunkelDiagnosticContext::valveDiagTestRequestChangedHandler FALSE";
            GarfunkelSystemData& sdo = GarfunkelSystemData::Instance();

            switch(_valveId)
            {
                case 0: //%S Product Valve   
                    sdo.fromUiCommandSU51(0, 0); //% DeActivate Diagnostic Operation = 0 (SU:51:0: 0)
                    break; 
                case 1: //% P Product Valve
                    sdo.fromUiCommandSU51(1, 0); //% DeActivate Diagnostic Operation = 0 (SU:51:1: 0)
                    break; 
                case 2: //% Aquanomics Dilution Water Inlet Valve
                    sdo.fromUiCommandSU51(2, 0); //% DeActivate Diagnostic Operation = 0 (SU:51:2: 0)
                    break; 
                case 3: //% O1 Valve
                    sdo.fromUiCommandSU51(3, 0); //% DeActivate Diagnostic Operation = 0 (SU:51:3: 0)
                    break; 
                case 4: //% O2 Valve
                    sdo.fromUiCommandSU51(4, 0); //% DeActivate Diagnostic Operation = 0 (SU:51:4: 0)
                    break; 
                case 5: //% Drain Valve
                    sdo.fromUiCommandSU51(5, 0); //% DeActivate Diagnostic Operation = 0 (SU:51:5: 0)
                    break; 
            }
            
        }

     }   


 }


//%==========================================================================================
//%
//%    SLOT    clearValveDiagnosticTest () 
 //%           Called on OnDestruction  //% Clear Test Values before New Test begins
//%
//%==========================================================================================

void GarfunkelDiagnosticContext::clearValveDiagnosticTest ()
{
   qDebug () << "GarfunkelDiagnosticContext::clearValveDiagnosticTest () called";
   //% Reset Initials
   _valveDiagMode = false; 
    _valveWaterTemp    = 0;
    _valveWaterConductivity = 0;
    _valveWaterPressureSS  = 0; 
    _valveDelayTimer = 0; 
    _valveTimer     = 0;
    _valveStateString  = "";
    _valveTestString   = ""; 

}




//%==========================================================================================
//%
//%        SETTER FOR DIAGNOSTIC TEST REQUEST
//%
//%==========================================================================================
void GarfunkelDiagnosticContext::setDiagnosticsTestRequest (bool b)
{
   if(_diagnosticsTestStartFlag!= b)
    {
      _diagnosticsTestStartFlag = b;
      qDebug() << "diagnosticsTestRequestChanged () to " <<  b;
      emit(diagnosticsTestRequestChanged ());
    }

}



//%==========================================================================================
//%
//%      SLOT TO HANDLE Diagnostic Test Request
//%             diagnosticsTestRequestChangedHandler () 
//%
//%==========================================================================================
 void GarfunkelDiagnosticContext::diagnosticsTestRequestChangedHandler ()
{
  if(true ==_diagnosticsTestStartFlag )
  {
    _diagMode = true;

    GarfunkelSystemData& sdo = GarfunkelSystemData::Instance();
    sdo.fromUiCommandSU50(1); //% Enable Diagnostics Mode  SU:50:1
    qDebug () << "Diagnostic Mode Enabled";

  }else
  {
    _diagMode = true;

    GarfunkelSystemData& sdo = GarfunkelSystemData::Instance();
    sdo.fromUiCommandSU50(0);  //% DisAble Diagnostics Mode  SU:50:1
    qDebug () << "Diagnostic Mode Disabled";
   
  }


}



//%============================================================================
//%
//%  SLOT   internalErrorEvent
//%         Caused when MCA Sends SU53 to UI  
//%
//%============================================================================
void GarfunkelDiagnosticContext::internalErrorEvent()
{
     qDebug() << "GarfunkelDiagnosticContext::internalErrorEvent Received Error";
    //internal error for diagnostics
    _isInternalErrorActive = true;
}



//%============================================================================
//%
//%  SETTERS
//%
//%============================================================================



//%%=============================================================================
//%
//%  Q_PROPERTY  SETTER for key1Enabled
//%  
//%%=============================================================================
void GarfunkelDiagnosticContext::setKey1Enabled( bool flag)
{
    if(flag != _key1Enabled)
    {
        qDebug() << "_key1Enabled CHANGED to " << flag;
        _key1Enabled = flag;
        emit key1EnabledChanged();
    }
}
//%%=============================================================================
//%
//%  Q_PROPERTY  SETTER for key2Enabled
//%  
//%%=============================================================================
void GarfunkelDiagnosticContext::setKey2Enabled( bool flag)
{
    if(flag != _key2Enabled)
    {
         qDebug() << "_key2Enabled CHANGED to " << flag;
        _key2Enabled = flag;
        emit key2EnabledChanged();
    }
}
//%%=============================================================================
//%
//%  Q_PROPERTY  SETTER for key3Enabled
//%  
//%%=============================================================================
void GarfunkelDiagnosticContext::setKey3Enabled( bool flag)
{
    if(flag != _key3Enabled)
    {
         qDebug() << "_key3Enabled CHANGED to " << flag;
        _key3Enabled = flag;
        emit key3EnabledChanged();
    }
}

//%%=============================================================================
//%
//%  Q_PROPERTY  SETTER for key4Enabled
//%  
//%%=============================================================================
void GarfunkelDiagnosticContext::setKey4Enabled( bool flag)
{
    if(flag != _key4Enabled)
    {
         qDebug() << "_key4Enabled CHANGED to " << flag;
        _key4Enabled = flag;
        emit key4EnabledChanged();
    }
}
//%%=============================================================================
//
//  Q_PROPERTY  SETTER for Button strings
//  
//%%=============================================================================
void GarfunkelDiagnosticContext::setButtonOneString( QString& s)
{
    _button1String = "";
    _button1String += s;
    emit buttonOneStringChanged();
}
void GarfunkelDiagnosticContext::setButtonTwoString( QString& s)
{
    _button2String = "";
    _button2String += s;
    emit buttonTwoStringChanged();
}
void GarfunkelDiagnosticContext::setButtonThreeString( QString& s)
{
    _button3String = "";
    _button3String += s;
    emit buttonThreeStringChanged();
}
void GarfunkelDiagnosticContext::setButtonFourString( QString& s)
{
    _button4String = "";
    _button4String += s;
    emit buttonFourStringChanged();
}


//%====================================================================
//%
//% SETTTER Valve Properties
//%
//%====================================================================


//%%=================================
//%         Temperature
//%==================================
//% Valve Temperature
void GarfunkelDiagnosticContext::setValveWaterTemp ( float &temperature)
{
    if (_valveWaterTemp != temperature)
	{
           _valveWaterTemp = temperature;
           qDebug () << "valveWaterTempChanged () " << temperature; 
           emit valveWaterTempChanged ();
	}
     else
	{
	   qDebug () <<"valveWater Temp Unchnaged";
	}

}

//%Valve Water Temperature Prefix String
void GarfunkelDiagnosticContext::setValveWaterTempPrefixString (QString &s)
{     
    _valveWaterTempPrefixString = s.toAscii();
    emit valveWaterTempPrefixStringChanged ();
}

//%Valve Water Temperature Suffix String
void GarfunkelDiagnosticContext::setValveWaterTempSuffixString (QString &s)
{     
    _valveWaterTempSuffixString = s.toAscii();
    emit valveWaterTempSuffixStringChanged ();
}

//%%=================================
//%       Water Conductivity
//%==================================
//% Water Cnductivity
void GarfunkelDiagnosticContext::setValveWaterConductivity ( float &cond)
{
    if(_valveWaterConductivity != cond)
	{
          _valveWaterConductivity = cond;
          qDebug () << "valveWaterConductivityChanged () "  << cond; 
          emit valveWaterConductivityChanged ();
	}
	else {
                qDebug ()  << "Valve Water conductivity unchanged!";
	}
}
//% Water Conductivity Prefix String
void GarfunkelDiagnosticContext::setValveWaterConductivityPrefixString (QString &s)
{     
    _valveWaterConductivityPrefixString = s.toAscii();
    emit valveWaterConductivityPrefixStringChanged ();
}

//% Water Conductivity Suffix String
void GarfunkelDiagnosticContext::setValveWaterConductivitySuffixString (QString &s)
{
    _valveWaterConductivitySuffixString = s.toAscii();
    emit valveWaterConductivitySuffixStringChanged ();
}

//%%=================================================
//%     Valve Water Pressure Switch Status
//%==================================================
//% Valve Water Pressure Switch Status
void GarfunkelDiagnosticContext::setValveWaterPressureSwitchStatus(int &status)
{
   if(_valveWaterPressureSS != status)
     {
      _valveWaterPressureSS = status; 
      qDebug () << "valveWaterPressureSwitchStatusChanged () " << status;
      emit valveWaterPressureSwitchStatusChanged (); 
   }else
       {
       qDebug () <<"valve Watwer Pressure Switch status Unchanged!";
    }	
}

//%%=================================================
//%     Valve Delay Timer
//%==================================================

void GarfunkelDiagnosticContext::setValveDelayTimer (int& dtimer)
{
    if(_valveDelayTimer != dtimer)
      {
      
        _valveDelayTimer = dtimer;
              
        qDebug () << "valveDelayTimerChanged () " << dtimer;
        emit valveDelayTimerChanged (); 
     
      }else 
	{
         qDebug () <<"Delay Timer Unchanged!!"; 
	}	
}

//%%=================================================
//%   Total Time SU:65:A 
//%============================================

void GarfunkelDiagnosticContext::setTotalTime (int &ttA)
{
    if(_totalTime != ttA)
      {
       _totalTime = ttA;   
       //qDebug () << "totalTimeChanged () " << ttA;
       emit totalTimeChanged ();
 
     } else
	{
         qDebug () << " Total Timer Unchanged!!";
	}	 
}

//%%=================================================
//%     Valve Total Time SU:52:A 
//%============================================

void GarfunkelDiagnosticContext::setValveTotalTime (int &tt)
{
    if(_valveTotalTime != tt)
       {
        _valveTotalTime = tt; 
    	//qDebug () << "valveTotalTimeChanged () " << tt;
        emit valveTotalTimeChanged ();
     
    }else
 	{ 
         qDebug () << "Valve Diganostics Total Timer Unchanged!!"; 
	} 
}

//%%=================================================
//%     Valve Spray Timer
//%==================================================
void GarfunkelDiagnosticContext::setValveTimer (int& timer)
{
    if(_valveTimer != timer)
      {
        _valveTimer = timer; 
        qDebug () << "valveTimerChanged () " << timer;
        emit ( valveTimerChanged () );
      }else
	{
          qDebug () << "Timer Unchanged!!"; 
	} 
}

//%Valve Time Prefix String
void GarfunkelDiagnosticContext::setValveTimePrefixString (QString &s)
{     
    _valveTimePrefixString = s.toAscii();
    emit valveTimePrefixStringChanged ();
}

//%Valve Time Suffix String
void GarfunkelDiagnosticContext::setValveTimeSuffixString (QString &s)
{     
    _valveTimeSuffixString = s.toAscii();
    emit valveTimeSuffixStringChanged ();
}


//%=============================================================================
//%
//%  Q_PROPERTY  SETTER for Valve Diagnostic Test & Valve State
//%  
//%=============================================================================

//%% Valve Test Status String
void GarfunkelDiagnosticContext::setValveTestString(QString& s)
{
    _valveTestString = s;
    emit valveTestStringChanged ();
}

//% Valve State String
void GarfunkelDiagnosticContext::setValveStateString (QString& s)
{
    _valveStateString = s;
    emit valveStateStringChanged ();
}






//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//% SETTER FOR VALVE ID
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void GarfunkelDiagnosticContext::setValveId (int& Id)
{
   if(_valveId != Id)
     {
      _valveId = Id;
      qDebug() << "valveIdChanged to " <<  Id;
      emit (valveIdChanged ());
     
     }else
     	{
 	  qDebug () << " Valve Id Unchanged";
	}

     
}



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%=====================================
//% SETTER FOR VALVE DIAGNOSTIC TEST REQUEST
//%=====================================
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 void GarfunkelDiagnosticContext::setValveDiagTestRequest (bool b )
 {

   if(_valveDiagTestStartFlag!= b)
    {
        _valveDiagTestStartFlag = b;
        qDebug() << "valveDiagTestRequestChanged to " <<  b;
        emit(valveDiagTestRequestChanged ());
    }

 }


//%%=============================================================================
//%
//%  Q_PROPERTY  SETTER for setIsValveTest
//%  
//%%=============================================================================
void GarfunkelDiagnosticContext::setIsValveTest( bool flag)
{
    if(flag != _isValveTest)
    {
         qDebug() << "_isValveTest CHANGED to " << flag;
        _isValveTest = flag;
        emit isValveTestChanged ();
    }
}






//%===========================================================================
//%
//%  MORE SLOTS 
//%
//%===========================================================================

//%=============================================================================
//%
//%     SLOT: From MCA SU:65:A:B Command 
//%          for  A: TotalTime
//%               B: Delay Timer
//%============================================================================= 
 void GarfunkelDiagnosticContext::diagOperationTimer (int vTotalTime, int vDelayTimer )
 {
   //% Update Total Timer/Delay Timer
    setTotalTime (vTotalTime);
    qDebug () << "Total Time  set to value from SU:65:A = " << vTotalTime ;
    setValveDelayTimer (vDelayTimer);
    qDebug () << "Delay Timer  set to value from SU:65:B = " << vDelayTimer;
 }


//%=============================================================================
//%
//%     SLOT: From MCA SU:52:A:B:C:D:E Command 
//%          for  A: TotalTime
//%               B: Timer
//%               C: Pressure Switch Status
//%               D: Temperature in Centigrade
//%               E: Conductivity in uSiemens/cm
//%=============================================================================
 void GarfunkelDiagnosticContext::diagDataUpdated (int vTT, int vTimer, int vPWstatus, float vTemp, float vCond )
 {
    //% Update Valve Data Infomation
    setValveTotalTime (vTT);
    //qDebug () << "Valve Total Time set to value from SU:52:A = " << vTT;

    setValveTimer (vTimer);
    //qDebug () << "Valve Timer  set to value  from SU:52:B = " << vTimer;

    setValveWaterPressureSwitchStatus (vPWstatus);
    //qDebug () << "Valve Water Pressure Switch Status  set to value  from SU:52:C = " << vPWstatus; 

    setValveWaterTemp (vTemp);
    //qDebug () << "Valve Temperature in Celsius set to value  from SU:52:D = " << vTemp;

    setValveWaterConductivity (vCond);
    //qDebug () << "Valve Conductivity in uSiemens/cm  set to value  from SU:52:E = " << vCond;

 }





//%% SOME NICE FUNCTIONS!!!
//=============================================================================
//
//  _makeSecondsString
//  Computes string representing time value to two digits precision
//
//=============================================================================
void GarfunkelDiagnosticContext::_makeSecondsString(int val, QString& target)
{
    QString buffer("");
    QTextStream s(&buffer);
    s.setFieldWidth(2);
    s.setPadChar(QChar(0x20));
    s << val;
    QString dest = *(s.string());
    target = "";
    target.append(dest);
}


//=============================================================================
//
//  _makePrompt
//  Utility for PromptString ? what about temp, pressure etc?
//  
//=============================================================================
void GarfunkelDiagnosticContext::_makePrompt(int val, QString& prefix, QString& suffix, QString& target)
{
    QString buffer("");
    QTextStream s(&buffer);
    s.setFieldWidth(2);
    s.setPadChar(QChar(0x20));
    s << val;
    QString seconds = *(s.string());
    target = "";
    target.append(prefix);
    target.append(" ");
    target.append(seconds);
    target.append(" ");
    target.append(suffix);
}


/*
//%============================================================================
//
//  SetIsDiagnosticsTest
//
//%============================================================================
void GarfunkelDiagnosticContext::setIsDiagnosticTest(bool b)
{
    if(_isDiagnosticTest!= b)
    {
        _isDiagnosticTest = b;
        qDebug() << "isDiagnosticTestChanged to " <<  b;
        emit isDiagnosticTestChanged();
    }
}
*/
