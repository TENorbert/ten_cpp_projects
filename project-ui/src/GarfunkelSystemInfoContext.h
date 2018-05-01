#ifndef GARFUNKEL_SYSTEM_INFO_CONTEXT_H
#define GARFUNKEL_SYSTEM_INFO_CONTEXT_H

#include <QObject>
#include <QStringList>
#include <QDeclarativeContext>
#include <QAbstractListModel>
#include <QDebug>
#include <QDateTime>
#include <QProcess>
//% Private include classes!!
#include "GarfunkelDB.h"
#include "GarfunkelSystemData.h"
#include "GarfunkelLocalizationManager.h" // For translation!!



//%    GarfunkelSystemInfoContext 
//%
//%    The GarfunkelSystemInfoContext class is an interface for exporting variables and
//%    methods to QML that are typically used for  interacting with the 
//%    Information perculier to the Garfunkel System as a  whole 
//%    GarfunkelDB/MCA class communicates with this class to make
//%    Requested System related Information available to the  UI 
//%    
//%
class GarfunkelSystemInfoContext : public QObject
{
	Q_OBJECT

    //%
    //%
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% IO BOARDS Firmware  Get From MCA  DU: 85 for Smart SImon, DU:86 for Garfunkel IO Board
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //
    //% Smart Simon IO Board
    //%
    //%Send IO Board Communication Message String  like "Set IO Board On/Off"
    //%If ON is sent and true is returned for message received then Display green on screen for success else display RED on screen for failure
    //
    ////Q_PROPERTY(QString  sendSSimonIOBoardStatusString  READ getSendSSimonIOBoardStatusString  WRITE setSendSSimonIOBoardStatusString   NOTIFY sendSSimonIOBoardStatusStringChanged)
    //
    //%Maybe IO board is always ON then we just want to get a received message (bool) that the board is ON. either way the logic is fine!
    //
    //%If  true = ON = Display green on screen for success else display RED on screen for failure
    //%string comparison? eg if ( str == "ON")? maybe but prone to error?  ( Returned bool Accessible to QML as its used to change color of QML screen or button)
    ////Q_PROPERTY(bool  sSimonIOBoardStatus  READ getSSimonIOBoardStatus   WRITE setSSimonIOBoardStatus 	NOTIFY sSimonIOBoardStatusChanged)
    //
    //%Display String holding Smart Simon IO board  Firmware version ( QML Accessible)
    //
    Q_PROPERTY(QString  sSimonIOBoardFirmwareVersionString  READ getSSimonIOBoardFirmwareVersionString  WRITE setSSimonIOBoardFirmwareVersionString NOTIFY sSimonIOBoardFirmwareVersionStringChanged)
    //
    //%Prefix to Smart Simon IO Board Firmware Version String
    //
    ////Q_PROPERTY(QString  sSimonIOBoardFirmwareVersionPrefixString  READ getSSimonIOBoardFirmwareVersionPrefixString 	WRITE setSSimonIOBoardFirmwareVersionPrefixString	 NOTIFY sSimonIOBoardFirmwareVersionPrefixStringChanged)
    //
    //%suffix to Smart Simon IO Board Firmware Version String
    //
    ////Q_PROPERTY(QString sSimonIOBoardFirmwareVersionSuffixString   READ getSSimonIOBoardFirmwareVersionSuffixString 	WRITE setSSimonIOBoardFirmwareVersionSuffixString 	NOTIFY  sSimonIOBoardFirmwareVersionSuffixStringChanged)
    //
    //% Garfunkel IO Board
    //
    //%Send IO Board Communication Message String  like "Set IO Board On/Off"
    //%If ON is sent and true is returned for message received then Display green on screen for success else display RED on screen for failure
    //
    ////Q_PROPERTY(QString  sendGarfunkelIOBoardStatusString  READ getSendGarfunkelIOBoardStatusString  WRITE setSendGarfunkelIOBoardStatusString   NOTIFY sendGarfunkelIOBoardStatusStringChanged)
    //
    //%Maybe IO board is always ON then we just want to get a received message (bool) that the board is ON. either way the logic is fine!
    //
    //%If  true = ON = Display green on screen for success else display RED on screen for failure
    //%string comparison? eg if ( str == "ON")? maybe but prone to error?  ( Returned bool Accessible to QML as its used to change color of QML screen or button)
    ////Q_PROPERTY(bool  garfunkelIOBoardStatus  READ getGarfunkelIOBoardStatus   WRITE setGarfunkelIOBoardStatus 	NOTIFY garfunkelIOBoardStatusChanged)
    //
    //%Display String holding Garfunkel IO board  Firmware version ( QML Accessible)
    //
    Q_PROPERTY(QString  garfunkelIOBoardFirmwareVersionString  READ getGarfunkelIOBoardFirmwareVersionString   WRITE setGarfunkelIOBoardFirmwareVersionString 	NOTIFY garfunkelIOBoardFirmwareVersionStringChanged)
    //
    //%Prefix to Garfunkel IO Board Firmware Version String
    //
    ////Q_PROPERTY(QString  garfunkelIOBoardFirmwareVersionPrefixString  READ getGarfunkelIOBoardFirmwareVersionPrefixString  WRITE setGarfunkelIOBoardFirmwareVersionPrefixString 		NOTIFY  garfunkelIOBoardFirmwareVersionPrefixStringChanged)
    //
    //%suffix to Garfunkel IO Board Firmware Version String
    //
    /////Q_PROPERTY(QString garfunkelIOBoardFirmwareVersionSuffixString   READ getGarfunkelIOBoardFirmwareVersionSuffixString   WRITE setGarfunkelIOBoardFirmwareVersionSuffixString 	NOTIFY  garfunkelIOBoardFirmwareVersionSuffixStringChanged)
    //
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% CONDOR  SOFTWARE VERSION  Get from DataBase From DataBase
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //
    //%Display String holding CONDOR  Software version ( QML Accessible)
    //
    Q_PROPERTY(QString  condorSoftwareVersionString   READ getCondorSoftwareVersionString   WRITE setCondorSoftwareVersionString    NOTIFY  condorSoftwareVersionStringChanged)
    //
    //%Prefix to CONDOR SW Version String
    //
    ////Q_PROPERTY(QString  condorSoftwareVersionPrefixString  READ getCondorSoftwarePrefixString   WRITE setCondorSoftwarePrefixString    NOTIFY condorSoftwarePrefixStringChanged)
    //
    //%suffix to CONDOR SW Version String
    //
    /////Q_PROPERTY(QString  condorSoftwareVersionSuffixString  READ getCondorSoftwareVersionSuffixString   WRITE  setCondorSoftwareVersionSuffixString NOTIFY condorSoftwareVersionSuffixStringChanged)
    //
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% GARFUNKEL SOWFWARE VERSION From Database or MCA with DU:84
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //
    //%Display String holding Garfunkel Software Version ( QML Accessible)
    //
    Q_PROPERTY(QString  garfunkelSoftwareVersionString  READ getGarfunkelSoftwareVersionString   WRITE setGarfunkelSoftwareVersionString   NOTIFY garfunkelSoftwareVersionStringChanged)
    //
    //%Prefix to Garfunkel Version String
    //
    ////Q_PROPERTY(QString  garfunkelSoftwareVersionPrefixString  READ getGarfunkelSoftwareVersionPrefixString  WRITE setGarfunkelSoftwareVersionPrefixString   NOTIFY garfunkelSoftwareVersionPrefixStringChanged)
    //
    //%suffix to Garfunkel Version String
    //
    ////Q_PROPERTY(QString  garfunkelSoftwareVersionSuffixString  READ getGarfunkelSoftwareVersionSuffixString 	WRITE setGarfunkelSoftwareVersionSuffixString   NOTIFY garfunkelSoftwareVersionSuffixStringChanged)
   //
      

    
    //%
    //%  Execute SQL Command to Read/Write to Database
    //%
    ecolab::DB::DataSet executeSQLStatement(QString sSQLString);



