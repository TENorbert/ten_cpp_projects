#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <sys/time.h>
#include <time.h>
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <boost/bimap.hpp>
#include "threads.h"
#include "locks.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "ApplicationContext.h"
#include "DBAccess.h"
#include "ecolab.h"
#include "ElapsedTime.h"
#include "SocketInterface.h"
#include "GarfunkelEnums.h"
#include "GarfunkelData.h"
#include "ProductData.h"
#include "IOBoardMessages.h"
#include "GarfunkelIPC.h"
#include "LocalizationManager.h"
#include "DatabaseCallbacks.h"
#include "AlarmHandler.h"



BOOLEAN Garfunkel::GarfunkelData::_initDone = False;
BOOLEAN Garfunkel::SystemData::_initDone = False;

Garfunkel::GarfunkelData::GarfunkelData():
_ioBoardDIString(""),
_garfunkelIOBoardAddressInstance("aa"),
_simonIOBoardAddressInstance("sa"),
_systemDIString("")

{
	_continueRunning.Set(True);
	_isMCAReady.Set(False);
	_dBSyncInProgress.Set(False);
	_alarmHandlerSleeping.Set(True);
	_pollIOBoard.Set(False);
	_uiAddressInstance.assign("0a");
	memset(&_timeOfLastGarIOBCommunication, 0, sizeof(timespec));
	memset(&_timeOfLastSimonIOBCommunication, 0, sizeof(timespec));
	memset(&_timeOfLastDBSync, 0, sizeof(timespec));

}

Garfunkel::GarfunkelData::GarfunkelData(const Garfunkel::GarfunkelData & objectToCopy):
_ioBoardDIString(""),
_garfunkelIOBoardAddressInstance("aa"),
_simonIOBoardAddressInstance("sa"),
_systemDIString("")
{
	_dBSyncInProgress.Set(False);
	_alarmHandlerSleeping.Set(True);


}

Garfunkel::GarfunkelData::~GarfunkelData()
{

	std::cout<<"GarfunkelData destructor called"<<std::endl;

    std::cout<<"GarfunkelData destructor done"<<std::endl;
}


void Garfunkel::GarfunkelData::Initailize()
{

}


void Garfunkel::GarfunkelData::SendMessageToUI(std::string &message)
{

	GarfunkelIPCMaster&  ipcMaster = GarfunkelIPCMaster::Instance();
    ipcMaster.SendESPCommandResponse(message);
    std::cout << "GarfunkelData : Sent message to UI: " << message << std::endl;
}

void     Garfunkel::GarfunkelData::StartPollingAllBoards()
{
	std::cout << "GarfunkelData : Start polling boards "<< std::endl;
	ResetTimeouts(False);
	_pollIOBoard.Set(True);

}

void     Garfunkel::GarfunkelData::StopPollingAllBoards()
{
	std::cout << "GarfunkelData : Stop polling boards "<< std::endl;
	_pollIOBoard.Set(False);

}



void Garfunkel::GarfunkelData::ResetTimeouts(BOOLEAN resetEvenIfAlarmsDetected)
{
	timespec     startTime;
	int no = 0;

	SystemData &  SysData = SystemData::Instance();
	AlarmSettings &  AlarmData =  AlarmSettings::Instance();
    time_t clock1 = time(0);
    struct tm *ct = localtime(&clock1);

	std::cout<<"Calling ResetTimeouts at "<<asctime(ct)<<std::endl;

	clock_gettime(CLOCK_MONOTONIC,&startTime);
	if(AlarmData.GarIOBoardCommunicationAlarm.Get()==False) //only reset if there was no alarm detected previously
	_timeOfLastGarIOBCommunication  = startTime;
	if(AlarmData.SimonIOBoardCommunicationAlarm.Get()==False) //only reset if there was no alarm detected previously
	_timeOfLastSimonIOBCommunication  = startTime;
	_timeOfLastDBSync = startTime;

}

Garfunkel::GarfunkelData&  Garfunkel::GarfunkelData::Instance()
{
	static GarfunkelData  singleton;
	if(!_initDone)
	singleton.Initailize();
	return singleton;
}



///////////////////////////////////////////////////////////
// SystemData

Garfunkel::SystemData::SystemData() :
        _primaryLanguage(0),
        _secondaryLanguage(0),
        _unitOfMeasurement(0),
        _TMLanguage(0),
        _alarmVolume(0),
		_alarmMuteTime(2.5*60)
{
	memset(&_audibleAlarmTime, 0, sizeof(timespec));
	memset(&_lastSystemIdleTime, 0, sizeof(timespec));
	_systemState.Set(eIdle);
	_hasSystemBeenIdle.Set(True);
	DiagnosticEnabled.Set(False);
    Locale.Set(0);
    IsDirty.Set(False);
    _dilutionValveState.Set(eClose);
    _drainValveState.Set(eClose);
	CondOOPThreshold.Set(1000);
	_primaryLanguageLocale.assign("en");
	_secondaryLanguageLocale.assign("en");
	_TMLanguageLocale.assign("en");

	_primaryLanguageFont.assign("helvetica");
	_secondaryLanguageFont.assign("helvetica");
	_TMLanguageFont.assign("helvetica");

	_primaryLanguageFontPointSize.Set(26);
	_secondaryLanguageFontPointSize.Set(26);
	_TMLanguageFontPointSize.Set(26);

	_primaryLanguageFontBold.Set(False);
	_secondaryLanguageFontBold.Set(False);
	_TMLanguageFontBold.Set(False);

	_primaryLanguageFallbackFont.assign("helvetica");
	_primaryLanguageFallbackFontPointSize.Set(26);
	_primaryLanguageFallbackFontBold.Set(False);

	_TMPassword.assign("ULRD");
	_secretTMPassword.assign("UDLR");
	_custPassword.assign("UDLR");
	_SimonIOBoardFaultLine.Set(False);
	_GarfunkelIOBoardFaultLine.Set(False);
	_GarfunkelIOBoardLocked.Set(False);
	_SimonIOBoardLocked.Set(False);

	_sLidSwitchState.Set(eSwitchClosed);
	_hLidSwitchState.Set(eSwitchClosed);
	_O1LidSwitchState.Set(eSwitchClosed);
	_O2LidSwitchState.Set(eSwitchClosed);
	_sumpLevelSwitchState.Set(eNormal);

	_primaryLanguage.Set(0);
	_secondaryLanguage.Set(0);
	_unitOfMeasurement.Set(0);
	_TMLanguage.Set(0);


	OperatingModeID.Set(0);
	IsDeareatorPresent.Set(True);
	CyclesOfConcentrationTarget.Set(30);
	IsBFWPIntermittent.Set(True);
	OperatingHoursPerDay.Set(24);
	ReferenceIntervalForTreatmentPump.Set(30);
	TreatmentPumpCalibrationValue.Set(113.5624);
	BFWPSignalFilterTime.Set(4);
	MaxTimeBetweenBFWPCallsInHours.Set(96);
	BaselineConductivity.Set(200);
	VirtualCounterVolumeInGallon.Set(0.79);
	SumpLowToFullVolumeInGallon.Set(1.056688);
	SumpFullToOverFlowVolumeInGallon.Set(1.849204);
	SumpOverFlowToAboveVolumeInGallon.Set(0.5283441);
	memset(&TimeDateOfStartOfLastFillEvent, 0, sizeof(timespec));
	memset(&TimeDateOfLastBFWPSignalReceived, 0, sizeof(timespec));
	memset(&TimeDatePowerOn, 0, sizeof(timespec));
	memset(&CausticRinseStartTime, 0, sizeof(timespec));
	memset(&CausticRinseStartTime, 0, sizeof(timespec));



	IsSystemInitialized.Set(False);
}

