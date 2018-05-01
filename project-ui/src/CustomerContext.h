#ifndef CUSTOMER_CONTEXT_H
#define CUSTOMER_CONTEXT_H

//% Qt classes
#include <QObject>
#include <QStringList> 
#include <QDeclarativeContext> 
#include <QAbstractListModel>  
#include <QTimer>  
#include <QDateTime>
#include <sstream>


//Private classes!!
#include "DBAccess.h"
#include "ecolab.h"

//% Private classes
#include "GarfunkelDB.h"
#include "GarfunkelSystemData.h"
#include "GarfunkelSystemContext.h" 
#include "GarfunkelLocalizationManager.h" 

//%*******************************************************************//
//%
//% CustomerContext
//% 
//% This class provides information related to customer
//% which is accessible to QML screens requesting
//% the information. It communicates with the DB or MCA(if necessary) and
//% SystemContext class
//%
//%**********************************************************************//


class CustomerContext : public QObject
{
     Q_OBJECT

public:
     //%
     //% Custructors are a Joy
     //%
     CustomerContext (GarfunkelDB *gdb, GarfunkelSystemContext *gsystemcontext, 
		      QDeclarativeContext *context,
		      GarfunkelLocalizationMgr2 *GarfunkelLM2,  
		      QObject *parent = 0);

     //%
     //% Destructor!!
     //%
     virtual ~CustomerContext ();

     //% Some Public Methods

signals:





public slots:




private: 
     GarfunkelDB * 		_gDB;
     QDeclarativeContext* 	_context;
     GarfunkelSystemContext* 	_gsystemcontext;
     GarfunkelLocalizationMgr2*  _GarfunkelLM2;
     //methods calling connections!
     void _customerdata ();
		   

};
#endif //CUSTOMER_CONTEXT_H
