#if !defined(_ALARM_H)
#define _ALARM_H
#include "GarfunkelData.h"

namespace Garfunkel
{
class Alarm
{
    public:
        /*!
            Constructor method for Alarm.
        */

        Alarm();
        Alarm(const Alarm &     objectToCopy);

        /*!
            Destructor method for Alarm.
        */
        virtual ~Alarm();

        /*!
            Assignment operator
        */
        Alarm& operator=(const Alarm &  objectToAssign);

        /*!
        */
        enum AlarmStatus
        {
            ALARM_STATUS_NONE = 0,
            ALARM_STATUS_ACTIVE = 1,
            ALARM_STATUS_LOW_ALARM = 2,
            ALARM_STATUS_HIGH_ALARM = 3,
            ALARM_STATUS_LOW_ALERT = 4,
            ALARM_STATUS_HIGH_ALERT = 5
        };


        double GetValue() const;


        AlarmStatus GetStatus() const;
        void SetStatus(AlarmStatus status);

        /*!
            Method to check the alarm/alert conditions to see if the status needs to change.

            \param[in]  None

            \param[out] None

            \return     Whether (true) or not (false) the alarm status has changed.
        */
        virtual bool CheckAlarmConditions() = 0;

        /*!
            Method to handle any changes to the MCA that maybe required due to a true alarm state

            \param[in]  None

            \param[out] None

            \return     True if the alarm/alert action was successfully handled
        */
        virtual bool HandleAlarmAction() = 0;

        /*!
            Method to handle any changes to the MCA that maybe required the alarm/alert to be cancelled

            \param[in]  None

            \param[out] None

            \return     True if the alarm/alert action was successfully handled
        */
        virtual bool CancelAlarmAction() = 0;

        void SetAlertLowLevel(double alertLowLevel)
        {
            _alertLowLevel = alertLowLevel;
        }

        void SetAlertHighLevel(double alertHighLevel)
        {
            _alertHighLevel = alertHighLevel;
        }

        void SetAlarmLowLevel(double alarmLowLevel)
        {
            _alarmLowLevel = alarmLowLevel;
        }

        void SetAlarmHighLevel(double alarmHighLevel)
        {
            _alarmHighLevel = alarmHighLevel;
        }

        void SetAlarmTimeThreshold(int alarmThreshold)
        {
            _alarmTimeThreshold = alarmThreshold;
        }


        void SetAlertTimeThreshold(int alertThreshold)
        {
            _alertTimeThreshold = alertThreshold;
        }


        void StartAlertActivation()
        {
            clock_gettime(CLOCK_MONOTONIC, &_alertActivationTime);
            _alertEventStarted = true;
        }

        void StartAlarmActivation()
        {
            clock_gettime(CLOCK_MONOTONIC, &_alarmActivationTime);
            _alarmEventStarted = true;
        }

        double GetAlertLowLevel() const { return _alertLowLevel; }
        double GetAlertHighLevel() const { return _alertHighLevel; }
        double GetAlarmLowLevel() const { return _alarmLowLevel; }
        double GetAlarmHighLevel() const { return _alarmHighLevel; }
        timespec GetTimeOfAlarmActivation() const { return _alarmActivationTime; }
        timespec GetTimeOfAlertActivation() const { return _alertActivationTime; }

        unsigned int TimeInAlertInSeconds();
        unsigned int TimeInAlarmInSeconds();
        bool    IsAlertTimeThresholdReached();
        bool    IsAlarmTimeThresholdReached();
        bool    IsAlertStarted();
        bool    IsAlarmStarted();

        virtual bool    WriteAlarmValuesToFlatFile(std::fstream &   outputStream) = 0;
        virtual bool    ReadAlarmValuesFromFlatFile(std::fstream &  inputStream) = 0;

        void    ClearAlarmStartTime();
        void    ClearAlertStartTime();

        bool    IsModified();

        int     GetRepeatTime();

    protected:
        ecolab::Shareable<AlarmStatus> _status;     //!< The current alarm status.

