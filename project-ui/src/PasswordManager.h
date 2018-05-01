#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

/***********************************************************************************
*  																				   *
*			copyright (c) ECOLAB 2016 											   *
*			Implemented by Tambe E. Norbert on March 2016 						   *
* 	 																			   *
***********************************************************************************/


#include <QObject>
#include <QString>
#include <QStringList>
#include <QDeclarativeContext>
#include <QAbstractListModel>
#include <QDebug>
#include <QtGlobal> // for types ike qint8,(8bits signed char), qint16 etc, qsrand(seed), qrand() etc

//% System C/C++ classes
#include <stdio.h>
#include <string.h>
#include <math.h>
#include  "PasswordGenerator.h"


#define SERIAL_NUMBER_A  10
#define SERIAL_NUMBER_B  12


typedef unsigned long  ulNum;

typedef char sNumA[SERIAL_NUMBER_A];
typedef char sNumB[SERIAL_NUMBER_B];

// Q_ASSERT(b != 0);

//%
//%  Class: PasswordManager 
//%        
//%  handles everything about validating the passwords
//%  use Qt C++ b/c it can easily be turned into and App for Password Generation 
//%


class PasswordManager : public QObject
{
	Q_OBJECT
	//properties

public:
	//constructor
	 PasswordManager (QDeclarativeContext *context,  QObject *parent = 0);
     virtual ~PasswordManager();


public slots:

        void pmanager(ulNum&, ulNum&, ulNum&, ulNum&);


private:

       QDeclarativeContext* _Context; 
       
	   sNumA _sNumberA;
	   sNumB _sNumberB; 

       ulNum _serialNumber; //or use ulong = Qt typdef for unsigned long
       ulNum _day;
       ulNum _month;
       ulNum _year;


private slots:




};

#endif // PASSWORD_MANAGER_H 