Garfunkel::SystemData::SystemData(const SystemData& ObjectToCopy):
		_primaryLanguage(0),
        _secondaryLanguage(0),
        _unitOfMeasurement(0),
        _TMLanguage(0),
        _alarmVolume(0),
		_alarmMuteTime(2.5*60)
{
	memset(&_audibleAlarmTime, 0, sizeof(timespec));
	memset(&_lastSystemIdleTime, 0, sizeof(timespec));
	_systemState.Set(eIdle);
	_CurrentSchedule.Set(ePrimary);
	_hasSystemBeenIdle.Set(True);
	DiagnosticEnabled.Set(False);
	_primaryLanguageLocale.assign("en");
	_secondaryLanguageLocale.assign("en");
	_TMLanguageLocale.assign("en");

	_primaryLanguageFont.assign("helvetica");
	_secondaryLanguageFont.assign("helvetica");
	_TMLanguageFont.assign("helvetica");

	_primaryLanguageFontPointSize.Set(26);
	_secondaryLanguageFontPointSize.Set(26);
	_TMLanguageFontPointSize.Set(26);

	_primaryLanguageFontBold.Set(False);
	_secondaryLanguageFontBold.Set(False);
	_TMLanguageFontBold.Set(False);

	_primaryLanguageFallbackFont.assign("helvetica");
	_primaryLanguageFallbackFontPointSize.Set(26);
	_primaryLanguageFallbackFontBold.Set(False);

	_TMPassword.assign("ULRD");
	_secretTMPassword.assign("UDLR");
	_custPassword.assign("UDLR");

	_treatmentPumpState.Set(eOff);
	_garfunkelPumpState.Set(eOff);
	DisableMakeSump.Set(False);
	DisableDispense.Set(False);


}

Garfunkel::SystemData::~SystemData()
{
    //deinit map datastructure in the class

}

void Garfunkel::SystemData::Initailize()
{
    ReadSystemDataFromDatabase(); //load config info from db
	_initDone = True;
}


Garfunkel::SystemData&  Garfunkel::SystemData::Instance()
{
	static SystemData singleton;
	if(!_initDone)
	singleton.Initailize();
	return singleton;
}







Garfunkel::GarfunkelProductPocket Garfunkel::SystemData::GetPocketIdForProduct(int productId)
{

}



void Garfunkel::SystemData::SetOCapsuleValveState(int Id, GarfunkelValveState eOpenOrClosed)
{
	if(Id==0)
		_O1ValveState = eOpenOrClosed;
	else
		_O2ValveState = eOpenOrClosed;

}

Garfunkel::GarfunkelValveState Garfunkel::SystemData::GetOCapsuleValveState(int Id)
{
	if(Id==0)
			return _O1ValveState.Get();
		else
			return _O2ValveState.Get();
}


void Garfunkel::SystemData::SetOCapsuleLidState(int Id, GarfunkelSwitchState eOpenOrClosed)
{
	if(Id==0)
		_O1LidSwitchState = eOpenOrClosed;
	else
		_O2LidSwitchState = eOpenOrClosed;

}

Garfunkel::GarfunkelSwitchState Garfunkel::SystemData::GetOCapsuleLidState(int Id)
{
	if(Id==0)
			return _O1LidSwitchState.Get();
		else
			return _O2LidSwitchState.Get();
}

void Garfunkel::SystemData::SetDilutionValveState(GarfunkelValveState eOpenOrClosed)
{
	_dilutionValveState = eOpenOrClosed;
}

Garfunkel::GarfunkelValveState Garfunkel::SystemData::GetDilutionValveState()
{

	return _dilutionValveState.Get();

}

void Garfunkel::SystemData::SetDrainValveState(Garfunkel::GarfunkelValveState eOpenOrClosed)
{
	_drainValveState = eOpenOrClosed;
}

Garfunkel::GarfunkelValveState Garfunkel::SystemData::GetDrainValveState()
{

	return _drainValveState.Get();

}


void Garfunkel::SystemData::SetSumpValveState(Garfunkel::GarfunkelValveState eOpenOrClosed)
{
	_sumpValveState = eOpenOrClosed;
}

Garfunkel::GarfunkelValveState Garfunkel::SystemData::GetSumpValveState()
{

	return _sumpValveState.Get();

}


void Garfunkel::SystemData::SetBFWPumpState(Garfunkel::GarfunkelPumpState eOpenOrClosed)
{
	_BFWPState = eOpenOrClosed;
}

Garfunkel::GarfunkelPumpState Garfunkel::SystemData::GetBFWPumpState()
{

	return _BFWPState.Get();

}



void Garfunkel::SystemData::SetOCapsuleLEDStatus(int Id, Garfunkel::GarfunkelPumpState eOpenOrClosed)
{
	if(Id==0)
		_O1EmptyLEDState = eOpenOrClosed;
	else
		_O2EmptyLEDState = eOpenOrClosed;

}

Garfunkel::GarfunkelPumpState Garfunkel::SystemData::GetOCapsuleLEDStatus(int Id)
{
	if(Id==0)
			return _O1EmptyLEDState.Get();
		else
			return _O2EmptyLEDState.Get();
}


void Garfunkel::SystemData::SetMainWaterInletState(Garfunkel::GarfunkelValveState eOpenOrClosed)
{
	//std::cout<<"Setting WaterInletState"<<eOpenOrClosed<<std::endl;
	_mainWaterInletState = eOpenOrClosed;
}

Garfunkel::GarfunkelValveState Garfunkel::SystemData::GetMainWaterInletState()
{

	return _mainWaterInletState.Get();

}

void Garfunkel::SystemData::SetSValveState(Garfunkel::GarfunkelValveState eOpenOrClosed)
{
	_sValveState = eOpenOrClosed;
}

Garfunkel::GarfunkelValveState Garfunkel::SystemData::GetSValveState()
{

	return _sValveState.Get();

}


void Garfunkel::SystemData::SetPValveState(Garfunkel::GarfunkelValveState eOpenOrClosed)
{
	_hValveState = eOpenOrClosed;
	//std::cout<<"SetPValveState= "<<eOpenOrClosed<<std::endl;
}

