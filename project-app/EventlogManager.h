#ifndef EVENTLOG_MGR_H
#define EVENTLOG_MGR_H

#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "ecolab.h"
#include "GarfunkelData.h"


namespace Garfunkel
{

	class EventDataLog
	{
		public:
			EventDataLog(const EventDataLog &   objectToCopy);
			~EventDataLog();
			static EventDataLog&    Instance();
			BOOLEAN EventLog(int type, int subflag, int dataOne, int dataTwo, int dataThree, int dataFour, int dataFive, int dataSix);
		private:
			EventDataLog();

	};


};


#endif //EVENTLOG_MGR_H
