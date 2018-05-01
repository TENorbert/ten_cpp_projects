#ifndef _DIAGNOSTICSMGR_H
#define _DIAGNOSTICSMGR_H

#include "GarfunkelData.h"

namespace Garfunkel
{


	class DiagnosticSystemData
	{
		public:
			DiagnosticSystemData(const DiagnosticSystemData & objectToCopy);
			~DiagnosticSystemData();

			// Create as a singleton
			static DiagnosticSystemData&  Instance();

			ecolab::Shareable<BOOLEAN>          WaterFlushInProgress;
			ecolab::Shareable<BOOLEAN>          DelayInProgress;
			ecolab::Shareable<BOOLEAN>          OnRequest;
			ecolab::Shareable<GarfunkelSparyObjType>              SprayObjectRequested;
			ecolab::Shareable<BOOLEAN>          DiagError;
			ecolab::Shareable<GarfunkelFailedOperations>          FailedReason;
			timespec                            LastUIUpdateTime;
			void Reset();

			void SendOperationCompleteMessage();
			void SendErrorMessage();
			void SendMessageToUI(std::string & message);
		private:
			DiagnosticSystemData();
	};




	class DiagnosticsManager : public ecolab::Thread
	{
	private:
		boost::shared_ptr< ecolab::ISocketCommunication >                           pSocketRS485;
    public:
		DiagnosticsManager(const std::string &name);
		DiagnosticsManager(const DiagnosticsManager &     objectToCopy);
		~DiagnosticsManager();

		int Run();
		void Cleanup();
	};

}

#endif  //_DIAGNOSTICSMGR_H
