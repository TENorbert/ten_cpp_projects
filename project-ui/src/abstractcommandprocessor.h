#ifndef ABSTRACT_COMMAND_PROCESSOR_H
#define ABSTRACT_COMMAND_PROCESSOR_H

#include <map>
#include <string>

#include "ESPStringCreate.h"
#include "abstractipcmessage.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

//% Note: Changes: For Garfunkel
//%             We will use "Ba"  instead of the present "Oa" for AddressInstance,
//%                 i.e B = Address & a = Instance 
//%             As from Feb 02, 2016

    class AbstractCommandProcessor : public QObject
    {
        Q_OBJECT

    public:
        AbstractCommandProcessor();
        virtual ~AbstractCommandProcessor();
        
        virtual bool executeESPCommand(std::string& command, std::string& output);
        virtual int  initializeCommandProcessor(const std::string&  database, const std::string& databaseItem) = 0;
        virtual bool addCommand(const std::string command, boost::shared_ptr< AbstractIPCMessage> msg);

    signals:
        void setSystemStatus(int status);

    public slots:

    protected:
        //
        // The following support ESP message processing
        //
        ecolab::ESP::ESPStringCreate                                  _espCreateString;
        std::string                                                   _addressInstance;    
        std::map< std::string, boost::shared_ptr< AbstractIPCMessage > > _commandMap;

        std::string     getAddressAndInstance(std::string& command);
        std::string     getCommand(std::string& command);
        std::string     getSubCommand(std::string& command);
        std::string     getCommandIdentifier(std::string& command);
        std::string     getPayload(std::string& command, INT32&  numParameters);            
        std::string     getParameter(std::string& command);
        BOOLEAN         isLengthOfCommandValid(std::string command);
        virtual void    setAddress(const std::string& address);

    };    

#endif
