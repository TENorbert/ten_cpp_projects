#include <QObject>
#include <QDebug>
#include <sstream>
#include "GarfunkelSystemInfoContext.h"



//% Constructor
//%Leave Context Stuff For now!!
GarfunkelSystemInfoContext::GarfunkelSystemInfoContext(GarfunkelDB *gdb, GarfunkelLocalizationMgr *GarfunkelLM,  GarfunkelLocalizationMgr2 *GarfunkelLM2, QDeclarativeContext *context,  QObject *parent) :
    QObject(parent),
    _gDB(gdb),
    _GarfunkelLM(GarfunkelLM),
    _GarfunkelLM2(GarfunkelLM2),
    _Context(context) 

//GarfunkelSystemInfoContext::GarfunkelSystemInfoContext(GarfunkelDB *gdb, QDeclarativeContext *context,  QObject *parent) :
//    QObject(parent),
//    _gDB(gdb),
 //   _Context(context)
{
    //connect(_gDB, SIGNAL(alarmDataUpdated()), this, SLOT(emitSignal()));

    //%Initialize Defualt Strings: Infuture Initialize to What is alreay in DataBase
    _sSimonFirmwareVersionString    = "";
    _garfunkelFirmwareVersionString = "";
    _condorSoftwareVersionString    = "";
    _gafunkelSoftwareVersionString  = "";

    //%   Grab data from dataBase First Time
    //%
    //emitSignal();
    _connectIPC();

}


//% Destructor
GarfunkelSystemInfoContext::~GarfunkelSystemInfoContext ()
{
   //%Delete Pointers
}



//% Connect to the MCA
void GarfunkelSystemInfoContext::_connectIPC()
{
    GarfunkelSystemData& sdo = GarfunkelSystemData::Instance();

    connect(&sdo,SIGNAL(ioConnectionDown()),    this, SLOT(ioConnectionDownSlot()));
    connect(&sdo,SIGNAL(ioConnectionUp()),    this, SLOT(ioConnectionUpSlot()));
    connect(&sdo,SIGNAL(garfunkelSoftwareVersion(QString)),    this, SLOT(garfunkelSoftwareVersionSlot(QString)),Qt::UniqueConnection );
    connect(&sdo,SIGNAL(sSimonIOBoardFirmwareVersion(QString)),    this, SLOT(sSimonIOBoardFirmwareVersionSlot(QString)),Qt::UniqueConnection );
    connect(&sdo,SIGNAL(garfunkelIOBoardFirmwareVersion(QString)),    this, SLOT(garfunkelIOBoardFirmwareVersionSlot(QString)),Qt::UniqueConnection );
    
}



//% Disconect from MCA
void GarfunkelSystemInfoContext::_disconnectIPC()
{
    GarfunkelSystemData& sdo = GarfunkelSystemData::Instance();

    disconnect(&sdo,SIGNAL(ioConnectionDown()),    this, SLOT(ioConnectionDownSlot()));
    disconnect(&sdo,SIGNAL(ioConnectionUp()),    this, SLOT(ioConnectionUpSlot()));
    disconnect(&sdo,SIGNAL(garfunkelSoftwareVersion(QString)),    this, SLOT(garfunkelSoftwareVersionSlot(QString)) );
    disconnect(&sdo,SIGNAL(sSimonIOBoardFirmwareVersion(QString)),    this, SLOT(sSimonIOBoardFirmwareVersionSlot(QString)));
    disconnect(&sdo,SIGNAL(garfunkelIOBoardFirmwareVersion(QString)),    this, SLOT(garfunkelIOBoardFirmwareVersionSlot(QString)));
    
  
}




//%
//% SETTING FUNCTIONS
//%

//% Smart Simonn  IO Board Firmware Update
void GarfunkelSystemInfoContext::setSSimonIOBoardFirmwareVersionString (QString   ssfwversion)
{
    qDebug() << "Recent Smart Simon IO Board Firmware version " << ssfwversion;
    _sSimonFirmwareVersionString = ssfwversion.toAscii();
    emit sSimonIOBoardFirmwareVersionStringChanged (ssfwversion) ;

}

