#include <bitset>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "ElapsedTime.h"
#include "GarfunkelData.h"
#include "SprayObject.h"

Garfunkel::SprayObjectFactory::SprayObjectFactory()
{
	CreateSparyObjects();
}


Garfunkel::SprayObjectFactory::~SprayObjectFactory()
{

	 if(_sprayObjPool.size() > 0)
	{
		 _sprayObjPool.erase(_sprayObjPool.begin(), _sprayObjPool.end());
	}

}

Garfunkel::SprayObjectFactory::SprayObjectFactory& Garfunkel::SprayObjectFactory::Instance()
{
	static SprayObjectFactory singleton;
	return singleton;

}

BOOLEAN   Garfunkel::SprayObjectFactory::CreateSparyObjects()
{
	ecolab::ScopeLock Lock(_sparyObjPoolLock);
	boost::shared_ptr<Garfunkel::SprayObject > conObj;
	for(int objType = (int) eSValve; objType < (int) eMaxSparyObj ; objType++)
	{
		switch((GarfunkelSparyObjType) objType)
		{
			case eSValve:
			{
				conObj = boost::shared_ptr<Garfunkel::SBlockSprayObject > (new SBlockSprayObject());
			}
			break;
			case ePValve:
			{
				conObj = boost::shared_ptr<Garfunkel::PBlockSprayObject > (new PBlockSprayObject());
			}
			break;
			case eAquanomicsToSumpValve:
			{
				conObj = boost::shared_ptr<Garfunkel::SumpValveSprayObject > (new SumpValveSprayObject());
			}
			break;
			case eO1Valve:
			{
				conObj = boost::shared_ptr<Garfunkel::OProductSprayObject > (new OProductSprayObject(0));
			}
			break;
			case eO2Valve:
			{
				conObj = boost::shared_ptr<Garfunkel::OProductSprayObject > (new OProductSprayObject(1));
			}
			break;
			case eDrainValve:
			{
				conObj = boost::shared_ptr<Garfunkel::DrainSprayObject > (new DrainSprayObject());
			}
			break;


		}
		if(conObj)
		{
			_sprayObjPool[(GarfunkelSparyObjType)objType]= conObj;
			std::cout<<" Adding ConObj type="<<objType<<std::endl;
			conObj.reset();

		}
	}
	return True;

}

boost::shared_ptr< Garfunkel::SprayObject > Garfunkel::SprayObjectFactory::GetSprayObject(GarfunkelSparyObjType Id)
{

	ecolab::ScopeLock Lock(_sparyObjPoolLock);
	boost::shared_ptr< Garfunkel::SprayObject>  obj;
	std::map<GarfunkelSparyObjType, boost::shared_ptr<Garfunkel::SprayObject> > ::const_iterator iter;
	obj.reset();
	iter = _sprayObjPool.find((GarfunkelSparyObjType) Id);
	if(iter!=_sprayObjPool.end())
	 return iter->second;
	else
	return obj;

}

Garfunkel::SprayObject::SprayObject()
{
	std::cout<<"SprayObject constructor called"<<std::endl;
	_enable= False;
	_isRunning  = False;
	_timer = 10;

}

Garfunkel::MainWaterInletSprayObject::MainWaterInletSprayObject()
{
	std::cout<<"MainWaterInletSprayObject constructor called"<<std::endl;
	std::stringstream cmd;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	cmd<<"SetMainWaterInletState";
	_msg = cmdProcIOBoard.GetCommand(cmd.str());
	_cmdString.assign("SetMainWaterInletState");

	if(_msg.get()!=NULL)
	{
		_pCmd = (SetMainWaterInletStateOnSIOB*)_msg.get();
	}
}

Garfunkel::MainWaterInletSprayObject::~MainWaterInletSprayObject()
{
	std::cout<<"MainWaterInletSprayObject destructor called"<<std::endl;
}

