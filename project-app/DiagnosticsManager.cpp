#include <bitset>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "GarfunkelData.h"
#include "GarfunkelIPC.h"
#include "GarfunkelEnums.h"
#include "ElapsedTime.h"
#include "GarfunkelData.h"
#include "SprayObject.h"
#include "DiagnosticsManager.h"
#include "EventlogManager.h"
/////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
//  DiagnosticSystemData System Data
Garfunkel::DiagnosticSystemData::DiagnosticSystemData()
{
	WaterFlushInProgress.Set(False);
	DelayInProgress.Set(False);
	OnRequest.Set(False);
	DiagError.Set(False);
	SprayObjectRequested.Set(eUndefinedObj);
	memset(&LastUIUpdateTime, 0, sizeof(timespec));

}

Garfunkel::DiagnosticSystemData::DiagnosticSystemData(const DiagnosticSystemData& ObjectToCopy)
{

}
Garfunkel::DiagnosticSystemData::~DiagnosticSystemData()
{

	std::cout<<"DiagnosticSystemData destructor called"<<std::endl;

}

Garfunkel::DiagnosticSystemData&  Garfunkel::DiagnosticSystemData::Instance()
{
	static DiagnosticSystemData singleton;
	return singleton;
}

void Garfunkel::DiagnosticSystemData::SendOperationCompleteMessage()
{
	std::stringstream strStream;
	std::string str;
	GarfunkelData& AqData = GarfunkelData::Instance();

/*	if(ProductDispenseInProgress.Get()==True&&WaterFlushInProgress.Get()==True)
		strStream<<AqData._uiAddressInstance<<":SU:43:"<<ActivePocketId.Get()<<":0:2:";
	else if(FourthProductFlushValveFlushInProgress.Get()==True)
		strStream<<AqData._uiAddressInstance<<":SU:43:7:0:2:";
	else if(WaterFlushInProgress.Get()==True)
		strStream<<AqData._uiAddressInstance<<":SU:43:0:0:2:";
	str = strStream.str();
*/

	GarfunkelIPCMaster&  ipcMaster = GarfunkelIPCMaster::Instance();
    ipcMaster.SendESPCommandResponse(str);
    std::cout << "DiagnosticSystemData : Sent message to UI: " << str << std::endl;


}
void Garfunkel::DiagnosticSystemData::SendErrorMessage()
{
	std::stringstream strStream;
	std::string str;
	GarfunkelData& AqData = GarfunkelData::Instance();
	strStream<<AqData._uiAddressInstance<<":SU:58:"<<eDiagnosticInternalError<<":";
	str = strStream.str();

	GarfunkelIPCMaster&  ipcMaster = GarfunkelIPCMaster::Instance();
    ipcMaster.SendESPCommandResponse(str);
    std::cout << "DiagnosticSystemData : Sent message to UI: " << str << std::endl;

}
void Garfunkel::DiagnosticSystemData::SendMessageToUI(std::string & message)
{
	std::stringstream strStream;
	std::string str;
	GarfunkelData& AqData = GarfunkelData::Instance();

	strStream<<AqData._uiAddressInstance<<message;
	str = strStream.str();
	GarfunkelIPCMaster&  ipcMaster = GarfunkelIPCMaster::Instance();
    ipcMaster.SendESPCommandResponse(str);
    std::cout << "DiagnosticSystemData : Sent message to UI: " << str << std::endl;

}




void Garfunkel::DiagnosticSystemData::Reset()
{
	DiagError.Set(False);
	WaterFlushInProgress.Set(False);
	DelayInProgress.Set(False);
	OnRequest.Set(False);
	SprayObjectRequested.Set(eUndefinedObj);
	memset(&LastUIUpdateTime, 0, sizeof(timespec));
}



Garfunkel::DiagnosticsManager::DiagnosticsManager(const std::string & name) : Thread(name)
{
    
}

Garfunkel::DiagnosticsManager::DiagnosticsManager(const DiagnosticsManager &     objectToCopy)
{

}

Garfunkel::DiagnosticsManager::~DiagnosticsManager()
{

}


void Garfunkel::DiagnosticsManager::Cleanup()
{
    // Cleanup
}