//% Garfunkel IO Board Firmware Update
void GarfunkelSystemInfoContext::setGarfunkelIOBoardFirmwareVersionString (QString  gfwversion)
{
    qDebug() << "Recent Garfunkel IO Board Firmware version " << gfwversion;
    _garfunkelFirmwareVersionString = gfwversion.toAscii();
    emit garfunkelIOBoardFirmwareVersionStringChanged (gfwversion) ;

}


//% Condor Software Update
void GarfunkelSystemInfoContext::setCondorSoftwareVersionString (QString  condorSW)
{
    qDebug() << "Recent Condor Softwar version " << condorSW;
    _condorSoftwareVersionString = condorSW.toAscii();
    emit condorSoftwareVersionStringChanged (condorSW) ;

}


//% Garfunle Software Update
void GarfunkelSystemInfoContext::setGarfunkelSoftwareVersionString (QString  gswversion)
{
    qDebug() << "Recent Garfunkel Softwar version " << gswversion;
    _gafunkelSoftwareVersionString = gswversion.toAscii();
    emit garfunkelSoftwareVersionStringChanged (gswversion) ;

}




//%
//%    SLOTS
//%


//% Emit MCA Connection Down signal
void GarfunkelSystemInfoContext::ioConnectionDownSlot()
{
    emit( ioConnectionDown() );
}


//% Emit MCA Connection Up Signal
void GarfunkelSystemInfoContext::ioConnectionUpSlot()
{
    emit( ioConnectionUp() );
}


//%
//% SLOT: sSimonIOBoardFirmwareVersionSlot (QString ssfwversion)
//% Recieves Smart Simon IO Board Firmware Version from MCA
//% Which is response to COMMAND: DU:85
//% The MCA response string "ssfwversion" is: IO Board,Rev A.B.C,ZZZZZZZ
//% where Rev A.B.C Is Revision Level
//% and   ZZZZZZZ: Is Smart Simon IO Board Serial Number
//%
void GarfunkelSystemInfoContext::sSimonIOBoardFirmwareVersionSlot (QString ssfwversion)
{
  qDebug() << "Setting Smart Simon IO Board Firmware Version ";
  setSSimonIOBoardFirmwareVersionString(ssfwversion);
}

//%
//% SLOT: garfunkelIOBoardFirmwareVersionSlot (QString gfwversion)
//% Recieves Smart Simon IO Board Frirmware Version from MCA
//% Which is response to COMMAND: DU:86
//% The MCA response String "gfwversion" is: IO Board,Rev A.B.C,ZZZZZZZ
//% where Rev A.B.C Is Revision Level
//% and   ZZZZZZZ: Is Garfunkel IO Board Serial Number
//%
void GarfunkelSystemInfoContext::garfunkelIOBoardFirmwareVersionSlot (QString gfwversion)
{
  qDebug() << "Setting Garfunkel IO Board Firmware Version ";
  setGarfunkelIOBoardFirmwareVersionString (gfwversion);
}

//%
//% SLOT: garfunkelSoftwareVersionSlot (QString gswversion)
//% Recieves Smart Simon IO Board Frirmware Version from MCA
//% Which is response to COMMAND: DU:84
//% The MCA response String "gswversion" is: A.B.C
//% where A.B.C: Is Revision Level
//% 
//%
void GarfunkelSystemInfoContext::garfunkelSoftwareVersionSlot (QString gswversion)
{
   qDebug() << "Setting Garfunkel Software Version ";
   setGarfunkelSoftwareVersionString(gswversion);
}



//%
//%  UI REQUEST SITE FUNCTIONS
//%

  
//%
//% Function: grabSmartSimonIOBoardFirmwareVersion
//% is Used to make request from UI to MCA to
//% fetch the Smart SIMON IO Board Firmware Version by emitting the COMMAND
//% MCA: DU:85 
//%

