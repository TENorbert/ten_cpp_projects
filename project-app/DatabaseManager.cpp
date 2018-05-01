#include <sstream>
#include <fstream>
#include "GarfunkelData.h"
#include "DatabaseManager.h"
#include "ElapsedTime.h"
#include "GarfunkelIPC.h"



const char *Garfunkel::GarfunkelDB::dbname = "Garfunkel";
const char *Garfunkel::GarfunkelDB::dbuser = "db_controller";
const char *Garfunkel::GarfunkelDB::dbpasswd = "controller";

Garfunkel::GarfunkelDB::GarfunkelDB()
{
    /*
        Establish a connection with the database.
    */
    connect();
}

Garfunkel::GarfunkelDB::~GarfunkelDB()
{
//    if(mDBAccess.DBisConnected())
    {
        mDBAccess.DBDisconnect();
//        std::cout << "[DB] Database disconnected" << std::endl;
    }
}

BOOLEAN Garfunkel::GarfunkelDB::connect(const int retryAttempts /*=5*/)
{
    BOOLEAN     haveConnection = False;

    mDBAccess.SetDBName(dbname);
    mDBAccess.SetDBUserName(dbuser);
    mDBAccess.SetDBPassword(dbpasswd);

    /*
        Attempt to create a connection with the database. Try a maxium of 5
        times to connect before failing out.
    */
    haveConnection = mDBAccess.DBConnect(retryAttempts);
    if(True == haveConnection)
    {
        std::cout << "[DB] Database connection established." << std::endl;

    }
    else
    {
        std::cout << "[DB] Error connecting to database 'PoolSpa'." << std::endl;
    }

    return haveConnection;
}

bool    Garfunkel::GarfunkelDB::disconnect()
{
    bool        retValue = false;
    if(NULL != mDBAccess.DBisConnected())
    {
        retValue = (True == mDBAccess.DBDisconnect()) ? true : false;

        std::cout << "[Garfunkel::disconnect()] complete" << std::endl;
    }

    return retValue;
}

void Garfunkel::GarfunkelDB::executeStoredFunction(const std::string &storedFunction, ecolab::DB::DataSet & dataSet)
{
    if(NULL != mDBAccess.DBisConnected())
    {
        const std::string execute("SELECT * FROM " + storedFunction + ";");

        std::cout << "[DB] executing: " << execute << std::endl;

        if(!mDBAccess.DBExecuteStored(execute, dataSet))
        {
            std::cout << "[DB] ERROR executing stored function.." << execute << std::endl;
        }
    }
    else
    {
        std::cout << "[DB] ERROR no connection to database.." << std::endl;
    }

    return;
}

void Garfunkel::GarfunkelDB::executeSQL(const std::string &executeString, ecolab::DB::DataSet & dataSet)
{
    if(NULL != mDBAccess.DBisConnected())
    {
        std::cout << "[DB] executing " << executeString << std::endl;

        if(!mDBAccess.DBTXNDoSQLCommand(executeString, dataSet))
        {
            std::cout << "[DB] ERROR executing sql.." << executeString << std::endl;
        }
    }
    else
    {
        std::cout << "[DB] ERROR no connection to database.." << std::endl;
    }

    return;
}

void Garfunkel::GarfunkelDB::executeSQL(const std::string &executeString)
{
    if(NULL != mDBAccess.DBisConnected())
    {
        std::cout << "[DB] executing " << executeString << std::endl;

        if(!mDBAccess.DBTXNExecuteOnly(executeString))
        {
            std::cout << "[DB] ERROR executing sql.." << executeString << std::endl;
        }
    }
    else
    {
        std::cout << "[DB] ERROR no connection to database.." << std::endl;
    }

    return;
}

int Garfunkel::GarfunkelDB::valueInt(ecolab::DB::DataRow rowData, const std::string &colName)
{
    int returnValue;
    boost::shared_ptr<ecolab::DB::IColumnData> colData;

    colData = rowData.GetColumn(colName);

    INT32 intValue;
    colData->AsInt(intValue);
    returnValue = intValue;

    return returnValue;
}


std::string Garfunkel::GarfunkelDB::valueString(ecolab::DB::DataRow rowData, const std::string &colName)
{
    std::string returnValue;
    boost::shared_ptr<ecolab::DB::IColumnData> colData;

    colData = rowData.GetColumn(colName);
    colData->AsString(returnValue);

    return returnValue;
}


