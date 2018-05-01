#ifndef GARFUNKELRESOURCESTRINGS_H
#define GARFUNKELRESOURCESTRINGS_H

//Qt modules include!
#include <QObject>
#include <QDebug>
#include <QtDeclarative>
#include "DBAccess.h"

#define MAIN_MENU_STRINGS_START                      3000
#define DATA_ENTRY_MENU_STRINGS_START                11000
#define DOWNLOAD_DATA_MENU_STRINGS_START             12000
#define SYSTEM_STATUS_MENU_STRINGS_START             13000
#define SERVICE_ACTIONS_MENU_STRINGS_START           14000
#define CONFIGURE_MENU_STRINGS_START                 15000
#define USER_OPTIONS_MENU_STRINGS_START              16000
#define QUICK_STATUS_STRINGS_START                   17000
#define ALARM_STATUS_STRINGS_START                   18000 

#define GENERAL_STRINGS_START               	     20000  // Strings and Values of info Display page!!

/********************************************************
* 							*
*   Garfunkel Resource String ID  Class                 *
*							*
*							*
********************************************************/
//% This is the resource string class used by ICU
//% for generating the resource bundle for Garfunkel
//%

class GarfunkelResourceStrings : public QObject
{
    Q_OBJECT
    Q_ENUMS(MainMenuResourceString)
    Q_ENUMS(ServiceActionsMenuResourceString)
    Q_ENUMS(DataEntryMenuResourceString)
    Q_ENUMS(DownloadDataMenuResourceString)
    Q_ENUMS(SystemStatusMenuResourceString)
    Q_ENUMS(ConfigureMenuResourceString)
    Q_ENUMS(UserOptionsMenuResourceString)
    Q_ENUMS(QuickStatusResourceString)
    Q_ENUMS(AlarmStatusResourceString)
    Q_ENUMS(GenericResourceString)
	Q_ENUMS(LanguageString)

    public:


       enum MainMenuResourceString
        {
                MainMenu = MAIN_MENU_STRINGS_START +1,
                DataEntry,
                DownloadData,
                ServiceActions,
                SystemStatus,
                Configure,
                UserOptions
        };

        enum ServiceActionsMenuResourceString
        {
                Diagnostics = SERVICE_ACTIONS_MENU_STRINGS_START+1,
        	    Phosphate,
                Sulfite,
             	CausticA,
            	CausticB,
            	EnVActions,
            	Valves,
            	Firmware,
            	Controller,
            	Status,
           		Software,
            	WaterInlet,
            	Drain,
            	SulfiteValve,
            	Temprature,
		        Conductivity,
        	    PressureSwitchStatus,
         		ValveState,
        		Timer,	
        		DelayTimer,
        		ValveTest,
                PhosphateValve,
                CausticValveA,
                CausticValveB,
                WaterInletValve,
                DrainValve,
                SmartSimon,
                Garfunkel,
                SmartSimonFirmware,
                GarfunkelFirmware,
                ControllerTest,
                KeyPadTest,
                PressKey,
                SystemMemory,
                EnVisionStatus,
                Memory,
                TotalMemory,
                UsedMemory,
                AvailableMemory,
                ConnectionStatus,
                CellStrength,
                EnVisionVersion,
                SoftwareVersion,
                Dispenser,
                DispenserVersion, 
                ControllerSoftware,
                ControllerVersion,
                LCDTest,
                FirmwareVersion,
                TestRunTime

        };
        enum DataEntryMenuResourceString
        {
                SetTitrationData = DATA_ENTRY_MENU_STRINGS_START +1,
                CausticATitrations,
                CausticBTitrations,
                SulfiteTitrations,
                PhosphateTitrations,
		Range
        };
        
	enum DownloadDataMenuResourceString
        {
            	IPAddress = DOWNLOAD_DATA_MENU_STRINGS_START +1,
	    	    Ssid,
		        ConnectionInformation,
		        SignalStrength
 	   
        };



