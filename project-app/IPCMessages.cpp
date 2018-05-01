#include <iostream>
#include <sstream>
#include <string>
#include <bitset>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include "GarfunkelEnums.h"
#include "GarfunkelData.h"
#include "GarfunkelIPC.h"
#include "GarfunkelCommandProcessor.h"
#include "ecolab.h"
#include "IPCMessages.h"
#include "SocketHandler.h"
#include "GarfunkelIPC.h"
#include "IOBoardMessages.h"
#include "ElapsedTime.h"
#include "AlarmHandler.h"

BOOLEAN Garfunkel::IIPCMessage::CreateESPString(std::string & dataToConvert)
{
	ecolab::ESP::ESPStringCreate    createString;
	return createString.ConvertToESPString(dataToConvert);
}

BOOLEAN Garfunkel::IIPCMessage::ConvertESPString(std::string & dataToConvert)
{
	ecolab::ESP::ESPStringCreate    convertString;
	return convertString.ConvertToESPString(dataToConvert);
}



///////////////////////////////////////////////////////////////////////////////
// Garfunkel IPC Mixin

Garfunkel::GarfunkelIPCMixin::GarfunkelIPCMixin()
{
}

Garfunkel::GarfunkelIPCMixin::~GarfunkelIPCMixin()
{
}

//////////////////////////////////////////////////////////////////////////////
// Commands for IPC


// Command DU 40
Garfunkel::SystemStateMessage::SystemStateMessage()
{
}

Garfunkel::SystemStateMessage::SystemStateMessage(const SystemStateMessage &   objectToCopy)
{
}

Garfunkel::SystemStateMessage::~SystemStateMessage()
{
}

BOOLEAN Garfunkel::SystemStateMessage::ProcessMessage(IPCCommand & command, std::string & response)
{
    BOOLEAN retValue = False;
    std::cout << "DU: System state message" << std::endl;
    if(True == command.IsDUCommand())
    {
	    std::cout <<"Recived DU "<<std::endl;
        std::stringstream strStream;
		GarfunkelSystemState systemstate;
		Garfunkel::GarfunkelData & GarfunkelData = Garfunkel::GarfunkelData::Instance();
		SystemData &   SysData = Garfunkel::SystemData::Instance();
		if(GarfunkelData._isMCAReady.Get()==True)
		systemstate = SysData.GetSystemState();
		else
		systemstate = eBootupInProgress;
        strStream << command.GetAddressAndInstance() << ":" << systemstate<< ":";
        response = strStream.str();
        CreateESPString(response);
        retValue = True;
    }

    return retValue;
}


/////////////////////////////////////////////////////////
// Command DU 41
Garfunkel::OperatingScheduleStatus::OperatingScheduleStatus()
{
}

Garfunkel::OperatingScheduleStatus::OperatingScheduleStatus(const OperatingScheduleStatus &   objectToCopy)
{
}

Garfunkel::OperatingScheduleStatus::~OperatingScheduleStatus()
{
}

BOOLEAN Garfunkel::OperatingScheduleStatus::ProcessMessage(IPCCommand & command, std::string & response)
{
    BOOLEAN retValue = False;
    std::cout << "DU: OperatingScheduleStatus message" << std::endl;

    std::cout <<"Recived DU "<<std::endl;
    std::stringstream strStream;
    GarfunkelSchedule sc;
	SystemData &   SysData = Garfunkel::SystemData::Instance();
	sc = SysData._CurrentSchedule.Get();
    strStream << command.GetAddressAndInstance() << ":" << sc<< ":";
    response = strStream.str();
    CreateESPString(response);
    retValue = True;
    return retValue;
}




/////////////////////////////////////////////////////////
// Command DU:59
Garfunkel::NoOfMachinesMessage::NoOfMachinesMessage()
{
}

Garfunkel::NoOfMachinesMessage::NoOfMachinesMessage(const NoOfMachinesMessage &   objectToCopy)
{
}

Garfunkel::NoOfMachinesMessage::~NoOfMachinesMessage()
{
}

BOOLEAN Garfunkel::NoOfMachinesMessage::ProcessMessage(IPCCommand & command, std::string & response)
{

    BOOLEAN retValue = False;
    if(True == command.IsDUCommand())
    {
	    std::cout <<"Recived DU for No of Machines"<<std::endl;
        std::stringstream strStream;
		SystemData &   Data = Garfunkel::SystemData::Instance();
        response = strStream.str();
		//std::cout <<"Sending"<<response<<std::endl;
        CreateESPString(response);
        retValue = True;
    }
    return retValue;
}


/////////////////////////////////////////////////////////
// Command DU 60
Garfunkel::NoOfPumpsMessage::NoOfPumpsMessage()
{
}

Garfunkel::NoOfPumpsMessage::NoOfPumpsMessage(const NoOfPumpsMessage &   objectToCopy)
{
}

Garfunkel::NoOfPumpsMessage::~NoOfPumpsMessage()
{
}

BOOLEAN Garfunkel::NoOfPumpsMessage::ProcessMessage(IPCCommand & command, std::string & response)
{
     BOOLEAN retValue = False;
    if(True == command.IsDUCommand())
    {
	    std::cout <<"Recived DU for No of Pumps"<<std::endl;
        std::stringstream strStream;
		SystemData &   Data = Garfunkel::SystemData::Instance();
		strStream << command.GetAddressAndInstance() << ":" << "0"<< ":";
        response = strStream.str();
		//std::cout <<"Sending"<<response<<std::endl;
        CreateESPString(response);
        retValue = True;
    }
	return retValue;
}





/////////////////////////////////////////////////////////
// Command 
Garfunkel::MakeDownProcessStateMessage::MakeDownProcessStateMessage()
{



}

Garfunkel::MakeDownProcessStateMessage::MakeDownProcessStateMessage(const MakeDownProcessStateMessage &   objectToCopy)
{



}

