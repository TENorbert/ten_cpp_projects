#ifndef OCAPSULE_CONTEXT_H
#define OCAPSULE_CONTEXT_H

//% Get Qt Modules
#include <QObject>
#include <QStringList>
#include <QDeclarativeContext>
#include <QDebug>

//% Include Private Classes
#include "GarfunkelDB.h"
#include "OcapsuleDataModel.h" //% for each OcapsuleData object
#include "garfunkelresourcestrings.h"
#include "GarfunkelLocalizationManager.h"


//%
//% This OcapsuleContext Class defines an interface for comunicating hence exporting
//% variables/methods to QML used for the Ocapsule Menu Properties
//%
//%

class OcapsuleContext : public QObject
{

 	Q_OBJECT

    //% Properties of Ocapsule Read by QML ( Are all these  properties readable? Which is from DB/MCA?)
	Q_PROPERTY ( int ocapsuleId 	READ  getOcapsuleId 	WRITE  setOcapsuleId 	NOTIFY  ocapsuleIdChanged )
	Q_PROPERTY ( bool isOcapsulePresent 	READ  getIsOcapsulePresent 		WRITE  setIsOcapsulePresent 	 NOTIFY  isOcapsulePresentChanged )
	Q_PROPERTY ( QVariant  ocapsuleType 	READ  getOcapsuleType 	 WRITE  setOcapsuleType 	NOTIFY  ocapsuleTypeChanged )
 	Q_PROPERTY (QString detergentName 	 READ  getDetergentName 	WRITE  setDetergentName 	NOTIFY	detergentNameChanged )
   
    Q_PROPERTY ( bool hasDetergent  	READ  getHasDetergent 	  WRITE  setHasDetergent 	 NOTIFY  hasDetergentChanged )
    Q_PROPERTY ( QVariant  ocapsuleValveSwitChState 		READ  getOcapsuleValveSwitchState 	 WRITE  setOcapsuleValveSwitchState 	NOTIFY  ocapsuleValveSwitChStateChanged )
    Q_PROPERTY ( QVariant  ocapsuleLidState 	READ  getOcapsuleLidState 	  WRITE  setOcapsuleLidState 	NOTIFY  ocapsuleLidStateChanged )
    Q_PROPERTY ( QVariant  ocapsuleLEDStatus 	READ  getOcapsuleLEDStatus 	 	WRITE  setOcapsuleLEDStatus 	NOTIFY ocapsuleLEDStatusChanged )
    Q_PROPERTY ( double  conductivity 	 READ  getConductivity 	   WRITE  setConductivity 	 	NOTIFY  conductivityChanged )
    Q_PROPERTY ( double temperature 	READ  getTemperature 	WRITE  setTemperature		NOTIFY  temperatureChanged )
    Q_PROPERTY ( double pressure 	READ  getPressure 	 WRITE  setPressure 	NOTIFY  pressureChanged )  //% How about Prefix/Suffix strings to Temp, Pressure, Conductivity e.g F or Celsius, mSiemens(uSiemens)
    Q_PROPERTY ( double detergentLevel 	  READ  getDetergentLevel 	WRITE  setDetergentLevel 	NOTIFY  detergentLevelChanged )
    Q_PROPERTY ( int valveOpenTime 	   READ  getValveOpenTime 	 WRITE  setValveOpenTime 	NOTIFY  valveOpenTimeChanged )

public:
	//% Constructor: Instance of DB, OcapsuleData, Context & QObject
	OcapsuleContext ( GarfunkelDB *gdb, OcapsuleDataiModel *odatamodel, QDeclarativeContext *context, QObject *parent );

	//
	//% HOW GET STUFF 
	//% ( No inline def here as we need Instance of OcapsuleDataModel )
	// 
	int getOcapsuleId ();
	bool getIsOcapsulePresent ();
	QVariant getOcapsuleType ();
	bool getHasDetergent ();
	QString getDetergentName ();
	double getDetergentLevel ();

	QVariant getOcapsuleValveSwitchState ();
	QVariant getOcapsuleLidState ();
	QVariant getOcapsuleLEDStatus ();
	double getConductivity ();
	double getTemperature ();
	double getPressure ();

	int getValveOpenTime ();

	//
	//% HOW TO SET STUFF 
	//% ( then emit signal)
	//
	void setOcapsuleId ();
	void setIsOcapsulePresent ();
	void setOcapsuleType ();
	void setHasDetergent ();
	void setDetergentName ();
	void setDetergentLevel ();

	void setOcapsuleValveSwitchState ();
	void setOcapsuleLidState ();
	void setOcapsuleLEDStatus ();
	void setConductivity ();
	void setTemperature ();
	void setPressure ();
	
	void setValveOpenTime ();

Signals:
    //% Signals emitted when new value is set( must be void)
    void ocapsuleDataChanged (); //% Signal to QML that Machine Data has been updated 

    void ocapsuleIdChanged ();
    void isOcapsulePresentChanged ();
    void ocapsuleTypeChanged ();
    void hasDetergentChanged ();
    void detergentNameChanged ();
    void detergentLevelChanged ();
    void ocapsuleValveSwitChStateChanged ();
    void ocapsuleLidStateChanged ();
    void ocapsuleLEDStatusChanged ();
    void conductivityChanged ();
    void temperatureChanged ();
    void pressureChanged ();
    void valveOpenTimeChanged ();

public slots:
	void    fetchOcapsuleData ();           //% Fetches OcapsuleData from DB? and emit signal to QML
    void    fetchLocaleNames ();
    void    dbSyncEvent ();

private:
	GarfunkelDB *_gdb;                 //% Pointer to a Database instance
	SystemContext *_systemcontext;    //% If we need to get some information from MCA through SystemData
	QDeclarativeContext *_context;     //% Pointer to a context
	OcapsuleDataModel  *_odataList;    //% Pointer to an OcapsuleDataModel QList instance

	GarfunkelLocalizationMgr *_GarfunkelMgr; //% Language, Font, translation etc purposes from DB or
	GarfunkelLocalizationMgr *_GarfunkelMgr2; //% From XML based translation 
    //
    //%  Simple Single Scalar Variables
    //
    int _primaryLanguage;
    int _secondaryLanguage;
    int _tmLanguage;
    int _noOfOCapsules;  //% must be 2 at all times!!!
    int _unitOfMeasure;

};

#endif // OCAPSULE_CONTEXT_H