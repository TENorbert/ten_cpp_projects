
/* This is where Everything is Implemented */

#include <QProcess>
#include "PasswordManager.h"


//% Construntor
PasswordManager::PasswordManager ( QDeclarativeContext* context,  QObject *parent  ) : 
 QObject(parent), _Context(context) 
{
	//initialise impt class stuff
       qDebug () << "Constructor Created!!"; 
      _serialNumber = _day = _month = _year = 0;
}

PasswordManager::~PasswordManager ( )
{
	//Delete useless pointers
}

//Define class methods!

void PasswordManager::pmanager(ulNum &serial_num, ulNum &day, ulNum &month, ulNum &year)
{
	printf("Srial Number = %lu \t", serial_num);
	printf("Day %lu \t", day);
	printf("Month = %lu \t", month);
	printf("Year = %lu \t", year);
}
