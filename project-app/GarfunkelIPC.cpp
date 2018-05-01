#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <iomanip>
#include <boost/algorithm/string.hpp>

#include "eipc.h"
#include "GarfunkelData.h"
#include "GarfunkelIPC.h"
#include "ElapsedTime.h"
#include "ESPStringCreate.h"
#include "IPCMessages.h"


Garfunkel::GarfunkelIPCSlave::GarfunkelIPCSlave() :
    ecolab::IPC("GarfunkelMCASlave", "GarfunkelUIMaster", 100)
{
    std::cout << "[Garfunkel Slave] IPC started..." << std::endl;
    init();
	std::cout << "[Garfunkel Slave] Init done..." << std::endl;
	GarfunkelCommandProcessor& cmdProc = GarfunkelCommandProcessor::Instance();
    cmdProc.InitializeCommandProcessor("GarfunkelUI", "GarfunkelMCA");
    std::cout << "[Garfunkel Slave] InitializeCommandProcessor...done" << std::endl;
    _ack.push_back((char)0x6);
    _nak.push_back((char)0x15);
}

/*!
    \brief    default destructor

    \param[in]  None

    \param[out] None

    \return     None

    \throw      None
*/
Garfunkel::GarfunkelIPCSlave::~GarfunkelIPCSlave()
{
    /* empty */
}

/*!
    \brief

    \param[in]  None

    \param[out] None

    \return     None

    \throw      None
*/
void Garfunkel::GarfunkelIPCSlave::init()
{
    //Finish the parameters to the data items here.

	boost::shared_ptr< Garfunkel::IIPCMessage > systemStateMessage(new Garfunkel::SystemStateMessage());
	boost::shared_ptr< Garfunkel::IIPCMessage > opStateMessage(new Garfunkel::OperatingScheduleStatus());
	boost::shared_ptr< Garfunkel::IIPCMessage > mkStateMessage(new Garfunkel::MakeDownProcessStateMessage());
    boost::shared_ptr< Garfunkel::IIPCMessage > alarmState(new Garfunkel::AlarmStatusMessage());
    boost::shared_ptr< Garfunkel::IIPCMessage > enableDiagnostics(new Garfunkel::EnableDiagnosticsMessage());
    boost::shared_ptr< Garfunkel::IIPCMessage > diagnostics(new Garfunkel::DiagnosticsMessage());
    boost::shared_ptr< Garfunkel::IIPCMessage > dispActiveMessage(new Garfunkel::DispenseActiveStateMessage());
    boost::shared_ptr< Garfunkel::IIPCMessage > layupModeMessage(new Garfunkel::LayupModeStateMessage());
	boost::shared_ptr< Garfunkel::IIPCMessage > stndbyStatusMessage(new Garfunkel::StandbyModeMessage());
    boost::shared_ptr< Garfunkel::IIPCMessage > unitOfMeasure(new Garfunkel::UnitOfMeasure());
    boost::shared_ptr< Garfunkel::IIPCMessage > gioBoardDIMessage(new Garfunkel::GarfunkelIOBoardDIMessage());
	boost::shared_ptr< Garfunkel::IIPCMessage > sioBoardDIMessage(new Garfunkel::SimonIOBoardDIMessage());
    boost::shared_ptr< Garfunkel::IIPCMessage > applicationDI(new Garfunkel::ApplicationDIMessage());
    boost::shared_ptr< Garfunkel::IIPCMessage > condorDI(new Garfunkel::CondorDIMessage());
	boost::shared_ptr< Garfunkel::IIPCMessage > noOfMachines(new Garfunkel::NoOfMachinesMessage());
	boost::shared_ptr< Garfunkel::IIPCMessage > noOfPumps(new Garfunkel::NoOfPumpsMessage());
	boost::shared_ptr< Garfunkel::IIPCMessage > ackAlarm(new Garfunkel::AckAlarmMessage());
	boost::shared_ptr< Garfunkel::IIPCMessage > dbSyncMessage(new Garfunkel::DBSyncStateMessage());
	
    RegisterCallback("DU:40", systemStateMessage); //done
	RegisterCallback("DU:41", opStateMessage); //done
	RegisterCallback("DU:42", mkStateMessage); //done
	RegisterCallback("SU:51", diagnostics);//
	RegisterCallback("DU:50","SU:50", enableDiagnostics); //done
	RegisterCallback("DU:51","SU:51", diagnostics);//
	RegisterCallback("DU:43", dispActiveMessage);
    RegisterCallback("DU:44", "SU:44", layupModeMessage); //
	RegisterCallback("DU:45", "SU:45", stndbyStatusMessage); //
	RegisterCallback("DU:85", gioBoardDIMessage); //done
	RegisterCallback("DU:86", sioBoardDIMessage);// done
	RegisterCallback("DU:87", condorDI);// done
	//RegisterCallback("DU:54", dispenseInfo); //done - sends signal no, active pump, next pump for the requested machine
	//SU - 58 for Prime/calib/diagnostic errors
	//RegisterCallback("DU:61", alarmState);
	//RegisterCallback("DU:63", "SU:63", ackAlarm ); /
	RegisterCallback("DU:84", applicationDI);// done

}