Garfunkel::GarfunkelValveState Garfunkel::SystemData::GetPValveState()
{

	return _hValveState.Get();

}

void Garfunkel::SystemData::SetSLidSwitchState(Garfunkel::GarfunkelSwitchState eOpenOrClosed)
{
	_sLidSwitchState = eOpenOrClosed;
}

Garfunkel::GarfunkelSwitchState Garfunkel::SystemData::GetSLidSwitchState()
{

	return _sLidSwitchState.Get();

}

void Garfunkel::SystemData::SetHLidSwitchState(Garfunkel::GarfunkelSwitchState eOpenOrClosed)
{
	_hLidSwitchState = eOpenOrClosed;
}

Garfunkel::GarfunkelSwitchState Garfunkel::SystemData::GetHLidSwitchState()
{

	return _hLidSwitchState.Get();

}

void Garfunkel::SystemData::SetTreatmentPumpState(Garfunkel::GarfunkelPumpState eOpenOrClosed)
{
	_treatmentPumpState = eOpenOrClosed;
}

Garfunkel::GarfunkelPumpState Garfunkel::SystemData::GetTreatmentPumpState()
{

	return _treatmentPumpState.Get();

}




void Garfunkel::SystemData::SetPumpSwitchState(Garfunkel::GarfunkelValveState eOpenOrClosed)
{
	_sumpPumpSwitchState = eOpenOrClosed;
}

Garfunkel::GarfunkelValveState Garfunkel::SystemData::GetPumpSwitchState()
{

	return _sumpPumpSwitchState.Get();

}


void Garfunkel::SystemData::SetGarfunkelPumpState(Garfunkel::GarfunkelPumpState eOpenOrClosed)
{
	_garfunkelPumpState = eOpenOrClosed;
}

Garfunkel::GarfunkelPumpState Garfunkel::SystemData::GetGarfunkelPumpState()
{

	return _garfunkelPumpState.Get();

}

void Garfunkel::SystemData::SetPressureSwitchState(Garfunkel::GarfunkelValveState eOpenOrClosed)
{
	_pressureSwitchState = eOpenOrClosed;
}

Garfunkel::GarfunkelValveState Garfunkel::SystemData::GetPressureSwitchState()
{

	return _pressureSwitchState.Get();

}

void Garfunkel::SystemData::SetSOutOfProductLEDStatus(Garfunkel::GarfunkelPumpState eOpenOrClosed)
{
	_SEmptyLEDState = eOpenOrClosed;
}

Garfunkel::GarfunkelPumpState Garfunkel::SystemData::GetSOutOfProductLEDStatus()
{

	return _SEmptyLEDState.Get();

}

void Garfunkel::SystemData::SetHOutOfProductLEDStatus(Garfunkel::GarfunkelPumpState eOpenOrClosed)
{
	_HEmptyLEDState = eOpenOrClosed;
}

Garfunkel::GarfunkelPumpState Garfunkel::SystemData::GetHOutOfProductLEDStatus()
{

	return _HEmptyLEDState.Get();

}


void Garfunkel::SystemData::SetSumpLevelSwitchState(Garfunkel::GarfunkelLevelSwitchState eOpenOrClosed)
{
	if(eOpenOrClosed!=eNormal)
	std::cout<<"Setting level switch="<<eOpenOrClosed<<std::endl;
	_sumpLevelSwitchState = eOpenOrClosed;
}

Garfunkel::GarfunkelLevelSwitchState Garfunkel::SystemData::GetSumpLevelSwitchState()
{
	return _sumpLevelSwitchState.Get();
}




int         Garfunkel::SystemData::GetAlarmMuteTime()
{
    return _alarmMuteTime.Get();
}


BOOLEAN Garfunkel::SystemData::SetTreatmentPumpState(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485, GarfunkelPumpState OnOff)
{

	BOOLEAN retValue = False;
	std::stringstream cmd;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	cmd<<"SetTreatmentPumpState";
	boost::shared_ptr< Garfunkel::IIOBoardMessage > msg  = cmdProcIOBoard.GetCommand(cmd.str());

	SetTreatmentPumpStateOnSIOB  *pCmd =  NULL;

	if(msg.get()!=NULL)
	{
		pCmd = (SetTreatmentPumpStateOnSIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetTreatmentPumpState(OnOff);
			pCmd->SetTimeInterval(5);
		    retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
			if(retValue==True)
			{
	            if(OnOff==eOn&&pCmd->IsMessageRunable(True)==False )
	            pCmd->StartTimedMessage();

				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				if(OnOff==eOn)
				std::cout<<"*** Pump  ON at "<<asctime(ct)<<std::endl;
				else
				{

					std::cout<<"*** Pump OFF at "<<asctime(ct)<<std::endl;
				}
			}
			else
			{
				std::cout<<"DispensingThread: Setting Pump State FAILED!!!"<<std::endl;
			}
		}
	}
   return retValue;

}




BOOLEAN Garfunkel::SystemData::SetSEmptyLEDState(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485, GarfunkelPumpState OnOff)
{

	BOOLEAN retValue = False;
	std::stringstream cmd;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	cmd<<"SetSEmptyLEDState";
	boost::shared_ptr< Garfunkel::IIOBoardMessage > msg  = cmdProcIOBoard.GetCommand(cmd.str());

	SetSEmptyLEDStateOnSIOB  *pCmd =  NULL;

	if(msg.get()!=NULL)
	{
		pCmd = (SetSEmptyLEDStateOnSIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetSEmptyLEDState(OnOff);
		    retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				if(OnOff==eOn)
					std::cout<<"*** S LED  ON at "<<asctime(ct)<<std::endl;
				else
					std::cout<<"*** S LED  OFF at "<<asctime(ct)<<std::endl;
			}
			else
			{
				std::cout<<"DispensingThread: S LED State FAILED!!!"<<std::endl;
			}
		}
	}
   return retValue;

}


BOOLEAN Garfunkel::SystemData::SetHEmptyLEDState(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485, GarfunkelPumpState OnOff)
{

	BOOLEAN retValue = False;
	std::stringstream cmd;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	cmd<<"SetHEmptyLEDState";
	boost::shared_ptr< Garfunkel::IIOBoardMessage > msg  = cmdProcIOBoard.GetCommand(cmd.str());

	SetHEmptyLEDStateOnSIOB  *pCmd =  NULL;

	if(msg.get()!=NULL)
	{
		pCmd = (SetHEmptyLEDStateOnSIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetHEmptyLEDState(OnOff);
		    retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				if(OnOff==eOn)
					std::cout<<"*** H LED  ON at "<<asctime(ct)<<std::endl;
				else
					std::cout<<"*** H LED  OFF at "<<asctime(ct)<<std::endl;
			}
			else
			{
				std::cout<<"DispensingThread: H LED State FAILED!!!"<<std::endl;
			}
		}
	}
   return retValue;

}


