#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <map>
#include "GarfunkelCommandProcessor.h"
#include "DBAccess.h"
#include "IPCCommand.h"
#include "GarfunkelData.h"

Garfunkel::GarfunkelCommandProcessor::GarfunkelCommandProcessor()
{
    _addressInstance = "Oa";  // This is just temporary
}

Garfunkel::GarfunkelCommandProcessor::~GarfunkelCommandProcessor()
{
    // Clean up the command map
    if(!_commandMap.empty())
    {
		std::cout << "delete command processor map" << std::endl;    
        std::map<std::string, boost::shared_ptr< Garfunkel::IIPCMessage > >::iterator  begin;
        std::map<std::string, boost::shared_ptr< Garfunkel::IIPCMessage > >::iterator  end;
        
        begin = _commandMap.begin();
        end = _commandMap.end();
        
        _commandMap.erase(begin, end);
    }
}
        
BOOLEAN Garfunkel::GarfunkelCommandProcessor::ExecuteESPCommand(std::string & command, std::string &    output)
{
    BOOLEAN             retValue = False;
    IPCCommand          cmd(command);
/*
std::cout << "Main Command processor" << std::endl;   
 std::cout << "Full Command: " << cmd.GetFullCommand() << std::endl;
 std::cout << "Address: " << cmd.GetAddress() << std::endl;
 std::cout << "Instance: " << cmd.GetInstance() << std::endl;
 std::cout << "Address & instance: " << cmd.GetAddressAndInstance() << std::endl;

 std::cout << "Command & Sub Command:" << cmd.GetCommandAndSubCommand() << ":End Command" << std::endl;
 std::cout << "Command: " << cmd.GetCommand() << std::endl;
 std::cout << "Sub Command: " << cmd.GetSubCommand() << std::endl;
 std::cout << "Payload: " << cmd.GetPayload() << std::endl;
 //std::vector<std::string> pl = cmd.GetPayloadList();
 //std::cout << "Payload List - length(" << pl.size() << "): "; 
 //int i; for (i=0;i<pl.size();i++) std::cout << pl[i] << " "; std::cout << std::endl;
 std::cout << "Address Valid: " << cmd.IsAddressValid(_addressInstance) << std::endl;
*/
    try
    {
        if (True == cmd.IsAddressValid(_addressInstance))
        {
            boost::shared_ptr< Garfunkel::IIPCMessage > msg;
            std::map<std::string, boost::shared_ptr< Garfunkel::IIPCMessage > >::iterator    foundCmd;
            //std::cout << "[CommandProcessor] IsAddressValid" << std::endl;

            foundCmd = _commandMap.find(cmd.GetCommandAndSubCommand());
            if(foundCmd != _commandMap.end())
            {
                if(NULL != foundCmd->second)
                {     
                    //std::cout << "Key:" << foundCmd->first << std::endl;
                    msg = foundCmd->second;
                    if(msg.get() != NULL)
                    {
                        if (True == (msg->ProcessMessage(cmd, output))) 
                        {
                            retValue = True;
                        }
                    }
                }
                else
                {
                  std::cout << "[CommandProcessor] Command Not Found -- Command: " << cmd.GetCommandAndSubCommand() << std::endl;

                }
            }
            else
            	std::cout << "[CommandProcessor] NOt found= " << cmd.GetCommandAndSubCommand() << std::endl;
        }
    }
    catch(std::exception & e)
    {
        std::cout << "Command Processor IPC: Error retrieve message to process: " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "Message not found" << std::endl;
    }
   
    if (False == retValue || output.length() <= 0)
    {
    	std::cout << "[CommandProcessor] invalid message -- return value: " << retValue << " output: " << output << " length: " << output.length() << std::endl;
        output = cmd.GetAddressAndInstance() + ":ERR1:";
        ecolab::ESP::ESPStringCreate    createString;
        createString.ConvertToESPString(output);
        retValue = True;    
    }
    
    return retValue;
}

