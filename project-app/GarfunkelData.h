#if !defined(_GARFUNKELDATA_H)
#define _GARFUNKELDATA_H
#include <iostream>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/bimap.hpp>
#include "GarfunkelEnums.h"
#include "DatabaseCommands.h"
#include "GarfunkelCommandProcessor.h"
#include "ecolab.h"
#include "threads.h"
#include <queue>
#include <list>
#include "LocalizationManager.h"
#include "ElapsedTime.h"
#include "SocketInterface.h"
#include "GarfunkelIPCData.h"
#include "GarfunkelIPC.h"
//#include "DatabaseManager.h"
#include "IOBoardMessages.h"
#include "IOBoardSyncManager.h"
#include "DiagnosticsManager.h"
#include "DatabaseCommands.h"
#include "AlarmHandler.h"



namespace Garfunkel
{
   
	class GarfunkelData 
	{
		public:
			GarfunkelData(const GarfunkelData & objectToCopy);
			~GarfunkelData();

			// Create as a singleton
			static GarfunkelData&  Instance();

			ecolab::Shareable<BOOLEAN> 			    _continueRunning;
		    ecolab::Shareable<BOOLEAN> 			    _isMCAReady;
		    ecolab::MutexLock                       _dBSyncInProgressLock;
		    ecolab::Shareable<BOOLEAN> 			    _dBSyncInProgress;
		    ecolab::Shareable<BOOLEAN> 			    _alarmHandlerSleeping;
			std::string								_ioBoardDIString;
			std::string								_garfunkelIOBoardAddressInstance;
			std::string								_simonIOBoardAddressInstance;
			std::string								_uiAddressInstance;
			std::string                             _systemDIString;
			timespec           						_timeOfLastGarIOBCommunication;
			timespec           						_timeOfLastSimonIOBCommunication;
			timespec           						_timeOfLastDBSync;
			// database connectivity
			boost::shared_ptr< Garfunkel::DatabaseCommands > _database;

			void     StopPollingAllBoards();
			void     StartPollingAllBoards();
			void     SendMessageToUI(std::string &message);
			void ResetTimeouts(BOOLEAN resetEvenIfAlarmsDetected);
			ecolab::Shareable<BOOLEAN>                        _pollIOBoard;

		private:
			GarfunkelData();
			static BOOLEAN _initDone;
			void Initailize();

	};
	
	class SystemData
	{
	public:
		SystemData(const SystemData & objectToCopy);
		~SystemData();

		// Create as a singleton
		static SystemData&  Instance();


		void        SetAlarmMuteTime(int value);
		int         GetAlarmMuteTime();

		BOOLEAN ReadSystemDataFromDatabase(); //Read sys data


		/*!
            Reading and writing the machine data to a flat file.
		 */
		void        SetPrimaryLanguage(int     value); //needed to send formula name to Fbox in appropriate language
		int         GetPrimaryLanguage();
		void        SetUnitOfMeasurement(int     value);
		int         GetUnitOfMeasurement();
		void        SetTMLanguage(int     value);
		int         GetTMLanguage();

		BOOLEAN ReadSystemDataFromFile();
		BOOLEAN WriteSystemDataToFile();
		BOOLEAN ReadLocaleInfoSystemDataFromDatabase();
		BOOLEAN ReadPasswordInfoFromDatabase();


		void SetDilutionValveState(Garfunkel::GarfunkelValveState eOpenOrClosed);
		Garfunkel::GarfunkelValveState GetDilutionValveState();

		void SetDrainValveState(Garfunkel::GarfunkelValveState eOpenOrClosed);
		Garfunkel::GarfunkelValveState GetDrainValveState();

		void SetSumpValveState(Garfunkel::GarfunkelValveState eOpenOrClosed);
		Garfunkel::GarfunkelValveState GetSumpValveState();

		void SetOCapsuleValveState(int pId, Garfunkel::GarfunkelValveState eOpenOrClosed);
		Garfunkel::GarfunkelValveState GetOCapsuleValveState(int Id);

