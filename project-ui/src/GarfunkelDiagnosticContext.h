#ifndef GARFUNKEL_DIAGNOSTIC_CONTEXT_H
#define GARFUNKEL_DIAGNOSTIC_CONTEXT_H

//% Get QtQuick ppties/methods 
#include <QObject> 
#include <QStringList> 
#include <QDeclarativeContext> 
#include <QAbstractListModel>   
#include <QTimer>  

//% Get private classes
#include "GarfunkelDB.h" 
#include "GarfunkelLocalizationManager.h" 

//%
//%  GarfunkelDiagnosticContext
//%   
//%  The GarfunkelDiagnosticContext class is an interface class with
//%  callable methods/properties which are made visible to the QML.
//%  This class makes possible the operations 
//%  presented in the Diagnostic Menu UI.
//%

class GarfunkelDiagnosticContext : public QObject
{
    Q_OBJECT // Letting Qt's Meta Object (MOC) know this Class Properties are acessible to QML/Other Classes

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% KEYS
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% Key flags to enabled/disabled  disable F1-F4 keys status dependent on State of Diagnostics
    Q_PROPERTY(bool key1Enabled READ getKey1Enabled WRITE setKey1Enabled NOTIFY key1EnabledChanged)
    Q_PROPERTY(bool key2Enabled READ getKey2Enabled WRITE setKey2Enabled NOTIFY key2EnabledChanged)
    Q_PROPERTY(bool key3Enabled READ getKey3Enabled WRITE setKey3Enabled NOTIFY key3EnabledChanged)
    Q_PROPERTY(bool key4Enabled READ getKey4Enabled WRITE setKey4Enabled NOTIFY key4EnabledChanged)

