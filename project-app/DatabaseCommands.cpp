#include "GarfunkelData.h"
#include "DBAccess.h"
#include "DatabaseCallbacks.h"
#include "DatabaseCommands.h"

Garfunkel::DatabaseCommands::DatabaseCommands(const std::string & dbName, const std::string & dbUser, const std::string & dbPass) : \
    _dbName(dbName), _dbUser(dbUser), _dbPass(dbPass), _database(), _callbacksSetup(False)
{
	EstablishDatabaseConnection();
}

/*!
    \brief        

    \param[in]    None

    \param[out]    None

    \return        None

    \throw        None
*/
Garfunkel::DatabaseCommands::~DatabaseCommands(void)
{
    /* Empty */
}

BOOLEAN Garfunkel::DatabaseCommands::EstablishDatabaseConnection (void)
{
    const UINT32            retryAttempts = 10;
    BOOLEAN                 connectionEstablished = False;
    _database.SetDBName(_dbName);
    _database.SetDBUserName(_dbUser);
    _database.SetDBPassword(_dbPass);

    connectionEstablished = _database.DBConnect(retryAttempts);
    if(True == connectionEstablished)
    {
        /* Connection established! */
        std::cout << "[DatabaseCommands] Database connection established." << std::endl;
        
        if(False == CallBacksSetup())
        {
            InitializeCallback();
        }

    }
    else
    {

    	Garfunkel::GarfunkelData & AqData = Garfunkel::GarfunkelData::Instance();
        //since we dont have db up, we will init all data from flat files/db (if available at that instant) and we dont want this process to be interrupted by db notify thread, we are taking dbsyncinprogess lock. This lock will be released once init of all data is done from flat files.
    	//Once this init is done, the lock is released and the db notify thread is expected to take this lock, stop polling of boards and do a safe reinitilization
        AqData._dBSyncInProgressLock.Lock(); //lock mutex and set flag
        AqData._dBSyncInProgress.Set(True);

        std::cout << "registering threading callback" << std::endl;
        // If there is not a connection to the database create one and and make sure the system get registered
        boost::shared_ptr<Garfunkel::ThreadingCallback> threadCallback(new Garfunkel::ThreadingCallback("threadCallback"));

        // Start monitoring thread
        BOOLEAN ret = _database.NotifyOnDBConnection(threadCallback);
        std::cout << "registering threading callback...done, ret="<<ret << std::endl;
    }
    
    return connectionEstablished;
}

BOOLEAN Garfunkel::DatabaseCommands::DBConnectionAvailable()
{
    return (NULL != _database.DBisConnected()) ? True : False;
}

