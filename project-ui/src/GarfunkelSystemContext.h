#ifndef GARFUNKEL_SYSTEM_CONTEXT_H
#define GARFUNKEL_SYSTEM_CONTEXT_H

#include <QObject>
#include <QStringList>
#include <QDeclarativeContext>
#include <QAbstractListModel>
#include <QDebug>
#include <QDateTime>
#include <QTime>
#include <QProcess>
//% Private classes!!
#include "GarfunkelDB.h"
#include "GarfunkelSystemData.h"  //% Communicate with MCA

//#include "timezonedata.h"


//%    GarfunkelSystemContext 
//%
//%    The GarfunkelSystemContext class is an interface for exporting variables and
//%    methods to QML that are typically used for  interacting with the 
//%    Configure Screen
//%    
//%
class GarfunkelSystemContext : public QObject
{
    Q_OBJECT

    //% SystemData ID from DB
    Q_PROPERTY (int systemDataID    READ  getSystemDataID   WRITE  setSystemDataID     NOTIFY systemDataIDChanged  )
    //%
    //% Region ID Primary Key
    Q_PROPERTY (int regionID    READ  getRegionID    WRITE  setRegionID      NOTIFY  regionIDChanged )
    //%
    //% Region Name
    Q_PROPERTY (int regionName   READ  getRegionName    WRITE  setRegionName    NOTIFY  regionNameChanged )
    //%
    //% Status Code default is always "A"
    Q_PROPERTY (QString  statusCode  READ  getStatusCode   WRITE setStatusCode    NOTIFY   statusCodeChanged )
    //%
    //% System Operation Mode ID
    Q_PROPERTY (int systemOpModeID   READ  getSystemOpModeID  WRITE setSystemOpModeID  NOTIFY  systemOpModeIDChanged )
    //%
    //% System Operation Mode Name
    Q_PROPERTY (int systemOpModeName   READ  getSystemOpModeName  WRITE setSystemOpModeName  NOTIFY systemOpModeNameChanged )
    //%
    //% Date Formate ID
    Q_PROPERTY (int dateFormatID  READ  getDateFormatID   WRITE  setDateFormatID   NOTIFY dateFormatIDChanged )
    //%
    //% Unit for Measuring quantities, default is US unit format
    Q_PROPERTY (int  unitOfMeasure   READ getUnitOfMeasure   WRITE setUnitOfMeasure   NOTIFY unitOfMeasureChanged )
    //%
    //% Use decimal or Comma for Numbers
    Q_PROPERTY (bool  decimalOrComma  READ getDecimalOrComma  WRITE setDecimalOrComma  NOTIFY decimalOrCommaChanged )
    //%
    //% 12 or 24 Hour Format  
    Q_PROPERTY (bool iSTwelveHourTimeFormat  READ  getIsTwelveHourTimeFormat   WRITE  setIsTwelveHourTimeFormat  NOTIFY  iSTwelveHourTimeFormatChanged )
    //%
    //% Operating Mode
    Q_PROPERTY (int operatingModeID   READ getOperatingModeID    WRITE  setOperatingModeID  NOTIFY  operatingModeIDChanged )
    //%
    //% Dual Operating Schedule
    Q_PROPERTY (bool dualOperatingSchedule   READ getDualOperatingSchedule   WRITE setDualOperatingSchedule  NOTIFY  dualOperatingScheduleChanged )
    //%
    //% Boiler Pressure
    Q_PROPERTY (float  boillerPressure   READ  getBoillerPressure    WRITE   setBoilerPressure  NOTIFY boilerPressureChanged )
    //%
    //% Deaerator Pressent
    Q_PROPERTY (bool  iSDeaeratorPresent    READ  getIsDeaeratorPresent    WRITE  setIsDeaeratorPresent    NOTIFY  iSDeaeratorPresentChanged )
    //%
    //% FeedWater Temperature
    Q_PROPERTY (float  feedWaterTemperature   READ  getFeedWaterTemperature    WRITE   setFeedWaterTemperature    NOTIFY  feedWaterTemperatureChanged  )
    //%
    //% DA Operating Pressure
    Q_PROPERTY (float dAOperatingPressure   READ getDAOperatingPressure   WRITE setDAOperatingPressure  NOTIFY dAOperatingPressureChanged )
    //%
    //% Cycles of Concentration Target
    Q_PROPERTY (float cyclesOfConcentrationTarget  READ getCyclesOfConcentrationTarget   WRITE setCyclesOfConcentrationTarget  NOTIFY cyclesOfConcentrationTargetChanged )
    //%
    //% Nominal STeam Flow
    Q_PROPERTY (float nominalSteamFlow  READ getNominalSteamFlow   WRITE setNominalSteamFlow  NOTIFY nominalSteamFlowChanged )
    //%
    //% Total Condensate Return
    Q_PROPERTY (float totalCondensateReturn  READ getTotalCondensateReturn    WRITE setTotalCondensateReturn   NOTIFY  totalCondensateReturnChanged )
    //%
    //% Type of Call of Boiler Water Feed Pressure
    Q_PROPERTY (bool iSBFWPIntermittent  READ  getIsBFWPIntermittent  WRITE setIsBFWPIntermittent    NOTIFY  iSBFWPIntermittentChanged )
    //%
    //% Hours of Operationg per day
    Q_PROPERTY (int operatingHoursPerDay   READ  getOperatingHoursPerDay  WRITE setOperatingHoursPerDay   NOTIFY operatingHoursPerDayChanged )
    //%
    //% Reference Interval for Water Pump
    Q_PROPERTY (int referenceIntervalForTreatmentPump   READ getReferenceIntervalForTreatmentPump   WRITE  setReferenceIntervalForTreatmentPump   NOTIFY  referenceIntervalForTreatmentPumpChanged )
    //%
    //% Pump Calibration Value
    Q_PROPERTY (float treatmentPumpCalibrationValue    READ  getTreatmentPumpCalibrationValue   WRITE  setTreatmentPumpCalibrationValue   NOTIFY  treatmentPumpCalibrationValueChanged )
    //%
    //% BFWP Signal Time 
    Q_PROPERTY (int bFWPSignalFilterTime   READ  getBFWPSignalFilterTime   WRITE  setBFWPSignalFilterTime   NOTIFY  bFWPSignalFilterTimeChanged )
    //%
    //% Maximum Time Between BFWP calls
    Q_PROPERTY (int maxTimeBetweenBFWPCallsInHours   READ  getMaxTimeBetweenBFWPCallsInHours   WRITE  setMaxTimeBetweenBFWPCallsInHours   NOTIFY maxTimeBetweenBFWPCallsInHoursChanged )
    //%
    //%  Maximum Time for Fill Event to Complete
    Q_PROPERTY (int maxTimeForFillEventToComplete    READ  getMaxTimeForFillEventToComplete   WRITE  setMaxTimeForFillEventToComplete    NOTIFY  maxTimeForFillEventToCompleteChanged )
    //%
    //% Virtual Level Counter Volve in Gallons
    Q_PROPERTY (float virtualLevelCounterVolumeInGallon     READ  getVirtualLevelCounterVolumeInGallon    WRITE  setVirtualLevelCounterVolumeInGallon    NOTIFY  virtualLevelCounterVolumeInGallonChanged )
    //%
    //% Sump Low to Full  Volume Ratio in Gallons
    Q_PROPERTY (float sumpLowToFullVolumeInGallon   READ  getSumpLowToFullVolumeInGallon    WRITE setSumpLowToFullVolumeInGallon   NOTIFY sumpLowToFullVolumeInGallonChanged )
    //%
    //% Sump Full to Over FLow Volume ratio in Gallons
    Q_PROPERTY (float sumpFullToOverflowVolumeInGallon    READ getSumpFullToOverflowVolumeInGallon   WRITE setSumpFullToOverflowVolumeInGallon     NOTIFY sumpFullToOverflowVolumeInGallonChanged )
    //%
    //% Sump Overflow to Above Volume Ratio in Gallons
    Q_PROPERTY (float sumpOverflowToAboveVolumeInGallon    READ getSumpOverflowToAboveVolumeInGallon  WRITE setSumpOverflowToAboveVolumeInGallon    NOTIFY sumpOverflowToAboveVolumeInGallonChanged )
    //%
    //% Time Date of Start of Last Fill Event
    //Q_PROPERTY (QDateTime  timeDateOfLastFillEvent    READ  getTimeDateOfLastFillEvent   WRITE setTimeDateOfLastFillEvent  NOTIFY  timeDateOfLastFillEventChanged )
    Q_PROPERTY (QString  timeDateOfLastFillEvent    READ  getTimeDateOfLastFillEvent   WRITE setTimeDateOfLastFillEvent  NOTIFY  timeDateOfLastFillEventChanged )
    //%
    //% Time Date of Last BFWP Signal Received
    //Q_PROPERTY (QDateTime  timeDateOfLastBFWPSignalReceived    READ  getTimeDateOfLastBFWPSignalReceived   WRITE  setTimeDateOfLastBFWPSignalReceived    NOTIFY  timeDateOfLastBFWPSignalReceivedChanhed )
    Q_PROPERTY (QString  timeDateOfLastBFWPSignalReceived    READ  getTimeDateOfLastBFWPSignalReceived   WRITE  setTimeDateOfLastBFWPSignalReceived    NOTIFY  timeDateOfLastBFWPSignalReceivedChanged )
    //%
    //% Time between BFWP Events
    Q_PROPERTY (int timeBetweenBFWPEvents    READ getTimeBetweenBFWPEvents   WRITE  setTimeBetweenBFWPEvents     NOTIFY  timeBetweenBFWPEventsChanged )
    //%
    //% TimeDate Power On
    //Q_PROPERTY (QDateTime timeDatePowerOn    READ getTimeDatePowerOn   WRITE setTimeDatePowerOn   NOTIFY  timeDatePowerOnChanged )
    Q_PROPERTY (QString timeDatePowerOn    READ getTimeDatePowerOn   WRITE setTimeDatePowerOn   NOTIFY  timeDatePowerOnChanged )
    //%
    //% CausticRinse Start Time
    //Q_PROPERTY (QTime  causticRinseStartTime   READ  getCausticRinseStartTime    WRITE  setCausticRinseStartTime   NOTIFY causticRinseStartTimeChanged )
    Q_PROPERTY (QString  causticRinseStartTime   READ  getCausticRinseStartTime    WRITE  setCausticRinseStartTime   NOTIFY causticRinseStartTimeChanged )
    //%
    //% CausticRinse Finish time
    //Q_PROPERTY (QTime  causticRinseFinishTime   READ getCausticRinseFinishTime  WRITE setCausticRinseFinishTime   NOTIFY causticRinseFinishTimeChanged )
    Q_PROPERTY (QString  causticRinseFinishTime   READ getCausticRinseFinishTime  WRITE setCausticRinseFinishTime   NOTIFY causticRinseFinishTimeChanged )
    //%
    //% Is system Initialized
    Q_PROPERTY (bool  iSSystemInitialized   READ  getIsSystemInitialized   WRITE setIsSystemInitialized   NOTIFY iSSystemInitializedChanged )
    //%
    //% Baseline Conductivity real
    //Q_PROPERTY(qreal  baselineConductivity   READ getBaselineConductivity  WRITE setBaselineConductivity  NOTIFY baselineConductivityChanged )
    Q_PROPERTY(float  baselineConductivity   READ getBaselineConductivity  WRITE setBaselineConductivity  NOTIFY baselineConductivityChanged )
    //%
    //% Layup Mode enabled
    Q_PROPERTY (bool layUpEnabled    READ getLayUpEnabled   WRITE  setLayUpEnabled    NOTIFY  layUpEnabledChanged )

