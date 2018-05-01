#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "GarfunkelApp.h"
#include "ProductData.h"


Garfunkel::GarfunkelApp::GarfunkelApp():
_ipcThread("UI-IPCThread"),
_gIOBoardThread("GIOBoardThread", "aa", ""),
_sIOBoardThread("SIOBoardThread", "sa", ""),
_syncThread("DispenseThread"),
_diagThread("DiagnosticsThread"),
_alarmThread("AlarmThread"),
_dbThread("DBThread")
{

}

Garfunkel::GarfunkelApp::~GarfunkelApp()
{

}

void Garfunkel::GarfunkelApp::Initailize()
{
    Garfunkel::GarfunkelData & GarfunkelData = Garfunkel::GarfunkelData::Instance();
    GarfunkelData._database.reset(new Garfunkel::DatabaseCommands("Garfunkel", "db_controller", "controller"));
	Garfunkel::SystemData & SysData = Garfunkel::SystemData::Instance();
	Garfunkel::ProductData & prodData = Garfunkel::ProductData::Instance();
	Garfunkel::PocketInfoData & pocData = Garfunkel::PocketInfoData::Instance();
	//now init is done, unlock
	if (GarfunkelData._dBSyncInProgress.Get() == True)
	{
		std::cout << " Init done" << std::endl;
		GarfunkelData._dBSyncInProgress.Set(False);
		std::cout << " Unlocking mutex" << std::endl;
		GarfunkelData._dBSyncInProgressLock.Unlock(); //reset flag and then unlock mutex
	}

}


void Garfunkel::GarfunkelApp::Run()
{
	Garfunkel::GarfunkelData & GarfunkelData = Garfunkel::GarfunkelData::Instance();
	Garfunkel::AlarmSettings& AlarmData = Garfunkel::AlarmSettings::Instance();

    _ipcThread.Start(ecolab::Thread::JOINED, ecolab::Thread::MEDIUM_PRIORITY, 128 * 1024);

    _gIOBoardThread.Start(ecolab::Thread::JOINED, ecolab::Thread::MEDIUM_PRIORITY, 128 * 1024);

    _sIOBoardThread.Start(ecolab::Thread::JOINED, ecolab::Thread::MEDIUM_PRIORITY, 128 * 1024);

    _syncThread.Start(ecolab::Thread::JOINED, ecolab::Thread::MEDIUM_PRIORITY, 128 * 1024);

	_diagThread.Start(ecolab::Thread::JOINED, ecolab::Thread::MEDIUM_PRIORITY, 128 * 1024);

    _alarmThread.Start(ecolab::Thread::JOINED, ecolab::Thread::MEDIUM_PRIORITY, 128 * 1024);

	_dbThread.Start(ecolab::Thread::JOINED, ecolab::Thread::MEDIUM_PRIORITY, 128 * 1024);


	//Shilpa : Add threads for checking current operating schedule, Make Sump(O product cleanup) and Dispense

	BOOLEAN readyUpdate = False;
	while(True == GarfunkelData._continueRunning.Get())
    {
		timespec Now;
        clock_gettime(CLOCK_MONOTONIC, &Now);

        sleep(2);

        if(GarfunkelData._isMCAReady.Get()==False)
		{
        	GarfunkelData.ResetTimeouts(True);
			AlarmData.ClearAllAlarmsAndResetTimeouts(False);
			GarfunkelData.StartPollingAllBoards();
			GarfunkelData._isMCAReady.Set(True);

			std::cout<<"MCA is ready"<<std::endl;
		}

    }
	std::cout << "After GarfunkelData._continueRunning.Get loop" << std::endl;

	_ipcThread.Terminate();
    _gIOBoardThread.Terminate();
    _sIOBoardThread.Terminate();
	_syncThread.Terminate();
	_diagThread.Terminate();
	_alarmThread.Terminate();
	_dbThread.Terminate();
    std::cout << "Main : Before wait till complete" << std::endl;
    ecolab::Thread::WaitUntilComplete(_ipcThread);
    ecolab::Thread::WaitUntilComplete(_gIOBoardThread);
	ecolab::Thread::WaitUntilComplete(_sIOBoardThread);
	ecolab::Thread::WaitUntilComplete(_syncThread);
	ecolab::Thread::WaitUntilComplete(_diagThread);
	ecolab::Thread::WaitUntilComplete(_alarmThread);
    ecolab::Thread::WaitUntilComplete(_dbThread);
    std::cout << "Main : Wait till complete done for all threads" << std::endl;



}

void Garfunkel::GarfunkelApp::Cleanup()
{

}