void Garfunkel::DatabaseCommands::InitializeCallback()
{    
    BOOLEAN     systemData = False, machineData = False, formData = False;
    BOOLEAN     machinePumpData = False, productMapData = False, prodData=False, pumpData=False, lStringsData=False, pulseData=False, dispPocketData=False;
    BOOLEAN     ret = False;
    if(False == CallBacksSetup())
    {

    	ret = _databaseNotify.DBNotifyInit("Garfunkel", "db_controller","controller");
        std::cout<<"dbname="<<_dbName<<"  dbuser="<<_dbUser<<" dbPass="<<_dbPass<<std::endl;
        if(ret)
        {
#if 0
	TODO Unocmment thsi Shilpa

        	BOOLEAN pMapping = False;
            BOOLEAN systemData = False;
            BOOLEAN nAlarmSettings = False;
            BOOLEAN spSc = False;
            BOOLEAN opSc = False;
            BOOLEAN nCustomerInfo = False;
            BOOLEAN oCapsule = False, sBlock = False, hBlock = False, bProperties = False;
            BOOLEAN pSlot = False;
            BOOLEAN ret = False;


            if(False == CallBacksSetup())
            {
                ret = _databaseNotify.DBNotifyInit("Garfunkel", "db_controller", "controller");
                if(ret)
                {
                    std::cout << "[DBNotify] Database callback notification thread started: RegisterDatabaseCallbacks()" << std::endl;

                    if(False == systemData)
                    {
                    	boost::shared_ptr< Garfunkel::SystemDataCallback>              sCallback(new  Garfunkel::SystemDataCallback("SystemDataCallback"), this);
                    	if(_databaseNotify.DBRegister("SystemData", sCallback, ecolab::DB::eChannelLevelLarge, True))  //large - update system & machine context, configure all msi, configure all fbox (loading formula info)
                    	{
                    		systemData = True;
                    		std::cout << "[DBNotify] SystemData registration successful" << std::endl;
                    	}
                    	else
                    	{
                    		std::cout << " [DBNotify] SystemData Registration was not successful!" << std::endl;
                    	}
                    }

                    // Same callback they will affect each other.
                    if(False == opSc)
                    {
                        // Notification for WaterBodyValues
                        boost::shared_ptr<Garfunkel::OperatingScheduleCallback> opScCallback(new Garfunkel::OperatingScheduleCallBack("OperatingScheduleCallBack", this));
                        if(_databaseNotify.DBRegister("OperatingSchedule", opScCallback, ecolab::DB::eChannelLevelMedium, True))
                        {
                            opSc = True;
                            std::cout << "[DBNotify] OperatingSchedule registration successful" << std::endl;
                        }
                        else
                        {
                            std::cout << "[DBNotify] OperatingSchedule Registration was not successful!" << std::endl;
                        }
                    }

                    if(False == spSc)
                    {
                        // Notification for WaterBodyControl
                        boost::shared_ptr<Garfunkel::ScheduleSpecificPropertiesCallBack> scSpCallback(new Garfunkel::ScheduleSpecificPropertiesCallBack("ScheduleSpecificPropertiesCallBack", this));
                        if(_databaseNotify.DBRegister("ScheduleSpecificProperties", scSpCallback, ecolab::DB::eChannelLevelMedium, True))
                        {
                            spSc = True;
                            std::cout << "[DBNotify] ScheduleSpecificProperties registration successful" << std::endl;
                        }
                        else
                        {
                            std::cout << "[DBNotify] ScheduleSpecificProperties Registration was not successful!" << std::endl;
                        }
                    }

                    if(False == bProperties)
                    {
                        // Notification for ProductType
                        boost::shared_ptr<Garfunkel::BoilerPropertiesForProductsCallback> bpCallback(new Garfunkel::BoilerPropertiesForProductsCallback("BoilerPropertiesForProducts", this));
                        if(_databaseNotify.DBRegister("BoilerPropertiesForProducts", bpCallback, ecolab::DB::eChannelLevelMedium, True))
                        {
                        	bProperties = True;
                            std::cout << "[DBNotify] BoilerPropertiesForProducts registration successful" << std::endl;
                        }
                        else
                        {
                            std::cout << "[DBNotify] BoilerPropertiesForProducts Registration was not successful!" << std::endl;
                        }
                    }


                    if(False == pMapping)
                    {
                        // Notification for ProductType
                        boost::shared_ptr<Garfunkel::ProductMappingCallback> ptCallback(new Garfunkel::ProductMappingCallback("ProductMappingCallback", this));
                        if(_databaseNotify.DBRegister("ProductMapping", ptCallback, ecolab::DB::eChannelLevelMedium, True))
                        {
                            pMapping = True;
                            std::cout << "[DBNotify] ProductMapping registration successful" << std::endl;
                        }
                        else
                        {
                            std::cout << "[DBNotify] ProductMapping Registration was not successful!" << std::endl;
                        }
                    }

                    if(False == pSlot)
                    {
                        // Notification for ProductType
                        boost::shared_ptr<Garfunkel::ProductSlotCallback> psCallback(new Garfunkel::ProductSlotCallback("ProductSlotCallback", this));
                        if(_databaseNotify.DBRegister("ProductSlot", psCallback, ecolab::DB::eChannelLevelMedium, True))
                        {
                            pSlot = True;
                            std::cout << "[DBNotify] ProductSlot registration successful" << std::endl;
                        }
                        else
                        {
                            std::cout << "[DBNotify] ProductSlot Registration was not successful!" << std::endl;
                        }
                    }

                    if(False == sBlock)
                    {
                        // Notification for ProductType
                        boost::shared_ptr<Garfunkel::SBlockProductPropertiesCallback> sbCallback(new Garfunkel::SBlockProductPropertiesCallback("SBlockProductPropertiesCallback", this));
                        if(_databaseNotify.DBRegister("SBlockProductProperties", sbCallback, ecolab::DB::eChannelLevelMedium, True))
                        {
                        	sBlock = True;
                            std::cout << "[DBNotify] SBlockProductProperties registration successful" << std::endl;
                        }
                        else
                        {
                            std::cout << "[DBNotify] SBlockProductProperties Registration was not successful!" << std::endl;
                        }
                    }

                    if(False == hBlock)
                    {
                        // Notification for ProductType
                        boost::shared_ptr<Garfunkel::HBlockProductPropertiesCallback> hbCallback(new Garfunkel::HBlockProductPropertiesCallback("PBlockProductPropertiesCallback", this));
                        if(_databaseNotify.DBRegister("PBlockProductProperties", sbCallback, ecolab::DB::eChannelLevelMedium, True))
                        {
                        	hBlock = True;
                            std::cout << "[DBNotify] PBlockProductProperties registration successful" << std::endl;
                        }
                        else
                        {
                            std::cout << "[DBNotify] PBlockProductProperties Registration was not successful!" << std::endl;
                        }
                    }


                    if(False == oCapsule)
                    {
                        // Notification for ProductType
                        boost::shared_ptr<Garfunkel::OCapsuleProductPropertiesCallback> ocCallback(new Garfunkel::OCapsuleProductPropertiesCallback("OCapsuleProductPropertiesCallback", this));
                        if(_databaseNotify.DBRegister("OCapsuleProductProperties", sbCallback, ecolab::DB::eChannelLevelMedium, True))
                        {
                        	oCapsule = True;
                            std::cout << "[DBNotify] OCapsuleProductProperties registration successful" << std::endl;
                        }
                        else
                        {
                            std::cout << "[DBNotify] OCapsuleProductProperties Registration was not successful!" << std::endl;
                        }
                    }

                    if(False == nAlarmSettings)
                    {
                        // Notification for AlarmSettings
                        boost::shared_ptr<Garfunkel::AlarmSettingsCallback> asCallback(new Garfunkel::AlarmSettingsCallback("AlarmSettingsCallback", this));
                        if(_databaseNotify.DBRegister("Alarm", asCallback, ecolab::DB::eChannelLevelMedium, True))
                        {
                            nAlarmSettings = True;
                            std::cout << "[DBNotify] Alarm registration successful" << std::endl;
                        }
                        else
                        {
                            std::cout << "[DBNotify] Alarm Registration was not successful!" << std::endl;
                        }
                    }


                    if(False == nCustomerInfo)
                    {
                        // Notification for CustomerInputSignalCallback
                        boost::shared_ptr<Garfunkel::CustomerInputSignalCallback> ciCallback(new Garfunkel::CustomerInputSignalCallback("CustomerInputSignalCallback", this));
                        if(_databaseNotify.DBRegister("CustomerInputSignal", ciCallback, ecolab::DB::eChannelLevelMedium, True))
                        {
                            nCustomerInfo = True;
                            std::cout << "[DBNotify] CustomerInputSignalCallback registration successful" << std::endl;
                        }
                        else
                        {
                            std::cout << "[DBNotify] CustomerInputSignalCallback Registration was not successful!" << std::endl;
                        }
                    }


                    _callbacksSetup = (systemData && nAlarmSettings && spSc && opSc && pMapping&&pSlot && nCustomerInfo && oCapsule && sBlock &&  hBlock && bProperties) ? True : False;
#endif
        	_databaseNotify.Start(ecolab::Thread::JOINED, ecolab::Thread::MEDIUM_PRIORITY, 128 * 1024);
        }
    }
}


BOOLEAN Garfunkel::DatabaseCommands::DelayedCallbacksPresent()
{

	//return (_databaseNotify.AllLoadLevelNumberOfCallbacksToExecute() > 0) ? True : False;
	return _databaseNotify.AllLoadLevelDelayedCallbacksToExecute();

}
BOOLEAN Garfunkel::DatabaseCommands::ExecuteDelayedCallbacksNow()
{
	//return _databaseNotify.ExecuteDelayedCallbacks();
	//return _databaseNotify.ExecuteLimitedCallbacks(MAX_DB_DELAYED_CALLS_TO_EXECUTE);
#if 1

	int numofDelayedExecute = 0;
	int numofLGDelayedPresent = 0, numofLGDelayedExecute=0;
	int numofMDDelayedPresent = 0, numofMDDelayedExecute = 0;
	int numofSMDelayedPresent = 0, numofSMDelayedExecute = 0;

	if(_databaseNotify.LargeLoadLevelDelayedCallbacksToExecute())
	{
		//large load notification preset
		std::cout << "ExecuteDelayedCallbacksNow: Executing Large DB Callbacks"<< std::endl;
		if((numofLGDelayedPresent = _databaseNotify.LargeLoadLevelNumberOfCallbacksToExecute() ) < GARFUNKEL_LARGE_LOAD_DB_CB)
		{
			_databaseNotify.LargeLoadLevelExecuteLimitedCallbacks(GARFUNKEL_LARGE_LOAD_DB_CB); //execute only max for large db
			numofLGDelayedExecute = GARFUNKEL_LARGE_LOAD_DB_CB;
		}
		else
		{
			_databaseNotify.LargeLoadLevelExecuteDelayedCallbacks(); //execute all large load
			numofLGDelayedExecute = numofLGDelayedPresent;
		}
		numofDelayedExecute += numofLGDelayedExecute;
		std::cout << "ExecuteDelayedCallbacksNow: Available= "<<numofLGDelayedPresent<<" Executed Large DB Callbacks="<<numofLGDelayedExecute<< std::endl;
	}

	if(_databaseNotify.MediumLoadLevelDelayedCallbacksToExecute()&&numofLGDelayedExecute< GARFUNKEL_LARGE_LOAD_DB_CB)
	{
		//medium load notification preset
		std::cout << "ExecuteDelayedCallbacksNow: Executing Medium DB Callbacks"<< std::endl;
		if((numofMDDelayedPresent = _databaseNotify.MediumLoadLevelNumberOfCallbacksToExecute()) > GARFUNKEL_MEDIUM_LOAD_DB_CB)
		{
			_databaseNotify.MediumLoadLevelExecuteLimitedCallbacks(GARFUNKEL_MEDIUM_LOAD_DB_CB); //execute only max for large db
			numofMDDelayedExecute = GARFUNKEL_MEDIUM_LOAD_DB_CB;
		}
		else
		{
			_databaseNotify.MediumLoadLevelExecuteDelayedCallbacks(); //execute all medium load
			numofMDDelayedExecute = numofMDDelayedPresent;
		}
		numofDelayedExecute += numofMDDelayedExecute;
		std::cout << "ExecuteDelayedCallbacksNow: Available= "<<numofMDDelayedPresent<<"  Executed Medium DB Callbacks="<<numofMDDelayedExecute<< std::endl;
	}

	if(_databaseNotify.SmallLoadLevelDelayedCallbacksToExecute()&&numofLGDelayedExecute<GARFUNKEL_LARGE_LOAD_DB_CB)
	{
		//small load notification preset
		std::cout << "ExecuteDelayedCallbacksNow: Executing Small DB Callbacks"<< std::endl;
		if((numofSMDelayedPresent = _databaseNotify.SmallLoadLevelNumberOfCallbacksToExecute()) > GARFUNKEL_SMALL_LOAD_DB_CB)
		{
			_databaseNotify.SmallLoadLevelExecuteLimitedCallbacks(GARFUNKEL_SMALL_LOAD_DB_CB); //execute only max for large db
			numofSMDelayedExecute = GARFUNKEL_SMALL_LOAD_DB_CB;
		}
		else
		{
			_databaseNotify.SmallLoadLevelExecuteDelayedCallbacks(); //execute all medium load
			numofSMDelayedExecute = numofSMDelayedPresent;
		}
		numofDelayedExecute += numofSMDelayedExecute;
		std::cout << "ExecuteDelayedCallbacksNow: Available= "<<numofSMDelayedPresent<<"  Executed Small DB Callbacks="<<numofSMDelayedExecute<< std::endl;
	}

	std::cout << "ExecuteDelayedCallbacksNow: Executed Total DB Callbacks="<<numofDelayedExecute<< std::endl;
	return True;
#endif
}



BOOLEAN Garfunkel::DatabaseCommands::GetSystemInformation(std::string & systemInfo)
{
    BOOLEAN  retValue = False;

    systemInfo = "ERR 1";

    if(!DBConnectionAvailable())
    {
    	std::cout<<" DB not connected"<<std::endl;
    }

    if(DBConnectionAvailable())
    {
        ecolab::DB::DataSet        dataSet;
        std::string                sql = "SELECT * from GetControllerData('Garfunkel')";

        if(_database.DBExecuteStored(sql, dataSet))
        {
            if(dataSet.GetNumberOfRows() == 1)
            {
                ecolab::DB::DataRow     currentRow;
                boost::shared_ptr<ecolab::DB::IColumnData>    colData;

                currentRow = dataSet.GetRow(0);

                if(currentRow.GetNumberOfColumns() > 0)
                {
                    systemInfo.clear();
                    std::string    value;
                    colData = currentRow.GetColumn("SoftwareVersion");

                    if(colData.get() != NULL)
                    {
                        colData->AsString(value);
                        systemInfo += value;
                    }
                    retValue = True;
                }
                else
                	std::cout<<" Failed: No of columns returned="<<currentRow.GetNumberOfColumns()<<std::endl;

            }
            else
            	std::cout<<" Failed: No of rows returned="<<dataSet.GetNumberOfRows()<<std::endl;
        }
        else
        	std::cout<<" Failed to execute "<<sql<<std::endl;
    }

    return retValue;
}

