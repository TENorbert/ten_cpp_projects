#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QString>
//% Boost Libraries
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
//Private classes!!
#include "DBAccess.h"
#include "ecolab.h"
#include "GarfunkelSystemContext.h"


//%
//%  Beloved Constructor
//%  Connects to the Database & Grab database Information once Instance is created
//%
//% Constructor
//%Leave Context Stuff For now!!
GarfunkelSystemContext::GarfunkelSystemContext(GarfunkelDB *gdb, QDeclarativeContext *context,  QObject *parent) :
    QObject(parent),
    _gDB(gdb),
    _Context(context)
{

    connect(_gDB, SIGNAL(systemDataUpdated()), this, SLOT( grabGarfunkelSystemContext() ));

    connect(_gDB, SIGNAL(dbSyncEvent()), this, SLOT(dbSyncEvent()),Qt::UniqueConnection );

    // in case I need infor from systemData
    //GarfunkelSystemData* sdo = GarfunkelSystemData::getInstancePtr();
    //%
    //% Grab Garfunkel System  Data for  the first time
    //%
    grabGarfunkelSystemContext ();
    grabLocalLanguageNames ();

    //%
    //%  Initialized Default Parameters
    //%
    _initDefaultVariables ();

}

//%
//%   destructor
//%
GarfunkelSystemContext::~GarfunkelSystemContext ()
{
	//% delete unused stuff
}

//%
//%  _initDefaultVariables() 
//%  Is called once  GarfunkelSystemContext class
//%  Instance is created and it
//%  Initialises ALL default Variables
//%
void GarfunkelSystemContext::_initDefaultVariables ()
{
    qDebug() << "GarfunkelSystemData Default Values initialised";
    _systemDataID  	        = -1;
    //% SystemRegion ref Stuff
    _regionID  		        = -1;
    _regionName             = -1;
    _statusCode		        = "A";
    //% SystemOpMode ref stuff
    _systemOpModeID         = -1;
    _systemOpModeName       = -1;
    //% DateFormat ref stuff
    _dateFormatID           = -1;
    _unitOfMeasure          = 0;
    _decimalOrComma         = true; //True = decimal, False = comma
    _iSTwelveHourTimeFormat =  true;
    _operatingModeID       = -1;
    _dualOperatingSchedule  = true;
    _boilerPressure         = -1;  
    _iSDeaeratorPresent     = true;
    _fWTemperature          = -1;
    _dAOperatingPressure    = -1;
    _cyclesOfConcentrationTarget = 30;
    _nominalSteamFlow       = -1;
    _totalCondensateReturn  = -1;
    _iSBFWPIntermittent     = true;
    _operatingHoursPerDay   = 24;
    _referenceIntervalForTreatmentPump  = 30;
    _treatmentPumpCalibrationValue      = 113.5624;
    _bFWPSignalFilterTime    = 4;
    _maxTimeBetweenBFWPCallsInHours  = 96;
    _maxTimeForFillEventToComplete   = -1;
    _virtualLevelCounterVolumeInGallon = 0.79; //% 0.79 gallons  (3000ml)
    _sumpLowToFullVolumeInGallon        = 1.056688; //% 4000ml
    _sumpFullToOverflowVolumeInGallon   = 1.849204; //% 7000ml
    _sumpOverflowToAboveVolumeInGallon  = 0.5283441; //% 2000ml

    _timeDateOfLastFillEvent     = "00:00:00"; //QDateTime::currentDateTime(); //% Default to Current time
    _timeDateOfLastBFWPSignalReceived   = "00:00:00"; //QDateTime::currentDateTime(); //% Default to Current time;
    _timeBetweenBFWPEvents              = -1;
    _timeDatePowerOn                    = "00:00:00"; //QDateTime::currentDateTime(); //% Default to Current time;
    _causticRinseStartTime              = "00:00:00"; //QTime::fromString("0.00", "m.s"); //% Default to 00:00:00.000;
    _causticRinseFinishTime             = "00:00:00"; //QTime::fromString("0.00", "m.s"); //% Default to 00:00:00.000;
    _iSSystemInitialized                = false;
    _baselineConductivity               = 1000;
    _layUpEnabled                       = true; 

    _primaryLanguage                    = -1;
    _tmLanguage                         = -1;
    //set to !!        
    _localeID                           = ""; // Default language in the database is = "en" for english!!
    _langID                             = -1;  // Language ID if needed!!
     // _dtmPassword                        = "";
   // _rTMPassword                        = "";
   // _custPassword                       = "";
    //%    _alarmVolume;
}


//%    setSystemDateTime Method to set the system date and time.
//%    This method sets the system date and time to the arguments passed in and
//%    writes out the time to the real time clock. Passing in a -1 for any of the
//%    arguments will keep that value unchanged (by setting the new value to the
//%    current value.
//%    Inputs[month, day, hour, minute, year]  
//%          month:  setting the date to. -1 keeps the month unchanged.
//%          day:     setting the date to. -1 keeps the day unchanged.
//%          hour:    setting the time to. -1 keeps the hour unchanged.
//%          minute:  setting the time to. -1 keeps the minute unchanged.
//%          year:    seting the date to. -1 keeps the year unchanged.