		void SetOCapsuleLidState(int Id, Garfunkel::GarfunkelSwitchState eOpenOrClosed);
		Garfunkel::GarfunkelSwitchState GetOCapsuleLidState(int Id);

		void SetBFWPumpState(Garfunkel::GarfunkelPumpState eOpenOrClosed);
		Garfunkel::GarfunkelPumpState GetBFWPumpState();

		void SetOCapsuleLEDStatus(int Id, Garfunkel::GarfunkelPumpState eOpenOrClosed);
		Garfunkel::GarfunkelPumpState GetOCapsuleLEDStatus(int Id);


		void SetMainWaterInletState(Garfunkel::GarfunkelValveState eOpenOrClosed);
		Garfunkel::GarfunkelValveState GetMainWaterInletState();

		void SetSValveState(Garfunkel::GarfunkelValveState eOpenOrClosed);
		Garfunkel::GarfunkelValveState GetSValveState();

		void SetPValveState(Garfunkel::GarfunkelValveState eOpenOrClosed);
		Garfunkel::GarfunkelValveState GetPValveState();

		void SetSLidSwitchState(Garfunkel::GarfunkelSwitchState eOpenOrClosed);
		Garfunkel::GarfunkelSwitchState GetSLidSwitchState();

		void SetHLidSwitchState(Garfunkel::GarfunkelSwitchState eOpenOrClosed);
		Garfunkel::GarfunkelSwitchState GetHLidSwitchState();

		void SetTreatmentPumpState(Garfunkel::GarfunkelPumpState eOpenOrClosed);
		Garfunkel::GarfunkelPumpState GetTreatmentPumpState();

		void SetGarfunkelPumpState(Garfunkel::GarfunkelPumpState eOpenOrClosed);
		Garfunkel::GarfunkelPumpState GetGarfunkelPumpState();

		void SetPumpSwitchState(Garfunkel::GarfunkelValveState eOpenOrClosed);
		Garfunkel::GarfunkelValveState GetPumpSwitchState();

		void SetPressureSwitchState(Garfunkel::GarfunkelValveState eOpenOrClosed);
		Garfunkel::GarfunkelValveState GetPressureSwitchState();

		void SetSOutOfProductLEDStatus(Garfunkel::GarfunkelPumpState eOpenOrClosed);
		Garfunkel::GarfunkelPumpState GetSOutOfProductLEDStatus();

		void SetHOutOfProductLEDStatus(Garfunkel::GarfunkelPumpState eOpenOrClosed);
		Garfunkel::GarfunkelPumpState GetHOutOfProductLEDStatus();

		void  SetSumpLevelSwitchState(Garfunkel::GarfunkelLevelSwitchState st);
		Garfunkel::GarfunkelLevelSwitchState GetSumpLevelSwitchState();


		GarfunkelProductPocket GetPocketIdForProduct(int productId);
		int GetProductIdForPocketId(GarfunkelProductPocket pocketId);

		BOOLEAN SetTreatmentPumpState(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485, GarfunkelPumpState OnOff);
		BOOLEAN SetSEmptyLEDState(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485, GarfunkelPumpState OnOff);
		BOOLEAN SetHEmptyLEDState(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485, GarfunkelPumpState OnOff);
		BOOLEAN SetOCapsuleLEDState(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485, int no, Garfunkel::GarfunkelPumpState OnOff);

		BOOLEAN ResetAllOutputsForGarfunkelBoard(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485 );
		BOOLEAN ResetAllOutputsForSimonBoard(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485 );


		ecolab::Shareable<BOOLEAN>      IsDirty;

		ecolab::Shareable<int>         CondOOPThreshold;
		ecolab::Shareable<float>              Conductivity;
		ecolab::Shareable<float>              TempInDegreeF;

