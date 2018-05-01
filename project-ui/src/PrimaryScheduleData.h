/*
*   PrimarySchedule Data
*   Holds Typical Data of a Primary Schedule
*   Recall: There are 4*24*7 primary Schedules are possible
*   if all are filled at once else Gaps are Secondary Schedules
*   
*   Author: TEN@ECOLAB; May 18th 2016
*/
#ifndef PRIMARY_SCHEDULE_DATA_H
#define PRIMARY_SCHEDULE_DATA_H

#include <QObject>
#include <QStringList>
#include <QDeclarativeContext>
#include <QAbstractListModel>
#include <QDebug>


class PrimaryScheduleData
{

// Public Stuff!!
public:

    PrimaryScheduleData(); // naked instance!! ( PrimaryScheduleData * FirstPrimaryScheduleData;) 

    //Custom roles enum
    enum Roles {
    	PrimaryScheduleIdRole = Qt::UserRole + 1,
    	DayIdPrimaryScheduleRole,
    	DayNamePrimaryScheduleRole,
    	StartHourPrimarySCheduleRole,
    	StartMinutePrimarySCheduleRole,
    	EndHourPrimaryScheduleRole,
    	EndMinutePrimaryScheduleRole,
    	IsValidPrimaryScheduleRole,
    	NewTreatmentPumpDutyCycleRole,
    	MaxTimeForFillEventsBeforeAlarmRole,
    	TMEnteredPercentageTimeBFWPIsOnRole,
    	ProductConcentrationForSprayRole
    };
  
    //Map Your Role to Names
    static QHash<int, QByteArray> roleNames() // or const
    {
    	QHash<int, QByteArray> roles;

    	roles[PrimaryScheduleIdRole]     = "primaryScheduleID";
    	roles[DayIdPrimaryScheduleRole]     = "dayIDprimarySchedule";
    	roles[DayNamePrimaryScheduleRole]     = "dayNameprimarySchedule";
    	roles[StartHourPrimarySCheduleRole]     = "startHourprimarySchedule";
    	roles[StartMinutePrimarySCheduleRole]     = "startMinuteprimarySchedule";
    	roles[EndHourPrimaryScheduleRole]     = "endHourprimarySchedule";
    	roles[EndMinutePrimaryScheduleRole]     = "endMinuteprimarySchedule";
    	roles[IsValidPrimaryScheduleRole]     = "isValidprimarySchedule";
    	roles[NewTreatmentPumpDutyCycleRole]     = "NewTreatmentPumpDutyCycle";
    	roles[MaxTimeForFillEventsBeforeAlarmRole]     = "MaxTimeForFillEventsBeforeAlarm";
    	roles[TMEnteredPercentageTimeBFWPIsOnRole]     = "TMEnteredPercentageTimeBFWPIsOn";
    	roles[ProductConcentrationForSprayRole]     = "ProductConcentrationForSpray";

    	return roles;
    }

    //Now What does the Data really returns?
    QVariant data ( int role = Qt::DisplayRole)
    {
    	QVariant  returnValue = 0; //always initialized stuff!!

    	if (role == PrimaryScheduleIdRole)
    	{
            #ifdef DEBUG
                qDebug() << "Role = PrimarySceduleIDRole";
            #endif
                returnValue = getPrimaryScheduleId();          		
    	}
    	else if (role == DayIdPrimaryScheduleRole )
        {
        	#ifdef DEBUG
        	    qDebug() << "Role = DayIdPrimaryScheduleRole";
        	#endif
        	    returnValue = getDayIdPrimarySchedule();    
        }
        else if (role == DayNamePrimaryScheduleRole)
        {
        	  returnValue = getDayNamePrimarySchedule();
        }
        else if (role == StartHourPrimarySCheduleRole)
        {
        	  returnValue = getStartHourPrimarySChedule();
        }
        else if (role == StartMinutePrimarySCheduleRole)
        {
        	  returnValue = getStartMinutePrimarySChedule();
        }
        else if (role == EndHourPrimaryScheduleRole)
        {
        	  returnValue = getEndHourPrimarySchedule();
        }	
        else if (role == EndMinutePrimaryScheduleRole )
        {
        	  returnValue = getEndMinutePrimarySchedule();
        }
        else if (role == IsValidPrimaryScheduleRole )
        {
        	#ifndef DEBUG
        	  qDebug() << "Role = IsValidPrimaryScheduleRole";
        	#endif
        	   returnValue = getIsValidPrimarySchedule();  
        }
        else if (role == NewTreatmentPumpDutyCycleRole )
        {
        	  returnValue = getNewTreatmentPumpDutyCycle();
        }
        else if (role == MaxTimeForFillEventsBeforeAlarmRole )
        {
        	  returnValue = getMaxTimeForFillEventsBeforeAlarm();
        }
        else if (role == TMEnteredPercentageTimeBFWPIsOnRole )
        {
        	  returnValue = getTMEnteredPercentageTimeBFWPIsOn();
        }
        else if (role == ProductConcentrationForSprayRole )
        {
        	  returnValue = getProductConcentrationForSpray();
        }		

         return returnValue;

    }