void GarfunkelSystemContext::setSystemDateTime(int month, int day, int hours, int minutes, int year)
{

    qDebug() << "GarfunkelSystemContext::setSystemDateTime";

    QString app;
    QStringList arguments;
    QProcess process;
    int currentTime = 0, newTime = 0, oldTime = 0;


    //% Get the current date & time to fill in any arguments that are -1.

    QDateTime datetime = QDateTime::currentDateTime();
    currentTime = datetime.toTime_t();
    oldTime = QDateTime::currentDateTime().toTime_t();

    //% zero fill our numbers to two digits with a leading zero if necessary 
    //% if the passed in argument is -1, use the current value from datetime
    const QString sMonth = QString::number(month == -1 ? datetime.date().month() : month).rightJustified(2, '0');
    const QString sDay = QString::number(day== -1 ? datetime.date().day() : day).rightJustified(2, '0');
    const QString sHours = QString::number(hours == -1 ? datetime.time().hour() : hours).rightJustified(2, '0');
    const QString sMinutes = QString::number(minutes == -1 ? datetime.time().minute() : minutes).rightJustified(2, '0');
    const QString sYear = QString::number(year == -1 ? datetime.date().year() : year).rightJustified(2, '0');

    //%    Specify the date command to run and construct the date/time setting as
    //%    an argument. This *needs* to be in the format as defined by the date
    //%    command. This format is MMDDhhmmYYYY.
    //%
    app = "/bin/date";
    arguments << sMonth + sDay + sHours + sMinutes + sYear;

    
    //% Excute the process and wait for it to finish.
    process.start(app, arguments);
    qDebug() << "[GarfunkelSystemContext] Running" << app << arguments.at(0) << "waitForFinished =" << process.waitForFinished();


    //% Write the new date out to the real time clock.
    app = "/etc/init.d/save-rtc.sh";
    arguments = QStringList();

    //% Excute the process and wait for it to finish.
    process.start(app, arguments);
    qDebug() << "[GarfunkelSystemContext] Running" << app << "waitForFinished =" << process.waitForFinished();


    newTime = QDateTime::currentDateTime().toTime_t();

    const QString executeString = "AddEventToLog(7,2,"+QString::number(newTime)+","+QString::number(oldTime)+",-1,-1, -1, -1,'ui')";

    _gDB->executeStoredFunction(executeString);

}


//%
//%  
//%     SETTING FUNCTIONS DEFINITION
//%

//%*********************************************************
//%   SETTERS OF THIS CLASS
//%  (Automatically sets this Class!)
//%******************************************************** 

//% setSystemDataID
void GarfunkelSystemContext::setSystemDataID (int &sysDataId)
{
    if(sysDataId != _systemDataID)
    {
        _systemDataID = sysDataId;
        qDebug () << "emitting Signal systemDataIDChanged ()";
        emit ( systemDataIDChanged () );
    }
}

//% setRegionID
void GarfunkelSystemContext::setRegionID (int &regId)
{
    if(regId != _regionID)
    {
        _regionID = regId;
        qDebug () << "emitting Signal regionIDChanged ()";
        emit ( regionIDChanged () );
    }
}

//% setRegionName
void GarfunkelSystemContext::setRegionName (int &regName)
{
    if(regName != _regionName)
    {
        _regionName = regName;
        qDebug () << "emitting Signal regionNameChanged ()";
        emit ( regionNameChanged () );
    }
}


//% setStatusCode
void GarfunkelSystemContext::setStatusCode (QString &sCode)
{
    if(sCode != _statusCode) //% Apparently Qt claim this is possible, hmm!
    {
        _statusCode = sCode.toAscii();
        qDebug () << "emitting Signal statusCodeChanged ()";
        emit ( statusCodeChanged () );
    }

}

//% setSystemOpModeID
void GarfunkelSystemContext::setSystemOpModeID (int &sysOpModeId)
{
    if(sysOpModeId != _systemOpModeID)
    {
        _systemOpModeID = sysOpModeId;
        qDebug () << "emitting Signal systemOpModeIDChanged ()";
        emit ( systemOpModeIDChanged () );
    }
}



//% setSystemOpModeName
void GarfunkelSystemContext::setSystemOpModeName (int &sysOpModeName)
{
    if(sysOpModeName != _systemOpModeName)
    {
        _systemOpModeName = sysOpModeName;
        qDebug () << "emitting Signal systemOpModeNameChanged ()";
        emit ( systemOpModeNameChanged () );
    }
}


//% setDateFormatID
void GarfunkelSystemContext::setDateFormatID (int &dateformatId)
{
    if(dateformatId != _dateFormatID)
    {
        _dateFormatID = dateformatId;
        qDebug () << "emitting Signal DateFormatIDChanged ()";
        emit ( dateFormatIDChanged () );
    }
}

//% setUnitOfMeasure
void GarfunkelSystemContext::setUnitOfMeasure (int &uOfM)
{
    if(uOfM != _unitOfMeasure)
    {
        _unitOfMeasure = uOfM;
        qDebug () << "emitting Signal UnitOfMeasureChanged ()";
        emit ( unitOfMeasureChanged () );
    }
}



//% setDecimalOrComma
void GarfunkelSystemContext::setDecimalOrComma (bool &dOrcFlag)
{
    if(dOrcFlag != _decimalOrComma)
    {
        _decimalOrComma = dOrcFlag;
        qDebug () << "emitting Signal DecimalOrCommaChanged ()";
        emit ( decimalOrCommaChanged () );
    }
}

//% setIsTwelveHourTimeFormat
void GarfunkelSystemContext::setIsTwelveHourTimeFormat (bool &hFlag)
{
    if(hFlag != _iSTwelveHourTimeFormat)
    {
        _iSTwelveHourTimeFormat = hFlag;
        qDebug () << "emitting Signal IsTwelveHourTimeFormatChanged ()";
        emit ( iSTwelveHourTimeFormatChanged () );
    }
}