BOOLEAN Garfunkel::MainWaterInletSprayObject::StartCommand()
{
	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();

	if(_msg.get()!=NULL)
	{
		_pCmd = (SetMainWaterInletStateOnSIOB*)_msg.get();
		if(_pCmd!=NULL)
		{
			_pCmd->SetMainWaterInletState(eOpen);
			if(_timer< 0 || _timer >10)
				_timer = 10;
			_pCmd->SetTimeInterval(_timer);
			retValue = cmdProcIOBoard.ExecuteCommand(_cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"*** MainWaterInlet OPEN at "<<asctime(ct)<<std::endl;

			}
			else
			{
				//RespCode = msg->_respCode ;
		        //ErrNo = msg->_errNo ;
				std::cout<<"DispensingThread: Setting Main Valve to OPEN state FAILED!!!"<<std::endl;
			}
		}
	}

   return retValue;

}

BOOLEAN Garfunkel::MainWaterInletSprayObject::StartSpray()
{
	BOOLEAN retValue = False;

	if(IsRunning()==False)
	{
		retValue = StartCommand();
		SetRunState(retValue);
	}

   return retValue;

}


BOOLEAN Garfunkel::MainWaterInletSprayObject::StopSpray()
{
	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	if(_msg.get()!=NULL)
	{
		_pCmd = (SetMainWaterInletStateOnSIOB*)_msg.get();
		if(_pCmd!=NULL)
		{
			_pCmd->SetMainWaterInletState(eClose);
			retValue = cmdProcIOBoard.ExecuteCommand(_cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"***MainWaterInlet CLOSED at "<<asctime(ct)<<std::endl;
				SetRunState(retValue);
			}
			else
			{
//		        RespCode = msg->_respCode ;
//		        ErrNo = msg->_errNo ;
				SetRunState(retValue);
				std::cout<<"DispensingThread: Setting main Valve  to off state FAILED!!!"<<std::endl;
			}
		}
	}

   return retValue;
}

BOOLEAN Garfunkel::MainWaterInletSprayObject::KeepRunning()
{
	BOOLEAN retValue = False;
	retValue = StartCommand();
	return retValue;
}

BOOLEAN Garfunkel::MainWaterInletSprayObject::IsRunningAsReportedByIOBoard()
{
	BOOLEAN retValue = False;
	SystemData& SysData = SystemData::Instance();
   if(SysData.GetMainWaterInletState()==eOpen)
   {
	   retValue = True;

   }
   else
   {
		time_t clock1 = time(0);
		struct tm *ct = localtime(&clock1);
		std::cout<<"MainWaterInletSprayObject : main water inlet not open at"<<asctime(ct)<<std::endl;
   }
   return retValue;
}

void Garfunkel::MainWaterInletSprayObject::SendSprayTimeToUi(double flushTime)
{
	std::cout<<"MainWaterInletSprayObject : SendSprayTimeToUi called "<<std::endl;
	std::stringstream strStream;
	std::string str;
	GarfunkelData& AqData = GarfunkelData::Instance();
	SystemData& SystemData = SystemData::Instance();
	std::string flushTimeString = boost::lexical_cast<std::string>(ceil(flushTime));
	strStream<<AqData._uiAddressInstance<<":SU:66:"<<flushTimeString<<":"<<SystemData.Conductivity.Get()<<":"<<SystemData.TempInDegreeF.Get()<<":"<<SystemData.GetPressureSwitchState()<<":";
	str = strStream.str();
	GarfunkelIPCMaster&  ipcMaster = GarfunkelIPCMaster::Instance();
	ipcMaster.SendESPCommandResponse(str);
	std::cout << "MainWaterInletSprayObject : Sent message to UI: " << str << std::endl;
}

