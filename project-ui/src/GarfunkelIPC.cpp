//=============================================================================================================
//%
//%  \brief File containing the interprocess communication commands for the Garfunkel UI.
//%
//%  This file contains the commands necessary to send and receive interprocess communication messages.
//%
//%  Orig: author David Clounch
//%  current: Tambe E. Norbert
//=============================================================================================================
#include <iostream>
#include <sstream>
#include <map>
#include <string>

#include "eipc.h"
#include "ESPStringCreate.h"
#include <QVariant>
#include <QtCore>
#include <QTime>


//#include "ipccallback.h"
#include "ipcexception.h"
#include "GarfunkelIPC.h"
#include "GarfunkelCommandProcessor.h"

//====================================================================================================
//!
//! \b GarfunkelIPC Constructor
//!
//! \param[in]  const std::string& from is the label for the originating connection or application
//!
//! \param[in]  const std::string& to is the label for the destination  connection or application
//!
//! \returns none
//====================================================================================================
GarfunkelIpc::GarfunkelIpc(const std::string &from, const std::string &to ) : _ipc(from, to, 200)
{
      _cp = 0; // Initialize pointer!
      std::cout << "[GarfunkelIpc] IPC started..." << std::endl; 
//    std::cout << "[GarfunkelIpc] IPC started..." << std::endl;
//    std::cout << "[GarfunkelIpc] to base class passed FROM =  " << from <<  " " << std::endl;
//    std::cout << "[GarfunkelIpc] to base class passed TO =    " << to <<  " " << std::endl;
}
//====================================================================================================
//!
//! \b GarfunkelIpc Destructor
//!
//! \param[in]  none
//!
//! \param[out  none
//!
//! \returns none
//====================================================================================================
GarfunkelIpc::~GarfunkelIpc()
{
}

bool
GarfunkelIpc::isMessageAvailable()
{
    // Call the ecolab ipc method
    return(_ipc.IsMessageAvailable());
}


//====================================================================================================
//!
//! \b sendStringMessage is a public method
//!
//! \param[in]  const std::string& message is the message to send
//! \param[out] none
//!
//! \returns none
//====================================================================================================
void 
GarfunkelIpc::sendStringMessage(const std::string& message) 
{

    /* fill a buffer with our message and send it off */
    ecolab::IPC::BufferT buffer(message.begin(), message.end());
    // test std::string me("");
    // test ecolab::IPC::BufferT buffer2(me.begin(), me.end());

    try
    {
//        qDebug() << "GarfunkelIpc::sendStringMessage:  SENDING to ecolab::IPC::SendMessage()";
        _ipc.SendMessage(buffer);
//        qDebug() << "SENT ";
    }
    catch(std::exception& e)
    {
        std::cout << "[GarfunkelIpc] Resending..." << std::endl;
        _ipc.SendMessage(buffer);
        std::cout << "[GarfunkelIpc] Recovery complete." << std::endl;
    }
    catch(...)
    {
        std::cout << "[GarfunkelIpc] DROPPING IT." << std::endl;
    }
}

