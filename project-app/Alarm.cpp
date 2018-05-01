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
#include "GarfunkelEnums.h"

Garfunkel::Alarm::Alarm() :
    _status(ALARM_STATUS_NONE),
    _value(0),
    _alertLowLevel(0),
    _alertHighLevel(0),
    _alarmLowLevel(0),
    _alarmHighLevel(0),
    _alertTimeThreshold(0),
    _alarmTimeThreshold(0),
    _alarmEventActive(false),
    _alertEventActive(false),
    _alertEventStarted(false),
    _alarmEventStarted(false),
    _repeatTime(720),
    _alertSent(false),
    _alertAlarmStatus(ALARM_STATUS_NONE)
{
    // Default ctor

    memset(&_alertActivationTime, 0, sizeof(timespec));
    memset(&_alarmActivationTime, 0, sizeof(timespec));
}


/*!
    Copy Constructor method for Alarm.

    \param[in]  body    Pointer to WaterBody instance.

    \param[out] None

    \return     None
*/
Garfunkel::Alarm::Alarm(const Alarm &     objectToCopy)
{
    _status.Set(objectToCopy._status.Get());
    _value = objectToCopy._value;
    _alertLowLevel = objectToCopy._alertLowLevel;
    _alertHighLevel = objectToCopy._alertHighLevel;
    _alarmLowLevel = objectToCopy._alarmLowLevel;
    _alarmHighLevel = objectToCopy._alarmHighLevel;
    _alarmTimeThreshold = objectToCopy._alarmTimeThreshold;
    _alertTimeThreshold = objectToCopy._alertTimeThreshold;
    _alertActivationTime = objectToCopy._alertActivationTime;
    _alarmActivationTime = objectToCopy._alarmActivationTime;
    _alertEventActive = objectToCopy._alertEventActive;
    _alarmEventActive = objectToCopy._alarmEventActive;
    _alertEventStarted = objectToCopy._alertEventStarted;
    _alarmEventStarted = objectToCopy._alarmEventStarted;
    _repeatTime = objectToCopy._repeatTime;
    _alertSent = objectToCopy._alertSent;
    _alertAlarmStatus.Set(objectToCopy._alertAlarmStatus.Get());
}

/*!
    Destructor method for Alarm.

    \param[in]  None

    \param[out] None

    \return     None
*/
Garfunkel::Alarm::~Alarm()
{
    /*
        Empty.
    */
}

/*!
    Assignment operator.

    \param[in]  objectToAssign

    \param[out] None

    \return     None
*/
Garfunkel::Alarm& Garfunkel::Alarm::operator=(const Alarm &  objectToAssign)
{
    _status.Set(objectToAssign._status.Get());
    _value = objectToAssign._value;
    _alertLowLevel = objectToAssign._alertLowLevel;
    _alertHighLevel = objectToAssign._alertHighLevel;
    _alarmLowLevel = objectToAssign._alarmLowLevel;
    _alarmHighLevel = objectToAssign._alarmHighLevel;
    _alarmTimeThreshold = objectToAssign._alarmTimeThreshold;
    _alertTimeThreshold = objectToAssign._alertTimeThreshold;
    _alertActivationTime = objectToAssign._alertActivationTime;
    _alarmActivationTime = objectToAssign._alarmActivationTime;
    _alertEventActive = objectToAssign._alertEventActive;
    _alarmEventActive = objectToAssign._alarmEventActive;
    _alertEventStarted = objectToAssign._alertEventStarted;
    _alarmEventStarted = objectToAssign._alarmEventStarted;
    _repeatTime = objectToAssign._repeatTime;
    _alertSent = objectToAssign._alertSent;
    _alertAlarmStatus.Set(objectToAssign._alertAlarmStatus.Get());

    return *this;
}


/*!
    Method to return the value that is monitored by the alarm.

    \param[in]  None

    \param[out] None

    \return     The value that is monitored by the alarm (e.g. current pH).
*/
double Garfunkel::Alarm::GetValue() const
{
    return _value;
}

/*!
    Method to return the status of the alarm.

    \param[in]  None

    \param[out] None

    \return     The status of the alarm.
*/
Garfunkel::Alarm::AlarmStatus Garfunkel::Alarm::GetStatus() const
{
    return _status.Get();
}

/*!
    Method to set the status of an alarm

    \param[in]  None

    \param[out] None

    \return     The status of the alarm.
*/
void Garfunkel::Alarm::SetStatus(Garfunkel::Alarm::AlarmStatus status)
{
    _status.Set(status);
}



Garfunkel::GarfunkelAlarm::GarfunkelAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold) :
		_alarmEnvisionTimeThreshold(alarmEnvisionTimeThreshold),
		_alertDeactivationTimeThreshold(alertDeactivationTimeThreshold),
		_alarmDeactivationTimeThreshold(alarmDeactivationTimeThreshold),
		_alarmEnvisionDeactivationTimeThreshold(alarmEnvisionDeactivationTimeThreshold),
		_alertDeactivationEventStarted(false),
		_alarmDeactivationEventStarted(false),
		_alarmEnvisionDeactivationEventStarted(false),
		_alarmEnvisionEventActive(false),
		_stopSumpCreation(false),
		_stopDispense(false),
		_isEnvisionEnabled(true)
{
    // Default ctor

    memset(&_alarmEnvisionActivationTime, 0, sizeof(timespec));
    memset(&_alertDeactivationTime, 0, sizeof(timespec));
    memset(&_alarmDeactivationTime, 0, sizeof(timespec));
    memset(&_alarmEnvisionDeactivationTime, 0, sizeof(timespec));



    _alertTimeThreshold = alertTimeThreshold; // this is debounce TODO , remove these..this is just for testing
    _alarmTimeThreshold = alarmTimeThreshold; //condor delay ..TODO , remove these..this is just for testing
    //_alarmEnvisionTimeThreshold = 5; //envisison delay..TODO , remove these..this is just for testing

/*
    _alertDeactivationTimeThreshold = 5; // this is debounce TODO , remove these..this is just for testing
    _alarmDeactivationTimeThreshold = 5; //condor delay ..TODO , remove these..this is just for testing
    _alarmEnvisionDeactivationTimeThreshold = 5; //envisison delay..TODO , remove these..this is just for testing*/
}

Garfunkel::GarfunkelAlarm::~GarfunkelAlarm()
{
    /*
        Empty.
    */
}