void Garfunkel::MainWaterInletSprayObject::SendDelayTimeToUi(double flushTime)
{
	std::cout<<"MainWaterInletSprayObject : SendDelayTimeToUi called "<<std::endl;
	std::stringstream strStream;
	std::string str;
	GarfunkelData& AqData = GarfunkelData::Instance();
	SystemData& SystemData = SystemData::Instance();
	std::string flushTimeString = boost::lexical_cast<std::string>(ceil(flushTime));
	strStream<<AqData._uiAddressInstance<<":SU:65:"<<flushTimeString<<":";
	str = strStream.str();
	GarfunkelIPCMaster&  ipcMaster = GarfunkelIPCMaster::Instance();
	ipcMaster.SendESPCommandResponse(str);
	std::cout << "MainWaterInletSprayObject : Sent message to UI: " << str << std::endl;
}

Garfunkel::SBlockSprayObject::SBlockSprayObject()
{
	std::cout<<"SBlockSprayObject constructor called"<<std::endl;
	std::stringstream cmd;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	cmd<<"SetSValveState";
	msg = cmdProcIOBoard.GetCommand(cmd.str());
	cmdString.assign("SetSValveState");

	if(msg.get()!=NULL)
	{
		pCmd = (SetSValveStateOnSIOB*)msg.get();
	}
}

Garfunkel::SBlockSprayObject::~SBlockSprayObject()
{

}

BOOLEAN Garfunkel::SBlockSprayObject::StartCommand()
{
	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();

	if(msg.get()!=NULL&&MainWaterInletSprayObject::StartCommand()==True)
	{
		pCmd = (SetSValveStateOnSIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetSValveState(eOpen);
			if(_timer< 0 || _timer >10)
				_timer = 10;
			pCmd->SetTimeInterval(_timer);
			retValue = cmdProcIOBoard.ExecuteCommand(cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"*** S valve OPEN at "<<asctime(ct)<<std::endl;
			}
			else
			{
				//RespCode = msg->_respCode ;
		        //ErrNo = msg->_errNo ;
				std::cout<<"DispensingThread: Setting S Valve to OPEN state FAILED!!!"<<std::endl;
			}
		}
	}

	return retValue;

}

BOOLEAN Garfunkel::SBlockSprayObject::StartSpray()
{
	BOOLEAN retValue = False;

	if(IsRunning()==False)
	{
		retValue = StartCommand();
		SetRunState(retValue);
	}
   return retValue;

}

BOOLEAN Garfunkel::SBlockSprayObject::StopSpray()
{


	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	if(msg.get()!=NULL&&MainWaterInletSprayObject::StopSpray())
	{
		pCmd = (SetSValveStateOnSIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetSValveState(eClose);
			retValue = cmdProcIOBoard.ExecuteCommand(cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"***S Valve CLOSED at "<<asctime(ct)<<std::endl;
				SetRunState(retValue);
			}
			else
			{
//		        RespCode = msg->_respCode ;
//		        ErrNo = msg->_errNo ;
				std::cout<<"DispensingThread: Setting S Valve  to off state FAILED!!!"<<std::endl;
				SetRunState(retValue);
			}
		}
	}

   return retValue;
}

BOOLEAN Garfunkel::SBlockSprayObject::KeepRunning()
{
	BOOLEAN retValue = False;
	retValue = StartCommand();
	return retValue;
}

BOOLEAN Garfunkel::SBlockSprayObject::IsRunningAsReportedByIOBoard()
{
	BOOLEAN retValue = False;
	SystemData& SysData = SystemData::Instance();
	if(MainWaterInletSprayObject::IsRunningAsReportedByIOBoard())
	{
		retValue = (SysData.GetSValveState()==eOpen) ? True : False;
	}
	if(retValue==False)
	{
		time_t clock1 = time(0);
		struct tm *ct = localtime(&clock1);
		std::cout<<"SBlockSprayObject not open at "<<asctime(ct)<<std::endl;
	}
	return retValue;
}


