
#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QString>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "DBAccess.h"
#include "ecolab.h"

#include "GarfunkelDB.h"


//% kepp these Outside
const char *GarfunkelDB::hostdb = "";
const char *GarfunkelDB::dbname = "Garfunkel";
const char *GarfunkelDB::dbuser = "db_user_admin"; // db_controller or 
const char *GarfunkelDB::dbpasswd = "controller";
bool GarfunkelDB::_dbSyncStop = false;



//%*******************************************
//%
//% Garfunkel CallBack Registration Begins
//%
//%*******************************************


//%************************************************************************************************
//%
//%   Implementation of class LocalizedStringsCallback
//%
//%************************************************************************************************
LocalizedStringsCallback::LocalizedStringsCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
LocalizedStringsCallback::~LocalizedStringsCallback()
{
}

BOOLEAN  LocalizedStringsCallback::Update()
{

    _garfunkelDB->emitLocalizedStringsUpdated (); 
    return True;
}

//%************************************************************************************************
//%
//%   Implementation of class OperatingScheduleCallback
//%
//%************************************************************************************************
OperatingScheduleCallback::OperatingScheduleCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
OperatingScheduleCallback::~OperatingScheduleCallback()
{
}

BOOLEAN  OperatingScheduleCallback::Update()
{
    _garfunkelDB->emitOperatingScheduleUpdated (); 
    //% Also Emit Date Format Refence Updated Signal
    _garfunkelDB->emitDateFormatRefUpdated ();  
    return True;
}

//%************************************************************************************************
//%
//%   Implementation of class ScheduleSpecificPropertiesCallback
//%
//%************************************************************************************************
ScheduleSpecificPropertiesCallback::ScheduleSpecificPropertiesCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
ScheduleSpecificPropertiesCallback::~ScheduleSpecificPropertiesCallback()
{
}

BOOLEAN  ScheduleSpecificPropertiesCallback::Update()
{
    _garfunkelDB->emitScheduleSpecificPropertiesUpdated (); 
    return True;
}

//%************************************************************************************************
//%
//%   Implementation of class ProductSlotCallback
//%
//%************************************************************************************************
ProductSlotCallback::ProductSlotCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
ProductSlotCallback::~ProductSlotCallback()
{
}

BOOLEAN  ProductSlotCallback::Update()
{
    _garfunkelDB->emitProductSlotUpdated (); 
    return True;
}


//%************************************************************************************************
//%
//%   Implementation of class ProductInfoCallback
//%
//%************************************************************************************************
ProductInfoCallback::ProductInfoCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
ProductInfoCallback::~ProductInfoCallback()
{
}

BOOLEAN  ProductInfoCallback::Update()
{
    _garfunkelDB->emitProductInfoUpdated ();
    //% Also Emit Nozzle Type Refence Updated Signal
    _garfunkelDB->emitNozzleTypeRefUpdated ();  
    return True;
}


//%************************************************************************************************
//%
//%   Implementation of class SBlockProductPropertiesCallback
//%
//%************************************************************************************************
SBlockProductPropertiesCallback::SBlockProductPropertiesCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
SBlockProductPropertiesCallback::~SBlockProductPropertiesCallback()
{
}

BOOLEAN  SBlockProductPropertiesCallback::Update()
{
    _garfunkelDB->emitSBlockProductPropertiesUpdated (); 
    return True;
}

//%************************************************************************************************
//%
//%   Implementation of class PBlockProductPropertiesCallback
//%
//%************************************************************************************************
PBlockProductPropertiesCallback::PBlockProductPropertiesCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
PBlockProductPropertiesCallback::~PBlockProductPropertiesCallback()
{
}

BOOLEAN  PBlockProductPropertiesCallback::Update()
{
    _garfunkelDB->emitPBlockProductPropertiesUpdated (); 
    return True;
}

//%************************************************************************************************
//%
//%   Implementation of class OCapsuleProductPropertiesCallback
//%
//%************************************************************************************************
OCapsuleProductPropertiesCallback::OCapsuleProductPropertiesCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
OCapsuleProductPropertiesCallback::~OCapsuleProductPropertiesCallback()
{
}

BOOLEAN  OCapsuleProductPropertiesCallback::Update()
{
    _garfunkelDB->emitOCapsuleProductPropertiesUpdated (); 
    return True;
}

//%************************************************************************************************
//%
//%   Implementation of class ProductConcentrationForSprayCallback
//%
//%************************************************************************************************
ProductConcentrationForSprayCallback::ProductConcentrationForSprayCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
ProductConcentrationForSprayCallback::~ProductConcentrationForSprayCallback()
{
}

BOOLEAN  ProductConcentrationForSprayCallback::Update()
{
    _garfunkelDB->emitProductConcentrationForSprayUpdated (); 
    return True;
}

//%************************************************************************************************
//%
//%   Implementation of class ProductMapCallback
//%
//%************************************************************************************************
ProductMapCallback::ProductMapCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
ProductMapCallback::~ProductMapCallback()
{
}

BOOLEAN  ProductMapCallback::Update()
{
    _garfunkelDB->emitProductMapUpdated (); 
    return True;
}

