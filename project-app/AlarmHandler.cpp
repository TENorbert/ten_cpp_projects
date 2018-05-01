#include <bitset>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "ElapsedTime.h"
#include "GarfunkelData.h"
#include "GarfunkelIPC.h"
#include "Alarm.h"
#include "AlarmHandler.h"
#include "GarfunkelEnums.h"
#include "DatabaseManager.h"
#include "EventlogManager.h"


/******************************************************************************

    Garfunkel::AlarmSettings class definitions.

******************************************************************************/

Garfunkel::AlarmSettings&  Garfunkel::AlarmSettings::Instance()
{
	static AlarmSettings  singleton;
	return singleton;
}


/*!
    Constructor method for AlarmSettings.

    \param[out] None

    \return     None
*/
Garfunkel::AlarmSettings::AlarmSettings()
{
    boost::shared_ptr<IOSimonCommunicationAlarm> ioSimonCommAlarm(new IOSimonCommunicationAlarm(30,0,0,0,0,0)); //TODO : Update all actiovation time to ones from db
    boost::shared_ptr<IOGarfunkelCommunicationAlarm> ioGarfunkelCommAlarm(new IOGarfunkelCommunicationAlarm(30,0,0,0,0,0));
    boost::shared_ptr<OverHighTempAlarm> overHighTempAlarm(new OverHighTempAlarm(10,20,0,10,20,0));
    boost::shared_ptr<SumpOverFlowAlarm> sumpOverflowAlarm(new SumpOverFlowAlarm(10,20,0,10,20,0));
    boost::shared_ptr<NoORemainsInBothCapsuleAlarm> noORemainsAlarm(new NoORemainsInBothCapsuleAlarm(10,20,0,10,20,0));
    boost::shared_ptr<EmptySumpAlarm> emptySumpAlarm(new EmptySumpAlarm(10,20,0,10,20,0));
    boost::shared_ptr<LowMakeupPressureAlarm> lowPressureAlarm(new LowMakeupPressureAlarm(10,20,0,10,20,0));
    boost::shared_ptr<HighTempAlarm> highTempAlarm(new HighTempAlarm(10,20,0,10,20,0));
    boost::shared_ptr<LowTempAlarm> lowTempAlarm(new LowTempAlarm(10,20,0,10,20,0));
    boost::shared_ptr<O1CapsuleLidOpenAlarm> o1LidOpenAlarm(new O1CapsuleLidOpenAlarm(10,20,0,10,20,0));
    boost::shared_ptr<O2CapsuleLidOpenAlarm> o2LidOpenAlarm(new O2CapsuleLidOpenAlarm(10,20,0,10,20,0));
    boost::shared_ptr<SBlockLidOpenAlarm> sLidOpenAlarm(new SBlockLidOpenAlarm(10,20,0,10,20,0));
    boost::shared_ptr<PBlockLidOpenAlarm> pLidOpenAlarm(new PBlockLidOpenAlarm(10,20,0,10,20,0));
    boost::shared_ptr<O1ProductEmptyAlarm> o1ProductEmptyAlarm(new O1ProductEmptyAlarm(10,20,0,10,20,0));
    boost::shared_ptr<O2ProductEmptyAlarm> o2ProductEmptyAlarm(new O2ProductEmptyAlarm(10,20,0,10,20,0));
    boost::shared_ptr<SProductEmptyAlarm> sProductEmptyAlarm(new SProductEmptyAlarm(10,20,0,10,20,0));
    boost::shared_ptr<PProductEmptyAlarm> pProductEmptyAlarm(new PProductEmptyAlarm(10,20,0,10,20,0));
    boost::shared_ptr<SLowPProductAlarm> sLowProductAlarm(new SLowPProductAlarm(10,20,0,10,20,0));
    boost::shared_ptr<PLowPProductAlarm> pLowProductAlarm(new PLowPProductAlarm(10,20,0,10,20,0));

    overHighTempAlarm->SetAlarmLowLevel(GARFUNKEL_OVER_HIGH_TEMP);
    overHighTempAlarm->SetAlarmHighLevel(2*GARFUNKEL_OVER_HIGH_TEMP);


    sumpOverflowAlarm->SetAlarmLowLevel((double)eOverflow);
    sumpOverflowAlarm->SetAlarmHighLevel((double)eOverflow+1);

    emptySumpAlarm->SetAlarmLowLevel((double)eVirtual);
    emptySumpAlarm->SetAlarmHighLevel((double)eLow);

    lowPressureAlarm->SetAlarmLowLevel((double)eOpen);
    lowPressureAlarm->SetAlarmHighLevel((double)eOpen+1);

    highTempAlarm->SetAlarmLowLevel(GARFUNKEL_HIGH_TEMP);
    highTempAlarm->SetAlarmHighLevel(GARFUNKEL_OVER_HIGH_TEMP);


    lowTempAlarm->SetAlarmLowLevel(GARFUNKEL_LOW_TEMP*(-1)); //35F
    lowTempAlarm->SetAlarmHighLevel(GARFUNKEL_LOW_TEMP); //-35

    o1LidOpenAlarm->SetAlarmLowLevel(eSwitchOpen);
    o1LidOpenAlarm->SetAlarmHighLevel(eSwitchOpen+1);

    o2LidOpenAlarm->SetAlarmLowLevel(eSwitchOpen);
    o2LidOpenAlarm->SetAlarmHighLevel(eSwitchOpen+1);

    sLidOpenAlarm->SetAlarmLowLevel(eSwitchOpen);
    sLidOpenAlarm->SetAlarmHighLevel(eSwitchOpen+1);

    pLidOpenAlarm->SetAlarmLowLevel(eSwitchOpen);
    pLidOpenAlarm->SetAlarmHighLevel(eSwitchOpen+1);

    /* TODO - Shilpa, set the levels
    o1ProductEmptyAlarm->SetAlarmLowLevel(eSwitchOpen);
    o1ProductEmptyAlarm->SetAlarmHighLevel(eSwitchOpen+1);

    o2ProductEmptyAlarm->SetAlarmLowLevel(eSwitchOpen);
    o2ProductEmptyAlarm->SetAlarmHighLevel(eSwitchOpen+1);

	sProductEmptyAlarm->SetAlarmLowLevel(eSwitchOpen);
    sProductEmptyAlarm->SetAlarmHighLevel(eSwitchOpen+1);

    pProductEmptyAlarm->SetAlarmLowLevel(eSwitchOpen);
    pProductEmptyAlarm->SetAlarmHighLevel(eSwitchOpen+1);*/

    sLowProductAlarm->SetAlarmLowLevel(1);
    sLowProductAlarm->SetAlarmHighLevel(2);

    pLowProductAlarm->SetAlarmLowLevel(1);
    pLowProductAlarm->SetAlarmHighLevel(2);

    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_SIMON_IO_COMM_ERROR, ioSimonCommAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_GARFUNKEL_IO_COMM_ERROR, ioGarfunkelCommAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_OVER_HIGH_TEMP, overHighTempAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_SUMP_OVERFLOW, sumpOverflowAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_NO_O_REMAINS, noORemainsAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_EMPTY_SUMP, emptySumpAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_LOW_MAKEUP_PRESSURE, lowPressureAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_HIGH_TEMP, highTempAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_LOW_TEMP, lowTempAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_O1_LID_OPEN, o1LidOpenAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_O2_LID_OPEN, o2LidOpenAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_S_LID_OPEN, sLidOpenAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_P2_LID_OPEN, pLidOpenAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_O1_PRODUCT_EMPTY, o1ProductEmptyAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_O2_PRODUCT_EMPTY, o2ProductEmptyAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_S_PRODUCT_EMPTY, sProductEmptyAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_P2_PRODUCT_EMPTY, pProductEmptyAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_S_LOW_PRODUCT, sLowProductAlarm));
    _alarms.insert(std::pair<AlarmType, boost::shared_ptr<GarfunkelAlarm> >(ALARM_TYPE_P2_LOW_PRODUCT, pLowProductAlarm));

	GarIOBoardCommunicationAlarm.Set(False);
	SimonIOBoardCommunicationAlarm.Set(False);
	ESRAlarmCount.Set(0);


}