Garfunkel::GarfunkelAlarm::GarfunkelAlarm(const GarfunkelAlarm &     objectToCopy)
{
    _status.Set(objectToCopy._status.Get());
    _value = objectToCopy._value;
    _alertLowLevel = objectToCopy._alertLowLevel;
    _alertHighLevel = objectToCopy._alertHighLevel;
    _alarmLowLevel = objectToCopy._alarmLowLevel;
    _alarmHighLevel = objectToCopy._alarmHighLevel;
    _alarmTimeThreshold = objectToCopy._alarmTimeThreshold;
    _alertTimeThreshold = objectToCopy._alertTimeThreshold;
    _alertActivationTime = objectToCopy._alertActivationTime;
    _alarmActivationTime = objectToCopy._alarmActivationTime;
    _alertEventActive = objectToCopy._alertEventActive;
    _alarmEventActive = objectToCopy._alarmEventActive;
    _alertEventStarted = objectToCopy._alertEventStarted;
    _alarmEventStarted = objectToCopy._alarmEventStarted;
    _repeatTime = objectToCopy._repeatTime;
    _alertSent = objectToCopy._alertSent;
    _alertAlarmStatus.Set(objectToCopy._alertAlarmStatus.Get());
    _alarmEnvisionEventActive = objectToCopy._alarmEnvisionEventActive;
    _alarmEnvisionTimeThreshold = objectToCopy._alarmEnvisionTimeThreshold;
    _alarmEnvisionActivationTime = objectToCopy._alarmEnvisionActivationTime;
    _alertDeactivationTime = objectToCopy._alertDeactivationTime;
    _alarmDeactivationTime = objectToCopy._alarmDeactivationTime;
    _alarmEnvisionDeactivationTime = objectToCopy._alarmEnvisionDeactivationTime;
	_alertDeactivationTimeThreshold = objectToCopy._alertDeactivationTimeThreshold;
	_alarmDeactivationTimeThreshold = objectToCopy._alarmDeactivationTimeThreshold;
	_alarmEnvisionDeactivationTimeThreshold = objectToCopy._alarmEnvisionDeactivationTimeThreshold;
	_stopSumpCreation = objectToCopy._stopSumpCreation;
	_stopDispense = objectToCopy._stopDispense;
	_isEnvisionEnabled = objectToCopy._isEnvisionEnabled;


}


Garfunkel::GarfunkelAlarm& Garfunkel::GarfunkelAlarm::operator=(const GarfunkelAlarm &  objectToAssign)
{
    _status.Set(objectToAssign._status.Get());
    _value = objectToAssign._value;
    _alertLowLevel = objectToAssign._alertLowLevel;
    _alertHighLevel = objectToAssign._alertHighLevel;
    _alarmLowLevel = objectToAssign._alarmLowLevel;
    _alarmHighLevel = objectToAssign._alarmHighLevel;
    _alarmTimeThreshold = objectToAssign._alarmTimeThreshold;
    _alertTimeThreshold = objectToAssign._alertTimeThreshold;
    _alertActivationTime = objectToAssign._alertActivationTime;
    _alarmActivationTime = objectToAssign._alarmActivationTime;
    _alertEventActive = objectToAssign._alertEventActive;
    _alarmEventActive = objectToAssign._alarmEventActive;
    _alertEventStarted = objectToAssign._alertEventStarted;
    _alarmEventStarted = objectToAssign._alarmEventStarted;
    _repeatTime = objectToAssign._repeatTime;
    _alertSent = objectToAssign._alertSent;
    _alertAlarmStatus.Set(objectToAssign._alertAlarmStatus.Get());
    _alarmEnvisionEventActive = objectToAssign._alarmEnvisionEventActive;
    _alarmEnvisionTimeThreshold = objectToAssign._alarmEnvisionTimeThreshold;
    _alarmEnvisionActivationTime = objectToAssign._alarmEnvisionActivationTime;
    _alertDeactivationTime = objectToAssign._alertDeactivationTime;
    _alarmDeactivationTime = objectToAssign._alarmDeactivationTime;
    _alarmEnvisionDeactivationTime = objectToAssign._alarmEnvisionDeactivationTime;
	_alertDeactivationTimeThreshold = objectToAssign._alertDeactivationTimeThreshold;
	_alarmDeactivationTimeThreshold = objectToAssign._alarmDeactivationTimeThreshold;
	_alarmEnvisionDeactivationTimeThreshold = objectToAssign._alarmEnvisionDeactivationTimeThreshold;
	_stopSumpCreation = objectToAssign._stopSumpCreation;
	_stopDispense = objectToAssign._stopDispense;
	_isEnvisionEnabled = objectToAssign._isEnvisionEnabled;

    return *this;
}



/*!
    Method to check if the current value is within the alert/alarm range.

    \param[in]  value   The current value to compare against the alert/alarm range.

    \param[out] None

    \return     The AlarmStatus based on the current value.
*/
Garfunkel::Alarm::AlarmStatus Garfunkel::Alarm::GetStatusForRange(double value)
{
    AlarmStatus status;

    if(value <= _alarmLowLevel && _alarmLowLevel != 0)
    {
        status = ALARM_STATUS_LOW_ALARM;
    }
    else if(value >= _alarmHighLevel && _alarmHighLevel != 0 )
    {
        status = ALARM_STATUS_HIGH_ALARM;
    }
    else if(value <= _alertLowLevel && _alertLowLevel != 0 )
    {
        status = ALARM_STATUS_LOW_ALERT;
    }
    else if(value >= _alertHighLevel && _alertHighLevel != 0)
    {
        status = ALARM_STATUS_HIGH_ALERT;
    }
    else
    {
        status = ALARM_STATUS_NONE;
    }

    // Increment the counter for the alarm/alert condition
    if((ALARM_STATUS_LOW_ALERT == status || ALARM_STATUS_HIGH_ALERT == status)
        && false == IsAlertStarted() && false == GetAlertActive())
    {
        StartAlertActivation();
    }
    else if((ALARM_STATUS_LOW_ALARM == status || ALARM_STATUS_HIGH_ALARM == status)
        && false == IsAlarmStarted() && false == GetAlarmActive())
    {
        StartAlarmActivation();
    }
    else if(ALARM_STATUS_NONE == status)
    {
        // Check if a time has started, if so clear its respective time, this should not be
        //  done in the individual alarms.  The individual alarms will handle its behavior
        //  for setting and clearing the alarms.
        if(true == IsAlertStarted())
        {
//std::cout << "[Alarm::GetStatusForRange] Clear Alert Activiation" << std::endl;
            ClearAlertStartTime();
        }

        if(true == IsAlarmStarted())
        {
//std::cout << "[Alarm::GetStatusForRange] Clear Alarm Activiation" << std::endl;
            ClearAlarmStartTime();
        }
    }
    else
    {
        // Do Nothing
    }

    return status;
}