/*!
    \brief

    \param[in]  None

    \param[out] None

    \return     None

    \throw      None
*/
void Garfunkel::GarfunkelIPCSlave::SendESPCommandResponse(const std::string &message)
{
    /* fill a buffer with our message and send it off */
    ecolab::IPC::BufferT buffer(message.begin(), message.end());

    try
    {
        SendMessage(buffer);
    }
    catch(std::exception &e)
    {
        std::cout << "[Garfunkel] Resending..." << std::endl;
        SendMessage(buffer);
        std::cout << "[Garfunkel] Recovery complete." << std::endl;
    }
}

/*!
    \brief

    \param[in]  None

    \param[out] None

    \return     None

    \throw      None
*/
int Garfunkel::GarfunkelIPCSlave::ReceiveESPCommand()
{
    int                  retValue = 0;
    ecolab::IPC::BufferT buffer;
    std::string          message;

    if( True == IsMessageAvailable() )
    {
        /* receive message and convert to a string */
        ReceiveMessage(buffer);
        message.assign(buffer.begin(), buffer.end());

        // Process the message
        std::string         response;

        // split the message and process it.
        if(message.length() > 0 )
        {
        	GarfunkelCommandProcessor& cmdProcInstance = GarfunkelCommandProcessor::Instance();

            // Excute the message and send the response back
            if(False != cmdProcInstance.ExecuteESPCommand(message, response))
            {
                if(response.length() > 0)
                {
                    //std::cout << "[IPC] Send ESP Command Response: " << response << std::endl;
                    SendESPCommandResponse(response);
                }
            }
        }
    }
    else
    {
        // Do nothing
    }

    return retValue;
}

/*!
    \brief

    \param[in]  None

    \param[out] None

    \return     None

    \throw      None
*/
int Garfunkel::GarfunkelIPCSlave::ReceiveESPCommandWithValidation()
{
    int                  retValue = 0;
    ecolab::IPC::BufferT buffer;
    std::string          message;

    if( True == IsMessageAvailable() )
    {
		
        /* receive message and convert to a string */
        ReceiveMessage(buffer);
        message.assign(buffer.begin(), buffer.end());
        // Process the message
        std::string                     response;
        ecolab::ESP::ESPStringCreate     espObject;
        std::cout << "[Received Message from UI]: " << message << std::endl;
        if(True == espObject.ConvertFromESPString(message))
        {
            std::stringstream   buffer;
            // split the message and process it.
            if(message.length() > 0 )
            {
            	GarfunkelCommandProcessor & cmdProcInstance = GarfunkelCommandProcessor::Instance();

                // Execute the message and send the response back
                if(False != cmdProcInstance.ExecuteESPCommand(message, response))
                {
                    if(response.length() > 0)
                    {
                        std::string     ack;
                        ack.push_back((char)0x6);

                        buffer << ack << response;
                        std::cout << "[GarfunkelIPCSlave] Send ESP Command Response: " << buffer.str() << std::endl;
                        SendESPCommandResponse(buffer.str());
                    }
                }
                else
                {
                    std::cout << "[GarfunkelIPCSlave] ESP Command execution failed" << std::endl;
                }
            }
        }
        else
        {
            std::string nak;
            nak.push_back((char)0x15);
            SendESPCommandResponse(nak);
        }
    }
    else
    {
        // Do nothing
    }

    return retValue;
}

BOOLEAN Garfunkel::GarfunkelIPCSlave::RegisterCallback(std::string command, boost::shared_ptr< Garfunkel::IIPCMessage > pMsg)
{
    BOOLEAN     ret = False;

    if (!command.empty())
    {
    	GarfunkelCommandProcessor & cmdProcInstance = GarfunkelCommandProcessor::Instance();

        std::cout << "[Garfunkel] Register ESP command: " << command << std::endl;
        ret = cmdProcInstance.AddCommand(command, pMsg);
    }
    return ret;
}

BOOLEAN Garfunkel::GarfunkelIPCSlave::RegisterCallback(std::string command1, std::string command2, boost::shared_ptr< Garfunkel::IIPCMessage > pMsg)
{
    BOOLEAN     retCommand1 = False;
    BOOLEAN     retCommand2 = False;

    retCommand1 = RegisterCallback(command1, pMsg);
    retCommand2 = RegisterCallback(command2, pMsg);

    return ((BOOLEAN)(retCommand1 && retCommand2));
}

////////////////////////////////////////////////////////////////////////
//

Garfunkel::GarfunkelIPCMaster::GarfunkelIPCMaster() :
    ecolab::IPC("GarfunkelMCAMaster", "GarfunkelUISlave", 100)
{
    _ack.push_back((char)0x6);
    _nak.push_back((char)0x15);

    std::cout << "[Garfunkel Master] IPC started..." << std::endl;
}