/*!
    Destructor method for AlarmSettings.

    \param[in]  None

    \param[out] None

    \return     None
*/
Garfunkel::AlarmSettings::~AlarmSettings()
{
//std::cout << "[AlarmSettings] The destructor has been called" << std::endl;
    /*
        Empty.
    */
    _alarms.erase(_alarms.begin(), _alarms.end());
}

std::string Garfunkel::AlarmSettings::AlarmTypeRange(AlarmType type)
{
    std::string str;
    std::ostringstream out;

    if(_alarms.count(type) > 0)
    {
    	boost::shared_ptr<Alarm> alarm = _alarms[type];

    	std::string alarmName(AlarmTypeToString(type).substr(0, 15));
    	out << alarmName << (alarmName.length() < 8 ? "\t\t" : "\t");
        out << alarm->GetAlarmLowLevel() << "\t\t";
        out << alarm->GetAlarmHighLevel();
    }
    return out.str();
}


std::string Garfunkel::AlarmSettings::AlarmTypeProperties(AlarmType type)
{

    std::string str;
    std::ostringstream out;

    if(_alarms.count(type) > 0)
    {
    	boost::shared_ptr<GarfunkelAlarm> alarm = _alarms[type];

    	std::string alarmName(AlarmTypeToString(type).substr(0, 15));
    	out << alarmName << (alarmName.length() < 8 ? "\t\t" : "\t");

    	out << alarm->GetAlertTimeThreshold() << "\t\t";
    	out << alarm->GetAlarmTimeThreshold() << "\t\t\t";
    	out << alarm->GetEnvisionAlarmTimeThreshold() << "\t\t";
    	out << alarm->GetAlertDeactivationTimeThreshold() << "\t\t";
    	out << alarm->GetAlarmDeactivationTimeThreshold() << "\t\t\t";
    	out << alarm->GetEnvisionAlarmDeactivationTimeThreshold() << "\t\t";
    	out << alarm->GetEnvisionEnableState() << "\t\t";
    	out << alarm->GetStopSumpCreationState() << "\t\t\t";
    	out << alarm->GetStopDispenseState();
    	out << std::endl;
    }

    return out.str();

}

