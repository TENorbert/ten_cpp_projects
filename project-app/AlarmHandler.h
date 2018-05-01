#if !defined(_ALARMHANDLER_H)
#define _ALARMHANDLER_H
#include "GarfunkelData.h"
#include "Alarm.h"
namespace Garfunkel
{

class AlarmSettings
{
    public:

    static AlarmSettings&     Instance();

		/*!
            Destructor method for AlarmSettings.
        */
        virtual ~AlarmSettings();

        /*
            Map of alarm type to EventDataLog.SubEventFlag.
        */
        enum AlarmType
        {
            ALARM_NONE_TYPE= -1,
        	ALARM_TYPE_SIMON_IO_COMM_ERROR = 0,
            ALARM_TYPE_GARFUNKEL_IO_COMM_ERROR = 1,
            ALARM_TYPE_OVER_HIGH_TEMP = 2,
            ALARM_TYPE_SUMP_OVERFLOW = 3,
            ALARM_TYPE_NO_O_REMAINS= 4,
            ALARM_TYPE_EMPTY_SUMP = 5,
            ALARM_TYPE_LOW_MAKEUP_PRESSURE = 6,
            ALARM_TYPE_HIGH_TEMP = 7,
            ALARM_TYPE_LOW_TEMP = 8,
            ALARM_TYPE_O1_LID_OPEN = 9,
            ALARM_TYPE_O2_LID_OPEN = 10,
            ALARM_TYPE_S_LID_OPEN = 11,
            ALARM_TYPE_P2_LID_OPEN = 12,
            ALARM_TYPE_O1_PRODUCT_EMPTY = 13,
            ALARM_TYPE_O2_PRODUCT_EMPTY = 14,
            ALARM_TYPE_S_PRODUCT_EMPTY = 15,
            ALARM_TYPE_P2_PRODUCT_EMPTY = 16,
            ALARM_TYPE_S_LOW_PRODUCT = 17,
            ALARM_TYPE_P2_LOW_PRODUCT = 18,
            ALARM_TYPE_EXCESSIVE_TIME_SINCE_SUMP_FILL= 19,
            ALARM_TYPE_EXCEED_MAX_TIME_BETWEEN_BFWP_CALLS = 20,
            ALARM_TYPE_INTERNET_CONNECTIVITY_LOST = 21,
        };

        /*!
            Method to fetch the alarm settings from the database.
        */
        void FetchAlarmSettingsFromDB();

        /*!
            Method to check all alarms to see if their status' have changed.
        */
        void CheckAlarms();

        /*!
            Method to return an alarm status for an alarm.
        */
        Alarm::AlarmStatus GetAlarmStatusByType(AlarmType type);

        /*!
            Method to return the current alarm
        */
        boost::shared_ptr<GarfunkelAlarm> GetAlarmByType(AlarmType type);

        void HandleAlarmActionForTheSystem(boost::shared_ptr<GarfunkelAlarm> al);

        BOOLEAN IsDiagnosticsAllowed();
        BOOLEAN IsMakeSumpOperationAllowed();
        BOOLEAN IsDispenseAllowed();

        /*
            Map of Alarms.EventID to specific alarm.
        */
        enum AlarmEventID
        {
            // Alerts
            ALARM_EVENT_PPM_LOW_ALERT = 38,
            ALARM_EVENT_PPM_HIGH_ALERT = 39,
            ALARM_EVENT_PH_LOW_ALERT = 40,
            ALARM_EVENT_PH_HIGH_ALERT = 41,
            ALARM_EVENT_FLOW_LOW_ALERT = 42,
            ALARM_EVENT_SALT_LOW_ALERT = 43,
            ALARM_EVENT_SALT_HIGH_ALERT = 44,
            ALARM_EVENT_TEMP_LOW_ALERT = 45,
            ALARM_EVENT_TEMP_HIGH_ALERT = 46,