Garfunkel::MakeDownProcessStateMessage::~MakeDownProcessStateMessage()
{
}


/*DU Command: DU:54:<machineNo>:
Response : SignalNo:ActivePump:Next Pump

*/
BOOLEAN Garfunkel::MakeDownProcessStateMessage::ProcessMessage(IPCCommand & command, std::string & response)
{

	BOOLEAN retValue = False;
	std::stringstream strStream;
	std::string         subResponse = ":ERR1:";


    if(True == command.IsDUCommand())
        {
    	    std::cout <<"Recived DU "<<std::endl;
            std::stringstream strStream;
    		BOOLEAN state;
    		SystemData &   SysData = Garfunkel::SystemData::Instance();
    		state = SysData._MakeDownActive.Get();
            strStream << command.GetAddressAndInstance() << ":" << state<< ":";
            response = strStream.str();
            CreateESPString(response);
            retValue = True;
        }
	
	return retValue;

}



////////////////////////////////////////////////////////////////////////////////////////
// Command 

Garfunkel::AlarmStatusMessage::AlarmStatusMessage()
{
}

Garfunkel::AlarmStatusMessage::AlarmStatusMessage(const AlarmStatusMessage &   objectToCopy)
{
}

Garfunkel::AlarmStatusMessage::~AlarmStatusMessage()
{
}




BOOLEAN Garfunkel::AlarmStatusMessage::ProcessMessage(IPCCommand &command, std::string &response)
{
    response = "ERR9";

    if(command.IsDUCommand() == True)
    {
        std::vector<std::string> payloadList(command.GetPayloadList());
        if(payloadList.size() == 1)
        {
            	AlarmSettings &  alarms =  AlarmSettings::Instance();

                std::ostringstream out;
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_SIMON_IO_COMM_ERROR);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_GARFUNKEL_IO_COMM_ERROR);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_OVER_HIGH_TEMP);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_SUMP_OVERFLOW);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_NO_O_REMAINS);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_EMPTY_SUMP);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_LOW_MAKEUP_PRESSURE);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_HIGH_TEMP);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_LOW_TEMP);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_O1_LID_OPEN);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_O2_LID_OPEN);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_S_LID_OPEN);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_P2_LID_OPEN);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_O1_PRODUCT_EMPTY);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_O2_PRODUCT_EMPTY);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_S_PRODUCT_EMPTY);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_P2_PRODUCT_EMPTY);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_S_LOW_PRODUCT);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_P2_LOW_PRODUCT);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_EXCESSIVE_TIME_SINCE_SUMP_FILL);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_EXCEED_MAX_TIME_BETWEEN_BFWP_CALLS);
                out << alarms.GetAlarmStatusByType(AlarmSettings::ALARM_TYPE_INTERNET_CONNECTIVITY_LOST);

                response = out.str();
        }
        else
        {
            /*
                Invalid number of parameters in payload.
            */
            response = "ERR9";
            return False;
        }
    }

    return True;
}

///////////////////////////////////////////////////////////////////////////////////
// Command 43

Garfunkel::DiagnosticsMessage::DiagnosticsMessage()
{
	_onOff = True;
}

Garfunkel::DiagnosticsMessage::DiagnosticsMessage(const DiagnosticsMessage & objectToCopy)
{
}

Garfunkel::DiagnosticsMessage::~DiagnosticsMessage()
{
}


BOOLEAN Garfunkel::DiagnosticsMessage::ProcessMessage(IPCCommand & command, std::string & response)
{

    BOOLEAN             retValue = False;
    GarfunkelData &     AqData = Garfunkel::GarfunkelData::Instance();
	SystemData& SystemData = SystemData::Instance();
    DiagnosticSystemData& DiagData = DiagnosticSystemData::Instance();

    std::string         subResponse = ":ERR1:";
    std::stringstream   strStream,cmd;
	int     diagEnabled = -1;
	std::vector<std::string>::iterator itemsIter;
	std::vector<std::string> items;

	if(AqData._dBSyncInProgress.Get()==True)
	{
		subResponse = ":ERR11:";
		retValue = True;
	}
	else if(SystemData.DiagnosticEnabled.Get() == False) //Check if diagnostic is enabled or not, if not send error
	{
		std::cout<<"Diagnostics not enabled"<<std::endl;
		retValue = True;
	}

	else if(True == command.IsSUCommand())
    {
		items = command.GetPayloadList();
		struct timespec startTime = { };
		INT32 elapsed = 0;
		timespec Now;
		AlarmSettings &  alarms =  AlarmSettings::Instance();
		if (alarms.IsDiagnosticsAllowed()==True)
		{
			std::cout<<" here 1"<<std::endl;
			if (items.size() > 0)
			{
				itemsIter = items.begin();
				if (itemsIter != items.end())
				{
					int typeofdiag = -1;
					typeofdiag = boost::lexical_cast<int>((std::string) *itemsIter);
					if (typeofdiag >=(int)eSValve && typeofdiag<=(int) eMaxSparyObj) //Main water Flush - For 60 seconds
					{
						if (items.size() > 0)
						{
							++itemsIter;
							if (itemsIter != items.end())
							{
								int onOff = -1;
								onOff = boost::lexical_cast<int>((std::string) *itemsIter);
								if (onOff==1&&DiagData.OnRequest.Get() == False&&DiagData.WaterFlushInProgress.Get() == False&&(SystemData._sumpLevelSwitchState.Get()!=eFull&&SystemData._sumpLevelSwitchState.Get()!=eOverflow))
								{
									DiagData.OnRequest.Set(True);
									DiagData.SprayObjectRequested.Set(static_cast<GarfunkelSparyObjType> (typeofdiag));
									std::cout<< " DiagnosticsMessage: Opening main water inlet valve for max =10 seconds"	<< std::endl;
									retValue = True;
								}
								else if(onOff==0&&DiagData.WaterFlushInProgress.Get() == True&&DiagData.OnRequest.Get() == True)
								{
									DiagData.OnRequest.Set(False);
									std::cout<< " DiagnosticsMessage: Stoping  main water inlet valve"	<< std::endl;
									retValue = True;
								}

							}
						}

						if (True == retValue)
						{
							subResponse = ":OK:";
						}
						else
						{
							subResponse = ":ERR1:";
						}

					}

				}
			}

		}

	}

	strStream << command.GetAddressAndInstance() << subResponse;
    response = strStream.str();
    CreateESPString(response);
    return True;

}