/*!
    Method to fetch the alarm settings from the database.

    \param[in]  None

    \param[out] None

    \return     None
*/
void Garfunkel::AlarmSettings::FetchAlarmSettingsFromDB()
{

	GarfunkelDB GarfunkelDBObj;
    ecolab::DB::DataSet dataSet;
    GarfunkelDBObj.executeSQL("SELECT * FROM GetAlarmSettings();", dataSet);

    const int rowCount = dataSet.GetNumberOfRows();
    std::cout<< "rowCount="<<rowCount<<std::endl;
    for(int row = 0; row < rowCount; ++row)
    {
        ecolab::DB::DataRow rowData(dataSet.GetRow(row));
        boost::shared_ptr<ecolab::DB::IColumnData> colData;

        if(rowData.GetNumberOfColumns() > 0)
        {
        	colData = rowData.GetColumn("AlarmID");
			int alarmId;
			colData->AsInt(alarmId);

			colData = rowData.GetColumn("IsEnvisionConfigurable"); //not used as there will be no config of alarms from envision
			BOOLEAN isEnvisionConfigurable;
			colData->AsBool(isEnvisionConfigurable);

			colData = rowData.GetColumn("IsEnvisionEnabled");
			BOOLEAN isEnvisionEnabled;
			colData->AsBool(isEnvisionEnabled);

			colData = rowData.GetColumn("ActivationDelay");
			int activationDelay;
			colData->AsInt(activationDelay);

			colData = rowData.GetColumn("ActivationCondorDelay");
			int activationCondorDelay;
			colData->AsInt(activationCondorDelay);

			colData = rowData.GetColumn("ActivationEnvisionDelay");
			int activationEnvisionDelay;
			colData->AsInt(activationEnvisionDelay);

			colData = rowData.GetColumn("StopSumpCreation");
			BOOLEAN stopSumpCreation;
			colData->AsBool(stopSumpCreation);

			colData = rowData.GetColumn("StopDispenseOperation");
			BOOLEAN stopDispenseOperation;
			colData->AsBool(stopDispenseOperation);

			colData = rowData.GetColumn("DeactivationDelay");
			int deactivationDelay;
			colData->AsInt(deactivationDelay);

			colData = rowData.GetColumn("DeactivationCondorDelay");
			int deactivationCondorDelay;
			colData->AsInt(deactivationCondorDelay);

			colData = rowData.GetColumn("DeactivationEnvisionDelay");
			int deactivationEnvisionDelay;
			colData->AsInt(deactivationEnvisionDelay);

			boost::shared_ptr<GarfunkelAlarm> alarm = GetAlarmByType((AlarmType) alarmId);
			if (alarm)
			{
				//activation time
				std::cout<< "Updating alarm id="<<alarmId<<std::endl;
				alarm->SetAlertTimeThreshold(activationDelay);
				alarm->SetAlarmTimeThreshold(activationCondorDelay);
				alarm->SetEnvisionAlarmTimeThreshold(activationEnvisionDelay);

				//deactivation time
				alarm->SetAlertDeactivationTimeThreshold(deactivationDelay);
				alarm->SetAlarmDeactivationTimeThreshold(deactivationCondorDelay);
				alarm->SetEnvisionAlarmDeactivationTimeThreshold(deactivationEnvisionDelay);

				alarm->SetEnvisionEnableState(isEnvisionEnabled);
				alarm->SetStopSumpCreationState(stopSumpCreation);
				alarm->SetStopDispenseState(stopDispenseOperation);

			}
			else
			{
				std::cout<< "[AlarmSettings::FetchAlarmSettingsFromDB] alarm type was not valid"<<std::endl;
			}
        }
        else
        	std::cout<< "Col data not found"<<std::endl;

    }

    std::string     fileName = "/usr/local/applications/garfunkel-alarm.txt";


    if(GarfunkelDBObj.isConnected()==false)
    {
    	std::cout<< "Reading Alarm Settings from flat file"<<std::endl;
        std::fstream    valuesWrite(fileName.c_str(), std::ios_base::in);
    	//read from flat files
    	if(True == valuesWrite.is_open())
    	{
    		ReadAlarmSettingsFromFlatFile(valuesWrite);
    	}
    }
    else
    {
    	std::cout<< "Writing Alarm Settings to flat file"<<std::endl;
        std::fstream    valuesWrite(fileName.c_str(), std::ios_base::trunc | std::ios_base::out);
    	//read from flat files
    	if(True == valuesWrite.is_open())
    	{
    		WriteAlarmSettingsToFlatFile(valuesWrite);
    	}
    }


    GarfunkelDBObj.disconnect();
    /*
        Print alarm ranges for debugging.
    */
   PrintAlarmRanges();

}