bool Garfunkel::GarfunkelAlarm::CheckGarfunkelAlarmConditions(double value)
{
	bool retValue = false;
	AlarmStatus before(GetStatus());
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    _value = value;

    AlarmStatus after = GetStatusForTime(value);

/*    std::cout<<"before="<<before<<std::endl;
    std::cout<<"after="<<after<<std::endl;*/

    if(ALARM_STATUS_NONE != after)
    {
    	if(true == IsAlertStarted() && false == GetAlertActive())
    	{
    		if(true == IsAlertTimeThresholdReached())
    		{
    			SetAlertState(true);
    			retValue = true;
    		}
    	}

    	if(true == IsAlarmStarted() && false == GetAlarmActive())
    	{
    		if(true == IsAlarmTimeThresholdReached())
    		{
    			if(false == GetAlertActive())
    			{
    				SetAlertState(true);
    			}

    			SetAlarmState(true);
    			retValue = true;
    		}
    	}

    	if(true == IsEnvisionAlarmStarted() && false == GetEnvisionAlarmActive())
    	{
    		if(true == IsEnvisionAlarmTimeThresholdReached())
    		{
    			if(false == GetAlertActive())
    			{
    				SetAlertState(true);
    			}
    			if(false == GetAlarmActive())
    			{
    				SetAlarmState(true);
    			}

    			SetEnvisionAlarmState(true);
    			retValue = true;
    		}
    	}

    }
    // Check the alarm clearing state
    if(ALARM_STATUS_NONE == after)
    {
        if(true == IsAlertDeactivationStarted()&& true == GetAlertActive())
        {
        	if(true == IsAlertDeactivationThresholdReached())
      	    {
        		std::cout << "[GarfunkelAlarm::CheckAlarmConditions] clear the alert" << std::endl;
       	        SetAlertState(false);
       	        retValue = true;
      	    }

        }

        else if(true == IsAlarmDeactivationStarted()&&true == GetAlarmActive()&&false == GetAlertActive())
        {
        	if(true == IsAlarmDeactivationThresholdReached())
      	    {
       			std::cout << "[GarfunkelAlarm::CheckAlarmConditions] clear the alarm" << std::endl;
       	        SetAlarmState(false);
       	        retValue = true;
      	    }

        }

        else if(true == IsEnvisionAlarmDeactivationStarted()&&true == GetEnvisionAlarmActive()&&false == GetAlertActive()&&false == GetAlarmActive())
        {
        	if(true == IsEnvisionAlarmDeactivationThresholdReached())
      	    {
       			std::cout << "[GarfunkelAlarm::CheckAlarmConditions] clear the Condor alarm" << std::endl;
       			SetEnvisionAlarmState(false);
       	        retValue = true;
      	    }
        }

    }


    // Capture the current status
    SetStatus(after);
    //std::cout<<" Returning..retValue = "<<retValue<<std::endl;
    return retValue;

}


bool Garfunkel::GarfunkelAlarm::HandleAlarmAction()
{
	 bool        retValue = false;

	    AlarmStatus  alarmStatus = _status.Get();
	   // std::cout << "[OverHighTempAlarm::CheckAlarmConditions] Inside OverHighTempAlarm : HandleAlarmAction" << std::endl;
	    if(alarmStatus==ALARM_STATUS_HIGH_ALERT) //alarm active
	    {
	    	if(GetEnvisionAlarmActive()==true) //check if condor alarm active , then send status to envision
	    	{
	    		std::cout<<" Envision alarm active"<<std::endl;
	    		retValue = true;
	    	}
	    	else if (GetAlarmActive()==true) //check if condor alarm active , tehn send status to envision
	    	{
	    		std::cout<<" Alarm active"<<std::endl;
	    		retValue = true;

	    	}
	    	else if(GetAlertActive()==true)//debounce satisfied
	    	{
	    		std::cout<<" Alert active"<<std::endl;
	    		retValue = true;

	    	}

	    }
	    return retValue;
}


bool Garfunkel::GarfunkelAlarm::CancelAlarmAction()
{
    bool retValue = false;

    AlarmStatus  alarmStatus = _status.Get();

	if(alarmStatus==ALARM_STATUS_NONE) //alarm clear
	{
    	if(GetAlertActive()==false&&IsAlarmDeactivationStarted()==false)
    	{
    		std::cout<<" Alert clear"<<std::endl;
    		retValue = true;
    	}
	   	else if (GetAlarmActive()==false&&IsEnvisionAlarmDeactivationStarted()==false)
	   	{
	   		std::cout<<" Condor Alarm clear"<<std::endl;
	   		retValue = true;
    	}
	   	else if(GetEnvisionAlarmActive()==false)
	   	{
	   		std::cout<<" Envision alarm clear"<<std::endl;
	   		retValue = true;
	   	}
    }

    return retValue;
}


/*!
    Write the current alarm values to a flat file

    \param[in]  outputStream - the fstream to receive the values to be written

    \param[out] None

    \return     None
*/
bool    Garfunkel::GarfunkelAlarm::WriteAlarmValuesToFlatFile(std::fstream &   outputStream)
{
    bool    retValue = false;

    if(True == outputStream.is_open())
    {
        //outputStream << _value << std::endl;
        outputStream << _alarmLowLevel << std::endl;
        outputStream << _alarmHighLevel << std::endl;
        outputStream << _alertTimeThreshold << std::endl;
        outputStream << _alarmTimeThreshold << std::endl;
        outputStream << _alarmEnvisionTimeThreshold << std::endl;
        outputStream << _alertDeactivationTimeThreshold << std::endl;
        outputStream << _alarmDeactivationTimeThreshold << std::endl;
        outputStream << _alarmEnvisionDeactivationTimeThreshold << std::endl;
        outputStream << _isEnvisionEnabled << std::endl;
        outputStream << _stopSumpCreation << std::endl;
        outputStream << _stopDispense << std::endl;
        retValue = true;
    }

    return retValue;
}

/*!
    Read the current alarm values from a flat file

    \param[in]  outputStream - the fstream to retreive the values from a flat file

    \param[out] None

    \return     None
*/
bool    Garfunkel::GarfunkelAlarm::ReadAlarmValuesFromFlatFile(std::fstream &  inputStream)
{
    bool    retValue = false;

    if(True == inputStream.is_open())
    {
        inputStream >> _alarmLowLevel;
        inputStream >> _alarmHighLevel;
        inputStream >> _alertTimeThreshold;
        inputStream >> _alarmTimeThreshold;
        inputStream >> _alarmEnvisionTimeThreshold;
        inputStream >> _alertDeactivationTimeThreshold;
        inputStream >> _alarmDeactivationTimeThreshold;
        inputStream >> _alarmEnvisionDeactivationTimeThreshold;
        inputStream >> _isEnvisionEnabled;
        inputStream >> _stopSumpCreation;
        inputStream >> _stopDispense;

        retValue = true;
    }

    return retValue;
}

unsigned int Garfunkel::GarfunkelAlarm::TimeInEnvisionAlarmInSeconds()
{
    unsigned int timeInAlert = 0;

    if(true == IsEnvisionAlarmStarted())
    {
        timespec currentTime;
        clock_gettime(CLOCK_MONOTONIC, &currentTime);
        const double timeSinceAlertStarted = ElapsedTime(&_alarmEnvisionActivationTime, &currentTime);
        timeInAlert = static_cast<int>(floor(timeSinceAlertStarted));
    }

    return timeInAlert;
}

unsigned int Garfunkel::GarfunkelAlarm::TimeInAlertDeactivationInSeconds()
{
    unsigned int timeInAlarm = 0;

    if(true == IsAlertDeactivationStarted())
    {
        timespec currentTime;
        clock_gettime(CLOCK_MONOTONIC, &currentTime);
        const double timeSinceAlarmStarted = ElapsedTime(&_alertDeactivationTime, &currentTime);
        timeInAlarm = static_cast<int>(floor(timeSinceAlarmStarted));
    }

    return timeInAlarm;
}

unsigned int Garfunkel::GarfunkelAlarm::TimeInAlarmDeactivationInSeconds()
{
    unsigned int timeInAlarm = 0;

    if(true == IsAlarmDeactivationStarted())
    {
        timespec currentTime;
        clock_gettime(CLOCK_MONOTONIC, &currentTime);
        const double timeSinceAlarmStarted = ElapsedTime(&_alarmDeactivationTime, &currentTime);
        timeInAlarm = static_cast<int>(floor(timeSinceAlarmStarted));
    }

    return timeInAlarm;
}