void GarfunkelSystemInfoContext::grabSmartSimonIOBoardFirmwareVersion()
{
    qDebug() << "Requesting Smart SIMON IO Board Firmware Version ";

    GarfunkelSystemData& sdo = GarfunkelSystemData::Instance();
    sdo.fromUiCommandDU85();
    //% In future if Database is needed we will get from Database also

}


//%
//% Function: grabGarfunkelIOBoardFirmwareVersion
//% is Used to make request from UI to MCA to
//% fetch the Smart SIMON IO Board Firmware Version by emitting the COMMAND
//% MCA: DU:86 
//%

void GarfunkelSystemInfoContext::grabGarfunkelIOBoardFirmwareVersion()
{
    qDebug() << "Requesting Garfunkel IO Board Firmware Version ";

    GarfunkelSystemData& sdo = GarfunkelSystemData::Instance();
    sdo.fromUiCommandDU86();
    //% In future if Database is needed we will get from Database also

}

  
//%
//% Function: grabGarfunkelSoftwareVersion
//% is Used to make request from UI to MCA/Database to
//% fetch the Garfunkel Software version by emitting signal the COMMAND
//% MCA: DU:84 or 
//% Read from Data Base
//% The idle case is that this comes from the MCA
//%
void GarfunkelSystemInfoContext::grabGarfunkelSoftwareVersion ()
{
    qDebug() << "Grabbing Garfunkel Software Version ";
#if 1
    GarfunkelSystemData& sdo = GarfunkelSystemData::Instance();
    sdo.fromUiCommandDU84();
#else

    ecolab::DB::DBAccess    myDBAccess;
    std::string             connectString="";
    connectString = "dbname = 'Condor' user = 'db_controller' password = 'controller'";
    ecolab::DB::DataSet        dataSet;
    std::stringstream strstream;
    strstream<<"SELECT * FROM GetControllerData() WHERE \"Description\"=\'Garfunkel\';";
    std::string sql = strstream.str();

    //std::string                sql = "SELECT * from GetControllerData('Garfunkel')";

    //% Connect to DB if it is not connected.
    if (NULL == myDBAccess.DBisConnected())
    {
        myDBAccess.DBConnect(connectString, 5);
    }

    if(NULL != myDBAccess.DBisConnected())
    {

        if(myDBAccess.DBExecuteStored(sql, dataSet))
        {
            if(dataSet.GetNumberOfRows() == 1)
            {
            ecolab::DB::DataRow     currentRow;
            boost::shared_ptr<ecolab::DB::IColumnData>    colData;

            currentRow = dataSet.GetRow(0);

            if(currentRow.GetNumberOfColumns() > 0)
            {
                std::string garfunkelInfo;
                std::string    value;
                /*
                colData = currentRow.GetColumn("Description");

                if(colData.get() != NULL)
                {
                    colData->AsString(value);
                    garfunkelInfo = value;
                    garfunkelInfo += ",";
                }
                */
                colData = currentRow.GetColumn("SoftwareVersion");

                if(colData.get() != NULL)
                {
                    colData->AsString(value);
                    garfunkelInfo += value;
                    //garfunkelInfo += ",";
                }
                /*
                colData = currentRow.GetColumn("SerialNumber");

                if(colData.get() != NULL)
                {
                    colData->AsString(value);
                    garfunkelInfo += value;
                }
                */
                QString str;
                str = QString::fromUtf8(garfunkelInfo.c_str(),garfunkelInfo.size());
                //% Update with new String From Database
                setGarfunkelSoftwareVersionString(str);
            }
            else
                std::cout<<" Failed: No of columns returned="<<currentRow.GetNumberOfColumns()<<std::endl;

        }
        else
            std::cout<<" Failed: No of rows returned="<<dataSet.GetNumberOfRows()<<std::endl;
    }
    else
        std::cout<<" Failed to execute "<<sql<<std::endl;
    }

#endif

}