//%************************************************************************************************
//%
//%   Implementation of class SprayLookUpTableCallback
//%
//%************************************************************************************************
SprayLookUpTableCallback::SprayLookUpTableCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
SprayLookUpTableCallback::~SprayLookUpTableCallback()
{
}

BOOLEAN  SprayLookUpTableCallback::Update()
{
    _garfunkelDB->emitSprayLookUpTableUpdated (); 
    return True;
}

//%************************************************************************************************
//%
//%   Implementation of class SystemDataCallback
//%
//%************************************************************************************************
SystemDataCallback::SystemDataCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
SystemDataCallback::~SystemDataCallback()
{
}

BOOLEAN  SystemDataCallback::Update()
{
    
    _garfunkelDB->emitSystemDataUpdated ();
    // Emit a signal indicating Diadgnostic info has changed
    _garfunkelDB->emitDiagnosticsUpdated ();
    // Emit a signal indicating EventDataLog info has changed
    _garfunkelDB->emitEventDataLogUpdated ();

    return True;
}


//%************************************************************************************************
//%
//%   Implementation of class BoilerPropertiesForProductsCallback
//%
//%************************************************************************************************
BoilerPropertiesForProductsCallback::BoilerPropertiesForProductsCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
BoilerPropertiesForProductsCallback::~BoilerPropertiesForProductsCallback()
{
}

BOOLEAN  BoilerPropertiesForProductsCallback::Update()
{
    _garfunkelDB->emitBoilerPropertiesForProductUpdated (); 
    return True;
}


//%************************************************************************************************
//%
//%   Implementation of class AlarmsCallback
//%
//%************************************************************************************************
AlarmsCallback::AlarmsCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
AlarmsCallback::~AlarmsCallback()
{
}

BOOLEAN  AlarmsCallback::Update()
{
    _garfunkelDB->emitAlarmDataUpdated (); 
    return True;
}


//%************************************************************************************************
//%
//%   Implementation of class RegionSpecificAlarmPropertiesCallback
//%
//%************************************************************************************************
RegionSpecificAlarmPropertiesCallback::RegionSpecificAlarmPropertiesCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
RegionSpecificAlarmPropertiesCallback::~RegionSpecificAlarmPropertiesCallback()
{
}

BOOLEAN  RegionSpecificAlarmPropertiesCallback::Update()
{
    _garfunkelDB->emitRegionSpecificAlarmPropertiesUpdated (); 
    return True;
}

//%************************************************************************************************
//%
//%   Implementation of class CustomerInputSignalCallback
//%
//%************************************************************************************************
CustomerInputSignalCallback::CustomerInputSignalCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
CustomerInputSignalCallback::~CustomerInputSignalCallback()
{
}

BOOLEAN  CustomerInputSignalCallback::Update()
{
    _garfunkelDB->emitCustomerInputSignalUpdated (); 
    //% Also Emit InputType Refence Updated
    _garfunkelDB->emitInputTypeRefUpdated (); 
    return True;
}

//%************************************************************************************************
//%
//%   Implementation of class RegulatoryLimitsCallback
//%
//%************************************************************************************************
RegulatoryLimitsCallback::RegulatoryLimitsCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
RegulatoryLimitsCallback::~RegulatoryLimitsCallback()
{
}

BOOLEAN  RegulatoryLimitsCallback::Update()
{
    _garfunkelDB->emitRegulatoryLimitsUpdated (); 
    return True;
}


//%************************************************************************************************
//%
//%   Implementation of class RegulatoryLimitsCallback
//%
//%************************************************************************************************
CustomerInfoCallback::CustomerInfoCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//% destructor
CustomerInfoCallback::~CustomerInfoCallback()
{
}

BOOLEAN  CustomerInfoCallback::Update()
{ 
    _garfunkelDB->emitCustomerInfoUpdated ();
    return True;
}


//%************************************************************************************************
//% 
//%  Implementation of class PasswordCallback
//%
//%************************************************************************************************
PasswordCallback::PasswordCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//%destructor
PasswordCallback::~PasswordCallback()
{
}

BOOLEAN  PasswordCallback::Update()
{
    // Emit a signal indicating password table has changed
    _garfunkelDB->emitPasswordUpdated();
    return True;
}


//%************************************************************************************************
//% 
//%  Implementation of class DBSyncStateCallback
//%
//%************************************************************************************************
DBSyncStateCallback::DBSyncStateCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//%destructor
DBSyncStateCallback::~DBSyncStateCallback()
{
}