void Garfunkel::AlarmSettings::HandleAlarmActionForTheSystem(boost::shared_ptr<GarfunkelAlarm> al)
{
  //TODO : take actions on each individual alarms here, do you want disable make sump, dispense , both and so on
	//also set system state to standby and so on
//also use garfunkellock and simon locks flags as well
//	AlarmData.ESRAlarmCount.Set() set this

}

BOOLEAN Garfunkel::AlarmSettings::IsDiagnosticsAllowed()
{
	BOOLEAN retValue = True;
	SystemData& SysData = SystemData::Instance();

	//no interlocking in effect
	if(SysData._SimonIOBoardLocked.Get()==True || SysData._GarfunkelIOBoardLocked.Get()==True ||  SysData._SimonIOBoardFaultLine.Get()==True ||  SysData._GarfunkelIOBoardFaultLine.Get()==True)
	{
		retValue = False;
	}
	//no Communications errors
	if(GetAlarmStatusByType(ALARM_TYPE_SIMON_IO_COMM_ERROR)!=Garfunkel::Alarm::ALARM_STATUS_NONE || GetAlarmStatusByType(ALARM_TYPE_SIMON_IO_COMM_ERROR)!=Garfunkel::Alarm::ALARM_STATUS_NONE )
	{
		retValue = False;

	}
	//if sump is not at high or overflow
	if(SysData.GetSumpLevelSwitchState()==eFull || SysData.GetSumpLevelSwitchState()==eOverflow)
	{
		retValue = False;
	}

	//no lids open
	if(SysData.GetOCapsuleLidState(0)==eSwitchOpen || SysData.GetOCapsuleLidState(1)==eSwitchOpen || SysData.GetSLidSwitchState()==eSwitchOpen || SysData.GetSLidSwitchState()==eSwitchOpen)
	{
		retValue = False;
	}

	return  retValue;
}