unsigned int Garfunkel::GarfunkelAlarm::TimeInEnvisionAlarmDeactivationInSeconds()
{
    unsigned int timeInAlarm = 0;

    if(true == IsEnvisionAlarmDeactivationStarted())
    {
        timespec currentTime;
        clock_gettime(CLOCK_MONOTONIC, &currentTime);
        const double timeSinceAlarmStarted = ElapsedTime(&_alarmEnvisionDeactivationTime, &currentTime);
        timeInAlarm = static_cast<int>(floor(timeSinceAlarmStarted));
    }

    return timeInAlarm;
}

bool    Garfunkel::GarfunkelAlarm::IsEnvisionAlarmTimeThresholdReached()
{
    bool    bRetValue = false;

    if(true == IsEnvisionAlarmStarted())
    {
        timespec currentTime;
        clock_gettime(CLOCK_MONOTONIC, &currentTime);
        const double timeSinceAlertStarted = ElapsedTime(&_alarmEnvisionActivationTime, &currentTime);

        // Check if the alert threshold time has bee exceeded.  If so trigger the alert
        if(timeSinceAlertStarted > _alarmEnvisionTimeThreshold)
        {
        	std::cout << "[Alarm::IsCondorAlarmTimeThresholdReached] Condor Time: " << timeSinceAlertStarted << std::endl;
            bRetValue = true;
        }
    }

    return bRetValue;
}

bool    Garfunkel::GarfunkelAlarm::IsAlertDeactivationThresholdReached()
{
    bool    bRetValue = false;

    if(true == IsAlertDeactivationStarted())
    {
        timespec currentTime;
        clock_gettime(CLOCK_MONOTONIC, &currentTime);
        const double timeSinceAlarmStarted = ElapsedTime(&_alertDeactivationTime, &currentTime);
        // Check if the alert threshold time has bee exceeded.  If so trigger the alert
        if(timeSinceAlarmStarted > _alertDeactivationTimeThreshold)
        {
        	std::cout << "[Alarm::IsAlertDeactivationThresholdReached] Alert Deativation Time: " << timeSinceAlarmStarted << std::endl;
            bRetValue = true;
        }
    }

    return bRetValue;
}


bool    Garfunkel::GarfunkelAlarm::IsAlarmDeactivationThresholdReached()
{
    bool    bRetValue = false;

    if(true == IsAlarmDeactivationStarted())
    {
        timespec currentTime;
        clock_gettime(CLOCK_MONOTONIC, &currentTime);
        const double timeSinceAlarmStarted = ElapsedTime(&_alarmDeactivationTime, &currentTime);

        // Check if the alert threshold time has bee exceeded.  If so trigger the alert
        if(timeSinceAlarmStarted > _alarmDeactivationTimeThreshold)
        {
        	std::cout << "[Alarm::IsAlarmDeactivationThresholdReached] Alarm Deativation Time: " << timeSinceAlarmStarted << std::endl;
        	bRetValue = true;
        }
    }

    return bRetValue;
}

bool    Garfunkel::GarfunkelAlarm::IsEnvisionAlarmDeactivationThresholdReached()
{
    bool    bRetValue = false;

    if(true == IsEnvisionAlarmDeactivationStarted())
    {
        timespec currentTime;
        clock_gettime(CLOCK_MONOTONIC, &currentTime);
        const double timeSinceAlarmStarted = ElapsedTime(&_alarmEnvisionDeactivationTime, &currentTime);
        // Check if the alert threshold time has bee exceeded.  If so trigger the alert
        if(timeSinceAlarmStarted > _alarmEnvisionDeactivationTimeThreshold)
        {
        	std::cout << "[Alarm::IsCondorAlarmDeactivationThresholdReached] Condor Alarm Deativation Time: " << timeSinceAlarmStarted << std::endl;
            bRetValue = true;
        }
    }

    return bRetValue;
}

bool    Garfunkel::GarfunkelAlarm::IsEnvisionAlarmStarted()
{
    return _alarmEnvisionEventStarted;
}

/*
    Used as a flag to known when a time based event has started
*/
bool    Garfunkel::GarfunkelAlarm::IsAlertDeactivationStarted()
{
    return _alertDeactivationEventStarted;
}

bool    Garfunkel::GarfunkelAlarm::IsAlarmDeactivationStarted()
{
    return _alarmDeactivationEventStarted;
}

bool    Garfunkel::GarfunkelAlarm::IsEnvisionAlarmDeactivationStarted()
{
    return _alarmEnvisionDeactivationEventStarted;
}


void    Garfunkel::GarfunkelAlarm::ClearEnvisionAlarmStartTime()
{
    //memset(&_alarmStarted, 0, sizeof(time_t));
    memset(&_alarmEnvisionActivationTime, 0, sizeof(timespec));
    _alarmEnvisionEventStarted = false;  // New addition
}

void    Garfunkel::GarfunkelAlarm::ClearAlertDeactivationStartTime()
{
    memset(&_alertDeactivationTime, 0, sizeof(timespec));
    _alertDeactivationEventStarted = false; // New addition
}

void    Garfunkel::GarfunkelAlarm::ClearAlarmDeactivationStartTime()
{
    memset(&_alarmDeactivationTime, 0, sizeof(timespec));
    _alarmDeactivationEventStarted = false; // New addition
}

void    Garfunkel::GarfunkelAlarm::ClearEnvisionAlarmDeactivationStartTime()
{
    memset(&_alarmEnvisionDeactivationTime, 0, sizeof(timespec));
    _alarmEnvisionDeactivationEventStarted = false; // New addition
}

Garfunkel::GarfunkelAlarm::AlarmStatus Garfunkel::GarfunkelAlarm::GetStatusForTime(double value)
{
    AlarmStatus status;


    if(value >= _alarmLowLevel && value <_alarmHighLevel )
     {
         status = ALARM_STATUS_HIGH_ALERT;
     }
     else
     {
         status = ALARM_STATUS_NONE;
     }

    // Increment the counter for the alarm/alert condition
    if((ALARM_STATUS_HIGH_ALERT == status)
        && false == IsAlertStarted() && false == GetAlertActive())
    {
        ClearAlertStartTime();
        ClearAlarmStartTime();
        ClearEnvisionAlarmStartTime();
        ClearAlertDeactivationStartTime();
        StartAlertActivation();
        //std::cout << "[Alarm::GetStatusForTime] Starting Alert Activiation" << std::endl;
    }
    else if((ALARM_STATUS_HIGH_ALERT == status)&&true == GetAlertActive()
        && false == IsAlarmStarted() && false == GetAlarmActive())
    {
    	ClearAlarmStartTime();
    	ClearAlarmDeactivationStartTime();
        StartAlarmActivation();
        //std::cout << "[Alarm::GetStatusForTime] Starting Alarm Activiation" << std::endl;
    }
    else if((ALARM_STATUS_HIGH_ALERT == status)&&true == GetAlertActive()
        && true == IsAlarmStarted() && true == GetAlarmActive()
        && false == IsEnvisionAlarmStarted() && false == GetEnvisionAlarmActive())
    {
    	ClearEnvisionAlarmStartTime();
    	ClearEnvisionAlarmDeactivationStartTime();
        StartEnvisionAlarmActivation();
       // std::cout << "[Alarm::GetStatusForTime] Starting Condor Alarm Activiation" << std::endl;
    }

    else if(ALARM_STATUS_NONE == status)
    {

        if(true == IsAlertStarted()&&true == GetAlertActive()&&false == IsAlertDeactivationStarted()) //&& true == IsAlarmStarted()&& true == IsCondorAlarmStarted())
        {
        	//std::cout<<" Clearing alert start time "<<std::endl;
        	ClearAlertStartTime();
        	ClearAlarmDeactivationStartTime();
        	ClearEnvisionAlarmDeactivationStartTime();
        	StartAlertDeactivation();
        }

        else if(true == GetAlarmActive()&&false == IsAlarmDeactivationStarted()&&false == GetAlertActive())
        {
        	//std::cout << "[Alarm::GetStatusForTime] Clear Alarm Activiation" << std::endl;
            ClearEnvisionAlarmDeactivationStartTime();
            StartAlarmDeactivation();
        }

        else if(true == GetEnvisionAlarmActive()&&false == IsEnvisionAlarmDeactivationStarted()&&false == GetAlertActive()&&false == GetAlarmActive())
        {
        	//std::cout << "[Alarm::GetStatusForTime] Clear Condor Alarm Activiation" << std::endl;
            StartEnvisionAlarmDeactivation();
        }

    }
    else
    {
        // Do Nothing
    }

    return status;
}