    //
    //% Button Strings( or Images) Appearing on F1-F4 Buttons depending on Diagnostic Test State
    //
    //% This is the string for button 1  LATER CHANGE TO IMAGE ( UI can't change Image on Button so no WRITE)
    //
    Q_PROPERTY(QString   buttonOneString  READ getButtonOneString  NOTIFY buttonOneStringChanged)
    //
    //% This is the string for button 2  LATER CHANGE TO IMAGE
    //
    Q_PROPERTY(QString   buttonTwoString  READ getButtonTwoString  NOTIFY buttonTwoStringChanged)
    //
    //% This is the string for button 3  LATER CHANGE TO IMAGE
    //
    Q_PROPERTY(QString   buttonThreeString  READ getButtonThreeString NOTIFY buttonThreeStringChanged)
    //
    //% This is the string for button 4  LATER CHANGE TO IMAGE
    //
    Q_PROPERTY(QString   buttonFourString  READ getButtonFourString  NOTIFY buttonFourStringChanged)
    //
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // % VALVES  Properties
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //%
    //% Select each Valve from UI through Valve Id to request Dianostics
    Q_PROPERTY(int valveId  READ getValveId  WRITE setValveId  NOTIFY valveIdChanged )
    //
    //% Temperature  presented in QML to display in either Celsius/Fahrenheit 
    //
    Q_PROPERTY(float valveWaterTemp     READ getValveWaterTemp     NOTIFY valveWaterTempChanged)
    //
    //% Temperature Prefix string if needed
    //
    Q_PROPERTY(QString valveWaterTempPrefixString    READ getValveWaterTempPrefixString     NOTIFY valveWaterTempPrefixStringChanged)
    //
    //% Temperature Suffix String if needed e.g 2 "^o C" or " F" etc
    //
    Q_PROPERTY(QString valveWaterTempSuffixString     READ getValveWaterTempSuffixString      NOTIFY valveWaterTempSuffixStringChanged)
    //
    //% Water Conductivity string presented in QML to display Conductivity 
    //
    Q_PROPERTY(float valveWaterConductivity     READ getValveWaterConductivity      NOTIFY valveWaterConductivityChanged)
    //
    //% Conductivity Prefix string if needed
    //
    Q_PROPERTY(QString valveWaterConductivityPrefixString     READ getValveWaterConductivityPrefixString        NOTIFY valveWaterConductivityPrefixStringChanged)
    //
    //% Conductivity Suffix String if needed e.g units? etc
    //
    Q_PROPERTY(QString valveWaterConductivitySuffixString     READ getValveWaterConductivitySuffixString        NOTIFY valveWaterConductivitySuffixStringChanged)
    //
    //% Display( QML Accessible) Water Pressure Switch Status  "OPEN" / "CLOSED" default string is CLOSED
    //
    //%
    //% Valve Water Pressure Switch Status Text String,  OPEN = 1 , CLOSE = 0
    Q_PROPERTY(int valveWaterPressureSwitchStatus     READ getValveWaterPressureSwitchStatus        NOTIFY valveWaterPressureSwitchStatusChanged)
    //
    //
    //% Valve Total Time( 10 or 3 seconds)from SU:65
    Q_PROPERTY(int totalTime     READ getTotalTime     NOTIFY totalTimeChanged)
    //
    //% Valve Delay Timer( every second until 10 seconds)  delay for(Test Operation) and 3 seconds for O1 & O2 Valve5 & 6 tests
    //
    Q_PROPERTY(int valveDelayTimer    READ getValveDelayTimer       NOTIFY valveDelayTimerChanged)
    //
    //% Count Timer for Spraying Time from SU:52
    Q_PROPERTY(int valveTimer    READ getValveTimer   WRITE setValveTimer   NOTIFY valveTimerChanged)
    //
    //% Valve Total Time of running Valve Test ( spray Time)
    Q_PROPERTY(int valveTotalTime     READ getValveTotalTime     NOTIFY valveTotalTimeChanged)
    //
    //% Valve Timer Prefix string if needed
    //
    Q_PROPERTY(QString valveTimePrefixString    READ getValveTimePrefixString       NOTIFY valveTimePrefixStringChanged)
    //
    //% Valve Timer Suffix String if needed e.g 2 "seconds" or "hours" etc
    //
    Q_PROPERTY(QString valveTimeSuffixString   READ getValveTimeSuffixString        NOTIFY valveTimeSuffixStringChanged)
    //
    //% Valve State Text String,  OPEN = true , CLOSE = false  //Valve should be open during testing
    Q_PROPERTY(QString valveStateString     READ getValveStateString     WRITE setValveStateString     NOTIFY valveStateStringChanged)
    //    
    // % Display "Test Complete/In Process/Failed" String QML accessible and also goBack() to Diagnostic Page OnEnterPressed()
    Q_PROPERTY(QString   valveTestString      READ getValveTestString       WRITE setValveTestString        NOTIFY valveTestStringChanged)
    //
    //% Valve Toggle On/Off ( ON = 1. Off = 0)  //On As soon as we are in Diagnostics Mode
    //
    //Q_PROPERTY(bool valveToggleStatus   READ getValveToggleStatus   WRITE setValveToggleStatus      NOTIFY valveToggleStatusChanged)
    //
    //% Make accessible Valve Toggle Status String "ON" or "OFF" to QML as a string
    //
    //Q_PROPERTY(QString valveToggleStatusString      READ getValveToggleStatusString      WRITE setValveToggleStatusString    NOTIFY valveToggleStatusStringChanged)  