///////////////////////////////////////////////////////////////////////////////////
// Command 42: enable/disable diagnostics
//DU:42  Response : 0/1  -  0 - disabled, 1 -enabled
//SU:42:0/1
Garfunkel::EnableDiagnosticsMessage::EnableDiagnosticsMessage()
{
}

Garfunkel::EnableDiagnosticsMessage::EnableDiagnosticsMessage(const EnableDiagnosticsMessage & objectToCopy)
{
}

Garfunkel::EnableDiagnosticsMessage::~EnableDiagnosticsMessage()
{
}

BOOLEAN Garfunkel::EnableDiagnosticsMessage::ProcessMessage(IPCCommand & command, std::string & response)
{
    std::stringstream strStream;
    BOOLEAN retValue = False;
    GarfunkelData &     AqData = Garfunkel::GarfunkelData::Instance();
	SystemData& SystemData = SystemData::Instance();

	if(AqData._dBSyncInProgress.Get()==True)
	{
        strStream << command.GetAddressAndInstance() << ":";
        strStream <<"ERR11:";
		retValue = True;
	}
	else if(True == command.IsDUCommand())
    {
        int diagEnabled = -1;
        diagEnabled = (SystemData.DiagnosticEnabled.Get()==True) ? 1 : 0;
        strStream << command.GetAddressAndInstance() << ":";
        strStream << diagEnabled << ":";
        retValue = True;
    }
    else if(True == command.IsSUCommand())
    {       
		strStream << command.GetAddressAndInstance() << ":";
		std::vector<std::string>::iterator      itemsIter;
        std::vector<std::string>                items;
        items = command.GetPayloadList();
        std::string subResponse = "ERR1:";

        if(items.size() > 0)
        {
           itemsIter = items.begin();
           if(itemsIter != items.end()) //TODO : Disable makesump and dispesne operation when diagnostics is requested.
           {
        	    Garfunkel::AlarmSettings& AlarmData = Garfunkel::AlarmSettings::Instance();

				int     enable = -1;
				enable = boost::lexical_cast<int> ((std::string)*itemsIter);

				(enable==1) ? SystemData.DiagnosticEnabled.Set(True) :SystemData.DiagnosticEnabled.Set(False);

				if(SystemData.DiagnosticEnabled.Get()==True)  //if diagnostic enabled, clear reset alarm detection
				{
					AlarmData.ClearAllAlarmsAndResetTimeouts(True);   //This will clear alarms so that they can be detected again when you run diagnostics
					SystemData.SetSystemState(eDiagnosticsActive);
					SystemData.DisableMakeSump.Set(True);
					SystemData.DisableDispense.Set(True);
					std::cout<<"EnableDiagnosticsMessage:  Diagnostics Enabled!!!"<<std::endl;
				}
				else
				{
					SystemData.SetSystemState(eIdle); //TODO ,if this is the right state
					SystemData.DisableMakeSump.Set(False);
					SystemData.DisableDispense.Set(True);
					std::cout<<"EnableDiagnosticsMessage:  Diagnostics Disabled!!"<<std::endl;
				}
				subResponse.assign("OK:");
		    }
		}		
        strStream<<subResponse;
        retValue = True;
    }

    response = strStream.str();
    CreateESPString(response);
    return retValue;
}

///////////////////////////////////////////////////////////////////////////////////
// Command 44: MachineData Primary Language

Garfunkel::DispenseActiveStateMessage::DispenseActiveStateMessage()
{
}

Garfunkel::DispenseActiveStateMessage::DispenseActiveStateMessage(const DispenseActiveStateMessage & objectToCopy)
{
}

Garfunkel::DispenseActiveStateMessage::~DispenseActiveStateMessage()
{
}

BOOLEAN Garfunkel::DispenseActiveStateMessage::ProcessMessage(IPCCommand & command, std::string & response)
{

    BOOLEAN retValue = False;
    SystemData &   Data = Garfunkel::SystemData::Instance();
    std::stringstream strStream;
    if(True == command.IsDUCommand())
    {

        int  str = 0;
        str = Data._DispenseActive.Get();
        strStream << command.GetAddressAndInstance() << ":";
        strStream << str << ":";
        response = strStream.str();
        CreateESPString(response);
        retValue = True;
    }

    return retValue;

}
///////////////////////////////////////////////////////////////////////////////////
// Command : SystemData Secondary Language

Garfunkel::LayupModeStateMessage::LayupModeStateMessage()
{
}

Garfunkel::LayupModeStateMessage::LayupModeStateMessage(const LayupModeStateMessage & objectToCopy)
{
}

Garfunkel::LayupModeStateMessage::~LayupModeStateMessage()
{
}