    //% Using the setDB methods also for the application of the changes of both this class and that of the DB
    //%
    //%Primary Language
    Q_PROPERTY(int  primaryLanguage    READ getPrimaryLanguage     WRITE setDBPrimaryLanguage    NOTIFY primaryLanguageChanged )
    //%
    //% TM Language
    Q_PROPERTY(int  tmLanguage       READ getTMLanguage     WRITE setDBTMLanguage     NOTIFY tmLanguageChanged)

    //% Set the Local Language of the System Languages
    Q_PROPERTY(QString  localLang    READ  getSystemLocalLang      WRITE setSystemLocalLang     NOTIFY localLangChanged )
 // % Set the Local LanguageID of the System Languages
    Q_PROPERTY(int  langID     READ  getSystemLangID      WRITE setSystemLangID     NOTIFY langIDChanged )
    //Q_PROPERTY(double  alarmMuteTime    READ getAlarmMuteTime  WRITE setDBAlarmMuteTime  NOTIFY alarmMuteTimeChanged)
    //Q_PROPERTY(double     alarmVolume      READ getAlarmVolume    WRITE setDBAlarmVolume   NOTIFY alarmVolumeChanged)
    //Q_PROPERTY(int     typeOfEmptyAlarm READ getTypeOfEmptyAlarm WRITE setDBTypeOfEmptyAlarm   NOTIFY typeOfEmptyAlarmChanged)
    //Q_PROPERTY(QString lastLCClearDate  READ getLastLCClearDate WRITE setLastLCClearDate   NOTIFY lastLCClearDateChanged)
 