    //%% Start/Stop Buttons for Diagnostic/Valve Test Requests
    //
    //% Request Diagnostic Test
    Q_PROPERTY(bool diagnosticsTestRequest       READ getDiagnosticsTestRequest     WRITE setDiagnosticsTestRequest       NOTIFY  diagnosticsTestRequestChanged )
    //
    //% Valve Test Request start/Stop,  diagnostic Test Request
    //
    Q_PROPERTY(bool valveDiagTestRequest     READ getValveDiagTestRequest     WRITE setValveDiagTestRequest     NOTIFY valveDiagTestRequestChanged)
    //
    //% During Diagnostic Test
    //Q_PROPERTY(bool isDiagnosticTest    READ getIsDiagnosticTest       WRITE setIsDiagnosticTest     NOTIFY  isDiagnosticTestChanged )
    //
    //% During Valve Test 
     Q_PROPERTY(bool isValveTest     READ getIsValveTest     WRITE setIsValveTest  NOTIFY isValveTestChanged )
    //


/*  //Keep Test Simple at Diagnostic Level
    //% Key flags to enabled/disabled  disable Navigation Keys dependent on State of Diagnostics
    Q_PROPERTY(bool keyUpEnabled READ getKeyUpEnabled WRITE setKeyUpEnabled NOTIFY keyUpEnabledChanged)
    Q_PROPERTY(bool keyDownEnabled READ getKeyDownEnabled WRITE setKeyDownEnabled NOTIFY keyDownEnabledChanged)
    Q_PROPERTY(bool keyLeftEnabled READ getKeyLeftEnabled WRITE setKeyLeftEnabled NOTIFY keyLeftEnabledChanged)
    Q_PROPERTY(bool keyRightEnabled READ getKeyRightEnabled WRITE setKeyRightEnabled NOTIFY keyRightEnabledChanged)
    Q_PROPERTY(bool keyEnterEnabled READ getKeyEnterEnabled WRITE setKeyEnterEnabled NOTIFY keyEnterEnabledChanged)
    //

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% MEMORY
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% String to Display available memory( QML Accessible)
    //
    Q_PROPERTY(QString availableMemString READ getAvailableMemString  NOTIFY availableMemStringChanged)
    //
    //% For Labels or Text or Image on the buttons if any (QML Accessible)
    //
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% ENVISION
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% Envision Connection Status, Cell Strength, Version Info to QML UI
    Q_PROPERTY(QString envisionConStatusString READ getEnvisionConStatusString  NOTIFY envisionConStatusStringChanged) // Envision Connection Status
    Q_PROPERTY(QString envisionConStrengthString READ getEnvisionConStrengthString  NOTIFY envisionConStrengthStringChanged) //Envision Connection Strength
    Q_PROPERTY(QString envisionVerInfoString READ getEnvisionVerInfoString  NOTIFY envisionVerInfoStringChanged)  //Envision Version Info
    
    //% Envision Push Data Button Display + Enabled/Disable button ( QML Accessible)
    Q_PROPERTY(QString envisionButtonString READ getEnvisionButtonString   WRITE setEnvisionButtonString  NOTIFY envisionButtonStringChanged) // "Send Data To Envision" Button
    //% Envision Send Data Button: Enabled = 1 = True , Disabled = 0 = False , Button Satus is sent to Envision OnPressed (QML Accessibled)
    Q_PROPERTY(bool enableEnvisionDataSend READ getEnableEnvisionDataSend  WRITE setEnableEnvisionDataSend  NOTIFY enableEnvisionDataSendChanged) // Enable/Disable Button State Sent to Envision   
    
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // FONT KEY + LCD TEST can be Implemented at the Level of Simple QML? Aren't they from Condor Controller? hmm!
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% PUMPS
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% For Pumps, it looks like we have only 1 pump so
    //% Pump Toggle On/Off ( ON = True = 1. OFF = False = 0)
    Q_PROPERTY(bool pumpToggleStatus READ getPumpToggleStatus WRITE setPumpToggleStatus  NOTIFY pumpToggleStatusChanged)
    //
    //% Make accessible pump Toggle Status String "ON" or "OFF" to QML as a string // DO we need to display the pump Toogle Status ( QML Accessible)? Maybe as Title of Pump Display QML View Screen
    Q_PROPERTY(QString pumpToggleStatusString READ getPumpToggleStatusString WRITE setPumpToggleStatusString NOTIFY pumpToggleStatusStringChanged)
    //
    //% For Pump CountDown Timer,  Display (QML Accessible) 
    Q_PROPERTY(QString pumpTimerString READ getPumpTimerString   NOTIFY pumpTimerStringChanged)
    //
    //%  Pump Timer Prefix string if needed. need WRITE? Well what if prefix and suffix are in another language? hmm!
    //
    Q_PROPERTY(QString pumpTimerPrefixString READ getPumpTimerPrefixString   NOTIFY pumpTimerPrefixStringChanged)
    //
    //%  Pump Timer Suffix String if needed e.g 2 "seconds" or "hours" etc
    //
    Q_PROPERTY(QString pumpTimerSuffixString READ getPumpTimerSuffixString   NOTIFY pumpTimerSuffixStringChanged)
    //
    //% Display( QML Accessible) Watter Pressure Switch Status  "OPEN" / "CLOSED" default string is CLOSED
    //
    Q_PROPERTY(QString pumpWaterPressureSwitchStatusString READ getPumpWaterPressureSwitchStatusString   NOTIFY pumpWaterPressureSwitchStatusStringChanged)
    //
    //% Pump Water Pressure Switch Status:  OPEN = true , CLOSE = false
    //
    Q_PROPERTY(bool pumpWaterPressureSwitchStatus  READ getPumpWaterPressureSwitchStatus NOTIFY pumpWaterPressureSwitchStatusChanged)
    //
    //
    //
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% IO BOARDS
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //
    //%Send IO Board Communication Message String  like "Set IO Board On/Off"
    //%If ON is sent and true is returned for message received then Display green on screen for success else display RED on screen for failure
    //
    Q_PROPERTY(QString  sendIOBoardStatusString  READ getSendIOBoardStatusString  WRITE setSendIOBoardStatusString   NOTIFY sendIOBoardStatusStringChanged)
    //
    //%Maybe IO board is always ON then we just want to get a received message (bool) that the board is ON. either way the logic is fine!
    //
    //%If  true = ON = Display green on screen for success else display RED on screen for failure
    //%string comparison? eg if ( str == "ON")? maybe but prone to error?  ( Returned bool Accessible to QML as its used to change color of QML screen or button)
    Q_PROPERTY(bool  ioBoardStatus  READ getIOBoardStatus  NOTIFY ioBoardStatusChanged)
    //
    //%Display String holding IO board version ( QML Accessible)
    //
    Q_PROPERTY(QString  ioBoardVersionString  READ getIOBoardVersionString  NOTIFY ioBoardVersionStringChanged)
    //
    //%Prefix to IO Board Version String
    //
    Q_PROPERTY(QString  ioBoardVersionPrefixString  READ getIOBoardVersionPrefixString  NOTIFY ioBoardVersionPrefixStringChanged)
    //
    //%suffix to IO Board Version String
    //
    Q_PROPERTY(QString  ioBoardVersionSuffixString  READ getIOBoardVersionSuffixString  NOTIFY  ioBoardVersionSuffixStringChanged)
    //
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% CONDOR 
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //
    //%Display String holding CONDOR version ( QML Accessible)
    //
    Q_PROPERTY(QString  condorVersionString  READ getCondorVersionString  NOTIFY condorVersionStringChanged)
    //
    //%Prefix to CONDOR Version String
    //
    Q_PROPERTY(QString  condorVersionPrefixString  READ getCondorVersionPrefixString  NOTIFY condorVersionPrefixStringChanged)
    //
    //%suffix to CONDOR Version String
    //
    Q_PROPERTY(QString  condorVersionSuffixString  READ getCondorVersionSuffixString  NOTIFY condorVersionSuffixStringChanged)
    //
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% GARFUNKEL
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //
    //%Display String holding Garfunkel version ( QML Accessible)
    //
    Q_PROPERTY(QString  garfunkelVersionString  READ getGarfunkelVersionString  NOTIFY garfunkelVersionStringChanged)
    //
    //%Prefix to Garfunkel Version String
    //
    Q_PROPERTY(QString  garfunkelVersionPrefixString  READ getGarfunkelVersionPrefixString  NOTIFY garfunkelVersionPrefixStringChanged)
    //
    //%suffix to Garfunkel Version String
    //
    Q_PROPERTY(QString  garfunkelVersionSuffixString  READ getGarfunkelVersionSuffixString  NOTIFY garfunkelVersionSuffixStringChanged)
   //
*/ 

public:
	//%  Class Instance is created using pointers to:
	//%  Database, 
	//%  QDeclarativeContext,
	//%  GarfunkelLocalizationManager,
	//%  QObject ( optional )
    //%  
    // Diagnostics includes Condor, Garfunkel, IO boards etc, Valves, Pump, Envision etc. Need an instance of IPC?