/*!
    Temporary function for sending an email.

    \param[in]  body

    \param[out] None

    \return     None
*/
bool    Garfunkel::Alarm::SendEmail(const std::string & fileName, const std::string & emailMessage, const std::string & errorCode)
{
    bool retValue = false;
    std::cout<<fileName<<": "<<emailMessage<<": errorCode:"<<errorCode<<std::endl;
    return retValue;
}


/*!
    Get the time_t struct which represents when the alarm has been initiated.

    \param[in]  time_t - fill in the object with the time the alarm was started.

    \param[out] None

    \return     None
*/
    /*
void    PoolSpa::Alarm::GetAlarmStartTime(time_t &  alarmStarted)
{
    alarmStarted = _alarmStarted;
}
*/

/*!
    Reset the time_t object that contains the time the alarm was initiated

    \param[in]  None

    \param[out] None

    \return     None
*/
void    Garfunkel::Alarm::ClearAlarmStartTime()
{
    //memset(&_alarmStarted, 0, sizeof(time_t));
    memset(&_alarmActivationTime, 0, sizeof(timespec));
    _alarmEventStarted = false;  // New addition
}

/*!
    Reset the time_t object that contains the time the alert was initiated

    \param[in]  None

    \param[out] None

    \return     None
*/
void    Garfunkel::Alarm::ClearAlertStartTime()
{
    memset(&_alertActivationTime, 0, sizeof(timespec));
    _alertEventStarted = false; // New addition
}


/*!
    Set the time_t object with the imte the system was initates.

    \param[in]  None

    \param[out] None

    \return     None
*/

/*
bool    PoolSpa::Alarm::SetAlarmStartTime()
{
    bool    retValue = false;

    if(-1 != time(&_alarmStarted))
    {
        retValue = true;
    }

    return retValue;
}
*/

void  Garfunkel::Alarm::SetAlertAlarmStatus(int alarmStatus)
{
    _alertAlarmStatus.Set(static_cast<AlarmStatus>(alarmStatus));
}

void Garfunkel::Alarm::ClearAlertAlarmStatus()
{
    _alertAlarmStatus.Set(ALARM_STATUS_NONE);
}

Garfunkel::Alarm::AlarmStatus Garfunkel::Alarm::GetAlertAlarmStatus() const
{
    return _alertAlarmStatus.Get();
}

int  Garfunkel::Alarm::GetRepeatTime()
{
    return _repeatTime;
}

unsigned int Garfunkel::Alarm::TimeInAlertInSeconds()
{
    unsigned int timeInAlert = 0;

    if(true == IsAlertStarted())
    {
        timespec currentTime;
        clock_gettime(CLOCK_MONOTONIC, &currentTime);
        const double timeSinceAlertStarted = ElapsedTime(&_alertActivationTime, &currentTime);
        timeInAlert = static_cast<int>(floor(timeSinceAlertStarted));
    }

    return timeInAlert;
}

unsigned int Garfunkel::Alarm::TimeInAlarmInSeconds()
{
    unsigned int timeInAlarm = 0;

    if(true == IsAlarmStarted())
    {
        timespec currentTime;
        clock_gettime(CLOCK_MONOTONIC, &currentTime);
        const double timeSinceAlarmStarted = ElapsedTime(&_alarmActivationTime, &currentTime);
        timeInAlarm = static_cast<int>(floor(timeSinceAlarmStarted));
    }

    return timeInAlarm;
}

bool    Garfunkel::Alarm::IsAlertTimeThresholdReached()
{
    bool    bRetValue = false;

    if(true == IsAlertStarted())
    {
        timespec currentTime;
        clock_gettime(CLOCK_MONOTONIC, &currentTime);
        const double timeSinceAlertStarted = ElapsedTime(&_alertActivationTime, &currentTime);
        // Check if the alert threshold time has bee exceeded.  If so trigger the alert
        if(timeSinceAlertStarted > _alertTimeThreshold)
        {
        	std::cout << "[Alarm::IsAlertTimeThresholdReached] Alert Time: " << timeSinceAlertStarted << std::endl;
        	bRetValue = true;
        }
    }

    return bRetValue;
}

bool    Garfunkel::Alarm::IsAlarmTimeThresholdReached()
{
    bool    bRetValue = false;

    if(true == IsAlarmStarted())
    {
        timespec currentTime;
        clock_gettime(CLOCK_MONOTONIC, &currentTime);
        const double timeSinceAlarmStarted = ElapsedTime(&_alarmActivationTime, &currentTime);
        // Check if the alert threshold time has bee exceeded.  If so trigger the alert
        if(timeSinceAlarmStarted > _alarmTimeThreshold)
        {
        	std::cout << "[Alarm::IsAlarmTimeThresholdReached] Alarm Time: " << timeSinceAlarmStarted << std::endl;
        	bRetValue = true;
        }
    }

    return bRetValue;
}



/*
    Used as a flag to known when a time based event has started
*/
bool    Garfunkel::Alarm::IsAlertStarted()
{
    return _alertEventStarted;
}

/*
    Used as a flag to known when a time based event has started
*/
bool    Garfunkel::Alarm::IsAlarmStarted()
{
    return _alarmEventStarted;
}





Garfunkel::IOSimonCommunicationAlarm::IOSimonCommunicationAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
: GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)
{
}

Garfunkel::IOSimonCommunicationAlarm::~IOSimonCommunicationAlarm()
{
}

