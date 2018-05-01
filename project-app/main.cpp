#include <boost/shared_ptr.hpp>
#include <iostream>
#include <fstream>
#include <signal.h>
#include <stdio.h> 
#include <sstream>
#include <fcntl.h>
#include <termios.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <syslog.h>
#include "ecolab.h"
#include "GarfunkelApp.h"
#include "ApplicationContext.h"
#include <sstream>


int main(int argv, char ** argc)
{

	ecolab::Signals::Instance().Add(SIGTERM, boost::shared_ptr<ecolab::Signals::IHandler>(new Garfunkel::TerminateGarfunkel()));
	ecolab::Signals::Instance().Add(SIGINT,	boost::shared_ptr<ecolab::Signals::IHandler>(new Garfunkel::TerminateGarfunkel()));
	ecolab::Signals::Instance().Start(ecolab::Thread::DETACHED);
	Garfunkel::GarfunkelApp app;
	app.Initailize();
	app.Run();
	std::cout << "[Garfunkel:MAIN] Main application exiting" << std::endl;
    return 0;
 
};
