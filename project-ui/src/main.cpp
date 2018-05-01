#include <QtGui/QApplication>
#include <QtCore>
#include <QtDeclarative>
#include <QDeclarativeView>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QWSServer>
#include <QBrush>
#include <QPointer>
//#include <QtQml>   //To register Custom C++ QML types

#include <eapplication.h>

#include "GarfunkelDB.h"
#include "GarfunkelCommThread.h" 
#include "GarfunkelSystemData.h"
#include "GarfunkelDiagnosticContext.h" 
#include "GarfunkelSystemContext.h" 
#include "GarfunkelSystemInfoContext.h" 
#include "GarfunkelDBContext.h"
#include "PasswordContext.h"
#include "PasswordManager.h"
#include "GarfunkelLocalizationManager.h"
#include "garfunkelresourcestrings.h"


int main(int argc, char *argv[])
{
    EcolabApplication gApp(argc, argv, QApplication::GuiServer);
    QDeclarativeView view;
    bool verbose = false;


#ifdef Q_WS_QWS
    // remove the titlebar in embedded linux
    view.setWindowFlags(Qt::FramelessWindowHint);
    //QWSServer::setCursorVisible(false); // No Cursors here!!
    QWSServer::setBackground(QBrush(QImage(":/images/ecolab-logo.png")));
#else
    view.setGeometry(QRect(100, 100, 480, 272));
#endif

    QApplication::setGraphicsSystem("raster");
    QApplication::setApplicationName("Garfunkel-ui");
    QApplication::sendPostedEvents(0,QEvent::DeferredDelete);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));


    QStringList arguments(QCoreApplication::arguments());
    QStringList::const_iterator itr;
    for (itr = arguments.constBegin(); itr != arguments.constEnd(); ++itr)
    {
        QString arg((*itr).constData());

        if (arg == "-verbose")
        {
            verbose = true;
        }
    }
    

     // Now add Custom Made QML Objects here!!
#if 1
    //% create Database Instance
    GarfunkelDB &gdb = GarfunkelDB::Instance();

    //% Garfunkel Database Status Context
    GarfunkelDBContext garfunkeldbcontext(&gdb, view.rootContext());
    view.rootContext()->setContextProperty("garfunkeldbcontext", &garfunkeldbcontext);

    //% System Context Class!!
    GarfunkelSystemContext garfunkelsystemcontext(&gdb, view.rootContext());
    view.rootContext()->setContextProperty("garfunkelsystemcontext", &garfunkelsystemcontext);

    
    //%Localization /Language Translation!! from DB
    GarfunkelLocalizationMgr GarfunkelLM(&gdb,&garfunkelsystemcontext);
    view.rootContext()->setContextProperty("GarfunkelLMFromDB", &GarfunkelLM);
    qmlRegisterUncreatableType<GarfunkelLocalizationMgr>("GarfunkelLM", 0, 1, "GarfunkelLM", "Garfunkel Localization Manager");

    // //%Localization /Language Translation!! from Resource Bundle!!!
    GarfunkelLocalizationMgr2 GarfunkelLM2(&gdb, &garfunkelsystemcontext);
    view.rootContext()->setContextProperty("GarfunkelLM", &GarfunkelLM2);
    qmlRegisterUncreatableType<GarfunkelLocalizationMgr2>("GarfunkelLM2", 0, 1, "GarfunkelLM2", "Garfunkel Localization Manager 2");
    

    //%% Garfunkel System Information Context Class!!
    GarfunkelSystemInfoContext garfunkelsysinfocontext(&gdb, &GarfunkelLM, &GarfunkelLM2, view.rootContext());
    //GarfunkelSystemInfoContext garfunkelsysinfocontext(&gdb, view.rootContext());
    view.rootContext()->setContextProperty("garfunkelsysinfocontext", &garfunkelsysinfocontext);

    // GarfunkelDiagnosticContext made accessible to QML screens
    GarfunkelDiagnosticContext diagcontext(&gdb, &GarfunkelLM2, view.rootContext());
    //GarfunkelDiagnosticContext diagcontext(view.rootContext());
    view.rootContext()->setContextProperty("diagcontext", &diagcontext);
    
    //% Password Manager
    PasswordManager pwdmanager(view.rootContext());
    view.rootContext()->setContextProperty("pwdmanager", &pwdmanager); 

    //%  Password Context
    PasswordContext passwdcontext(&gdb, &garfunkelsystemcontext, view.rootContext());
    view.rootContext()->setContextProperty("passwdcontext", &passwdcontext);


#endif
    // This is the MASTER side that sends commands to the MCA and gets responses from it.
    //GarfunkelCommThread mca_client(CommManager::MCA_MASTER); //% leave DB alone for now!!
    GarfunkelCommThread mca_client(gdb,CommManager::MCA_MASTER); 
    mca_client.start();

    // This is the SLAVE side that takes commands from the MCA (ie, serves it).
    //GarfunkelCommThread mca_server(CommManager::MCA_SLAVE); //% Leave DB alone for now!!
    GarfunkelCommThread mca_server(gdb,CommManager::MCA_SLAVE); 
    mca_server.start();
  
   // Default screen will be Quick Status idle screen 
   //view.setSource(QUrl("qrc:/qml/GarfunkelIdleScreen.qml"));
   //view.setSource(QUrl("qrc:/qml/MainScreen.qml"));
   view.setSource(QUrl("qrc:/qml/QuickStatus.qml"));

  // register a new C++ custom defined QML Type as
  // Recall to add #include <QtQml> in your .h or .cpp file
  // qmlRegisterType<MyCustomType> ("MyCustomTypeName", 0, 1, "MyCustomType");
  // For local qml files do:
  // view.setSource(QUrl::fromLocalFile("myFileToView.qml"));

    view.setAttribute(Qt::WA_OpaquePaintEvent);
    view.setAttribute(Qt::WA_NoSystemBackground);
    view.viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
    view.viewport()->setAttribute(Qt::WA_NoSystemBackground);

    //GarfunkelSystemData Instance used during entire program life;
    GarfunkelSystemData& sdo = GarfunkelSystemData::Instance();

    sdo.checkFirstConnection();
#ifdef Q_WS_QWS
    view.showFullScreen();
#else
    view.show();
#endif

    return gApp.exec();
}
