//% Qt include Stuff
#include <QDebug>
#include <QtGui>
#include <QtDeclarative>
//% Declaration file include
#include "OcapsuleContext.h"
#include "GarfunkelSystemContext.h"
#include "GarfunkelData.h" //% for data if needed
#include "garfunkelresourcestrings.h" //% for Language Stuff


//%  Constructor
OcapsuleContext::OcapsuleContext ( GarfunkelDB *gdb, OcapsuleDataModel *odataList, GarfunkelLocalizationMgr *GarfunkelMgr, GarfunkelLocalizationMgr2 *GarfunkelMgr2 QtDeclarativeContext *context, 	SystemContext *systemcontext QObject *parent) :
   _gdb ( gdb ), 
   _odataList ( odataList ),
   _context ( context ),
   _systemcontext ( systemcontext ),
   _GarfunkelMgr ( GarfunkelMgr ), 
   _GarfunkelMgr2 ( GarfunkelMgr2 ),
   QObject ( parent )
{
 	//
 	//% Initialise the stuff you want
 	//% make slot Signal Connections
 	//	
 	_primaryLanguage = -1;
 	_secondaryLanguage = -1;
 	_tmLanguage = -1;
    _noOfOCapsules = -1;  //% must be 2 at all times!!!
    _unitOfMeasure = -1;
    
    //% Make connecting with Database
    connect(_gdb, SIGNAL(ocapsuleDataUpdated()), this, SLOT(fetchOcapsulData()));
    //% Connect with Data base to get recent OcapsuleData Language format
    connect(_gdb, SIGNAL(localizedStringsDataUpdated()), this, SLOT(fetchOcapsuleData()));
    connect(_gdb, SIGNAL(localizedStringsDataUpdated()), this, SLOT(fetchOpModeNames()));

    //% Sync with Data base throuh only One Connection
    connect(_gdb, SIGNAL(dbSyncEvent()), this, SLOT(dbSyncEvent()),Qt::UniqueConnection );

    //% connect With SystemContext if needed
    connect(_systemcontext, SIGNAL(noOfOcapsulesChangedinDB()), this, SLOT(fetchOcapsuleData()));
    connect(_systemcontext, SIGNAL(noOfOcapsulesChanged()), this, SLOT(fetchOcapsuleData()));

    _context->setContextProperty("odataList", _odataList);

    //% Connect with  GarfunkelData if need be
    GarfunkelData& gdata = GarfunkelData::Instance();
    connect(&gdata, SIGNAL(oCapsuleProductDataChanged(int, int)), this, SLOT(updateProductDataForOcapsule(int, int)),Qt::UniqueConnection );

    //
    //% Fetch Ocapsule Data from MCA/Database for the first time
    //
    fetchOcapsuleData ();
    fetchLocaleNames();
} 


//
//% Definition of GETTERS
//




//
//% Definition of SETTERS
//






void OcapsuleContext::dbSyncEvent()
{
	emit dbSyncStarted();
}

void OcapsuleContext::fetchOcapsuleData ()
{
   if( !_gdb->isconnected() )
   	 {

   	 

   }else  //% if not Connected to DataBase use Flat file instead
     {
     	qDebug() << "Ocapsuleontext : Reading Ocapsule data from flat files";


   }

}

void SystemContext::fetchLocaleNames()
{


    if (!_gdb->isConnected())
      {
        qDebug() << "fetchLocaleNames NOT CONNECTED";
        _gdb->connect();
    }
    if(_gdb->isConnected())
    {
        qDebug() << "fetchLocaleNames CONNECTED";
        ecolab::DB::DataSet dataSet = _gdb->executeStoredFunction(QString("GetLocaleNames()"));


    }else
     {
            qDebug() << "fetchLocaleNames NO DATA FOUND";
    }


//%
//% More OcapsuleData function definitions    
}    




