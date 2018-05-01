#include "GarfunkelLocalizationManager.h"

#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QString>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/algorithm/string.hpp>
#include "DBAccess.h"
#include "ecolab.h"
#include "GarfunkelSystemContext.h"


/***********************************************************************************
* Class: Localization manager :     Use Qt's own Localization Manager Type 
*                           
*
************************************************************************************/

//bool GarfunkelLocalizationMgr::_initialized = false;

GarfunkelLocalizationMgr::GarfunkelLocalizationMgr( GarfunkelDB *gdb, GarfunkelSystemContext *systemContext, QObject *parent) :QObject(parent), _gdb(gdb),  _systemContext(systemContext)
{
	connect(_gdb, SIGNAL(localizedStringsUpdated()), this, SLOT(LoadLanguageStrings()));

    connect(_systemContext, SIGNAL(primaryLanguageChangedinDB()), this, SLOT(LoadLanguageStrings()));
    connect(_systemContext, SIGNAL(tmLanguageChangedinDB()), this, SLOT(LoadLanguageStrings()));

    connect(_systemContext, SIGNAL(primaryLanguageChanged()), this, SLOT(LoadLanguageStrings()));
    connect(_systemContext, SIGNAL(tmLanguageChanged()), this, SLOT(LoadLanguageStrings()));

    _lm.SetDatabaseConnectionParameters("Garfunkel", "db_user_admin", "controller");
	/*_lm.SetPrimaryLanguageStoredProc("GetPrimaryLanguageStrings( )");
	_lm.SetProgrammingLanguageStoredProc("GetProgrammingLanguageStrings( )");
	_lm.SetSpecialStringStoredProc("GetSpecialLanguageStrings( )");
	_lm.BuildStringMaps();
    */
	qDebug() << "Done with GarfunkelLocalizationMgr::Constructor";
}


//% Reading from Flat File!!
/*void GarfunkelLocalizationMgr::Initialize()
{

    	_lm.SetPrimaryLanguageStoredProc("GetPrimaryLanguageStrings( )");
    	_lm.SetProgrammingLanguageStoredProc("GetProgrammingLanguageStrings( )");
    	_lm.SetSpecialStringStoredProc("GetSpecialLanguageStrings( )");
    	_lm.BuildStringMaps();
    	qmlRegisterUncreatableType<GarfunkelResourceStrings>("GarfunkelResourceStrings", 0, 1, "ResourceString", "enum for resource strings");
    	//_initialized = true;
}

GarfunkelLocalizationMgr&  GarfunkelLocalizationMgr::Instance()
{
	static GarfunkelLocalizationMgr singleton;
	if(!_initialized)
	singleton.Initialize();
	return singleton;
}*/

/***********************************************************************************
* Class: Localization manager 2: Explicitely creates and registers
*                                  the ResourceStrings QML type.
*
************************************************************************************/
GarfunkelLocalizationMgr2::GarfunkelLocalizationMgr2(GarfunkelDB *gdb, GarfunkelSystemContext *syscontext, QObject *parent) :
		QObject(parent), _gdb(gdb), _systemcontext(syscontext)
{

    connect(_systemcontext, SIGNAL(primaryLanguageChanged()), this, SLOT(LoadLanguageStrings()));;
    connect(_systemcontext, SIGNAL(tmLanguageChanged()), this, SLOT(LoadLanguageStrings()));

    connect(_systemcontext, SIGNAL(primaryLanguageChangedinDB()), this, SLOT(LoadLanguageStrings())); 
    connect(_systemcontext, SIGNAL(tmLanguageChangedinDB()), this, SLOT(LoadLanguageStrings()));
    
    //% Set localization Resource Bundle!!
    // Set primary locale load
    _primaryLanguage.SetResourcePath("/usr/local/applications/garfunkel/");
    _primaryLanguage.SetResourceName("Garfunkel");


    // Set programming locale load
    _programmingLanguage.SetResourcePath("/usr/local/applications/garfunkel/");
    _programmingLanguage.SetResourceName("Garfunkel");

    LoadLanguageStrings();

    //% Register the localised GarfunkelResourceStrings as a qml module!!!!!
    qmlRegisterUncreatableType<GarfunkelResourceStrings>("GarfunkelResourceStrings", 0, 1, "ResourceString", "enum for resource strings");
    qDebug() << "GarfunkelLocalizationMgr2 Object Constructed!!";
}

GarfunkelLocalizationMgr2::~GarfunkelLocalizationMgr2()
{
        _primaryLanguage.CloseLanguage();
       // _secondaryLanguage.CloseLanguage();
        _programmingLanguage.CloseLanguage();
}