BOOLEAN Garfunkel::AlarmSettings::IsMakeSumpOperationAllowed()
{
	BOOLEAN retValue = True;

	if(IsDiagnosticsAllowed()==False)
	{
		// TODo add others he

	}
	else
	{
		retValue = False;
	}
	return  retValue;
}

BOOLEAN Garfunkel::AlarmSettings::IsDispenseAllowed()
{
	BOOLEAN retValue = True;
	return  retValue;
}

void Garfunkel::AlarmSettings::CheckAlarms()
{
    bool sendIPC(false);
    /*
        Don't check for alarms until the I/O board thread initiates communication with the I/O board.

        NOTE: this effectively disables the IO board communication error alarm for the time being.
    */
    //std::cout << "Enter Check Alarms" << std::endl;

    if(1)
    {
        std::map<AlarmType, boost::shared_ptr<GarfunkelAlarm> >::iterator it;
        for(it = _alarms.begin(); it != _alarms.end(); ++it)
        {
            boost::shared_ptr<GarfunkelAlarm> alarm = (*it).second;
            if(alarm->CheckAlarmConditions())
            {
            	//std::cout << "Inside the if block" << std::endl;

                AlarmType type((*it).first);
                Alarm::AlarmStatus status(alarm->GetStatus());

                if(Alarm::ALARM_STATUS_NONE != status)
                {
                    alarm->HandleAlarmAction();
                }
                else if(Alarm::ALARM_STATUS_NONE == status)
                {
                    alarm->CancelAlarmAction();
                }
                else
                {
                    // do nothing
                }

                std::cout << "Alarm status changed " << AlarmTypeToString(type) << " status=" << AlarmStatusToString(status) << " value=" << alarm->GetValue() << std::endl;

                HandleAlarmActionForTheSystem(alarm);
                /*
                    Log the alarm status change to the database.
                */
                LogAlarmEvent(type, status, alarm->GetValue());

                /*
                    Send the updated alarm status' to the UI.
                */
                sendIPC = true;
            }
        }

        if(true == sendIPC)
        {
std::cout << "[AlarmSettings::CheckAlarms()] sending to the IPC mechanism" << std::endl;
            SendAlarmsToUI();
        }
    }
}

/*!
    Method to return an alarm status for an alarm.

    \param[in]  type    The alarm to return the status for.

    \param[out] None

    \return     The alarm status of the alarm.
*/
Garfunkel::Alarm::AlarmStatus Garfunkel::AlarmSettings::GetAlarmStatusByType(Garfunkel::AlarmSettings::AlarmType type)
{
	Garfunkel::Alarm::AlarmStatus status(Garfunkel::Alarm::ALARM_STATUS_NONE);

    if(_alarms.count(type) > 0)
    {
        status = _alarms[type]->GetStatus();
    }

    return status;
}