    //% Interesting Functions!!!
    //% Sets the date/time of entire system
    void setSystemDateTime(int month, int day, int hours, int minutes, int year);

public:
    //%
    //%   Our Beloved   Constructor
    //%
    GarfunkelSystemContext(GarfunkelDB *gdb, QDeclarativeContext *context, QObject *parent = 0);

    //%
    //%  Destructor 
    //%
    virtual ~GarfunkelSystemContext ();


    //% Call from UI how to set system date and Time
    Q_INVOKABLE void setSystemDate(int year, int month, int day)
    {
	setSystemDateTime(month, day, -1, -1, year);
    }
	//%Call from UI how to set system date and Time
    Q_INVOKABLE void setSystemTime(int hours, int minutes, int seconds)
    {
    Q_UNUSED(seconds);
    //% default should be current date and time!!
	setSystemDateTime(-1, -1, hours, minutes, -1);
    }

    //%
    //%  GETTING FUNCTIONS
    //%
    int getSystemDataID ( )                                 { return    _systemDataID;                      }
    int getRegionID ()                                      { return    _regionID;                          }
    int getRegionName ()                                    { return    _regionName;                        }
    QString getStatusCode ()                                { return    _statusCode;                        }
    int getSystemOpModeID ()                                { return    _systemOpModeID;                    }
    int getSystemOpModeName ()                              { return    _systemOpModeName;                  }
    int getDateFormatID ()                                  { return    _dateFormatID;                      }
    int getUnitOfMeasure ()                                 { return    _unitOfMeasure;                     }
    bool getDecimalOrComma ()                               { return    _decimalOrComma;                    }
    bool getIsTwelveHourTimeFormat ()                       { return    _iSTwelveHourTimeFormat;            }
    int getOperatingModeID ()                               { return    _operatingModeID;                  }
    bool getDualOperatingSchedule ()                        { return    _dualOperatingSchedule;             }
    float getBoillerPressure ()                             { return    _boilerPressure;                    }
    bool getIsDeaeratorPresent ()                           { return    _iSDeaeratorPresent;                }
    float getFeedWaterTemperature ()                        { return    _fWTemperature;                     }
    float getDAOperatingPressure ()                         { return    _dAOperatingPressure;               }
    float getCyclesOfConcentrationTarget ()                 { return    _cyclesOfConcentrationTarget;       }
    float getNominalSteamFlow ()                            { return    _nominalSteamFlow;                  }
    float getTotalCondensateReturn ()                       { return    _totalCondensateReturn;             }
    bool getIsBFWPIntermittent ()                           { return    _iSBFWPIntermittent;                }
    int getOperatingHoursPerDay ()                          { return    _operatingHoursPerDay;              }
    int getReferenceIntervalForTreatmentPump ()             { return    _referenceIntervalForTreatmentPump; }
    float getTreatmentPumpCalibrationValue ()               { return    _treatmentPumpCalibrationValue;     }
    int getBFWPSignalFilterTime ()                          { return    _bFWPSignalFilterTime;              }
    int getMaxTimeBetweenBFWPCallsInHours ()                { return    _maxTimeBetweenBFWPCallsInHours;    }
    int getMaxTimeForFillEventToComplete ()                 { return    _maxTimeForFillEventToComplete;     }
    float getVirtualLevelCounterVolumeInGallon ()           { return    _virtualLevelCounterVolumeInGallon; }
    float getSumpLowToFullVolumeInGallon ()                 { return    _sumpLowToFullVolumeInGallon;       }
    float getSumpFullToOverflowVolumeInGallon ()            { return    _sumpFullToOverflowVolumeInGallon;  }
    float getSumpOverflowToAboveVolumeInGallon ()           { return    _sumpOverflowToAboveVolumeInGallon; }
    //QDateTime getTimeDateOfLastFillEvent ()                 { return    _timeDateOfLastFillEvent;           }
    //QDateTime getTimeDateOfLastBFWPSignalReceived ()        { return    _timeDateOfLastBFWPSignalReceived;  }
    QString getTimeDateOfLastFillEvent ()                 { return    _timeDateOfLastFillEvent;           }
    QString getTimeDateOfLastBFWPSignalReceived ()        { return    _timeDateOfLastBFWPSignalReceived;  }
    int getTimeBetweenBFWPEvents ()                         { return    _timeBetweenBFWPEvents;             }
    //QDateTime getTimeDatePowerOn ()                         { return    _timeDatePowerOn;                   }
    //QTime getCausticRinseStartTime ()                       { return    _causticRinseStartTime;             }
    //QTime getCausticRinseFinishTime ()                      { return    _causticRinseFinishTime;            }
    QString getTimeDatePowerOn ()                         { return    _timeDatePowerOn;                   }
    QString getCausticRinseStartTime ()                       { return    _causticRinseStartTime;             }
    QString getCausticRinseFinishTime ()                      { return    _causticRinseFinishTime;            }
    bool getIsSystemInitialized ()                          { return    _iSSystemInitialized;               }
    //qreal getBaselineConductivity ()                        { return    _baselineConductivity;              }
    float getBaselineConductivity ()                        { return    _baselineConductivity;              }
    bool getLayUpEnabled ()                                 { return    _layUpEnabled;                      }
    int getPrimaryLanguage ()                               { return    _primaryLanguage;                   }
    int getTMLanguage ()                                    { return    _tmLanguage;                        }