//% setOperatingModeID
void GarfunkelSystemContext::setOperatingModeID (int &opModeId)
{
    if(opModeId != _operatingModeID)
    {
        _operatingModeID = opModeId;
        qDebug () << "emitting Signal OperatingModeIDChanged ()";
        emit ( operatingModeIDChanged () );
    }
}

//% setDualOperatingSchedule
void GarfunkelSystemContext::setDualOperatingSchedule (bool &dOpSchFlag)
{
    if(dOpSchFlag != _dualOperatingSchedule)
    {
        _dualOperatingSchedule = dOpSchFlag;
        qDebug () << "emitting Signal DualOperatingScheduleChanged ()";
        emit ( dualOperatingScheduleChanged () );
    }
}


//% setBoilerPressure
void GarfunkelSystemContext::setBoilerPressure (float &bPressure)
{
    if(bPressure != _boilerPressure)
    {
        _boilerPressure = bPressure;
        qDebug () << "emitting Signal BoilerPressureChanged ()";
        emit ( boilerPressureChanged () );
    }
}


//% setIsDeaeratorPresent
void GarfunkelSystemContext::setIsDeaeratorPresent (bool &dFlag)
{
    if(dFlag != _iSDeaeratorPresent)
    {
        _iSDeaeratorPresent = dFlag;
        qDebug () << "emitting Signal IsDeaeratorPresentChanged ()";
        emit ( iSDeaeratorPresentChanged () );
    }
}


//% setFeedWaterTemperature
void GarfunkelSystemContext::setFeedWaterTemperature (float &fwTemp)
{
    if(fwTemp != _fWTemperature)
    {
        _fWTemperature = fwTemp;
        qDebug () << "emitting Signal FeedWaterTemperatureChanged ()";
        emit ( feedWaterTemperatureChanged () );
    }
}



//% setDAOperatingPressure
void GarfunkelSystemContext::setDAOperatingPressure (float &daOpPressure)
{
    if(daOpPressure != _dAOperatingPressure)
    {
        _dAOperatingPressure = daOpPressure;
        qDebug () << "emitting Signal DAOperatingPressureChanged ()";
        emit ( dAOperatingPressureChanged () );
    }
}


//% setCyclesOfConcentrationTarget
void GarfunkelSystemContext::setCyclesOfConcentrationTarget (float &concTarget)
{
    if(concTarget != _cyclesOfConcentrationTarget)
    {
        _cyclesOfConcentrationTarget = concTarget;
        qDebug () << "emitting Signal CyclesOfConcentrationTargetChanged ()";
        emit ( cyclesOfConcentrationTargetChanged () );
    }
}

//% setNominalSteamFlow
void GarfunkelSystemContext::setNominalSteamFlow (float &nsteamFlow)
{
    if(nsteamFlow != _nominalSteamFlow)
    {
        _nominalSteamFlow = nsteamFlow;
        qDebug () << "emitting Signal NominalSteamFlowChanged ()";
        emit ( nominalSteamFlowChanged () );
    }
}

//% setTotalCondensateReturn
void GarfunkelSystemContext::setTotalCondensateReturn (float &tCondRet)
{
    if(tCondRet != _totalCondensateReturn)
    {
        _totalCondensateReturn = tCondRet;
        qDebug () << "emitting Signal TotalCondensateReturnChanged ()";
        emit ( totalCondensateReturnChanged () );
    }
}


//% setIsBFWPIntermittent
void GarfunkelSystemContext::setIsBFWPIntermittent (bool &bwiFlage)
{
    if(bwiFlage != _iSBFWPIntermittent)
    {
        _iSBFWPIntermittent = bwiFlage;
        qDebug () << "emitting Signal IsBFWPIntermittentChanged ()";
        emit ( iSBFWPIntermittentChanged () );
    }
}

//% setOperatingHoursPerDay
void GarfunkelSystemContext::setOperatingHoursPerDay (int &opHpD)
{
    if(opHpD != _operatingHoursPerDay)
    {
        _operatingHoursPerDay = opHpD;
        qDebug () << "emitting Signal OperatingHoursPerDayChanged ()";
        emit ( operatingHoursPerDayChanged () );
    }
}

//% setReferenceIntervalForTreatmentPump
void GarfunkelSystemContext::setReferenceIntervalForTreatmentPump (int &reftime)
{
    if(reftime != _referenceIntervalForTreatmentPump)
    {
        _referenceIntervalForTreatmentPump = reftime;
        qDebug () << "emitting Signal ReferenceIntervalForTreatmentPumpChanged ()";
        emit ( referenceIntervalForTreatmentPumpChanged () );
    }
}


//% setTreatmentPumpCalibrationValue
void GarfunkelSystemContext::setTreatmentPumpCalibrationValue (float &pcaliValue)
{
    if(pcaliValue != _treatmentPumpCalibrationValue)
    {
        _treatmentPumpCalibrationValue = pcaliValue;
        qDebug () << "emitting Signal TreatmentPumpCalibrationValueChanged ()";
        emit ( treatmentPumpCalibrationValueChanged () );
    }
}

//% setBFWPSignalFilterTime
void GarfunkelSystemContext::setBFWPSignalFilterTime (int &bwfSFtime)
{
    if(bwfSFtime != _bFWPSignalFilterTime)
    {
        _bFWPSignalFilterTime = bwfSFtime;
        qDebug () << "emitting Signal BFWPSignalFilterTimeChanged ()";
        emit ( bFWPSignalFilterTimeChanged () );
    }
}