Garfunkel::DatabaseManager::DatabaseManager(const std::string & name) :
    Thread(name) 
{
}

Garfunkel::DatabaseManager::DatabaseManager(const DatabaseManager &     objectToCopy)
{
}

Garfunkel::DatabaseManager::~DatabaseManager()
{
}

void Garfunkel::DatabaseManager::SendMessageToUI(std::string &message)
{

	GarfunkelIPCMaster&  ipcMaster = GarfunkelIPCMaster::Instance();
    ipcMaster.SendESPCommandResponse(message);
    std::cout << "DatabaseThread : Sent message to UI: " << message << std::endl;
}


int Garfunkel::DatabaseManager::Run()
{
    int             retValue = 0;
    timespec        initial;
    timespec        Now;
    BOOLEAN ret = False;
	std::string message;
	std::stringstream strStream;

    clock_gettime(CLOCK_MONOTONIC, &initial);
    GarfunkelData &   AqData = Garfunkel::GarfunkelData::Instance();
    SystemData &   SysData = Garfunkel::SystemData::Instance();
    std::cout << "<-------------DatabaseThread thread : Started-------------->" << std::endl;

    try
    {
        while(True)
        {
            clock_gettime(CLOCK_MONOTONIC, &Now);
            
#if 0
    		if(AqData._database->DelayedCallbacksPresent()==True&&ElapsedTime(&(AqData._timeOfLastDBSync), &Now) > AQUAGATOR_DB_SYNC_TIMEOUT&&SysData.GetSystemState()!=ePrimeActive&&SysData.GetSystemState()!=eCalibrationActive&&DispensingInfo.IsDispenseActive.Get()==False&&SysData.CheckIfOptLiquidProdDispensingActivityPendingForAnyMachine()==False&&SysData.DiagnosticEnabled.Get()==False&&AqData.IsInputQueueEmpty()&&DispensingInfo.IsOutputQueueEmpty()&&DispensingInfo.IsProductQueueEmpty()&&AqData._dBSyncInProgress.Get()==False&&AqData._isMCAReady.Get()==True) //check for any delayed callbacks
    		{

    			ecolab::ScopeLock Lock(AqData._dBSyncInProgressLock); //lock mutex and set flag
    			AqData._dBSyncInProgress.Set(True);
    			std::cout << "******Datawriter....Calling delayed callbacks*****************" << std::endl;
/*    			strStream.str("");
    			strStream<<AqData._uiAddressInstance<<":SU:64:1:";
    			message.assign(strStream.str());
    			SendMessageToUI(message); //send message to UI that DB is being updated and no operations, (like prime/calib/diagnostics and activation of formula) can continue*/
    			while(AqData._alarmHandlerSleeping.Get()==False)
    			{
    				sleep(50); //wait for sometime cos Alarm handler can finish 1 round and stop checking for alarms
    				std::cout << "DatabaseThread After Sleep...waiting to Call delayed callbacks..........." << std::endl;
    			}
    			AqData.StopPollingAllBoards(); //done to make sure we don't have com alarms
    			AqData._database->ExecuteDelayedCallbacksNow();
    			AqData._dBSyncInProgress.Set(False);
    			AqData.StartPollingAllBoards(); //resume polling boards
/*    			strStream.str("");
    			strStream<<AqData._uiAddressInstance<<":SU:64:0:";
    			message.assign(strStream.str());
    			SendMessageToUI(message); //send message to UI that DB is done updating and operations can resume*/
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
    			std::cout << "*******************Datawriter....delayed callbacks done****************** at"<<asctime(ct) << std::endl;
    			clock_gettime(CLOCK_MONOTONIC, &AqData._timeOfLastDBSync);

    		}
#endif

            sleep(100);
            //std::cout << "DatabaseWriter thread" << std::endl;
        }
    }
    catch(...)
    {
        std::cout << "Exception thrown, Database writing error: DatabaseWriterThread" << std::endl;
        std::cout << "Exiting" << std::endl;
        AqData._continueRunning.Set(False);
    }
    
    return retValue;
}


void Garfunkel::DatabaseManager::Cleanup()
{
}
        
//  Add all of the board messages, creates the connection with the RS485 Socket layer
BOOLEAN     Garfunkel::DatabaseManager::Initialize()
{      
    return True;
}