Garfunkel::PBlockSprayObject::PBlockSprayObject()
{
	std::cout<<"PBlockSprayObject constructor called"<<std::endl;
	std::stringstream cmd;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	cmd<<"SetPValveState";
	msg = cmdProcIOBoard.GetCommand(cmd.str());
	cmdString.assign("SetPValveState");

	if(msg.get()!=NULL)
	{
		pCmd = (SetPValveStateOnSIOB*)msg.get();
	}
}

Garfunkel::PBlockSprayObject::~PBlockSprayObject()
{

}

BOOLEAN Garfunkel::PBlockSprayObject::StartCommand()
{
	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();

	if(msg.get()!=NULL&&MainWaterInletSprayObject::StartCommand()==True)
	{
		pCmd = (SetPValveStateOnSIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetPValveState(eOpen);
			if(_timer< 0 || _timer >10)
				_timer = 10;
			pCmd->SetTimeInterval(_timer);
			retValue = cmdProcIOBoard.ExecuteCommand(cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"*** P valve OPEN at "<<asctime(ct)<<std::endl;
			}
			else
			{
				//RespCode = msg->_respCode ;
		        //ErrNo = msg->_errNo ;
				std::cout<<"DispensingThread: Setting P Valve to OPEN state FAILED!!!"<<std::endl;
			}
		}
	}

	return retValue;

}

BOOLEAN Garfunkel::PBlockSprayObject::StartSpray()
{
	BOOLEAN retValue = False;

	if(IsRunning()==False)
	{
		retValue = StartCommand();
		SetRunState(True);
	}
   return retValue;

}

BOOLEAN Garfunkel::PBlockSprayObject::StopSpray()
{


	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	if(msg.get()!=NULL&&MainWaterInletSprayObject::StopSpray())
	{
		pCmd = (SetPValveStateOnSIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetPValveState(eClose);
			retValue = cmdProcIOBoard.ExecuteCommand(cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"***P Valve CLOSED at "<<asctime(ct)<<std::endl;
				SetRunState(retValue);
			}
			else
			{
//		        RespCode = msg->_respCode ;
//		        ErrNo = msg->_errNo ;
				std::cout<<"DispensingThread: Setting P Valve  to off state FAILED!!!"<<std::endl;
				SetRunState(retValue);
			}
		}
	}

   return retValue;
}

BOOLEAN Garfunkel::PBlockSprayObject::KeepRunning()
{
	BOOLEAN retValue = False;
	retValue = StartCommand();
	return retValue;
}

BOOLEAN Garfunkel::PBlockSprayObject::IsRunningAsReportedByIOBoard()
{
	BOOLEAN retValue = False;
	SystemData& SysData = SystemData::Instance();
	if(MainWaterInletSprayObject::IsRunningAsReportedByIOBoard())
	{
		retValue = (SysData.GetPValveState()==eOpen) ? True : False;
	}
	if(retValue==False)
	{
		time_t clock1 = time(0);
		struct tm *ct = localtime(&clock1);
		std::cout<<"PBlockSprayObject not open at"<<asctime(ct)<<std::endl;
	}
	return retValue;
}

Garfunkel::AquanomicsPumpObject::AquanomicsPumpObject()
{
	std::cout<<"AquanomicsPumpObject constructor called"<<std::endl;
	std::stringstream cmd;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	cmd<<"SetGarfunkelPumpState";
	msg = cmdProcIOBoard.GetCommand(cmd.str());
	cmdString.assign("SetGarfunkelPumpState");

	if(msg.get()!=NULL)
	{
		pCmd = (SetGarfunkelPumpStateOnGIOB*)msg.get();
	}
}

Garfunkel::AquanomicsPumpObject::~AquanomicsPumpObject()
{

}

