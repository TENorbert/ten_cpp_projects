/*
  Decided to Only Define Class Initialization & Setting fxns Here!! 
*/
#include <QDebug>
#include "PrimaryScheduleData.h"

PrimaryScheduleData::PrimaryScheduleData() 
{
	 _regionId                           = 0;        // Schedules might differ region
    _systemId                            = 0;        // SystemData ID
    _operatingRefID                      = 0;  // FK NOT NULL in PrimarySchedule(OperatingSchedule Table in DB)

	_primaryscheduleId                   = 0; 
	_dayIdprimaryschedule                = 0; 
	_dayNameprimaryschedule              = ""; 
    _startHourprimaryschedule            = 00;
	_startMinuteprimaryschedule          = 00;
	_endHourprimaryschedule              = 00;
	_endMinuteprimaryschedule            = 00;
	_isValidprimaryschedule              = false;
	_newTreatmentPumpDutyCycle           = 0.5; //Default
	_maxTimeForFillEventsBeforeAlarm     = 48; //Default = 48 Hours
	_tMEnteredPercentageTimeBFWPIsOn     = 0;
	_productConcentrationForSpray        = 1; //Default = 1 

	
}


/* Setters Defination */

void PrimaryScheduleData::setRegionId ( int &rId ) 
{
    _regionId = rId;
}

void PrimaryScheduleData::setSystemId ( int &sId ) 
{
    _systemId = sId;
}

void PrimaryScheduleData::setOperatingRefId ( int &opRefId )
{
	_operatingRefID = opRefId;
}

// Primary Schedule Stuff!!
void PrimaryScheduleData::setPrimaryScheduleId ( int &psId )
{
	_primaryscheduleId = psId;
}

void PrimaryScheduleData::setDayIdPrimarySchedule ( int &psDayId )
{
	_dayIdprimaryschedule = psDayId;
}

void PrimaryScheduleData::setDayNamePrimarySchedule ( QString &psDay )
{
	_dayNameprimaryschedule = psDay.toAscii();
} 

void PrimaryScheduleData::setStartHourPrimarySChedule ( int &psSHour )
{
	_startHourprimaryschedule = psSHour;
}

void PrimaryScheduleData::setStartMinutePrimarySChedule ( int &psSMinute )
{
	_startMinuteprimaryschedule = psSMinute;
}

void PrimaryScheduleData::setEndHourPrimarySChedule ( int &psEHour )
{
	_endHourprimaryschedule = psEHour;
}

void PrimaryScheduleData::setEndMinutePrimarySChedule ( int &psEMinute )
{
	_endMinuteprimaryschedule = psEMinute;
}

void PrimaryScheduleData::setIsValidPrimarySchedule ( bool &psIsValid)
{
	_isValidprimaryschedule = psIsValid;
}

void PrimaryScheduleData::setNewTreatmentPumpDutyCycle ( double &nTreatmentPumpDutyCycle )
{
	_newTreatmentPumpDutyCycle = nTreatmentPumpDutyCycle;
}

void PrimaryScheduleData::setMaxTimeForFillEventsBeforeAlarm ( int &maxTimeForFillEventsBeforeAlarm )
{
	_maxTimeForFillEventsBeforeAlarm = maxTimeForFillEventsBeforeAlarm;
}

void PrimaryScheduleData::setTMEnteredPercentageTimeBFWPIsOn ( double &tmEnteredPerCentTimeBFWPIsOn )
{
	_tMEnteredPercentageTimeBFWPIsOn = tmEnteredPerCentTimeBFWPIsOn;
}

void PrimaryScheduleData::setProductConcentrationForSpray ( double &procConcSpray )
{
	_productConcentrationForSpray = procConcSpray;
}