#include <bitset>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "GarfunkelData.h"
#include "GarfunkelIPC.h"
#include "GarfunkelEnums.h"
#include "BoardCommands.h"
#include "ElapsedTime.h"
#include "IOBoardMessages.h"

using namespace Garfunkel;
/////////////////////////////////////////////////////////////////////////////
// ConfigureIOBoard message from the IO Board
/////////////////////////////////////////////////////////////////////////////

Garfunkel::ConfigureIOBoard::ConfigureIOBoard(std::string & addressInstance) :
    IIOBoardMessage(addressInstance)
{
    _runCommand = True;
    _commandName = "DI";
}

Garfunkel::ConfigureIOBoard::~ConfigureIOBoard()
{
}

int Garfunkel::ConfigureIOBoard::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{

    // This will be all calls to the IO Board to do the setup.
    int     retValue = -1;
    return retValue;

}



BOOLEAN Garfunkel::ConfigureIOBoard::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::ConfigureIOBoard::HandleIPCResponse(std::string &     response)
{
    return -1;
}


/////////////////////////////////////////////////////////////////////////////
// Get DI message from the IO Board
/////////////////////////////////////////////////////////////////////////////

Garfunkel::DIBoardMessage::DIBoardMessage(std::string & addressInstance) :
    IIOBoardMessage(addressInstance)
{
    _runCommand = True;
    _commandName = "DI";
}

Garfunkel::DIBoardMessage::~DIBoardMessage()
{
}

int Garfunkel::DIBoardMessage::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = 0;
    std::string message;
    std::string response;

    message.clear();
    response.clear();
    message = _addressInstance + ":DI:";
    retValue = SendMessage(pSocketRS485, message, response);

    GarfunkelData& GfData = GarfunkelData::Instance();
    if(retValue>0)
    {
        clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);

        GfData._ioBoardDIString = response;
        _runCommand = False;  //Run only once

    }
    return retValue;
}

BOOLEAN Garfunkel::DIBoardMessage::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::DIBoardMessage::HandleIPCResponse(std::string &     response)
{
    return -1;
}

/////////////////////////////////////////////////////////////////////////////
// Get temp and conductivity from the IO Board
/////////////////////////////////////////////////////////////////////////////

Garfunkel::GetAnalogSensorDatafromGIOB::GetAnalogSensorDatafromGIOB(std::string & addressInstance) :
		IIOBoardTimedMessage(addressInstance)
{
    _runCommand = True;
    _commandName = "DU:42";
    SetTimeInterval(1); //read every 2 sec
}

Garfunkel::GetAnalogSensorDatafromGIOB::~GetAnalogSensorDatafromGIOB()
{
}

int Garfunkel::GetAnalogSensorDatafromGIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
    GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
    message.clear();
    response.clear();

	message = _addressInstance + ":DU:42:";  //get temp, conductivity and other analog data

    retValue = SendMessage(pSocketRS485, message, response);
    //std::cerr << "Garfunkel::GetAnalogSensorDatafromIOB"<<": retval = "<<retValue<< std::endl;
    //std::cout << "GetTempAndConductivityfromIOB : Response = " << response << std::endl;
	if(retValue >= 0)
    {
		//std::cout << "GetTempAndConductivityfromIOB : Response = " << response << std::endl;
        clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
        IPCReturnCommand   cmdResponse(response);
		std::vector<std::string>::iterator      itemsIter;
        std::vector<std::string>                items;
		std::string tempInString, condInString, tempHexString;
        float temp = 0;
        float cond = 0;
        float an1  = 0, an2 = 0, an3 = 0, an4 = 0;

        items = cmdResponse.GetPayloadList();
        if(items.size() > 0&&(GfData._dBSyncInProgress.Get()==False ||  GfData._alarmHandlerSleeping.Get()==False))
        {
        	SystemData& SysData = SystemData::Instance();
        	itemsIter = items.begin();
        	if(itemsIter != items.end())
        	{
        			tempHexString = (std::string)(*itemsIter);
        			cond = FromHex(tempHexString);
            		++itemsIter;
            		if(itemsIter != items.end())
            		{
            			tempHexString = (std::string)(*itemsIter);
            			temp = FromHex(tempHexString);


            			SysData.TempInDegreeF.Set(temp);
            			SysData.Conductivity.Set(cond);
            			//std::cout << "GetAnalogSensorDatafromIOB : TempInDegreeF = " << SysData.TempInDegreeF.Get()<< std::endl;
            			//std::cout << "GetAnalogSensorDatafromIOB : Conductivity = " << SysData.Conductivity.Get() << std::endl;

                		++itemsIter;
                		if(itemsIter != items.end())
                		{
                			tempHexString = (std::string)(*itemsIter);
                			an1 = FromHex(tempHexString);

                    		++itemsIter;
                    		if(itemsIter != items.end())
                    		{
                    			tempHexString = (std::string)(*itemsIter);
                    			an2 = FromHex(tempHexString);

                        		++itemsIter;
                        		if(itemsIter != items.end())
                        		{
                        			tempHexString = (std::string)(*itemsIter);
                        			an3 = FromHex(tempHexString);

                            		++itemsIter;
                            		if(itemsIter != items.end())
                            		{
                            			tempHexString = (std::string)(*itemsIter);
                            			an4 = FromHex(tempHexString);

                            			SysData.Analog1.Set(an1);
                            			SysData.Analog2.Set(an2);
                            			SysData.Analog3.Set(an3);
                            			SysData.Analog4.Set(an4);
                            			/*std::cout << "GetAnalogSensorDatafromIOB : Analog1 = " << SysData.Analog1.Get()<< std::endl;
                            			std::cout << "GetAnalogSensorDatafromIOB : Analog2 = " << SysData.Analog2.Get() << std::endl;
                            			std::cout << "GetAnalogSensorDatafromIOB : Analog3 = " << SysData.Analog3.Get()<< std::endl;
                            			std::cout << "GetAnalogSensorDatafromIOB : Analog4 = " << SysData.Analog4.Get() << std::endl;*/

                            		}
                        		}
                    		}
                		}


            	}
        	}

        }


    }

	return retValue;
}

BOOLEAN Garfunkel::GetAnalogSensorDatafromGIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::GetAnalogSensorDatafromGIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}


Garfunkel::GetDigitalInputOutputStatefromGIOB::GetDigitalInputOutputStatefromGIOB(std::string & addressInstance) :
		IIOBoardTimedMessage(addressInstance)
{
    _runCommand = True;
    _commandName = "DU:41";
    SetTimeInterval(1); //read every 2 sec
}

Garfunkel::GetDigitalInputOutputStatefromGIOB::~GetDigitalInputOutputStatefromGIOB()
{
}