    //int getAlarmVolume();
    //int getTypeOfEmptyAlarm();
    //double getAlarmMuteTime();
    //QString getLastLCClearDate();

    //% Get the Local Language of the  system!!
    QString getSystemLocalLang ()                               { return  _localeID;                        }   
    //% Get the Local Language of the  system!!
    int getSystemLangID ()                                  { return  _langID;                            }   

    //%
    //%   SETTING FUNCTIONS
    //%
    void setSystemDataID (int &sysDataId);
    void setRegionID (int &regId);
    void setRegionName ( int &regName);
    void setStatusCode ( QString &sCode);
    void setSystemOpModeID ( int &sysOpModeId);
    void setSystemOpModeName (int &sysOpModeName);
    void setDateFormatID ( int &dateformatId);
    void setUnitOfMeasure(int &uOfM);
    void setDecimalOrComma ( bool &dOrcFlag);
    void setIsTwelveHourTimeFormat ( bool &hFlag);
    void setOperatingModeID (int &opModeId);
    void setDualOperatingSchedule ( bool &dOpSchFlag);
    void setBoilerPressure ( float &bPressure);
    void setIsDeaeratorPresent ( bool &dFlag);
    void setFeedWaterTemperature ( float &fwTemp);
    void setDAOperatingPressure ( float &daOpPressure);
    void setCyclesOfConcentrationTarget ( float &concTarget);
    void setNominalSteamFlow ( float &nsteamFlow);
    void setTotalCondensateReturn ( float &tCondRet);
    void setIsBFWPIntermittent ( bool &bwiFlage);
    void setOperatingHoursPerDay ( int &opHpD);
    void setReferenceIntervalForTreatmentPump ( int &reftime);
    void setTreatmentPumpCalibrationValue ( float &pcaliValue);
    void setBFWPSignalFilterTime ( int &bwfSFtime);
    void setMaxTimeBetweenBFWPCallsInHours ( int &maxHours);
    void setMaxTimeForFillEventToComplete  (int &maxComHours);
    void setVirtualLevelCounterVolumeInGallon ( float &vcounterVolInGal);
    void setSumpLowToFullVolumeInGallon ( float &lToFVolInGal);
    void setSumpFullToOverflowVolumeInGallon ( float &fToOVolInGal);
    void setSumpOverflowToAboveVolumeInGallon ( float &oToAVolInGal);
    //void setTimeDateOfLastFillEvent ( QDateTime &lFillDate);
    //void setTimeDateOfLastBFWPSignalReceived (QDateTime &lSigRecDate);
    void setTimeDateOfLastFillEvent ( QString &lFillDate);
    void setTimeDateOfLastBFWPSignalReceived (QString &lSigRecDate);
    void setTimeBetweenBFWPEvents ( int &inEventsTime);
    //void setTimeDatePowerOn (QDateTime &pOnDate);
    //void setCausticRinseStartTime (QTime &rStartTime);
    //void setCausticRinseFinishTime (QTime &rFinishTime);
    void setTimeDatePowerOn (QString &pOnDate);
    void setCausticRinseStartTime (QString &rStartTime);
    void setCausticRinseFinishTime (QString &rFinishTime);
    void setIsSystemInitialized (bool &isFlag);
    //void setBaselineConductivity (qreal &bconductivity);
   