BOOLEAN Garfunkel::LayupModeStateMessage::ProcessMessage(IPCCommand & command, std::string & response)
{

    BOOLEAN retValue = False;
    SystemData &   SystemData = Garfunkel::SystemData::Instance();
    std::stringstream strStream;
    if(True == command.IsDUCommand())
    {

        int  str = 0;
        str = SystemData._LayupEnabled.Get();
        strStream << command.GetAddressAndInstance() << ":";
        strStream << str << ":";
        retValue = True;
    }
    else if(True == command.IsSUCommand())
    {
		strStream << command.GetAddressAndInstance() << ":";
		std::vector<std::string>::iterator      itemsIter;
        std::vector<std::string>                items;
        items = command.GetPayloadList();
        std::string subResponse = "ERR1:";

        if(items.size() > 0)
        {
           itemsIter = items.begin();
           if(itemsIter != items.end())
           {
				int     enable = -1;
				enable = boost::lexical_cast<int> ((std::string)*itemsIter);

				(enable==1) ? SystemData._LayupEnabled.Set(True) :SystemData._LayupEnabled.Set(False);

				std::cout<<"LayupModeStateMessage:  layup state="<<SystemData._LayupEnabled.Get()<<std::endl;
				subResponse.assign("OK:");
		    }
		}
        strStream<<subResponse;
        retValue = True;
    }

    response = strStream.str();
    CreateESPString(response);
    return retValue;

}

///////////////////////////////////////////////////////////////////////////////////
// Command : SystemData TM Language

Garfunkel::StandbyModeMessage::StandbyModeMessage()
{
}

Garfunkel::StandbyModeMessage::StandbyModeMessage(const StandbyModeMessage & objectToCopy)
{
}

Garfunkel::StandbyModeMessage::~StandbyModeMessage()
{
}

BOOLEAN Garfunkel::StandbyModeMessage::ProcessMessage(IPCCommand & command, std::string & response)
{

    BOOLEAN retValue = False;
    SystemData &   Data = Garfunkel::SystemData::Instance();
    std::stringstream strStream;
    if(True == command.IsDUCommand())
    {

        int  str = 0;
        if(Data.GetSystemState()==eStandBy)
        	str = 1;
        else
        	str = 0;
        strStream << command.GetAddressAndInstance() << ":";
        strStream << str << ":";
        retValue = True;
    }
    else if(True == command.IsSUCommand())
    {
		strStream << command.GetAddressAndInstance() << ":";
		std::vector<std::string>::iterator      itemsIter;
        std::vector<std::string>                items;
        items = command.GetPayloadList();
        std::string subResponse = "ERR1:";

        if(items.size() > 0)
        {
           itemsIter = items.begin();
           if(itemsIter != items.end())
           {
				int     enable = -1;
				enable = boost::lexical_cast<int> ((std::string)*itemsIter);

				if(enable==1)
					Data.SetSystemState(eStandBy);
				else
					Data.SetSystemState(eIdle); //TODO : Check if idle is the correct state to swicth back to?

				std::cout<<"StandbyModeMessage:  Standby state="<<Data.GetSystemState()<<std::endl;
				subResponse.assign("OK:");
		    }
		}
        strStream<<subResponse;
        retValue = True;
    }


    response = strStream.str();
    CreateESPString(response);
    return retValue;

}



///////////////////////////////////////////////////////////////////////////////////
// Command : SystemData  Unit of Measure

Garfunkel::UnitOfMeasure::UnitOfMeasure()
{
}

Garfunkel::UnitOfMeasure::UnitOfMeasure(const UnitOfMeasure & objectToCopy)
{
}

Garfunkel::UnitOfMeasure::~UnitOfMeasure()
{
}

BOOLEAN Garfunkel::UnitOfMeasure::ProcessMessage(IPCCommand & command, std::string & response)
{

    BOOLEAN retValue = False;
    SystemData &   Data = Garfunkel::SystemData::Instance();

    if(True == command.IsDUCommand())
    {
        std::stringstream strStream;
        int  str=-1;
       // str = Data.GetUnitOfMeasurement();
        strStream << command.GetAddressAndInstance() << ":";
        strStream << str << ":";

        response = strStream.str();
        CreateESPString(response);

        retValue = True;
    }

    return retValue;

}

//////////////////////////////////////////////////////////////////////////
// Command
Garfunkel::GarfunkelIOBoardDIMessage::GarfunkelIOBoardDIMessage()
{
}

Garfunkel::GarfunkelIOBoardDIMessage::GarfunkelIOBoardDIMessage(const GarfunkelIOBoardDIMessage &   objectToCopy)
{
}

Garfunkel::GarfunkelIOBoardDIMessage::~GarfunkelIOBoardDIMessage()
{
}

BOOLEAN Garfunkel::GarfunkelIOBoardDIMessage::ProcessMessage(IPCCommand & command, std::string & response)
{
    BOOLEAN          retValue = False;
    
    if(True == command.IsDUCommand())
    {
        boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485;
        ecolab::SocketFactory & FactoryInstance = ecolab::SocketFactory::Instance();
        std::cout<<"MCA: Connecting to pSocketRS485 "<<std::endl;
        pSocketRS485.reset(FactoryInstance.CreateSocket(ecolab::eCondor, ecolab::eRS485));
        pSocketRS485->Connect();
        GarfunkelData& AqData = GarfunkelData::Instance();
        std::stringstream strStream;
        strStream<<AqData._garfunkelIOBoardAddressInstance;
        std::string     message = ":DI:";
        strStream<<message;
        message.assign(strStream.str());

        //ConvertESPString(message);

        // This should ping the IO Board.
        std::cout<<"MCA: Issuing IOBoard  DI Command ="<<message<<std::endl;

        if((NULL != pSocketRS485.get()) && (True == pSocketRS485->SocketConnected()) && (pSocketRS485->SocketStatus() == ecolab::eConnectionAvailable))
        {
            if(True == pSocketRS485->WriteData(message))
            {
                //  Was an appropriate ack returned.
                if(False == pSocketRS485->IsNAK())
                {
                    if(True == pSocketRS485->ReadData(response))
                    {
                        // Validate if the data is a properly formatted ESPString
                        retValue = True;  // some placeholder
                    }
                    else
                    	std::cout<<" failed to read response"<<std::endl;
                }
                else
                {
                    std::cout << "Nak received" << std::endl;

                }
            }
            else
            	std::cout<<" failed to write data properly"<<std::endl;
        }
        else
        	std::cout<<" Socket not connected"<<std::endl;

        pSocketRS485->Disconnect();
        
        if(True == retValue)
        {
            IPCReturnCommand  returnCommand(response);
            strStream.str("");
            strStream.clear();
            strStream << command.GetAddressAndInstance() << ":";
            std::cout << "command.GetAddressAndInstance()"<<strStream.str()<< std::endl;
            strStream << returnCommand.GetPayload() << ":";
            std::cout << "returnCommand.GetPayload()"<<strStream.str()<< std::endl;
        }
        else
        {
        	std::cout<<"IOBoardDIMessage: IOBoard may not be connecting or may not be installed "<<std::endl;
            strStream.str("");
            strStream.clear();
        	strStream << command.GetAddressAndInstance() << ":ERR1:";
        }
        response = strStream.str();
        std::cout << "response = "<<response<< std::endl;
        CreateESPString(response);

        retValue = True;
    }
    else
    {
        // Do nothing
    }

    return retValue;
}