int Garfunkel::GetDigitalInputOutputStatefromGIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
    GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
	std::vector<std::string>::iterator      itemsIter;
    std::vector<std::string>                items;

    message.clear();
    response.clear();

	message = _addressInstance + ":DU:41:";  //valve state for all washers

    retValue = SendMessage(pSocketRS485, message, response);
    //std::cerr << "Garfunkel::GetDigitalInputOutputStatefromIOB"<<": retval = "<<retValue<< std::endl;
	if(retValue >= 0)
    {
		std::cout << "GetDigitalInputOutputStatefromIOB : Response = " << response << std::endl;
        clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
        IPCReturnCommand   cmdResponse(response);
		std::string        value;
		items = cmdResponse.GetPayloadList();
		//std::cout << "GetDigitalInputOutputStatefromIOB : items size= " << items.size() << std::endl;
        if(items.size() > 0&&(GfData._dBSyncInProgress.Get()==False ||  GfData._alarmHandlerSleeping.Get()==False))
        {
        	SystemData& SysData = SystemData::Instance();
        	itemsIter = items.begin();
        	if(itemsIter != items.end()) //get inputs
        	{

           		std::string inputs =  ((std::string)*itemsIter);

           		unsigned int temp = FromHex(inputs);
    			//std::cout << "GetDigitalInputOutputStatefromIOB : temp= " << temp << std::endl;

    			const std::bitset<16> State(temp);
    			std::vector<bool> i_state;

    			i_state.push_back(State.test(0));//reserved unused
    			i_state.push_back(State.test(1)); //a01
    			i_state.push_back(State.test(2)); //a02
    			i_state.push_back(State.test(3));//a03,
    			i_state.push_back(State.test(4));//a04
    			i_state.push_back(State.test(5));//a05
    			i_state.push_back(State.test(6));//a06
    			i_state.push_back(State.test(7));//a07
    			i_state.push_back(State.test(8));//a08..fault
    			i_state.push_back(State.test(9));//a09 ..fuse blown


    			SysData._Digital1.Set((i_state[1]==true) ? True : False);
    			SysData._Digital2.Set((i_state[2]==true) ? True : False);
    			//i_state[3]is Magnetic Filed CFP , ignore
    			SysData.SetOCapsuleLidState(0, (i_state[4]==true)?   eSwitchOpen : eSwitchClosed );
    			SysData.SetOCapsuleLidState(1, (i_state[5]==true)?   eSwitchOpen : eSwitchClosed );
    			//std::cout << "GetDigitalInputOutputStatefromIOB : O1 capsule lid status= " <<SysData.GetOCapsuleLidState(0) << std::endl;
    			//std::cout << "GetDigitalInputOutputStatefromIOB : O2 capsule lid status= " <<SysData.GetOCapsuleLidState(1) << std::endl;
    			SysData.SetBFWPumpState((i_state[6]==true || i_state[7]==true) ? eOn : eOff);
    			//std::cout << "GetDigitalInputOutputStatefromIOB : BFWP status= " <<SysData.GetBFWPumpState() << std::endl;
    			//std::cout << "Garfunkel : FAULT STATE = " << i_state[8] << std::endl;
    			SysData._GarfunkelIOBoardFaultLine.Set((i_state[8]==true) ? True : False);
          		++itemsIter;
            	if(itemsIter != items.end()) //get outputs
            	{

               		std::string outputs =  ((std::string)*itemsIter);
               		temp = FromHex(outputs);

        			const std::bitset<16> oState(temp);
        			std::vector<bool> o_state;
        			o_state.push_back(oState.test(0));//reserved unused
        			o_state.push_back(oState.test(1)); //a01
        			o_state.push_back(oState.test(2)); //a02
        			o_state.push_back(oState.test(3));//a03,
        			o_state.push_back(oState.test(4));//a04
        			o_state.push_back(oState.test(5));//a05

        			SysData.SetDilutionValveState((o_state[1]==true)? eOpen : eClose);
        			SysData.SetOCapsuleValveState(0, (o_state[2]==true)? eOpen : eClose);
        			SysData.SetOCapsuleValveState(1, (o_state[3]==true)? eOpen : eClose);
        			SysData.SetSumpValveState((o_state[4]==true)? eOpen : eClose);
        			SysData.SetDrainValveState((o_state[5]==true)? eOpen : eClose);
        			/*std::cout << "GetDigitalInputOutputStatefromIOB :DilutionValveState status= " <<SysData.GetDilutionValveState() << std::endl;
        			std::cout << "GetDigitalInputOutputStatefromIOB :O1 CapsuleValveState status= " <<SysData.GetOCapsuleValveState(0) << std::endl;
        			std::cout << "GetDigitalInputOutputStatefromIOB :O2 CapsuleValveState status= " <<SysData.GetOCapsuleValveState(1) << std::endl;
        			std::cout << "GetDigitalInputOutputStatefromIOB :SumpValveState status= " <<SysData.GetSumpValveState() << std::endl;
        			std::cout << "GetDigitalInputOutputStatefromIOB :DrainValveState status= " <<SysData.GetDrainValveState() << std::endl;*/

              		++itemsIter;
                	if(itemsIter != items.end()) //get led status
                	{
                   		std::string leds =  ((std::string)*itemsIter);
                   		temp = FromHex(leds);
            			const std::bitset<16> ledState(temp);
            			std::vector<bool> l_state;

            			l_state.push_back(ledState.test(0));//reserved unused
            			l_state.push_back(ledState.test(1)); //a01
            			l_state.push_back(ledState.test(2)); //a02

            			SysData.SetOCapsuleLEDStatus(0, (l_state[1]==true)? eOn :  eOff);
            			SysData.SetOCapsuleLEDStatus(1, (l_state[2]==true)? eOn :  eOff);
            			/*std::cout << "GetDigitalInputOutputStatefromIOB :O1 CapsuleLEDStatus status= " <<SysData.GetOCapsuleLEDStatus(0) << std::endl;
            			std::cout << "GetDigitalInputOutputStatefromIOB :O2 CapsuleLEDStatus status= " <<SysData.GetOCapsuleLEDStatus(1) << std::endl;*/
            			//TODO : Shilpa Check for open /close what they mean,
            			++itemsIter;
            		    if(itemsIter != items.end()) //get pump status
            		    {
            		    	std::string pumpSt =  ((std::string)*itemsIter);
            		        temp = FromHex(pumpSt);
            		        const std::bitset<16> pmpState(temp);
            		        std::vector<bool> p_state;
            		        p_state.push_back(pmpState.test(0));//reserved unused
            		        p_state.push_back(pmpState.test(1)); //51h, S OOP led

                			SysData.SetGarfunkelPumpState((p_state[1]==true)? eOn :  eOff);

            		    }


                	}



            	}


        	}


        }



    }

	return retValue;
}

BOOLEAN Garfunkel::GetDigitalInputOutputStatefromGIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::GetDigitalInputOutputStatefromGIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}




/////////////////////////////////////////////////////////////////////////////
// Get pump state from the IO Board
/////////////////////////////////////////////////////////////////////////////
//Get pump status for all pumps on IOBoard
Garfunkel::GetTreatmentPumpStatusfromSIOB::GetTreatmentPumpStatusfromSIOB(std::string & addressInstance) :
		IIOBoardTimedMessage(addressInstance)
{
    _runCommand = True;
    _commandName = "DG:03:0100:51:";
    SetTimeInterval(1); //read every 5 sec
}

Garfunkel::GetTreatmentPumpStatusfromSIOB::~GetTreatmentPumpStatusfromSIOB()
{
}

int Garfunkel::GetTreatmentPumpStatusfromSIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
    message.clear();
    response.clear();
    message = _addressInstance + ":DG:03:0100:51:"; //du for treatment pump
    retValue = SendMessage(pSocketRS485, message, response);
/*    std::cerr << "Garfunkel::GetPumpStatus"<<": response = "<<response<< std::endl;
    std::cerr << "Garfunkel::GetPumpStatus"<<": retValue = "<<retValue<< std::endl;*/
	if(retValue >= 0)
    {
		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastSimonIOBCommunication);

        IPCReturnCommand   cmdResponse(response);
		std::string        value;
        value = cmdResponse.GetPayloadWithoutWhiteSpace();
		if(value.length()>0&&(GfData._dBSyncInProgress.Get()==False ||  GfData._alarmHandlerSleeping.Get()==False))
		{
			SystemData& SysData = SystemData::Instance();
			unsigned int temp = FromHex(value);
			const std::bitset<16> oState(temp);
			std::vector<bool> o_state;
			o_state.push_back(oState.test(7));//on/off state
			SysData.SetTreatmentPumpState((o_state[0]==true)? eOn : eOff);
			//std::cerr << "Garfunkel::GetPumpStatus="<<SysData.GetTreatmentPumpState()<< std::endl;
		}

    }
    return retValue;
}

BOOLEAN Garfunkel::GetTreatmentPumpStatusfromSIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::GetTreatmentPumpStatusfromSIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}


#if 0

/////////////////////////////////////////////////////////////////////////////
// GetSolidProdDispenseInfoOnIOB
/////////////////////////////////////////////////////////////////////////////

Garfunkel::GetSolidProdDispenseInfoOnIOB::GetSolidProdDispenseInfoOnIOB(std::string & addressInstance) :
	IIOBoardTimedMessage(addressInstance)
{
    _runCommand = False;
    _commandName = "DU:40";
    SetTimeInterval(2); //check every 2 secs
}