        double          _value;                              //!< The current value that is monitored by the alarm.
        double          _alertLowLevel;                      //!< The low level alert condition value (e.g. trigger an alert if value drops below this).
        double          _alertHighLevel;                     //!< The high level alert condition value (e.g. trigger an alert if the value goes above this).
        double          _alarmLowLevel;                      //!< The low level alarm condition value (e.g. trigger an alarm if the value goes below this).
        double          _alarmHighLevel;                     //!< used to be alert samples, The high level alarm condition value (e.g. trigger an alarm if the value goes above this).
        unsigned int    _alertTimeThreshold;                //activation delay
        unsigned int    _alarmTimeThreshold;                //condor
        timespec        _alertActivationTime;
        timespec        _alarmActivationTime;
        bool            _alarmEventActive;
        bool            _alertEventActive;                   //!< Per alarm/alert, tracks if has sent its notification.
        bool            _alertEventStarted;
        bool            _alarmEventStarted;
        int             _repeatTime;                        //!< The alarm repeat time if still active.  Initially this will come from a hard coded value, but eventually it will be moved to the database
        bool            _alertSent;
        ecolab::Shareable<AlarmStatus> _alertAlarmStatus;   //!< This is set only when the object is in alarm or alert.

        /*!
            Method to check if the current value is within the alert/alarm range.
        */
        AlarmStatus GetStatusForRange(double value);

        /*!
            Method to send an activation of an alarm/alert to Axeda
        */
        void  SetAlertAlarmStatus(int alarmStatus);
        void  ClearAlertAlarmStatus();
        AlarmStatus GetAlertAlarmStatus() const;

        /*
            Temporary, this is only for field test(June 2013) and now Market test (3Feb2015)
        */
        bool    SendEmail(const std::string & fileName, const std::string & emailMessage, const std::string & errorCode);

        bool    GetAlarmActive() {return _alarmEventActive;}
        void    SetAlarmState(bool bActive) {  _alarmEventActive = bActive;}
        bool    GetAlertActive() {return _alertEventActive;}
        void    SetAlertState(bool bActive) {_alertEventActive = bActive;}
};


class GarfunkelAlarm : public Alarm
{
public:

	GarfunkelAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
				   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmCondorDeactivationTimeThreshold);
	GarfunkelAlarm(const GarfunkelAlarm &     objectToCopy);

    /*!
        Destructor method for Alarm.
    */
    virtual ~GarfunkelAlarm();

    /*!
        Assignment operator
    */
    GarfunkelAlarm& operator=(const GarfunkelAlarm &  objectToAssign);

    bool CheckGarfunkelAlarmConditions(double value);
    bool HandleAlarmAction();
    bool CancelAlarmAction();

    void SetEnvisionAlarmTimeThreshold(int alarmThreshold)
    {
    	_alarmEnvisionTimeThreshold = alarmThreshold;
    }

    void StartEnvisionAlarmActivation()
    {
        clock_gettime(CLOCK_MONOTONIC, &_alarmEnvisionActivationTime);
        _alarmEnvisionEventStarted = true;
    }

    void StartAlertDeactivation()
    {
        clock_gettime(CLOCK_MONOTONIC, &_alertDeactivationTime);
        _alertDeactivationEventStarted = true;
    }

    void StartAlarmDeactivation()
    {
        clock_gettime(CLOCK_MONOTONIC, &_alarmDeactivationTime);
        _alarmDeactivationEventStarted = true;
    }

    void StartEnvisionAlarmDeactivation()
    {
        clock_gettime(CLOCK_MONOTONIC, &_alarmEnvisionDeactivationTime);
        _alarmEnvisionDeactivationEventStarted = true;
    }