//%
//%  Function: grabCondorSoftwareVersion
//% is Used to make request from UI to Database to  
//% fetch for the Condor Software version  
//% 
//% Read from Data Base
//%
void GarfunkelSystemInfoContext::grabCondorSoftwareVersion ()
{
    qDebug() << " Grabbing Condor Software Version ";

    ecolab::DB::DBAccess    myDBAccess;
    std::string             connectString ="";
    //BOOLEAN                 retValue = False;
    std::string             softwareName ="";
    std::string             condorVersion ="";
    std::string             serialNumber ="";
    std::stringstream       strStream;
    std::string             response ="";

    connectString = "dbname = 'Condor' user = 'db_controller' password = 'controller'";

        /* Connect to DB if it is not connected. */
        if (NULL == myDBAccess.DBisConnected())
        {
            myDBAccess.DBConnect(connectString, 5);
        }

        if(NULL != myDBAccess.DBisConnected())
        {

            ecolab::DB::DataSet        dataSet;
            std::string                sql;
            std::stringstream strstream;
            strstream<<"SELECT * FROM GetControllerData() WHERE \"Description\"=\'Condor\';";
            sql = strstream.str();


            std::cout << "Trying to execute " << sql << std::endl;
            if(myDBAccess.DBExecuteStored(sql, dataSet))
            {

                std::cout << "Execution of " << sql << std::endl;

               if(dataSet.GetNumberOfRows() > 0)
               {
                    ecolab::DB::DataRow                         rowData;
                    boost::shared_ptr<ecolab::DB::IColumnData>    colData;
                    std::string                                 colDataAsString;
                    int     numRows = 0;
                    numRows = dataSet.GetNumberOfRows();
                    std::cout << "No Of rows : " << numRows;

                    rowData = dataSet.GetFirstRow();
                    if(rowData.GetNumberOfColumns() > 0)
                    {
                        colData = rowData.GetColumn("Description");
                        if(colData.get() != NULL)
                        {
                            colData->AsString(softwareName);
//                          qDebug() <<"softwareName -> "<< softwareName ;
                        }

                        colData = rowData.GetColumn("SoftwareVersion");
                        if(colData.get() != NULL)
                        {
                            colData->AsString(condorVersion);
                            std::cout << "condorVersion -> "<<condorVersion;
                        }

                        /*
                        colData = rowData.GetColumn("SerialNumber");
                        if(colData.get() != NULL)
                        {
                            colData->AsString(serialNumber);
//                          std::cout <<"serialNumber -> "<<serialNumber;
                        }
                        */

                        //strStream << softwareName << ", " << condorVersion << ", " << serialNumber << ":";
                        strStream << condorVersion ;
                        response = strStream.str();
                        //std::cout << "DI Message: " << response;
                        std::cout << "Condor Version: " << response ;
                        QString condorSW;
                        condorSW = QString::fromUtf8(response.c_str(),response.size());
                        //condorDIMessageSlot(str);
                        setCondorSoftwareVersionString(condorSW);

                    }
                    else
                    {
                        std::cout << "[DB] ERROR GetNumberOfColumns returned " << rowData.GetNumberOfColumns() << " columns. Expected 1 or more" << std::endl;
                    }
                }
                else
                {
                    std::cout << "[DB] ERROR GetNumberOfRows returned " << dataSet.GetNumberOfRows() << " rows. Expected 1." << std::endl;
                }
            }
            else
            {
                std::cout << "[DB] ERROR: Execute the stored procedure GetControllerData." << std::endl;
            }
        }
        else
        {
            std::cout << "[DB] ERROR: Can't connect to DB." << std::endl;
        }

        myDBAccess.DBDisconnect();

}




//%
//%     Execute Generic SQL statement
//%
ecolab::DB::DataSet GarfunkelSystemInfoContext::executeSQLStatement(QString sSQLString)
{
    ecolab::DB::DataSet dataSet;

        if (!_gDB->isConnected())
        {
            #ifdef DEBUG
                        qDebug() << "CONNECTING";
                #endif
                _gDB->connect();
        }

        if(_gDB->isConnected())
        {
                #ifdef DEBUG
                        qDebug() << "CONNECTED";
                #endif

                qDebug() << sSQLString;
                dataSet = _gDB->executeStoredFunction(sSQLString);
        }

    return dataSet;
}