int Garfunkel::DiagnosticsManager::Run()
{

    timespec Now;
    struct timespec     diagMainWaterFlushStartTime = {}, diagDelayStartTime = {};
    struct timespec     calibPumpStartTime = {}, calibFlushStartTime = {}, calibFlushStopTime = {};
    struct timespec		calibPumpStopTime = {}, calibPumpFinalStopTime = {}; //this is set when pump is stopped after 60 seconds
    struct timespec flushProdFlushStartTime = {}, flushOptFlushStartTime = {};

	BOOLEAN prodFlushDone = False;
	BOOLEAN optFlushDone = False;
    int primeFlushTime = 0;
    int diagPostFlushTime = 0;

	ecolab::SocketFactory & FactoryInstance = ecolab::SocketFactory::Instance();
    pSocketRS485.reset(FactoryInstance.CreateSocket(ecolab::eCondor, ecolab::eRS485));
    pSocketRS485->Connect();
    std::stringstream strStream;
    GarfunkelData& AqData = GarfunkelData::Instance();
	SystemData& SystemData = SystemData::Instance();
	DiagnosticSystemData& DiagData = DiagnosticSystemData::Instance();
	Garfunkel::EventDataLog &    log = Garfunkel::EventDataLog::Instance();
	AlarmSettings &  alarms =  AlarmSettings::Instance();
	SprayObjectFactory& sprayObjectFactory = SprayObjectFactory::Instance();
	boost::shared_ptr<SprayObject> sprayObj;

	std::cout << "<-------------DiagnosticsManager thread : Started-------------->" << std::endl;
	try
	{

	while(True)
	{

			clock_gettime(CLOCK_MONOTONIC, &Now);

			if(SystemData.DiagnosticEnabled.Get()==True&&SystemData.GetSystemState()==eDiagnosticsActive&&alarms.IsDiagnosticsAllowed()==True) //Diag activity
	        {
	    	   	 if(alarms.IsDiagnosticsAllowed()==False) //if state changes after the above if is satisified
	    	   	 {
	    	   		DiagData.DiagError.Set(True);
	    	   	 }
	    	   	 else if(DiagData.WaterFlushInProgress.Get()==True &&ElapsedTime(&DiagData.LastUIUpdateTime, &Now)> 1)
	        	{
	        		double flushTime = 0, delayTime = 0;
	        		if(DiagData.WaterFlushInProgress.Get()==True)
	        		    flushTime = ElapsedTime(&diagMainWaterFlushStartTime, &Now);
	        		DiagData.LastUIUpdateTime = Now;
	        		delayTime = ElapsedTime(&diagDelayStartTime, &Now);
	        		if(sprayObj)
	        		{
	        			if(DiagData.WaterFlushInProgress.Get()==True)
	        				sprayObj->SendSprayTimeToUi(flushTime);
	        			else if (DiagData.DelayInProgress.Get()==True)
	        				sprayObj->SendDelayTimeToUi(delayTime);
	        		}

	         		if((flushTime<diagPostFlushTime)&&((static_cast<unsigned int>(flushTime)%5)==0)&&flushTime>4)
	         		{
	         			if(sprayObj)
	         				sprayObj->KeepRunning();
	         		}
	        	}
	    	   	 else if(DiagData.WaterFlushInProgress.Get()==False&&DiagData.DelayInProgress.Get()==False&&DiagData.OnRequest.Get()==True&&DiagData.SprayObjectRequested.Get()!=eUndefinedObj) //main water inlet open
	        	{
	        		std::cout<<" Diagnostics :Starting main water flush....."<<std::endl;
	        		sprayObj = sprayObjectFactory.GetSprayObject(DiagData.SprayObjectRequested.Get()); //boost::shared_ptr<Garfunkel::SBlockSprayObject> ( new SBlockSprayObject());
	        		if(sprayObj)
	        		{
	        			sprayObj->Reset();
	        			sprayObj->SetSocket(pSocketRS485);
	        			clock_gettime(CLOCK_MONOTONIC, &diagDelayStartTime);
	        			DiagData.DelayInProgress.Set(True);
	        		}
	        	}

	    	   	else if(DiagData.WaterFlushInProgress.Get()==False&&DiagData.DelayInProgress.Get()==True&&DiagData.OnRequest.Get()==True&&DiagData.SprayObjectRequested.Get()!=eUndefinedObj&&ElapsedTime(&diagDelayStartTime,&Now) >10) //main water inlet open
	    	   	{

	        		if(sprayObj&&sprayObj->StartSpray())
	        		{
	        			clock_gettime(CLOCK_MONOTONIC, &diagMainWaterFlushStartTime);
	        			DiagData.WaterFlushInProgress.Set(True);
	        			diagPostFlushTime = MAX_FLUSH_FOR_WATER_INLET_DIAGNOSTICS;
	        			std::cout<<"Diagnostics : Opened main water valve..."<<std::endl;
	        		}
	        		else
	        		{
	        			std::cout<<"Diagnostics : Error occured while startign spray during diagnostics..resetting Diagdata"<<std::endl;
	        			DiagData.DiagError.Set(True);
	        		}

	    	   	}
	        	else if(DiagData.WaterFlushInProgress.Get()==True&&DiagData.SprayObjectRequested.Get()!=eUndefinedObj&&(DiagData.OnRequest.Get()==False || ElapsedTime(&diagMainWaterFlushStartTime,&Now) >diagPostFlushTime))  //water inlet close
	        	{

	        		if(sprayObj&&sprayObj->IsRunningAsReportedByIOBoard()==True)
	        		{
	        			if(DiagData.OnRequest.Get()==False )
	        			std::cout<<" Diagnostics :Water valve is open...UI asked to close"<<std::endl;
	        			else
	            		std::cout<<" Diagnostics :Max Time hit...Water valve is open...closing.."<<std::endl;
	        			if(sprayObj&&sprayObj->StopSpray())
	        			{
        					DiagData.SendOperationCompleteMessage(); //send diagnostic operation complete message
        					DiagData.Reset();
	        			}
	        			else
	        			{
	        				std::cout<<"Diagnostics : Failed to Close water inlet valve"<<std::endl;
	        				//log.EventLog(eInternalErrors, eDiagnosticInternalError, eWaterInletValveCloseOperationFailed, DispensingInfo.RespCode, DispensingInfo.ErrNo, -1, -1, DiagData.MachineId.Get()+1);
	            			DiagData.DiagError.Set(True);

	        			}
	        		}
	    			else
	    			{
	    				if(sprayObj)
	    				{
	    					sprayObj->StopSpray();
	    				}
	    				std::cout<<"Diagnostics : water inlet valve needs to be open to close during diagnostics"<<std::endl;
	    				//log.EventLog(eInternalErrors, eDiagnosticInternalError,  eWaterInletValveOpenOperationFailed, DispensingInfo.RespCode, DispensingInfo.ErrNo, -1, -1, DiagData.MachineId.Get()+1);
	        			DiagData.DiagError.Set(True);
	        			exit(0);
	    			}
	        	}
	        	if(DiagData.DiagError.Get()==True)
	        	{
	        		std::cout<<" Diagnostics : Error occured during diagnostics..resetting Diagdata"<<std::endl;
	        		DiagData.SendErrorMessage(); //send diagnostic process error message
	        		DiagData.SendOperationCompleteMessage(); //send diagnostic operation complete message
	            	DiagData.Reset();
	            	//SystemData.DiagnosticEnabled.Set(False);
	            	SystemData.ResetAllOutputsForSimonBoard(pSocketRS485);
	            	SystemData.ResetAllOutputsForGarfunkelBoard(pSocketRS485);
	        	}
	        }
			else if(SystemData.DiagnosticEnabled.Get()==True&&SystemData.GetSystemState()==eDiagnosticsActive&&alarms.IsDiagnosticsAllowed()==False&&DiagData.WaterFlushInProgress.Get()==True) //Diag activity
	        {
        		std::cout<<" Diagnostics : Error occured during diagnostics..resetting Diagdata"<<std::endl;
        		DiagData.SendErrorMessage(); //send diagnostic process error message
        		DiagData.SendOperationCompleteMessage(); //send diagnostic operation complete message
            	DiagData.Reset();
            	//SystemData.DiagnosticEnabled.Set(False);
            	SystemData.ResetAllOutputsForSimonBoard(pSocketRS485);
            	SystemData.ResetAllOutputsForGarfunkelBoard(pSocketRS485);
        		sprayObj.reset();
	        }



		sleep(75);

	} //while 1
	}
	catch (std::exception & e)
	{
		std::cout<<"DiagnosticsManager :  Caught Exception : "<<e.what()<<std::endl;
        std::cout << "Exiting" << std::endl;
        AqData._continueRunning.Set(False);
	}
	pSocketRS485->Disconnect();

	
    return 0;
}