bool Garfunkel::IOSimonCommunicationAlarm::CheckAlarmConditions()
{
	AlarmStatus before(GetStatus());
    GarfunkelData& AqData = GarfunkelData::Instance();
    Garfunkel::AlarmSettings& AlarmData = Garfunkel::AlarmSettings::Instance();
    timespec lastComm(AqData._timeOfLastSimonIOBCommunication);
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    const double timeSinceLastComm = ElapsedTime(&lastComm, &now);

    AlarmStatus after;
    if(timeSinceLastComm > IOBOARD_MESSAGE_TIMEOUT)
    {
        after = ALARM_STATUS_ACTIVE;
        AlarmData.SimonIOBoardCommunicationAlarm.Set(True);
/*
        if(false == SetAlarmStartTime())
        {
            std::cout << "IO Communication, could not get alarm start time_t" << std::endl;
        }
*/
    }
    else
    {
        after = ALARM_STATUS_NONE;
        AlarmData.SimonIOBoardCommunicationAlarm.Set(False);
		//SysData.SetSystemState(eIdle);

        //ClearAlarmStartTime();
    }

    SetStatus(after);
    return (before != after);

}

/*!
    Method to handle any changes to the MCA that maybe required due to a true alarm state

    \param[in]  None

    \param[out] None

    \return     True if the alarm action was successfully handled
*/
bool Garfunkel::IOSimonCommunicationAlarm::HandleAlarmAction()
{
    bool        retValue = false;

    AlarmStatus  alarmStatus = GetStatus();

    if(ALARM_STATUS_NONE != alarmStatus &&
       ALARM_STATUS_LOW_ALERT != alarmStatus &&
       ALARM_STATUS_HIGH_ALERT != alarmStatus)
    {
        std::string     emailMessage = "Simon IOCommunication Error has occurred";
        std::string     errorCode = "61";
        retValue = SendEmail("IOCommunicationAlarm", emailMessage, errorCode);

        //_alarmSent = errorCode;
        SetAlertAlarmStatus(alarmStatus);
    }

    return retValue;
}


bool Garfunkel::IOSimonCommunicationAlarm::CancelAlarmAction()
{
    bool bRetValue = false;

    {
        std::string     emailMessage = "IOCommunication Error is cancelled";
        std::string     errorCode = "61";

        SendEmail("IOCommunicationAlarm", emailMessage, errorCode);
        bRetValue = true; //Alarm::CancelAlarmAction();
    }

    return bRetValue;
}







Garfunkel::IOGarfunkelCommunicationAlarm::IOGarfunkelCommunicationAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		: GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)
{
}

Garfunkel::IOGarfunkelCommunicationAlarm::~IOGarfunkelCommunicationAlarm()
{
}

bool Garfunkel::IOGarfunkelCommunicationAlarm::CheckAlarmConditions()
{
	AlarmStatus before(GetStatus());
    GarfunkelData& AqData = GarfunkelData::Instance();
    Garfunkel::AlarmSettings& AlarmData = Garfunkel::AlarmSettings::Instance();
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    const double timeSinceLastComm = ElapsedTime(&AqData._timeOfLastGarIOBCommunication, &now);

    AlarmStatus after;
    if(timeSinceLastComm > IOBOARD_MESSAGE_TIMEOUT)
    {
        after = ALARM_STATUS_ACTIVE;
        AlarmData.GarIOBoardCommunicationAlarm.Set(True);
    }
    else
    {
        after = ALARM_STATUS_NONE;
        AlarmData.GarIOBoardCommunicationAlarm.Set(False);
        //ClearAlarmStartTime();
    }

    SetStatus(after);
    return (before != after);

}

/*!
    Method to handle any changes to the MCA that maybe required due to a true alarm state

    \param[in]  None

    \param[out] None

    \return     True if the alarm action was successfully handled
*/
bool Garfunkel::IOGarfunkelCommunicationAlarm::HandleAlarmAction()
{
    bool        retValue = false;

    AlarmStatus  alarmStatus = GetStatus();

    if(ALARM_STATUS_NONE != alarmStatus &&
       ALARM_STATUS_LOW_ALERT != alarmStatus &&
       ALARM_STATUS_HIGH_ALERT != alarmStatus)
    {
        std::string     emailMessage = "Garfunkel IOCommunication Error has occurred";
        std::string     errorCode = "61";
        retValue = SendEmail("IOCommunicationAlarm", emailMessage, errorCode);

        //_alarmSent = errorCode;
        SetAlertAlarmStatus(alarmStatus);
    }

    return retValue;
}


bool Garfunkel::IOGarfunkelCommunicationAlarm::CancelAlarmAction()
{
    bool bRetValue = false;

    {
        std::string     emailMessage = "IOCommunication Error is cancelled";
        std::string     errorCode = "61";

        SendEmail("IOCommunicationAlarm", emailMessage, errorCode);
        bRetValue = true; //Alarm::CancelAlarmAction();
    }

    return bRetValue;
}


Garfunkel::OverHighTempAlarm::OverHighTempAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}

Garfunkel::OverHighTempAlarm::~OverHighTempAlarm()
{
}

bool Garfunkel::OverHighTempAlarm::CheckAlarmConditions()
{
	SystemData& SysData = SystemData::Instance();
    return CheckGarfunkelAlarmConditions(SysData.TempInDegreeF.Get());

}

Garfunkel::SumpOverFlowAlarm::SumpOverFlowAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}

Garfunkel::SumpOverFlowAlarm::~SumpOverFlowAlarm()
{
}

bool Garfunkel::SumpOverFlowAlarm::CheckAlarmConditions()
{
	SystemData& SysData = SystemData::Instance();

    return CheckGarfunkelAlarmConditions((double) SysData.GetSumpLevelSwitchState());

}

Garfunkel::NoORemainsInBothCapsuleAlarm::NoORemainsInBothCapsuleAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}

Garfunkel::NoORemainsInBothCapsuleAlarm::~NoORemainsInBothCapsuleAlarm()
{
}

bool Garfunkel::NoORemainsInBothCapsuleAlarm::CheckAlarmConditions()
{

	//TODO : Implement this
	//SystemData& SysData = SystemData::Instance();
    //return CheckGarfunkelAlarmConditions((double) SysData.GetSumpLevelSwitchState());
	return false;
}


Garfunkel::EmptySumpAlarm::EmptySumpAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}

Garfunkel::EmptySumpAlarm::~EmptySumpAlarm()
{
}

bool Garfunkel::EmptySumpAlarm::CheckAlarmConditions()
{

	//TODO : Implement this : the sump level switch reaches virtual counter limit AND system is unable to initiate a sump water make down process
	SystemData& SysData = SystemData::Instance();
    return CheckGarfunkelAlarmConditions((double) SysData.GetSumpLevelSwitchState());
	return false;
}

Garfunkel::LowMakeupPressureAlarm::LowMakeupPressureAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}

Garfunkel::LowMakeupPressureAlarm::~LowMakeupPressureAlarm()
{
}

bool Garfunkel::LowMakeupPressureAlarm::CheckAlarmConditions()
{

	//TODO : o	Alarm will activate when makeup pressure indicates low  while attempting to start sump water make down process
	SystemData& SysData = SystemData::Instance();
    return CheckGarfunkelAlarmConditions((double) SysData.GetPressureSwitchState());
	return false;
}



Garfunkel::HighTempAlarm::HighTempAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}



Garfunkel::HighTempAlarm::~HighTempAlarm()
{
}