BOOLEAN Garfunkel::AquanomicsPumpObject::StartCommand()
{
	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();

	if(msg.get()!=NULL&&AquanomicsDilutionSprayObject::StartCommand()==True)
	{
		pCmd = (SetGarfunkelPumpStateOnGIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetGarfunkelPumpState(eOn);
			if(_timer< 0 || _timer >10)
				_timer = 10;
			pCmd->SetTimeInterval(_timer);
			retValue = cmdProcIOBoard.ExecuteCommand(cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"*** Garfunkel PUMP ON at "<<asctime(ct)<<std::endl;
			}
			else
			{
				//RespCode = msg->_respCode ;
		        //ErrNo = msg->_errNo ;
				std::cout<<"DispensingThread: Setting Garfunkel PUMP OFF state FAILED!!!"<<std::endl;
			}
		}
	}

	return retValue;
}

BOOLEAN Garfunkel::AquanomicsPumpObject::StartSpray()
{
	BOOLEAN retValue = False;

	if(IsRunning()==False)
	{
		retValue = StartCommand();
		SetRunState(retValue);
	}
   return retValue;

}

BOOLEAN Garfunkel::AquanomicsPumpObject::StopSpray()
{
	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	if(msg.get()!=NULL&&AquanomicsDilutionSprayObject::StopSpray())
	{
		pCmd = (SetGarfunkelPumpStateOnGIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetGarfunkelPumpState(eOff);
			retValue = cmdProcIOBoard.ExecuteCommand(cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"***Garfunkel Pump Off at "<<asctime(ct)<<std::endl;
				SetRunState(retValue);
			}
			else
			{
//		        RespCode = msg->_respCode ;
//		        ErrNo = msg->_errNo ;
				std::cout<<"DispensingThread: Setting Garfunkel Pump Off state FAILED!!!"<<std::endl;
				SetRunState(retValue);
			}
		}
	}

   return retValue;
}

BOOLEAN Garfunkel::AquanomicsPumpObject::KeepRunning()
{
	BOOLEAN retValue = False;
	retValue = StartCommand();
	return retValue;
}

BOOLEAN Garfunkel::AquanomicsPumpObject::IsRunningAsReportedByIOBoard()
{
	BOOLEAN retValue = False;
	SystemData& SysData = SystemData::Instance();
	if(AquanomicsDilutionSprayObject::IsRunningAsReportedByIOBoard())
	{
		retValue = (SysData.GetGarfunkelPumpState()==eOn) ? True : False;
	}
	if(retValue==False)
	{
		time_t clock1 = time(0);
		struct tm *ct = localtime(&clock1);
		std::cout<<"Pump not open at"<<asctime(ct)<<std::endl;
	}

	return retValue;
}



Garfunkel::AquanomicsDilutionSprayObject::AquanomicsDilutionSprayObject()
{
	std::cout<<"AquanomicsDilutionSprayObject constructor called"<<std::endl;
	std::stringstream cmd;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	cmd<<"SetDilutionValveState";
	msg = cmdProcIOBoard.GetCommand(cmd.str());
	cmdString.assign("SetDilutionValveState");

	if(msg.get()!=NULL)
	{
		pCmd = (SetDilutionValveStateOnGIOB*)msg.get();
	}
}

Garfunkel::AquanomicsDilutionSprayObject::~AquanomicsDilutionSprayObject()
{

}

BOOLEAN Garfunkel::AquanomicsDilutionSprayObject::StartCommand()
{
	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();

	if(msg.get()!=NULL&&MainWaterInletSprayObject::StartCommand()==True)
	{
		pCmd = (SetDilutionValveStateOnGIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetDilutionValveState(eOpen);
			if(_timer< 0 || _timer >10)
				_timer = 10;
			pCmd->SetTimeInterval(_timer);
			retValue = cmdProcIOBoard.ExecuteCommand(cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"*** Dilution valve OPEN at "<<asctime(ct)<<std::endl;
			}
			else
			{
				//RespCode = msg->_respCode ;
		        //ErrNo = msg->_errNo ;
				std::cout<<"DispensingThread: Setting Dilution Valve to OPEN state FAILED!!!"<<std::endl;
			}
		}
	}

	return retValue;
}

