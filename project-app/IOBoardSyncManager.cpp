#include <bitset>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "GarfunkelData.h"
//#include "GarfunkelIPC.h"
#include "ElapsedTime.h"
#include "IOBoardSyncManager.h"
#include "DispenseAlgorithm.h"
#include "IOBoardMessages.h"

/////////////////////////////////////////////////////////////////////////////
// IO Board threading
/////////////////////////////////////////////////////////////////////////////
Garfunkel::IOBoardSyncThread::IOBoardSyncThread(const std::string & name) : Thread(name)
{

}

Garfunkel::IOBoardSyncThread::IOBoardSyncThread(const IOBoardSyncThread &     objectToCopy)
{
}

Garfunkel::IOBoardSyncThread::~IOBoardSyncThread()
{
}

int Garfunkel::IOBoardSyncThread::Run()
{
	ecolab::SocketFactory & FactoryInstance = ecolab::SocketFactory::Instance();
    pSocketRS485.reset(FactoryInstance.CreateSocket(ecolab::eCondor, ecolab::eRS485WithReadTimeout));
    pSocketRS485->SetRS485ReadTimeout(2000); //set timeout at 2 secs
    pSocketRS485->Connect();

    BOOLEAN ret = False;
    SystemData& SysData = SystemData::Instance();
    GarfunkelData& GaData = GarfunkelData::Instance();
	std::cout << "<-------------IOBoardSyncThread thread : Started-------------->" << std::endl;

	try
	{

		while(True)
		{
			if(GaData._isMCAReady.Get()==True)
			{
				if(SysData._SimonIOBoardLocked.Get()==False && (SysData.GetOCapsuleLidState(0)==eSwitchOpen || SysData.GetOCapsuleLidState(1)==eSwitchOpen || SysData._GarfunkelIOBoardFaultLine.Get()==True))
				{
					std::cout << "Interlocking Simon Board" << std::endl;
					std::cout << "O1 LID="<<SysData.GetOCapsuleLidState(0)<< std::endl;
					std::cout << "O2 LID="<<SysData.GetOCapsuleLidState(1)<< std::endl;
					std::cout << " Garfunkel FaultLine ="<< SysData._GarfunkelIOBoardFaultLine.Get()<< std::endl;
					SysData.ResetAllOutputsForSimonBoard(pSocketRS485);
					SysData._SimonIOBoardLocked.Set(True);
				}
				if(SysData._GarfunkelIOBoardLocked.Get()==False && (SysData.GetHLidSwitchState() == eSwitchOpen || SysData.GetSLidSwitchState() == eSwitchOpen || SysData.GetSumpLevelSwitchState() == eOverflow || SysData.GetPressureSwitchState() == eOpen ||  SysData._SimonIOBoardFaultLine.Get()==True))
				{
					std::cout << "Interlocking Garfunkel Board" << std::endl;
					std::cout << "H LID="<<SysData.GetHLidSwitchState()<< std::endl;
					std::cout << "S LID="<<SysData.GetSLidSwitchState()<< std::endl;
					std::cout << "Pressure switch="<<SysData.GetPressureSwitchState()<< std::endl;
					std::cout << "Level  switch="<<SysData.GetSumpLevelSwitchState()<< std::endl;
					std::cout << " Simon FaultLine ="<< SysData._SimonIOBoardFaultLine.Get()<< std::endl;
					SysData.ResetAllOutputsForGarfunkelBoard(pSocketRS485);
					SysData._GarfunkelIOBoardLocked.Set(True);
				}
				//TODO check for pressure switch and main water inlet in certain conditiosns to initate locking..may not need if relying on fault line?

				//reset
				if(SysData._SimonIOBoardLocked.Get()==True && (SysData.GetOCapsuleLidState(0)==eSwitchClosed &&SysData.GetOCapsuleLidState(1)==eSwitchClosed&&SysData._GarfunkelIOBoardFaultLine.Get()==False))
				{
					std::cout << "Releasing Simon Board lock" << std::endl;
					SysData._SimonIOBoardLocked.Set(False);
				}

				if(SysData._GarfunkelIOBoardLocked.Get()==True && (SysData.GetHLidSwitchState() == eSwitchClosed&&SysData.GetSLidSwitchState() == eSwitchClosed&&SysData.GetSumpLevelSwitchState() != eOverflow&&SysData._SimonIOBoardFaultLine.Get()==False)) //TODO -Add overflow switch state
				{
					std::cout << "Releasing Garfunkel Board lock" << std::endl;
					SysData._GarfunkelIOBoardLocked.Set(False);
				}

				if(SysData._SimonIOBoardLocked.Get()==False&&SysData._GarfunkelIOBoardLocked.Get()==False)
				{

				}

			}

			sleep(10);
			//std::cout << "DispenseManager thread" << std::endl;
		} //while 1

	}
	catch (std::exception & e)
	{
		std::cout<<"DispenseManager :  Caught Exception : "<<e.what()<<std::endl;
        std::cout << "Exiting" << std::endl;
        GaData._continueRunning.Set(False);

	}

	return 0;
}



void Garfunkel::IOBoardSyncThread::Cleanup()
{
    // Cleanup
}