QString GarfunkelLocalizationMgr2::GetPrimaryLanguageStringByID(int stringID)
{
    std::string retString = "primarystring";
    bool retValue;
    QString    primaryString;
    //qDebug() << "[GarfunkelLocalizationMgr2::GetPrimaryLanguageStringByID] id="<<stringID;
    retValue = _primaryLanguage.GetStringByKey(stringID, retString);
    //std::cout << "[GarfunkelLocalizationMgr2::Return String with StringID id =" <<stringID << " is String =" << retString << std::endl;

    if(retValue == true)
    {
           primaryString = QString::fromUtf8(retString.c_str(), retString.size());
    }
    else
 	    	qDebug() << "[GarfunkelLocalizationMgr2::GetPrimaryLanguageStringByID] failed for id="<<stringID;

    return primaryString;
}


QString GarfunkelLocalizationMgr2::GetTMLanguageStringByID(int stringID)
{
    std::string retString = "programing string";
    bool retValue;
    QString    tmString;

     //qDebug() << "[GarfunkelLocalizationMgr2::GetTMLanguageStringByID] id="<<stringID;

    retValue = _programmingLanguage.GetStringByKey(stringID, retString);

    //std::cout << "[GarfunkelLocalizationMgr2::Return String with StringID id ="<<stringID << " is String =" << retString  << std::endl;
    if(True == true)
    {
    	tmString = QString::fromUtf8(retString.c_str(), retString.size());
    }
    else
    	qDebug() << "[GarfunkelLocalizationMgr2::GetTMLanguageStringByID] failed for id="<<stringID;

    return tmString;
}

void GarfunkelLocalizationMgr2::SetPrimaryLanguageFont()
{

	//QString font;
	//font = QString::fromUtf8(_primaryLocaleFont.c_str(), _primaryLocaleFont.size());
	int pointSize= _primaryLocaleFontPointSize;
	QFont::Weight boldFont = QFont::Normal;

	if(_primaryLocaleFontBold==true)
		boldFont = QFont::Bold;

	QFont newFont(primaryFont, pointSize, boldFont);
	QApplication::setFont(newFont);

	_fallbackFontLoaded = 0;
	qDebug() << "[GarfunkelLocalizationMgr2::SetPrimaryLanguageFont] Setting primary lang font";
}

void GarfunkelLocalizationMgr2::SetTMLanguageFont()
{
	//QString font;

	//font = QString::fromUtf8(_programmingLocaleFont.c_str(), _programmingLocaleFont.size());
	int pointSize= _programmingLocaleFontPointSize;
	QFont::Weight boldFont = QFont::Normal;

	if(_programmingLocaleFontBold==true)
		boldFont = QFont::Bold;

	QFont newFont(programmingFont, pointSize, boldFont);
	QApplication::setFont(newFont);
	qDebug() << "[GarfunkelLocalizationMgr2::SetTMLanguageFont] Setting TM lang font="<<programmingFont<<" size="<<pointSize<<" boldStatus="<<boldFont;
}

QString GarfunkelLocalizationMgr2::GetPrimaryLanguageFontName()
{

    //qDebug() << "[GarfunkelLocalizationMgr2::GetTMLanguageFontName] GetPrimaryLanguageFontName="<<primaryFont;
    return primaryFont;
}


bool GarfunkelLocalizationMgr2::GetPrimaryLanguageFontBoldStatus()
{

    //qDebug() << "[GarfunkelLocalizationMgr2::GetPrimaryLanguageFontBoldStatus] GetPrimaryLanguageFontBoldStatus="<<_primaryLocaleFontBold;
    return (_primaryLocaleFontBold==True) ? true : false;
}


int GarfunkelLocalizationMgr2::GetPrimaryLanguageFontPointSize()
{

    //qDebug() << "[GarfunkelLocalizationMgr2::GetPrimaryLanguageFontPointSize] GetPrimaryLanguageFontPointSize="<<_primaryLocaleFontPointSize;
    return _primaryLocaleFontPointSize;
}

QString GarfunkelLocalizationMgr2::GetTMLanguageFontName()
{

    //qDebug() << "[GarfunkelLocalizationMgr2::GetTMLanguageFontName] programmingFont="<<programmingFont;
    return programmingFont;
}


bool GarfunkelLocalizationMgr2::GetTMLanguageFontBoldStatus()
{

    //qDebug() << "[GarfunkelLocalizationMgr2::GetTMLanguageFontBoldStatus] _programmingLocaleFontBold="<<_programmingLocaleFontBold;
    return (_programmingLocaleFontBold==True) ? true : false;
}

