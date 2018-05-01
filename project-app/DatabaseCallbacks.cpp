#include <string>
#include <sstream>
#include "DatabaseCallbacks.h"
#include "GarfunkelCommandProcessor.h"
#include "GarfunkelIPC.h"
#include "ProductData.h"


/////////////////////////////////////////////////////////
// Database callbacks
Garfunkel::SystemDataCallback::SystemDataCallback(const std::string & name) :
	Callback(name)
{
	_firstUpdate = True;
}

Garfunkel::SystemDataCallback::~SystemDataCallback()
{
}

BOOLEAN Garfunkel::SystemDataCallback::Update()
{
	BOOLEAN retValue = False;
	GarfunkelData & AqData = GarfunkelData::Instance();
	SystemData & SysData = SystemData::Instance();

	if(SysData.GetSystemState()==eIdle) //reset the state of system on if it is not changed
	{
		boost::bimap<std::string, int>::const_iterator iter, iend;
		std::stringstream cmd;
		std::cout<<"SYSTEM db CALLBACK called"<<std::endl;
		int n = 0;
		int prevLocale = SysData.Locale.Get();
		SysData._languageMgr.BuildStringMaps(); //build again
		retValue = SysData.ReadSystemDataFromDatabase(); //read only system data table here, do not configure machines as u may lose any active formula for machine otherwise


		GarfunkelCommandProcessorIOBoard & cmdProcIOBoard = GarfunkelCommandProcessorIOBoard::Instance();
		boost::shared_ptr<ecolab::ISocketCommunication> pSocketRS485;
		ecolab::SocketFactory & FactoryInstance = ecolab::SocketFactory::Instance();

		pSocketRS485.reset(FactoryInstance.CreateSocket(ecolab::eCondor, ecolab::eRS485WithReadTimeout));
		pSocketRS485->SetRS485ReadTimeout(2000); //set timeout at 2 secs
		pSocketRS485->Connect();
		cmdProcIOBoard.ExecuteCommand("ConfigureIOBoard", pSocketRS485, True);

		pSocketRS485->Disconnect();
		SysData.IsDirty.Set(False);
	}
	else
	{
		std::cout<<" Delaying SystemDataCallback...setting flag dirty for system data"<<std::endl;
		SysData.IsDirty.Set(True);
	}
	return (BOOLEAN) (retValue);
}	



///////////////////////////////////////////////////////////////////////////////////
// ProductMapCallback callback

Garfunkel::ProductMapCallback::ProductMapCallback(const std::string & name) :
	Callback(name)
{
}

Garfunkel::ProductMapCallback::~ProductMapCallback()
{
}

BOOLEAN Garfunkel::ProductMapCallback::Update()
{
    BOOLEAN         retValue = False;
    GarfunkelData &  AqData = GarfunkelData::Instance();
    SystemData &   SysData = SystemData::Instance();
    std::cout<<"ProductMap db callback called"<<std::endl;
    retValue = True;
    return (BOOLEAN)(retValue);
}


///////////////////////////////////////////////////////////////////////////////////
// ProductDataCallback callback

Garfunkel::ProductDataCallback::ProductDataCallback(const std::string & name) :
	Callback(name)
{
}

Garfunkel::ProductDataCallback::~ProductDataCallback()
{
}

BOOLEAN Garfunkel::ProductDataCallback::Update()
{
    BOOLEAN         retValue = False;
    std::cout<<"Productdata db CALLBACK called"<<std::endl;
    ProductData& ProdInfo = ProductData::Instance();
    ProdInfo.Reset();
    retValue = True;
    return (BOOLEAN)(retValue);
}



///////////////////////////////////////////////////////////////////////////////////
// ProductPulseCriteria callback

Garfunkel::ProductPulseCriteriaDataCallback::ProductPulseCriteriaDataCallback(const std::string & name) :
	Callback(name)
{
}

Garfunkel::ProductPulseCriteriaDataCallback::~ProductPulseCriteriaDataCallback()
{
}

