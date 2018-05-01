#include "GarfunkelData.h"
#include "GarfunkelIPC.h"
#include "GarfunkelEnums.h"
#include "BoardCommands.h"
#include <boost/lexical_cast.hpp>

////////////////////////////////////////////////////////////
//  This is an interface base class
////////////////////////////////////////////////////////////
Garfunkel::IIOBoardMessage::IIOBoardMessage(std::string & addressInstance) :
    _addressInstance(addressInstance)
{
    _runCommand = False;
    _commandName = "Unknown";
    _isCommandComplete = False;
    _respCode = eUndefinedESPResponse;
    _errNo = -1;

}


Garfunkel::IIOBoardMessage::~IIOBoardMessage()
{

}

int Garfunkel::IIOBoardMessage::SendMessage(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485, std::string & message, std::string & response)
{
    int     retValue = -1;


	SystemData& SystemData = SystemData::Instance();

    if((NULL != pSocketRS485.get()) && (True == pSocketRS485->SocketConnected()) && (pSocketRS485->SocketStatus() == ecolab::eConnectionAvailable))
    {
        // First convert the message to an appropriately formatted ESP-GEN2 string

    	//std::cout<<"Sending : "<<message<<std::endl;

        if(True == pSocketRS485->WriteData(message))
        {
            //  Was an appropriate ack returned.
            if(False == pSocketRS485->IsNAK())
            {
                if(True == pSocketRS485->ReadData(response))
                {
                	if(response.find("ERR",0)!=std::string::npos)
                	{
                		std::cout<<"IIOBoardMessage::SendMessage : Error response="<<response<<" for command="<<message<<std::endl;
                		_respCode = eErrorResponse;
                		retValue = -1;
                		//exit(0);
                	}
                	else
                    retValue = 1;
                	//std::cout << "Response : "<<response<< std::endl;
                }
                else
                {
                	_respCode = eFailedToReadResponse;
                	std::cout << "Failed to read response for "<<message<< std::endl;
                }
            }
            else
            {
            	_respCode = eNAKResponse;
				std::cout << "Nak received for "<<message<< std::endl;
				//exit(0);
            }

        }
        else
        {
        	_respCode = eFailedToWriteCommand;
            std::cout << "Data was not sent correctly" << std::endl;
        }
    }
    else
    {
    	_respCode = eSocketConnectionNotAvailable;
    	std::cout << "No Socket connection" << std::endl;
    }

    if(0) //retValue!=1)
    {
    	int commandType = 0; ///0 -du , 1- su command
    	int subCommandNo = -1;
    	GarfunkelESPCommandDestination addr = eUndefinedDestination;
    	int instance = 0;
    	std::string command, retResponse;
    	std::string subCommand, errNoString;

    	try
    	{
    		if(message.find("SU",0)!=std::string::npos)
    		{
    			commandType = 1;
    		}

    		command.assign(message);
    		retResponse.assign(response);
    		GetESPDestinationBoardInfo(addr, instance);
    		StripAddressAndInstance(command); //strip adress and instance of
    		StripCommandType(command); //strip command
    		StripSubCommand(command);
    		subCommand = GetCommandNumber(command);
    		subCommandNo = boost::lexical_cast <int>(subCommand);
    		if(_respCode==eErrorResponse)
    		{
    			int pos;
    			pos = command.find("ERR",0);
    			if(pos!=std::string::npos)
    			{
    				errNoString = response.substr(pos+3,0);
    				_errNo = boost::lexical_cast <int>(errNoString);
    			}
    		}
    		std::cout << "eESPResponseError : respCode="<<_respCode << std::endl;
    		//log.EventLog(eESPResponseError, (int) addr, instance, (int) _respCode, commandType, subCommandNo, _errNo, -1);
    	}
    	catch(std::exception & e)
        {
            std::cout << "SendMessage: caught exception while parsing for log messgae: " <<e.what()<< std::endl;

        }
    }

    return retValue;
}


std::string	Garfunkel::IIOBoardMessage::StripAddressAndInstance(std::string & command)
{
	std::string  	retValue;
	size_t			pos = 0;
	std::string		findChar = ":";

	pos = command.find(findChar);
	if(pos != std::string::npos)
	{
		retValue = command.substr(0, pos);

        // Shorten the overall string
        command = command.erase(0, pos + 1);
	}

	return retValue;
}

std::string	Garfunkel::IIOBoardMessage::StripCommandType(std::string & command)
{
	std::string  	retValue;
    retValue = command.substr(0, 1);
    command = command.erase(0, 1);

	return retValue;
}

std::string	Garfunkel::IIOBoardMessage::StripSubCommand(std::string & command)
{
	std::string  	retValue;
    size_t          pos;
    std::string		findChar = ":";

    retValue = command.substr(0, 1);

    pos = command.find(findChar);
    if(std::string::npos != pos)
    {
    	command = command.erase(0, pos + 1);
    }

	return retValue;
}

