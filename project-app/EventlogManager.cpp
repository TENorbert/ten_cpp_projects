#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "ecolab.h"
#include "EventlogManager.h"
////////////////////////////////////////////////////////////////
// EventDataLog

Garfunkel::EventDataLog::EventDataLog(const EventDataLog &   objectToCopy)
{
}

Garfunkel::EventDataLog::~EventDataLog()
{

	std::cout<<"EventDataLog destructor called"<<std::endl;
}


Garfunkel::EventDataLog&    Garfunkel::EventDataLog::Instance()
{
    static EventDataLog     singleton;
    return singleton;
}

Garfunkel::EventDataLog::EventDataLog()
{
    // Empty default constructor
}

BOOLEAN Garfunkel::EventDataLog::EventLog(int type, int subflag, int dataOne, int dataTwo, int dataThree, int dataFour, int dataFive, int dataSix)
{
    ecolab::MutexLock       DatabaseLock;   //!< Mutex lock for the database object.
    ecolab::DB::DBAccess    myDBAccess;
    std::string             connectString;
    BOOLEAN                 retValue = False;

    // Use of the connection string.
    connectString = "dbname = 'Garfunkelext' user = 'db_controller' password = 'controller'";

    /* Connect to DB if it is not connected. */
    if (!myDBAccess.DBisConnected())
    {
        myDBAccess.DBConnect(connectString, 5);
    }

    if(myDBAccess.DBisConnected())
    {
        std::stringstream strSql;
        strSql << "SELECT * FROM AddEventToLog(" << type << "," << subflag << "," << dataOne;
        strSql << "," << dataTwo << "," << dataThree << "," << dataFour<< "," << dataFive << ","<<dataSix<< ","<< "'mca');";
        const std::string executeCmdString = strSql.str();

        std::cout << "executeCmdString: " << executeCmdString << std::endl;

        ecolab::ScopeLock Lock(DatabaseLock);
        ecolab::DB::DataSet DataSet;

        if(myDBAccess.DBExecuteStored(executeCmdString, DataSet))
        {
			retValue = True;
		}
		else
        {
            std::cout << "EventLog failed to update.." << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR: no database connection!" << std::endl;
    }
    return retValue;
}