void Garfunkel::GetSolidProdDispenseInfoOnIOB::GetSolidProdDispenseInfo(BOOLEAN yesNo)
{
	_getInfo = yesNo;
}

Garfunkel::GetSolidProdDispenseInfoOnIOB::~GetSolidProdDispenseInfoOnIOB()
{
}


int Garfunkel::GetSolidProdDispenseInfoOnIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;

    if(_getInfo==True)
    {
    	message.clear();
    	response.clear();
    	message = _addressInstance + ":DU:40:";
    	retValue = SendMessage(pSocketRS485, message, response);
    	if(retValue >= 0)
    	{
    		std::cerr << "GetSolidProdDispenseInfoOnIOB response= " << response << std::endl;
    		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
    		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
    		std::string        value;
    		REAL64 rstate;

    		IPCReturnCommand   cmdResponse(response);
    		std::vector<std::string>::iterator      itemsIter;
    		std::vector<std::string>                items;
    		std::string tempInString, condInString;
    		float temp = 0;
    		float cond = 0;
    		float dispRate = 0, amountDisp=0;
    		BOOLEAN currentSolidOOPState = False;
    		items = cmdResponse.GetPayloadList();
    		if(items.size() > 0&&(GfData._dBSyncInProgress.Get()==False ||  GfData._alarmHandlerSleeping.Get()==False))
    		{
    			SystemData& SysData = SystemData::Instance();
    			itemsIter = items.begin();
    			if(itemsIter != items.end())
    			{
    				temp = boost::lexical_cast<float > ((std::string)*itemsIter);
    				++itemsIter;
    				if(itemsIter != items.end())
    				{
    					cond = boost::lexical_cast<float> ((std::string)*itemsIter);
    					SysData.TempInDegreeF.Set(temp);
    					SysData.Conductivity.Set(cond);
    					++itemsIter;
    					if(itemsIter != items.end())
    					{
    						dispRate = boost::lexical_cast<float > ((std::string)*itemsIter);
    						SysData.DispenseRate.Set(dispRate);
    						++itemsIter;
    						if(itemsIter != items.end())
    						{
    							amountDisp = boost::lexical_cast<float > ((std::string)*itemsIter);
    							SysData.TotalSolidAmountDispensed.Set(amountDisp);
                    			++itemsIter;
                    			if(itemsIter != items.end())
                    			{
                    				std::string value;
                    				value = ((std::string)*itemsIter);
                    				const std::bitset<1> oopState(value);

                    				SysData.CurrentSolidOOPState.Set((oopState.test(0)==true) ? True :False);
                    				++itemsIter; //skip low time for OOP
                    				++itemsIter;
                        			if(itemsIter != items.end())
                        			{
                        				value = ((std::string)*itemsIter);
                        				const std::bitset<1> disp(value);

                        				SysData.SolidDispenseOn.Set((disp.test(0)==true) ? True :False);
                        			}

                    			}

                			}

            			}
        			}
        		}
        	}
    	}
    }
    else
    {
    	std::cout<<"GetSolidProdDispenseInfoOnIOB: Resetting disp values"<<std::endl;
    	SystemData& SysData = SystemData::Instance();
    	SysData.DispenseRate.Set(0);
    	SysData.TotalSolidAmountDispensed.Set(0);
    	SysData.CurrentSolidOOPState.Set(False);
    	SysData.SolidDispenseOn.Set(False);
    	retValue = 0;
    }

    return retValue;
}


BOOLEAN Garfunkel::GetSolidProdDispenseInfoOnIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::GetSolidProdDispenseInfoOnIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}


#endif


/*************************************************************************
Set Commands
***************************************************************************/


/////////////////////////////////////////////////////////////////////////////
// Set product valve state from the IO Board
/////////////////////////////////////////////////////////////////////////////

Garfunkel::SetDilutionValveStateOnGIOB::SetDilutionValveStateOnGIOB(std::string & addressInstance) :
		IIOBoardTimedMessage(addressInstance)
{
    _runCommand = False;
    _commandName = "SG:03:0500:01:";
    _onCommand  = "A5FF"; //open for 127 milli secs
    _offCommand = "A500";
}

Garfunkel::SetDilutionValveStateOnGIOB::~SetDilutionValveStateOnGIOB()
{
}

void Garfunkel::SetDilutionValveStateOnGIOB::SetDilutionValveState( GarfunkelValveState eOpenOrClosed)
{
	_eOpenOrClosed = eOpenOrClosed;

}

int Garfunkel::SetDilutionValveStateOnGIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
	std::stringstream strStream;
    message.clear();
    response.clear();
	message = _addressInstance + ":SG:03:0500:01:";
	strStream<<message;

	if(_eOpenOrClosed==eOpen)
	{
		strStream<<_onCommand<<":";
	}
	else
	{
		strStream<<_offCommand<<":";
		StopTimedMessage();
	}
	//strStream<<"127:";//open for 127 milli secs
	message.assign(strStream.str());
	retValue = SendMessage(pSocketRS485, message, response);
	std::cout<<"SetDilutionValveStateOnGIOB Message ="<<message<<" Response="<<response<<std::endl;
	if(retValue >= 0)
    {
		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);

		// Sleep in order to ramp up.
	    usleep(100);
		std::stringstream cmd;
		GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
		cmd<<"GetDigitalInputOutputStateForGarfunkel";
		retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
		if(retValue >= 0)
		{
    		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
		}

    }



    return retValue;
}

BOOLEAN Garfunkel::SetDilutionValveStateOnGIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::SetDilutionValveStateOnGIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}


/////////////////////////////////////////////////////////////////////////////
// Set washer valve state from the IO Board
/////////////////////////////////////////////////////////////////////////////

Garfunkel::SetOCapsuleValveStateOnGIOB::SetOCapsuleValveStateOnGIOB(std::string & addressInstance) :
		IIOBoardTimedMessage(addressInstance)
{
    _runCommand = False;
    _commandName = "SG:03:0500:";
    _onCommand  = "A5FF"; //open for 127 milli secs
    _offCommand = "A500";

}

Garfunkel::SetOCapsuleValveStateOnGIOB::~SetOCapsuleValveStateOnGIOB()
{
}

void Garfunkel::SetOCapsuleValveStateOnGIOB::SetOCapsuleValveState( int id, GarfunkelValveState eOpenOrClosed)
{
    _OCapsuleId = id;
	_eOpenOrClosed = eOpenOrClosed;

}

int Garfunkel::SetOCapsuleValveStateOnGIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
	std::stringstream strStream;
    message.clear();
    response.clear();
	message = _addressInstance + ":SG:03:0500:";
	strStream<<message<<((_OCapsuleId==0) ? "02:" : "03:" );
	if(_eOpenOrClosed==eOpen)
	{
		strStream<<_onCommand<<":";
	}
	else
	{
		strStream<<_offCommand<<":";
		StopTimedMessage();
	}
	message.assign(strStream.str());
	retValue = SendMessage(pSocketRS485, message, response);
	//std::cout<<" SetWasherValveStateOnIOB Message ="<<message<<" Response="<<response<<std::endl;
	if(retValue >= 0)
    {
		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);

		// Sleep in order to ramp up.
	    usleep(100);
		std::stringstream cmd;
		GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
		cmd<<"GetDigitalInputOutputStateForGarfunkel";
		retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
		if(retValue >= 0)
		{
    		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
		}

    }



    return retValue;
}

BOOLEAN Garfunkel::SetOCapsuleValveStateOnGIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::SetOCapsuleValveStateOnGIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}




/////////////////////////////////////////////////////////////////////////////
// Set 4th product valve state on the IO Board
/////////////////////////////////////////////////////////////////////////////

Garfunkel::SetDrainValveStateOnGIOB::SetDrainValveStateOnGIOB(std::string & addressInstance) :
IIOBoardTimedMessage(addressInstance)
{
    _runCommand = False; //keep this false initially, this on will be enabled by Dispendata helper function when required
    _commandName = "SG:03:0500:05:";
    _onCommand  = "A5FF"; //open for 127 milli secs
    _offCommand = "A500";
}

