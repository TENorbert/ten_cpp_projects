#include <iostream>
#include "abstractipcmessage.h"
#include "GarfunkelIPC.h"

#include "ecolab.h"
#include "ESPStringCreate.h"

AbstractIPCMessage::AbstractIPCMessage(GarfunkelIpc* ipc):  _ipc(ipc)
{
    _ACK.push_back((char)0x6);
    _NACK.push_back((char)0x15);
    _setLoopCount(200);
    _setSleepFactor(50000);
    _address_instance = "Oa";

}
AbstractIPCMessage::~AbstractIPCMessage()
{
}

bool
AbstractIPCMessage::createESPString(std::string& dataToConvert)
{
    ecolab::ESP::ESPStringCreate    createString;
    
    return createString.ConvertToESPString(dataToConvert);
}

bool
AbstractIPCMessage::convertESPString(std::string& dataToConvert)
{
    ecolab::ESP::ESPStringCreate    convertString;    
    
    return convertString.ConvertFromESPString(dataToConvert);
}
bool
AbstractIPCMessage::sendMessage(int& status)
{
    Q_UNUSED(status);
    qDebug() << "AbstractIPCMessage::sendMessage called - did you forget to implement a method?";
    return(true);
}
bool
AbstractIPCMessage::processMessage(IPCCommand& command, std::string& response)
{
    Q_UNUSED(command);
    Q_UNUSED(response);
    return(true);
}