//////////////////////////////////////////////////////////////////////////
// Command
Garfunkel::SimonIOBoardDIMessage::SimonIOBoardDIMessage()
{
}

Garfunkel::SimonIOBoardDIMessage::SimonIOBoardDIMessage(const SimonIOBoardDIMessage &   objectToCopy)
{
}

Garfunkel::SimonIOBoardDIMessage::~SimonIOBoardDIMessage()
{
}

BOOLEAN Garfunkel::SimonIOBoardDIMessage::ProcessMessage(IPCCommand & command, std::string & response)
{
    BOOLEAN          retValue = False;

    if(True == command.IsDUCommand())
    {
        boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485;
        ecolab::SocketFactory & FactoryInstance = ecolab::SocketFactory::Instance();
        std::cout<<"MCA: Connecting to pSocketRS485 "<<std::endl;
        pSocketRS485.reset(FactoryInstance.CreateSocket(ecolab::eCondor, ecolab::eRS485));
        pSocketRS485->Connect();
        GarfunkelData& AqData = GarfunkelData::Instance();
        std::stringstream strStream;
        strStream<<AqData._simonIOBoardAddressInstance;
        std::string     message = ":DI:";
        strStream<<message;
        message.assign(strStream.str());

        //ConvertESPString(message);

        // This should ping the IO Board.
        std::cout<<"MCA: Issuing IOBoard  DI Command ="<<message<<std::endl;

        if((NULL != pSocketRS485.get()) && (True == pSocketRS485->SocketConnected()) && (pSocketRS485->SocketStatus() == ecolab::eConnectionAvailable))
        {
            if(True == pSocketRS485->WriteData(message))
            {
                //  Was an appropriate ack returned.
                if(False == pSocketRS485->IsNAK())
                {
                    if(True == pSocketRS485->ReadData(response))
                    {
                        // Validate if the data is a properly formatted ESPString
                        retValue = True;  // some placeholder
                    }
                    else
                    	std::cout<<" failed to read response"<<std::endl;
                }
                else
                {
                    std::cout << "Nak received" << std::endl;

                }
            }
            else
            	std::cout<<" failed to write data properly"<<std::endl;
        }
        else
        	std::cout<<" Socket not connected"<<std::endl;

        pSocketRS485->Disconnect();

        if(True == retValue)
        {
            IPCReturnCommand  returnCommand(response);
            strStream.str("");
            strStream.clear();
            strStream << command.GetAddressAndInstance() << ":";
            std::cout << "command.GetAddressAndInstance()"<<strStream.str()<< std::endl;
            strStream << returnCommand.GetPayload() << ":";
            std::cout << "returnCommand.GetPayload()"<<strStream.str()<< std::endl;
        }
        else
        {
        	std::cout<<"IOBoardDIMessage: IOBoard may not be connecting or may not be installed "<<std::endl;
            strStream.str("");
            strStream.clear();
        	strStream << command.GetAddressAndInstance() << ":ERR1:";
        }
        response = strStream.str();
        std::cout << "response = "<<response<< std::endl;
        CreateESPString(response);

        retValue = True;
    }
    else
    {
        // Do nothing
    }

    return retValue;
}


//////////////////////////////////////////////////////////////////////////
// Command 51
Garfunkel::ApplicationDIMessage::ApplicationDIMessage()
{
}

Garfunkel::ApplicationDIMessage::ApplicationDIMessage(const ApplicationDIMessage &   objectToCopy)
{
}

Garfunkel::ApplicationDIMessage::~ApplicationDIMessage()
{
}

BOOLEAN Garfunkel::ApplicationDIMessage::ProcessMessage(IPCCommand & command, std::string & response)
{

	BOOLEAN         retValue = False;
    GarfunkelData &  Data = GarfunkelData::Instance();
    if(True == command.IsDUCommand())
    {
        std::stringstream strStream;
        strStream << command.GetAddressAndInstance() << ":";
        
        if(False == Data._systemDIString.empty())
        {
            strStream << Data._systemDIString << ":";
        }
        else
        {
            std::string         systemInfo = "Information not available";
            if(NULL != Data._database.get())
            {
                if(Data._database->GetSystemInformation(systemInfo)==True)
                Data._systemDIString = systemInfo;
            }
            strStream << systemInfo << ":";
        }
        response = strStream.str();
        CreateESPString(response);
     std::cout << "DI Message: " << response << std::endl;            

        retValue = True;
    }
    else
    {
        // Do nothing
    }

    return retValue;

}

//////////////////////////////////////////////////////////////////////////
// Command 71
Garfunkel::CondorDIMessage::CondorDIMessage()
{
}