BOOLEAN  DBSyncStateCallback::Update()
{
    _garfunkelDB->emitdbSyncEvent ();
    return True;
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%         THESE MIGHT NOT BE NEEDED
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


//%************************************************************************************************
//% 
//%  Implementation of class SystemRegionRefCallback
//%
//%************************************************************************************************
SystemRegionRefCallback::SystemRegionRefCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//%destructor
SystemRegionRefCallback::~SystemRegionRefCallback()
{
}

BOOLEAN  SystemRegionRefCallback::Update()
{
  
    _garfunkelDB->emitSystemRegionRefUpdated ();
    return True;
}



//%************************************************************************************************
//% 
//%  Implementation of class DefaultParametersCallback
//%
//%************************************************************************************************
DefaultParametersCallback::DefaultParametersCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//%destructor
DefaultParametersCallback::~DefaultParametersCallback()
{
}

BOOLEAN  DefaultParametersCallback::Update()
{
  
    _garfunkelDB->emitDefaultParametersUpdated ();
    return True;
}



//%************************************************************************************************
//% 
//%  Implementation of class LanguageRefCallback
//%
//%************************************************************************************************
LanguageRefCallback::LanguageRefCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//%destructor
LanguageRefCallback::~LanguageRefCallback()
{
}

BOOLEAN  LanguageRefCallback::Update()
{
  
    _garfunkelDB->emitLanguageRefUpdated ();
    return True;
}



//%************************************************************************************************
//% 
//%  Implementation of class ControllerDataCallback
//%
//%************************************************************************************************
ControllerDataCallback::ControllerDataCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//%destructor
ControllerDataCallback::~ControllerDataCallback()
{
}

BOOLEAN  ControllerDataCallback::Update()
{
  
    _garfunkelDB->emitControllerDataUpdated ();
    return True;
}



//%************************************************************************************************
//% 
//%  Implementation of class CondorBusinessDataCallback
//%
//%************************************************************************************************
CondorBusinessDataCallback::CondorBusinessDataCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//%destructor
CondorBusinessDataCallback::~CondorBusinessDataCallback()
{
}

BOOLEAN  CondorBusinessDataCallback::Update()
{
  
    _garfunkelDB->emitCondorBusinessDataUpdated ();
    return True;
}

//%************************************************************************************************
//% 
//%  Implementation of class SystemOpModeRefCallback
//%
//%************************************************************************************************
SystemOpModeRefCallback::SystemOpModeRefCallback(const std::string &name, GarfunkelDB *db) 
    : Callback(name), _garfunkelDB(db) 
{
}

//%destructor
SystemOpModeRefCallback::~SystemOpModeRefCallback()
{
}

BOOLEAN  SystemOpModeRefCallback::Update()
{
  
    _garfunkelDB->emitSystemOpModeUpdated ();
    return True;
}





//%*************************************************************************************************
//% 
//%  Garfunkel Constructors & Functions
//%
//%*************************************************************************************************

//% Singleton Instantiation
GarfunkelDB&  GarfunkelDB::Instance()
{
    static GarfunkelDB singleton;
    return singleton;
}

//%
//% QObject instantiation
//%
GarfunkelDB::GarfunkelDB(QObject *parent) : QObject(parent)
{

	notifyDBConnectionThreadStarted = False;
	qDebug() << "DB Obj constructor called, notifyThreadStarted=" << notifyDBConnectionThreadStarted;
	_gDBAccess.SetDBName("Garfunkel");
    _gDBAccess.SetDBUserName("db_user_admin");
    _gDBAccess.SetDBPassword("controller");
    connect();
}


//%
//% Destructor
//%
GarfunkelDB::~GarfunkelDB()
{
    _gDBNotifications.Terminate();
    ecolab::Thread::WaitUntilComplete(_gDBNotifications);

    if(_gDBAccess.DBisConnected()!=NULL)
    {
        _gDBAccess.DBDisconnect();
        qDebug() << "[DB] Database disconnected";
    }
}



//%
//%  Is GarfunkelDB Object Connected to Database?
//%
bool GarfunkelDB::isConnected()
{
    if (_gDBAccess.DBisConnected() == NULL)
    {
        return false;
    }
    else if(notifyDBConnectionThreadStarted == True)
    {
        return false;
    }

    return true;
}


//%
//% Connect the GarfunkelDB instance to the DB
//%
void GarfunkelDB::connect()
{

    //%
    //%    Attempt to create a connection with the database. Try a maxium of 5
    //%    times to connect before failing out.
    //%
    if(_gDBAccess.DBConnect(5))
    {
        qDebug() << "[DB] Database connection established.";

        //%    Register Callbacks for database notifications.
        
        registerDatabaseCallbacks ();
        notifyDBConnectionThreadStarted = False;
    }
    else if(notifyDBConnectionThreadStarted==False)
    {

        QString qdatabasename(dbname);
        qCritical() << "[DB] Error connecting to database " << qdatabasename << ". Starting monitoring thread.";

        //%
        //%    Create a callback to notify us when a connection to the database
        //%    has been established.
        //%
        boost::shared_ptr<ThreadingCallback> threadCallback(new ThreadingCallback("threadCallback", this));
        _gDBAccess.NotifyOnDBConnection(threadCallback);
        notifyDBConnectionThreadStarted = True;
        qCritical() << "[DB] Starting monitoring thread: notifyDBConnectionThreadStarted=" << notifyDBConnectionThreadStarted ;
    }
}


//%
//% executeStoredFunction Updates/Reads info from DataBase for a given stored Procedure
//% if needed by UI
//% Input [ parm1]
//% parm1: given stored function from UI e.g GetControllerData()
//% Output [ NONE]
//% Returns: data read from database
//%
ecolab::DB::DataSet GarfunkelDB::executeStoredFunction(const QString &storedFunction)
{
    ecolab::DB::DataSet dataSet;
    //% Check if we are connected first
    if(isConnected()==true)
    {
        const QString execute("SELECT * FROM " + storedFunction + ";");
        std::string str = execute.toStdString();

        qDebug() << "[DB] executing" << execute;

        if(!_gDBAccess.DBExecuteStored(str, dataSet))
        {
            qCritical() << "[DB] ERROR executing stored function.." << execute;
        }
    }
    else
    {
        qCritical() << "[DB] ERROR no connection to database..";
    }

    return dataSet;
}

//%
//% executeSQLCommand Updates/Reads from DataBase using given SQL statement/commands!!
//% Input[ param1]
//%       param1: String which is SQL statement/Command to execute
//% Output[ NONE]
//% Return : dataset from exxecuted SQL statement/Command
//%
ecolab::DB::DataSet GarfunkelDB::executeSQLCommand (const QString &sqlStringToExecute )
{
    ecolab::DB::DataSet dataSet;
    if(isConnected () == true)
    {    
        const std::string str = sqlStringToExecute.toStdString();

        qDebug() << "[DB] executing " << sqlStringToExecute;

        if(!_gDBAccess.DBTXNDoSQLCommand(str, dataSet))
        {
            qCritical() << "[DB] ERROR executing sql.." << sqlStringToExecute;
        }

    }
    else
    {

        qCritical() << "[DB] ERROR no connection to database..";
    }

    return dataSet;

}


//%
//% value: simple function to perform Type conversion and make sure 
//%        Data type from Database is true QML/Qt Type
//%

QVariant GarfunkelDB::value(ecolab::DB::DataRow rowData, const QString &colName, ReturnTypeT returnAs)
{
    QVariant returnValue;
    boost::shared_ptr<ecolab::DB::IColumnData> colData;
    std::string sColName = colName.toStdString();

    try {
        colData = rowData.GetColumn(sColName);

        switch (returnAs) {
        case Bool:
        {
            BOOLEAN boolValue;
            colData->AsBool(boolValue);
            returnValue = boolValue;
            Q_ASSERT(returnValue.type() == QVariant::Bool); //% Debug type correctness!
            break;
        }
        case Int:
        {
            INT32 intValue;
            colData->AsInt(intValue);
            returnValue = intValue;
            Q_ASSERT(returnValue.type() == QVariant::Int);
            break;
        }
        case Double:
        {
            REAL64 realValue;
            colData->AsFloat(realValue);
            returnValue = realValue;
            Q_ASSERT(returnValue.type() == QVariant::Double);
            break;
        }
        case Float:
        {
            REAL64 realValue;
            colData->AsFloat(realValue);
            returnValue = realValue;
            Q_ASSERT(returnValue.type() == QMetaType::Float); //% Use MetaType instead! Will work?
            break;
        }
        case String:
        {
            std::string stringValue;
            colData->AsString(stringValue);
            returnValue = QString::fromUtf8(stringValue.c_str(),stringValue.size());
            Q_ASSERT(returnValue.type() == QVariant::String);
            break;
        }
        case Byte:
        {
            Q_ASSERT(false);
            break;
        }
        default:
        {
            qDebug() << "Switch error";
        }
        }
    } catch (std::exception &e) {
        qDebug() << "[GarfunkelDB] caught exception " << e.what() << " at GarfunkelDB::value() colName=" + colName + " returnAs=" + returnAs;
    }

    return returnValue;
}


//%
//% Execute/Call all DBCallbacks
//%
void GarfunkelDB::callDatabaseCallbacks()
{
    if( (_gDBNotifications.AllLoadLevelDelayedCallbacksToExecute()==True) && (getDBSyncState()==False ) ) 
    {
        _gDBNotifications.AllLoadLevelExecuteDelayedCallbacks();
    }
}


//%
//% Reset DB state by calling the 
//% SetDBSyncState(stateToChange boolean, Operator character(8)) 
//% function from the DB.
//% Input[NONE],
//% Output[dataVal], dataVal: integer denoting DBSyncState 
//% Return[NONE]
//%
void GarfunkelDB::resetDbSyncState()
{
    ecolab::DB::DataSet dataSet;
    QString storedFunction= "SetDBSyncState(false, \'ui\')";
    const QString execute(storedFunction);
     std::string str = execute.toStdString();

    qDebug() << "[DB] executing" << execute;

    dataSet= executeStoredFunction(execute);

}

//%
//% RegisterDatabaseCallbacks: 
//%                           Registers all the Callbacks
//%                           Input[ NONE], OUTPUT [ NONE], RETURN[NONE]
//%                           Called as soon as we have connection with Database.
//%
void GarfunkelDB::registerDatabaseCallbacks()
{
    _gDBNotifications.DBNotifyInit(dbname, dbuser, dbpasswd);
    std::cout << "[DBNotify] Thread started" << std::endl;

    resetDbSyncState(); //clear flag after reboot irrespective of comm server connection

    //%
    //%  Register  LocalizedStringsCallback
    //%
    boost::shared_ptr<LocalizedStringsCallback> localizedStringsCallback(new LocalizedStringsCallback("LocalizedStrings", this));
    if(_gDBNotifications.DBRegister("LocalizedStrings", localizedStringsCallback, ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] LocalizedStrings registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] LocalizedStrings registration was not successful!";
    }

    //%
    //% Register OperatingScheduleCallback
    //%
    boost::shared_ptr<OperatingScheduleCallback> operatingScheduleCallback(new OperatingScheduleCallback("OperatingSchedule", this));
    if(_gDBNotifications.DBRegister("OperatingSchedule", operatingScheduleCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] OperatingScheduleCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] OperatingScheduleCallback registration was not successful!";
    }



    //%
    //% Register ScheduleSpecificPropertiesCallback
    //%
    boost::shared_ptr<ScheduleSpecificPropertiesCallback> scheduleSpecificPropertiesCallback(new ScheduleSpecificPropertiesCallback("ScheduleSpecificProperties", this));
    if(_gDBNotifications.DBRegister("ScheduleSpecificProperties", scheduleSpecificPropertiesCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] ScheduleSpecificPropertiesCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] ScheduleSpecificPropertiesCallback registration was not successful!";
    }


    //%
    //% Register ProductSlotCallback
    //%
    boost::shared_ptr<ProductSlotCallback> productSlotCallback(new ProductSlotCallback("ProductSlot", this));
    if(_gDBNotifications.DBRegister("ProductSlot", productSlotCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] ProductSlotCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] ProductSlotCallback registration was not successful!";
    }

    //%
    //% Register ProductInfoCallback
    //%
    boost::shared_ptr<ProductInfoCallback> prodInfoCallback(new ProductInfoCallback("ProductInfo", this));
    if(_gDBNotifications.DBRegister("ProductInfo", prodInfoCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] ProductInfoCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] ProductInfoCallback registration was not successful!";
    }


    //%
    //% Register SBlockProductPropertiesCallback
    //%
    boost::shared_ptr<SBlockProductPropertiesCallback> sBlockProductPropertiesCallback(new SBlockProductPropertiesCallback("SBlockProductProperties", this));
    if(_gDBNotifications.DBRegister("SBlockProductProperties", sBlockProductPropertiesCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] SBlockProductPropertiesCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] SBlockProductPropertiesCallback registration was not successful!";
    }

    //%
    //% Register PBlockProductPropertiesCallback
    //%
    boost::shared_ptr<PBlockProductPropertiesCallback> pBlockProductPropertiesCallback(new PBlockProductPropertiesCallback("PBlockProductProperties", this));
    if(_gDBNotifications.DBRegister("PBlockProductProperties", pBlockProductPropertiesCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] PBlockProductPropertiesCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] PBlockProductPropertiesCallback registration was not successful!";
    }


    //%
    //% Register OCapsuleProductPropertiesCallback
    //%
    boost::shared_ptr<OCapsuleProductPropertiesCallback> oCapsuleProductPropertiesCallback(new OCapsuleProductPropertiesCallback("OCapsuleProductProperties", this));
    if(_gDBNotifications.DBRegister("OCapsuleProductProperties", oCapsuleProductPropertiesCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] OCapsuleProductPropertiesCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] OCapsuleProductPropertiesCallback registration was not successful!";
    }


    //%
    //% Register ProductConcentrationForSprayCallback
    //%
    boost::shared_ptr<ProductConcentrationForSprayCallback> productConcentrationForSprayCallback(new ProductConcentrationForSprayCallback("ProductConcentrationForSpray", this));
    if(_gDBNotifications.DBRegister("ProductConcentrationForSpray", productConcentrationForSprayCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] ProductConcentrationForSprayCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] ProductConcentrationForSprayCallback registration was not successful!";
    }


    //%
    //% Register ProductMapCallback
    //%
    boost::shared_ptr<ProductMapCallback> prodMapCallback(new ProductMapCallback("ProductMap", this));
    if(_gDBNotifications.DBRegister("ProductMap", prodMapCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] ProductMap registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] ProductMap registration was not successful!";
    }


    //%
    //% Register SprayLookUpTableCallback
    //%
    boost::shared_ptr<SprayLookUpTableCallback> sprayLookUpTableCallback(new SprayLookUpTableCallback("SprayLookUpTable", this));
    if(_gDBNotifications.DBRegister("SprayLookUpTable", sprayLookUpTableCallback, ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] SprayLookUpTableCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] SprayLookUpTableCallback registration was not successful!";
    }

    //%
    //% Register  SystemDataCallback
    //%
    boost::shared_ptr<SystemDataCallback> systemDataCallback(new SystemDataCallback("SystemData", this));
    if(_gDBNotifications.DBRegister("SystemData", systemDataCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] SystemData registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] SystemData registration was not successful!";
    }


    //%
    //% Register  BoilerPropertiesForProductsCallback
    //%
    boost::shared_ptr<BoilerPropertiesForProductsCallback>  boilerPropertiesForProductsCallback(new  BoilerPropertiesForProductsCallback("BoilerPropertiesForProducts", this));
    if(_gDBNotifications.DBRegister("BoilerPropertiesForProducts", boilerPropertiesForProductsCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] BolierPropertiesForProductsCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] BolierPropertiesForProductsCallback registration was not successful!";
    }

    //%
    //% Register AlarmsCallback
    //%
    boost::shared_ptr<AlarmsCallback> alarmsCallback(new AlarmsCallback("Alarms", this));
    if(_gDBNotifications.DBRegister("Alarms", alarmsCallback, ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] AlarmsCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] AlarmsCallback registration was not successful!";
    }


    //%
    //% Register  RegionSpecificAlarmPropertiesCallback
    //%
    boost::shared_ptr<RegionSpecificAlarmPropertiesCallback>  regionSpecificAlarmPropertiesCallback(new  RegionSpecificAlarmPropertiesCallback("RegionSpecificAlarmProperties", this));
    if(_gDBNotifications.DBRegister("RegionSpecificAlarmProperties", regionSpecificAlarmPropertiesCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] RegionSpecificAlarmPropertiesCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] RegionSpecificAlarmPropertiesCallback registration was not successful!";
    }


    //%
    //% Register  CustomerInputSignalCallback
    //%
    boost::shared_ptr<CustomerInputSignalCallback>  customerInputSignalCallback(new  CustomerInputSignalCallback("CustomerInputSignal", this));
    if(_gDBNotifications.DBRegister("CustomerInputSignal", customerInputSignalCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] CustomerInputSignalCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] CustomerInputSignalCallback registration was not successful!";
    }


    //%
    //% Register  RegulatoryLimitsCallback
    //%
    boost::shared_ptr<RegulatoryLimitsCallback>  regulatoryLimitsCallback(new  RegulatoryLimitsCallback("RegulatoryLimits", this));
    if(_gDBNotifications.DBRegister("RegulatoryLimits", regulatoryLimitsCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] RegulatoryLimitsCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] RegulatoryLimitsCallback registration was not successful!";
    }

    
    //%
    //% Register CustomerInfoCallback
    //%
    boost::shared_ptr<CustomerInfoCallback> customerInfoCallback(new CustomerInfoCallback("CustomerInfo", this));
    if(_gDBNotifications.DBRegister("CustomerInfo", customerInfoCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] CustomerInfoCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] CustomerInfoCallback registration was not successful!";
    }


    //%
    //% Register PasswordCallback
    //%
    boost::shared_ptr<PasswordCallback> passwordCallback(new PasswordCallback("Password", this));
    if(_gDBNotifications.DBRegister("Password", passwordCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] PasswordCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] PasswordCallback registration was not successful!";
    }


    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //%
    //%         MIGHT NOT NEED THESE
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //%
    //% Register SystemRegionRefCallback
    //%
    boost::shared_ptr<SystemRegionRefCallback> systemRegionRefCallback(new SystemRegionRefCallback("SystemRegionRef", this));
    if(_gDBNotifications.DBRegister("SystemRegionRef", systemRegionRefCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] SystemRegionRefCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] SystemRegionRefCallback registration was not successful!";
    }

    //%
    //% Register DefaultParametersCallback
    //%
    boost::shared_ptr<DefaultParametersCallback> defaultParametersCallback(new DefaultParametersCallback("DefaultParameters", this));
    if(_gDBNotifications.DBRegister("DefaultParameters", defaultParametersCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] DefaultParametersCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] DefaultParametersCallback registration was not successful!";
    }

    //%
    //% Register LanguageRefCallback
    //%
    boost::shared_ptr<LanguageRefCallback> languageRefCallback(new LanguageRefCallback("LanguageRef", this));
    if(_gDBNotifications.DBRegister("LanguageRef", languageRefCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] LanguageRefCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] LanguageRefCallback registration was not successful!";
    }

    //%
    //% Register ControllerDataCallback
    //%
    boost::shared_ptr<ControllerDataCallback> controllerDataCallback(new ControllerDataCallback("ControllerData", this));
    if(_gDBNotifications.DBRegister("ControllerData", controllerDataCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] ControllerDataCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] ControllerDataCallback registration was not successful!";
    }

    //%
    //% Register CondorBusinessDataCallback
    //%
    boost::shared_ptr<CondorBusinessDataCallback> condorBusinessDataCallback(new CondorBusinessDataCallback("CondorBusinessData", this));
    if(_gDBNotifications.DBRegister("CondorBusinessData", condorBusinessDataCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] CondorBusinessDataCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] CondorBusinessDataCallback registration was not successful!";
    }


    //%
    //% Register SystemOpModeRefCallback
    //%
    boost::shared_ptr<SystemOpModeRefCallback> systemOpModeRefCallback(new SystemOpModeRefCallback("SystemOpModeRef", this));
    if(_gDBNotifications.DBRegister("SystemOpModeRef", systemOpModeRefCallback,  ecolab::DB::eChannelLevelMedium, True))
    {
        qDebug() << "[DBNotify] SystemOpModeRefCallback registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] SystemOpModeRefCallback registration was not successful!";
    }

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


    //%
    //% Register DBSyncState Changed this should NOT be registed as delayed callback
    //%
    boost::shared_ptr<DBSyncStateCallback> dbSyncStateCallback(new DBSyncStateCallback("DBSyncState", this));
    if(_gDBNotifications.DBRegister("DBSyncState", dbSyncStateCallback, False ))
    {
        qDebug() << "[DBNotify] DBSyncState registration successful";
    }
    else
    {
        qCritical() << "[DBNotify] DBSyncState registration was not successful!";
    }

   
    //% Now that callbacks have been registered please Start the Delayed notification threads
    _gDBNotifications.Start();


}