/*!
    Method to return an alarm.

    \param[in]  type    The alarm to return.

    \param[out] None

    \return     the requested alarm.
*/
boost::shared_ptr<Garfunkel::GarfunkelAlarm> Garfunkel::AlarmSettings::GetAlarmByType(AlarmType type)
{
    boost::shared_ptr<GarfunkelAlarm>   requestedAlarm;

    if(_alarms.count(type) > 0)
    {
        requestedAlarm = _alarms[type];
    }
    else
    {
    	std::cout<<" Alarm not found for id="<<type<<std::endl;
    }

    return requestedAlarm;
}

/*!
    Method to log an alarm event to the EventDataLog database table.

    \param[in]  type    The type of alarm (pH, PPM, ORP, etc).
    \param[in]  status  The current status of the alarm.

    \param[out] None

    \return     None
*/
void Garfunkel::AlarmSettings::LogAlarmEvent(Garfunkel::AlarmSettings::AlarmType type, Garfunkel::Alarm::AlarmStatus status, double value)
{

	Garfunkel::EventDataLog &    log = Garfunkel::EventDataLog::Instance();

    int alarmEventDataLogID = 5;

    log.EventLog(alarmEventDataLogID, (int)type, (int)status, -1, -1, -1, -1, -1);

}

/*!
    Method to send an IPC message to the UI containing the alarm status'.

    \param[in]  None

    \param[out] None

    \return     None
*/
void Garfunkel::AlarmSettings::SendAlarmsToUI()
{
	GarfunkelIPCMaster &masterIPC = GarfunkelIPCMaster::Instance();

	//TBD : IMP Shilpa, update SRS documnet to reflect this one
    std::ostringstream out;
    out << "SU:61:";
    std::map<AlarmType, boost::shared_ptr<GarfunkelAlarm> >::iterator it;
    for(it = _alarms.begin(); it != _alarms.end(); ++it)
    {
        out<< (*it).first<<":"<< (*it).second->GetStatus()<<":";
        out << (*it).second->GetStatus();
     }

   std::string  alarmString = out.str();

    std::cout << "[AlarmSettings::SendAlarmsToUI] Status of the alarm state: " << alarmString << std::endl;

    masterIPC.SendESPCommandResponse(alarmString);
}

/*!
    Method to write out all of the individual alarm settings

    \param[in]  None

    \param[out] None

    \return     None
*/
bool    Garfunkel::AlarmSettings::WriteAlarmSettingsToFlatFile(std::fstream & outputStream)
{
    bool    retValue = false;

    if(True == outputStream.is_open())
    {
        // Write out the number of alarms.
        outputStream << _alarms.size() << std::endl;

        boost::shared_ptr<GarfunkelAlarm>   alarm;
        std::map<AlarmType, boost::shared_ptr<GarfunkelAlarm> >::iterator it;
        for(it = _alarms.begin(); it != _alarms.end(); ++it)
        {
            if(NULL != (*it).second)
            {
                alarm = (*it).second;

                // Write out the alarm type
                outputStream << (*it).first << std::endl;
                // output the alarm data
                alarm->WriteAlarmValuesToFlatFile(outputStream);
            }
        }

        retValue = true;
    }

    return retValue;
}

/*!
    Method to read in all of the individual alarm settings

    \param[in]  None

    \param[out] None

    \return     None
*/
bool    Garfunkel::AlarmSettings::ReadAlarmSettingsFromFlatFile(std::fstream &  inputStream)
{
    bool    retValue = false;

    if(True == inputStream.is_open())
    {
        int                                                      numberOfAlarms = 0;
        int                                                      alarmType = 0;
        boost::shared_ptr<GarfunkelAlarm>                                 alarm;  // The new alarm will need to get initialized with the body id.
        std::map<AlarmType, boost::shared_ptr<GarfunkelAlarm> >::iterator it;

        inputStream >> numberOfAlarms;
        for(int x = 0; x < numberOfAlarms; x++)
        {
            inputStream >> alarmType;
            std::cout << "Alarm item: " << alarmType << std::endl;
            it = _alarms.find((AlarmType)alarmType);
            if(NULL != (*it).second)
            {
                alarm = (*it).second;

                alarm->ReadAlarmValuesFromFlatFile(inputStream);
            }

        }
        retValue = true;
    }

    return retValue;
}