int     Garfunkel::GarfunkelCommandProcessor::InitializeCommandProcessor(const std::string &  database, const std::string & databaseItem)
{
    int                     retValue = 0;
    ecolab::DB::DBAccess    myDBAccess;
    ecolab::DB::DataSet     myDataSet;
    std::string             connectString;
    GarfunkelData& AqData = GarfunkelData::Instance();

    connectString = "dbname = Garfunkel user = db_controller password = controller";
    if(myDBAccess.DBConnect(connectString) == True)
    {    
        std::string        execute;
        execute = "SELECT * FROM GetControllerData('" + databaseItem + "');";

        if(myDBAccess.DBExecuteStored(execute, myDataSet) == True)
        {
            // Get the port data back out from the stored function execution
            int                                numRows = 0;
            ecolab::DB::DataRow             myRow;
            boost::shared_ptr<ecolab::DB::IColumnData>    colData;
            
            numRows = myDataSet.GetNumberOfRows();
            try
            {
                if(numRows == 1)
                {
                    //  There should only be one row.
                    ecolab::DB::DataRow             myRow;

                    // Get the first row only.
                    myRow = myDataSet.GetRow(0);

                    // There should be two columns returned                
                    std::string address;
                    std::string instance;
                    
                    colData = myRow.GetColumn("Address");
                    if(colData.get() != NULL)
                    {
                        colData->AsString(address);
                    }
                    
                    colData = myRow.GetColumn("Instance");
                    if(colData.get() != NULL)
                    {
                        colData->AsString(instance);
                    }
                    
                    // Combine the address and the instance
                    if(!instance.empty() && !address.empty())
                    {
                        _addressInstance = address + instance;
                        AqData._uiAddressInstance.assign(_addressInstance);
                        std::cout<<"CommandProcessor: AddresInstance ="<< _addressInstance<<std::endl;
                        retValue = 1;
                    }
                }
            }
            catch(std::exception & e)
            {
                std::cout << "Address and Instance database call failed: " << e.what() << std::endl;
            }
        }

        myDBAccess.DBDisconnect();


    }

	if (retValue)
	{
        /*
            Write the  data to a flat file.
        */
		WriteUIAddressesToFile();
	}
	else
    {
	    /*
	        Database  data are not available.
	        Read the  data from the flat file.
	    */
		std::cout << "Read UI address from a flat file" << std::endl;
		retValue = ReadUIAddressestFromFile();
    }



    return retValue;
}



BOOLEAN Garfunkel::GarfunkelCommandProcessor::ReadUIAddressestFromFile()
{
	BOOLEAN retValue = False;
    std::fstream    valuesRead("/usr/local/applications/Garfunkel-uiaddress.txt", std::ios_base::in );
    Garfunkel::GarfunkelData& AqData = Garfunkel::GarfunkelData::Instance();
    if(True == valuesRead.is_open())
    {
        std::string  StrValue;
       	valuesRead >> StrValue;
       	_addressInstance = StrValue;
       	AqData._uiAddressInstance.assign(StrValue);
       	std::cout<<"ReadUIAddressestFromFile :addressInstance="<<AqData._uiAddressInstance<<std::endl;
        retValue = True;
        valuesRead.close();
    }
    else
    {
        std::cout << "ERROR: Can't open Garfunkel-ioboardaddress.txt." << std::endl;
    }

    return retValue;
}


BOOLEAN Garfunkel::GarfunkelCommandProcessor::WriteUIAddressesToFile()
{

    BOOLEAN         retValue = False;
    Garfunkel::GarfunkelData& AqData = Garfunkel::GarfunkelData::Instance();
    std::fstream    valuesWrite("/usr/local/applications/Garfunkel-uiaddress.txt", std::ios_base::trunc | std::ios_base::out);

    if(True == valuesWrite.is_open())
    {
        std::string  StrValue;
        StrValue = AqData._uiAddressInstance;
        valuesWrite << StrValue << std::endl;
        valuesWrite.close();
        retValue = True;
    }
    return retValue;
}


BOOLEAN Garfunkel::GarfunkelCommandProcessor::AddCommand(const std::string command, boost::shared_ptr< Garfunkel::IIPCMessage > pMsg)
{
    BOOLEAN ret = False;
    
    if (pMsg != NULL)
    {
        _commandMap.insert(std::pair<std::string, boost::shared_ptr< Garfunkel::IIPCMessage > >(command, pMsg));
        ret = True;
    }
    
    return ret;
}

/*!
	\brief	A Singleton that represents an instance of the CommandProcessor
                
    \param[in]  None
                
    \param[out] None
                
    \return     CommandProcessor - a reference to the ESP factory
                
    \throw      None
*/			
Garfunkel::GarfunkelCommandProcessor&	Garfunkel::GarfunkelCommandProcessor::Instance()
{
	static GarfunkelCommandProcessor singleton;
	return singleton;
}


////////////////////////////////////////////////////////////////////////////////
//  IO Board Command Processor
Garfunkel::GarfunkelCommandProcessorIOBoard::GarfunkelCommandProcessorIOBoard()
{
}

