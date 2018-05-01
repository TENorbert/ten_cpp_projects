#ifndef DATABASE_WRITER_H
#define DATABASE_WRITER_H

#include <vector>
#include <memory>
#include <poll.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#include "GarfunkelData.h"

#include "DatabaseCommands.h"
#include "ecolab.h"
#include "threads.h"


namespace Garfunkel
{

	class GarfunkelDB
	{

	public:
		GarfunkelDB();
		~GarfunkelDB();

		/*!
        	Method to connect to the database.
		 */
		BOOLEAN    connect(const int retryAttempts = 5);
		bool       disconnect();

		/*!
        	Method to execute a stored function in the database.
		 */
		void executeStoredFunction(const std::string &storedFunction, ecolab::DB::DataSet & dataSet);

		/*!
        	Method to execute a straight SQL statement on the database.
		 */
		void executeSQL(const std::string &executeString, ecolab::DB::DataSet & dataSet);
		void executeSQL(const std::string &executeString);
		bool isConnected(){return (NULL != mDBAccess.DBisConnected() ? true : false);}

		int valueInt(ecolab::DB::DataRow rowData, const std::string &colName);
		std::string valueString(ecolab::DB::DataRow rowData, const std::string &colName);

	private:
		static const char *dbname;
		static const char *dbuser;
		static const char *dbpasswd;
		ecolab::DB::DBAccess mDBAccess;                 //!< Database access object.
	};



    class DatabaseManager : public ecolab::Thread
    {
    public:
    	DatabaseManager(const std::string & name);
    	DatabaseManager(const DatabaseManager &     objectToCopy);
        virtual ~DatabaseManager();

        virtual int Run();
        virtual void Cleanup();
        
        //  Add all of the board messages, creates the connection with the RS485 Socket layer
        BOOLEAN     Initialize();
    private:
        void SendMessageToUI(std::string &message);
       
    };



};

#endif
