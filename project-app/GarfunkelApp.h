#ifndef GARFUNKEL_APP_H
#define GARFUNKEL_APP_H

#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "ecolab.h"
#include "GarfunkelData.h"
#include "DatabaseManager.h"

namespace Garfunkel
{

	class GarfunkelApp
	{
		public:
			GarfunkelApp();
			GarfunkelApp(const GarfunkelData & objectToCopy);
			~GarfunkelApp();
			void Initailize();
			void Run();
			void Cleanup();
		private:
			Garfunkel::GarfunkelIPCSlaveCommunication    _ipcThread;
			Garfunkel::GarfunkelIOBoardThread            _gIOBoardThread;
			Garfunkel::SimonlIOBoardThread               _sIOBoardThread;
			Garfunkel::IOBoardSyncThread                 _syncThread;
			Garfunkel::DiagnosticsManager                _diagThread;
			Garfunkel::AlarmHandler                      _alarmThread;
			Garfunkel::DatabaseManager                   _dbThread;

	};



};


#endif //GARFUNKEL_APP_H