BOOLEAN Garfunkel::AquanomicsDilutionSprayObject::StartSpray()
{
	BOOLEAN retValue = False;

	if(IsRunning()==False)
	{
		retValue = StartCommand();
		SetRunState(retValue);
	}
   return retValue;

}

BOOLEAN Garfunkel::AquanomicsDilutionSprayObject::StopSpray()
{
	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	if(msg.get()!=NULL&&MainWaterInletSprayObject::StopSpray())
	{
		pCmd = (SetDilutionValveStateOnGIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetDilutionValveState(eClose);
			retValue = cmdProcIOBoard.ExecuteCommand(cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"***Dilution Valve CLOSED at "<<asctime(ct)<<std::endl;
				SetRunState(retValue);
			}
			else
			{
//		        RespCode = msg->_respCode ;
//		        ErrNo = msg->_errNo ;
				std::cout<<"DispensingThread: Setting Dilution Valve  to off state FAILED!!!"<<std::endl;
				SetRunState(retValue);
			}
		}
	}

   return retValue;
}

BOOLEAN Garfunkel::AquanomicsDilutionSprayObject::KeepRunning()
{
	BOOLEAN retValue = False;
	retValue = StartCommand();
	return retValue;
}

BOOLEAN Garfunkel::AquanomicsDilutionSprayObject::IsRunningAsReportedByIOBoard()
{
	BOOLEAN retValue = False;
	SystemData& SysData = SystemData::Instance();
	if(MainWaterInletSprayObject::IsRunningAsReportedByIOBoard())
	{
		retValue = (SysData.GetDilutionValveState()==eOpen) ? True : False;
	}
	if(retValue==False)
	{
		time_t clock1 = time(0);
		struct tm *ct = localtime(&clock1);
		std::cout<<"AquanomicsDilutionSprayObject not open at"<<asctime(ct)<<std::endl;
	}
	return retValue;

}

Garfunkel::SumpValveSprayObject::SumpValveSprayObject()
{
	std::cout<<"SumpValveSprayObject constructor called"<<std::endl;
	std::stringstream cmd;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	cmd<<"SetSumpValveState";
	msg = cmdProcIOBoard.GetCommand(cmd.str());
	cmdString.assign("SetSumpValveState");

	if(msg.get()!=NULL)
	{
		pCmd = (SetSumpValveStateOnGIOB*)msg.get();
	}
}

Garfunkel::SumpValveSprayObject::~SumpValveSprayObject()
{

}

BOOLEAN Garfunkel::SumpValveSprayObject::StartCommand()
{
	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();

	if(msg.get()!=NULL&&AquanomicsPumpObject::StartCommand()==True)
	{
		pCmd = (SetSumpValveStateOnGIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetSumpValveState(eOpen);
			if(_timer< 0 || _timer >10)
				_timer = 10;
			pCmd->SetTimeInterval(_timer);
			retValue = cmdProcIOBoard.ExecuteCommand(cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"*** Sump valve OPEN at "<<asctime(ct)<<std::endl;
			}
			else
			{
				//RespCode = msg->_respCode ;
		        //ErrNo = msg->_errNo ;
				std::cout<<"DispensingThread: Setting Sump Valve to OPEN state FAILED!!!"<<std::endl;
			}
		}
	}

	return retValue;
}

BOOLEAN Garfunkel::SumpValveSprayObject::StartSpray()
{
	BOOLEAN retValue = False;

	if(IsRunning()==False)
	{
		retValue = StartCommand();
		SetRunState(retValue);
	}
   return retValue;

}

BOOLEAN Garfunkel::SumpValveSprayObject::StopSpray()
{


	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	if(msg.get()!=NULL&&AquanomicsPumpObject::StopSpray())
	{
		pCmd = (SetSumpValveStateOnGIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetSumpValveState(eClose);
			retValue = cmdProcIOBoard.ExecuteCommand(cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"***Sump Valve CLOSED at "<<asctime(ct)<<std::endl;
				SetRunState(retValue);
			}
			else
			{
//		        RespCode = msg->_respCode ;
//		        ErrNo = msg->_errNo ;
				std::cout<<"DispensingThread: Setting Sump Valve  to off state FAILED!!!"<<std::endl;
				SetRunState(retValue);
			}
		}
	}

   return retValue;
}

