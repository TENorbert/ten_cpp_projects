#if !defined(_DISPENSEALGORITHM_H)
#define _DISPENSEALGORITHM_H
#include "ecolab.h"
#include <boost/shared_ptr.hpp>
#include "threads.h"
#include "GarfunkelData.h"
#include "BoardCommands.h"


namespace Garfunkel
{
	
	class IDispenseAlgorithm
	{
    public:
		IDispenseAlgorithm();
		virtual ~IDispenseAlgorithm();
		virtual void Dispense(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485) = 0;
	};


	class DummyDispenseAlgorithm : public IDispenseAlgorithm
	{
     public:
		DummyDispenseAlgorithm(): IDispenseAlgorithm() { };
		void Dispense(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485);

	};

	class StandardDispenseAlgorithm : public IDispenseAlgorithm
	{
	private:
		int  NoOfPumpsDispensed;
     public:
		StandardDispenseAlgorithm() : IDispenseAlgorithm() { NoOfPumpsDispensed=0;};
		void Dispense(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485);

	};

	class AdvanceDispenseAlgorithm : public IDispenseAlgorithm
	{
     public:
		AdvanceDispenseAlgorithm():IDispenseAlgorithm() { };
		void Dispense(boost::shared_ptr< ecolab::ISocketCommunication > pSocketRS485);

	};

	class DispenseAlgorithmFactory
	{
		private:

		DispenseAlgorithmFactory();

		public:

		virtual ~DispenseAlgorithmFactory();
		static DispenseAlgorithmFactory& Instance();
		boost::shared_ptr<Garfunkel::IDispenseAlgorithm>   GetDispenseAlgorithm();
	};


 	class DispensingSystemData
	{
		public:
			DispensingSystemData(const DispensingSystemData & objectToCopy);
			~DispensingSystemData();

			// Create as a singleton
			static DispensingSystemData&  Instance();
			ecolab::Shareable<BOOLEAN>          IsDispenseActive;
			ecolab::Shareable<BOOLEAN>          DispenseError;
			ecolab::Shareable<float>            AvgBaselineConductivity;

			timespec                            LastUIUpdateTime;
	        GarfunkelESPResponse               RespCode;
	        int                                 ErrNo;


			void Reset();
			BOOLEAN NeedToStopDispensing();

			//simon

			void SendDispensingUpdateMessageToUI(int noOfSignalsDispensed, int totalNoOfProgSignals);

		private:
			DispensingSystemData();
	};


}

#endif  //_DISPENSEALGORITHM_H