    //
    //%     Class Constructor
    //
    
    //% Don't talk to DB now
    GarfunkelDiagnosticContext (GarfunkelDB *gdb, GarfunkelLocalizationMgr2 *GarfunkelLM,
                                  QDeclarativeContext *context,  QObject *parent = 0 );
    

    //% keep dianostic simple for Now!! Use only GarfunkelSystemData
    //GarfunkelDiagnosticContext(QDeclarativeContext *context, QObject *parent = 0 ); 

    //
    // %    Class Destructor
    //
    // Destroy instance once no nlonger needed!
    virtual ~GarfunkelDiagnosticContext ();

    //
    //%Get Functions
    //
    bool    getKey1Enabled()       {  return _key1Enabled;           }
    bool    getKey2Enabled()       {  return _key2Enabled;           }
    bool    getKey3Enabled()       {  return _key3Enabled;           }
    bool    getKey4Enabled()       {  return _key4Enabled;           }

   
    QString getButtonOneString()   {  return _button1String;         }
    QString getButtonTwoString()   {  return _button2String;         }
    QString getButtonThreeString() {  return _button3String;         }
    QString getButtonFourString()  {  return _button4String;         }
    

    int     getValveId ()              {   return  _valveId;            }
    float   getValveWaterTemp ()     {   return _valveWaterTemp;       }
    QString getValveWaterTempPrefixString()    { return _valveWaterTempPrefixString;    }
    QString getValveWaterTempSuffixString()    { return _valveWaterTempSuffixString;    }