//====================================================================================================
//!
//! \b processMessage is a public method
//!
//! \param[in]  none
//! \param[out] none
//!
//! \returns int
//====================================================================================================
int 
GarfunkelIpc::processMessage() 
{

#ifdef TBD
    if(!_ipc.isMessageAvailable())
    {
        return -1;
    }

    std::string messageStr;
    receiveStringMessage(messageStr);

    boost::char_separator<char> sep(";");
    boost::tokenizer< boost::char_separator<char> > tok(messageStr, sep);
    for(boost::tokenizer< boost::char_separator<char> >::iterator beg = tok.begin(); beg != tok.end(); ++beg) 
    {
        std::string value;
        std::string name;
        std::string message(*beg);
        message = message + ";";
        if(parseNameValuePair(message, name, value) != 0)
        {
            return -1;
        }
        if(commandMap[name] != NULL) 
        {
            QVariant updateValue(QString::fromStdString(value));
            commandMap[name]->Update(updateValue);
        } else {
            std::cout << "[IPC] ERROR: No callback for message=" << name << std::endl;
        }
    }
#endif
    return 0;
}
void
GarfunkelIpc::printMessage(const char *tag, std::string& message )
{

    Q_UNUSED(tag);
    int sz = message.size();
//    std::cout << tag << ": Message has " << sz << " bytes "<< std::endl;
    const char* ptr = message.c_str();
    QString tmp1(": BYTES =  ");
    QString tmp2(": CHARS =  ");
    for (int i = 0; i < sz; i++)
    {
        char c = *(ptr + i);
        int chex = c;
        QString s = QString::number(chex,16);
        tmp1.append(s);
        switch(c)
        {
            case 0x01:
                tmp2.append(" SOH ");
                break;
            case 0x04:
                tmp2.append(" EOT ");
                break;
            case 0x06:
                tmp2.append(" ACK ");
                break;
            case 0x15:
                tmp2.append(" NAK ");
                break;
            default:
                tmp2.append(c);
                break;
        }
        tmp1.append("  ");
        tmp2.append("  ");
    }
//    qDebug() << tag << tmp1;
//    qDebug() << tag << tmp2;

}
//====================================================================================================
//!
//! \b receiveESPCommandWithValidation 
//!
//! \param[in]  const std::string& message is the message to receive
//! \param[out] const std::string& message is the message to receive
//!
//! \returns none
//====================================================================================================
int  
GarfunkelIpc::receiveESPCommandWithValidation()
{

    int                  retValue = 0;
    ecolab::IPC::BufferT buffer;
    std::string          message;

    if( True == isMessageAvailable() )
    {    
//        qDebug() << "qualogicIPC::receiveESPCommandWithValidation: MESSAGE AVAILABLE";
        /* receive message and convert to a string */
        _ipc.ReceiveMessage(buffer);
//        qDebug() << "qualogicIPC::receiveESPCommandWithValidation: _ipc.ReceiveMessage returned";
        message.assign(buffer.begin(), buffer.end());

        // Process the message
        std::string                      response;
        ecolab::ESP::ESPStringCreate     espObject;
        
//        printMessage("GarfunkelIpc::receiveESPCommandWithValidation",message);

//        std::cout << "--- [GarfunkelIpc] calling ConvertFromESPString ---" << std::endl;
        if(True == espObject.ConvertFromESPString(message))
        {
            std::stringstream   buffer;

            // split the message and process it.
            if(message.length() > 0 )
            {
                // Execute the message and send the response back
                if(False != _cp->ExecuteESPCommand(message, response))
                {
                    if(response.length() > 0)
                    {
                        std::string     ack;
                        ack.push_back((char)0x6);
                        
                        buffer << ack << response;
//                        SendESPCommandResponse(buffer.str());
                    }
                } 
                else
                {
                    std::cout << "[GarfunkelIpc] ESP Command execution failed" << std::endl;
                }
            }
        }
        else
        {
            std::cout << "[GarfunkelIpc] ConvertFromESPString == FALSE";
            std::string nak;
            nak.push_back((char)0x15);
       }
    }
    else
    {
        qDebug() << " qualogicIPC::receiveESPCommandWithValidation: NO MESSAGE AVAILABLE";
        // Do nothing
    }
    
    return retValue;
}
//====================================================================================================
//!
//! \b receiveStringMessage is a public method
//!
//! \param[in]  const std::string& message is the message to receive
//! \param[out] const std::string& message is the message to receive
//!
//! \returns none
//====================================================================================================
void 
GarfunkelIpc::receiveStringMessage(std::string& message)
{
    ecolab::IPC::BufferT buffer;

    /* receive message and convert to a string */
    //qDebug() << "------------------------------------------------- IPC MSG 1" << QTime::currentTime().toString("ss.zzz");
    _ipc.ReceiveMessage(buffer);
    //qDebug() << "------------------------------------------------- IPC MSG 2" << QTime::currentTime().toString("ss.zzz");
    message.assign(buffer.begin(), buffer.end());
}

