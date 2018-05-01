#ifndef DB_COMMANDS_H
#define DB_COMMANDS_H

#include <stdio.h>
#include <iostream>

#include "ecolab.h"
#include "DBAccess.h"
#include "DBException.h"

namespace Garfunkel
{
    class DatabaseCommands
    {
        public:
            DatabaseCommands(const std::string & dbName, const std::string & dbUser, const std::string & dbPass);
            ~DatabaseCommands();

            BOOLEAN GetSystemInformation(std::string & systemInfo);

            BOOLEAN EstablishDatabaseConnection(void);
            void InitializeCallback();
            BOOLEAN CallBacksSetup() {return _callbacksSetup;};
            BOOLEAN DelayedCallbacksPresent();
            BOOLEAN ExecuteDelayedCallbacksNow();



        private:
            BOOLEAN DBConnectionAvailable(void);

            const std::string               _dbName;
            const std::string               _dbUser;
            const std::string               _dbPass;

            ecolab::DB::DBAccess            _database;
            ecolab::DB::DBNotify2            _databaseNotify;
            BOOLEAN                         _callbacksSetup;

    };
};

#endif //DB_COMMANDS_H