    float   getValveWaterConductivity ()      {   return _valveWaterConductivity;         }
    QString getValveWaterConductivityPrefixString ()    { return _valveWaterConductivityPrefixString;    }
    QString getValveWaterConductivitySuffixString ()    { return _valveWaterConductivitySuffixString;    }

    int     getValveWaterPressureSwitchStatus ()   { return _valveWaterPressureSS;    }
 
    int     getTotalTime ()      { return _totalTime;         }
    int     getValveDelayTimer ()      { return _valveDelayTimer;         }
    int     getValveTotalTime ()      { return _valveTotalTime;         }
    int     getValveTimer ()      { return _valveTimer;         }

    QString getValveTimePrefixString ()  {  return _valveTimePrefixString;    }
    QString getValveTimeSuffixString ()   {  return _valveTimeSuffixString;    }

    QString getValveStateString () {  return _valveStateString;     }

    QString getValveTestString()      {  return _valveTestString;     }
    
   // bool    getValveToggleStatus()  { return _valveToggleStatus;        }
   // QString getValveToggleStatusString ()   { return _valveToggleStatusString;    }


    bool    getDiagnosticsTestRequest () {   return _diagnosticsTestStartFlag;            }

    bool    getValveDiagTestRequest () {    return  _valveDiagTestStartFlag;            }
   
    //bool    getIsDiagnosticTest ()          {  return _isDiagnosticTest;            }
    bool    getIsValveTest ()     { return _isValveTest;      }
   

/*    
    bool    getKeyUpEnabled()       {  return _keyUpEnabled;         }
    bool    getKeyDownEnabled()     {  return _keyDownEnabled;       }
    bool    getKeyLeftEnabled()     {  return _keyLeftEnabled;       }
    bool    getKeyRightEnabled()    {  return _keyRightEnabled;      }
    bool    getKeyEnterEnabled()    {  return _keyEnterEnabled;      }


    QString getAvailableMemString()  { return _availableMemString;   }
    QString getSendIOBoardStatusString()    { return _sendIOBoardStatusString;   }
    bool    getIOBoardStatus()      { return _ioBoardStatus;     }
    QString getIOBoardVersionString()   { return    _ioBoardVersionString;      }
    QString getIOBoardVersionPrefixString()  { return _ioBoardVersionPrefixString;     }
    QString getIOBoardVersionSuffixString()  { return _ioBoardVersionSuffixString;     }

    QString getCondorVersionString()    { return _condorVersionString;     }
    QString getCondorVersionPrefixString()     { return _condorVersionPrefixString;     }
    QString getCondorVersionSuffixString()      { return _condorVersionSuffixString;     }

    QString getGarfunkelVersionString()         { return _garfunkelVersionString;        }
    QString getGarfunkelVersionPrefixString()   { return _garfunkelVersionPrefixString;   }
    QString getGarfunkelVersionSuffixString()   { return _garfunkelVersionSuffixString;   }


    QString getEnvisionConStatusString()  { return _envisionConStatusString;        }
    QString getEnvisionConStrengthString()  { return _envisionConStrengthString;    }
    QString getEnvisionVerInfoString()   { return _envisionVerInfoString;         }
    Qstring getEnvisionButtonString()     { return _envisionbuttonString;          }
    bool    getEnableEnvisionDataSend()    { return _enableEnvisionDataSend;      }

    bool    getPumpToggleStatus()   { return _pumpToggleStatus;         }
    QString getPumpToggleStatusString()     { return _pumpToggleStatusString;    }
    Qstring getPumpTimerString()    { return _pumpTimerString;          }
    QString getPumpTimerPrefixString()     { return _pumpTimerPrefixString;     }
    QString getPumpTimerSuffixString()     { return _pumpTimerSuffixString;     }
    bool    getPumpWaterPressureSwitchStatus()      { return    _pumpWaterPressureSwitchStatus;       }
    QString getPumpWaterPressureSwitchStatusString()   { return _pumpWaterPressureSSString;     }

    QString getDiagLine1String()   {  return _diagLine1String;       }
    QString getDiagLine2String()   {  return _diagLine2String;       }
    QString getDiagLine3String()   {  return _diagLine3String;       }
    QString getDiagLine4String()   {  return _diagLine4String;       }
    
 */  
   
    
    //
    //%Set Functions
    //
    void setKey1Enabled (bool);
    void setKey2Enabled (bool );
    void setKey3Enabled (bool);
    void setKey4Enabled (bool);

    
    void setButtonOneString (QString&);
    void setButtonTwoString (QString&);
    void setButtonThreeString (QString&);
    void setButtonFourString (QString&);