BOOLEAN  Garfunkel::SystemData::SetOCapsuleLEDState(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485, int no, Garfunkel::GarfunkelPumpState OnOff)
{

	BOOLEAN retValue = False;
	std::stringstream cmd;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	cmd<<"SetOEmptyLEDState";
	boost::shared_ptr< Garfunkel::IIOBoardMessage > msg  = cmdProcIOBoard.GetCommand(cmd.str());

	SetOCapsuleEmptyLEDStateOnGIOB  *pCmd =  NULL;


	if(msg.get()!=NULL)
	{
		pCmd = (SetOCapsuleEmptyLEDStateOnGIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetOCapsuleEmptyLEDState(no, OnOff);
			retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				if(OnOff==eOn)
					std::cout<<"*** OCapsule  LED ON for No ="<<no<<"at"<<asctime(ct)<<std::endl;
				else
					std::cout<<"*** OCapsule  LED OFF for No ="<<no<<"at"<<asctime(ct)<<std::endl;
			}
			else
			{
				std::cout<<"DispensingThread: Setting OCapsule  LED state FAILED!!!"<<no<<std::endl;

			}
		}
	}
   return retValue;

}


BOOLEAN Garfunkel::SystemData::ResetAllOutputsForGarfunkelBoard(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485 )
{

	BOOLEAN retValue = False;
	std::stringstream cmd;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	cmd<<"SetAllOutputsOffGarfunkel";
	boost::shared_ptr< Garfunkel::IIOBoardMessage > msg  = cmdProcIOBoard.GetCommand(cmd.str());

	SetAllOutputsOffOnGIOB  *pCmd =  NULL;


	if(msg.get()!=NULL)
	{
		pCmd = (SetAllOutputsOffOnGIOB*)msg.get();
		if(pCmd!=NULL)
		{
			retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"*** All outputs off for garfunkel IOBoard"<<asctime(ct)<<std::endl;
			}
			else
			{
				std::cout<<"DispensingSystemData: ll outpust off for garfunkel IOBoard FAILED!!!"<<std::endl;

			}
		}
	}
   return retValue;
}



BOOLEAN Garfunkel::SystemData::ResetAllOutputsForSimonBoard(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485 )
{

	BOOLEAN retValue = False;
	std::stringstream cmd;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	cmd<<"SetAllOutputsOffSimon";
	boost::shared_ptr< Garfunkel::IIOBoardMessage > msg  = cmdProcIOBoard.GetCommand(cmd.str());

	SetAllOutputsOffOnSIOB  *pCmd =  NULL;


	if(msg.get()!=NULL)
	{
		pCmd = (SetAllOutputsOffOnSIOB*)msg.get();
		if(pCmd!=NULL)
		{
			retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"*** All outputs off for simon IOBoard"<<asctime(ct)<<std::endl;
			}
			else
			{
				std::cout<<"DispensingSystemData: ll outpust off for garfunkel IOBoard FAILED!!!"<<std::endl;

			}
		}
	}
   return retValue;
}




Garfunkel::GarfunkelSystemState Garfunkel::SystemData::GetSystemState()
{
	ecolab::ScopeLock Lock(_systemStateLock);
	return _systemState.Get();

}

void Garfunkel::SystemData::SetSystemState(Garfunkel::GarfunkelSystemState st)
{
	ecolab::ScopeLock Lock(_systemStateLock);

	if(st==eIdle)
	{
		_hasSystemBeenIdle.Set(True);
		clock_gettime(CLOCK_MONOTONIC, &_lastSystemIdleTime);
		GarfunkelData &   AqData = Garfunkel::GarfunkelData::Instance();
		//std::cout<<"#### System is set to IDLE state ####"<<std::endl;
		if(IsDirty.Get()==True&&AqData._dBSyncInProgress.Get()==False) //something has changed in system data while we were busy, lets update out systemdata context
		{
			GarfunkelIPCMaster&  ipcMaster = GarfunkelIPCMaster::Instance();
			std::string message;
			std::stringstream strStream;
			ecolab::ScopeLock Lock(AqData._dBSyncInProgressLock); //lock mutex and set flag
   			AqData._dBSyncInProgress.Set(True);
   			std::cout << "******SetSystemState....Calling delayed callbacks*****************" << std::endl;
  			strStream.str("");
  			strStream<<AqData._uiAddressInstance<<":SU:64:1:";
  			message.assign(strStream.str());
  			ipcMaster.SendESPCommandResponse(message); //send message to UI that DB is being updated and no operations, (like prime/calib/diagnostics and activation of formula) can continue
  			while(AqData._alarmHandlerSleeping.Get()==False)
   			{
   				sleep(50); //wait for sometime cos Alarm handler can finish 1 round and stop checking for alarms
   				std::cout << "DatabaseThread After Sleep...waiting to Call delayed callbacks..........." << std::endl;
   			}
   			AqData.StopPollingAllBoards(); //done to make sure we don't have com alarms
   			boost::shared_ptr<SystemDataCallback>              sCallback(new SystemDataCallback("SystemDataCallback"));
   		    sCallback->Update();
   			AqData._dBSyncInProgress.Set(False);
   			AqData.StartPollingAllBoards(); //resume polling boards
   			strStream.str("");
  			strStream<<AqData._uiAddressInstance<<":SU:64:0:";
  			message.assign(strStream.str());
  			ipcMaster.SendESPCommandResponse(message); //send message to UI that DB is done updating and operations can resume
  			time_t clock1 = time(0);
  			struct tm *ct = localtime(&clock1);
			std::cout << "*******************SetSystemState....delayed callback done****************** at"<<asctime(ct) << std::endl;
			clock_gettime(CLOCK_MONOTONIC, &AqData._timeOfLastDBSync);
			IsDirty.Set(False);
		}
	}
	else
	{
		//std::cout<<"#System is set to non idle state#"<<std::endl;
		_hasSystemBeenIdle.Set(False);
	}
	_systemState.Set(st);
	std::cout<<"#### System is set State"<<st<<std::endl;
}





void        Garfunkel::SystemData::SetPrimaryLanguage(int     value)
{
    _primaryLanguage = value;
}

int         Garfunkel::SystemData::GetPrimaryLanguage()
{
    return _primaryLanguage.Get();
}


void        Garfunkel::SystemData::SetTMLanguage(int     value)
{
    _TMLanguage = value;
}

int         Garfunkel::SystemData::GetTMLanguage()
{
    return _TMLanguage.Get();
}

void        Garfunkel::SystemData::SetUnitOfMeasurement(int     value)
{
    _unitOfMeasurement = value;
}

int         Garfunkel::SystemData::GetUnitOfMeasurement()
{
    return _unitOfMeasurement.Get();
}


