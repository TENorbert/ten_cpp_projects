#ifndef  GARFUNKELDB_H
#define  GARFUNKELDB_H
//% Inherited Qt Includes 
#include <QObject>
#include <QDebug>


//% inherited Ecolab classes 
#include "DBAccess.h"
#include "ecolab.h"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%
//%     GarfunkelDB
//%     
//%     This GarfunkelDB class defines the main class  which communitcates with the DataBase   
//%     and allows Other Classes or QML extended objects to communicate with the Database
//%     Signals emitted by this class are used by the MCA/QML screens(Through Other Context Classes)
//%     to handle interaction with UI screens.
//%
//%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




class GarfunkelDB;




//%
//%% REGISTER DATABASE CALLBACKS
//%

//%
//% One time signal Condidates
/*************************************

//%% THESE ARE DEFAULTS %%%//
SystemRegionRef () 
DefaultParameters ()
SystemDefaults ()

LanguageRef ()
ControllerData ()
CondorBusinessData ()
SystemOpModeRef ()   // emitted in OperatingSchedule ()
OperatingScheduleRef () // emitted in Product Concentration spray Updates
NozzleTypeRef ()
DateFormatRef () // emitted in OperatingSchedule ()
RegionSpecificAlarmProperties () // emitted in Alarm ()
InputTypeRef ()  // emitted in  CustomerInputSignal ()
 
**************************************/


//%
//% CallBack for Localized strings Table in DB
//%
class LocalizedStringsCallback : public ecolab::DB::Callback
{   
    public:
        LocalizedStringsCallback (const std::string &callbackName, GarfunkelDB *gdb );
        virtual ~LocalizedStringsCallback ();
        virtual  BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;
};



//%
//% Callback for OperatingSchedule Table in DB
//% Also handles OperatingSchedule_Ref
//%
class OperatingScheduleCallback : public ecolab::DB::Callback
{   
    public:
        OperatingScheduleCallback (const std::string &callbackName, GarfunkelDB *gdb );
        virtual ~OperatingScheduleCallback ();
        virtual  BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;
};

//%
//% Callback for ScheduleSpecificProperties Table in DB
//%
class ScheduleSpecificPropertiesCallback : public ecolab::DB::Callback
{   
    public:
        ScheduleSpecificPropertiesCallback (const std::string &callbackName, GarfunkelDB *gdb );
        virtual ~ScheduleSpecificPropertiesCallback ();
        virtual  BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;
};


//%
//% Callback for ProductSlot Table in DB
//% Simultaneously handles NozzleType_Ref due to Primary Key
//%
class ProductSlotCallback : public ecolab::DB::Callback
{   
    public:
        ProductSlotCallback (const std::string &callbackName, GarfunkelDB *gdb );
        virtual ~ProductSlotCallback ();
        virtual  BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;
};


//%
//% Callback for Product Infomation Table in DB
//%
class ProductInfoCallback : public ecolab::DB::Callback
{   
    public:
        ProductInfoCallback (const std::string &callbackName, GarfunkelDB *gdb );
        virtual ~ProductInfoCallback ();
        virtual  BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;
};


//%
//% CallBack for SBlockProductProperties Table
//%
class SBlockProductPropertiesCallback : public ecolab::DB::Callback
{
    public:
        SBlockProductPropertiesCallback ( const std::string &callbackName, GarfunkelDB* gdb );
        virtual ~SBlockProductPropertiesCallback ();
        virtual BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;   

};

//%
//% CallBack for PBlockProductProperties Table
//%
class PBlockProductPropertiesCallback : public ecolab::DB::Callback
{
    public:
        PBlockProductPropertiesCallback ( const std::string &callbackName, GarfunkelDB* gdb );
        virtual ~PBlockProductPropertiesCallback ();
        virtual BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;   

};


//%
//% CallBack for OCapsuleProductProperties Table
//%
class OCapsuleProductPropertiesCallback : public ecolab::DB::Callback
{
    public:
        OCapsuleProductPropertiesCallback ( const std::string &callbackName, GarfunkelDB* gdb );
        virtual ~OCapsuleProductPropertiesCallback ();
        virtual BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;   

};