    void setValveId (int& );

    void setValveWaterTemp (float& );
    void setValveWaterTempPrefixString (QString&);
    void setValveWaterTempSuffixString (QString&);

    void setValveWaterConductivity (float& );
    void setValveWaterConductivityPrefixString (QString&);
    void setValveWaterConductivitySuffixString (QString&);

    void setValveWaterPressureSwitchStatus(int&);


    void setTotalTime ( int&);
    void setValveDelayTimer (int&);
    void setValveTotalTime ( int&);
    void setValveTimer (int&);
    void setValveTimePrefixString (QString&);
    void setValveTimeSuffixString (QString&);

    void setValveTestString (QString&);
    void setValveStateString (QString&);

    //void setValveToggleStatusString (bool);
    //void setValveToggleStatusString (QString&);
    
    
    void setValveDiagTestRequest (bool);
    void setDiagnosticsTestRequest (bool);

   
    //void setIsDiagnosticTest (bool);
    void setIsValveTest (bool);
    
    //void setValveTimeString(QString&);
    //void setValveTimerPrefixString(QString&);
    //void setValveTimerSuffixString(QString&);

    //void setValveWaterTempString(QString&);
    //void setValveWaterTempPrefixString(QString&);
    //void setValveWaterTempSuffixString(QString&);

    //void setValveWaterConductivityString(QString&);
    //void setValveWaterConductivityPrefixString(QString&);
    //void setValveWaterConductivitySuffixString(QString&);

/*

    void setKeyUpEnabled    (bool);
    void setKeyDownEnabled  (bool);
    void setKeyLeftEnabled  (bool);
    void setKeyRightEnabled (bool);
    void setKeyEnterEnabled (bool);

    void setSendIOBoardStatusString(QString&);

    void setIOBoardStatus(bool);
    void setIOBoardVersionString(QString&);
    void setIOBoardVersionPrefixString(QString&);
    void setIOBoardVersionSuffixString(QString&);

    void setCondorVersionString(QString&);
    void setCondorVersionPrefixString(QString&);
    void setCondorVersionSuffixString(QString&);

    void setGarfunkelVersionString(QString&);
    void setGarfunkelVersionPrefixString(QString&);
    void setGarfunkelVersionSuffixString(QString&);

    void setDiagLine1String(QString&);
    void setDiagLine2String(QString&);
    void setDiagLine3String(QString&);
    void setDiagLine4String(QString&);

    void setAvailableMemString(QString&);

    void setEnvisionConStatusString(QString&);
    void setEnvisionConStrengthString(QString&);
    void setEnvisionVerInfoString(QString&);
    void setEnvisionButtonString(QString&);
    void setEnableEnvisionDataSend(bool);

    void setPumpToggleStatus(bool);
    void setPumpToggleStatusString(QString&);
    void setPumpTimerString(QString&);
    void setPumpTimerPrefixString(QString&);
    void setPumpTimerSuffixString(QString&);
    void setPumpWaterPressureSwitchStatus(bool);
    void setPumpWaterPressureSwitchStatusString( QString&);

*/


signals:
    
    void key1EnabledChanged ();
    void key2EnabledChanged ();
    void key3EnabledChanged ();
    void key4EnabledChanged ();  

    void buttonOneStringChanged ();
    void buttonTwoStringChanged ();
    void buttonThreeStringChanged ();
    void buttonFourStringChanged ();

    void valveIdChanged ();
    void valveWaterTempChanged ();
    void valveWaterTempPrefixStringChanged ();
    void valveWaterTempSuffixStringChanged ();

    void valveWaterConductivityChanged ();
    void valveWaterConductivityPrefixStringChanged ();
    void valveWaterConductivitySuffixStringChanged ();

    void valveWaterPressureSwitchStatusChanged (); //change Switch string from "CLOSE"(false) to "OPEN"(true) if MCA returns "true"(1)
       