            // Alarms
            ALARM_EVENT_PPM_LOW_ALARM = 47,
            ALARM_EVENT_PPM_HIGH_ALARM = 48,
            ALARM_EVENT_PH_LOW_ALARM = 49,
            ALARM_EVENT_PH_HIGH_ALARM = 50,
            ALARM_EVENT_FLOW_LOW_ALARM = 51,
            ALARM_EVENT_SALT_LOW_ALARM = 52,
            ALARM_EVENT_SALT_HIGH_ALARM = 53,
            ALARM_EVENT_TEMP_LOW_ALARM = 54,
            ALARM_EVENT_TEMP_HIGH_ALARM = 55,

            ALARM_EVENT_PH_OOPA_ALARM = 56,
            ALARM_EVENT_PH_OVERFEED_ALARM = 57,
            ALARM_EVENT_PPM_OVERFEED_ALARM = 58,
            ALARM_EVENT_SALT_OVERFEED_ALARM = 59,
            ALARM_EVENT_AUX1_OVERFEED_ALARM = 60,
            ALARM_EVENT_AUX2_OVERFEED_ALARM = 61,
        };

        bool    WriteAlarmSettingsToFlatFile(std::fstream & outputStream);
        bool    ReadAlarmSettingsFromFlatFile(std::fstream &  inputStream);

        bool    ClearAllAlarms();
        BOOLEAN ClearAllAlarmsAndResetTimeouts(BOOLEAN override);
        void    SendClearAlarmInfoToUI();

        ecolab::Shareable<BOOLEAN>          GarIOBoardCommunicationAlarm;
        ecolab::Shareable<BOOLEAN>          SimonIOBoardCommunicationAlarm;

    private:

        AlarmSettings();
        std::map<AlarmType, boost::shared_ptr<GarfunkelAlarm> > _alarms;         //!< Map alarm type to alarm object.

        /*!
            Method to log an alarm event to the EventDataLog database table.

        */
        void LogAlarmEvent(AlarmType type, Alarm::AlarmStatus status, double value);

        /*!
            Method to send an IPC message to the UI containing the alarm status'.
        */
        void SendAlarmsToUI();
        /*!
            Method to return a printable alarm type for debugging.
        */
        std::string AlarmTypeToString(AlarmType type)
        {
            std::string str;
            switch(type)
            {
                case ALARM_TYPE_SIMON_IO_COMM_ERROR:
                    str = "SIMON Communication Error";
                    break;
                case ALARM_TYPE_GARFUNKEL_IO_COMM_ERROR:
                    str = "ALARM_TYPE_GARFUNKEL_IO_COMM_ERROR";
                    break;
                case ALARM_TYPE_OVER_HIGH_TEMP:
                    str = "ALARM_TYPE_OVER_HIGH_TEMP";
                    break;
                case ALARM_TYPE_SUMP_OVERFLOW:
                    str = "ALARM_TYPE_SUMP_OVERFLOW";
                    break;
                case ALARM_TYPE_NO_O_REMAINS:
                    str = "ALARM_TYPE_NO_O_REMAINS";
                    break;
                case ALARM_TYPE_EMPTY_SUMP:
                    str = "ALARM_TYPE_EMPTY_SUMP";
                    break;
                case ALARM_TYPE_LOW_MAKEUP_PRESSURE:
                    str = "ALARM_TYPE_LOW_MAKEUP_PRESSURE";
                    break;
                case ALARM_TYPE_HIGH_TEMP:
                    str = "ALARM_TYPE_HIGH_TEMP";
                    break;
                case ALARM_TYPE_LOW_TEMP:
                    str = "ALARM_TYPE_LOW_TEMP";
                    break;
                case ALARM_TYPE_O1_LID_OPEN:
                    str = "ALARM_TYPE_O1_LID_OPEN";
                    break;
                case ALARM_TYPE_O2_LID_OPEN:
                    str = "ALARM_TYPE_O2_LID_OPEN";
                    break;
                case ALARM_TYPE_S_LID_OPEN:
                    str = "ALARM_TYPE_S_LID_OPEN";
                    break;
                case ALARM_TYPE_P2_LID_OPEN:
                    str = "ALARM_TYPE_P2_LID_OPEN";
                    break;
                case ALARM_TYPE_O1_PRODUCT_EMPTY:
                    str = "ALARM_TYPE_O1_PRODUCT_EMPTY";
                    break;
                case ALARM_TYPE_O2_PRODUCT_EMPTY:
                    str = "ALARM_TYPE_O2_PRODUCT_EMPTY";
                    break;
                case ALARM_TYPE_S_PRODUCT_EMPTY:
                    str = "ALARM_TYPE_S_PRODUCT_EMPTY";
                    break;
                case ALARM_TYPE_P2_PRODUCT_EMPTY:
                    str = "ALARM_TYPE_P2_PRODUCT_EMPTY";
                    break;
                case ALARM_TYPE_S_LOW_PRODUCT:
                    str = "ALARM_TYPE_S_LOW_PRODUCT";
                    break;
                case ALARM_TYPE_P2_LOW_PRODUCT:
                    str = "ALARM_TYPE_P2_LOW_PRODUCT";
                    break;
                case ALARM_TYPE_EXCESSIVE_TIME_SINCE_SUMP_FILL:
                    str = "ALARM_TYPE_EXCESSIVE_TIME_SINCE_SUMP_FILL";
                    break;
                case ALARM_TYPE_EXCEED_MAX_TIME_BETWEEN_BFWP_CALLS:
                    str = "ALARM_TYPE_EXCEED_MAX_TIME_BETWEEN_BFWP_CALLS";
                    break;
                case ALARM_TYPE_INTERNET_CONNECTIVITY_LOST:
                    str = "ALARM_TYPE_INTERNET_CONNECTIVITY_LOST";
                    break;

            }
            return str;
        }