        enum ConfigureMenuResourceString
        {
                UnitOfMeasure = CONFIGURE_MENU_STRINGS_START +1,
		        DateAndTime,
                Standard,
                Metric,
                StandardDelay,
                Secs,
                StandardString,
                MetricString,
        		SelectTimeZone,
        		SetDate,
        		SetTime,
        		SelectLocale,
        		SetLanguage

        };

        enum UserOptionsMenuResourceString
        {
                SetUserPassword = USER_OPTIONS_MENU_STRINGS_START +1,
                LayupFunctionality,
                DualSchedule,
                PrimarySchedule,
                SecondarySchedule,
                RefillSulfiteProduct,
                RefillPhosphateProduct,
                RefillCausticAProduct,
                RefillCausticBProduct,
		        ChangeDisplayInformation,
                Languages,
                English,
		        Spanish,
		        French,
                Chinese,
                UnitOfMeasurement,
                DateFormat,
		        ChangeSeperator

        };

       enum SystemStatusMenuResourceString
        {
        		ProductRefill = SYSTEM_STATUS_MENU_STRINGS_START+1,
        		Alarms,
        		MakeDown,
        		FWSignal,
        		EnVisionActions,
                Display
        };

        enum QuickStatusResourceString
        {
        		AlarmStatus = QUICK_STATUS_STRINGS_START+1,
        		BoilerCallForWater,
        		MakeDownStatus,
        		Actions,
        		SetUpNotComplete,
        		DateTime,
        		AlarmIsActive,
        		AlarmsAreActive
        };

        enum AlarmStatusResourceString
        {
        		PowerDownError = ALARM_STATUS_STRINGS_START+1,
        		IOCommunicationError,
        		ProductValveFlowSwitchError,
        		FlowSwitchErrorForMachine,
        		DrainFlushError,
        		ProductFlushErrorForDrainValve,
        		ProductEmptyForPocket,
        };
        
	    enum LanguageString
        {
                NoneLanguage = 7013,
                EnglishLanguage,
                SpanishLanguage,
                FrenchLanguage,
                ChineseLanguage = 7025
        };
    
     	
        enum GenericResourceString
    	{
            	Open = GENERAL_STRINGS_START +1,
            	Close,
                None,
                Completed,
                InComplete,
                InProgress,
                Home,
                Back,
                On,
                Off,
                Help,
                Seconds,
                Minutes,
                Months,
                Year,
                SerialNumber,
	            F,
                C,
        	    Us, // microSiemens
        	    Cm, // for cm
                Ml,
                Oz,
                Kg,
                Lb,
                Passed,
                Failed,
                DBSyncError,
                IoError,
                InternalError,
                ProtocolError,
        	    AlarmsMayBeActiveError,
        	    ElapsedTime,
                NoConnect,
                State,
                EnterPassword,
                ChangePassword,
                InvalidPassword,
        	    Exit,
        	    Save,
                Customer,
                TM,
        	    Test,
        	    Red,
        	    Green,
        	    Blue,
        	    Up,
        	    Down,
        	    Left,
        	    Right,
        	    Enter,
        	    F1,
        	    F2,
        	    F3,
        	    F4,
        	    Signal,
        	    Step,
        	    Delay,
        	    Amount,
        	    Cancel,
	            Connectivity,
	            NoConnectivity,
                Connected,
                Full,
                Half,
                Empty,
                Zero,
        	    No,
        	    Yes,
        		ActionFailed,
        		Product,
        		Total,
        		TimeLeft,
        		Capacity,
        		Copying,
        		Reseting,
        		To,
        		Copy,
        		Enabled,
        		Disabled,
        		Enable,
        		Disable,
        		ExceededMaxProduct,
        		SystemInfo,
        		Clear,     
        		NoProgram, //used by MCA
        		Run,
                Gallons,
        		MicroSiemens,
        		Centigrade,
        		Farenheit,
        		SaveTMLangConfirmation,
                SaveCustomerLangConfirmation,
                DegreeCentigrade,
                DegreeFarenheit,
                Kb // for kilobytes
    	};

};
#endif // GARFUNKELRESOURCESTRINGS_H