/*!
     Read the machine data from the database.
*/
BOOLEAN Garfunkel::SystemData::ReadSystemDataFromDatabase()
{

    ecolab::DB::DBAccess    myDBAccess;
    std::string             connectString;
    BOOLEAN                 retValue = False;

    // Use of the connection string.
    connectString = "dbname = 'Garfunkel' user = 'db_controller' password = 'controller'";

    /* Connect to DB if it is not connected. */
    if (NULL == myDBAccess.DBisConnected())
    {
        myDBAccess.DBConnect(connectString, 10);
    }

    if(NULL != myDBAccess.DBisConnected())
    {

        ecolab::DB::DataSet        dataSet;
        std::string                sql = "SELECT * from GetSystemData()";

        if(myDBAccess.DBExecuteStored(sql, dataSet))
        {
           if(dataSet.GetNumberOfRows() == 1)
            {
                boost::shared_ptr<ecolab::DB::IColumnData>    colData;
			    ecolab::DB::DataRow rowData(dataSet.GetFirstRow());

                if(rowData.GetNumberOfColumns() > 0)
                {

                    INT32     IntValue  = 0;
                    REAL64    RealValue = 0.0;
                    BOOLEAN   BoolValue = False;
                    std::string StringValue;
                    colData = rowData.GetColumn("PrimaryLanguage");
                    if(colData.get() != NULL)
                    {
                        colData->AsInt(IntValue);
    					SetPrimaryLanguage(IntValue);
                        std::cout << "PrimaryLanguage: " << IntValue << std::endl;
                    }

                    colData = rowData.GetColumn("TMLanguage");
                    if(colData.get() != NULL)
                    {
                        colData->AsInt(IntValue);
    					SetTMLanguage(IntValue);
                       std::cout << "TMLang: " << IntValue << std::endl;
                    }

                    colData = rowData.GetColumn("UnitOfMeasure");
                    if(colData.get() != NULL)
                    {
                        colData->AsInt(IntValue);
                        SetUnitOfMeasurement(IntValue);
                        std::cout << "UnitOfMeasure: " << IntValue << std::endl;
                    }

                    colData = rowData.GetColumn("OperatingModeID");
                    if(colData.get() != NULL)
                    {
                        colData->AsInt(IntValue);
                        OperatingModeID.Set(IntValue);
                        std::cout << "OperatingModeID: " << IntValue << std::endl;
                    }

					colData = rowData.GetColumn("IsDeareatorPresent");
					if (colData.get() != NULL)
					{
						colData->AsBool(BoolValue);
						IsDeareatorPresent.Set(BoolValue);
						std::cout << "IsDeareatorPresent: " << BoolValue	<< std::endl;
					}

					colData = rowData.GetColumn("CyclesOfConcentrationTarget");
					if (colData.get() != NULL)
					{
						colData->AsFloat(RealValue);
						CyclesOfConcentrationTarget.Set(RealValue);
						std::cout << "CyclesOfConcentrationTarget: "
								<< RealValue << std::endl;
					}
					colData = rowData.GetColumn("IsBFWPIntermittent");
					if (colData.get() != NULL)
					{
						colData->AsBool(BoolValue);
						IsBFWPIntermittent.Set(BoolValue);
						std::cout << "IsBFWPIntermittent: " << BoolValue	<< std::endl;
					}

					colData = rowData.GetColumn("OperatingHoursPerDay");
					if (colData.get() != NULL) {
						colData->AsInt(IntValue);
						OperatingHoursPerDay.Set(IntValue);
						std::cout << "OperatingHoursPerDay: " << IntValue
								<< std::endl;
					}
					colData = rowData.GetColumn("ReferenceIntervalForTreatmentPump");
					if (colData.get() != NULL)
					{
						colData->AsInt(IntValue);
						ReferenceIntervalForTreatmentPump.Set(IntValue);
						std::cout << "ReferenceIntervalForTreatmentPump: "<< IntValue << std::endl;
					}

					colData = rowData.GetColumn("TreatmentPumpCalibrationValue");
					if (colData.get() != NULL)
					{
						colData->AsFloat(RealValue);
						TreatmentPumpCalibrationValue.Set(RealValue);
						std::cout << "TreatmentPumpCalibrationValue: "<< RealValue << std::endl;
					}

					colData = rowData.GetColumn("BFWPSignalFilterTime");
					if (colData.get() != NULL)
					{
						colData->AsInt(IntValue);
						BFWPSignalFilterTime.Set(IntValue);
						std::cout << "BFWPSignalFilterTime: " << IntValue << std::endl;
					}

					colData = rowData.GetColumn("MaxTimeBetweenBFWPCallsInHours");
					if (colData.get() != NULL)
					{
						colData->AsInt(IntValue);
						MaxTimeBetweenBFWPCallsInHours.Set(IntValue);
						std::cout << "MaxTimeBetweenBFWPCallsInHours: "	<< IntValue << std::endl;
					}

					colData = rowData.GetColumn("BaselineConductivity");
					if (colData.get() != NULL)
					{
						colData->AsFloat(RealValue);
						BaselineConductivity.Set(RealValue);
						std::cout << "BaselineConductivity: " << RealValue<< std::endl;
					}

                    colData = rowData.GetColumn("IsSystemInitialized");
                    if(colData.get() != NULL)
                    {
                        colData->AsBool(BoolValue);
                        IsSystemInitialized.Set(BoolValue);
                        std::cout << "IsSystemInitialized: " << BoolValue << std::endl;
                    }

                    colData = rowData.GetColumn("VirtualCounterVolumeInGallon");
					if (colData.get() != NULL)
					{
						colData->AsFloat(RealValue);
						VirtualCounterVolumeInGallon.Set(RealValue);
						std::cout << "VirtualCounterVolumeInGallon: "<< RealValue << std::endl;
					}
					colData = rowData.GetColumn("SumpLowToFullVolumeInGallon");
					if (colData.get() != NULL)
					{
						colData->AsFloat(RealValue);
						SumpLowToFullVolumeInGallon.Set(RealValue);
						std::cout << "SumpLowToFullVolumeInGallon: "<< RealValue << std::endl;
					}

					colData = rowData.GetColumn("SumpFullToOverFlowVolumeInGallon");
					if (colData.get() != NULL)
					{
						colData->AsFloat(RealValue);
						SumpFullToOverFlowVolumeInGallon.Set(RealValue);
						std::cout << "SumpFullToOverFlowVolumeInGallon: "<< RealValue << std::endl;
					}

					colData = rowData.GetColumn("SumpOverFlowToAboveVolumeInGallon");
					if (colData.get() != NULL)
					{
						colData->AsFloat(RealValue);
						SumpOverFlowToAboveVolumeInGallon.Set(RealValue);
						std::cout << "SumpOverFlowToAboveVolumeInGallon: "<< RealValue << std::endl;
					}

					/* TODO colData = rowData.GetColumn("TimeDateOfStartOfLastFillEvent");
					if (colData.get() != NULL)
					{
						colData->AsInt(IntValue);
						TimeDateOfStartOfLastFillEvent.Set(IntValue);
						std::cout << "TimeDateOfStartOfLastFillEvent: " << IntValue << std::endl;
					}

					colData = rowData.GetColumn("TimeDateOfLastBFWPSignalReceived");
					if (colData.get() != NULL)
					{
						colData->AsInt(IntValue);
						TimeDateOfLastBFWPSignalReceived.Set(IntValue);
						std::cout << "TimeDateOfLastBFWPSignalReceived: "<< IntValue << std::endl;
					}*/

					/*TODO
					colData = rowData.GetColumn("TimeDatePowerOn");
					if (colData.get() != NULL)
					{
						colData->AsInt(IntValue);
						TimeDatePowerOn.Set(IntValue);
						std::cout << "TimeDatePowerOn: " << IntValue << std::endl;
					}

					colData = rowData.GetColumn("CausticRinseStartTime");
					if (colData.get() != NULL)
					{
						colData->AsInt(IntValue);
						CausticRinseStartTime.Set(IntValue);
						std::cout << "CausticRinseStartTime: " << IntValue << std::endl;
					}
					colData = rowData.GetColumn("CausticRinseFinishTime");
					if (colData.get() != NULL)
					{
						colData->AsInt(IntValue);
						CausticRinseFinishTime.Set(IntValue);
						std::cout << "CausticRinseFinishTime: " << IntValue	<< std::endl;
					}*/


                    if(IsSystemInitialized.Get()==True)
                    {
						colData = rowData.GetColumn("BoilerPressure");
						if (colData.get() != NULL)
						{
							colData->AsFloat(RealValue);
							BoilerPressure.Set(RealValue);
							std::cout << "BoilerPressure: " << RealValue << std::endl;
						}
						colData = rowData.GetColumn("FWTemperature");
						if (colData.get() != NULL)
						{
							colData->AsFloat(RealValue);
							FWTemperature.Set(RealValue);
							std::cout << "FWTemperature: " << RealValue	<< std::endl;
						}

						colData = rowData.GetColumn("DAOperatingPressure");
						if (colData.get() != NULL)
						{
							colData->AsFloat(RealValue);
							DAOperatingPressure.Set(RealValue);
							std::cout << "DAOperatingPressure: " << RealValue << std::endl;
						}


						colData = rowData.GetColumn("NominalSteamFlow");
						if (colData.get() != NULL)
						{
							colData->AsFloat(RealValue);
							NominalSteamFlow.Set(RealValue);
							std::cout << "NominalSteamFlow: " << RealValue << std::endl;
						}

						colData = rowData.GetColumn("TotalCondensateReturn");
						if (colData.get() != NULL)
						{
							colData->AsFloat(RealValue);
							TotalCondensateReturn.Set(RealValue);
							std::cout << "TotalCondensateReturn: " << RealValue	<< std::endl;
						}


						colData = rowData.GetColumn("MaxTimeForFillEventToComplete");
						if (colData.get() != NULL)
						{
							colData->AsInt(IntValue);
							MaxTimeForFillEventToComplete.Set(IntValue);
							std::cout << "MaxTimeForFillEventToComplete: " << IntValue << std::endl;
						}


						colData = rowData.GetColumn("TimeBetweenBFWPEvents");
						if (colData.get() != NULL)
						{
							colData->AsFloat(RealValue);
							TimeBetweenBFWPEvents.Set(RealValue);
							std::cout << "TimeBetweenBFWPEvents: " << RealValue	<< std::endl;
						}


                    }
					retValue = True;

			    }
			    else
			    {
				    std::cout << "[DB] ERROR GetSystemData returned " << rowData.GetNumberOfColumns() << " columns. Expected 1 or more" << std::endl;
			    }

			}
			else
			{
				std::cout << "[DB] ERROR GetSystemData returned " << dataSet.GetNumberOfRows() << " rows. Expected 1." << std::endl;
			}
		}
		else
		{
			std::cout << "[DB] ERROR: Execute the stored procedure GetSystemData." << std::endl;
		}
    }
    else
    {
		std::cout << "[DB] ERROR: Can't connect to DB." << std::endl;
	}


	if (retValue)
	{
        /*
            Write the machine data to a flat file.
        */
        WriteSystemDataToFile();
	}
	else
    {
	    /*
	        Database machine data are not available.
	        Read the machine data fom the flat file.
	    */
		std::cout << "Reading system data values from a flat file" << std::endl;
        ReadSystemDataFromFile();
        retValue = True;

    }

    myDBAccess.DBDisconnect();

	return retValue;
}