		//Analog signals
		ecolab::Shareable<float>              Analog1;
		ecolab::Shareable<float>              Analog2;
		ecolab::Shareable<float>              Analog3;
		ecolab::Shareable<float>              Analog4;

		ecolab::Shareable<BOOLEAN>                                  _Digital1;
		ecolab::Shareable<BOOLEAN>                                  _Digital2;

		ecolab::Shareable<BOOLEAN>                       _SLowProductState;
		ecolab::Shareable<BOOLEAN>                       _HLowProductState;

		ecolab::Shareable<BOOLEAN>                       _GarfunkelIOBoardFaultLine;
		ecolab::Shareable<BOOLEAN>                       _SimonIOBoardFaultLine;

		ecolab::Shareable<BOOLEAN>                       _GarfunkelIOBoardLocked;
		ecolab::Shareable<BOOLEAN>                       _SimonIOBoardLocked;

		GarfunkelSystemState GetSystemState();
		void SetSystemState(Garfunkel::GarfunkelSystemState st);
		ecolab::Shareable<BOOLEAN>              DiagnosticEnabled;
		ecolab::DB::LocalizationManager          _languageMgr;
		ecolab::Shareable<int>         Locale;

		ecolab::Shareable<GarfunkelSchedule>                       _CurrentSchedule;
		ecolab::Shareable<BOOLEAN>                       _MakeDownActive;
		ecolab::Shareable<BOOLEAN>                       _DispenseActive;
		ecolab::Shareable<BOOLEAN>                       _LayupEnabled;
		ecolab::Shareable<Garfunkel::GarfunkelLevelSwitchState>  _sumpLevelSwitchState;

		ecolab::Shareable<int>       OperatingModeID;
		ecolab::Shareable<BOOLEAN>   IsDeareatorPresent;
		ecolab::Shareable<float>     CyclesOfConcentrationTarget;
		ecolab::Shareable<BOOLEAN>   IsBFWPIntermittent;
		ecolab::Shareable<int>       OperatingHoursPerDay;
		ecolab::Shareable<int>       ReferenceIntervalForTreatmentPump;
		ecolab::Shareable<float>     TreatmentPumpCalibrationValue;
		ecolab::Shareable<int>       BFWPSignalFilterTime;
		ecolab::Shareable<int>       MaxTimeBetweenBFWPCallsInHours;
		ecolab::Shareable<float>     BaselineConductivity;
		ecolab::Shareable<float>     VirtualCounterVolumeInGallon;
		ecolab::Shareable<float>     SumpLowToFullVolumeInGallon;
		ecolab::Shareable<float>     SumpFullToOverFlowVolumeInGallon;
		ecolab::Shareable<float>     SumpOverFlowToAboveVolumeInGallon;
		ecolab::Shareable<BOOLEAN>   IsSystemInitialized;

		//no defaults for below
		ecolab::Shareable<float>     BoilerPressure;
		ecolab::Shareable<float>     FWTemperature;
		ecolab::Shareable<float>     DAOperatingPressure;
		ecolab::Shareable<float>     NominalSteamFlow;

		ecolab::Shareable<float>     TotalCondensateReturn;
		ecolab::Shareable<int>       MaxTimeForFillEventToComplete;
		ecolab::Shareable<float>       TimeBetweenBFWPEvents;
		timespec                     TimeDateOfStartOfLastFillEvent;
		timespec                     TimeDateOfLastBFWPSignalReceived;
		timespec                     TimeDatePowerOn;
		timespec                     CausticRinseStartTime;
		timespec                     CausticRinseFinishTime;

		ecolab::Shareable<BOOLEAN>          DisableMakeSump;
		ecolab::Shareable<BOOLEAN>          DisableDispense;

	private:

		SystemData();
		ecolab::Shareable<int>         _primaryLanguage;
		ecolab::Shareable<int>         _secondaryLanguage;
		ecolab::Shareable<int>         _unitOfMeasurement;
		ecolab::Shareable<int>         _TMLanguage;
		ecolab::Shareable<int>         _alarmVolume;
		ecolab::Shareable<int>         _alarmMuteTime;
		ecolab::Shareable<int>          _isDirty;