//% setMaxTimeBetweenBFWPCallsInHours
void GarfunkelSystemContext::setMaxTimeBetweenBFWPCallsInHours (int &maxHours)
{
    if(maxHours != _maxTimeBetweenBFWPCallsInHours)
    {
        _maxTimeBetweenBFWPCallsInHours = maxHours;
        qDebug () << "emitting Signal MaxTimeBetweenBFWPCallsInHoursChanged ()";
        emit ( maxTimeBetweenBFWPCallsInHoursChanged () );
    }
}



//% setMaxTimeForFillEventToComplete
void GarfunkelSystemContext::setMaxTimeForFillEventToComplete (int &maxComHours)
{
    if(maxComHours != _maxTimeForFillEventToComplete)
    {
        _maxTimeForFillEventToComplete = maxComHours;
        qDebug () << "emitting Signal MaxTimeForFillEventToCompleteChanged ()";
        emit ( maxTimeForFillEventToCompleteChanged () );
    }
}


//% setVirtualLevelCounterVolumeInGallon
void GarfunkelSystemContext::setVirtualLevelCounterVolumeInGallon (float &vcounterVolInGal)
{
    if(vcounterVolInGal != _virtualLevelCounterVolumeInGallon)
    {
        _virtualLevelCounterVolumeInGallon = vcounterVolInGal;
        qDebug () << "emitting Signal VirtualLevelCounterVolumeInGallonChanged ()";
        emit ( virtualLevelCounterVolumeInGallonChanged () );
    }
}


//% setSumpLowToFullVolumeInGallon
void GarfunkelSystemContext::setSumpLowToFullVolumeInGallon (float &lToFVolInGal)
{
    if(lToFVolInGal != _sumpLowToFullVolumeInGallon)
    {
        _sumpLowToFullVolumeInGallon = lToFVolInGal;
        qDebug () << "emitting Signal SumpLowToFullVolumeInGallonChanged ()";
        emit ( sumpLowToFullVolumeInGallonChanged () );
    }
}


//% setSumpFullToOverflowVolumeInGallon
void GarfunkelSystemContext::setSumpFullToOverflowVolumeInGallon (float &fToOVolInGal)
{
    if(fToOVolInGal != _sumpFullToOverflowVolumeInGallon)
    {
        _sumpFullToOverflowVolumeInGallon = fToOVolInGal;
        qDebug () << "emitting Signal SumpFullToOverflowVolumeInGallonChanged ()";
        emit ( sumpFullToOverflowVolumeInGallonChanged () );
    }
}


//% setSumpOverflowToAboveVolumeInGallon
void GarfunkelSystemContext::setSumpOverflowToAboveVolumeInGallon (float &oToAVolInGal)
{
    if(oToAVolInGal != _sumpOverflowToAboveVolumeInGallon)
    {
        _sumpOverflowToAboveVolumeInGallon = oToAVolInGal;
        qDebug () << "emitting Signal SumpOverflowToAboveVolumeInGallonChanged ()";
        emit ( sumpOverflowToAboveVolumeInGallonChanged () );
    }
}

//% setTimeDateOfLastFillEvent
//void GarfunkelSystemContext::setTimeDateOfLastFillEvent ( QDateTime &lFillDate)
void GarfunkelSystemContext::setTimeDateOfLastFillEvent (QString &lFillDate)
{
    if(lFillDate != _timeDateOfLastFillEvent)
    {
        //_timeDateOfLastFillEvent = lFillDate;
        _timeDateOfLastFillEvent = lFillDate.toAscii();
        qDebug () << "emitting Signal TimeDateOfLastFillEventChanged ()";
        emit ( timeDateOfLastFillEventChanged () );
    }
}


//% setTimeDateOfLastBFWPSignalReceived
//void GarfunkelSystemContext::setTimeDateOfLastBFWPSignalReceived ( QDateTime &lSigRecDate)
void GarfunkelSystemContext::setTimeDateOfLastBFWPSignalReceived (QString &lSigRecDate)
{
    if(lSigRecDate != _timeDateOfLastBFWPSignalReceived)
    {
        //_timeDateOfLastBFWPSignalReceived = lSigRecDate;
        _timeDateOfLastBFWPSignalReceived = lSigRecDate.toAscii();
        qDebug () << "emitting Signal TimeDateOfLastBFWPSignalReceivedChanged ()";
        emit ( timeDateOfLastBFWPSignalReceivedChanged () );
    }
}


//% setTimeBetweenBFWPEvents
void GarfunkelSystemContext::setTimeBetweenBFWPEvents ( int &inEventsTime)
{
    if(inEventsTime != _timeBetweenBFWPEvents)
    {
        _timeBetweenBFWPEvents = inEventsTime;
        qDebug () << "emitting Signal timeBetweenBFWPEventsChanged ()";
        emit ( timeBetweenBFWPEventsChanged () );
    }
}


//% setTimeDatePowerOn
//void GarfunkelSystemContext::setTimeDatePowerOn (QDateTime &pOnDate)
void GarfunkelSystemContext::setTimeDatePowerOn (QString &pOnDate)
{
    if(pOnDate != _timeDatePowerOn )
    {
       // _timeDatePowerOn = pOnDate;
        _timeDatePowerOn = pOnDate.toAscii();
        qDebug () << "emitting Signal TimeDatePowerOnChanged ()";
        emit ( timeDatePowerOnChanged () );
    }
}


