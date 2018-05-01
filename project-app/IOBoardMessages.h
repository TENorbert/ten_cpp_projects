//
//
//
//  @ File Name : IOBoardMessages.h
//  @ Date : 6/14/2012
//  @ Author : 
//
//


#if !defined(_IOBOARDMESSAGING_H)
#define _IOBOARDMESSAGING_H
#include "BoardCommands.h"
#include "GarfunkelData.h"
namespace Garfunkel
{

		//Get Commands, created and put in _ioBoardMessages vector
	    // DI

		//This will configure IOboard . : will send init params to IOBoard


     class ConfigureIOBoard : public IIOBoardMessage
     {
     public:
    	 ConfigureIOBoard(std::string & addressInstance);
    	 virtual ~ConfigureIOBoard();
    	 virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);
    	 virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);
    	 virtual int HandleIPCResponse(std::string &     response);
     private:
     };


    class DIBoardMessage : public IIOBoardMessage
    {
    public:
        DIBoardMessage(std::string & addressInstance);
        virtual ~DIBoardMessage();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);  // This will check if the message should be run
        virtual int HandleIPCResponse(std::string &     response);

    };



    //DU:20, temp+conductivity
    class GetAnalogSensorDatafromGIOB : public IIOBoardTimedMessage
    {

    public:
    	GetAnalogSensorDatafromGIOB(std::string & addressInstance);
        virtual ~GetAnalogSensorDatafromGIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);  // This will check if the message should be run
        virtual int HandleIPCResponse(std::string &     response);

    };


    //DU:24
    class GetDigitalInputOutputStatefromGIOB  : public IIOBoardTimedMessage
    {

    public:
        GetDigitalInputOutputStatefromGIOB(std::string & addressInstance);
        virtual ~GetDigitalInputOutputStatefromGIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);       // Will send the data 
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);  // This will check if the message should be run
        virtual int HandleIPCResponse(std::string &     response);

    };
    
    


	class SetDilutionValveStateOnGIOB : public IIOBoardTimedMessage
    {
		private:
		GarfunkelValveState _eOpenOrClosed;
		std::string _onCommand;
		std::string _offCommand;
    public:
		SetDilutionValveStateOnGIOB(std::string & addressInstance);
		void SetDilutionValveState( GarfunkelValveState eOpenOrClosed);
        virtual ~SetDilutionValveStateOnGIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);
        virtual int HandleIPCResponse(std::string &     response);
    };

	class SetOCapsuleValveStateOnGIOB : public IIOBoardTimedMessage
    {
		private:
		int _OCapsuleId;
		GarfunkelValveState _eOpenOrClosed;
		std::string _onCommand;
		std::string _offCommand;

    public:
        SetOCapsuleValveStateOnGIOB(std::string & addressInstance); 
		void SetOCapsuleValveState( int washerId, GarfunkelValveState eOpenOrClosed);
        virtual ~SetOCapsuleValveStateOnGIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);       
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);  
        virtual int HandleIPCResponse(std::string &     response);    
    };

	// drain valve
	class SetDrainValveStateOnGIOB : public IIOBoardTimedMessage
    {
		private:
		GarfunkelValveState _eOpenOrClosed;
		std::string _onCommand;
		std::string _offCommand;

    public:
		SetDrainValveStateOnGIOB(std::string & addressInstance);
		void SetDrainValveState( GarfunkelValveState eOpenOrClosed);
        virtual ~SetDrainValveStateOnGIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);       
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);  
        virtual int HandleIPCResponse(std::string &     response);    
    };


	//sump valve
	class SetSumpValveStateOnGIOB : public IIOBoardTimedMessage
    {
		private:
		GarfunkelValveState _eOpenOrClosed;
		std::string _onCommand;
		std::string _offCommand;

    public:
		SetSumpValveStateOnGIOB(std::string & addressInstance);
		void SetSumpValveState( GarfunkelValveState eOpenOrClosed);
        virtual ~SetSumpValveStateOnGIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);
        virtual int HandleIPCResponse(std::string &     response);
    };


	class SetOCapsuleEmptyLEDStateOnGIOB : public IIOBoardMessage
    {
		private:
		int _OCapsuleId;
		GarfunkelPumpState _eOnOrOff;
		std::string _onCommand;
		std::string _offCommand;

    public:
		SetOCapsuleEmptyLEDStateOnGIOB(std::string & addressInstance);
		void SetOCapsuleEmptyLEDState( int Id, GarfunkelPumpState eOpenOrClosed);
        virtual ~SetOCapsuleEmptyLEDStateOnGIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);
        virtual int HandleIPCResponse(std::string &     response);
    };

	class SetGarfunkelPumpStateOnGIOB : public IIOBoardTimedMessage
	 {
			private:
			GarfunkelPumpState _oNOff;
			std::string _onCommand;
			std::string _offCommand;

	    public:
			SetGarfunkelPumpStateOnGIOB(std::string & addressInstance);
			void SetGarfunkelPumpState( GarfunkelPumpState OnOff);
	        virtual ~SetGarfunkelPumpStateOnGIOB();
	        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);
	        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);
	        virtual int HandleIPCResponse(std::string &     response);
	  };

	class SetAllOutputsOffOnGIOB : public IIOBoardMessage
    {
    public:
		SetAllOutputsOffOnGIOB(std::string & addressInstance);
        virtual ~SetAllOutputsOffOnGIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);
        virtual int HandleIPCResponse(std::string &     response);
    };