//====================================================================================================
//!
//! \b _parseNameValuePair is a private method
//!
//! \param[in]  std::string& message is the message to send
//! \param[out] std::string& name    is the resulting name field
//! \param[out] std::string& name    is the resulting value field
//!
//! \returns err                     is the error code, -1 if failed, 0 if success 
//====================================================================================================
int 
GarfunkelIpc::_parseNameValuePair(std::string& message, std::string& name, std::string& value) 
{
    int err = -1;
    int pos = message.find('=', 0);

    /* Verify message is valid (eg contains = and ; */
    if (pos > 0 && message.at(message.length() - 1) == ';') {
        name = message.substr(0, pos);
        value = message.substr(pos + 1, message.length() - pos - 2);
        err = 0;
    } else {
        std::cout << "[GarfunkelIpc] " << "error parsing received string" << std::endl;
    }

    return err;
}

//====================================================================================================
//!
//! \b _convertToInt is a private method
//!
//! \param[in]  const std::string& message is the string to convert
//!
//! \returns    int                        is the converted value
//!
//====================================================================================================
int 
GarfunkelIpc::_convertToInt(const std::string& str) 
{
    std::istringstream i(str);
    int x;
    if (!(i >> x))
        throw IPCException("convertToInt(\"" + str + "\")");

    return x;
}

//====================================================================================================
//!
//! \b _convertToDouble is a private method
//!
//! \param[in]  const std::string& str is value message to convert
//! \param[out] none
//!
//! \returns double                        is the converted value
//
//====================================================================================================
double 
GarfunkelIpc::_convertToDouble(const std::string& str) 
{
    std::istringstream i(str);
    double x;
    if (!(i >> x))
        throw IPCException("convertToDouble(\"" + str + "\")");

    return x;
}

//====================================================================================================
//!
//! \b _convertToBool is a private method
//!
//! \param[in]  const std::string& str is the string to send
//! \param[out] none
//!
//! \returns bool                        is the converted value
//!
//====================================================================================================
bool 
GarfunkelIpc::_convertToBool(const std::string& str) 
{
    std::istringstream i(str);
    bool x;
    if (!(i >> x))
        throw IPCException("convertToBool(\"" + str + "\")");

    return x;
}

#ifdef TBD
//====================================================================================================
//!
//! \b processMessage is a public method
//!
//! \param[in]  none
//! \param[out] none
//!
//! \returns int         0 if message is available, -1 if message not available
//====================================================================================================
int 
GarfunkelIpc::processMessage() 
{
    std::string message;
    std::string name;
    std::string value;

    if (!_ipc.isMessageAvailable())
        return -1;

    _ipc.receiveStringMessage(message);

    if (_parseNameValuePair(message, name, value) != 0)
        return -1;

    if (_commandMap[name] != NULL) {
        //std::cout << "[GarfunkelIpc] " << "calling update.." << std::endl;
        _commandMap[name]->Update(_convertToInt(value));
        //std::cout << "[GarfunkelIpc] " << "update call done" << std::endl;
    } else {
        std::cout << "[GarfunkelIpc] " << "no callback for message=" << name << std::endl;
    }

    return 0;
}
#endif
//====================================================================================================
//!
//! \b registerCallback is a public method
//!
//! \param[in]  std::string message is the command  to register
//! \param[out] none
//!
//! \returns none
//====================================================================================================
void 
GarfunkelIpc::registerCallback(const std::string& command, IPCCallback *fPtr) 
{

    Q_UNUSED(command);
    Q_UNUSED(fPtr);
//    _commandMap[command] = fPtr;
}