//% setCausticRinseStartTime
//void GarfunkelSystemContext::setCausticRinseStartTime (QTime &rStartTime)
void GarfunkelSystemContext::setCausticRinseStartTime (QString &rStartTime)
{
    if(rStartTime != _causticRinseStartTime )
    {
        //_causticRinseStartTime = rStartTime.toAscii();
        _causticRinseStartTime = rStartTime.toAscii();
        qDebug () << "emitting Signal CausticRinseStartTimeChanged ()";
        emit ( causticRinseStartTimeChanged () );
    }
}


//% setCausticRinseFinishTime
//void GarfunkelSystemContext::setCausticRinseFinishTime (QTime &rFinishTime)
void GarfunkelSystemContext::setCausticRinseFinishTime (QString &rFinishTime)
{
    if(rFinishTime != _causticRinseFinishTime )
    {
        //_causticRinseFinishTime = rFinishTime;
        _causticRinseFinishTime = rFinishTime.toAscii();
        qDebug () << "emitting Signal CausticRinseFinishTimeChanged ()";
        emit ( causticRinseFinishTimeChanged () );
    }
}

//% setIsSystemInitialized
void GarfunkelSystemContext::setIsSystemInitialized (bool &isFlag)
{
    if(isFlag != _iSSystemInitialized)
    {
        _iSSystemInitialized = isFlag;
        qDebug () << "emitting Signal IsSystemInitializedChanged ()";
        emit ( iSSystemInitializedChanged () );
    }
}

//% setBaselineConductivity
//void GarfunkelSystemContext::setBaselineConductivity (qreal &bconductivity)
void GarfunkelSystemContext::setBaselineConductivity (float &bconductivity)
{
    if(bconductivity != _baselineConductivity)
    {
        _baselineConductivity = bconductivity;
        qDebug () << "emitting Signal BaselineConductivityChanged ()";
        emit ( baselineConductivityChanged () );
    }
}


//% setLayUpEnabled
void GarfunkelSystemContext::setLayUpEnabled (bool &eFlag)
{
    if(eFlag != _layUpEnabled)
    {
        _layUpEnabled = eFlag;
        qDebug () << "emitting Signal LayUpEnabledChanged ()";
        emit ( layUpEnabledChanged () );
    }
}


//% setPrimaryLanguage
void GarfunkelSystemContext::setPrimaryLanguage (int &pLang)
{

    if(pLang != _primaryLanguage)
    {
        _primaryLanguage = pLang;
        qDebug() << "emitting Signal PrimaryLanguageChanged ()";
        emit ( primaryLanguageChanged() );
    }
}



//%
//% setTMLanguage
//% Changes TM language in this class!!
//%
void GarfunkelSystemContext::setTMLanguage (int &tmLang)
{
    
    if(tmLang != _tmLanguage)
    {
        _tmLanguage = tmLang;
        qDebug() << "emitting Signal TMLanguageChanged ()";
        emit ( tmLanguageChanged() );
    }
}

//%
//% setSystemLangID
//%  
void GarfunkelSystemContext::setSystemLangID (int &langId)
{
     if(langId != _langID)
    {
        _langID = langId;
        qDebug() << "emitting Signal langChanged ()";
        emit (langIDChanged() );
    }

}
//%
//% setSystemLocalLang 
//% Sets the Local Language of the system TM this class!!
//% and notifies all other classes depending on language!!
//%
void GarfunkelSystemContext::setSystemLocalLang (const QString &localeID)
{

    if(localeID != _localeID)
    {
        _localeID = localeID.toAscii();
        emit localLangChanged ();
        //emit other signals so that other tables also get updated

        //%emit signal for Language changed!!!
        emit  _gDB->emitLocalizedStringsUpdated ();
        emit  _gDB->emitProductInfoUpdated ();
        emit  _gDB->emitProductSlotUpdated ();
        emit  _gDB->emitCustomerInfoUpdated ();
        emit  _gDB->emitAlarmDataUpdated ();
        emit  _gDB->emitScheduleSpecificPropertiesUpdated ();

        emit  _gDB->emitSBlockProductPropertiesUpdated ();
        emit  _gDB->emitPBlockProductPropertiesUpdated ();
        emit  _gDB->emitOCapsuleProductPropertiesUpdated ();

        emit  _gDB->emitBoilerPropertiesForProductUpdated ();
        emit  _gDB->emitRegulatoryLimitsUpdated ();

        emit  _gDB->emitCustomerInputSignalUpdated ();
        emit  _gDB->emitRegionSpecificAlarmPropertiesUpdated ();
        emit  _gDB->emitProductMapUpdated ();

        
    }
}




//%*********************************************************
//%   SETTERS OF THE DB
//%  (Automatically sets this class and the DB)
//%******************************************************** 



//% setDBUnitOfMeasure
//% set unit of measure in DB while at the same time
//% setting unit of measure in this class!
void GarfunkelSystemContext::setDBUnitOfMeasure(int &dbUofm)
{
    setUnitOfMeasure(dbUofm);
    const QString executeString = "SetUnitOfMeasure(" + QString::number(dbUofm) + ", " + "\'ui\')";
    qDebug() << "GarfunkelSystemContext::setDBUnitOfMeasure string = " << executeString;
    _gDB->executeStoredFunction(executeString);
}