bool Garfunkel::HighTempAlarm::CheckAlarmConditions()
{
	SystemData& SysData = SystemData::Instance();
    return CheckGarfunkelAlarmConditions(SysData.TempInDegreeF.Get());

}

Garfunkel::LowTempAlarm::LowTempAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}



Garfunkel::LowTempAlarm::~LowTempAlarm()
{
}

bool Garfunkel::LowTempAlarm::CheckAlarmConditions()
{
	SystemData& SysData = SystemData::Instance();
    return CheckGarfunkelAlarmConditions(SysData.TempInDegreeF.Get());

}


Garfunkel::O1CapsuleLidOpenAlarm::O1CapsuleLidOpenAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}



Garfunkel::O1CapsuleLidOpenAlarm::~O1CapsuleLidOpenAlarm()
{
}

bool Garfunkel::O1CapsuleLidOpenAlarm::CheckAlarmConditions()
{
	SystemData& SysData = SystemData::Instance();
    return CheckGarfunkelAlarmConditions((double)SysData.GetOCapsuleLidState(0));

}


Garfunkel::O2CapsuleLidOpenAlarm::O2CapsuleLidOpenAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}



Garfunkel::O2CapsuleLidOpenAlarm::~O2CapsuleLidOpenAlarm()
{
}

bool Garfunkel::O2CapsuleLidOpenAlarm::CheckAlarmConditions()
{
	SystemData& SysData = SystemData::Instance();
    return CheckGarfunkelAlarmConditions((double)SysData.GetOCapsuleLidState(1));

}


Garfunkel::SBlockLidOpenAlarm::SBlockLidOpenAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}



Garfunkel::SBlockLidOpenAlarm::~SBlockLidOpenAlarm()
{
}

bool Garfunkel::SBlockLidOpenAlarm::CheckAlarmConditions()
{
	SystemData& SysData = SystemData::Instance();
    return CheckGarfunkelAlarmConditions((double)SysData.GetSLidSwitchState());

}


Garfunkel::PBlockLidOpenAlarm::PBlockLidOpenAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}



Garfunkel::PBlockLidOpenAlarm::~PBlockLidOpenAlarm()
{
}

bool Garfunkel::PBlockLidOpenAlarm::CheckAlarmConditions()
{
	SystemData& SysData = SystemData::Instance();
    return CheckGarfunkelAlarmConditions((double)SysData.GetHLidSwitchState());

}


Garfunkel::O1ProductEmptyAlarm::O1ProductEmptyAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}



Garfunkel::O1ProductEmptyAlarm::~O1ProductEmptyAlarm()
{
}

bool Garfunkel::O1ProductEmptyAlarm::CheckAlarmConditions()
{

	//TODO : Implement this : the sump level switch reaches virtual counter limit AND system is unable to initiate a sump water make down process
	//SystemData& SysData = SystemData::Instance();
	//return CheckGarfunkelAlarmConditions((double)SysData.Conductivity.Get());
	return false;

}


bool Garfunkel::O1ProductEmptyAlarm::HandleAlarmAction()
{
	boost::shared_ptr< ecolab::ISocketCommunication >                           pSocketRS485Socket;
	SystemData& SysData = SystemData::Instance();

	AlarmStatus  alarmStatus = _status.Get();

	if(alarmStatus==ALARM_STATUS_HIGH_ALERT) //alarm active
	{
		if(GetAlertActive()==true&&IsAlarmStarted()==false)//debounce satisfied
		{
			std::cout<<" Turning O1 OOP LED ON"<<std::endl;
		    ecolab::SocketFactory & FactoryInstance = ecolab::SocketFactory::Instance();
		    pSocketRS485Socket.reset(FactoryInstance.CreateSocket(ecolab::eCondor, ecolab::eRS485WithReadTimeout));
		    pSocketRS485Socket->SetRS485ReadTimeout(2000); //set timeout at 2 secs
		    pSocketRS485Socket->Connect();
		    SysData.SetOCapsuleLEDState(pSocketRS485Socket, 0, eOn); //TODO, test this

    	}
	}

	return GarfunkelAlarm::HandleAlarmAction(); //call base class actions now

}

bool Garfunkel::O1ProductEmptyAlarm::CancelAlarmAction()
{
	boost::shared_ptr< ecolab::ISocketCommunication >                           pSocketRS485Socket;
	SystemData& SysData = SystemData::Instance();

    AlarmStatus  alarmStatus = _status.Get();

	if(alarmStatus==ALARM_STATUS_NONE) //alarm clear
	{
    	if(GetAlertActive()==false&&IsAlarmDeactivationStarted()==false)
    	{
    		std::cout<<" Turning O1 OOP LED OFF"<<std::endl;
		    ecolab::SocketFactory & FactoryInstance = ecolab::SocketFactory::Instance();
		    pSocketRS485Socket.reset(FactoryInstance.CreateSocket(ecolab::eCondor, ecolab::eRS485WithReadTimeout));
		    pSocketRS485Socket->SetRS485ReadTimeout(2000); //set timeout at 2 secs
		    pSocketRS485Socket->Connect();
		    SysData.SetOCapsuleLEDState(pSocketRS485Socket, 1, eOff); //TODO, test this

    	}
    }

	return GarfunkelAlarm::CancelAlarmAction(); //call base class actions now
}



Garfunkel::O2ProductEmptyAlarm::O2ProductEmptyAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}



Garfunkel::O2ProductEmptyAlarm::~O2ProductEmptyAlarm()
{
}

bool Garfunkel::O2ProductEmptyAlarm::CheckAlarmConditions()
{

	//TODO : Implement this : the sump level switch reaches virtual counter limit AND system is unable to initiate a sump water make down process
	//SystemData& SysData = SystemData::Instance();
	//return CheckGarfunkelAlarmConditions((double)SysData.Conductivity.Get());
	return false;

}

Garfunkel::SProductEmptyAlarm::SProductEmptyAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}



Garfunkel::SProductEmptyAlarm::~SProductEmptyAlarm()
{
}

bool Garfunkel::SProductEmptyAlarm::CheckAlarmConditions()
{

	SystemData& SysData = SystemData::Instance();
	//return CheckGarfunkelAlarmConditions((double)SysData.GetS);
	//TODO : Implement this
	return false;

}

Garfunkel::PProductEmptyAlarm::PProductEmptyAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}



Garfunkel::PProductEmptyAlarm::~PProductEmptyAlarm()
{
}

bool Garfunkel::PProductEmptyAlarm::CheckAlarmConditions()
{

	SystemData& SysData = SystemData::Instance();
	//return CheckGarfunkelAlarmConditions((double)SysData.GetS);
	//TODO : Implement this
	return false;

}

Garfunkel::SLowPProductAlarm::SLowPProductAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}



Garfunkel::SLowPProductAlarm::~SLowPProductAlarm()
{
}

bool Garfunkel::SLowPProductAlarm::CheckAlarmConditions()
{

	SystemData& SysData = SystemData::Instance();
	return CheckGarfunkelAlarmConditions((double)SysData._SLowProductState.Get());

}

