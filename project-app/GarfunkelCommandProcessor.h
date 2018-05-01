#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <map>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>


#include "DBAccess.h"
#include "ESPStringCreate.h"

#include "SocketHandler.h"
#include "IPCMessages.h"
#include "BoardCommands.h"
#define COMMAND_LENGTH 2

namespace Garfunkel
{
    // Needs to be created as a template?

    class GarfunkelCommandProcessor
    {
    public:
        virtual ~GarfunkelCommandProcessor();
        
        // This is a override to handle the command processing from th slave device
        virtual BOOLEAN ExecuteESPCommand(std::string & command, std::string &    output);
        virtual int     InitializeCommandProcessor(const std::string &  database, const std::string & databaseItem);
    
        BOOLEAN AddCommand(const std::string command, boost::shared_ptr< Garfunkel::IIPCMessage > pMsg);

        // Create as a singleton
        static GarfunkelCommandProcessor&	Instance();
    private:
        ecolab::ESP::ESPStringCreate                _espCreateString;
        std::string                                 _addressInstance;    
        std::map<std::string, boost::shared_ptr< Garfunkel::IIPCMessage > >   _commandMap;
        BOOLEAN ReadUIAddressestFromFile();
        BOOLEAN WriteUIAddressesToFile();
        GarfunkelCommandProcessor();
    };    

    class GarfunkelCommandProcessorIOBoard
    {
    public:
        virtual ~GarfunkelCommandProcessorIOBoard();
        
        // This is a override to handle the command processing from th slave device
        virtual BOOLEAN ExecuteCommand(const std::string  command, boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485, BOOLEAN override = False);
        virtual int     InitializeCommandProcessor(const std::string &  database, const std::string & databaseItem);
    
        BOOLEAN AddCommand(const std::string command, boost::shared_ptr< Garfunkel::IIOBoardMessage > pMsg);
        
        void    EnableCommand(const std::string  command);
        void    DisableCommand(const std::string command);
        boost::shared_ptr< Garfunkel::IIOBoardMessage > GetCommand(const std::string  command);
        
        // Create as a singleton
        static GarfunkelCommandProcessorIOBoard&	Instance();
    private:
        ecolab::ESP::ESPStringCreate                _espCreateString;
        std::string                                 _addressInstance;    
        std::map<std::string, boost::shared_ptr< Garfunkel::IIOBoardMessage > >   _commandMap;
        
        GarfunkelCommandProcessorIOBoard();
    };    
    

};

#endif