Garfunkel::SetDrainValveStateOnGIOB::~SetDrainValveStateOnGIOB()
{
}

void Garfunkel::SetDrainValveStateOnGIOB::SetDrainValveState( GarfunkelValveState eOpenOrClosed)
{
	_eOpenOrClosed = eOpenOrClosed;
}

int Garfunkel::SetDrainValveStateOnGIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
	std::stringstream strStream;

	message.clear();
    response.clear();

	message = _addressInstance + ":SG:03:0500:05:";
	strStream<<message;
	if(_eOpenOrClosed==eOpen)
	{
		strStream<<_onCommand<<":";
	}
	else
	{
		strStream<<_offCommand<<":";
		StopTimedMessage();
	}
	message.assign(strStream.str());
    retValue = SendMessage(pSocketRS485, message, response);
    //std::cout<<"SetFourthProductFlushValveStateOnIOB:: Message : "<<message<<std::endl;
    //std::cout<<"SetFourthProductFlushValveStateOnIOB:: response : "<<response<<std::endl;
    //std::cout<<"SetFourthProductFlushValveStateOnIOB:: retValue : "<<retValue<<std::endl;
	if(retValue >= 0 ) //     && (std::string::npos != response.find("OK")))
    {
		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);

        // Sleep in order to ramp up.
            usleep(100);
        //Now get valve state
        std::stringstream cmd;
        GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
        cmd<<"GetDigitalInputOutputStateForGarfunkel";
        retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
        if(retValue >= 0)
        {
        	clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
        }

    }
    return retValue;
}

BOOLEAN Garfunkel::SetDrainValveStateOnGIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::SetDrainValveStateOnGIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}




/////////////////////////////////////////////////////////////////////////////
// Set  valve state on the IO Board
/////////////////////////////////////////////////////////////////////////////

Garfunkel::SetSumpValveStateOnGIOB::SetSumpValveStateOnGIOB(std::string & addressInstance) :
IIOBoardTimedMessage(addressInstance)
{
    _runCommand = False; //keep this false initially, this on will be enabled by Dispendata helper function when required
    _commandName = "SG:03:0500:04:";
    _onCommand  = "A5FF"; //open for 127 milli secs
    _offCommand = "A500";

}

Garfunkel::SetSumpValveStateOnGIOB::~SetSumpValveStateOnGIOB()
{
}

void Garfunkel::SetSumpValveStateOnGIOB::SetSumpValveState( GarfunkelValveState eOpenOrClosed)
{
	_eOpenOrClosed = eOpenOrClosed;
}

int Garfunkel::SetSumpValveStateOnGIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
	std::stringstream strStream;

	message.clear();
    response.clear();

	message = _addressInstance + ":SG:03:0500:04:";
	strStream<<message;
	if(_eOpenOrClosed==eOpen)
	{
		strStream<<_onCommand<<":";
	}
	else
	{
		strStream<<_offCommand<<":";
		StopTimedMessage();
	}
	message.assign(strStream.str());
    retValue = SendMessage(pSocketRS485, message, response);
    //std::cout<<"SetWaterInletValveStateOnIOB:: Message : "<<message<<std::endl;
	if(retValue >= 0 )
    {
		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
		std::cout<<"SetSumpValveStateOnGIOB:: Message : "<<message<< " response="<<response<<std::endl;
        // Sleep in order to ramp up.
            usleep(100);
        //Now get valve state
        std::stringstream cmd;
        GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
        cmd<<"GetDigitalInputOutputStateForGarfunkel";
        retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
        if(retValue >= 0)
        {
        	clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
        }
#if 0
        SystemData& SysData = SystemData::Instance();
        GarfunkelValveState valveState= SysData.GetDilutionValveState();
        if(_eOpenOrClosed==eOpen&&valveState==eOpen) //Command is for open valve
         {
        	if(SysData.IsWaterValveFlushInProgress()==False)
   			SysData.StartWaterFlowTimeForWaterValve();
   			//std::cerr << "SetWaterInletValveStateOnIOB : Water Flow started from main water inlet" << std::endl;
   			SysData.SetWaterValveFlushComplete(False);
   			retValue = 1;
          }
         else if(_eOpenOrClosed==eClose&&valveState==eClose) //Command is for closing valve
         {
           	IsMessageRunable(False);
           	SysData.StopWaterFlowTimeForWaterValve();
   			std::cerr << "SetWaterInletValveStateOnIOB: Water Flow stopped from main water inlet" << std::endl;
   			SysData.SetWaterValveFlushComplete(True);
   			retValue = 1;
        }

#endif
    }
    return retValue;
}

BOOLEAN Garfunkel::SetSumpValveStateOnGIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::SetSumpValveStateOnGIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}


Garfunkel::SetOCapsuleEmptyLEDStateOnGIOB::SetOCapsuleEmptyLEDStateOnGIOB(std::string & addressInstance) :
		IIOBoardMessage(addressInstance)
{
    _runCommand = False;
    _commandName = "SG:03:0300:";
    _onCommand  = "A501";
    _offCommand = "A500";

}

Garfunkel::SetOCapsuleEmptyLEDStateOnGIOB::~SetOCapsuleEmptyLEDStateOnGIOB()
{
}

void Garfunkel::SetOCapsuleEmptyLEDStateOnGIOB::SetOCapsuleEmptyLEDState( int id, GarfunkelPumpState eOnOrOff)
{
    _OCapsuleId = id;
    _eOnOrOff = eOnOrOff;

}

int Garfunkel::SetOCapsuleEmptyLEDStateOnGIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
	std::stringstream strStream;
    message.clear();
    response.clear();
	message = _addressInstance + ":SG:03:0300:";
	strStream<<message<<((_OCapsuleId==0) ? "01:" : "02:")<<":";
	if(_eOnOrOff==eOn)
	{
		strStream<<_onCommand<<":";
	}
	else
	{
		strStream<<_offCommand<<":";
	}
	message.assign(strStream.str());
	retValue = SendMessage(pSocketRS485, message, response);
	std::cout<<" SetOCapsuleEmptyLEDStateOnGIOB Message ="<<message<<" Response="<<response<<std::endl;
	if(retValue >= 0)
    {
		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);

		// Sleep in order to ramp up.
	    usleep(100);
		std::stringstream cmd;
		GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
		cmd<<"GetDigitalInputOutputStateForGarfunkel";
		retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
		if(retValue >= 0)
		{
    		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
		}

    }



    return retValue;
}

BOOLEAN Garfunkel::SetOCapsuleEmptyLEDStateOnGIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::SetOCapsuleEmptyLEDStateOnGIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}



Garfunkel::SetGarfunkelPumpStateOnGIOB::SetGarfunkelPumpStateOnGIOB(std::string & addressInstance) :
		IIOBoardTimedMessage(addressInstance)
{
    _runCommand = False; //keep this false initially, this on will be enabled by Dispendata helper function when required
    _commandName = "SG:03:0100:01:";
    _onCommand  = "A5FF"; //open for 127 milli secs
    _offCommand = "A500";

}

Garfunkel::SetGarfunkelPumpStateOnGIOB::~SetGarfunkelPumpStateOnGIOB()
{
}

void Garfunkel::SetGarfunkelPumpStateOnGIOB::SetGarfunkelPumpState( GarfunkelPumpState oNOff)
{

	_oNOff = oNOff;

}

int Garfunkel::SetGarfunkelPumpStateOnGIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
	std::stringstream strStream;
    message.clear();
    response.clear();
	message = _addressInstance + ":SG:03:0100:01:";
	strStream<<message;
	if(_oNOff==eOn)
	{
		strStream<<_onCommand<<":";
	}
	else
	{
		strStream<<_offCommand<<":";
		StopTimedMessage();
	}
	message.assign(strStream.str());
	retValue = SendMessage(pSocketRS485, message, response);
	std::cout<<" SetGarfunkelPumpStateOnGIOB Message ="<<message<<" Response="<<response<<std::endl;
	if(retValue >= 0)
    {
		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);

		// Sleep in order to ramp up.
	    usleep(100);
		std::stringstream cmd;
		GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
		cmd<<"GetDigitalInputOutputStateForGarfunkel";
		retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
		if(retValue >= 0)
		{
    		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
		}

    }

    return retValue;

}