/*!
    Method to reset all of the current alarm settings.  Currently this is only
    called on a reset to factory defaults.

    \param[in]  None

    \param[out] None

    \return     None
*/
bool    Garfunkel::AlarmSettings::ClearAllAlarms()
{
    bool  retValue = false;

    std::cout << "[AlarmSettings] Clear all alarms" << std::endl;
    std::map<AlarmType, boost::shared_ptr<GarfunkelAlarm> >::iterator it;
    for(it = _alarms.begin(); it != _alarms.end(); ++it)
    {
       boost::shared_ptr<GarfunkelAlarm>  alarm =  (*it).second;
       if((NULL != alarm.get()) &&
            (Garfunkel::Alarm::ALARM_STATUS_NONE != alarm->GetStatus()))
       {
            alarm->SetStatus(Garfunkel::Alarm::ALARM_STATUS_NONE);
       }
    }

    // After the alarms are cleared send the updated bitfield to the UI.
    SendAlarmsToUI();

    return retValue;
}




BOOLEAN Garfunkel::AlarmSettings::ClearAllAlarmsAndResetTimeouts(BOOLEAN override)
{
	std::cout<<"AlarmStatus: ClearAllAlarms called"<<std::endl;
	SystemData& SysData = SystemData::Instance();
	GarfunkelData& AqData = GarfunkelData::Instance();
	AlarmSettings &  alarms =  AlarmSettings::Instance();

	AqData.ResetTimeouts(True);
	SysData.SetSystemState(eIdle);

	GarIOBoardCommunicationAlarm.Set(False);
	SimonIOBoardCommunicationAlarm.Set(False);
    ESRAlarmCount.Set(0);
	SendClearAlarmInfoToUI();
	alarms.ClearAllAlarms();

    return True;

}

void Garfunkel::AlarmSettings::SendClearAlarmInfoToUI()
{
 //TODO
}

/////////////////////////////////////////////////////////////////////////////
// Garfunkel Alarm handler thread
/////////////////////////////////////////////////////////////////////////////
Garfunkel::AlarmHandler::AlarmHandler(const std::string & name) : Thread(name), _continue(False)
{

}

Garfunkel::AlarmHandler::AlarmHandler(const AlarmHandler &     objectToCopy)
{
}

Garfunkel::AlarmHandler::~AlarmHandler()
{

}






int Garfunkel::AlarmHandler::Run()
{
	std::cout << "<-------------Alarm thread : Started-------------->" << std::endl;
    GarfunkelData& AqData = GarfunkelData::Instance();
    AlarmSettings &  alarms =  AlarmSettings::Instance();

    try
    {
        _continue = True;

        time_t      currentTime;
        struct tm   localTime;
        alarms.FetchAlarmSettingsFromDB();

        while(True == _continue)
        {
            if(AqData._dBSyncInProgress.Get()==False&&AqData._isMCAReady.Get()==True)
            {
                // do alarm checking
                alarms.CheckAlarms();
            }

            sleep(100);
            checkCancellation();
        }
    }
    catch(std::exception & e)
    {
        std::cout << "Error in thread " << Name() << " reason " << e.what() << std::endl;
        _continue = False;
    }
    catch(...)
    {
        std::cout << "General exception caught in Alarm Settings " << Name() << std::endl;
        assert(false);
        _continue = False;
    }
    return 0;


}

void Garfunkel::AlarmHandler::Cleanup()
{
    
}

BOOLEAN     Garfunkel::AlarmHandler::Initialize()
{
    return True;
}