//%
//% Callback for ProductConcentrationForSpray in DB
//% One time signal candidate?
//%
class ProductConcentrationForSprayCallback : public ecolab::DB::Callback
{   
    public:
        ProductConcentrationForSprayCallback (const std::string &callbackName, GarfunkelDB *gdb );
        virtual ~ProductConcentrationForSprayCallback ();
        virtual  BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;
};


//%
//% CallBack for Product Mapping Table in DB 
//%
class ProductMapCallback : public ecolab::DB::Callback
{   
    public:
        ProductMapCallback (const std::string &callbackName, GarfunkelDB *gdb );
        virtual ~ProductMapCallback ();
        virtual  BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;
};


//%
//% CallBack for  SprayLookUpTable Table in DB 
//% One time signal Candidate?
//%
class SprayLookUpTableCallback : public ecolab::DB::Callback
{   
    public:
        SprayLookUpTableCallback (const std::string &callbackName, GarfunkelDB *gdb );
        virtual ~SprayLookUpTableCallback ();
        virtual  BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;
};


//%
//% CallBack for SystemData Table
//%
class SystemDataCallback : public ecolab::DB::Callback
{
    public:
        SystemDataCallback ( const std::string &callbackName, GarfunkelDB* gdb );
        virtual ~SystemDataCallback ();
        virtual BOOLEAN Update ();
    private:
    	GarfunkelDB *_garfunkelDB;   
};



//%
//% CallBack for BoilerPropertiesForProducts  Table in DB
//%
class BoilerPropertiesForProductsCallback : public ecolab::DB::Callback
{   
    public:
        BoilerPropertiesForProductsCallback (const std::string &callbackName, GarfunkelDB *gdb );
        virtual ~BoilerPropertiesForProductsCallback ();
        virtual  BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;
};


//%
//% Callback for Alarms Table in DB
//%
class AlarmsCallback : public ecolab::DB::Callback
{   
    public:
        AlarmsCallback (const std::string &callbackName, GarfunkelDB *gdb );
        virtual ~AlarmsCallback ();
        virtual  BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;
};



//%
//% Callback for Alarms Table in DB
//% One time signal emitted in AlarmsCallback?
//%
class RegionSpecificAlarmPropertiesCallback : public ecolab::DB::Callback
{   
    public:
        RegionSpecificAlarmPropertiesCallback (const std::string &callbackName, GarfunkelDB *gdb );
        virtual ~RegionSpecificAlarmPropertiesCallback ();
        virtual  BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;
};



//%
//% Callback for CustomerInputSignal Table in DB
//% 
class CustomerInputSignalCallback : public ecolab::DB::Callback
{	
	public:
		CustomerInputSignalCallback (const std::string &callbackName, GarfunkelDB *gdb );
		virtual ~CustomerInputSignalCallback ();
		virtual  BOOLEAN Update ();
	private:
		GarfunkelDB *_garfunkelDB;
};


//%
//% Callback for RegulatoryLimits Table in DB
//%
class RegulatoryLimitsCallback : public ecolab::DB::Callback
{   
    public:
        RegulatoryLimitsCallback (const std::string &callbackName, GarfunkelDB *gdb );
        virtual ~RegulatoryLimitsCallback ();
        virtual  BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;
};


//%
//% Callback for CustomerInfo Table in DB
//%
class CustomerInfoCallback : public ecolab::DB::Callback
{   
    public:
        CustomerInfoCallback (const std::string &callbackName, GarfunkelDB *gdb );
        virtual ~CustomerInfoCallback ();
        virtual  BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;
};


//%
//% Callback for Password Table in DB
//%
class PasswordCallback : public ecolab::DB::Callback
{   
    public:
        PasswordCallback (const std::string &callbackName, GarfunkelDB *gdb );
        virtual ~PasswordCallback ();
        virtual  BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;
};


//%
//% Callback for DBSyncState  Table in DB
//%
class DBSyncStateCallback : public ecolab::DB::Callback
{
    public:
    DBSyncStateCallback(const std::string &name, GarfunkelDB *gdb);
        virtual ~DBSyncStateCallback();
        virtual BOOLEAN Update();
    private:
        GarfunkelDB *_garfunkelDB;
};





