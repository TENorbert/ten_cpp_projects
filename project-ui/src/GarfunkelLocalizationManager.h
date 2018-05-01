#ifndef GARFUNKELLOCALIZATIONMANAGER_H
#define GARFUNKELLOCALIZATIONMANAGER_H
#include <QObject>
#include <QDebug>
#include <QtDeclarative>
#include "DBAccess.h"
#include "QtLocalizationManager.h"
#include "garfunkelresourcestrings.h"
#include "GarfunkelSystemContext.h"
#include "LocalizationHandler.h"

class GarfunkelLocalizationMgr;





//%
//%  Class 1 Handles Localization  simply using Qt's own Localization class, no
//%  need for creating a resource String QML accessible type
//%
class GarfunkelLocalizationMgr : public QObject
{
    Q_OBJECT
private:
    //static bool _initialized;
    GarfunkelDB*  _gdb;                //!< Pointer to the database object.
    GarfunkelSystemContext         *_systemContext;

    //void Initialize();

    void SetDatabaseConnectionParameters(const QString &  dbInstance, const QString & dbUser, const QString &    dbPassword)
    {
    	qDebug() << "GarfunkelLocalizationMgr::SetDatabaseConnectionParameters";
    	return _lm.SetDatabaseConnectionParameters(dbInstance,dbUser, dbPassword);
    }
    void        SetPrimaryLanguageStoredProc(const QString &    primaryStoredProc)
    {
    	return _lm.SetPrimaryLanguageStoredProc(primaryStoredProc);
    }
    void        SetSecondaryLanguageStoredProc(const QString &  secondaryStoredProc)
    {
    	return _lm.SetSecondaryLanguageStoredProc(secondaryStoredProc);
    }

    void        SetProgrammingLanguageStoredProc(const QString &  programmingStoredProc)
    {
    	return _lm.SetPrimaryLanguageStoredProc(programmingStoredProc);
    }

    void        SetSpecialStringStoredProc(const QString &  specialStoredProc)
    {
    	return _lm.SetSpecialStringStoredProc(specialStoredProc);
    }

    void        SetPrimaryLanguageFile(const QString &    primaryLanguageFile)
    {
    	return _lm.SetPrimaryLanguageFile(primaryLanguageFile);
    }
    void        SetSecondaryLanguageFile(const QString &  secondaryLanguageFile)
    {
    	return _lm.SetSecondaryLanguageStoredProc(secondaryLanguageFile);
    }
    void        SetProgrammingLanguageFile(const QString &  programmingLanguageFile)
    {
    	return _lm.SetProgrammingLanguageFile(programmingLanguageFile);
    }

    void        SetSpecialStringFile(const QString &  specialStringFile)
    {
    	return _lm.SetSpecialStringFile(specialStringFile);
    }

public:

    GarfunkelLocalizationMgr(GarfunkelDB *gdb, GarfunkelSystemContext *systemContext, QObject *parent=0);
    ~GarfunkelLocalizationMgr()
    {

    }


public slots:

	void LoadLanguageStrings()
	{

		qDebug() << "GarfunkelLocalizationMgr::Language Changed, reloading language strings";
		_lm.SetPrimaryLanguageStoredProc("GetPrimaryLanguageStrings( )");
		//_lm.SetSecondaryLanguageStoredProc("GetSecondaryLanguageStrings( )");
		_lm.SetProgrammingLanguageStoredProc("GetProgrammingLanguageStrings( )");
		_lm.SetSpecialStringStoredProc("GetSpecialLanguageStrings( )");
		_lm.BuildStringMaps();
		emit localizedStringsChanged();

	}


    QString GetPrimaryLanguageStringByID(int stringID)
    {
    	QString    primaryString;
    	_lm.GetPrimaryLanguageStringByID(stringID, primaryString);
    	return primaryString;

    }

    QString GetPrimaryLanguageStringByName(const QString & stringName)
    {
    	QString    primaryString;
    	_lm.GetPrimaryLanguageStringByName(stringName, primaryString);
    	return primaryString;

    }
    QString GetSecondaryLanguageStringByID(int stringID)
    {
    	QString    secondaryString;
    	_lm.GetSecondaryLanguageStringByID(stringID, secondaryString);
    	return secondaryString;

    }
    QString GetSecondaryLanguageStringByName(const QString & stringName)
    {
    	QString    secondaryString;
    	_lm.GetSecondaryLanguageStringByName(stringName, secondaryString);
    	return secondaryString;
    }
    QString GetTMLanguageStringByID(int stringID)
    {
    	QString    tmString;
    	_lm.GetTMLanguageStringByID(stringID, tmString);
    	return tmString;
    }

    QString GetTMLanguageStringByName(const QString & stringName)
    {
    	QString    tmString;
    	_lm.GetTMLanguageStringByName(stringName, tmString);
    	return tmString;
    }

    QString GetSpecialStringByID(int stringID)
    {
    	QString     specialString;
    	_lm.GetSpecialStringByID(stringID, specialString);
    	return 		specialString;
    }

    QString GetSpecialStringByName(const QString & stringName)
    {
    	QString     specialString;
    	_lm.GetSpecialStringByName(stringName, specialString);
    	return 		specialString;
    }

    BOOLEAN      BuildStringMaps()
    {
    	return _lm.BuildStringMaps();
    }
signals:
	void localizedStringsChanged();
private:
    QtLocalizationManager _lm;

};

//%
//%  Class 2 Handles Localization  by explicitely 
//%  creating a resource String QML accessible type
//%

class GarfunkelLocalizationMgr2 : public QObject
{
    Q_OBJECT

public:
    GarfunkelLocalizationMgr2(GarfunkelDB *gdb, GarfunkelSystemContext *syscontext, QObject *parent = 0);
    virtual ~GarfunkelLocalizationMgr2();

    //%
    //%  Public Slots!!
    //%
public slots:
    void LoadLanguageStrings();

    QString GetPrimaryLanguageStringByID(int stringID);

    QString GetTMLanguageStringByID(int stringID);
    void SetPrimaryLanguageFont();
    QString GetPrimaryLanguageFontName();
    bool GetPrimaryLanguageFontBoldStatus();
    void SetFallbackFontForPrimaryLanguage();
  
    //void SetFallbackFontWhenPrimaryAndSecondaryFontDifferent();
   
     void SetTMLanguageFont();
    QString GetTMLanguageFontName();
    bool GetTMLanguageFontBoldStatus();
    int GetPrimaryLanguageFontPointSize();


signals:
    void localizedStringsChanged();

private:
    GarfunkelDB*              _gdb;                //!< Pointer to the database object.
    GarfunkelSystemContext *   _systemcontext;

    QString primaryFont;
    QString programmingFont;

    std::string             _primaryLocale;

    std::string             _programmingLocale;

    std::string             _primaryLocaleFont;
    std::string             _primaryLocaleFontFallback;
    
    std::string             _programmingLocaleFont;

    int             _primaryLocaleFontPointSize;
    int             _primaryLocaleFallbackFontPointSize;
    int             _programmingLocaleFontPointSize;
    BOOLEAN         _primaryLocaleFontBold;
    BOOLEAN         _primaryLocaleFallbackFontBold;
    //BOOLEAN         _secondaryLocaleFontBold;
    BOOLEAN         _programmingLocaleFontBold;

    ecolab::ICU::LocalizationHandlerFlatDefinition      _primaryLanguage;
    ecolab::ICU::LocalizationHandlerFlatDefinition      _programmingLanguage;

    int    _fallbackFontLoaded;
    bool   GetLocalLanguageDisplay();
};


#endif // GARFUNKELLOCALIZATIONMANAGER_H