		std::string         _primaryLanguageLocale;
		std::string         _secondaryLanguageLocale;
		std::string         _TMLanguageLocale;

		std::string         _primaryLanguageFont;
		std::string         _secondaryLanguageFont;
		std::string         _TMLanguageFont;

		ecolab::Shareable<int>                 _primaryLanguageFontPointSize;
		ecolab::Shareable<int>                 _secondaryLanguageFontPointSize;
		ecolab::Shareable<int>                 _TMLanguageFontPointSize;

		ecolab::Shareable<BOOLEAN>                 _primaryLanguageFontBold;
		ecolab::Shareable<BOOLEAN>                 _secondaryLanguageFontBold;
		ecolab::Shareable<BOOLEAN>                 _TMLanguageFontBold;

		std::string         _primaryLanguageFallbackFont;
		ecolab::Shareable<int>                 _primaryLanguageFallbackFontPointSize;
		ecolab::Shareable<BOOLEAN>                 _primaryLanguageFallbackFontBold;

		std::string         _TMPassword;
		std::string         _secretTMPassword;
		std::string         _custPassword;

		ecolab::MutexLock              _audibleAlarmTimeDataLock;
		timespec                       _audibleAlarmTime;


		ecolab::Shareable<Garfunkel::GarfunkelValveState>  _dilutionValveState;
		ecolab::Shareable<Garfunkel::GarfunkelValveState>  _drainValveState;
		ecolab::Shareable<Garfunkel::GarfunkelValveState>  _O1ValveState;
		ecolab::Shareable<Garfunkel::GarfunkelValveState>  _O2ValveState;
		ecolab::Shareable<Garfunkel::GarfunkelValveState>  _sumpValveState;
		ecolab::Shareable<Garfunkel::GarfunkelSwitchState> _O1LidSwitchState;
		ecolab::Shareable<Garfunkel::GarfunkelSwitchState> _O2LidSwitchState;
		ecolab::Shareable<Garfunkel::GarfunkelPumpState>   _BFWPState;
		ecolab::Shareable<Garfunkel::GarfunkelPumpState>   _O1EmptyLEDState;
		ecolab::Shareable<Garfunkel::GarfunkelPumpState>   _O2EmptyLEDState;



		ecolab::Shareable<Garfunkel::GarfunkelValveState>  _mainWaterInletState;
		ecolab::Shareable<Garfunkel::GarfunkelValveState>  _sValveState;
		ecolab::Shareable<Garfunkel::GarfunkelValveState>  _hValveState;
		ecolab::Shareable<Garfunkel::GarfunkelSwitchState>  _sLidSwitchState;
		ecolab::Shareable<Garfunkel::GarfunkelSwitchState>  _hLidSwitchState;

		ecolab::Shareable<Garfunkel::GarfunkelValveState>  _sumpPumpSwitchState;
		ecolab::Shareable<Garfunkel::GarfunkelPumpState>   _garfunkelPumpState;
		ecolab::Shareable<Garfunkel::GarfunkelValveState>  _pressureSwitchState;
		ecolab::Shareable<Garfunkel::GarfunkelPumpState>   _treatmentPumpState;
		ecolab::Shareable<Garfunkel::GarfunkelPumpState>   _SEmptyLEDState;
		ecolab::Shareable<Garfunkel::GarfunkelPumpState>   _HEmptyLEDState;


		ecolab::Shareable<Garfunkel::GarfunkelSystemState>        _systemState;
		ecolab::MutexLock                                           _systemStateLock;
		ecolab::Shareable<BOOLEAN>                                  _hasSystemBeenIdle;
		timespec                                                    _lastSystemIdleTime;

		static BOOLEAN _initDone;
		void Initailize();

	};

	






}

#endif  //_GARFUNKELDATA_H