BOOLEAN Garfunkel::SystemData::ReadSystemDataFromFile()
{
    BOOLEAN retValue = False;


    std::fstream    valuesRead("/usr/local/applications/Garfunkel-systemdata.txt", std::ios_base::in );

    if(True == valuesRead.is_open())
    {
        REAL64       RealValue;
        int          IntValue;
        std::stringstream StringStreamValue;
        std::string StringValue;
        // System Data

        valuesRead >> IntValue;
        Garfunkel::SystemData::SetPrimaryLanguage(IntValue);

        valuesRead >> IntValue;
        Garfunkel::SystemData::SetTMLanguage(IntValue);

        valuesRead >> IntValue;
        Garfunkel::SystemData::SetUnitOfMeasurement(IntValue);

        valuesRead >> IntValue;
		OperatingModeID.Set(IntValue);

        valuesRead >> IntValue;
		IsDeareatorPresent.Set(static_cast<BOOLEAN> (IntValue));

		valuesRead >> RealValue;
		CyclesOfConcentrationTarget.Set(RealValue);

        valuesRead >> IntValue;
        IsBFWPIntermittent.Set(static_cast<BOOLEAN> (IntValue));

        valuesRead >> IntValue;
        OperatingHoursPerDay.Set(IntValue);

        valuesRead >> IntValue;
		ReferenceIntervalForTreatmentPump.Set(IntValue);

        valuesRead >> RealValue;
        TreatmentPumpCalibrationValue.Set(RealValue);

        valuesRead >> IntValue;
        BFWPSignalFilterTime.Set(IntValue);

        valuesRead >> IntValue;
        MaxTimeBetweenBFWPCallsInHours.Set(IntValue);

        valuesRead >> RealValue;
        BaselineConductivity.Set(RealValue);


        valuesRead >> IntValue;
        IsSystemInitialized.Set(static_cast<BOOLEAN> (IntValue));

        valuesRead >> RealValue;
        VirtualCounterVolumeInGallon.Set(RealValue);

        valuesRead >> RealValue;
        SumpLowToFullVolumeInGallon.Set(RealValue);

        valuesRead >> RealValue;
        SumpFullToOverFlowVolumeInGallon.Set(RealValue);

        valuesRead >> RealValue;
        SumpOverFlowToAboveVolumeInGallon.Set(RealValue);

        /* TODO
         *
        valuesRead >> RealValue;
       	TimeDateOfStartOfLastFillEvent.Set(RealValue);

        valuesRead >> RealValue;
        SumpOverFlowToAboveVolumeInGallon.Set(RealValue);

        valuesRead >> RealValue;
        TimeDatePowerOn.Set(RealValue);

        valuesRead >> RealValue;
        CausticRinseStartTime.Set(RealValue);

        valuesRead >> RealValue;
        CausticRinseFinishTime.Set(RealValue);
         */

        if(IsSystemInitialized.Get()==True)
        {

            valuesRead >> RealValue;
        	BoilerPressure.Set(RealValue);

            valuesRead >> RealValue;
            FWTemperature.Set(RealValue);

            valuesRead >> RealValue;
            DAOperatingPressure.Set(RealValue);

            valuesRead >> RealValue;
            NominalSteamFlow.Set(RealValue);

            valuesRead >> RealValue;
            TotalCondensateReturn.Set(RealValue);

            valuesRead >> RealValue;
            MaxTimeForFillEventToComplete.Set(RealValue);

            valuesRead >> RealValue;
            TimeBetweenBFWPEvents.Set(RealValue);
        }

        valuesRead.close();
        retValue = True;
    }
    else
    {
        std::cout << "ERROR: Can't open Garfunkel-systemdata.txt." << std::endl;
    }

    return retValue;

}