    void setBaselineConductivity (float &bconductivity);
    void setLayUpEnabled ( bool &eFlag);
    void setPrimaryLanguage (int &pLang);
    void setTMLanguage (int &tmLang);
    //Set the system Context Language!!
    void setSystemLocalLang (const QString &localID);
    void setSystemLangID ( int &langId);
    



    //%
    //%  DB SETTERS (& this calss!!)!!
    //%
    void setDBUnitOfMeasure (int &dbUofm);
    void setDBPrimaryLanguage (int &dbpLang);
    void setDBTMLanguage (int &dbtmLang);

    //Set the Language in the DB and obviously this class!
    //void setDBSystemLocalLang (const QString &dblocal);
    //void setDBSystemLangID ( int &dblangId);

    //void setAlarmVolume(int);
    //void setTypeOfEmptyAlarm(int);
    //void setAlarmMuteTime(double);
    //void setLastLCClearDate(QString);

    ////%%void setDBSystemLocale(int &dbLocal);

    //void setDBTypeOfEmptyAlarm(int);
    //void setDBAlarmVolume(int);
    //void setDBAlarmMuteTime(double);

    
    //%
    //%  SIGNALS
    //%


signals:

    void systemDataIDChanged ();
    void regionIDChanged ();
    void regionNameChanged ();
    void statusCodeChanged ();
    void systemOpModeIDChanged ();
    void systemOpModeNameChanged ();
    void dateFormatIDChanged ();
    void unitOfMeasureChanged();
    void decimalOrCommaChanged ();
    void iSTwelveHourTimeFormatChanged ();
    void operatingModeIDChanged ();
    void dualOperatingScheduleChanged ();
    void boilerPressureChanged ();
    void iSDeaeratorPresentChanged ();
    void feedWaterTemperatureChanged ();
    void dAOperatingPressureChanged ();
    void cyclesOfConcentrationTargetChanged ();
    void nominalSteamFlowChanged ();
    void totalCondensateReturnChanged ();
    void iSBFWPIntermittentChanged ();
    void operatingHoursPerDayChanged ();
    void referenceIntervalForTreatmentPumpChanged ();
    void treatmentPumpCalibrationValueChanged ();
    void bFWPSignalFilterTimeChanged ();
    void maxTimeBetweenBFWPCallsInHoursChanged ();
    void maxTimeForFillEventToCompleteChanged ();
    void virtualLevelCounterVolumeInGallonChanged ();
    void sumpLowToFullVolumeInGallonChanged ();
    void sumpFullToOverflowVolumeInGallonChanged ();
    void sumpOverflowToAboveVolumeInGallonChanged ();
    void timeDateOfLastFillEventChanged ();
    void timeDateOfLastBFWPSignalReceivedChanged ();
    void timeBetweenBFWPEventsChanged ();
    void timeDatePowerOnChanged ();
    void causticRinseStartTimeChanged ();
    void causticRinseFinishTimeChanged ();
    void iSSystemInitializedChanged ();
    void baselineConductivityChanged ();
    void layUpEnabledChanged ();
    void primaryLanguageChanged ();
    void secondaryLanguageChanged ();
    void tmLanguageChanged ();
    //% signal LocalLanguage has changed!!
    void localLangChanged (); 
    void langIDChanged ();  