BOOLEAN Garfunkel::SumpValveSprayObject::KeepRunning()
{
	BOOLEAN retValue = False;
	retValue = StartCommand();
	return retValue;
}

BOOLEAN Garfunkel::SumpValveSprayObject::IsRunningAsReportedByIOBoard()
{
	BOOLEAN retValue = False;
	SystemData& SysData = SystemData::Instance();
	if(AquanomicsPumpObject::IsRunningAsReportedByIOBoard())
	{
		retValue = (SysData.GetSumpValveState()==eOpen) ? True : False;
	}
	if(retValue==False)
	{
		time_t clock1 = time(0);
		struct tm *ct = localtime(&clock1);
		std::cout<<"SumpValveSprayObject not open at"<<asctime(ct)<<std::endl;
	}
	return retValue;

}


Garfunkel::OProductSprayObject::OProductSprayObject(int n)
{
	_no = n;
	std::cout<<"OProductSprayObject constructor called"<<std::endl;
	std::stringstream cmd;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	cmd<<"SetOCapsuleValveState";
	msg = cmdProcIOBoard.GetCommand(cmd.str());
	cmdString.assign("SetOCapsuleValveState");

	if(msg.get()!=NULL)
	{
		pCmd = (SetOCapsuleValveStateOnGIOB*)msg.get();
	}
}

Garfunkel::OProductSprayObject::~OProductSprayObject()
{

}

BOOLEAN Garfunkel::OProductSprayObject::StartCommand()
{
	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();

	if(msg.get()!=NULL&&SumpValveSprayObject::StartCommand()==True)
	{
		pCmd = (SetOCapsuleValveStateOnGIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetOCapsuleValveState(_no, eOpen);
			if(_timer< 0 || _timer >10)
				_timer = 10;
			pCmd->SetTimeInterval(_timer);
			retValue = cmdProcIOBoard.ExecuteCommand(cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"*** O valve OPEN at "<<asctime(ct)<<std::endl;
			}
			else
			{
				//RespCode = msg->_respCode ;
		        //ErrNo = msg->_errNo ;
				std::cout<<"DispensingThread: Setting O Valve to OPEN state FAILED!!!"<<std::endl;
			}
		}
	}

	return retValue;
}

BOOLEAN Garfunkel::OProductSprayObject::StartSpray()
{
	BOOLEAN retValue = False;

	if(IsRunning()==False)
	{
		retValue = StartCommand();
		SetRunState(retValue);
	}
   return retValue;

}

BOOLEAN Garfunkel::OProductSprayObject::StopSpray()
{


	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	if(msg.get()!=NULL&&SumpValveSprayObject::StopSpray())
	{
		pCmd = (SetOCapsuleValveStateOnGIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetOCapsuleValveState(_no, eClose);
			retValue = cmdProcIOBoard.ExecuteCommand(cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"***O Valve CLOSED at "<<asctime(ct)<<std::endl;
				SetRunState(retValue);
			}
			else
			{
//		        RespCode = msg->_respCode ;
//		        ErrNo = msg->_errNo ;
				std::cout<<"DispensingThread: Setting O Valve  to off state FAILED!!!"<<std::endl;
				SetRunState(retValue);
			}
		}
	}

   return retValue;
}

BOOLEAN Garfunkel::OProductSprayObject::KeepRunning()
{
	BOOLEAN retValue = False;
	retValue = StartCommand();
	return retValue;
}