//*************************************************************************//
//%%      UNNECCESARY CALL BACKS ?
//*************************************************************************//

//%
//% Callback for SystemRegionRef Table in DB
//% 
class SystemRegionRefCallback : public ecolab::DB::Callback
{
    public:
        SystemRegionRefCallback ( const std::string &callbackName, GarfunkelDB* gdb );
        virtual ~SystemRegionRefCallback ();
        virtual BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;   
};


//%
//% Callback for DefaultParameters Table in DB
//% 
class DefaultParametersCallback : public ecolab::DB::Callback
{
    public:
        DefaultParametersCallback ( const std::string &callbackName, GarfunkelDB* gdb );
        virtual ~DefaultParametersCallback ();
        virtual BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;   
};


//%
//% Callback for Language_Ref Table in DB
//% 
class LanguageRefCallback : public ecolab::DB::Callback
{
    public:
        LanguageRefCallback ( const std::string &callbackName, GarfunkelDB* gdb );
        virtual ~LanguageRefCallback ();
        virtual BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;   
};



//%
//% Does not Change Often; need only Signal?
//% CallBack for ControllerData Table in DB 
class ControllerDataCallback : public ecolab::DB::Callback
{
    public:
        ControllerDataCallback ( const std::string &callbackName, GarfunkelDB* gdb );
        virtual ~ControllerDataCallback ();
        virtual BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;   
};


//% Does not Change Often; need only Signal?
//% CallBack for CondorBusinessData Table
//%
class CondorBusinessDataCallback : public ecolab::DB::Callback
{
    public:
        CondorBusinessDataCallback ( const std::string &callbackName, GarfunkelDB* gdb );
        virtual ~CondorBusinessDataCallback ();
        virtual BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;   
      
};


//%CallBack for SystemOpModeRef
//% Does it get Updated often? One time Signal?
//%
class SystemOpModeRefCallback : public ecolab::DB::Callback
{   
    public:
        SystemOpModeRefCallback (const std::string &callbackName, GarfunkelDB *gdb );
        virtual ~SystemOpModeRefCallback ();
        virtual  BOOLEAN Update ();
    private:
        GarfunkelDB *_garfunkelDB;
};

//***************************************************************************************//






//% Now GarfunkelDB Class
class GarfunkelDB : public QObject {
    
    Q_OBJECT
   //% If we wanted to go the rout of accessing DB directly from QML with SQL
   //% Q_PROPERTY (QString  coonect READ getconnect WRITE setConnect NOTIFY connectChanged ) 
      

public:
	//%Create Singleton of GarfunkelDB Object
	static GarfunkelDB& Instance (); 
	virtual ~GarfunkelDB ( );

    //%
    //%      MUST DEFINE  SIGNAL EMITTERS
    //%

    //%Methods to emit Signal after Updated
    //%Database Triggered, so emit Signal to Notify MCA/OTHERS

    //% LocalizedString Change Signal
    void emitLocalizedStringsUpdated ();
    //% OperatingSchedule Change Signal
    void emitOperatingScheduleUpdated ();
    //% SheduleSpecificProperties Changed Signal
    void emitScheduleSpecificPropertiesUpdated ();
    //%  ProductSlot Change Signal
    void emitProductSlotUpdated ();
    //% ProductInfo Change Signal
    void emitProductInfoUpdated ();
    //% SBlockProductProperties Change Signal
    void emitSBlockProductPropertiesUpdated (); 
    //% PBlockProductProperties Change Signal
    void emitPBlockProductPropertiesUpdated ();
    //% OcapsuleProductProperties Change Signal
    void emitOCapsuleProductPropertiesUpdated (); 
    //% ProductConcentrationForSpray Change Signal
    void emitProductConcentrationForSprayUpdated ();
    //% ProductMap Change Signal
    void emitProductMapUpdated ();
    //% SprayLookUpTable Change Signal
    void emitSprayLookUpTableUpdated ();  //% Can Spray Look Up Table entries Change?
    //% SystemData Change Signal
    void emitSystemDataUpdated ();
    //% BolierPropertiesForProducts Change Signal
    void emitBoilerPropertiesForProductUpdated (); //% Think Boiler PPty can Change freqly? 
    //% Alarm Change Signal
    void emitAlarmDataUpdated ();
    //% RegionSpecificAlarmProperties Change Siganl
    void emitRegionSpecificAlarmPropertiesUpdated ();
    //% CustomerInputSignal Change Signal
    void emitCustomerInputSignalUpdated ();
    //% RegulatoryLimits Change Signal
    void emitRegulatoryLimitsUpdated ();
    //% Customer Info Change Signal
    void emitCustomerInfoUpdated ();
    //% PasswordUpdate Change Signal 
    void emitPasswordUpdated ();
    //%  DBSyncState Change Signal   
    void updateDBSyncState (bool state);
    bool getDBSyncState ();
    void emitdbSyncEvent ();


