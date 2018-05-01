#ifndef IPC_COMMAND_H
#define IPC_COMMAND_H

#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "ecolab.h"

#define COMMAND_LENGTH 2

    class IPCCommand
    {
        public:
            IPCCommand(std::string & command);
            
            ~IPCCommand();
            
            std::string                 GetFullCommand() { return GetAddressAndInstance() + ":" + GetCommandAndSubCommand() + ":" + GetPayload(); }
            std::string                 GetAddress() { return _address; }
            std::string                 GetInstance() { return _instance; }
            std::string                 GetAddressAndInstance() { return _address + _instance; }
            std::string                 GetCommandAndSubCommand();
            std::string                 GetCommand() { return _command; }
            std::string                 GetSubCommand() { return _subCommand; }
            std::string                 GetPayload() { return _payload; }
            std::string                 GetCommandNumber() {return _commandNumber;};
            std::vector<std::string>    GetPayloadList();
            
            BOOLEAN                     IsAddressValid(const std::string & addressInstance);
            BOOLEAN                     IsDUCommand();
            BOOLEAN                     IsSUCommand();            

        private:
            void ProcessCommand(std::string & command);
            BOOLEAN ExtractAddressAndInstance(std::string & command);
            BOOLEAN ExtractCommands(std::string & command);
            BOOLEAN ExtractPayload(std::string & command);
            
            std::string             _address;
            std::string             _instance;
            std::string             _command;
            std::string             _subCommand;
            std::string             _payload;
            std::string             _commandNumber;
    };
    
    // Used to parse the returned command.
    class IPCReturnCommand
    {
    public:
        IPCReturnCommand(std::string  & retCommand);
        ~IPCReturnCommand();
        
        BOOLEAN                     IsAddressValid(const std::string & addressInstance);
        std::string                 GetPayload();
        std::vector<std::string>    GetPayloadList();
        std::string                 GetPayloadWithoutWhiteSpace();
    private:
        void                    ProcessCommand(std::string & command);
        BOOLEAN                 ExtractAddressAndInstance(std::string & command);
        BOOLEAN                 ExtractPayload(std::string & command);
        
        std::string             _address;
        std::string             _instance;
        std::string             _payload;
    };


#endif //IPC_COMMAND_H