    // In case above signals are not doing their job!!!
    void primaryLanguageChangedinDB();
    //void secondaryLanguageChangedinDB();
    void tmLanguageChangedinDB();

    //% when to emit this?
    void lastLoginChanged();


    //void alarmMuteTimeChanged();
    //void alarmVolumeChanged(); 
    //void lastLCClearDateChanged();
    //void localeChanged();

    

    void dbSyncStarted();



    //%
    //%    SLOTS 
    //%
public slots:

    void    grabGarfunkelSystemContext ();           //% Grabs all data elements from DB
    void    grabLocalLanguageNames ();
    void    dbSyncEvent();
    /*
    void    getFontProperties(std::string &primLang, std::string &secLang, std::string &tmLanguage,
        					   std::string &primLangFont, std::string &secLangFont, std::string &tmLangFont,
        					   int &primLangFontPointSize, int &secLangFontPointSize, int &tmLangFontPointSize,
        					   BOOLEAN &primLangFontBold,  BOOLEAN &secLangFontBold, BOOLEAN &tmLangFontBold,
        					   std::string &primLangFallbackFont, int &primLangFallbackFontPointSize, BOOLEAN &primLangFallbackFontBold);
    */
    //void    getPasswordProperties(QString &tmPwd, QString &secTMPwd, QString &custPwd);


private:
    GarfunkelDB*        _gDB;               //% Pointer to the database instances.
    QDeclarativeContext* _Context;          //% Pointer to the declarative context.