        /*!
            Method to return a printable alarm status for debugging.
        */
        std::string AlarmStatusToString(Alarm::AlarmStatus status)
        {
            std::string str;
            switch(status)
            {
                case Alarm::ALARM_STATUS_NONE:
                    str = "None";
                    break;
                case Alarm::ALARM_STATUS_ACTIVE:
                    str = "Active";
                    break;
                case Alarm::ALARM_STATUS_LOW_ALARM:
                    str = "LowAlarm";
                    break;
                case Alarm::ALARM_STATUS_HIGH_ALARM:
                    str = "HighAlarm";
                    break;
                case Alarm::ALARM_STATUS_LOW_ALERT:
                    str = "LowAlert";
                    break;
                case Alarm::ALARM_STATUS_HIGH_ALERT:
                    str = "HighAlert";
                    break;
            }
            return str;
        }

        std::string AlarmTypeRange(AlarmType type);
        std::string AlarmTypeProperties(AlarmType type);

        void PrintAlarmRanges()
        {
            std::cout << std::endl;
            std::cout << "Alarm\t\tAlertActiveThreshold\tAlarmActiveThreshold\t\tEnvisionActiveThreshold\ttAlertDeactiveThreshold\ttAlarmDeactiveThreshold\ttAlarmDeactiveThreshold\ttEnvisionEnable\ttStopSump\ttStopDispense" << std::endl;
            for(int it = (int) ALARM_TYPE_SIMON_IO_COMM_ERROR; it <= (int) ALARM_TYPE_INTERNET_CONNECTIVITY_LOST; ++it)
            {
            	boost::shared_ptr<GarfunkelAlarm> alarm = GetAlarmByType((AlarmType)it);
                if(alarm)
                {
                	std::cout<<AlarmTypeProperties((AlarmType)it);

                }
                else
                {
                	std::cout<<"Alarm not present";
                }
                std::cout<< std::endl;
            }

        }

        ecolab::Shareable<int>          ESRAlarmCount;
		ecolab::MutexLock                   AlarmDataCommInProgress;  /*mutex that needs to be acquired either by the UI thread
		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 or FBox thread before it makes changes to alarm data.*/



};


class AlarmHandler : public  ecolab::Thread
{
private:
	boost::shared_ptr< ecolab::ISocketCommunication >                           pSocketRS485Socket;
	BOOLEAN        _continue;

public:
	AlarmHandler(const std::string & name);
	AlarmHandler(const AlarmHandler& objectToCopy);
	virtual ~AlarmHandler();
	virtual int Run();
	virtual void Cleanup();
	BOOLEAN Initialize();
};

}
#endif  //_ALARMHANDLER_H