BOOLEAN Garfunkel::OProductSprayObject::IsRunningAsReportedByIOBoard()
{
	BOOLEAN retValue = False;
	SystemData& SysData = SystemData::Instance();
	if(SumpValveSprayObject::IsRunningAsReportedByIOBoard())
	{
		retValue = (SysData.GetOCapsuleValveState(_no)==eOpen) ? True : False;
	}
	if(retValue==False)
	{
		time_t clock1 = time(0);
		struct tm *ct = localtime(&clock1);
		std::cout<<"OProductSprayObject not open --no="<<_no<<" at"<<asctime(ct)<<std::endl;
	}
	return retValue;

}

Garfunkel::DrainSprayObject::DrainSprayObject()
{
	std::cout<<"DrainSprayObject constructor called"<<std::endl;
	std::stringstream cmd;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	cmd<<"SetDrainValveState";
	msg = cmdProcIOBoard.GetCommand(cmd.str());
	cmdString.assign("SetDrainValveState");

	if(msg.get()!=NULL)
	{
		pCmd = (SetDrainValveStateOnGIOB*)msg.get();
	}
}

Garfunkel::DrainSprayObject::~DrainSprayObject()
{

}

BOOLEAN Garfunkel::DrainSprayObject::StartCommand()
{
	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();

	if(msg.get()!=NULL&&AquanomicsDilutionSprayObject::StartCommand()==True)
	{
		pCmd = (SetDrainValveStateOnGIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetDrainValveState(eOpen);
			if(_timer< 0 || _timer >10)
				_timer = 10;
			pCmd->SetTimeInterval(_timer);
			retValue = cmdProcIOBoard.ExecuteCommand(cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"*** Drain valve OPEN at "<<asctime(ct)<<std::endl;
			}
			else
			{
				//RespCode = msg->_respCode ;
		        //ErrNo = msg->_errNo ;
				std::cout<<"DispensingThread: Setting Drain Valve to OPEN state FAILED!!!"<<std::endl;
			}
		}
	}

	return retValue;
}

BOOLEAN Garfunkel::DrainSprayObject::StartSpray()
{
	BOOLEAN retValue = False;

	if(IsRunning()==False)
	{
		retValue = StartCommand();
		SetRunState(retValue);
	}
   return retValue;

}

BOOLEAN Garfunkel::DrainSprayObject::StopSpray()
{
	BOOLEAN retValue = False;
	GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
	if(msg.get()!=NULL&&AquanomicsDilutionSprayObject::StopSpray())
	{
		pCmd = (SetDrainValveStateOnGIOB*)msg.get();
		if(pCmd!=NULL)
		{
			pCmd->SetDrainValveState(eClose);
			retValue = cmdProcIOBoard.ExecuteCommand(cmdString, _pSocketRS485, True);
			if(retValue==True)
			{
				time_t clock1 = time(0);
				struct tm *ct = localtime(&clock1);
				std::cout<<"***Drain Valve CLOSED at "<<asctime(ct)<<std::endl;
				SetRunState(retValue);
			}
			else
			{
//		        RespCode = msg->_respCode ;
//		        ErrNo = msg->_errNo ;
				std::cout<<"DispensingThread: Setting Drain Valve  to off state FAILED!!!"<<std::endl;
				SetRunState(retValue);
			}
		}
	}

   return retValue;
}

BOOLEAN Garfunkel::DrainSprayObject::KeepRunning()
{
	BOOLEAN retValue = False;
	retValue = StartCommand();
	return retValue;
}

BOOLEAN Garfunkel::DrainSprayObject::IsRunningAsReportedByIOBoard()
{
	BOOLEAN retValue = False;
	SystemData& SysData = SystemData::Instance();
	if(AquanomicsDilutionSprayObject::IsRunningAsReportedByIOBoard())
	{
		retValue = (SysData.GetDrainValveState()==eOpen) ? True : False;
	}
	if(retValue==False)
	{
		time_t clock1 = time(0);
		struct tm *ct = localtime(&clock1);
		std::cout<<"DrainSprayObject not open at"<<asctime(ct)<<std::endl;
	}
	return retValue;

}