    void totalTimeChanged ();
    void valveDelayTimerChanged ();
    void valveTimerChanged ();
    void valveTotalTimeChanged ();

    void valveTimePrefixStringChanged ();
    void valveTimeSuffixStringChanged ();

    void valveTestStringChanged ();
    void valveStateStringChanged ();

  
    //void valveToggleStatusChanged ();
    //void valveToggleStatusStringChanged ();
    void diagnosticsTestRequestChanged ();
    void valveDiagTestRequestChanged ();

   
   // void isDiagnosticTestChanged (); 
    void isValveTestChanged ();


       
/*

    void keyUpEnabled ();
    void keyDownEnabled ();
    void keyLeftEnabled ();
    void keyRightEnabled ();
    void keyEnterEnabled ();
    void sendIOBoardStatusStringChanged();
    void ioBoardStatusChanged();
    void ioBoardVersionStringChanged();
    void ioBoardVersionPrefixStringChanged();
    void ioBoardVersionSuffixStringChanged();

    void condorVersionStringChanged();
    void condorVersionPrefixStringChanged();
    void condorVersionSuffixStringChanged();

    void garfunkelVersionStringChanged();
    void garfunkelVersionPrefixStringChanged();
    void garfunkelVersionSuffixStringChanged();

    void diagLine1StringChanged(); // sent to QML
    void diagLine2StringChanged(); // sent to QML
    void diagLine3StringChanged(); // sent to QML
    void diagLine4StringChanged(); // sent to QML
    void availableMemStringChanged();

    void envisionConStatusStringChanged();
    void envisionConStrengthStringChanged();
    void envisionVerInfoStringChanged();
    void envisionButtonStringChanged();
    void enableEnvisionDataSendChanged();

    void pumpToggleStatusChanged();
    void pumpToggleStatusStringChanged();
    void pumpTimerSuffixStringChanged();
    void pumpTimerPrefixStringChanged();
    void pumpTimerSuffixStringChanged();
    void pumpWaterPressureSwitchStatusChanged();
    void pumpWaterPressureSwitchStatusStringChanged(); // change Switch string from "CLOSE"(false) to "OPEN"(true) if MCA returns "true"(1)
*/

    


    //% Functions to connect Signals from GarfunkelData to,
    //% And to Handle Signals 
    //% Need to know what Diganostic Test(Method)/or MCA method to carryout


public slots:

    // Slots to Receive infor from garfunkelSystemData
    //
    //% Initiate Diagnostic test
    //void initDiagTest (); 
    //% Initiate Valve Test
 
    //% Handles Diagnostic Test Changed Signal
    //void isDiagnosticTestChangedHandler ();  
    //% Handles Valve Test Changed Signal
    //void isValveTestChangedHandler ();

     //% init resource strings
    void _stringInit(); //% initialised all the default strings

    void diagOpComplete ();
    void diagOpStarted (int); 
    void diagOpFailed (int);    

    //% Set Buttons Once SU51 Reply is OK
    void valveDiagOpStarted (int);

    void internalErrorEvent();
    //% Handles Valve Test request Signal
    void valveDiagTestRequestChangedHandler ();
    //% Handles Diagnostic Test request Signal
    void diagnosticsTestRequestChangedHandler ();
    //% Slot Recieving Timing from MCA
    void diagOperationTimer (int, int ); 
    //% Setting of Diagnostic test results
    void diagDataUpdated (int, int, int, float, float ); 

    //% Clear Test Values before New Test begins
    void clearValveDiagnosticTest ();
    
    

   
//%  Perculiar variables/methods to this class
private:

    GarfunkelDB *_gDB;
    GarfunkelLocalizationMgr2 *_GarfunkelLM;
    QDeclarativeContext *_context;


    //bool _productLidSwitch ;  // If productLidSwicth is open cannot Enter diagnostic mode
    //bool _envisionStatus;  // status of Envision

    void _diagInit();  //% Init diagnostics tests

    void _makeSecondsString(int, QString&);
    void _makePrompt(int, QString&, QString&, QString&);
    //
    // Conatainer elements  Need this for Valves?
    //
    // PumpInfoModel*           _pumplist;
    // GarfunkelDataModel*        _garfunkelPtr;
    // ValveInfoModel*          _valvelist;

    //
    //%Private Variables
    //
    bool _key1Enabled;
    bool _key2Enabled;
    bool _key3Enabled;
    bool _key4Enabled;

    