BOOLEAN Garfunkel::SetGarfunkelPumpStateOnGIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::SetGarfunkelPumpStateOnGIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}


/////////////////////////////////////////////////////////////////////////////
// Set pump state from the IO Board
/////////////////////////////////////////////////////////////////////////////

Garfunkel::SetTreatmentPumpStateOnSIOB::SetTreatmentPumpStateOnSIOB(std::string & addressInstance) :
		IIOBoardTimedMessage(addressInstance)
{
    _runCommand = False; //keep this false initially, this on will be enabled by Dispendata helper function when required
    _commandName = "SG:03:0100:51:";
    _onCommand  = "A5FF"; //open for 127 milli secs
    _offCommand = "A500";

}

Garfunkel::SetTreatmentPumpStateOnSIOB::~SetTreatmentPumpStateOnSIOB()
{
}

void Garfunkel::SetTreatmentPumpStateOnSIOB::SetTreatmentPumpState( GarfunkelPumpState oNOff)
{

	_oNOff = oNOff;

}

int Garfunkel::SetTreatmentPumpStateOnSIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
	std::stringstream strStream;

	message.clear();
    response.clear();

    SystemData& SysData = Garfunkel::SystemData::Instance();
#if 0
    if(_pumpId>=0&&_pumpId< AQUAGATOR_MAX_PUMPS)
    {
    	message = _addressInstance + ":SU:27:";
    	strStream<<message<<_pumpId<<":";
    	if(_oNOff==eOn)
    		strStream<<"1:";
    	else
    	{
    		strStream<<"0:";
    		StopTimedMessage();
    	}
    	strStream<<"10:";
    	message.assign(strStream.str());
    	retValue = SendMessage(pSocketRS485, message, response);
    	if(retValue >= 0)
    	{
    		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
    		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastSimonIOBCommunication);

			time_t clock1 = time(0);
			struct tm *ct = localtime(&clock1);
    		//std::cout<<"SetPumpOnStateOnIOB: msg="<<message<<"  retvalue = "<<retValue<<" at "<<asctime(ct)<<std::endl;

    		// Sleep in order to ramp up.
   		    usleep(100);
   		    //Get Pump state
    		std::stringstream cmd;
    		GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
    		cmd<<"GetPumpState";
 			retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
 			if(retValue >= 0)
 			{
 	    		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
 			}

 			cmd.str("");
 			cmd.clear();
    		// Sleep in order to ramp up.
   		    usleep(100);
   		    //Get OOP state

    		cmd<<"GetOOPState";
 			int retValue1 = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
 			if(retValue1 >= 0)
 			{
 	    		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
 			}


    	}
    }
#endif
    return retValue;
}

BOOLEAN Garfunkel::SetTreatmentPumpStateOnSIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::SetTreatmentPumpStateOnSIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}

/////////////////////////////////////////////////////////////////////////////
// Set all outputs G IO Board
/////////////////////////////////////////////////////////////////////////////

Garfunkel::SetAllOutputsOffOnGIOB::SetAllOutputsOffOnGIOB(std::string & addressInstance) :
    IIOBoardMessage(addressInstance)
{
    _runCommand = True;
    _commandName = "SU:41";
}

Garfunkel::SetAllOutputsOffOnGIOB::~SetAllOutputsOffOnGIOB()
{
}


int Garfunkel::SetAllOutputsOffOnGIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
	std::stringstream strStream;

	message.clear();
    response.clear();

	message = _addressInstance + ":SU:41:";
	strStream<<message;
	message.assign(strStream.str());
    retValue = SendMessage(pSocketRS485, message, response);
	if(retValue >= 0)
    {
		std::cerr<<"SetAllOutputsOff for Garfunkel : retvalue = "<<retValue<<std::endl;
		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);

    }
    return retValue;
}

BOOLEAN Garfunkel::SetAllOutputsOffOnGIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::SetAllOutputsOffOnGIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}



Garfunkel::SetMainWaterInletStateOnSIOB::SetMainWaterInletStateOnSIOB(std::string & addressInstance) :
IIOBoardTimedMessage(addressInstance)
{
    _runCommand = False; //keep this false initially, this on will be enabled by Dispendata helper function when required
    _commandName = "SG:03:0500:53:";
    _onCommand  = "A5FF";
    _offCommand = "A500";

}

Garfunkel::SetMainWaterInletStateOnSIOB::~SetMainWaterInletStateOnSIOB()
{
}

void Garfunkel::SetMainWaterInletStateOnSIOB::SetMainWaterInletState( GarfunkelValveState eOpenOrClosed)
{
	_eOpenOrClosed = eOpenOrClosed;
}

int Garfunkel::SetMainWaterInletStateOnSIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
	std::stringstream strStream;

	message.clear();
    response.clear();

	message = _addressInstance + ":SG:03:0500:53:";
	strStream<<message;
	if(_eOpenOrClosed==eOpen)
	{
		strStream<<_onCommand<<":";
	}
	else
	{
		strStream<<_offCommand<<":";
		StopTimedMessage();
	}
	message.assign(strStream.str());
    retValue = SendMessage(pSocketRS485, message, response);
    std::cout<<"SetWaterInletValveStateOnIOB:: Message : "<<message<<std::endl;
	if(retValue >= 0 )
    {
		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastSimonIOBCommunication);

        // Sleep in order to ramp up.
            usleep(100);
        //Now get valve state
        std::stringstream cmd;
        GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
        cmd<<"GetDigitalInputOutputStateForSimon";
        retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
        if(retValue >= 0)
        {
        	clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
        }
#if 0
        SystemData& SysData = SystemData::Instance();
        GarfunkelValveState valveState= SysData.GetDilutionValveState();
        if(_eOpenOrClosed==eOpen&&valveState==eOpen) //Command is for open valve
         {
        	if(SysData.IsWaterValveFlushInProgress()==False)
   			SysData.StartWaterFlowTimeForWaterValve();
   			//std::cerr << "SetWaterInletValveStateOnIOB : Water Flow started from main water inlet" << std::endl;
   			SysData.SetWaterValveFlushComplete(False);
   			retValue = 1;
          }
         else if(_eOpenOrClosed==eClose&&valveState==eClose) //Command is for closing valve
         {
           	IsMessageRunable(False);
           	SysData.StopWaterFlowTimeForWaterValve();
   			std::cerr << "SetWaterInletValveStateOnIOB: Water Flow stopped from main water inlet" << std::endl;
   			SysData.SetWaterValveFlushComplete(True);
   			retValue = 1;
        }

#endif
    }
    return retValue;
}

BOOLEAN Garfunkel::SetMainWaterInletStateOnSIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::SetMainWaterInletStateOnSIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}



Garfunkel::SetSValveStateOnSIOB::SetSValveStateOnSIOB(std::string & addressInstance) :
IIOBoardTimedMessage(addressInstance)
{
    _runCommand = False; //keep this false initially, this on will be enabled by Dispendata helper function when required
    _commandName = "SG:03:0500:52:";
    _onCommand  = "A5FF"; //open for 127 milli secs
    _offCommand = "A500";

}

Garfunkel::SetSValveStateOnSIOB::~SetSValveStateOnSIOB()
{
}

void Garfunkel::SetSValveStateOnSIOB::SetSValveState( GarfunkelValveState eOpenOrClosed)
{
	_eOpenOrClosed = eOpenOrClosed;
}

int Garfunkel::SetSValveStateOnSIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
	std::stringstream strStream;

	message.clear();
    response.clear();

	message = _addressInstance + ":SG:03:0500:52:";
	strStream<<message;
	if(_eOpenOrClosed==eOpen)
	{
		strStream<<_onCommand<<":";
	}
	else
	{
		strStream<<_offCommand<<":";
		StopTimedMessage();
	}

	message.assign(strStream.str());
    retValue = SendMessage(pSocketRS485, message, response);
    std::cout<<"SetSValveStateOnSIOB:: Message : "<<message<<std::endl;
	if(retValue >= 0 )
    {
		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastSimonIOBCommunication);

        // Sleep in order to ramp up.
            usleep(100);
        //Now get valve state
        std::stringstream cmd;
        GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
        cmd<<"GetDigitalInputOutputStateForSimon";
        retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
        if(retValue >= 0)
        {
        	clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
        }
    }
    return retValue;
}