    void SetAlarmSettings(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
    {

    }
    timespec GetTimeOfEnvisionAlarmActivation() const { return _alarmEnvisionActivationTime; }

    unsigned int TimeInEnvisionAlarmInSeconds();

    void SetAlertDeactivationTimeThreshold(int threshold)
    {
    	_alertDeactivationTimeThreshold = threshold;
    }


    void SetAlarmDeactivationTimeThreshold(int threshold)
    {
    	_alarmDeactivationTimeThreshold = threshold;
    }

    void SetEnvisionAlarmDeactivationTimeThreshold(int threshold)
    {
    	_alarmEnvisionDeactivationTimeThreshold = threshold;
    }

    unsigned int TimeInAlertDeactivationInSeconds();
    unsigned int TimeInAlarmDeactivationInSeconds();
    unsigned int TimeInEnvisionAlarmDeactivationInSeconds();

    bool    IsEnvisionAlarmTimeThresholdReached();

    bool    IsAlertDeactivationThresholdReached();
    bool    IsAlarmDeactivationThresholdReached();
    bool    IsEnvisionAlarmDeactivationThresholdReached();

    bool    IsEnvisionAlarmStarted();

    bool    IsAlertDeactivationStarted();
    bool    IsAlarmDeactivationStarted();
    bool    IsEnvisionAlarmDeactivationStarted();

    void    ClearEnvisionAlarmStartTime();
    void    ClearAlertDeactivationStartTime();
    void    ClearAlarmDeactivationStartTime();
    void    ClearEnvisionAlarmDeactivationStartTime();

    bool    GetEnvisionEnableState() {return _isEnvisionEnabled;}
    void    SetEnvisionEnableState(bool bActive) {_isEnvisionEnabled = bActive;}

    bool    GetStopSumpCreationState() {return _stopSumpCreation;}
    void    SetStopSumpCreationState(bool bActive) {_stopSumpCreation = bActive;}

    bool    GetStopDispenseState() {return _stopDispense;}
    void    SetStopDispenseState(bool bActive) {_stopDispense = bActive;}


    unsigned int GetAlertTimeThreshold()
    {
        return _alertTimeThreshold;
    }

    unsigned int GetAlarmTimeThreshold()
    {
        return _alarmTimeThreshold;
    }

    unsigned int GetEnvisionAlarmTimeThreshold()
    {
        return _alarmEnvisionTimeThreshold;
    }


    unsigned int GetAlertDeactivationTimeThreshold()
    {
        return _alertDeactivationTimeThreshold;
    }

    unsigned int GetAlarmDeactivationTimeThreshold()
    {
        return _alarmDeactivationTimeThreshold;
    }

    unsigned int GetEnvisionAlarmDeactivationTimeThreshold()
    {
        return _alarmEnvisionDeactivationTimeThreshold;
    }

    bool    WriteAlarmValuesToFlatFile(std::fstream &   outputStream);
    bool    ReadAlarmValuesFromFlatFile(std::fstream &  inputStream);

protected:
    bool             _stopSumpCreation; //
    bool             _stopDispense; //
    bool             _isEnvisionEnabled; //

    unsigned int    _alarmEnvisionTimeThreshold;                //activation delay
    timespec        _alarmEnvisionActivationTime;

    timespec        _alertDeactivationTime;
    timespec        _alarmDeactivationTime;
    timespec        _alarmEnvisionDeactivationTime;

    bool            _alarmEnvisionEventActive;

    bool            _alarmEnvisionEventStarted;
    bool            _alertDeactivationEventStarted;
    bool            _alarmDeactivationEventStarted;
    bool            _alarmEnvisionDeactivationEventStarted;


    unsigned int    _alertDeactivationTimeThreshold;
    unsigned int    _alarmDeactivationTimeThreshold;
    unsigned int    _alarmEnvisionDeactivationTimeThreshold;


    AlarmStatus GetStatusForTime(double value);

    bool    GetEnvisionAlarmActive() {return _alarmEnvisionEventActive;}
    void    SetEnvisionAlarmState(bool bActive) {_alarmEnvisionEventActive = bActive;}



};

class IOSimonCommunicationAlarm : public GarfunkelAlarm
{
    public:
        /*
            Constructor method for IOCommunicationAlarm.
        */
        IOSimonCommunicationAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
				   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmCondorDeactivationTimeThreshold);

        /*!
            Destructor method for IOCommunicationAlarm.
        */
        virtual ~IOSimonCommunicationAlarm();

        /*!
            Method to check the alarm conditionds to see if the status needs to change.
        */
        bool CheckAlarmConditions();

        /*!
            Method to handle any changes to the MCA that maybe required due to a true alarm state
        */
        bool HandleAlarmAction();

        /*!
            Method to handle the cancellation of an Alarm or Alert state.
        */
        bool CancelAlarmAction();

    private:
};



class IOGarfunkelCommunicationAlarm : public GarfunkelAlarm
{
    public:
        /*
            Constructor method for IOCommunicationAlarm.
        */
	IOGarfunkelCommunicationAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        /*!
            Destructor method for IOCommunicationAlarm.
        */
        virtual ~IOGarfunkelCommunicationAlarm();

        /*!
            Method to check the alarm conditionds to see if the status needs to change.
        */
        bool CheckAlarmConditions();

        /*!
            Method to handle any changes to the MCA that maybe required due to a true alarm state
        */
        bool HandleAlarmAction();

        /*!
            Method to handle the cancellation of an Alarm or Alert state.
        */
        bool CancelAlarmAction();

    private:
};