/*
void GarfunkelLocalizationMgr2::SetFallbackFontWhenPrimaryAndSecondaryFontDifferent()
{

	if(_systemcontext->getSecondaryLanguage()==-1)
	{

		qDebug() << "[GarfunkelLocalizationMgr2::ArePrimaryAndScondaryFontDifferent] Secondary lang not set sending false";
		return;
	}
	else
	{
		if(boost::iequals(_primaryLocaleFont,_secondaryLocaleFont))
		{
			qDebug() << "[GarfunkelLocalizationMgr2::ArePrimaryAndScondaryFontDifferent] returning False";
			return;
		}
		else
		{
			qDebug() << "[GarfunkelLocalizationMgr2::ArePrimaryAndScondaryFontDifferent] Setting fallback font";
			if(_fallbackFontLoaded==0)
			{
				//SetFallbackFontForPrimaryLanguage();
				_fallbackFontLoaded = 1;
			}
			return;
		}


	}
}
*/
void GarfunkelLocalizationMgr2::SetFallbackFontForPrimaryLanguage()
{
	QString font;
	font = QString::fromUtf8(_primaryLocaleFontFallback.c_str(), _primaryLocaleFontFallback.size());
	int pointSize= _primaryLocaleFallbackFontPointSize;
	QFont::Weight boldFont = QFont::Normal;

	if(_primaryLocaleFallbackFontBold==true)
		boldFont = QFont::Bold;

	QFont newFont(font, pointSize, boldFont);
	QApplication::setFont(newFont);

	qDebug() << "[GarfunkelLocalizationMgr2::SetFallbackFontForPrimaryLanguage] Setting primary lang FALLBACK font="<<font<<" pt size="<<pointSize;
}

void GarfunkelLocalizationMgr2::LoadLanguageStrings()
{
    qDebug() << "GarfunkelLocalizationMgr2::Language Changed, reloading language strings";

    if(true == GetLocalLanguageDisplay())
    {
        // Close out previous languages
                // Open the new languages.
        if(false == _primaryLanguage.OpenLanguage(_primaryLocale))
        {
                qDebug() << "[GarfunkelLocalizationMgr2::LoadLanguageStrings] could not open primaryLocale: " << _primaryLocale.c_str();
        }
        else
        {
                qDebug() << "[GarfunkelLocalizationMgr2::LoadLanguageStrings] Primary actual Locale: " << _primaryLanguage.GetActualLocale().c_str();
        }
        if(false == _programmingLanguage.OpenLanguage(_programmingLocale))
        {
        		qDebug() << "[GarfunkelLocalizationMgr2::LoadLanguageStrings] could not open programmingLocale: " << _programmingLocale.c_str();
        }
        else
        {
        		qDebug() << "[GarfunkelLocalizationMgr2::LoadLanguageStrings] Tm Programming actual Locale: " << _programmingLanguage.GetActualLocale().c_str();
        }

        _fallbackFontLoaded = 0;
        
        SetPrimaryLanguageFont ();
        SetTMLanguageFont();
        SetFallbackFontForPrimaryLanguage();
        //SetFallbackFontWhenPrimaryAndSecondaryFontDifferent();
    }

    emit localizedStringsChanged();
}