BOOLEAN Garfunkel::SetSValveStateOnSIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::SetSValveStateOnSIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}


Garfunkel::SetPValveStateOnSIOB::SetPValveStateOnSIOB(std::string & addressInstance) :
IIOBoardTimedMessage(addressInstance)
{
    _runCommand = False; //keep this false initially, this on will be enabled by Dispendata helper function when required
    _commandName = "SG:03:0500:51:";
    _onCommand  = "A5FF"; //open for 127 milli secs
    _offCommand = "A500";

}

Garfunkel::SetPValveStateOnSIOB::~SetPValveStateOnSIOB()
{
}

void Garfunkel::SetPValveStateOnSIOB::SetPValveState( GarfunkelValveState eOpenOrClosed)
{
	_eOpenOrClosed = eOpenOrClosed;
}

int Garfunkel::SetPValveStateOnSIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
	std::stringstream strStream;

	message.clear();
    response.clear();

	message = _addressInstance + ":SG:03:0500:51:";
	strStream<<message;
	if(_eOpenOrClosed==eOpen)
	{
		strStream<<_onCommand<<":";
	}
	else
	{
		strStream<<_offCommand<<":";
		StopTimedMessage();
	}
	strStream<<"10:";
	message.assign(strStream.str());
    retValue = SendMessage(pSocketRS485, message, response);
    //std::cout<<"SetWaterInletValveStateOnIOB:: Message : "<<message<<std::endl;
	if(retValue >= 0 )
    {
		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastSimonIOBCommunication);

        // Sleep in order to ramp up.
            usleep(100);
        //Now get valve state
        std::stringstream cmd;
        GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
        cmd<<"GetDigitalInputOutputStateForSimon";
        retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
        if(retValue >= 0)
        {
        	clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
        }
    }
    return retValue;
}

BOOLEAN Garfunkel::SetPValveStateOnSIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::SetPValveStateOnSIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}


Garfunkel::GetDigitalInputOutputStatefromSIOB::GetDigitalInputOutputStatefromSIOB(std::string & addressInstance) :
		IIOBoardTimedMessage(addressInstance)
{
    _runCommand = True;
    _commandName = "DU:41";
    SetTimeInterval(1); //read every 2 sec
}

Garfunkel::GetDigitalInputOutputStatefromSIOB::~GetDigitalInputOutputStatefromSIOB()
{
}

int Garfunkel::GetDigitalInputOutputStatefromSIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
    GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
	std::vector<std::string>::iterator      itemsIter;
    std::vector<std::string>                items;

    message.clear();
    response.clear();

	message = _addressInstance + ":DU:41:";  //valve state for all washers

    retValue = SendMessage(pSocketRS485, message, response);
    //std::cerr << "Garfunkel::GetDigitalInputOutputStatefromIOB"<<": retval = "<<retValue<< std::endl;
	if(retValue >= 0)
    {
		std::cout << "GetDigitalInputOutputStatefromIOB : Response = " << response << std::endl;
        clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastSimonIOBCommunication);
        IPCReturnCommand   cmdResponse(response);
		std::string        value;
		items = cmdResponse.GetPayloadList();
		//std::cout << "Simon : items.size() =  "<<items.size() << std::endl;
        if(items.size() > 0&&(GfData._dBSyncInProgress.Get()==False ||  GfData._alarmHandlerSleeping.Get()==False))
        {
        	SystemData& SysData = SystemData::Instance();
        	itemsIter = items.begin();
        	if(itemsIter != items.end()) //get inputs
        	{

           		std::string inputs =  ((std::string)*itemsIter);
           		unsigned int temp = FromHex(inputs);
    			const std::bitset<16> State(temp);
    			std::vector<bool> i_state;


    			i_state.push_back(State.test(0));//reserved unused
    			i_state.push_back(State.test(1)); //51h, pressure switch
    			i_state.push_back(State.test(2)); //52h, sump empty
    			i_state.push_back(State.test(3));//53h, sump full state
    			i_state.push_back(State.test(4));//54h sum overflow
    			i_state.push_back(State.test(5));//55h s oop
    			i_state.push_back(State.test(6));//56h h oop
    			i_state.push_back(State.test(7));//57h s lid switch
    			i_state.push_back(State.test(8));//58h..2h lid switch
    			i_state.push_back(State.test(9));//59h ..flow switch
    			i_state.push_back(State.test(10));//5ah ..fault
    			i_state.push_back(State.test(11));//5Bh ..valve fuse blown status

    			SysData.SetPressureSwitchState((i_state[1]==true) ? eOpen : eClose);
    			if((i_state[2]==true))
    				SysData.SetSumpLevelSwitchState(eLow);
    			else if ((i_state[3]==true))
        			SysData.SetSumpLevelSwitchState(eFull);
    			else if ((i_state[4]==true))
        			SysData.SetSumpLevelSwitchState(eOverflow);
    			else
    				SysData.SetSumpLevelSwitchState(eNormal);


    			SysData._SLowProductState.Set((i_state[5]==true) ? True : False);
    			SysData._HLowProductState.Set((i_state[6]==true) ? True : False);

    			SysData.SetSLidSwitchState((i_state[7]==true) ? eSwitchOpen : eSwitchClosed );
    			SysData.SetHLidSwitchState((i_state[8]==true) ?  eSwitchOpen : eSwitchClosed );

    			SysData.SetPumpSwitchState((i_state[9]==true) ? eClose : eOpen);

    			//std::cout << "Simon : FAULT STATE = " << i_state[10] << std::endl;
    			SysData._SimonIOBoardFaultLine.Set((i_state[10]==true) ? True : False);
    			++itemsIter;
            	if(itemsIter != items.end()) //get outputs
            	{
               		std::string outputs =  ((std::string)*itemsIter);
               		unsigned int temp = FromHex(outputs);
        			const std::bitset<16> oState(temp);
        			std::vector<bool> o_state;
        			o_state.push_back(oState.test(0)); //reserved unused
					o_state.push_back(oState.test(1)); // 51h, h2 valve
					o_state.push_back(oState.test(2)); //52h, s valve
					o_state.push_back(oState.test(3)); //53, master valve
        			SysData.SetPValveState((o_state[1]==true)? eOpen : eClose);
        			SysData.SetSValveState((o_state[2]==true)? eOpen : eClose);
        			SysData.SetMainWaterInletState((o_state[3]==true)? eOpen : eClose);
              		++itemsIter;
                	if(itemsIter != items.end()) //get led status
                	{
                   		std::string leds =  ((std::string)*itemsIter);
                   		temp = FromHex(leds);
            			const std::bitset<16> ledState(temp);
            			std::vector<bool> l_state;

            			l_state.push_back(ledState.test(0));//reserved unused
            			l_state.push_back(ledState.test(1)); //51h, S OOP led
            			l_state.push_back(ledState.test(2)); //52h, H2 OOP led

            			SysData.SetSOutOfProductLEDStatus((l_state[1]==true)? eOn :  eOff);
            			SysData.SetHOutOfProductLEDStatus((l_state[2]==true)? eOn :  eOff);

            			//TODO : Shilpa Check for open /close what they mean,
            			++itemsIter;
            		    if(itemsIter != items.end()) //get pump status
            		    {
            		    	std::string pumpSt =  ((std::string)*itemsIter);
            		        temp = FromHex(pumpSt);
            		        const std::bitset<16> pmpState(temp);
            		        std::vector<bool> p_state;
            		        p_state.push_back(pmpState.test(0));//reserved unused
            		        p_state.push_back(pmpState.test(1)); //51h, S OOP led

                			SysData.SetTreatmentPumpState((p_state[1]==true)? eOn :  eOff);

            		    }
                	}


            	}

        	}


        }



    }

	return retValue;
}

