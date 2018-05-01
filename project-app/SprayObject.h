#if !defined(_SPARY_H)
#define _SPRAY_H
#include "GarfunkelData.h"

namespace Garfunkel
{
	class SprayObject
	{
	   public:
 			SprayObject() ;
 			virtual ~SprayObject() { std::cout<<"SprayObject destructor called"<<std::endl;};
 			BOOLEAN GetEnableState() { return _enable; };
 			void SetEnableState(BOOLEAN st) { _enable = st;} ;
 			void Reset() { _timer = 10; _isRunning = False; }
 			virtual BOOLEAN StartSpray() = 0;
 			virtual BOOLEAN KeepRunning() = 0;
 			virtual BOOLEAN StopSpray() = 0;
 			virtual void  SendSprayTimeToUi(double flushTime) = 0;
 			virtual void  SendDelayTimeToUi(double flushTime) = 0;
 			virtual BOOLEAN IsRunningAsReportedByIOBoard()= 0;
 			BOOLEAN IsRunning() { return _isRunning; };
 			void SetRunState(BOOLEAN st) { _isRunning = st;} ;
 			void SetSocket(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485) { _pSocketRS485= pSocketRS485; };
	   protected:
 			BOOLEAN  _enable;
 			int      _timer;
 			BOOLEAN _isRunning;
 			boost::shared_ptr< ecolab::ISocketCommunication > _pSocketRS485;
	};


	class SprayObjectFactory
	{

		public:
			~SprayObjectFactory();

			static SprayObjectFactory&	Instance();
			boost::shared_ptr<SprayObject >   GetSprayObject(GarfunkelSparyObjType	connectType);

		private:
			SprayObjectFactory();
			std::map<GarfunkelSparyObjType, boost::shared_ptr<SprayObject > >    _sprayObjPool;
			ecolab::MutexLock             _sparyObjPoolLock;
			BOOLEAN  CreateSparyObjects();

	};

	class  MainWaterInletSprayObject : public SprayObject
	{
		public:
	 		MainWaterInletSprayObject();
	 		virtual ~MainWaterInletSprayObject();
	 		virtual BOOLEAN StartSpray();
	 		virtual BOOLEAN KeepRunning();
	 		virtual BOOLEAN StopSpray();
	 		virtual void  SendSprayTimeToUi(double flushTime);
	 		virtual void  SendDelayTimeToUi(double flushTime);
	 		virtual BOOLEAN IsRunningAsReportedByIOBoard();
		protected:
	 		BOOLEAN  StartCommand();
		private:
	 		SetMainWaterInletStateOnSIOB  *_pCmd;
	 		boost::shared_ptr< Garfunkel::IIOBoardMessage > _msg;
	 		std::string _cmdString;
	};

	class  SBlockSprayObject : public MainWaterInletSprayObject
	{
		public:
	 		SBlockSprayObject();
	 		virtual ~SBlockSprayObject();
	 		virtual BOOLEAN StartSpray();
	 		virtual BOOLEAN KeepRunning();
	 		virtual BOOLEAN StopSpray();
	 		virtual BOOLEAN IsRunningAsReportedByIOBoard();
		private:
	 		BOOLEAN  StartCommand();
	 		SetSValveStateOnSIOB  *pCmd;
	 		boost::shared_ptr< Garfunkel::IIOBoardMessage > msg;
	 		std::string cmdString;

	};

	class  PBlockSprayObject : public MainWaterInletSprayObject
	{
		public:
	 		PBlockSprayObject();
	 		virtual ~PBlockSprayObject();
	 		virtual BOOLEAN StartSpray();
	 		virtual BOOLEAN StopSpray();
	 		virtual BOOLEAN KeepRunning();
	 		virtual BOOLEAN IsRunningAsReportedByIOBoard();
		private:
	 		BOOLEAN  StartCommand();
	 		SetPValveStateOnSIOB  *pCmd;
	 		boost::shared_ptr< Garfunkel::IIOBoardMessage > msg;
	 		std::string cmdString;

	};


	class  AquanomicsDilutionSprayObject : public MainWaterInletSprayObject
	{
		public:
	 		AquanomicsDilutionSprayObject();
	 		virtual ~AquanomicsDilutionSprayObject();
	 		virtual BOOLEAN StartSpray();
	 		virtual BOOLEAN StopSpray();
	 		virtual BOOLEAN KeepRunning();
	 		virtual BOOLEAN IsRunningAsReportedByIOBoard();
		protected:
	 		BOOLEAN  StartCommand();
		private:
	 		SetDilutionValveStateOnGIOB  *pCmd;
	 		boost::shared_ptr< Garfunkel::IIOBoardMessage > msg;
	 		std::string cmdString;

	};

	class  AquanomicsPumpObject : public AquanomicsDilutionSprayObject
	{
 	 	public:
	 	 	AquanomicsPumpObject();
	 	 	virtual ~AquanomicsPumpObject();
	 	 	virtual BOOLEAN StartSpray();
	 	 	virtual BOOLEAN StopSpray();
	 	 	virtual BOOLEAN KeepRunning();
	 	 	virtual BOOLEAN IsRunningAsReportedByIOBoard();
 	 	protected:
	 	 	BOOLEAN  StartCommand();
 	 	private:
	 	 	SetGarfunkelPumpStateOnGIOB  *pCmd;
	 	 	boost::shared_ptr< Garfunkel::IIOBoardMessage > msg;
	 	 	std::string cmdString;

	};



	class  SumpValveSprayObject : public AquanomicsPumpObject
	{
 	 	public:
	 		SumpValveSprayObject(); //start valave and pump here
	 		virtual ~SumpValveSprayObject();
	 		virtual BOOLEAN StartSpray();
	 		virtual BOOLEAN StopSpray();
	 		virtual BOOLEAN KeepRunning();
	 		virtual BOOLEAN IsRunningAsReportedByIOBoard();
 	 	protected:
	 		BOOLEAN  StartCommand();
 	 	private:
	 		SetSumpValveStateOnGIOB  *pCmd;
	 		boost::shared_ptr< Garfunkel::IIOBoardMessage > msg;
	 		std::string cmdString;
	};

	class  OProductSprayObject : public SumpValveSprayObject
	{
 	 	public:
	 		OProductSprayObject( int n);
	 		virtual ~OProductSprayObject();
	 		void SetOProduct(int n) { _no= n; }
	 		virtual BOOLEAN StartSpray();
	 		virtual BOOLEAN StopSpray();
	 		virtual BOOLEAN KeepRunning();
	 		virtual BOOLEAN IsRunningAsReportedByIOBoard();
 	 	private:
	 		BOOLEAN  StartCommand();
	 		SetOCapsuleValveStateOnGIOB  *pCmd;
	 		boost::shared_ptr< Garfunkel::IIOBoardMessage > msg;
	 		std::string cmdString;
	 		int _no;
	};

 	class  DrainSprayObject : public AquanomicsDilutionSprayObject
 	{
 	 	public:
	 		DrainSprayObject();
	 		virtual ~DrainSprayObject();
	 		virtual BOOLEAN StartSpray();
	 		virtual BOOLEAN StopSpray();
	 		virtual BOOLEAN KeepRunning();
	 		virtual BOOLEAN IsRunningAsReportedByIOBoard();

 	 	private:
	 		BOOLEAN  StartCommand();
	 		SetDrainValveStateOnGIOB  *pCmd;
	 		boost::shared_ptr< Garfunkel::IIOBoardMessage > msg;
	 		std::string cmdString;

 	};

}
#endif  //_spary_H
