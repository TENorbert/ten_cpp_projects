#include <QVariant>  
#include <QDebug>
#include <QProcess>
//Header File
#include "ProductContext.h"



ProductContext::ProductContext (GarfunkelDB *gdb, GarfunkelSystemContext *gsystemcontext, 
		      QDeclarativeContext *context,
		      GarfunkelLocalizationMgr2 *GarfunkelLM2,  
		      QObject *parent) :  
 QObject(parent),
  _gDB(gdb), 
  _context(context), 
  _gsystemcontext(gsystemcontext),
  _GarfunkelLM2 (GarfunkelLM2)

{  //Getting information directly from Database
  	//connect(_gDB, SIGNAL(systemDataUpdated()), this, SLOT( grabproductDataContext() ));
    
    // Get Data for this class!! if from SystemData class or MCA !!
    _productdata();
    qDebug () << " ProductContext Class Instantiated!!";
}

ProductContext::~ProductContext ()
{
	//Dummy Destructor!!!
}


//% Define Methods!!
void ProductContext::_productdata ()
 {
	qDebug() << "Getting product data from MCA!!";
   //Create instance of System Data!
   //GarfunkelSystemData *sdo = GarfunkelSystemData::getInstancePtr();
   //connect(sdo, SIGNAL(toUiSU78Reply(int)), this, SLOT(productDatFromMCA(int)),Qt::UniqueConnection );
}