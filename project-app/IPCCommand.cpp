#include "IPCCommand.h"

Garfunkel::IPCCommand::IPCCommand(std::string & command) : _address(""), _instance(""), _command(""), _subCommand(""), _payload("")
{
    std::string tempCommand(command);
    ProcessCommand(tempCommand);
}

Garfunkel::IPCCommand::~IPCCommand()
{
    /* empy */
}

void Garfunkel::IPCCommand::ProcessCommand(std::string & command)
{
    if (True != ExtractAddressAndInstance(command))
        return;

    if (True != ExtractCommands(command))
        return;

    ExtractPayload(command);  
}

BOOLEAN Garfunkel::IPCCommand::ExtractAddressAndInstance(std::string & command)
{
    BOOLEAN             retValue = False;
    std::string         temp;
    size_t              pos = 0;
    std::string         findChar = ":";

    pos = command.find(findChar); 

    if(pos != std::string::npos)
    {
        temp = command.substr(0, pos);
        
        if (temp.length() == 2)
        {
            _address = temp[0];
            _instance = temp[1];
            retValue = True;                
        }
        
        command = command.erase(0, pos + 1);
    }

    return retValue;
}

BOOLEAN Garfunkel::IPCCommand::ExtractCommands(std::string & command)
{
    BOOLEAN     retValue = False;

    if (command.length() >= 2)
    {
        _command = command.substr(0, 1);
        _subCommand = command.substr(1, 1);
        command = command.erase(0, 2);
        retValue = True;
    }

    return retValue;
}

BOOLEAN Garfunkel::IPCCommand::ExtractPayload(std::string & command)
{
    BOOLEAN         retValue = False;
    size_t          pos = 0;
    std::string     findChar = ":";

    pos = command.find(findChar); 
    if(pos != std::string::npos)
    {      
        _payload = command.substr(pos+1, command.length() - pos);
        // Payload needs to be broken apart, there is the command numeric and the actual command payload
        size_t  payloadPos = 0;
        payloadPos = _payload.find(findChar);        

        if(std::string::npos != payloadPos)
        {
            _commandNumber = _payload.substr(0, payloadPos);
//std::cout << "_commandNumber: " << _commandNumber << std::endl;
            _payload = _payload.erase(0, payloadPos + 1);
        }
        command = command.erase(pos+1, command.length() - pos);
    }

    return retValue;
}

BOOLEAN Garfunkel::IPCCommand::IsAddressValid(const std::string & addressInstance)
{
    std::string     currentAddressInstance = _address + _instance;
    
    return ((BOOLEAN)(currentAddressInstance.compare("?") == 0 \
        || currentAddressInstance.compare("??") == 0 \
        || currentAddressInstance.compare(addressInstance) == 0));
}

BOOLEAN Garfunkel::IPCCommand::IsDUCommand()
{
    BOOLEAN     retValue = False;
    
    if (_command.length() == 1 && (_command[0] == 'd' || _command[0] == 'D'))
    {
        retValue = True;
    }
    
    return retValue;
}

BOOLEAN Garfunkel::IPCCommand::IsSUCommand()
{
    BOOLEAN     retValue = False;

    if (_command.length() == 1 && (_command[0] == 's' || _command[0] == 'S'))
    {
        retValue = True;
    }
    
    return retValue;
}

std::string Garfunkel::IPCCommand::GetCommandAndSubCommand()
{ 
    std::string retValue = "";
    
    retValue = _command + _subCommand;
    
    // Only if there is a command number tack that onto the command name.
    if(_commandNumber.length() > 0  && _commandNumber.length() <= 2)
    {
        retValue += ":" + _commandNumber; 
    }
    
    return retValue;
}

std::vector<std::string> Garfunkel::IPCCommand::GetPayloadList()
{
    std::vector<std::string>    payloadList;
    std::string                 payloadTemp = _payload;
    size_t                      pos;
    std::string                 findChar(":");

    if (payloadTemp.length() > 0)
    {
        pos = payloadTemp.find_last_of(findChar);
        if(std::string::npos != pos)
        {
            payloadTemp = payloadTemp.erase(pos, payloadTemp.length() - 1);
        }

        boost::split(payloadList, payloadTemp, boost::is_any_of(":"));
    }
    
    return payloadList;
}

/////////////////////////////////////////////////////////////////////////////
//  IPCReturnCommand

Garfunkel::IPCReturnCommand::IPCReturnCommand(std::string  & retCommand) :
    _address(""), _instance(""), _payload("")
{
    std::string tempCommand(retCommand);
    ProcessCommand(tempCommand);
}

Garfunkel::IPCReturnCommand::~IPCReturnCommand()
{
}

std::string Garfunkel::IPCReturnCommand::GetPayload()
{
    return _payload;
}

void Garfunkel::IPCReturnCommand::ProcessCommand(std::string & command)
{
    if (True != ExtractAddressAndInstance(command))
        return;
    if (True != ExtractPayload(command))
        return;
}

BOOLEAN Garfunkel::IPCReturnCommand::ExtractAddressAndInstance(std::string & command)
{
    BOOLEAN             retValue = False;
    std::string         temp;
    size_t              pos = 0;
    std::string         findChar = ":";

//    std::cout<<"ExtractAddressAndInstance command="<<command<<std::endl;

    pos = command.find(findChar); 

    if(pos != std::string::npos)
    {
        temp = command.substr(0, pos);
        
        if (temp.length() == 2)
        {
            _address = temp[0];
            _instance = temp[1];
            retValue = True;
           // std::cout<<"_address="<<_address<<std::endl;
            //std::cout<<"_instance="<<_instance<<std::endl;
        }
        
        command = command.erase(0, pos + 1);
    }

    return retValue;
}
    
BOOLEAN Garfunkel::IPCReturnCommand::IsAddressValid(const std::string & addressInstance)
{
    std::string     currentAddressInstance = _address + _instance;
    
    return ((BOOLEAN)(currentAddressInstance.compare("?") == 0 \
        || currentAddressInstance.compare("??") == 0 \
        || currentAddressInstance.compare(addressInstance) == 0));
}

BOOLEAN Garfunkel::IPCReturnCommand::ExtractPayload(std::string & command)
{
    BOOLEAN         retValue = False;
    size_t          pos = 0;
    std::string     findChar = ":";
    pos = command.find_last_of(findChar); 

    // Remove the trailing ':'
    if(pos != std::string::npos)
    {      
        _payload = command.substr(0, pos);
        //std::cout << "Payload: " << _payload << std::endl;
        // Payload needs to be broken apart, there is the command numeric and the actual command payload
        size_t  payloadPos = 0;
        payloadPos = _payload.find(findChar);        
        retValue = True;
    }

    return retValue;
}

std::vector<std::string> Garfunkel::IPCReturnCommand::GetPayloadList()
{
    std::vector<std::string>    payloadList;
    std::string                 payloadTemp = _payload;
    std::string                 findChar(":");
//std::cout << "Payload temp: " << payloadTemp << std::endl;
    if (payloadTemp.length() > 0)
    {
        boost::split(payloadList, payloadTemp, boost::is_any_of(":"));
    }
    
    return payloadList;
}

std::string     Garfunkel::IPCReturnCommand::GetPayloadWithoutWhiteSpace()
{
    std::string     payloadNoWhiteSpace = "";
    int             x = 0;
    int             strLength = -1;
   
    strLength = _payload.length();
    
    for(; x < strLength; x++)
    {
        if(_payload.at(x) != ' ')
        {
            payloadNoWhiteSpace += _payload.at(x);
        }
    }
    
    return payloadNoWhiteSpace;
}
