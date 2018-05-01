#include <QVariant>
#include <QDebug> 
#include <QProcess>
#include "CustomerContext.h"




// Constructor Definition!!
CustomerContext::CustomerContext (GarfunkelDB *gdb, GarfunkelSystemContext *gsystemcontext, 
		      QDeclarativeContext *context,
		      GarfunkelLocalizationMgr2 *GarfunkelLM2,  
		      QObject *parent) :  
  QObject(parent),
  _gDB(gdb), 
  _context(context), 
  _gsystemcontext(gsystemcontext),
  _GarfunkelLM2 (GarfunkelLM2)

{  //Getting information directly from Database
  	//connect(_gDB, SIGNAL(systemDataUpdated()), this, SLOT( grabCustomerDataContext() ));
    
    // Get Data for this class!! if from SystemData class or MCA !!
    //_customerdata ();
    qDebug () << " CustomerContext Class Instantiated!!";
}

//Destructor Definition!!
CustomerContext::~CustomerContext ()
{
	//Dummy Destructor!!!
}


//% Define Methods!!
//% Connect with SystemData(MCA) Method!!
void CustomerContext::_customerdata()
{
	qDebug () << "Getting Customer data from MCA!!";
   //Create instance of System Data!
   //GarfunkelSystemData *sdo = GarfunkelSystemData::getInstancePtr();
   //connect(sdo, SIGNAL(toUiSU78Reply(int)), this, SLOT(CustomerDatFromMCA(int)),Qt::UniqueConnection );
}