//%************************************************************************************************************
//%
//%  
//%  Emitting Functions
//%
//%************************************************************************************************************



//% emit localizedStringsUpdated signal
void GarfunkelDB::emitLocalizedStringsUpdated ()
{
    qDebug() << "emitting GarfunkelDB::localizedStringsUpdated signal";
    emit localizedStringsUpdated ();
}

//More Emitters!
//% Emit operatingScheduleUpdated Signal
void GarfunkelDB::emitOperatingScheduleUpdated ()
{
    qDebug() << "emitting GarfunkelDB::operatingScheduleUpdated () signal";
    emit operatingScheduleUpdated ();
}

//% Emit scheduleSpecificPropertiesUpdated Signal
void GarfunkelDB::emitScheduleSpecificPropertiesUpdated ()
{
    qDebug() << "emitting GarfunkelDB::scheduleSpecificPropertiesUpdated () signal";
    emit scheduleSpecificPropertiesUpdated ();
}

//% Emit productSlotUpdated Signal
void GarfunkelDB::emitProductSlotUpdated ()
{
    qDebug() << "emitting GarfunkelDB::productSlotUpdated () signal";
    emit productSlotUpdated ();
}

//% Emit productInfoUpdated Signal
void GarfunkelDB::emitProductInfoUpdated ()
{
    qDebug() << "emitting GarfunkelDB::productInfoUpdated () signal";
    emit productInfoUpdated ();
}