BOOLEAN Garfunkel::ProductPulseCriteriaDataCallback::Update()
{
    BOOLEAN         retValue = False;
    std::cout<<"ProductPulseCriteria db CALLBACK called"<<std::endl;
    ProductData& ProdInfo = ProductData::Instance();
    ProdInfo.Reset();
    ProductData& ProdInfo1 = ProductData::Instance(); //this call will update context from db
    retValue = True;
    return (BOOLEAN)(retValue);
}


///////////////////////////////////////////////////////////////////////////////////
// DispenserPocketInfo callback

Garfunkel::DispenserPocketInfoDataCallback::DispenserPocketInfoDataCallback(const std::string & name) :
	Callback(name)
{
}

Garfunkel::DispenserPocketInfoDataCallback::~DispenserPocketInfoDataCallback()
{
}

BOOLEAN Garfunkel::DispenserPocketInfoDataCallback::Update()
{
    BOOLEAN         retValue = False;
    SystemData & SysData = SystemData::Instance();
    retValue = True;
    return (BOOLEAN)(retValue);
}


///////////////////////////////////////////////////////////////////////////////////
// ProductDataCallback callback

Garfunkel::LocalizedStringsCallback::LocalizedStringsCallback(const std::string & name) :
	Callback(name)
{
}

Garfunkel::LocalizedStringsCallback::~LocalizedStringsCallback()
{
}

BOOLEAN Garfunkel::LocalizedStringsCallback::Update()
{
    BOOLEAN         retValue = False;

    retValue = True;
    return (BOOLEAN)(retValue);
}


//////////////////////////////////////////////////////////////////////////

// This is the call back in case the database does not come up right away
Garfunkel::ThreadingCallback::ThreadingCallback(const std::string & name) :
    Callback(name)
{
}

Garfunkel::ThreadingCallback::~ThreadingCallback()
{
}

BOOLEAN Garfunkel::ThreadingCallback::Update()
{
    BOOLEAN         retValue = False;
    std::vector<int>::iterator iter, iend;

    GarfunkelData &  AqData = GarfunkelData::Instance();

    std::cout<<"Threading db CALLBACK called"<<std::endl;
    ecolab::ScopeLock Lock(AqData._dBSyncInProgressLock); //lock mutex and set flag
	AqData._dBSyncInProgress.Set(True);
	std::cout << "******ThreadingCallback::Update....Calling delayed callbacks*****************" << std::endl;
	/*strStream.str("");
	strStream<<AqData._uiAddressInstance<<":SU:64:1:";
	message.assign(strStream.str());
	SendMessageToUI(message); //send message to UI that DB is being updated and no operations, (like prime/calib/diagnostics and activation of formula) can continue*/
	while(AqData._alarmHandlerSleeping.Get()==False)
	{
		sleep(50); //wait for sometime cos Alarm handler can finish 1 round and stop checking for alarms
		std::cout << "ThreadingCallback::Update: After Sleep...waiting to Call system update callbacks..........." << std::endl;
	}


   	boost::shared_ptr<ProductDataCallback>              pdCallback(new ProductDataCallback("ProductDataCallback")); //update product data from DB
   	pdCallback->Update();
    boost::shared_ptr<SystemDataCallback>              sCallback(new SystemDataCallback("SystemDataCallback"));
    sCallback->Update();

    AqData._dBSyncInProgress.Set(False);
	/*strStream.str("");
	strStream<<AqData._uiAddressInstance<<":SU:64:0:";
	message.assign(strStream.str());
	SendMessageToUI(message); //send message to UI that DB is done updating and operations can resume*/
	time_t clock1 = time(0);
	struct tm *ct = localtime(&clock1);
	std::cout << "*******************ThreadingCallback::Update.... callback done****************** at"<<asctime(ct) << std::endl;
	clock_gettime(CLOCK_MONOTONIC, &AqData._timeOfLastDBSync);

	retValue = AqData._database->EstablishDatabaseConnection();

    if(NULL != AqData._database.get())
    {
    	 AqData._database->InitializeCallback();
    }
    std::cout << "*******************ThreadingCallback::Update returned="<<retValue<<std::endl;
    return (BOOLEAN)(retValue);
}