//% 
//% setDBPrimaryLanguage
//%  sets Primary Language in DB and also in this class!!
//% 
void GarfunkelSystemContext::setDBPrimaryLanguage(int &dbpLang)
{
    setPrimaryLanguage(dbpLang);
    const QString executeString = "SetPrimaryLanguage(" + QString::number(dbpLang) + ", " + "\'ui\')";
    qDebug() << "GarfunkelSystemContext::setDBPrimaryLanguage string = " << executeString;
    _gDB->executeStoredFunction(executeString);
    emit primaryLanguageChangedinDB();
}


//% 
//% setDBTMLanguage
//% sets TM Language in DB and also in this class!!
//%
void GarfunkelSystemContext::setDBTMLanguage(int &dbtmLang)
{
    setTMLanguage(dbtmLang);
    const QString executeString = "SetTMLanguage(" + QString::number(dbtmLang) + ", " + "\'ui\')";
    qDebug() << "GarfunkelSystemContext::setDBTMLanguage string = " << executeString;
    _gDB->executeStoredFunction(executeString);
    emit tmLanguageChangedinDB();
}

/*
//% 
//% setDBSystemLocalLang  why?
//% sets system Language in DB and abviously in this class!!
//%
void GarfunkelSystemContext::setDBSystemLocalLang (const QString &dblocale)
{
    const QString executeString = "SetSystemLocaleID(" + dblocale + ", " + "\'ui\')";
    qDebug() << "GarfunkelSystemContext::setSystemLocalLang = " << executeString;
    ecolab::DB::DataSet dataSet;
    dataSet = _gDB->executeStoredFunction(executeString);
    setSystemLocalLang (dblocale);
}
*/


//%
//%
//%     SLOTS
//%



/*
//%
//%    SLOT
//%
//%
//%  getPasswordProperties
//%  of TM, SecretTM password Customer
//%
void GarfunkelSystemContext::getPasswordProperties(QString &tmPwd, QString &secTMPwd, QString &custPwd)
{
    tmPwd = QString::fromUtf8(_tmPassword.c_str(),_tmPassword.size());
    secTMPwd = QString::fromUtf8(_secretTMPassword.c_str(),_secretTMPassword.size());
    custPwd = QString::fromUtf8(_custPassword.c_str(),_custPassword.size());

}
*/

//%
//%     SLOT
//%    Makes sure synchronization with Database is good!!
//%  
void GarfunkelSystemContext::dbSyncEvent()
{
    qDebug() << "GarfunkelSystemContext::dbSyncStarted";
    emit dbSyncStarted();

}