//% Emit  sBlockProductPropertiesUpdated Signal
void GarfunkelDB::emitSBlockProductPropertiesUpdated ()
{
    qDebug() << "emitting GarfunkelDB::sBlockProductPropertiesUpdated () signal";
    emit sBlockProductPropertiesUpdated ();
}

//% Emit  pBlockProductPropertiesUpdated Signal
void GarfunkelDB::emitPBlockProductPropertiesUpdated ()
{
    qDebug() << "emitting GarfunkelDB::pBlockProductPropertiesUpdated () signal";
    emit pBlockProductPropertiesUpdated ();
}

//% Emit  oCapsuleProductPropertiesUpdated Signal
void GarfunkelDB::emitOCapsuleProductPropertiesUpdated ()
{
    qDebug() << "emitting GarfunkelDB::oCapsuleProductPropertiesUpdated signal";
    emit oCapsuleProductPropertiesUpdated ();
}

//% Emit  productConcentrationForSprayUpdated Signal
void GarfunkelDB::emitProductConcentrationForSprayUpdated ()
{
    qDebug() << "emitting GarfunkelDB::productConcentrationForSprayUpdated signal";
    emit productConcentrationForSprayUpdated ();
}

//% Emit  productMapUpdated Signal
void GarfunkelDB::emitProductMapUpdated ()
{
    qDebug() << "emitting GarfunkelDB::productMapUpdated signal";
    emit productMapUpdated ();
}