bool Garfunkel::SLowPProductAlarm::HandleAlarmAction()
{
	boost::shared_ptr< ecolab::ISocketCommunication >                           pSocketRS485Socket;
	SystemData& SysData = SystemData::Instance();

	AlarmStatus  alarmStatus = _status.Get();

	if(alarmStatus==ALARM_STATUS_HIGH_ALERT) //alarm active
	{
		if(GetAlertActive()==true&&IsAlarmStarted()==false)//debounce satisfied
		{
			std::cout<<" Turning S OOP LED ON"<<std::endl;
		    ecolab::SocketFactory & FactoryInstance = ecolab::SocketFactory::Instance();
		    pSocketRS485Socket.reset(FactoryInstance.CreateSocket(ecolab::eCondor, ecolab::eRS485WithReadTimeout));
		    pSocketRS485Socket->SetRS485ReadTimeout(2000); //set timeout at 2 secs
		    pSocketRS485Socket->Connect();
		    SysData.SetSEmptyLEDState(pSocketRS485Socket, eOn);

    	}
	}

	return GarfunkelAlarm::HandleAlarmAction(); //call base class actions now

}

bool Garfunkel::SLowPProductAlarm::CancelAlarmAction()
{
	boost::shared_ptr< ecolab::ISocketCommunication >                           pSocketRS485Socket;
	SystemData& SysData = SystemData::Instance();

    AlarmStatus  alarmStatus = _status.Get();

	if(alarmStatus==ALARM_STATUS_NONE) //alarm clear
	{
    	if(GetAlertActive()==false&&IsAlarmDeactivationStarted()==false)
    	{
    		std::cout<<" Turning S OOP LED OFF"<<std::endl;
		    ecolab::SocketFactory & FactoryInstance = ecolab::SocketFactory::Instance();
		    pSocketRS485Socket.reset(FactoryInstance.CreateSocket(ecolab::eCondor, ecolab::eRS485WithReadTimeout));
		    pSocketRS485Socket->SetRS485ReadTimeout(2000); //set timeout at 2 secs
		    pSocketRS485Socket->Connect();
		    SysData.SetSEmptyLEDState(pSocketRS485Socket, eOff);

    	}
    }

	return GarfunkelAlarm::CancelAlarmAction(); //call base class actions now
}


Garfunkel::PLowPProductAlarm::PLowPProductAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}



Garfunkel::PLowPProductAlarm::~PLowPProductAlarm()
{
}

bool Garfunkel::PLowPProductAlarm::CheckAlarmConditions()
{

	SystemData& SysData = SystemData::Instance();
	return CheckGarfunkelAlarmConditions((double)SysData._HLowProductState.Get());

}

bool Garfunkel::PLowPProductAlarm::HandleAlarmAction()
{
	boost::shared_ptr< ecolab::ISocketCommunication >                           pSocketRS485Socket;
	SystemData& SysData = SystemData::Instance();
	AlarmStatus  alarmStatus = _status.Get();

	if(alarmStatus==ALARM_STATUS_HIGH_ALERT) //alarm active
	{
		if(GetAlertActive()==true&&IsAlarmStarted()==false)//debounce satisfied
		{
			std::cout<<" Turning P OOP LED ON"<<std::endl;
		    ecolab::SocketFactory & FactoryInstance = ecolab::SocketFactory::Instance();
		    pSocketRS485Socket.reset(FactoryInstance.CreateSocket(ecolab::eCondor, ecolab::eRS485WithReadTimeout));
		    pSocketRS485Socket->SetRS485ReadTimeout(2000); //set timeout at 2 secs
		    pSocketRS485Socket->Connect();
		    SysData.SetHEmptyLEDState(pSocketRS485Socket, eOn);

    	}
	}

	return GarfunkelAlarm::HandleAlarmAction(); //call base class actions now

}

bool Garfunkel::PLowPProductAlarm::CancelAlarmAction()
{
	boost::shared_ptr< ecolab::ISocketCommunication >                           pSocketRS485Socket;
	SystemData& SysData = SystemData::Instance();

    AlarmStatus  alarmStatus = _status.Get();

	if(alarmStatus==ALARM_STATUS_NONE) //alarm clear
	{
    	if(GetAlertActive()==false&&IsAlarmDeactivationStarted()==false)
    	{
    		std::cout<<" Turning P OOP LED OFF"<<std::endl;
		    ecolab::SocketFactory & FactoryInstance = ecolab::SocketFactory::Instance();
		    pSocketRS485Socket.reset(FactoryInstance.CreateSocket(ecolab::eCondor, ecolab::eRS485WithReadTimeout));
		    pSocketRS485Socket->SetRS485ReadTimeout(2000); //set timeout at 2 secs
		    pSocketRS485Socket->Connect();
		    SysData.SetHEmptyLEDState(pSocketRS485Socket, eOff);

    	}
    }

	return GarfunkelAlarm::CancelAlarmAction(); //call base class actions now
}




Garfunkel::ExcessiveTimeSinceSumpFillAlarm::ExcessiveTimeSinceSumpFillAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}



Garfunkel::ExcessiveTimeSinceSumpFillAlarm::~ExcessiveTimeSinceSumpFillAlarm()
{
}

bool Garfunkel::ExcessiveTimeSinceSumpFillAlarm::CheckAlarmConditions()
{

	SystemData& SysData = SystemData::Instance();
	//return CheckGarfunkelAlarmConditions((double)SysData._HLowProductState.Get());
	return false;

}

bool Garfunkel::ExcessiveTimeSinceSumpFillAlarm::HandleAlarmAction()
{

	//TODO Update this

	return GarfunkelAlarm::HandleAlarmAction(); //call base class actions now

}

bool Garfunkel::ExcessiveTimeSinceSumpFillAlarm::CancelAlarmAction()
{
	//TODO Update this

	return GarfunkelAlarm::CancelAlarmAction(); //call base class actions now
}




Garfunkel::ExceedMaxTimeBetweenBFWPCallAlarm::ExceedMaxTimeBetweenBFWPCallAlarm(unsigned int alertTimeThreshold, unsigned int alarmTimeThreshold, unsigned int alarmEnvisionTimeThreshold,
		   unsigned int alertDeactivationTimeThreshold, unsigned int alarmDeactivationTimeThreshold,  unsigned int alarmEnvisionDeactivationTimeThreshold)
		   : GarfunkelAlarm(alertTimeThreshold,alarmTimeThreshold,alarmEnvisionTimeThreshold, alertDeactivationTimeThreshold, alarmDeactivationTimeThreshold,alarmEnvisionDeactivationTimeThreshold)

{

}



Garfunkel::ExceedMaxTimeBetweenBFWPCallAlarm::~ExceedMaxTimeBetweenBFWPCallAlarm()
{
}

bool Garfunkel::ExceedMaxTimeBetweenBFWPCallAlarm::CheckAlarmConditions()
{

	SystemData& SysData = SystemData::Instance();
	//return CheckGarfunkelAlarmConditions((double)SysData._HLowProductState.Get());
	return false;

}

bool Garfunkel::ExceedMaxTimeBetweenBFWPCallAlarm::HandleAlarmAction()
{

	//TODO Update this

	return GarfunkelAlarm::HandleAlarmAction(); //call base class actions now

}

bool Garfunkel::ExceedMaxTimeBetweenBFWPCallAlarm::CancelAlarmAction()
{
	//TODO Update this

	return GarfunkelAlarm::CancelAlarmAction(); //call base class actions now
}