Garfunkel::CondorDIMessage::CondorDIMessage(const CondorDIMessage &   objectToCopy)
{
}

Garfunkel::CondorDIMessage::~CondorDIMessage()
{
}
//DU
BOOLEAN Garfunkel::CondorDIMessage::ProcessMessage(IPCCommand & command, std::string & response)
{
	ecolab::DB::DBAccess    myDBAccess;
    std::string             connectString="";
    BOOLEAN                 retValue = False;
	std::string				softwareName="";
	std::string				condorVersion="";
	std::string				serialNumber="";

    if(True == command.IsDUCommand())
    {
        std::stringstream strStream;
        strStream << command.GetAddressAndInstance() << ":";
	    // Use of the connection string.
	    connectString = "dbname = 'Condor' user = 'db_controller' password = 'controller'";

	    /* Connect to DB if it is not connected. */
	    if (NULL == myDBAccess.DBisConnected())
	    {
	        myDBAccess.DBConnect(connectString, 5);
	    }

	    if(NULL != myDBAccess.DBisConnected())
	    {

	        ecolab::DB::DataSet        dataSet;
	        std::string                sql;
	        std::stringstream strstream;
	        strstream<<"SELECT * FROM GetControllerData() WHERE \"Description\"=\'Condor\';";
	        sql = strstream.str();


	        std::cout << "Trying to execute " << sql << std::endl;
	        if(myDBAccess.DBExecuteStored(sql, dataSet))
	        {

	        	std::cout << "Execution of " << sql << std::endl;

	           if(dataSet.GetNumberOfRows() > 0)
	           {
					ecolab::DB::DataRow 						rowData;
	        	   	boost::shared_ptr<ecolab::DB::IColumnData>    colData;
					std::string									colDataAsString;
					int		numRows = 0;
					numRows = dataSet.GetNumberOfRows();
					std::cout << "No Of rows : " << numRows << std::endl;

					rowData = dataSet.GetFirstRow();
					if(rowData.GetNumberOfColumns() > 0)
					{
						colData = rowData.GetColumn("Description");
						if(colData.get() != NULL)
						{
							colData->AsString(softwareName);
//							std::cout<<"softwareName -> "<<softwareName<<std::endl;
						}

						colData = rowData.GetColumn("SoftwareVersion");
						if(colData.get() != NULL)
						{
							colData->AsString(condorVersion);
//							std::cout<<"condorVersion -> "<<condorVersion<<std::endl;
						}

						colData = rowData.GetColumn("SerialNumber");
						if(colData.get() != NULL)
						{
							colData->AsString(serialNumber);
//							std::cout<<"serialNumber -> "<<serialNumber<<std::endl;
						}

						strStream << softwareName << ", " << condorVersion << ", " << serialNumber << ":";
						response = strStream.str();
						CreateESPString(response);
						std::cout << "DI Message: " << response << std::endl;            

						retValue = True;

					}
					else
					{
						std::cout << "[DB] ERROR GetNumberOfColumns returned " << rowData.GetNumberOfColumns() << " columns. Expected 1 or more" << std::endl;
					}
				}
				else
				{
					std::cout << "[DB] ERROR GetNumberOfRows returned " << dataSet.GetNumberOfRows() << " rows. Expected 1." << std::endl;
				}
			}
			else
			{
				std::cout << "[DB] ERROR: Execute the stored procedure GetControllerData." << std::endl;
			}
		}
		else
		{
			std::cout << "[DB] ERROR: Can't connect to DB." << std::endl;
		}

		myDBAccess.DBDisconnect();

    }
    else
    {
        // Do nothing
    }

    return retValue;

}



/////////////
/// AckAlarmMessage alarm
// SU: <alarmType>:<machineId/pumpId>
/////////////
Garfunkel::AckAlarmMessage::AckAlarmMessage()
{
}

Garfunkel::AckAlarmMessage::AckAlarmMessage(const AckAlarmMessage & objectToCopy)
{
}

Garfunkel::AckAlarmMessage::~AckAlarmMessage()
{
}

/*
 * SU: <alarmType>:<machineId/pumpId>
 *
*/