//% Emit  sprayLookUpTableUpdated Signal
void GarfunkelDB::emitSprayLookUpTableUpdated ()
{
    qDebug() << "emitting GarfunkelDB::sprayLookUpTableUpdated signal";
    emit sprayLookUpTableUpdated ();
}

//% Emit  systemDataUpdated Signal
void GarfunkelDB::emitSystemDataUpdated ()
{
    qDebug() << "emitting GarfunkelDB::systemDataUpdated signal";
    emit systemDataUpdated ();
}


//% Emit  boilerPropertiesForProductUpdated Signal
void GarfunkelDB::emitBoilerPropertiesForProductUpdated ()
{
    qDebug() << "emitting GarfunkelDB::boilerPropertiesForProductUpdated signal";
    emit boilerPropertiesForProductUpdated ();
}

//% Emit  alarmDataUpdated Signal
void GarfunkelDB::emitAlarmDataUpdated ()
{
    qDebug() << "emitting GarfunkelDB::alarmDataUpdated signal";
    emit alarmDataUpdated ();
}

//% Emit  regionSpecificAlarmPropertiesUpdated Signal
void GarfunkelDB::emitRegionSpecificAlarmPropertiesUpdated ()
{
    qDebug() << "emitting GarfunkelDB::regionSpecificAlarmPropertiesUpdated signal";
    emit regionSpecificAlarmPropertiesUpdated ();
}


