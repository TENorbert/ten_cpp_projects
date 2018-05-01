#ifndef _IOBOARDSYNCMGR_H
#define _IOBOARDSYNCMGR_H

#include "GarfunkelData.h"


namespace Garfunkel
{
	class IOBoardSyncThread : public ecolab::Thread
	{
	private:
	 boost::shared_ptr< ecolab::ISocketCommunication >                           pSocketRS485;
	
    public:
	 IOBoardSyncThread(const std::string &name);
	 IOBoardSyncThread(const IOBoardSyncThread &     objectToCopy);
	 ~IOBoardSyncThread();
	 int Run();
	 void Cleanup();
	};



}

#endif  //IOBOARDSYNCMGR
