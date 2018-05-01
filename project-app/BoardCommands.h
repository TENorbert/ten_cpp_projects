#ifndef BOARD_COMMANDS_H
#define BOARD_COMMANDS_H


#include "ecolab.h"
#include "SocketHandler.h"
#include <boost/shared_ptr.hpp>
#include "GarfunkelEnums.h"

namespace Garfunkel
{
    class IIOBoardMessage
    {
    public:
        IIOBoardMessage(std::string & addressInstance);

        virtual ~IIOBoardMessage();
        
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485) = 0;       // Will send the data 
    
        // This is an addition back into the System commands
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated) = 0;  // This will check if the message should be run
        virtual int HandleIPCResponse(std::string &     response) = 0;
        
		virtual void    SetMessageToRun(BOOLEAN setToRun){_runCommand = setToRun;}
        std::string     GetCommandName() {return _commandName;};
        std::string     GetAddressInstance() {return _addressInstance;};
        BOOLEAN         IsCommandCompleted(){return _isCommandComplete;};
        virtual void    SetCommandReadyToRun(BOOLEAN    runCommand);
        GarfunkelESPResponse               _respCode;
        int                                 _errNo;

        
    protected:
        std::string                         _addressInstance;
        ecolab::ESP::ESPStringCreate        _espString;
        BOOLEAN				                _runCommand;
        std::string                         _commandName;
        BOOLEAN                             _isCommandComplete;
        
        virtual int SendMessage(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485, std::string & message, std::string & response);
        std::string	StripAddressAndInstance(std::string & command);
        std::string	StripCommandType(std::string & command);
        std::string	StripSubCommand(std::string & command);
        std::string GetCommandNumber(std::string & command);
        void GetESPDestinationBoardInfo( GarfunkelESPCommandDestination &addr, int &instance);

    };    


	 class IIOBoardTimedMessage : public IIOBoardMessage
	 {
	 public:
		 IIOBoardTimedMessage(std::string & addressInstance) ;
		 ~ IIOBoardTimedMessage();

		 void UpdateLastRunTime();
		 BOOLEAN ReadyToRestart();
		 void SetTimeInterval(int sec);
		 BOOLEAN operator>(const IIOBoardTimedMessage &rhs);
		 void StartTimedMessage();
		 void StopTimedMessage();

	 protected:
		 timespec _lastRunTime;
		 int      _intervalTime; //in sec
		 int FromHex(const std::string &s) { return strtoul(s.c_str(), NULL, 16); }
	 };

	 class SortTimedMessagesByExpiry
		    {
		    public:
		    	bool operator()(boost::shared_ptr<IIOBoardTimedMessage > lhs, boost::shared_ptr<IIOBoardTimedMessage > rhs)
		    	{
		   			return (*lhs > *rhs);
		    	}
		    };

} 
    
#endif