//% Emit  customerInputSignalUpdated Signal
void GarfunkelDB::emitCustomerInputSignalUpdated ()
{
    qDebug() << "emitting GarfunkelDB::customerInputSignalUpdated signal";
    emit customerInputSignalUpdated ();
}

//% Emit  regulatoryLimitsUpdated Signal
void GarfunkelDB::emitRegulatoryLimitsUpdated ()
{
    qDebug() << "emitting GarfunkelDB::regulatoryLimitsUpdated signal";
    emit regulatoryLimitsUpdated ();
}


//% Emit  customerInfoUpdated Signal
void GarfunkelDB::emitCustomerInfoUpdated ()
{
    qDebug() << "emitting GarfunkelDB::customerInfoUpdated signal";
    emit customerInfoUpdated ();
}


//% Emit  passwordUpdated Signal
void GarfunkelDB::emitPasswordUpdated ()
{
    qDebug() << "emitting GarfunkelDB::passwordUpdated signal";
    emit passwordUpdated ();
}


//% Registered?

//% Emit  languageRefUpdated Signal
void GarfunkelDB::emitLanguageRefUpdated ()
{
    qDebug() << "emitting GarfunkelDB::languageRefUpdated signal";
    emit languageRefUpdated ();
}

//% Emit  operatingScheduleRefUpdated Signal
void GarfunkelDB::emitOperatingScheduleRefUpdated ()
{
    qDebug() << "emitting GarfunkelDB::operatingScheduleRefUpdated signal";
    emit operatingScheduleRefUpdated ();
}