    //%    Default variables
    //% 

    //% initialises default variables
    void    _initDefaultVariables ();

    int     _systemDataID;
    //% SystemRegion ref Stuff
    int     _regionID;
    int     _regionName;
    QString     _statusCode;
    //% SystemOpMode ref stuff
    int     _systemOpModeID;
    int     _systemOpModeName;
    //% DateFormat ref stuff
    int     _dateFormatID;
  
    int     _unitOfMeasure;
    bool    _decimalOrComma;
    bool    _iSTwelveHourTimeFormat;
    int     _operatingModeID;

    bool    _dualOperatingSchedule;
    float   _boilerPressure;  
    bool    _iSDeaeratorPresent;
    float   _fWTemperature;
    float   _dAOperatingPressure;
    float   _cyclesOfConcentrationTarget;
    float   _nominalSteamFlow;
    float   _totalCondensateReturn;
    bool    _iSBFWPIntermittent;
    int     _operatingHoursPerDay;
    int     _referenceIntervalForTreatmentPump;
    float   _treatmentPumpCalibrationValue;
    int     _bFWPSignalFilterTime;
    int     _maxTimeBetweenBFWPCallsInHours;
    float   _maxTimeForFillEventToComplete;
    float   _virtualLevelCounterVolumeInGallon;
    float   _sumpLowToFullVolumeInGallon;
    float   _sumpFullToOverflowVolumeInGallon;
    float   _sumpOverflowToAboveVolumeInGallon;

    //QDateTime   _timeDateOfLastFillEvent;
    //QDateTime   _timeDateOfLastBFWPSignalReceived;
    QString   _timeDateOfLastFillEvent;
    QString   _timeDateOfLastBFWPSignalReceived;
    int     _timeBetweenBFWPEvents;
    //QDateTime   _timeDatePowerOn;
    //QTime   _causticRinseStartTime;
    //QTime   _causticRinseFinishTime;
    QString   _timeDatePowerOn;
    QString   _causticRinseStartTime;
    QString  _causticRinseFinishTime;
    bool    _iSSystemInitialized;
    //qreal    _baselineConductivity;
    float    _baselineConductivity;
    bool    _layUpEnabled; 

    int     _primaryLanguage;
    int     _tmLanguage;
    QString     _localeID; 
    int     _langID; 

    /*
    std::string             _dtmPassword;
    std::string             _rTMPassword ;
    std::string             _custPassword;
    */
    //int     _alarmVolume;
    //double  _alarmMuteTime;
    //QString _lastLCClearDate;
    
    //% Stuff read from Local file, Local file is read if database connection is down!
    //int                     _locale;
    //std::string             _primaryLocale;

    //std::string             _programmingLocale;
    //std::string             _primaryLocaleFont;
    //std::string             _primaryLocaleFontFallback;
    //std::string             _programmingLocaleFont;

    //int             _primaryLocaleFontPointSize;
    //int             _primaryLocaleFallbackFontPointSize;
    //int             _programmingLocaleFontPointSize;
    //BOOLEAN         _primaryLocaleFontBold;
    //BOOLEAN         _primaryLocaleFallbackFontBold;
    //BOOLEAN         _programmingLocaleFontBold;

    
};

#endif // GARFUNKEL_SYSTEM_CONTEXT_H