Garfunkel::GarfunkelCommandProcessorIOBoard::~GarfunkelCommandProcessorIOBoard()
{
    // Clean up the command map
    if(!_commandMap.empty())
    {
        std::map<std::string, boost::shared_ptr< Garfunkel::IIOBoardMessage > >::iterator  begin;
        std::map<std::string, boost::shared_ptr< Garfunkel::IIOBoardMessage > >::iterator  end;
        
        begin = _commandMap.begin();
        end = _commandMap.end();
        
        _commandMap.erase(begin, end);
    }
}

        
BOOLEAN Garfunkel::GarfunkelCommandProcessorIOBoard::ExecuteCommand(const std::string  command, boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485, BOOLEAN override)
{
    BOOLEAN             retValue = False;
    boost::shared_ptr< Garfunkel::IIOBoardMessage > msg;

    try
    {
        std::map<std::string, boost::shared_ptr< Garfunkel::IIOBoardMessage > >::iterator    foundCmd;
             
        foundCmd = _commandMap.find(command);  
        if(foundCmd != _commandMap.end())
        {
            if(NULL != foundCmd->second)
            {     
                msg = foundCmd->second;
                if(msg.get() != NULL)
                {
                    if (((True == msg->IsMessageRunable(False)) || (True == override))
						&& (msg->Execute(pSocketRS485) >= 0)) 
                    {
                        retValue = True;
                    }
                }
            }
            else
            {
            	std::cout << "[CommandProcessor] Command Not Found -- Command: " << command << std::endl;

            }
        }
    }
    catch(std::exception & e)
    {
        std::cout << "Command Processor IO Board Error retrieve message to process: " << e.what() << " : " << msg->GetCommandName() << std::endl;
    }
       
    return retValue;	
}

void    Garfunkel::GarfunkelCommandProcessorIOBoard::EnableCommand(const std::string  command)
{
    try
    {
        boost::shared_ptr< Garfunkel::IIOBoardMessage > msg;
        std::map<std::string, boost::shared_ptr< Garfunkel::IIOBoardMessage > >::iterator    foundCmd;
             
        foundCmd = _commandMap.find(command);       
        if(NULL != foundCmd->second && foundCmd != _commandMap.end())
        {     
            msg = foundCmd->second;
            if(msg.get() != NULL)
            {
std::cout << "Enable command: " << msg->GetCommandName() << std::endl;            
                msg->SetMessageToRun(True);
            }
        }
        else
        {
std::cout << "[Board CommandProcessor] Command Not Found -- Command: " << command << std::endl;

        }
    }
    catch(std::exception & e)
    {
        std::cout << "Board Command process command not found: " << e.what() << std::endl;

    }
}

void    Garfunkel::GarfunkelCommandProcessorIOBoard::DisableCommand(const std::string command)
{
    try
    {
        boost::shared_ptr< Garfunkel::IIOBoardMessage > msg;
        std::map<std::string, boost::shared_ptr< Garfunkel::IIOBoardMessage > >::iterator    foundCmd;
             
        foundCmd = _commandMap.find(command);       
        if(NULL != foundCmd->second && foundCmd != _commandMap.end())
        {     
            msg = foundCmd->second;
            if(msg.get() != NULL)
            {
std::cout << "Disable command: " << msg->GetCommandName() << std::endl;       
                msg->SetMessageToRun(False);
            }
        }
        else
        {
std::cout << "[Board CommandProcessor] Command Not Found -- Command: " << command << std::endl;                
        }
    }
    catch(std::exception & e)
    {
        std::cout << "Board Command process command not found: " << e.what() << std::endl;
    }
}

boost::shared_ptr< Garfunkel::IIOBoardMessage > Garfunkel::GarfunkelCommandProcessorIOBoard::GetCommand(const std::string  command)
{
    boost::shared_ptr< Garfunkel::IIOBoardMessage > msg;

    try
    {
        std::map<std::string, boost::shared_ptr< Garfunkel::IIOBoardMessage > >::iterator    foundCmd;
             
        foundCmd = _commandMap.find(command);       
        if(NULL != foundCmd->second && foundCmd != _commandMap.end())
        {     
            msg = foundCmd->second;
        }
        else
        {
std::cout << "[Board CommandProcessor] Command Not Found -- Command: " << command << std::endl;                
        }
    }
    catch(std::exception & e)
    {
        std::cout << "Board Command process command not found: " << e.what() << std::endl;
    }
    
    return msg;
}

int     Garfunkel::GarfunkelCommandProcessorIOBoard::InitializeCommandProcessor(const std::string &  database, const std::string & databaseItem)
{
	//does nothing
    return 0;
}
    
BOOLEAN Garfunkel::GarfunkelCommandProcessorIOBoard::AddCommand(const std::string command, boost::shared_ptr< Garfunkel::IIOBoardMessage > pMsg)
{
    BOOLEAN ret = False;
    
    if (pMsg != NULL)
    {
        _commandMap.insert(std::pair<std::string, boost::shared_ptr< Garfunkel::IIOBoardMessage > >(command, pMsg));
        ret = True;
    }
    
    return ret;
}

Garfunkel::GarfunkelCommandProcessorIOBoard&	Garfunkel::GarfunkelCommandProcessorIOBoard::Instance()
{
    static GarfunkelCommandProcessorIOBoard  singleton;
    return singleton;
}