    QString _button1String;
    QString _button2String;
    QString _button3String;
    QString _button4String;

    int _valveId;
    
    float _valveWaterTemp;
    QString _valveWaterTempPrefixString;
    QString _valveWaterTempSuffixString;
    float _valveWaterConductivity;
    QString _valveWaterConductivityPrefixString;
    QString _valveWaterConductivitySuffixString;

    int _valveWaterPressureSS;
  
    int _totalTime; 
    int _valveDelayTimer;
    int _valveTotalTime; //% Total Time of spray
    int _valveTimer;  //% Count Timer for Spraying

    QString _valveTimePrefixString;
    QString _valveTimeSuffixString;

    QString _valveStateString;
    QString _valveTestString;


    //bool _valveToggleStatus;
    //QString _valveToggleStatusString;
    
    //% initiate Diagnostics Test Mode from UI 
    bool _diagnosticsTestStartFlag; 

    //% initiate Valve Test Mode
    bool _valveDiagTestStartFlag; 


    
    //bool _isDiagnosticTest;
    bool _isValveTest;

    bool _isInternalErrorActive; //% Internal Error

    bool _valveDiagMode; 
    bool _diagMode;

    // These are Defaults from Database Once available...
    QString _secondsString;   // seconds number as a string

    QString _blank; //% for empty strings
    QString _dbTestPassedString;
    QString _dbTestFailedString;
    QString _dbTestInProgressString;
    QString _dbTestFailedStringReason;
    QString _dbErrorString; 
    
    QString _dbButtonOffString;  // database localized label for OFF button
    QString _dbButtonOnString;   // database localized label for ON button

    QString _dbValveIdString; // Default Valve ID = -1 //Need String to Int conversion
    QString _dbTempString; 
    QString _dbTempPrefixString;
    QString _dbTempSuffixString;  

    QString    _dbConductivity; 
    QString _dbConductivityPrefixString; // database localized label in front of time value
    QString _dbConductivitySuffixString;

    QString    _dbTimerString; //%Default Delay Timer from DataBase?
    QString     _dbTTimeString; //%Default Total Time from DataBase?
    QString _dbTimePrefixString; // database localized label in front of time value
    QString _dbTimeSuffixString; // database localized units label (like 'seconds') after time value
    
    QString _dbIOFailedString; //% IO Connection Down!!
    QString  _dbDiagOpeFailedString; //% Unspecified Error from SU51Error(1)
    QString _dbTestString; 

    QString _dbValveOPENStateString;  //% State Of Value is OPEN during Test and Closed when no Test
    QString _dbValveCLOSEStateString;  //% State Of Value is CLOSE when no Test

    QString _dbToggleStatusString;

    QString _dbValveDiagFailedString;//% SU51:ERR1

    
    QString _dbPressOffString;
    QString _dbPressOnString;
    QString _dbHomeString;
    QString _dbBackString;  
    QString _dbHelpString; 
    QString _fString;
    QString _dbPressCANCELString;


/*

    bool _keyUpEnabled;
    bool _keyDownEnabled;
    bool _keyLeftEnabled;
    bool _keyRightEnabled;
    bool _keyEnterEnabled;

    QString _sendIOBoardStatusString;

    bool  _ioBoardStatus;
    QString _ioBoardVersionString;
    QString _ioBoardVersionPrefixString;
    QString _ioBoardVersionSuffixString;

    QString _condorVersionString;
    QString _condorVersionPrefixString;
    QString _condorVersionSuffixString;

    QString _garfunkelVersionString;
    QString _garfunkelVersionPrefixString;
    QString _garfunkelVersionSuffixString;

    QString _diagLine1String;
    QString _diagLine2String;
    QString _diagLine3String;
    QString _diagLine4String;

    QString _availableMemString;
    QString _envisionConStatusString;
    QString _envisionConStrengthString;
    QString _envisionbuttonString;
    QString _envisionVerInfoString;
    bool _enableEnvisionDataSend;

    bool _pumpToggleStatus;
    QString _pumpToggleStatusString;
    QString _pumpTimerString;
    QString _pumpTimerPrefixString;
    QString _pumpTimerSuffixString;
    bool _pumpWaterPressureSwitchStatus;
    QString _pumpWaterPressureSSString;
*/

  

};

#endif // GARFUNKEL_DIAGNOSTIC_CONTEXT_H
