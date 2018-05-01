#include <bitset>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "ecolab.h"
#include "threads.h"
#include "GarfunkelData.h"
#include "GarfunkelEnums.h"
#include "DispenseAlgorithm.h"
#include "ElapsedTime.h"


Garfunkel::DispenseAlgorithmFactory::DispenseAlgorithmFactory()
{
    
}


Garfunkel::DispenseAlgorithmFactory::~DispenseAlgorithmFactory()
{
    
}


Garfunkel::DispenseAlgorithmFactory&  Garfunkel::DispenseAlgorithmFactory::Instance()
{
	static DispenseAlgorithmFactory singleton;
	return singleton;
}

boost::shared_ptr<Garfunkel::IDispenseAlgorithm>   Garfunkel::DispenseAlgorithmFactory::GetDispenseAlgorithm()
{

}







/////////////////////////////////////////////////////////////////////////////
// IDispenseAlgorithm
/////////////////////////////////////////////////////////////////////////////
Garfunkel::IDispenseAlgorithm::IDispenseAlgorithm()
{

}


Garfunkel::IDispenseAlgorithm::~IDispenseAlgorithm()
{

}



/////////////////////////////////////////////////////////////////////////////
// 
/////////////////////////////////////////////////////////////////////////////

void Garfunkel::DummyDispenseAlgorithm::Dispense(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485)
{

    std::cout<<"Dispense : DummyDispenseAlgorithm"<<std::endl;
}

/////////////////////////////////////////////////////////////////////////////
// 
/////////////////////////////////////////////////////////////////////////////



void Garfunkel::StandardDispenseAlgorithm::Dispense(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485)
{





}

/////////////////////////////////////////////////////////////////////////////
// IDispenseAlgorithm
/////////////////////////////////////////////////////////////////////////////


void Garfunkel::AdvanceDispenseAlgorithm::Dispense(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485)
{

	std::cout<<"Dispense : Advance Mode not yet implemented"<<std::endl;
}



//  Dispensing System Data
Garfunkel::DispensingSystemData::DispensingSystemData()
{
	IsDispenseActive.Set(False);
	DispenseError.Set(False);
	AvgBaselineConductivity.Set(0);
	memset(&LastUIUpdateTime, 0, sizeof(timespec));
	RespCode = eUndefinedESPResponse;
	ErrNo = -1;

}

Garfunkel::DispensingSystemData::DispensingSystemData(const DispensingSystemData& ObjectToCopy)
{

}
Garfunkel::DispensingSystemData::~DispensingSystemData()
{
	std::cout<<"DispensingSystemData destructor called"<<std::endl;


}


Garfunkel::DispensingSystemData&     Garfunkel::DispensingSystemData::Instance()
{
    static DispensingSystemData  singleton;
    return singleton;
}

void Garfunkel::DispensingSystemData::Reset()
{

	std::cout<<"DispensingSystemData Reset called"<<std::endl;
	IsDispenseActive.Set(False);
	DispenseError.Set(False);
	memset(&LastUIUpdateTime, 0, sizeof(timespec));
	RespCode = eUndefinedESPResponse;
	ErrNo = -1;

}

BOOLEAN Garfunkel::DispensingSystemData::NeedToStopDispensing()
{

    BOOLEAN ret = False;
    SystemData& SysData = SystemData::Instance();

    /*if(SysData.GetSystemState()==StandBy) TODO Shilpa : Uncomment this
    {
        	ret = True;
    }
    if(SysData.GetVirtualcounterLevel()==True)
    {
        	ret = True;
    }
    if(SysData.GetPumpSwitchState()==eOpen)
    {
        	ret = True;
    }*/

    if(SysData.GetBFWPumpState()==eOff)
    {
    	ret = True;
    }

   	return ret;
}


void Garfunkel::DispensingSystemData::SendDispensingUpdateMessageToUI(int noOfSignalsDispensed, int totalNoOfProgSignals)
{
	std::string message;
	std::stringstream strStream;

	if(IsDispenseActive.Get()==True)
	{
		GarfunkelIPCMaster&  ipcMaster = GarfunkelIPCMaster::Instance();
		GarfunkelData& AqData = GarfunkelData::Instance();
		//add noofsignalsdispense:totalsignals dispensed
		SystemData& SysData = SystemData::Instance();

		message = strStream.str();
		ipcMaster.SendESPCommandResponse(message);
		//std::cout<<"DispensingSystemData : Sent message to UI "<<message<<std::endl;
	}

}