    public:
    	//%  Constructor
    	GarfunkelSystemInfoContext(GarfunkelDB *gdb, GarfunkelLocalizationMgr *GarfunkelLM, GarfunkelLocalizationMgr2 *GarfunkelLM2, QDeclarativeContext *context, QObject *parent = 0);
    	//GarfunkelSystemInfoContext (GarfunkelDB *gdb, QDeclarativeContext *context,  QObject *parent = 0);
    	//% Destructor
    	virtual ~GarfunkelSystemInfoContext ();

    	//%
    	//%   GETTERS
    	//%
    	QString getSSimonIOBoardFirmwareVersionString ()  			{ return  	_sSimonFirmwareVersionString; 		}
    	QString getGarfunkelIOBoardFirmwareVersionString () 		{ return  	_garfunkelFirmwareVersionString; 	}
    	QString getCondorSoftwareVersionString () 					{ return  	_condorSoftwareVersionString;		}
    	QString getGarfunkelSoftwareVersionString () 				{ return 	_gafunkelSoftwareVersionString;		}


   		


    	//%		
    	//%   SETTERS
    	//% 
    	void setSSimonIOBoardFirmwareVersionString (QString 	ssfwversion);
    	void setGarfunkelIOBoardFirmwareVersionString (QString 	gfwversion);
    	void setCondorSoftwareVersionString (QString 	condorSW);
    	void setGarfunkelSoftwareVersionString (QString 	gswversion);





    	//% 
    	//%   SIGNALS
    	//%    
    signals: 
    	void sSimonIOBoardFirmwareVersionStringChanged ( QString ssfwversion);
    	void garfunkelIOBoardFirmwareVersionStringChanged (QString gfwversion);
    	void condorSoftwareVersionStringChanged (QString condorSW);
    	void garfunkelSoftwareVersionStringChanged (QString gswversion);
	    void ioConnectionDown();
    	void ioConnectionUp();




    	//%
    	//%   SLOTS
    	//%   
    public slots:

        //% Requests info from Database/MCA
    	void grabSmartSimonIOBoardFirmwareVersion ();
    	void grabGarfunkelIOBoardFirmwareVersion ();  
		void grabCondorSoftwareVersion ();
		void grabGarfunkelSoftwareVersion ();

		//Recieves info from MCA through commands 
		void sSimonIOBoardFirmwareVersionSlot (QString ssfversion);
		void garfunkelIOBoardFirmwareVersionSlot (QString gfwversion);
		void garfunkelSoftwareVersionSlot (QString gswversion); 

		//% Ensuring We have connection
		void ioConnectionDownSlot();
    		void ioConnectionUpSlot();
    	


   

    private:

   	    GarfunkelDB*            	_gDB;
   	    QDeclarativeContext*     	_Context;                            

        //% For language, font etc
   	    GarfunkelLocalizationMgr*  _GarfunkelLM;
        GarfunkelLocalizationMgr2*  _GarfunkelLM2;

        QString  _sSimonFirmwareVersionString;
        QString  _garfunkelFirmwareVersionString;
   	    QString  _condorSoftwareVersionString;
   	    QString  _gafunkelSoftwareVersionString;
      
        //% Connect & disconnect from IPC
   	    void _connectIPC();
	    void _disconnectIPC();

};

#endif // GARFUNKEL_SYSTEM_INFO_CONTEXT_H  