//%     SLOT
//%
//%    grabGarfunkelSystemContext() Methods is a SLOT which receives SystemData from 
//%    Garfunkel DB instance and Updates the values to be read by the UI
//%
void GarfunkelSystemContext::grabGarfunkelSystemContext()
{
   

    if (!_gDB->isConnected())
    {
        qDebug() << "grabGarfunkelSystemContext NOT CONNECTED";
        _gDB->connect();
    }
    if(_gDB->isConnected())
    {
        qDebug() << "grabGarfunkelSystemContext CONNECTED";
        ecolab::DB::DataSet dataSet;
        dataSet = _gDB->executeStoredFunction(QString("GetSystemData()"));
        //if (dataSet.GetNumberOfRows() == 1) 
        if (dataSet.GetNumberOfRows() > 0) 
        {

            QString tmpString;
            ecolab::DB::DataRow rowData(dataSet.GetFirstRow());
            QVariant tmp;
            bool b;
            float f;
            int i; 

            disconnect(_gDB, SIGNAL(systemDataUpdated()), this, SLOT(grabGarfunkelSystemContext()));

            tmp = _gDB->value(rowData, "SystemDataID", GarfunkelDB::Int);
            i = tmp.toInt();
            setSystemDataID(i);
            /// Get Region ID
            tmp = _gDB->value(rowData, "RegionID", GarfunkelDB::Int);
            i = tmp.toInt();
            setRegionID(i);

            tmp = _gDB->value(rowData, "RegionName", GarfunkelDB::Int);
            i = tmp.toInt();
            setRegionName(i);
          
            /*
            tmp = _gDB->value(rowData, "SystemOpModeName", GarfunkelDB::Int);
            i = tmp.toInt();
            setSystemOpModeName(i);

            */
            
            
            tmp = _gDB->value(rowData, "DateFormatID", GarfunkelDB::Int);
            i = tmp.toInt();
            setDateFormatID(i);

            tmp = _gDB->value(rowData, "UnitOfMeasure", GarfunkelDB::Int);
            i = tmp.toInt();
            setUnitOfMeasure(i);

            tmp = _gDB->value(rowData, "DecimalOrComma", GarfunkelDB::Bool);
            b = tmp.toBool();
            setDecimalOrComma(b);

            tmp = _gDB->value(rowData, "IsTweleveHourFormat", GarfunkelDB::Bool);
            b = tmp.toBool();
            setIsTwelveHourTimeFormat(b);

            tmp = _gDB->value(rowData, "OperatingModeID", GarfunkelDB::Int);
            i = tmp.toInt();
            setOperatingModeID(i);
            /*
            tmp = _gDB->value(rowData, "DualOpSchedule", GarfunkelDB::Bool);
            bool b = tmp.toBool();
            setDualOperatingSchedule(b);
            */

            tmp = _gDB->value(rowData, "BoilerPressure", GarfunkelDB::Float); //%Real is DB
            f = tmp.toFloat();
            setBoilerPressure(f);

            tmp = _gDB->value(rowData, "IsDeareatorPresent", GarfunkelDB::Bool);
            b = tmp.toBool();
            setIsDeaeratorPresent(b);

            tmp = _gDB->value(rowData, "FWTemperature", GarfunkelDB::Float); //%Real is DB
            f = tmp.toFloat();
            setFeedWaterTemperature(f);

            tmp = _gDB->value(rowData, "DAOperatingPressure", GarfunkelDB::Float); //%Real is DB
            f = tmp.toFloat();
            setDAOperatingPressure(f);

            tmp = _gDB->value(rowData, "CyclesOfConcentrationTarget", GarfunkelDB::Float); //%Real is DB
            f = tmp.toFloat();
            setCyclesOfConcentrationTarget(f);

            tmp = _gDB->value(rowData, "NominalSteamFlow", GarfunkelDB::Float); //%Real is DB
            f = tmp.toFloat();
            setNominalSteamFlow(f);


            tmp = _gDB->value(rowData, "TotalCondensateReturn", GarfunkelDB::Float); //%Real is DB
            f = tmp.toFloat();
            setTotalCondensateReturn(f);

            tmp = _gDB->value(rowData, "IsBFWPIntermittent", GarfunkelDB::Bool);
            b = tmp.toBool();
            setIsBFWPIntermittent(b);

            tmp = _gDB->value(rowData, "OperatingHoursPerDay", GarfunkelDB::Int);
            i = tmp.toInt();
            setOperatingHoursPerDay(i);

            tmp = _gDB->value(rowData, "ReferenceIntervalForTreatmentPump", GarfunkelDB::Int);
            i = tmp.toInt();
            setReferenceIntervalForTreatmentPump(i);

            tmp = _gDB->value(rowData, "TreatmentPumpCalibrationValue", GarfunkelDB::Float); //%Real is DB
            f = tmp.toFloat();
            setTreatmentPumpCalibrationValue(f);

            tmp = _gDB->value(rowData, "BFWPSignalFilterTime", GarfunkelDB::Int);
            i = tmp.toInt();
            setBFWPSignalFilterTime(i);

            tmp = _gDB->value(rowData, "MaxTimeBetweenBFWPCallsInHours", GarfunkelDB::Int);
            i = tmp.toInt();
            setMaxTimeBetweenBFWPCallsInHours(i);

            tmp = _gDB->value(rowData, "MaxTimeForFillEventToComplete", GarfunkelDB::Int);
            i = tmp.toInt();
            setMaxTimeForFillEventToComplete(i);

            tmp = _gDB->value(rowData, "VirtualCounterVolumeInGallon", GarfunkelDB::Float); //%Real is DB
            f = tmp.toFloat();
            setVirtualLevelCounterVolumeInGallon(f);

            tmp = _gDB->value(rowData, "SumpLowToFullVolumeInGallon", GarfunkelDB::Float); //%Real is DB
            f = tmp.toFloat();
            setSumpLowToFullVolumeInGallon(f);

            tmp = _gDB->value(rowData, "SumpFullToOverFlowVolumeInGallon", GarfunkelDB::Float); //%Real is DB
            f = tmp.toFloat();
            setSumpFullToOverflowVolumeInGallon(f);

            tmp = _gDB->value(rowData, "SumpOverFlowToAboveVolumeInGallon", GarfunkelDB::Float); //%Real is DB
            f = tmp.toFloat();
            setSumpOverflowToAboveVolumeInGallon(f);

            //Use ALL QDateTime as Strings
            tmp = _gDB->value(rowData, "TimeDateOfStartOfLastFillEvent", GarfunkelDB::String); //%QDateTime in DB notes
            tmpString = tmp.toString();
            setTimeDateOfLastFillEvent(tmpString);

            //Use ALL QDateTime as Strings
            tmp = _gDB->value(rowData, "TimeDateOfLastBFWPSignalReceived", GarfunkelDB::String); //%QDateTime in DB notes
            tmpString = tmp.toString();
            setTimeDateOfLastBFWPSignalReceived(tmpString);

            tmp = _gDB->value(rowData, "TimeBetweenBFWPEvents", GarfunkelDB::Int); //%Real is DB
            i = tmp.toFloat();
            setTimeBetweenBFWPEvents(i);

            //Use ALL QDateTime as Strings
            tmp = _gDB->value(rowData, "TimeDatePowerOn", GarfunkelDB::String); //%QDateTime in DB notes
            tmpString = tmp.toString();
            setTimeDatePowerOn(tmpString);

            //Use ALL QDateTime as Strings
            tmp = _gDB->value(rowData, "CausticRinseStartTime", GarfunkelDB::String); //%QDateTime in DB notes
            tmpString = tmp.toString();
            setCausticRinseStartTime(tmpString);

            //Use ALL QDateTime as Strings
            tmp = _gDB->value(rowData, "CausticRinseFinishTime", GarfunkelDB::String); //%QDateTime in DB notes
            tmpString = tmp.toString();
            setCausticRinseFinishTime(tmpString);

            tmp = _gDB->value(rowData, "IsSystemInitialized", GarfunkelDB::Bool);
            b = tmp.toBool();
            setIsSystemInitialized(b);

            tmp = _gDB->value(rowData, "BaselineConductivity", GarfunkelDB::Float); //%Real is DB
            f = tmp.toFloat();
            setBaselineConductivity(f);

            tmp = _gDB->value(rowData, "LayupEnabled", GarfunkelDB::Bool);
            b = tmp.toBool();
            setLayUpEnabled(b);

            tmp = _gDB->value(rowData, "PrimaryLanguage", GarfunkelDB::Int);
            i = tmp.toInt();
            setPrimaryLanguage(i);

            tmp = _gDB->value(rowData, "TMLanguage", GarfunkelDB::Int);
            i = tmp.toInt();
            setTMLanguage(i);
            
            /*
            tmp = _gDB->value(rowData, "AlarmVolume", GarfunkelDB::Int);
            i = tmp.toInt();
            setAlarmVolume(i);

            tmp = _gDB->value(rowData, "AlarmMuteTime", GarfunkelDB::Int);
            i = tmp.toInt();
            setAlarmMuteTime(i);

            tmp = _gDB->value(rowData, "LastLCClearDate", GarfunkelDB::String);
            tmpString  = tmp.toString();
            setLastLCClearDate(tmpString);
            */

            connect(_gDB, SIGNAL(systemDataUpdated()), this, SLOT(grabGarfunkelSystemContext()));
        }
        else
        {
            qDebug() << " GarfunkelSystemContext NO DATA FOUND";
        }
    }
    else//if db not connected, read from flat files
    {

        qDebug() << "GarfunkelSystemContext : Reading system data from flat files";
        /*
           std::fstream    valuesRead("/usr/local/applications/Garfunkel-systemdata.txt", std::ios_base::in );

            if(True == valuesRead.is_open())
            {
                REAL64       RealValue;
                int          IntValue;
                std::string  StringValue;
                BOOLEAN      BoolValue;

                // System Data

                valuesRead >> IntValue;
                setPrimaryLanguage(IntValue);

                valuesRead >> IntValue;
                setTMLanguage(IntValue);

                valuesRead >> IntValue;
                setUnitOfMeasure(IntValue);

                valuesRead >> IntValue;
                setAlarmVolume(IntValue);

                valuesRead >> RealValue;
                setAlarmMuteTime(RealValue);

                valuesRead >> IntValue;
                setTypeOfEmptyAlarm(IntValue);

                valuesRead >> IntValue;
                setProbeSensorEmptyAlarmDelay(IntValue);

                valuesRead >> IntValue;
                setAdditionalProbeSensorEmptyAlarmDelay(IntValue);

                valuesRead >> IntValue;
                setOptionalFlushInstalled(IntValue);

                
                valuesRead >> StringValue;
                _primaryLocale.assign(StringValue);

                valuesRead >> StringValue;
                _programmingLocale.assign(StringValue);

                valuesRead >> StringValue;
                _primaryLocaleFont.assign(StringValue);


                valuesRead >> StringValue;
                _programmingLocaleFont.assign(StringValue);

                valuesRead >> IntValue;
                _primaryLocaleFontPointSize = IntValue;

                valuesRead >> IntValue;
                _programmingLocaleFontPointSize = IntValue;

                valuesRead >> IntValue;
                if(IntValue==1)
                    _primaryLocaleFontBold = True;
                else
                    _primaryLocaleFontBold = False;
               
                valuesRead >> IntValue;
                if(IntValue==1)
                    _programmingLocaleFontBold = True;
                else
                    _programmingLocaleFontBold = False;


                valuesRead >> StringValue;
                _primaryLocaleFontFallback.assign(StringValue);

                valuesRead >> IntValue;
                _primaryLocaleFallbackFontPointSize = IntValue;

                valuesRead >> IntValue;
                if(IntValue==1)
                    _primaryLocaleFallbackFontBold = True;
                else
                    _primaryLocaleFallbackFontBold = False;

                valuesRead >> StringValue;
                _tmPassword.assign(StringValue);

                valuesRead >> StringValue;
                _secretTMPassword.assign(StringValue);

                valuesRead >> StringValue;
                _custPassword.assign(StringValue);

                valuesRead.close();

            }
            else
            {
                std::cout << "ERROR: Can't open Garfunkel-systemdata.txt." << std::endl;
            }

       */

    }


}