BOOLEAN Garfunkel::GetDigitalInputOutputStatefromSIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::GetDigitalInputOutputStatefromSIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}



Garfunkel::SetSEmptyLEDStateOnSIOB::SetSEmptyLEDStateOnSIOB(std::string & addressInstance) :
		IIOBoardMessage(addressInstance)
{
    _runCommand = False; //keep this false initially, this on will be enabled by Dispendata helper function when required
    _commandName = "SG:03:0300:51:";
    _onCommand  = "A501";
    _offCommand = "A500";
}

Garfunkel::SetSEmptyLEDStateOnSIOB::~SetSEmptyLEDStateOnSIOB()
{
}

void Garfunkel::SetSEmptyLEDStateOnSIOB::SetSEmptyLEDState( GarfunkelPumpState oNOff)
{

	_oNOff = oNOff;

}

int Garfunkel::SetSEmptyLEDStateOnSIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
	std::stringstream strStream;

	message.clear();
    response.clear();
    message = _addressInstance + ":SG:03:0300:51:";
    strStream<<message;
	if(_oNOff==eOn)
	{
		strStream<<_onCommand<<":";
	}
	else
	{
		strStream<<_offCommand<<":";
	}
	message.assign(strStream.str());
	retValue = SendMessage(pSocketRS485, message, response);
	std::cout<<" SetSEmptyLEDStateOnSIOB Message ="<<message<<" Response="<<response<<std::endl;
	if(retValue >= 0)
    {
		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);

		// Sleep in order to ramp up.
	    usleep(100);
		std::stringstream cmd;
		GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
		cmd<<"GetDigitalInputOutputStateForGarfunkel";
		retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
		if(retValue >= 0)
		{
    		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
		}

    }


    return retValue;
}

BOOLEAN Garfunkel::SetSEmptyLEDStateOnSIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::SetSEmptyLEDStateOnSIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}




Garfunkel::SetHEmptyLEDStateOnSIOB::SetHEmptyLEDStateOnSIOB(std::string & addressInstance) :
		IIOBoardMessage(addressInstance)
{
    _runCommand = False; //keep this false initially, this on will be enabled by Dispendata helper function when required
    _commandName = "SG:03:0300:52:";
    _onCommand  = "A501";
    _offCommand = "A500";

}

Garfunkel::SetHEmptyLEDStateOnSIOB::~SetHEmptyLEDStateOnSIOB()
{
}

void Garfunkel::SetHEmptyLEDStateOnSIOB::SetHEmptyLEDState( GarfunkelPumpState oNOff)
{

	_oNOff = oNOff;

}

int Garfunkel::SetHEmptyLEDStateOnSIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
	std::stringstream strStream;

	message.clear();
    response.clear();

    SystemData& SysData = Garfunkel::SystemData::Instance();
    message = _addressInstance + ":SG:03:0300:52:";
    strStream<<message;
	if(_oNOff==eOn)
	{
		strStream<<_onCommand<<":";
	}
	else
	{
		strStream<<_offCommand<<":";
	}
	message.assign(strStream.str());
	retValue = SendMessage(pSocketRS485, message, response);
	std::cout<<" SetHEmptyLEDStateOnSIOB Message ="<<message<<" Response="<<response<<std::endl;
	if(retValue >= 0)
    {
		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);

		// Sleep in order to ramp up.
	    usleep(100);
		std::stringstream cmd;
		GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
		cmd<<"GetDigitalInputOutputStateForGarfunkel";
		retValue = cmdProcIOBoard.ExecuteCommand(cmd.str(), pSocketRS485, True);
		if(retValue >= 0)
		{
    		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastGarIOBCommunication);
		}

    }
    return retValue;

}

BOOLEAN Garfunkel::SetHEmptyLEDStateOnSIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::SetHEmptyLEDStateOnSIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}


/////////////////////////////////////////////////////////////////////////////
// Set all outputs off S IO Board
/////////////////////////////////////////////////////////////////////////////

Garfunkel::SetAllOutputsOffOnSIOB::SetAllOutputsOffOnSIOB(std::string & addressInstance) :
    IIOBoardMessage(addressInstance)
{
    _runCommand = True;
    _commandName = "SU:41";

}

Garfunkel::SetAllOutputsOffOnSIOB::~SetAllOutputsOffOnSIOB()
{
}


int Garfunkel::SetAllOutputsOffOnSIOB::Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485)
{
    int         retValue = -1;
    std::string message;
    std::string response;
	std::stringstream strStream;

	message.clear();
    response.clear();

	message = _addressInstance + ":SU:41:";
	strStream<<message;
	message.assign(strStream.str());
    retValue = SendMessage(pSocketRS485, message, response);
	if(retValue >= 0)
    {
		std::cerr<<"SetAllOutputs Simon: retvalue = "<<retValue<<std::endl;
		GarfunkelData &   GfData = Garfunkel::GarfunkelData::Instance();
		clock_gettime(CLOCK_MONOTONIC, &GfData._timeOfLastSimonIOBCommunication);

    }
    return retValue;
}

BOOLEAN Garfunkel::SetAllOutputsOffOnSIOB::IsMessageRunable(BOOLEAN    bAutomated)
{
    SetCommandReadyToRun(True);
    return _runCommand;
}

int Garfunkel::SetAllOutputsOffOnSIOB::HandleIPCResponse(std::string &     response)
{
    return -1;
}


/////////////////////////////////////////////////////////////////////////////
// IO Board thread
/////////////////////////////////////////////////////////////////////////////
Garfunkel::IOBoardBaseThread::IOBoardBaseThread(const std::string & name, const std::string &addressInstance, const std::string &File) : Thread(name)
{
	dBItem = addressInstance;
	flatFilePath = File;
}

Garfunkel::IOBoardBaseThread::IOBoardBaseThread(const IOBoardBaseThread &     objectToCopy)
{
}

Garfunkel::IOBoardBaseThread::~IOBoardBaseThread()
{
}

int Garfunkel::IOBoardBaseThread::Run()
{

    std::list<boost::shared_ptr< Garfunkel::IIOBoardTimedMessage > >::iterator     timedMsgIter;
    boost::shared_ptr< Garfunkel::IIOBoardTimedMessage >                             tMsgToPr;
    int washerNo = -1, pumpNo =-1;
	std::stringstream strStream;
	std::string command;

	GarfunkelData& GaData = GarfunkelData::Instance();

	ecolab::SocketFactory & FactoryInstance = ecolab::SocketFactory::Instance();
	pSocketRS485 =  boost::shared_ptr< ecolab::ISocketCommunication>  (FactoryInstance.CreateSocket(ecolab::eCondor, ecolab::eRS485WithReadTimeout));
    pSocketRS485->SetRS485ReadTimeout(5000);
    pSocketRS485->Connect();



    try
    {
        GarfunkelIPCMaster&     ipcMaster = GarfunkelIPCMaster::Instance();

        while(True)
        {
            timedMsgIter = _ioBoardTimedMessages.begin();
            while(timedMsgIter != _ioBoardTimedMessages.end())
            {
            	tMsgToPr = (boost::shared_ptr< Garfunkel::IIOBoardTimedMessage >)(*timedMsgIter);

                if(NULL != tMsgToPr &&  tMsgToPr->IsMessageRunable(True)==True&&tMsgToPr->ReadyToRestart()==True&&GaData._pollIOBoard.Get()==True)
                {

                	if(pSocketRS485->SocketConnected() && pSocketRS485->SocketStatus() == ecolab::eConnectionAvailable)
                	{
               			tMsgToPr->Execute(pSocketRS485);
               			tMsgToPr->UpdateLastRunTime();
               			_ioBoardTimedMessages.sort(SortTimedMessagesByExpiry());
                	}
                	else
                	{
                		std::cout << "IOBoard timed msg thread: Socket Not Connected : "<< std::endl;
                	}
                }
                ++timedMsgIter;
                sleep(10);
                ipcMaster.ClearTheReceiveQueue();
            }
        }
    }
    catch(std::exception & e)
    {
        std::cerr << "Caught std exception :"<<e.what() <<" for IO Board message processing error: " << tMsgToPr->GetCommandName() << std::endl;
        std::cerr << "Exiting" << std::endl;
        GaData._continueRunning.Set(False);

    }
    catch(...)
    {
        std::cerr << "Caught general exception: IO Board message processing error: " << tMsgToPr->GetCommandName() << std::endl;
    }
	pSocketRS485->Disconnect();
    return 0;
}