    //% How about us... when do we get the green light? Never?
    void emitLanguageRefUpdated ();
    void emitOperatingScheduleRefUpdated ();
    void emitSystemRegionRefUpdated ();
    void emitDefaultParametersUpdated();
    void emitOperationalParametersUpdated ();   
    void emitControllerDataUpdated ();
    void emitCondorBusinessDataUpdated ();
    void emitSystemOpModeUpdated ();
    void emitNozzleTypeRefUpdated ();

    //% Signal that Input Type Ref Table Updated 
    void emitInputTypeRefUpdated (); // really?
    //% Signal for dateFormat updated
    void emitDateFormatRefUpdated (); // emitted in OperatingSchedule ()
    //% Signal that Diagnostics Table Updated
    void emitDiagnosticsUpdated ();
    

    void emitExposedFunctionUpdated (); //% why did I put this here?
    void emitEventDataLogUpdated ();
    
    //
    //% How the GarfunkleDB Object connects to the database
    //
    void connect ();
    //
    // % Check if connection
    //
    bool isConnected ();
    //
    //% Execute Stored functions from Gadfunkel DataTables: GarfunkelStoredFuncs.sql
    //
    ecolab::DB::DataSet executeStoredFunction (const QString &storedFunction);
    //
    //% Execute SQL Statement directly
    //
    ecolab::DB::DataSet executeSQLCommand (const QString &sqlStringToExecute);
    //
    //% enum for QVariant Types return value of database
    //
    typedef enum
    {
      Bool,
      Int,
      Double,
      Float,
      String,
      Byte, 	
    } ReturnTypeT;
    
    //
    //% Make Sure Return type from database is always legit
    //
    QVariant value (ecolab::DB::DataRow rowData, const QString &colName, ReturnTypeT returnAs);

    //
    //%% call DatabaseCallbacks
    //
    void callDatabaseCallbacks ();