//%
//%  grabLocalLanguageNames ()
//%  Updates the Local (RegionID, RegionName, Status) from DB of this class)
//%
 void GarfunkelSystemContext::grabLocalLanguageNames ()
 {

    if (!_gDB->isConnected())
    {
        qDebug() << "grabLocalLanguageNames NOT CONNECTED";
        _gDB->connect();
    }
    if(_gDB->isConnected())
    {
        qDebug() << "grabLocalLanguageNames CONNECTED";
        ecolab::DB::DataSet dataSet = _gDB->executeStoredFunction(QString("GetLanguageRef()"));
        //ecolab::DB::DataSet dataSet = _gDB->executeStoredFunction(QString("GetLocaleNames()")); The better way!!
        
        int numRows = dataSet.GetNumberOfRows();

        for(int row = 0; row < numRows; ++row)
        {
            ecolab::DB::DataRow rowData = dataSet.GetRow(row);
            QVariant tmp = "";
            QString tmpString = "";
            int i = -1;

            //% Get LocalLanguage stuff already in the DB
            tmp = _gDB->value(rowData, "LanguageID", GarfunkelDB::Int);
            i = tmp.toInt();
            setSystemLangID(i);

            tmp = _gDB->value(rowData, "LocaleID", GarfunkelDB::String);
            tmpString = tmp.toString();
            setSystemLocalLang (tmpString);

            //Get Status Code!!!
            tmp = _gDB->value(rowData, "StatusCode", GarfunkelDB::String); 
            tmpString = tmp.toString();
            setStatusCode(tmpString);
       }

    }
     else

      {
            qDebug() << "grabLocalLanguageNames  NOT CONNECTED SO NO DATA FOUND";
      }


 }
  



