#ifndef GARFUNKELDB_CONTEXT_H
#define GARFUNKELDB_CONTEXT_H

#include <QObject>
#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include <QtDeclarative>
#include <QAbstractListModel>

#include <QStringList>
#include <QDebug>
#include <QDate>
#include <QTimer>


#include "GarfunkelDB.h"

class DateTime;


 //%   The number of seconds of inactivity while the user is in the programming menu before logging them out.

#define LOGIN_TIMEOUT_SECONDS   (int)(15*60) //15 minutes
//#define LOGIN_TIMEOUT_SECONDS   (int)(1 * 60) //15 minutes


//%   GarfunkelDBContext class.

class GarfunkelDBContext: public QObject
{
        Q_OBJECT

        Q_PROPERTY(QString lastLoginDate     READ   getlastLoginDate    WRITE setLastLoginDate   NOTIFY lastLoginDateChanged)
        Q_PROPERTY(bool loggedIn             READ   getloggedIn     WRITE   setLoggedIn    NOTIFY loggedInChanged)

public:
       //%  GarfunkelDBContext constructor.  
       GarfunkelDBContext (GarfunkelDB *gdb, QDeclarativeContext *context, QObject *parent = 0);

       // GarfunkelDBContext destructor.
       virtual ~GarfunkelDBContext();

       Q_INVOKABLE  
       void registerUserLogin();

      //%
      //%  GETTERS     
      //%
      //%    Method to return the date of the last login on the controller.
      //%    returns    The date of the last login on the controller.
      QString getlastLoginDate() const { return    _LastLoginDate; }
      //%    Method to return whether the user is logged in or not.
      bool getloggedIn() const { return         _LoggedIn; }

      //%
      //% SETTERS
      //% 
      void setLoggedIn (bool loggedIn);
      void setLastLoginDate ( QString date);




    //%
    //%  SIGNALS EMITTED     
    //%
signals:

        //%  Signal to notify that the last login date has changed.
        void lastLoginDateChanged();

        //%  Signal indicating that the user has logged in or out of the UI.
        void loggedInChanged();


//%
//%  Public SLOTS     
//%

public slots:
        //%    Slot to log an event to the EventDataLog showing that a user logged
        //%    out the TM menu.
        void logLogoutTime();



    
    
private:
        GarfunkelDB *_gDB;                        //!< Pointer to the database instance.
        QDeclarativeContext *_Context;      //!< Pointer to the root declarative context.


        QString _LastLoginDate;             //!< The date of the last login on the controller, set from the database.
        bool _LoggedIn;                     //!< This holds whether the user is logged into the  menus.
        QTimer loggedInTimer;               //!< Timer to detect for keypress inactivity while the user is logged in.


        //% Method to store the current date as the last login date in the database.
        void setLastLoginDateDB();


        //%
        //%  Private SLOTS     
        //%
private slots:

        //%  Method to get the last login date from the database.
        void getLastLoginDateDB();

        //%  Slot to handle a keypress, this is only used to reset the inactivity timer for the UI.
        void handleKeypress();

        //% Slot to act on a timeout of the login inactivity timeout timer.    
        void handleLoginTimeout();
    
};

#endif //GARFUNKELDB_CONTEXT_H