void Garfunkel::IOBoardBaseThread::Cleanup()
{
    // Cleanup the IOBoardMessages

}

BOOLEAN     Garfunkel::IOBoardBaseThread::Initialize()
{
    return True;
}

BOOLEAN Garfunkel::IOBoardBaseThread::RegisterCallback(std::string command, boost::shared_ptr< Garfunkel::IIOBoardMessage > pMsg)
{
    BOOLEAN     ret = False;

    if (!command.empty())
    {
    	GarfunkelCommandProcessorIOBoard & cmdProcInstance = GarfunkelCommandProcessorIOBoard::Instance();

        std::cerr << "[Garfunkel] Register IOBoard command: " << command << std::endl;
        ret = cmdProcInstance.AddCommand(command, pMsg);
    }

    return ret;
}


Garfunkel::GarfunkelIOBoardThread::GarfunkelIOBoardThread(const std::string & name, const std::string &addressInstance, const std::string &flatFile) : IOBoardBaseThread(name, addressInstance, flatFile )
{
	RegisterCommands();
}


Garfunkel::GarfunkelIOBoardThread::~GarfunkelIOBoardThread()
{
}

void Garfunkel::GarfunkelIOBoardThread::RegisterCommands()
{

	GarfunkelData& GaData = GarfunkelData::Instance();

		std::string addressInstance = GaData._garfunkelIOBoardAddressInstance;

		//DU commands
		boost::shared_ptr< Garfunkel::IIOBoardTimedMessage >     tempConductivity(new GetAnalogSensorDatafromGIOB(addressInstance));
		RegisterCallback("GetTempAndConductivity", tempConductivity);
		_ioBoardTimedMessages.push_back(tempConductivity); //check every sec


		boost::shared_ptr< Garfunkel::IIOBoardTimedMessage >     inputOutputState(new GetDigitalInputOutputStatefromGIOB(addressInstance));
		RegisterCallback("GetDigitalInputOutputStateForGarfunkel", inputOutputState);
		_ioBoardTimedMessages.push_back(inputOutputState); //check every sec

		//Set commands
		boost::shared_ptr< Garfunkel::IIOBoardMessage > configureIOBoard(new Garfunkel::ConfigureIOBoard(addressInstance));
		RegisterCallback("ConfigureIOBoard", configureIOBoard);


		boost::shared_ptr< Garfunkel::IIOBoardTimedMessage > setDilutionValveState(new Garfunkel::SetDilutionValveStateOnGIOB(addressInstance));
		RegisterCallback("SetDilutionValveState", setDilutionValveState);
		_ioBoardTimedMessages.push_back(setDilutionValveState);


		boost::shared_ptr< Garfunkel::IIOBoardTimedMessage > setOCapsuleValveState(new Garfunkel::SetOCapsuleValveStateOnGIOB(addressInstance));
		RegisterCallback("SetOCapsuleValveState", setOCapsuleValveState);
		_ioBoardTimedMessages.push_back(setOCapsuleValveState);

		boost::shared_ptr< Garfunkel::IIOBoardTimedMessage > setDrainValveState(new Garfunkel::SetDrainValveStateOnGIOB(addressInstance));
		RegisterCallback("SetDrainValveState", setDrainValveState);
		_ioBoardTimedMessages.push_back(setDrainValveState);

		boost::shared_ptr< Garfunkel::IIOBoardTimedMessage > setSumpValveState(new Garfunkel::SetSumpValveStateOnGIOB(addressInstance));
		RegisterCallback("SetSumpValveState", setSumpValveState);
		_ioBoardTimedMessages.push_back(setSumpValveState);

		boost::shared_ptr< Garfunkel::IIOBoardMessage > setOLEDState(new Garfunkel::SetOCapsuleEmptyLEDStateOnGIOB(addressInstance));
		RegisterCallback("SetOEmptyLEDState", setOLEDState);

		boost::shared_ptr< Garfunkel::IIOBoardTimedMessage > setPumpState(new Garfunkel::SetGarfunkelPumpStateOnGIOB(addressInstance));
		RegisterCallback("SetGarfunkelPumpState", setPumpState);
		_ioBoardTimedMessages.push_back(setPumpState);

		boost::shared_ptr< Garfunkel::IIOBoardMessage > setAllOutputsOff(new Garfunkel::SetAllOutputsOffOnGIOB(addressInstance));
		RegisterCallback("SetAllOutputsOffGarfunkel", setAllOutputsOff);

		usleep(1000); //wait for sometime after registering

}


Garfunkel::SimonlIOBoardThread::SimonlIOBoardThread(const std::string & name, const std::string &addressInstance, const std::string &flatFile) : IOBoardBaseThread(name, addressInstance, flatFile )
{
	RegisterCommands();
}


Garfunkel::SimonlIOBoardThread::~SimonlIOBoardThread()
{
}

void Garfunkel::SimonlIOBoardThread::RegisterCommands()
{

	GarfunkelData& GaData = GarfunkelData::Instance();

		std::string addressInstance = GaData._simonIOBoardAddressInstance;


		boost::shared_ptr< Garfunkel::IIOBoardTimedMessage >     inputOutputState(new GetDigitalInputOutputStatefromSIOB(addressInstance));
		RegisterCallback("GetDigitalInputOutputStateForSimon", inputOutputState);
		_ioBoardTimedMessages.push_back(inputOutputState); //check every sec

		boost::shared_ptr< Garfunkel::IIOBoardTimedMessage > getPumpState(new Garfunkel::GetTreatmentPumpStatusfromSIOB(addressInstance));
		RegisterCallback("GetPumpState", getPumpState);
		_ioBoardTimedMessages.push_back(getPumpState);

		//Set commands

		boost::shared_ptr< Garfunkel::IIOBoardTimedMessage > setMain(new Garfunkel::SetMainWaterInletStateOnSIOB(addressInstance));
		RegisterCallback("SetMainWaterInletState", setMain);
		_ioBoardTimedMessages.push_back(setMain);

		boost::shared_ptr< Garfunkel::IIOBoardTimedMessage > setSValveState(new Garfunkel::SetSValveStateOnSIOB(addressInstance));
		RegisterCallback("SetSValveState", setSValveState);
		_ioBoardTimedMessages.push_back(setSValveState);

		boost::shared_ptr< Garfunkel::IIOBoardTimedMessage > setHValveState(new Garfunkel::SetPValveStateOnSIOB(addressInstance));
		RegisterCallback("SetPValveState", setHValveState);
		_ioBoardTimedMessages.push_back(setHValveState);

		boost::shared_ptr< Garfunkel::IIOBoardTimedMessage > setPumpState(new Garfunkel::SetTreatmentPumpStateOnSIOB(addressInstance));
		RegisterCallback("SetTreatmentPumpState", setPumpState);
		_ioBoardTimedMessages.push_back(setPumpState);

		boost::shared_ptr< Garfunkel::IIOBoardMessage > setSLEDState(new Garfunkel::SetSEmptyLEDStateOnSIOB(addressInstance));
		RegisterCallback("SetSEmptyLEDState", setSLEDState);

		boost::shared_ptr< Garfunkel::IIOBoardMessage > setHLEDState(new Garfunkel::SetHEmptyLEDStateOnSIOB(addressInstance));
		RegisterCallback("SetHEmptyLEDState", setHLEDState);


		boost::shared_ptr< Garfunkel::IIOBoardMessage > setAllOutputsOff(new Garfunkel::SetAllOutputsOffOnSIOB(addressInstance));
		RegisterCallback("SetAllOutputsOffSimon", setAllOutputsOff);

		usleep(1000); //wait for sometime after registering

}