    //
    //% Signals Database emits if a Table information is Updated
    //% Other Classes should receive these SIGNALS through SLOTS
signals:
    //%
    //%% THE SIGNALS
    //%
    //% Signal that Localization Strings & Data Table Updated
    void localizedStringsUpdated ();
    //% Signal that Operating Schedule Table Updated
    void operatingScheduleUpdated ();
    //% Signal that Schedule specific Ppty Table Updated
    void scheduleSpecificPropertiesUpdated ();
    //% Signal that Product Slot Table Updated
    void productSlotUpdated ();
    //% Signal that Product Information Table Updated
    void productInfoUpdated ();
    //% Signal that SBlockProduct Property(Ppty) Table Updated
    void sBlockProductPropertiesUpdated ();
    //% Signal that PBlockProduct Property(Ppty) Table Updated
    void pBlockProductPropertiesUpdated ();
    //% Signal that OCapsuleProduct Property(Ppty) Table Updated
    void oCapsuleProductPropertiesUpdated ();
    //% Signal that Product Concentration For Spray Table Updated
    void productConcentrationForSprayUpdated ();
    //% Signal that Product Mapping Information Table Updated
    void productMapUpdated ();
    //% If Ever SprayLookUp Table entry change( Signal needed? b/c currently all its info is updated elsewhere! so?)
    void sprayLookUpTableUpdated ();  // Can Spray Look Up Table entries Change?
    //% Signal that SystemData table Updated
    void systemDataUpdated ();
    //% Signal that Boiler Ppty for Products Table Updated ( will it ever changed?)
    void boilerPropertiesForProductUpdated ();
    //% Signal that Alarm Data and Priority Table Updated
    void alarmDataUpdated ();
    //% Signal that Region Specific Alarm Ppty Table Updated 
    void regionSpecificAlarmPropertiesUpdated ();
    //% Signal that CustomerInput Signal Table Updated
    void customerInputSignalUpdated ();
    //% Signal that Regulatory Limit Information Table Updated
    void regulatoryLimitsUpdated ();
    //% Signal that Customer Information Table Updated
    void customerInfoUpdated ();
    //% Signal that Password  Table Updated
    void passwordUpdated ();
    //% Signal of Database Synchronisation Event
    void dbSyncEvent ();
    
    
    //% Signal that LanguageRef Table Updated
    void languageRefUpdated ();
    //% Signal that Operating Schedule Ref( Schedule Name?) Table Updated
    void operatingScheduleRefUpdated ();
    //% Signal that Region Data Table Updated
    void systemRegionRefUpdated ();
    //% Signal that  Default Parameters Table Updated
    void defaultParametersUpdated ();
    //% Signal that Operational Parameters Table Updated
    void operationalParametersUpdated ();
    //% Signal that ControllerData Updated
    void controllerDataUpdated ();
    //% Signal that Condor Business Data  Table Updated
    void condorBusinessDataUpdated ();
    //% Signal that System Operation Mode Table Updated( same as previous?)
    void systemOpModeUpdated ();
    //% Signal that Nozzle Type Ref Table Updated
    void nozzleTypeRefUpdated ();
    //% Signal that Input Type Ref Table Updated 
    void inputTypeRefUpdated (); // really?
    //% Signal for dateFormat updated
    void dateFormatRefUpdated (); // emitted in OperatingSchedule ()
   
    
    //% Signal that Exposed Function Table Updated
    void exposedFunctionUpdated ();
    //% Signal that EventDatalog Table Updated
    void eventDataLogUpdated (); 
    
    //% Signal that Diagnostics Table Updated
    void diagnosticsUpdated ();
     
private: 
	GarfunkelDB (QObject *parent = 0 );
	static const char *hostdb ;
	static const char *dbname ;
	static const char *dbuser ;
	static const char *dbpasswd;

	static bool _dbSyncStop;

    
	BOOLEAN  notifyDBConnectionThreadStarted;
    	ecolab::DB::DBAccess _gDBAccess;                 //% Object Used to access Database .
    	ecolab::DB::DBNotify2 _gDBNotifications;    //% Object used to (delay) notify Database .
    	//
   	//%    Method to register database callbacks.
    	//
    	void registerDatabaseCallbacks ();
    	void resetDbSyncState ();

    	//
    	//% Threading Callback: 
    	//% To register all other Callbacks in GarfunkelDB Object
    	// 
   class ThreadingCallback : public ecolab::DB::Callback
   {
    public:
    	//
    	//% ThreadingCallback Constructor
    	//% Input[param1, param2]
    	//% param1: Callback's name
    	//% param2: Pointer to GarfunkelDB class

    	//% OutPut[None]
    	//% 
        ThreadingCallback (const std::string &name, GarfunkelDB *gDB ) : Callback (name), _garfunkelDB (gDB) {};

        //% ThreadCallback Destructor: Input[NONE], Output[NONE]
        virtual ~ThreadingCallback () {};
        //% Database Update Callback method: RETURN[bool], bool indicate update method succeeded
        virtual BOOLEAN Update ()
        {
          qDebug () << "GarfunkelDB::ThreadingCallback::Update ()";
          //% Now connect to the database
          _garfunkelDB->connect ();
          return True;
        }

    private: 
       GarfunkelDB *_garfunkelDB;   //% Pointer to GarfunkelDB Object.    
   };       
};

#endif // GARFUNKELDB_H 