/*---------Simon Board--------------------*/
	
	class SetTreatmentPumpStateOnSIOB : public IIOBoardTimedMessage
    {
		private:
		GarfunkelPumpState _oNOff;
		std::string _onCommand;
		std::string _offCommand;

    public:
        SetTreatmentPumpStateOnSIOB(std::string & addressInstance);
		void SetTreatmentPumpState( GarfunkelPumpState OnOff);
        virtual ~SetTreatmentPumpStateOnSIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);       
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);  
        virtual int HandleIPCResponse(std::string &     response);    
    };
	
    //DU:27
    class GetTreatmentPumpStatusfromSIOB  : public IIOBoardTimedMessage
    {
    public:
        GetTreatmentPumpStatusfromSIOB(std::string & addressInstance);
        virtual ~GetTreatmentPumpStatusfromSIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);       // Will send the data
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);  // This will check if the message should be run
        virtual int HandleIPCResponse(std::string &     response);
    };


	class SetMainWaterInletStateOnSIOB : public IIOBoardTimedMessage
    {
		private:
		GarfunkelValveState _eOpenOrClosed;
		std::string _onCommand;
		std::string _offCommand;

    public:
		SetMainWaterInletStateOnSIOB(std::string & addressInstance);
		void SetMainWaterInletState( GarfunkelValveState eOpenOrClosed);
        virtual ~SetMainWaterInletStateOnSIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);
        virtual int HandleIPCResponse(std::string &     response);
    };


	class SetSValveStateOnSIOB : public IIOBoardTimedMessage
    {
		private:
		GarfunkelValveState _eOpenOrClosed;
		std::string _onCommand;
		std::string _offCommand;

    public:
		SetSValveStateOnSIOB(std::string & addressInstance);
		void SetSValveState( GarfunkelValveState eOpenOrClosed);
        virtual ~SetSValveStateOnSIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);
        virtual int HandleIPCResponse(std::string &     response);
    };


	class SetPValveStateOnSIOB : public IIOBoardTimedMessage
    {
		private:
		GarfunkelValveState _eOpenOrClosed;
		std::string _onCommand;
		std::string _offCommand;

    public:
		SetPValveStateOnSIOB(std::string & addressInstance);
		void SetPValveState( GarfunkelValveState eOpenOrClosed);
        virtual ~SetPValveStateOnSIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);
        virtual int HandleIPCResponse(std::string &     response);
    };

    class GetDigitalInputOutputStatefromSIOB  : public IIOBoardTimedMessage
    {
    public:
    	GetDigitalInputOutputStatefromSIOB(std::string & addressInstance);
        virtual ~GetDigitalInputOutputStatefromSIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);       // Will send the data
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);  // This will check if the message should be run
        virtual int HandleIPCResponse(std::string &     response);

    };

	class SetSEmptyLEDStateOnSIOB : public IIOBoardMessage
    {
		private:
		GarfunkelPumpState _oNOff;
		std::string _onCommand;
		std::string _offCommand;

    public:
		SetSEmptyLEDStateOnSIOB(std::string & addressInstance);
		void SetSEmptyLEDState( GarfunkelPumpState OnOff);
        virtual ~SetSEmptyLEDStateOnSIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);
        virtual int HandleIPCResponse(std::string &     response);
    };


	class SetHEmptyLEDStateOnSIOB : public IIOBoardMessage
    {
		private:
		GarfunkelPumpState _oNOff;
		std::string _onCommand;
		std::string _offCommand;

    public:
		SetHEmptyLEDStateOnSIOB(std::string & addressInstance);
		void SetHEmptyLEDState( GarfunkelPumpState OnOff);
        virtual ~SetHEmptyLEDStateOnSIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);
        virtual int HandleIPCResponse(std::string &     response);
    };


	class SetAllOutputsOffOnSIOB : public IIOBoardMessage
    {
    public:
		SetAllOutputsOffOnSIOB(std::string & addressInstance);
        virtual ~SetAllOutputsOffOnSIOB();
        virtual int Execute(boost::shared_ptr< ecolab::ISocketCommunication >   pSocketRS485);
        virtual BOOLEAN IsMessageRunable(BOOLEAN    bAutomated);
        virtual int HandleIPCResponse(std::string &     response);
    };

	class IOBoardBaseThread : public ecolab::Thread
	{
		public:
			IOBoardBaseThread(const std::string &name, const std::string &addressInstance, const std::string &flatFile);
			IOBoardBaseThread(const IOBoardBaseThread& objectToCopy);
			virtual ~IOBoardBaseThread();
			virtual int Run();
			virtual void Cleanup();
			virtual BOOLEAN Initialize();
			void SetAddressInstance(std::string        &dBItem);
			void SetFlatFilePath(std::string        &dBItem);
			BOOLEAN RegisterCallback(std::string command, boost::shared_ptr< Garfunkel::IIOBoardMessage > pMsg);
			/*BOOLEAN GetIOBoardAddressFromDatabase();
			BOOLEAN ReadIOBoardAddressestFromFile();
			BOOLEAN WriteIOBoardAddressesToFile();*/

		protected:
			std::list<boost::shared_ptr< Garfunkel::IIOBoardTimedMessage > >   _ioBoardTimedMessages;
			std::string        dBItem;
			std::string        flatFilePath;
		private:
			boost::shared_ptr< ecolab::ISocketCommunication >                           pSocketRS485;

	};


	class GarfunkelIOBoardThread : public IOBoardBaseThread
		{
		public:
			GarfunkelIOBoardThread(const std::string &name, const std::string &addressInstance, const std::string &flatFile);
			virtual ~GarfunkelIOBoardThread();
			void RegisterCommands();

		};


	class SimonlIOBoardThread : public IOBoardBaseThread
		{
		public:
		SimonlIOBoardThread(const std::string &name, const std::string &addressInstance, const std::string &flatFile);
			virtual ~SimonlIOBoardThread();
			void RegisterCommands();

		};

}
#endif  //_IOBOARDMESSAGING_H