BOOLEAN Garfunkel::AckAlarmMessage::ProcessMessage(IPCCommand & command, std::string & response)
{
#if 0
	BOOLEAN retValue = False;
	std::stringstream strStream;
	std::string         subResponse = ":ERR1:";
	std::vector<std::string>::iterator      itemsIter;
    std::vector<std::string>                items;
    timespec Now;
    int flag = 0;

	SystemData &   SysData = Garfunkel::SystemData::Instance();
	PumpData& PumpSysdata = PumpData::Instance();
	Garfunkel::PocketInfoData & pocData = Garfunkel::PocketInfoData::Instance();
    DispensingSystemData& DispenseData = DispensingSystemData::Instance();
	GarfunkelData &     AqData = Garfunkel::GarfunkelData::Instance();
	Garfunkel::AlarmData& AlarmData = Garfunkel::AlarmData::Instance();

	 /*if(AqData._dBSyncInProgress.Get()==True) // Commented this out , cos we have to let ack alarm operations or we may potentially miss silencing alarms (esp audible alarms)
	{
	    strStream << command.GetAddressAndInstance() << ":";
	    strStream <<"ERR11:";
	    retValue = True;
	}
    else */
	if(0) //True==command.IsDUCommand()) TODO: Add DU command for all alarms cases not just OOP
	{
		strStream <<command.GetAddressAndInstance();
        items = command.GetPayloadList();
		if(items.size() > 0)
        {
			itemsIter = items.begin();
			if(itemsIter != items.end())
			{
				int     pumpNo = -1;
				pumpNo = boost::lexical_cast<int>((std::string)*itemsIter);
				if(pumpNo!=-1)
				{
					//int pumpNo = SysData.GetPumpId(prodNo); //use pump no istaed of product no
					boost::shared_ptr< Garfunkel::PumpInfo> pdata = PumpSysdata.GetContextForPump(pumpNo);
					if(pdata.get() != NULL)
					{
						if(pdata->OOP_State.Get()==eEmpty&&pdata->IsAlarmMuted.Get()==True)
						{

							strStream <<":"<<pumpNo<<":1:"; //Muted

						}
						else
						{
							strStream <<":"<<pumpNo<<":0:"; //Muted
						}
					}
				}
			}
        }
	}

	else if(True == command.IsSUCommand())
	{

        items = command.GetPayloadList();
		if(items.size() > 0)
        {
			 itemsIter = items.begin();
			 if(itemsIter != items.end())
			 {
	        	   int type = boost::lexical_cast<int> ((std::string)*itemsIter);
	        	   AlarmEvent     alarmType;
	        	   alarmType = (AlarmEvent) type;
	   	   		   boost::shared_ptr<ecolab::ISocketCommunication>     pSocketRS485;
	   	   		   ecolab::SocketFactory & FactoryInstance = ecolab::SocketFactory::Instance();
	   	   		   pSocketRS485.reset(FactoryInstance.CreateSocket(ecolab::eCondor, ecolab::eRS485));
	   	   		   pSocketRS485->Connect();
	   	   		   GarfunkelProductPhysicalState prodType = eUndefinedPhysicalState;
	   	   		   ecolab::ScopeLock Lock(AlarmData.AlarmDataCommInProgress);

	   	   		   switch(alarmType)
	        	   {

	        	   case eProductEmpty : {

	        		   	   	   	   	   	   int     pumpNo = -1;
	        		   	   	   	   	   	   if(itemsIter != items.end())
	        		   	   	   	   	   	   {
	        		   	   	   	   	   		   itemsIter++;
	        		   	   	   	   	   		   pumpNo = boost::lexical_cast<int>((std::string)*itemsIter);
	        		   	   	   	   	   		   boost::shared_ptr< Garfunkel::OOPState> pdata;
	        		   	   	   	   	   		   if(pumpNo!=-1)
	        		   	   	   	   	   		   {
	        		   	   	   	   	   			   if(pumpNo>=START_LIQUID_PRODUCT_EMPTY)
	        		   	   	   	   	   			   {
	        		   	   	   	   	   				   pumpNo=pumpNo-START_LIQUID_PRODUCT_EMPTY; //liquid product
	        		   	   	   	   	   				   std::cout<<"MuteOOPAlarmMessage: Trying UI muting OOP for liquid prod pumpNo="<<pumpNo<<std::endl;

		        		   	   	   	   	   			   pdata = PumpSysdata.GetContextForPump(pumpNo);
		        		   	   	   	   	   			   prodType = eLiquid;
	        		   	   	   	   	   				   std::cout<<"MuteOOPAlarmMessage: Trying UI muting OOP for liquid prod pumpNo="<<pumpNo<<std::endl;
	        		   	   	   	   	   			   }
	        		   	   	   	   	   			   else
	        		   	   	   	   	   			   {
	        		   	   	   	   	   				   std::cout<<"MuteOOPAlarmMessage: Trying UI muting OOP for SOLID prod pocketNo="<<pumpNo<<std::endl;
		        		   	   	   	   	   			   pdata = pocData.GetContextForPocket(pumpNo);
		        		   	   	   	   	   			   prodType = eSolid;
	        		   	   	   	   	   			   }

	        		   	   	   	   	   			   if(pdata.get() != NULL&& (prodType==eLiquid || prodType==eSolid))
	        		   	   	   	   	   			   {
	        		   	   	   	   	   				   std::cout<<"MuteOOPAlarmMessage: here  pdata->OOPAlarmAlreadyDetected.Get()="<<pdata->OOPAlarmAlreadyDetected.Get()<<std::endl;
	        		   	   	   	   	   				   std::cout<<"MuteOOPAlarmMessage: here pdata->OOP_State.Get()==eEmpty="<<pdata->OOP_State.Get()<<std::endl;
	        		   	   	   	   	   				   std::cout<<"MuteOOPAlarmMessage: here  pdata->IsAlarmMuted.Get()="<<pdata->IsAlarmMuted.Get()<<std::endl;
	        		   	   	   	   	   				   std::cout<<"MuteOOPAlarmMessage: here  pdata->AlarmMuteCount.Get()="<<pdata->AlarmMuteCount.Get()<<std::endl;

	        		   	   	   	   	   				   if(pdata->OOPAlarmAlreadyDetected.Get()==True&&pdata->OOP_State.Get()==eEmpty&&pdata->IsAlarmMuted.Get()==False&&pdata->AlarmMuteCount.Get()<MAX_MUTE_ATTEMPTS)
	        		   	   	   	   	   				   {
	        		   	   	   	   	   					   std::cout<<"MuteOOPAlarmMessage: UI muting OOP for pump="<<pumpNo<<std::endl;
	        		   	   	   	   	   					   std::cout<<"MuteOOPAlarmMessage: No Of snooze attempts="<<pdata->AlarmMuteCount.Get()<<std::endl;
	        		   	   	   	   	   					   pdata->IsAlarmMuted.Set(True);
		        		   	   	   	   	   		   		   pdata->AlarmMuteCount.Set(pdata->AlarmMuteCount.Get()+1);
		        		   	   	   	   	   		   		   std::cout<<"MuteOOPAlarmMessage: No Of snooze attempts="<<pdata->AlarmMuteCount.Get()<<std::endl;
		        		   	   	   	   	   		   		   pdata->UpdateLastAlarmMuteTime();

		        		   	   	   	   	   		   				flag = 1;
		        		   	   	   	   	   				}

		        		   	   	   	   	   			}
		        		   	   	   	   	   			else
		        		   	   	   	   	   			{
		        		   	   	   	   	   				std::cout<<"ERROR : here"<<std::endl;
		        		   	   	   	   	   			}
	        		   	   	   	   	   		   }
	        		   	   	   	   	   	   }
	        	   	   	   	   	   	   }
	        	   break;
	        	   case eFormulaNotFinished : {

  	   	   	   	   	   	   	   	   	   	   	   int     machineNo = -1;
  	   	   	   	   	   	   	   	   	   	   	   if(itemsIter != items.end())
  	   	   	   	   	   	   	   	   	   	   	   {
  	   	   	   	   	   	   	   	   	   	   		   itemsIter++;
  	   	   	   	   	   	   	   	   	   	   		   machineNo = boost::lexical_cast<int>((std::string)*itemsIter);
  	   	   	   	   	   	   	   	   	   	   		   if(machineNo!=-1)
  	   	   	   	   	   	   	   	   	   	   		   {
  	   	   	   	   	   	   	   	   	   	   			   if(alarmType==eFormulaNotFinished)
  	   	   	   	   	   	   	   	   	   	   			   {
  	   	   	   	   	   	   	   	   	   	   				   AlarmData.SetFormulaNotFinishedAlarm(machineNo, False);
  	   	   	   	   	   	   	   	   	   	   				   AlarmData.SetFormulaNotFinishedAlarmMuteState(machineNo, False);
  	   	   	   	   	   	   	   	   	   	   			   }

  	   	   	   	   	   	   	   	   	   	   			   flag = 1;

  	   	   	   	   	   	   	   	   	   	   		   }
  	   	   	   	   	   	   	   	   	   	   	   }

	   	   	   	   	  	  	  	  	  	  }


	        	   	   	   	   	   	   	   break;
	        	   case eFBoxCommError :
	        	   case eMSICommError :
	        	   	   	                       {

	        		   	   	   	   	   	   	   	   int     machineNo = -1;
	        		   	   	   	   	   	   	   	   if(itemsIter != items.end())
	        		   	   	   	   	   	   	   	   {
	        		   	   	   	   	   	   	   		   itemsIter++;
	        		   	   	   	   	   	   	   		   machineNo = boost::lexical_cast<int>((std::string)*itemsIter);
	        		   	   	   	   	   	   	   		   if(machineNo!=-1)
	        		   	   	   	   	   	   	   		   {
 	        		   	   	   	   	   		   			   if(alarmType!=eFormulaNotFinished)
     	        		   	   	   	   	   		   			; //do nothing
 	        		   	   	   	   	   		   			   if(alarmType==eFormulaNotFinished)
 	        		   	   	   	   	   		   			   {
 	        		   	   	   	   	   		   				   AlarmData.SetFormulaNotFinishedAlarm(machineNo, False);
 	        		   	   	   	   	   		   				   AlarmData.SetFormulaNotFinishedAlarmMuteState(machineNo, False);
 	        		   	   	   	   	   		   			   }
 	        		   	   	   	   	   		   			   else if(alarmType==eMSICommError)
 	        		   	   	   	   	   		   			   {
 	        		   	   	   	   	   		   				   AlarmData.SetMSICommAlarmMuteState(machineNo, True);

 	        		   	   	   	   	   		   			   }
 	        		   	   	   	   	   		   			   else if(alarmType==eFBoxCommError)
 	        		   	   	   	   	   		   			   {
 	        		   	   	   	   	   		   				   AlarmData.SetFBoxCommAlarmMuteState(machineNo, True);

 	        		   	   	   	   	   		   			   }

	       		   	   	   	   	   	   	   			   flag = 1;

	        		   	   	   	   	   	   	   		   }
	        		   	   	   	   	   	   	   	   }

	        	   	   	   	   	   	   	  	  }

	        	   break;
	        	   case eIOBoardCommError :
	        	   	   	   	   	   	   	   {
	        		   	   	   	   	   	   	   	   	//mute audible alarm, and NO alarm clear info. These alarms are cleared and communicated by alarm handler
	        		   	   	   	   	   	   	   	   	if(alarmType==eIOBoardCommError)
	        		   	   	   	   	   	   	   	    AlarmData.IOBoardCommAlarmMuteState.Set(True);

	   	   	   		   								flag = 1;
	        	   	   	   	   	   	   	   	}
	        	   break;


	        	   } //switch

	   	   		 pSocketRS485->Disconnect();

			 }
        }

		if(flag ==1)
		{
			subResponse = ":OK:";
		}
		else
		{
			subResponse = ":ERR1:";
		}
		retValue = True;
		strStream << command.GetAddressAndInstance() << subResponse;
     }

	response = strStream.str();
	CreateESPString(response);
    return retValue;
#endif
}



Garfunkel::DBSyncStateMessage::DBSyncStateMessage()
{
}

Garfunkel::DBSyncStateMessage::DBSyncStateMessage(const DBSyncStateMessage & objectToCopy)
{
}

Garfunkel::DBSyncStateMessage::~DBSyncStateMessage()
{
}

/*
 * DU:64  0/1 where 0 - Sync Off, 1- Sync  On
*/

BOOLEAN Garfunkel::DBSyncStateMessage::ProcessMessage(IPCCommand & command, std::string & response)
{

	BOOLEAN retValue = False;
	std::stringstream strStream;
	std::string         subResponse = ":ERR1:";

    GarfunkelData &   AqData = Garfunkel::GarfunkelData::Instance();
    //std::cout<<"DBSyncStateMessage"<<std::endl;
    if(True==command.IsDUCommand())
	{
	    std::cout <<"Recived DU "<<std::endl;
        strStream << command.GetAddressAndInstance() << ":" << AqData._dBSyncInProgress.Get()<< ":";
        response = strStream.str();
        CreateESPString(response);
        retValue = True;
	}

    return retValue;

}