/*!
    \brief  Persist the system data to a flatfile

    This flat file is used to load the machine data incase the database is not
    immediately available.

    \param[in]  None

    \param[out] None

    \return     True if the flat file is written

    \throw      None
*/
BOOLEAN Garfunkel::SystemData::WriteSystemDataToFile()
{

    BOOLEAN         retValue = False;

    std::fstream    valuesWrite("/usr/local/applications/Garfunkel-systemdata.txt", std::ios_base::trunc | std::ios_base::out);

    if(True == valuesWrite.is_open())
    {
        // Scope lock the
        int          IntValue;
        REAL64       RealValue;
        BOOLEAN      BoolValue;
        std::string StringValue;

        // System Data
		IntValue = Garfunkel::SystemData::GetPrimaryLanguage();
        valuesWrite << IntValue << std::endl;

		IntValue =  Garfunkel::SystemData::GetTMLanguage();
        valuesWrite << IntValue << std::endl;

		IntValue = Garfunkel::SystemData::GetUnitOfMeasurement();
        valuesWrite << IntValue << std::endl;


        /*if(ReadLocaleInfoSystemDataFromDatabase()==True)
        {
        	StringValue = _primaryLanguageLocale;
        	valuesWrite << StringValue << std::endl;

        	StringValue = _secondaryLanguageLocale;
        	valuesWrite << StringValue << std::endl;

        	StringValue = _TMLanguageLocale;
        	valuesWrite << StringValue << std::endl;

        	StringValue = _primaryLanguageFont;
        	valuesWrite << StringValue << std::endl;

        	StringValue = _secondaryLanguageFont;
        	valuesWrite << StringValue << std::endl;

        	StringValue = _TMLanguageFont;
        	valuesWrite << StringValue << std::endl;

        	IntValue = _primaryLanguageFontPointSize.Get();
            valuesWrite << IntValue << std::endl;

        	IntValue = _secondaryLanguageFontPointSize.Get();
            valuesWrite << IntValue << std::endl;

        	IntValue = _TMLanguageFontPointSize.Get();
            valuesWrite << IntValue << std::endl;

        	IntValue = _primaryLanguageFontBold.Get();
            valuesWrite << IntValue << std::endl;

        	IntValue = _secondaryLanguageFontBold.Get();
            valuesWrite << IntValue << std::endl;

        	IntValue = _TMLanguageFontBold.Get();
            valuesWrite << IntValue << std::endl;

        	StringValue = _primaryLanguageFallbackFont;
        	valuesWrite << StringValue << std::endl;

        	IntValue = _primaryLanguageFallbackFontPointSize.Get();
            valuesWrite << IntValue << std::endl;

        	IntValue = _primaryLanguageFallbackFontBold.Get();
            valuesWrite << IntValue << std::endl;

        }

        if(ReadPasswordInfoFromDatabase()==True)
        {
        	StringValue = _TMPassword;
        	valuesWrite << StringValue << std::endl;

        	StringValue = _secretTMPassword;
        	valuesWrite << StringValue << std::endl;

        	StringValue = _custPassword;
        	valuesWrite << StringValue << std::endl;
        }*/

		IntValue = OperatingModeID.Get();
        valuesWrite << IntValue << std::endl;

		IntValue = static_cast<int> (IsDeareatorPresent.Get());
        valuesWrite << IntValue << std::endl;

        RealValue = CyclesOfConcentrationTarget.Get();
        valuesWrite << RealValue << std::endl;

		IntValue = static_cast<int> (IsBFWPIntermittent.Get());
        valuesWrite << IntValue << std::endl;

		IntValue = OperatingHoursPerDay.Get();
        valuesWrite << IntValue << std::endl;

		IntValue = ReferenceIntervalForTreatmentPump.Get();
        valuesWrite << IntValue << std::endl;

        RealValue = TreatmentPumpCalibrationValue.Get();
        valuesWrite << RealValue << std::endl;

		IntValue = BFWPSignalFilterTime.Get();
        valuesWrite << IntValue << std::endl;

		IntValue = MaxTimeBetweenBFWPCallsInHours.Get();
        valuesWrite << IntValue << std::endl;

        RealValue = BaselineConductivity.Get();
        valuesWrite << RealValue << std::endl;

		IntValue = static_cast<int> (IsSystemInitialized.Get());
        valuesWrite << IntValue << std::endl;

        RealValue = VirtualCounterVolumeInGallon.Get();
        valuesWrite << RealValue << std::endl;

        RealValue = SumpLowToFullVolumeInGallon.Get();
        valuesWrite << RealValue << std::endl;

        RealValue = SumpFullToOverFlowVolumeInGallon.Get();
        valuesWrite << RealValue << std::endl;

        RealValue = SumpOverFlowToAboveVolumeInGallon.Get();
        valuesWrite << RealValue << std::endl;

        /* TODO
        RealValue = TimeDateOfStartOfLastFillEvent.Get();
        valuesWrite << RealValue << std::endl;

        RealValue = SumpOverFlowToAboveVolumeInGallon.Get();
        valuesWrite << RealValue << std::endl;

        RealValue = TimeDatePowerOn.Get();
        valuesWrite << RealValue << std::endl;

        RealValue = CausticRinseStartTime.Get();
        valuesWrite << RealValue << std::endl;

        RealValue = CausticRinseFinishTime.Get();
        valuesWrite << RealValue << std::endl;


         */

        if(IsSystemInitialized.Get()==True)
        {

            RealValue = BoilerPressure.Get();
            valuesWrite << RealValue << std::endl;

            RealValue = FWTemperature.Get();
            valuesWrite << RealValue << std::endl;

            RealValue = DAOperatingPressure.Get();
            valuesWrite << RealValue << std::endl;

            RealValue = NominalSteamFlow.Get();
            valuesWrite << RealValue << std::endl;

            RealValue = TotalCondensateReturn.Get();
            valuesWrite << RealValue << std::endl;

            RealValue = MaxTimeForFillEventToComplete.Get();
            valuesWrite << RealValue << std::endl;

            RealValue = TimeBetweenBFWPEvents.Get();
            valuesWrite << RealValue << std::endl;

        }

        valuesWrite.close();
        retValue = True;
    }
    return retValue;
}


