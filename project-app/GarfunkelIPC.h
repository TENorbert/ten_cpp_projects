#ifndef AQUAGATOR_IPC_H
#define AQUAGATOR_IPC_H

#include <exception>
#include <map>
#include <string>
#include "eipc.h"
#include "GarfunkelData.h"
#include "GarfunkelCommandProcessor.h"
#include "IPCMessages.h"
//#include "DatabaseCommands.h"


namespace Garfunkel
{
    class BadConversion : public std::runtime_error
    {
        public:
            BadConversion(std::string const &s) : std::runtime_error(s) {}
    };

    class GarfunkelIPCSlave : public ecolab::IPC
    {
    public:
        GarfunkelIPCSlave();
        virtual ~GarfunkelIPCSlave();
            
        void init();
        void SendESPCommandResponse(const std::string &message);
        int ReceiveESPCommand();
        int ReceiveESPCommandWithValidation();
        
    private:
        BOOLEAN RegisterCallback(std::string command, boost::shared_ptr<Garfunkel::IIPCMessage> pMsg);
        BOOLEAN RegisterCallback(std::string command1, std::string command2, boost::shared_ptr<Garfunkel::IIPCMessage> pMsg);

        std::string                                     _ack;
        std::string                                     _nak;    
    };
    
    class GarfunkelIPCMaster : public ecolab::IPC
    {
    public:
        GarfunkelIPCMaster(const GarfunkelIPCMaster & objectToCopy);
        virtual ~GarfunkelIPCMaster();
            
        void SendESPCommandResponse(std::string &message);
        BOOLEAN ReceiveESPCommandWithValidation();
        void    ClearTheReceiveQueue();
        
        static GarfunkelIPCMaster&  Instance();
        

    private:
        std::string                         _ack;
        std::string                         _nak;
        ecolab::ESP::ESPStringCreate        _espString;
                
        GarfunkelIPCMaster();
    };
    
    
    class GarfunkelIPCSlaveCommunication : public ecolab::Thread
    {
    public:
        GarfunkelIPCSlaveCommunication(const std::string & name);
        virtual ~GarfunkelIPCSlaveCommunication();
        
        virtual int Run();
        virtual void Cleanup();
        
    private:
    };
    
};
#endif
