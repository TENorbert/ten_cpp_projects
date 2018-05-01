#ifndef PRODUCT_CONTEXT_H
#define PRODUCT_CONTEXT_H

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

#include "GarfunkelDB.h"
#include "GarfunkelSystemData.h"
#include "GarfunkelSystemContext.h" 
#include "GarfunkelLocalizationManager.h" 

//%*******************************************************************//
//%
//% ProductContext
//% 
//% This class provides information related to Products
//% which is accessible to QML screens requesting
//% the information. It communicates with the DB (if necessary) and
//% SystemContext class
//%
//%**********************************************************************//


class ProductContext : public QObject
{
     Q_OBJECT

public:
     //%
     //% Custructors are a Joy
     //%
     ProductContext (GarfunkelDB *gdb, GarfunkelSystemContext *gsystemcontext, 
		      QDeclarativeContext *context,
		      GarfunkelLocalizationMgr2 *GarfunkelLM2,  
		      QObject *parent = 0);
     //%
     //% Destructor!!
     //%
     virtual ~ProductContext();

     //% Some Public Methods



signals:





public slots:




private: 
     GarfunkelDB * 		_gDB;
     QDeclarativeContext* 	_context;
     GarfunkelSystemContext* 	_gsystemcontext;
     GarfunkelLocalizationMgr2*  _GarfunkelLM2;
 
     //methods calling connections!
     void _productdata ();
		   

};
#endif //PRODUCT_CONTEXT_H