class OverHighTempAlarm : public GarfunkelAlarm
{
    public:
		OverHighTempAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~OverHighTempAlarm();
        bool CheckAlarmConditions();

    private:
};

class SumpOverFlowAlarm : public GarfunkelAlarm
{
    public:
	SumpOverFlowAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~SumpOverFlowAlarm();
        bool CheckAlarmConditions();

    private:
};

class NoORemainsInBothCapsuleAlarm : public GarfunkelAlarm
{
    public:
	NoORemainsInBothCapsuleAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~NoORemainsInBothCapsuleAlarm();
        bool CheckAlarmConditions();

    private:
};

class EmptySumpAlarm : public GarfunkelAlarm
{
    public:
	EmptySumpAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~EmptySumpAlarm();
        bool CheckAlarmConditions();

    private:
};

class LowMakeupPressureAlarm : public GarfunkelAlarm
{
    public:
	LowMakeupPressureAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~LowMakeupPressureAlarm();
        bool CheckAlarmConditions();

    private:
};


class HighTempAlarm : public GarfunkelAlarm
{
    public:

		HighTempAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~HighTempAlarm();

        bool CheckAlarmConditions();


    private:
};

class LowTempAlarm : public GarfunkelAlarm
{
    public:

		LowTempAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~LowTempAlarm();

        bool CheckAlarmConditions();


    private:
};

class O1CapsuleLidOpenAlarm : public GarfunkelAlarm
{
    public:
		O1CapsuleLidOpenAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~O1CapsuleLidOpenAlarm();
        bool CheckAlarmConditions();

    private:
};

class O2CapsuleLidOpenAlarm : public GarfunkelAlarm
{
    public:
		O2CapsuleLidOpenAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~O2CapsuleLidOpenAlarm();
        bool CheckAlarmConditions();

    private:
};

class SBlockLidOpenAlarm : public GarfunkelAlarm
{
    public:
		SBlockLidOpenAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~SBlockLidOpenAlarm();
        bool CheckAlarmConditions();

    private:
};

class PBlockLidOpenAlarm : public GarfunkelAlarm
{
    public:
		PBlockLidOpenAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~PBlockLidOpenAlarm();
        bool CheckAlarmConditions();

    private:
};


class O1ProductEmptyAlarm : public GarfunkelAlarm
{
    public:
		O1ProductEmptyAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~O1ProductEmptyAlarm();
        bool CheckAlarmConditions();
        bool HandleAlarmAction();
        bool CancelAlarmAction();


    private:
};

class O2ProductEmptyAlarm : public GarfunkelAlarm
{
    public:
		O2ProductEmptyAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~O2ProductEmptyAlarm();
        bool CheckAlarmConditions();
        //bool HandleAlarmAction();
        //bool CancelAlarmAction();


    private:
};

class SProductEmptyAlarm : public GarfunkelAlarm
{
    public:
		SProductEmptyAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~SProductEmptyAlarm();
        bool CheckAlarmConditions();

    private:
};

class PProductEmptyAlarm : public GarfunkelAlarm
{
    public:
		PProductEmptyAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~PProductEmptyAlarm();
        bool CheckAlarmConditions();

    private:
};

class SLowPProductAlarm : public GarfunkelAlarm
{
    public:
		SLowPProductAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~SLowPProductAlarm();
        bool CheckAlarmConditions();
        bool HandleAlarmAction();
        bool CancelAlarmAction();

    private:
};

class PLowPProductAlarm : public GarfunkelAlarm
{
    public:
		PLowPProductAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~PLowPProductAlarm();
        bool CheckAlarmConditions();
        bool HandleAlarmAction();
        bool CancelAlarmAction();

    private:
};

class ExcessiveTimeSinceSumpFillAlarm : public GarfunkelAlarm
{
    public:
		ExcessiveTimeSinceSumpFillAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~ExcessiveTimeSinceSumpFillAlarm();
        bool CheckAlarmConditions();
        bool HandleAlarmAction();
        bool CancelAlarmAction();

    private:
};

class ExceedMaxTimeBetweenBFWPCallAlarm : public GarfunkelAlarm
{
    public:
		ExceedMaxTimeBetweenBFWPCallAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
			   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold);

        virtual ~ExceedMaxTimeBetweenBFWPCallAlarm();
        bool CheckAlarmConditions();
        bool HandleAlarmAction();
        bool CancelAlarmAction();

    private:
};



}
#endif  //_ALARM_H