   /*So What are these getting functions? */
   //
   //  GETTERS!
   //

   int getRegionId () const          { return  _regionId;   }
   int getSystemId () const          { return  _systemId;     }
   int getOperatingRefId () const    { retunr  _operatingRefID;  }

   //% Unique ID for each Primary Schedule Enetered!!
   int getPrimaryScheduleId() const   { return    _primaryscheduleId;  }
   //% Day ID from 0-6(Sun - Mon)
   int getDayIdPrimarySchedule()  const { return   _dayIdprimaryschedule; }
   //% Name of thd Day (e.g Sunday)
   QString getDayNamePrimarySchedule()    { return  _dayNameprimaryschedule; }
   //% Start Hour 00-23
   int getStartHourPrimarySChedule()    { return   _startHourprimaryschedule;  }
   //% Start Minute 00-59
   int getStartMinutePrimarySChedule()    { return   _startMinuteprimaryschedule;  }
   //% End Hour 00-23
   int getEndHourPrimarySChedule()    { return   _endHourprimaryschedule;  }
   //% End Minute 00-59
   int getEndMinutePrimarySChedule()    { return   _endMinuteprimaryschedule;  }
   //% Is ScheduleValid?
   bool getIsValidPrimarySchedule()     { return   _isValidprimaryschedule;    }
   //% NewTreatmentPumpDutyCycle
   double getNewTreatmentPumpDutyCycle()    { return   _newTreatmentPumpDutyCycle;  }
   //% MaxTimeForFillEventsBeforeAlarm
   int getMaxTimeForFillEventsBeforeAlarm()    { return    _maxTimeForFillEventsBeforeAlarm;  }
   //%  TMEnteredPercentageTimeBFWPIsOn
   double getTMEnteredPercentageTimeBFWPIsOn()    { return     _tMEnteredPercentageTimeBFWPIsOn;  }
   //%  ProductConcentrationForSpray or ProdConc as in DB 
   double getProductConcentrationForSpray()   {  return   _productConcentrationForSpray; }



   /*So How do we Update Stuff? */   
   //
   //  SETTERS!
   //
   void setRegionId ( int &rId );
   void setSystemId ( int &sId );
   void setOperatingRefId ( int & opRefId );

   void setPrimaryScheduleId ( int &psId );
   void setDayIdPrimarySchedule ( int &psDayId );
   void setDayNamePrimarySchedule ( QString &psDay );
   void setStartHourPrimarySChedule ( int &psSHour );
   void setStartMinutePrimarySChedule ( int &psSMinute );
   void setEndHourPrimarySChedule ( int &psEHour );
   void setEndMinutePrimarySChedule ( int &psEMinute );
   void setIsValidPrimarySchedule ( bool &psIsValid);

   void setNewTreatmentPumpDutyCycle ( double &nTreatmentPumpDutyCycle ); 
   void setMaxTimeForFillEventsBeforeAlarm ( int &maxTimeForFillEventsBeforeAlarm );
   void setTMEnteredPercentageTimeBFWPIsOn ( double &tmEnteredPerCentTimeBFWPIsOn );
   void setProductConcentrationForSpray ( double &procConcSpray ); 



// Personal Stuff!!
private: 

    int _regionId;        // Schedules might differ region
    int _systemId;        // SystemData ID
    int _operatingRefID;  // FK NOT NULL in PrimarySchedule(OperatingSchedule Table in DB)

	int _primaryscheduleId; 
	int _dayIdprimaryschedule; 
	QString _dayNameprimaryschedule; 
	int _startHourprimaryschedule;
	int _startMinuteprimaryschedule;
	int _endHourprimaryschedule;
	int _endMinuteprimaryschedule;
	bool _isValidprimaryschedule;

	double _newTreatmentPumpDutyCycle;
	int  _maxTimeForFillEventsBeforeAlarm;
	double _tMEnteredPercentageTimeBFWPIsOn;
	double _productConcentrationForSpray; 

};    

#endif //PRIMARY_SCHEDULE_DATA_H
