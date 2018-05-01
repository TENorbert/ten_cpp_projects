#ifndef IPCMESSAGES_H
#define IPCMESSAGES_H

//#include "ApplicationContext.h"
//#include "GarfunkelData.h"
//#include "GarfunkelIPCData.h"
#include "ESPStringCreate.h"
#include "IPCCommand.h"

namespace Garfunkel
{
    // This is the message object to be processed when an incoming IPC message is sent
    class IIPCMessage
    {
    public:
        IIPCMessage(){};
        virtual ~IIPCMessage(){};

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response) = 0;

        // methods to create and
        BOOLEAN  CreateESPString(std::string & dataToConvert);
        BOOLEAN  ConvertESPString(std::string & dataToConvert);
    };

    class GarfunkelIPCMixin
    {
    public:
        GarfunkelIPCMixin();
        virtual ~GarfunkelIPCMixin();

    protected:
    };

	    // Command
    class SystemStateMessage : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
        SystemStateMessage();
        SystemStateMessage(const SystemStateMessage &   objectToCopy);
        virtual ~SystemStateMessage();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };

    // Command
    class OperatingScheduleStatus : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
    	OperatingScheduleStatus();
    	OperatingScheduleStatus(const OperatingScheduleStatus &   objectToCopy);
        virtual ~OperatingScheduleStatus();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };



	 // Command
	 //DU - NoOfMachines
    class NoOfMachinesMessage : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
        NoOfMachinesMessage();
        NoOfMachinesMessage(const NoOfMachinesMessage &   objectToCopy);
        virtual ~NoOfMachinesMessage();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };

	// Command
	//DU - NoOfPumps:NoOfProducts(?)
    class NoOfPumpsMessage : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
        NoOfPumpsMessage();
        NoOfPumpsMessage(const NoOfPumpsMessage &   objectToCopy);
        virtual ~NoOfPumpsMessage();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };






	//DU commands: response-> Current dispensing MachineNo:SignalNo:PumpNo:NextPumpNo:
	//No need to send Pump Delay, PumpRuntime and Product amounts as they are fetched by UI from DB
	//
    class MakeDownProcessStateMessage : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
        MakeDownProcessStateMessage();
        MakeDownProcessStateMessage(const MakeDownProcessStateMessage &   objectToCopy);
        virtual ~MakeDownProcessStateMessage();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };


    // Command
    class AlarmStatusMessage : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
    	AlarmStatusMessage();
    	AlarmStatusMessage(const AlarmStatusMessage &   objectToCopy);
        virtual ~AlarmStatusMessage();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };

    // Command
	//Includes multiple command:  actiavte product, optional flush, do dispensing for as selected formula, send message fbox, and pickup probe examination
	//All the above for each washer
    class DiagnosticsMessage : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
        DiagnosticsMessage();
        DiagnosticsMessage(const DiagnosticsMessage & objectToCopy);
        virtual ~DiagnosticsMessage();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    private:
        BOOLEAN _onOff;
    };

    // Command : Enable/disable diagnostics
    class EnableDiagnosticsMessage : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
    	EnableDiagnosticsMessage();
    	EnableDiagnosticsMessage(const EnableDiagnosticsMessage & objectToCopy);
        virtual ~EnableDiagnosticsMessage();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };

    // Command : SystemData Primary Language
    class DispenseActiveStateMessage : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
        DispenseActiveStateMessage();
        DispenseActiveStateMessage(const DispenseActiveStateMessage & objectToCopy);
        virtual ~DispenseActiveStateMessage();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };

    // Command : SystemData Secondary Language
    class LayupModeStateMessage : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
    	LayupModeStateMessage();
    	LayupModeStateMessage(const LayupModeStateMessage & objectToCopy);
    	virtual ~LayupModeStateMessage();

    	virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };


	// Command : SystemData TM Language
    class StandbyModeMessage : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
    	StandbyModeMessage();
    	StandbyModeMessage(const StandbyModeMessage & objectToCopy);
    	virtual ~StandbyModeMessage();

    	virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };


    // Command : SystemData Daytank Unit of Measure
    class UnitOfMeasure : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
        UnitOfMeasure();
        UnitOfMeasure(const UnitOfMeasure & objectToCopy);
        virtual ~UnitOfMeasure();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };


    // Command
    class GarfunkelIOBoardDIMessage : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
        GarfunkelIOBoardDIMessage();
        GarfunkelIOBoardDIMessage(const GarfunkelIOBoardDIMessage &   objectToCopy);
        virtual ~GarfunkelIOBoardDIMessage();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };


    class SimonIOBoardDIMessage : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
        SimonIOBoardDIMessage();
        SimonIOBoardDIMessage(const SimonIOBoardDIMessage &   objectToCopy);
        virtual ~SimonIOBoardDIMessage();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };

    // Command
    class ApplicationDIMessage : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
        ApplicationDIMessage();
        ApplicationDIMessage(const ApplicationDIMessage &   objectToCopy);
        virtual ~ApplicationDIMessage();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };

    // Command 71
    class CondorDIMessage : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
        CondorDIMessage();
        CondorDIMessage(const CondorDIMessage &   objectToCopy);
        virtual ~CondorDIMessage();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };

    // Command required to enable and disable particular items on UI
    class UIEnableItem : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
        UIEnableItem();
        UIEnableItem(const UIEnableItem & objectToCopy);
        virtual ~UIEnableItem();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };

    // Command
    class ClearESRAlarm : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
        ClearESRAlarm();
        ClearESRAlarm(const ClearESRAlarm & objectToCopy);
        virtual ~ClearESRAlarm();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };


	//For SU Command: On/Off
	class AckAlarmMessage : public IIPCMessage, GarfunkelIPCMixin
    {
    public:
		AckAlarmMessage();
		AckAlarmMessage(const AckAlarmMessage & objectToCopy);
        virtual ~AckAlarmMessage();

        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
    };

	//Only DU
	class DBSyncStateMessage : public IIPCMessage, GarfunkelIPCMixin
	    {
	    public:
		DBSyncStateMessage();
		DBSyncStateMessage(const DBSyncStateMessage & objectToCopy);
	        virtual ~DBSyncStateMessage();

	        virtual BOOLEAN ProcessMessage(IPCCommand & command, std::string & response);
	    };


};

#endif