//% Emit  systemRegionRefUpdated Signal
void GarfunkelDB::emitSystemRegionRefUpdated ()
{
    qDebug() << "emitting GarfunkelDB::systemRegionRefUpdated signal";
    emit systemRegionRefUpdated ();
}


//% Emit  defaultParametersUpdated Signal
void GarfunkelDB::emitDefaultParametersUpdated ()
{
    qDebug() << "emitting GarfunkelDB::defaultParametersUpdated signal";
    emit defaultParametersUpdated ();
}


//% Emit  operationalParametersUpdated Signal
void GarfunkelDB::emitOperationalParametersUpdated ()
{
    qDebug() << "emitting GarfunkelDB::operationalParametersUpdated signal";
    emit operationalParametersUpdated ();
}


//% Emit  controllerDataUpdated Signal
void GarfunkelDB::emitControllerDataUpdated ()
{
    qDebug() << "emitting GarfunkelDB::controllerDataUpdated signal";
    emit controllerDataUpdated ();
}


//% Emit  condorBusinessDataUpdated Signal
void GarfunkelDB::emitCondorBusinessDataUpdated ()
{
    qDebug() << "emitting GarfunkelDB::condorBusinessDataUpdated signal";
    emit condorBusinessDataUpdated ();
}


//% Emit  systemOpModeUpdated Signal
void GarfunkelDB::emitSystemOpModeUpdated ()
{
    qDebug() << "emitting GarfunkelDB::systemOpModeUpdated signal";
    emit systemOpModeUpdated ();
}

//% Emit  nozzleTypeRefUpdated Signal
void GarfunkelDB::emitNozzleTypeRefUpdated ()
{
    qDebug() << "emitting GarfunkelDB::nozzleTypeRefUpdated signal";
    emit nozzleTypeRefUpdated ();
}

//% Emit  inputTypeRefUpdated Signal
void GarfunkelDB::emitInputTypeRefUpdated ()
{
    qDebug() << "emitting GarfunkelDB::inputTypeRefUpdated signal";
    emit inputTypeRefUpdated ();
}

//% Emit  dateFormatRefUpdated Signal
void GarfunkelDB::emitDateFormatRefUpdated ()
{
    qDebug() << "emitting GarfunkelDB::dateFormatRefUpdated signal";
    emit dateFormatRefUpdated ();
}


//% Emit  diagnosticsUpdated Signal
void GarfunkelDB::emitDiagnosticsUpdated ()
{
    qDebug() << "emitting GarfunkelDB::diagnosticsUpdated signal";
    emit diagnosticsUpdated ();
}


//% Emit  exposedFunctionUpdated Signal
void GarfunkelDB::emitExposedFunctionUpdated ()
{
    qDebug() << "emitting GarfunkelDB::exposedFunctionUpdated signal";
    emit exposedFunctionUpdated ();
}


//% Emit  eventDataLogUpdated Signal
void GarfunkelDB::emitEventDataLogUpdated ()
{
    qDebug() << "emitting GarfunkelDB::eventDataLogUpdated signal";
    emit eventDataLogUpdated ();
}



//% Emit Updated DB Sync Event Signal
void GarfunkelDB::emitdbSyncEvent ()
{
    qDebug() << "emitting dbSyncEvent from GarfunkelDB";
    emit dbSyncEvent ();
}
//% Set/Update DB SyncState
void GarfunkelDB::updateDBSyncState (bool state)
{
     if (state !=_dbSyncStop)
        {	 
          qDebug() << "_dbSyncStop Updated to " << state;
          _dbSyncStop = state;
        } else
             {
               qDebug () <<"_dbSyncStop unchanged!!"; 
	}	  
}

//% Get DBSyncState
bool GarfunkelDB::getDBSyncState()
{
    return _dbSyncStop;
}