std::string Garfunkel::IIOBoardMessage::GetCommandNumber(std::string & command)
{
	std::string  	retValue;
	size_t		    pos = 0;
	std::string	    findChar = ":";

	pos = command.find(findChar);

	if(std::string::npos != pos)
	{
		retValue = command.substr(0, pos);
        command = command.erase(0, pos + 1);
    }

	return retValue;
}

void Garfunkel::IIOBoardMessage::GetESPDestinationBoardInfo( GarfunkelESPCommandDestination &addr, int &instance)
{
	//find addr
	 int pos;
	 pos = _addressInstance.find("r",0);
	 if(pos!=std::string::npos)
	 {
		 addr = eIOBoard;
	 }
	 pos = _addressInstance.find("m",0);
	 if(pos!=std::string::npos)
	 {
		 addr = eMSIBoard;
	 }
	 pos = _addressInstance.find("j",0);
	 if(pos!=std::string::npos)
	 {
		 addr = eFormulaSelectBoard;
	 }

	 //find instance
	 pos = _addressInstance.find("a",0);
	 if(pos!=std::string::npos)
	 {
		 instance = 1; //machine 1
	 }
	 pos = _addressInstance.find("b",0);
	 if(pos!=std::string::npos)
	 {
		 instance = 2; //machine 2
	 }
	 pos = _addressInstance.find("c",0);
	 if(pos!=std::string::npos)
	 {
		 instance = 3; //machine 3
	 }
	 pos = _addressInstance.find("d",0);
	 if(pos!=std::string::npos)
	 {
		 instance = 4; //machine 4
	 }

	 std::cout << "eESPResponseError :  addr ="<<addr << std::endl;
	 std::cout << "eESPResponseError :  instance ="<<instance << std::endl;
}

// Set the commands completion state
void    Garfunkel::IIOBoardMessage::SetCommandReadyToRun(BOOLEAN    runCommand)
{
    if(True == runCommand)
    {
        _isCommandComplete = False;
    }
    else
    {
        _isCommandComplete = True;
    }
}

Garfunkel::IIOBoardTimedMessage::IIOBoardTimedMessage(std::string & addressInstance) :
		IIOBoardMessage(addressInstance)
{
	clock_gettime(CLOCK_MONOTONIC, &_lastRunTime); //reset
	_intervalTime = 8; //8 sec default
}

Garfunkel::IIOBoardTimedMessage::~IIOBoardTimedMessage()
{

}
void Garfunkel::IIOBoardTimedMessage::UpdateLastRunTime()
{
	timespec Now;
	 time_t clock1 = time(0);
	 struct tm *ct = localtime(&clock1);
	 clock_gettime(CLOCK_MONOTONIC, &Now);

	 /*std::cout<<"_addressInstance="<<_addressInstance<<std::endl;
	 std::cout<<"_commandName="<<_commandName<<std::endl;
	 std::cout<<"_intervalTime="<<_intervalTime<<std::endl;
	 std::cout<<"ElapsedTime="<<ElapsedTime(&_lastRunTime,&Now)<<std::endl;
	 std::cout<<"Current run time="<<asctime(ct)<<std::endl;*/

	time_t clock2 = time(0);
	 struct tm *ct2 = localtime(&clock2);
	clock_gettime(CLOCK_MONOTONIC, &_lastRunTime);
	//std::cout<<"Updated last time="<<asctime(ct2)<<std::endl;

}

BOOLEAN Garfunkel::IIOBoardTimedMessage::ReadyToRestart()
{
	 timespec Now;
	 clock_gettime(CLOCK_MONOTONIC, &Now);
	 if(ElapsedTime(&_lastRunTime,&Now) >= _intervalTime)
	 {
		 return True;
	 }
	 else
     return False;
}
void Garfunkel::IIOBoardTimedMessage::SetTimeInterval(int sec)
{
	 _intervalTime = sec;
}

BOOLEAN Garfunkel::IIOBoardTimedMessage::operator>(const IIOBoardTimedMessage &rhs)
{
	BOOLEAN _isGreater = False;

	if(_lastRunTime.tv_sec > rhs._lastRunTime.tv_sec)
	{
	 	 _isGreater = False;
	}
	else if(_lastRunTime.tv_sec < rhs._lastRunTime.tv_sec)
	{
	  	 _isGreater = False;
	}
	else if(_lastRunTime.tv_nsec > rhs._lastRunTime.tv_nsec)
	{
	  	 _isGreater = False;
	}
	return _isGreater;
 }

void Garfunkel::IIOBoardTimedMessage::StartTimedMessage()
{
	SetMessageToRun(True);
}
void Garfunkel::IIOBoardTimedMessage::StopTimedMessage()
{
	SetMessageToRun(False);
}