Garfunkel::GarfunkelIPCMaster::GarfunkelIPCMaster(const GarfunkelIPCMaster & objectToCopy) :
    ecolab::IPC("GarfunkelMCAMaster", "GarfunkelUISlave")
{
    _ack = objectToCopy._ack;
    _nak = objectToCopy._nak;
}

Garfunkel::GarfunkelIPCMaster::~GarfunkelIPCMaster()
{
}

void Garfunkel::GarfunkelIPCMaster::SendESPCommandResponse(std::string &message)
{
    ecolab::ESP::ESPStringCreate    createString;
    createString.ConvertToESPString(message);

    /* fill a buffer with our message and send it off */
    ecolab::IPC::BufferT buffer(message.begin(), message.end());

    try
    {
        SendMessage(buffer);
    }
    catch(std::exception &e)
    {
        std::cout << "[Garfunkel] Resending..." << std::endl;
        SendMessage(buffer);
        std::cout << "[Garfunkel] Recovery complete." << std::endl;
    }
}

Garfunkel::GarfunkelIPCMaster&  Garfunkel::GarfunkelIPCMaster::Instance()
{
    static GarfunkelIPCMaster singleton;
    return singleton;
}

BOOLEAN Garfunkel::GarfunkelIPCMaster::ReceiveESPCommandWithValidation()
{
    BOOLEAN              lookForMessage = True;
    BOOLEAN              retValue = False;
    ecolab::IPC::BufferT buffer;
    std::string          message;
    timespec             initial;
    timespec             Now;
    GarfunkelData& AqData = GarfunkelData::Instance();
    
    clock_gettime(CLOCK_MONOTONIC, &initial);
    
    while(True == lookForMessage)
    {
        if(True == IsMessageAvailable())
        {        
            // receive message and convert to a string
            ReceiveMessage(buffer);
            message.assign(buffer.begin(), buffer.end());
            // Process the message
            // Check if the first character is a ACK.
			 std::cout << "Recived a message : " << std::endl;
            if(_ack[0] == message[0])
            {
                // Erase the first character
                message = message.erase(0, 1);
                if(True == _espString.ConvertFromESPString(message))
                {
                    // Validate that OK was returned
                    std::string     address;
                    size_t          pos = std::string::npos;
                    char            charToFind = ':';

                    pos = message.find(charToFind);

                    if(std::string::npos != pos)
                    {
                        address = message.substr(0, pos - 1);
                        if(address.compare(AqData._uiAddressInstance) == 0)
                        {
                            // Now check if value is OK
                            std::string   temp = "OK";
                            std::string   str1;
                            size_t        nextPos = std::string::npos;

                            nextPos = message.find(charToFind, pos + 1);
                            if(std::string::npos != nextPos)
                            {
                                str1 = message.substr(pos + 1, nextPos - 1);
                                if(True == boost::iequals(temp,str1))
                                {
                                    retValue = True;
                                }
                            }
                        }
                    }
                }
                else
                {
                    // Error with the string
                }
            }
            else
            {
                retValue = False;
            }
            
            lookForMessage = False;
        }
        else
        {
            // If a message is not found timeout after ~10 seconds
            clock_gettime(CLOCK_MONOTONIC, &Now);
            if(ElapsedTime(&initial, &Now) >= IPC_MESSAGE_TIMEOUT)
            {
                lookForMessage = False;
            }
            
            sleep(1);
        }
    }
    return retValue;
}

void    Garfunkel::GarfunkelIPCMaster::ClearTheReceiveQueue()
{
    ecolab::IPC::BufferT buffer;       

    do
    {
        if(True == IsMessageAvailable())
        {
            // receive message and convert to a string
            ReceiveMessage(buffer);
        }
    }
    while( True == IsMessageAvailable() );
}


////////////////////////////////////////////////////////////////////////
//

Garfunkel::GarfunkelIPCSlaveCommunication::GarfunkelIPCSlaveCommunication(const std::string & name) : Thread(name)
{
}

Garfunkel::GarfunkelIPCSlaveCommunication::~GarfunkelIPCSlaveCommunication()
{
}

int Garfunkel::GarfunkelIPCSlaveCommunication::Run()
{
    std::cout << "Garfunkel IPC monitoring thread is starting" << std::endl;

    /*
        Garfunkel communication IPC
    */
    Garfunkel::GarfunkelIPCSlave     GarfunkelIPC;
    Garfunkel::GarfunkelData & GarfunkelData = Garfunkel::GarfunkelData::Instance();

    try
    {
        while(True)
        {
            GarfunkelIPC.ReceiveESPCommandWithValidation();
			sleep(75);
			//std::cout << "GarfunkelIPC thread" << std::endl;
        }
    }
    catch(std::exception &  e)
    {
        std::cout << "Exception caught [GarfunkelIPC] : " << e.what() << std::endl;
        std::cout << "Exiting" << std::endl;
        GarfunkelData._continueRunning.Set(False);
    }

    return 0;
}

void Garfunkel::GarfunkelIPCSlaveCommunication::Cleanup()
{
    std::cout << Name() << "Exiting thread..." << std::endl;
}