//% Get from the DB, the current Language Display Locals!!
bool GarfunkelLocalizationMgr2::GetLocalLanguageDisplay()
{
        bool retValue = false;

        if(false == _gdb->isConnected())
        {
        	_gdb->connect();
        }

        if(true == _gdb->isConnected())
        {
                // Set the name of the stored procedure to get the current languages.
                QString  langStoreProc =  "GetLanguageRef()";  
                ecolab::DB::DataSet     dataSet;
                dataSet = _gdb->executeStoredFunction(langStoreProc);

                if(dataSet.GetNumberOfRows() > 0)
                {
                        ecolab::DB::DataRow  row = dataSet.GetRow(0);

                        if(row.GetNumberOfColumns() > 0)
                        {
                                // Get the locales for the three different language strings.
                               //% For Primary Language( user Lanaguage!!)
                               //boost::shared_ptr<ecolab::DB::IColumnData>  column = row.GetColumn("primaryLang");
                                boost::shared_ptr<ecolab::DB::IColumnData>  column = row.GetColumn("LocaleID");
                                if(NULL != column.get())
                                {
                                        column->AsString(_primaryLocale);  // _primaryLocale = "en" for example
                                        std::cout << "[GarfunkelLocalizationMgr2::GetLocalLanguageDisplay] LocaleID = " << _primaryLocale << std::endl;
                                }
                               
                                //column = row.GetColumn("primaryLangFont");
                                column = row.GetColumn("Font");
                                if(NULL != column.get())
                                {
                                        column->AsString(_primaryLocaleFont);
                                        primaryFont = QString::fromUtf8(_primaryLocaleFont.c_str(), _primaryLocaleFont.size());
                                        std::cout << "[GarfunkelLocalizationMgr2::GetLocalLanguageDisplay] _primaryLocaleFont=" << _primaryLocaleFont << std::endl;
                                }
                                //column = row.GetColumn("primarylangfontpointsize");
                                column = row.GetColumn("PointSize");
                                if(NULL != column.get())
                                {
                                        column->AsInt(_primaryLocaleFontPointSize);
                                       // qDebug() << "[GarfunkelLocalizationMgr2::  GetLocalLanguageDisplay] _primaryLocaleFontPointSize="<<_primaryLocaleFontPointSize;
                                }
                                //column = row.GetColumn("primarylangfontbold");
                                column = row.GetColumn("BoldFont");
                                if(NULL != column.get())
                                {
                                        column->AsBool(_primaryLocaleFontBold);
                                         std::cout << "[GarfunkelLocalizationMgr2:: GetLocalLanguageDisplay] _primaryLocaleFontBold=" << _primaryLocaleFontBold << std::endl;
                                }

                                //column = row.GetColumn("primarylangfallbackfont");
                                column = row.GetColumn("Font");
                                if(NULL != column.get())
                                {
                                        column->AsString(_primaryLocaleFontFallback);
                                }

                                //column = row.GetColumn("primarylangfallbackfontpointsize");
                                column = row.GetColumn("PointSize");
                                if(NULL != column.get())
                                {
                                        column->AsInt(_primaryLocaleFallbackFontPointSize);
                                       // qDebug() << "[GarfunkelLocalizationMgr2::  GetLocalLanguageDisplay] _primaryLocaleFontPointSize="<<_primaryLocaleFontPointSize;
                                }
                                //column = row.GetColumn("primarylangfallbackfontbold");
                                column = row.GetColumn("BoldFont");
                                if(NULL != column.get())
                                {
                                        column->AsBool(_primaryLocaleFallbackFontBold);
                                         std::cout << "[GarfunkelLocalizationMgr2::  GetLocalLanguageDisplay] _primaryLocaleFallbackFontBold=" << _primaryLocaleFallbackFontBold << std::endl;
                                }

                                //% For TM Language!!
                                //column = row.GetColumn("programminglang");
                                column = row.GetColumn("LocaleID");
                                if(NULL != column.get())
                                {
                                        column->AsString(_programmingLocale);
                                       // qDebug() << "[GarfunkelLocalizationMgr2::  GetLocalLanguageDisplay] programminglang="<<_programmingLocale;
                                }
                                //column = row.GetColumn("programminglangfont");
                                column = row.GetColumn("Font");
                                if(NULL != column.get())
                                {
                                        column->AsString(_programmingLocaleFont);
                                        programmingFont = QString::fromUtf8(_programmingLocaleFont.c_str(), _programmingLocaleFont.size());
                                      //  qDebug() << "[GarfunkelLocalizationMgr2::  GetLocalLanguageDisplay] _programmingLocaleFont="<<_programmingLocaleFont;
                                }
                                //column = row.GetColumn("programminglangfontpointsize");
                                column = row.GetColumn("PointSize");
                                if(NULL != column.get())
                                {
                                        column->AsInt(_programmingLocaleFontPointSize);
                                        std::cout << "[GarfunkelLocalizationMgr2::  GetLocalLanguageDisplay] _programmingLocaleFontPointSize=" << _programmingLocaleFontPointSize << std::endl;
                                }
                                //column = row.GetColumn("programminglangfontbold");
                                column = row.GetColumn("BoldFont");
                                if(NULL != column.get())
                                {
                                        column->AsBool(_programmingLocaleFontBold);
                                        std::cout << "[GarfunkelLocalizationMgr2::  GetLocalLanguageDisplay] _programmingLocaleFontBold=" << _programmingLocaleFontBold << std::endl;
                                }

                                retValue = true;
                         }
                }
                else
                	qDebug() << "[GarfunkelLocalizationMgr2::  GetLocalLanguageDisplay] No rows returned";
      }
       else //db not connected, read from flat files
       {
          /*  //will read from flat files once implemented!!
    	  _systemcontext->getFontProperties(_primaryLocale, _programmingLocale, _primaryLocaleFont,  _programmingLocaleFont,
    			  _primaryLocaleFontPointSize, _programmingLocaleFontPointSize, _primaryLocaleFontBold, _programmingLocaleFontBold,
    			  _primaryLocaleFontFallback, _primaryLocaleFallbackFontPointSize, _primaryLocaleFallbackFontBold);
    	  primaryFont = QString::fromUtf8(_primaryLocaleFont.c_str(), _primaryLocaleFont.size());
	      programmingFont = QString::fromUtf8(_programmingLocaleFont.c_str(), _programmingLocaleFont.size());

    	  retValue = true;

          */
       }
      return retValue;
}