BOOLEAN Garfunkel::SystemData::ReadLocaleInfoSystemDataFromDatabase()
{
    ecolab::DB::DBAccess    myDBAccess;
    std::string             connectString;
    BOOLEAN                 retValue = True;

    // Use of the connection string.
    connectString = "dbname = 'Garfunkel' user = 'db_controller' password = 'controller'";

    /* Connect to DB if it is not connected. */
    if (NULL == myDBAccess.DBisConnected())
    {
        myDBAccess.DBConnect(connectString, 5);
    }

    if(NULL != myDBAccess.DBisConnected())
    {

        ecolab::DB::DataSet        dataSet;
        std::string                sql = "SELECT * from GetLanguageDisplayLocales()";

        if(myDBAccess.DBExecuteStored(sql, dataSet))
        {
           if(dataSet.GetNumberOfRows() == 1)
            {
                boost::shared_ptr<ecolab::DB::IColumnData>    colData;
			    ecolab::DB::DataRow row(dataSet.GetFirstRow());
			    std::string StringVal;
			    BOOLEAN BoolValue;
			    int IntVal=26; //default font point size
                if(row.GetNumberOfColumns() > 0)
                {
                    boost::shared_ptr<ecolab::DB::IColumnData>  column = row.GetColumn("primarylang");
                    if(NULL != column.get())
                    {
                         column->AsString(StringVal);
                         _primaryLanguageLocale.assign(StringVal);
                    }

                    column = row.GetColumn("secondarylang");
                    if(NULL != column.get())
                    {
                         column->AsString(StringVal);
                         _secondaryLanguageLocale.assign(StringVal);
                    }

                    column = row.GetColumn("programminglang");
                    if(NULL != column.get())
                    {
                         column->AsString(StringVal);
                         _TMLanguageLocale.assign(StringVal);
                    }

                    column = row.GetColumn("primarylangfont");
                    if(NULL != column.get())
                    {
                         column->AsString(StringVal);
                         _primaryLanguageFont.assign(StringVal);
                    }

                    column = row.GetColumn("secondarylangfont");
                    if(NULL != column.get())
                    {
                         column->AsString(StringVal);
                         _secondaryLanguageFont.assign(StringVal);
                    }
                    column = row.GetColumn("programminglangfont");
                    if(NULL != column.get())
                    {
                         column->AsString(StringVal);
                         _TMLanguageFont.assign(StringVal);
                    }
                    column = row.GetColumn("primarylangfontpointsize");
                    if(NULL != column.get())
                    {
                         column->AsInt(IntVal);
                         _primaryLanguageFontPointSize.Set(IntVal);
                    }
                    column = row.GetColumn("secondarylangfontpointsize");
                    if(NULL != column.get())
                    {
                         column->AsInt(IntVal);
                         _secondaryLanguageFontPointSize.Set(IntVal);
                    }
                    column = row.GetColumn("programminglangfontpointsize");
                    if(NULL != column.get())
                    {
                         column->AsInt(IntVal);
                         _TMLanguageFontPointSize.Set(IntVal);
                    }

                    column = row.GetColumn("primarylangfontbold");
                    if(NULL != column.get())
                    {
                         column->AsBool(BoolValue);
                         _primaryLanguageFontBold.Set(BoolValue);
                    }

                    column = row.GetColumn("secondarylangfontbold");
                    if(NULL != column.get())
                    {
                         column->AsBool(BoolValue);
                         _secondaryLanguageFontBold.Set(BoolValue);
                    }

                    column = row.GetColumn("programminglangfontbold");
                    if(NULL != column.get())
                    {
                         column->AsBool(BoolValue);
                         _TMLanguageFontBold.Set(BoolValue);
                    }

                    column = row.GetColumn("primarylangfallbackfont");
                    if(NULL != column.get())
                    {
                         column->AsString(StringVal);
                         _primaryLanguageFallbackFont.assign(StringVal);
                    }

                    column = row.GetColumn("primarylangfallbackfontpointsize");
                    if(NULL != column.get())
                    {
                         column->AsInt(IntVal);
                         _primaryLanguageFallbackFontPointSize.Set(IntVal);
                    }

                    column = row.GetColumn("primarylangfallbackfontbold");
                    if(NULL != column.get())
                    {
                         column->AsBool(BoolValue);
                         _primaryLanguageFallbackFontBold.Set(BoolValue);
                    }


                }
            }
        }
    }


    return retValue;
}

BOOLEAN Garfunkel::SystemData::ReadPasswordInfoFromDatabase()
{
    ecolab::DB::DBAccess    myDBAccess;
    std::string             connectString;
    BOOLEAN                 retValue = True;

    // Use of the connection string.
    connectString = "dbname = 'Garfunkel' user = 'db_controller' password = 'controller'";

    /* Connect to DB if it is not connected. */
    if (NULL == myDBAccess.DBisConnected())
    {
        myDBAccess.DBConnect(connectString, 5);
    }

    if(NULL != myDBAccess.DBisConnected())
    {

        ecolab::DB::DataSet        dataSet;
        std::string                sql = "SELECT * from GetPasswords()";

        if(myDBAccess.DBExecuteStored(sql, dataSet))
        {
           if(dataSet.GetNumberOfRows() == 1)
            {
                boost::shared_ptr<ecolab::DB::IColumnData>    colData;
			    ecolab::DB::DataRow row(dataSet.GetFirstRow());
			    std::string StringVal;
			    BOOLEAN BoolValue;
			    int IntVal=26; //default font point size
                if(row.GetNumberOfColumns() > 0)
                {
                    boost::shared_ptr<ecolab::DB::IColumnData>  column = row.GetColumn("TMPassword");
                    if(NULL != column.get())
                    {
                         column->AsString(StringVal);
                         _TMPassword.assign(StringVal);
                    }

                    column = row.GetColumn("SecretTMPassword");
                    if(NULL != column.get())
                    {
                         column->AsString(StringVal);
                         _secretTMPassword.assign(StringVal);
                    }

                    column = row.GetColumn("CustomerPassword");
                    if(NULL != column.get())
                    {
                         column->AsString(StringVal);
                         _custPassword.assign(StringVal);
                    }

                }
            }
        }
    }


    return retValue;
}
