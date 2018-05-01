#include "abstractcommandprocessor.h"
#include "DBAccess.h"
#include "IPCCommand.h"
#include "abstractipcmessage.h"

//=================================================================================================
//!
//!    \brief      AbstractCommandProcessor CONSTRUCTOR
//!                
//!    \param[in]  None
//!                
//!    \param[out] None
//!                
//!    \return     None
//!                
//!    \throw      None
//=================================================================================================
AbstractCommandProcessor::AbstractCommandProcessor()
{
    _addressInstance = "Oa";  // This is just temporary
}

//=================================================================================================
//!
//!    \brief      AbstractCommandProcessor DESTRUCTOR
//!                
//!    \param[in]  None
//!                
//!    \param[out] None
//!                
//!    \return     None
//!                
//!    \throw      None
//=================================================================================================
AbstractCommandProcessor::~AbstractCommandProcessor()
{
    // Clean up the command map
    if(!_commandMap.empty())
    {
        std::map<std::string, boost::shared_ptr< AbstractIPCMessage > >::iterator  begin;
        std::map<std::string, boost::shared_ptr< AbstractIPCMessage > >::iterator  end;
        
        begin = _commandMap.begin();
        end = _commandMap.end();
        
        _commandMap.erase(begin, end);
    }
}
        
//=================================================================================================
//!
//!    \brief    
//!                
//!    \param[in]  None
//!                
//!    \param[out] None
//!                
//!    \return     None
//!                
//!    \throw      None
//=================================================================================================
bool
AbstractCommandProcessor::executeESPCommand(std::string& command, std::string& output)
{
    Q_UNUSED(output);
    BOOLEAN             retValue = False;
    IPCCommand          cmd(command);
/*   
 std::cout << "Full Command: " << cmd.GetFullCommand() << std::endl;
 std::cout << "Address: " << cmd.GetAddress() << std::endl;
 std::cout << "Instance: " << cmd.GetInstance() << std::endl;
 std::cout << "Address & instance: " << cmd.GetAddressAndInstance() << std::endl;

 std::cout << "Command & Sub Command: " << cmd.GetCommandAndSubCommand() << std::endl;
 std::cout << "Command: " << cmd.GetCommand() << std::endl;
 std::cout << "Sub Command: " << cmd.GetSubCommand() << std::endl;
 std::cout << "Payload: " << cmd.GetPayload() << std::endl;
 //std::vector<std::string> pl = cmd.GetPayloadList();
 //std::cout << "Payload List - length(" << pl.size() << "): "; 
 //int i; for (i=0;i<pl.size();i++) std::cout << pl[i] << " "; std::cout << std::endl;
 std::cout << "Address Valid: " << cmd.IsAddressValid(_addressInstance) << std::endl;
*/

    return retValue;
}

//=================================================================================================
//!
//!    \brief    
//!                
//!    \param[in]  None
//!                
//!    \param[out] None
//!                
//!    \return     None
//!                
//!    \throw      None
//=================================================================================================
int
AbstractCommandProcessor::initializeCommandProcessor(const std::string&  database, const std::string& databaseItem)
{
    int                     retValue = 0;
    ecolab::DB::DBAccess    myDBAccess;
    ecolab::DB::DataSet     myDataSet;
    std::string             connectString;
            
    // Use of the connection string.
    connectString = "dbname = '" + database + "' user = db_controller password = controller";
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
                    }
                }
            }
            catch(std::exception e)
            {
                std::cout << "Address and Instance database call failed: " << e.what() << std::endl;
            }
        }

        myDBAccess.DBDisconnect();
    }    
    
    setAddress(_addressInstance);

    return retValue;
}

//=================================================================================================
//!
//!    \brief      addCommand
//!                
//!    \param[in]  None
//!                
//!    \param[out] None
//!                
//!    \return     None
//!                
//!    \throw      None
//=================================================================================================
bool
AbstractCommandProcessor::addCommand(const std::string command, boost::shared_ptr<AbstractIPCMessage >msg)
{
    bool ret = False;
    
    if (msg != 0)
    {
        _commandMap.insert( std::pair<std::string, boost::shared_ptr< AbstractIPCMessage > > (command, msg));
        ret = True;
    }
    
    return ret;
}

//=================================================================================================
//!
//!    \brief      setAddress
//!                
//!    \param[in]  None
//!                
//!    \param[out] None
//!                
//!    \return     None
//!                
//!    \throw      None
//=================================================================================================
void
AbstractCommandProcessor::setAddress(const std::string & address)
{ 
    _addressInstance = address;
}


