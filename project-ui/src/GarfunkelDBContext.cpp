
#include "GarfunkelDBContext.h"


//%
//%    GarfunkelDBContext constructor.
//%

GarfunkelDBContext::GarfunkelDBContext(GarfunkelDB *gdb, QDeclarativeContext *context, QObject *parent) :
    QObject(parent), _gDB(gdb), _Context(context)
{
    _LastLoginDate = "";
    _LoggedIn = false;
    loggedInTimer.setInterval(1000 * LOGIN_TIMEOUT_SECONDS);   //% default timeout is 15 minutes


    //%   Update the database driven values when the table updates.
    connect(_gDB, SIGNAL(controllerDataUpdated()), this, SLOT(getLastLoginDateDB()));


    //%   Fetch the last login date from the database.
    getLastLoginDateDB();

    //%  Receive an alert every time the user presses a button on the UI. This is used to detect for inactivity while the user is logged into the programming menu.
    connect(qApp, SIGNAL(keypress()), this, SLOT(handleKeypress()));


     //%  If inactivity is detected, and our timer fires, log the user out.
    connect(&loggedInTimer, SIGNAL(timeout()), this, SLOT(handleLoginTimeout()));

    // Equally Log user log out time from Status Screen hm?
    connect(&loggedInTimer, SIGNAL(timeout()), this, SLOT(logLogoutTime()));

}



//%  GarfunkelDBContext destructor.

GarfunkelDBContext::~GarfunkelDBContext()
{
  // Nothing to do for Now!!
}


//%
//% PUBLIC SLOTS
//%

//%
//%    logLogoutTime()
//%
//%    Method to log an event to the EventDataLog showing that a user logged into
//%    the Status screen.
//%

//% Log user logout time!!!
void GarfunkelDBContext::logLogoutTime()
{
    /*
    const QString executeString = "AddEventToLog(15,0,-1,-1,-1,-1,-1,-1,'ui')";
    _gDB->executeStoredFunction(executeString);
    */
    qDebug () <<"Doing Nothing for now!! Can't log when you loggin!!"; 
}


//%
//%  SETTERS   
//%

//%    setLastLoginDate(QString date)
//%
//%    Method to set the date of the last login on the controller.
//%    Input :   date    The date of the last login.
void GarfunkelDBContext::setLastLoginDate(QString date)
{
    if(_LastLoginDate != date)
    {
        _LastLoginDate = date;
        emit lastLoginDateChanged();
    }
}

//%
//%    setLoggedIn(bool loggedIn)
//%    Method to set whether the user is logged in.
///%   Input from UI is: loggedIn   
//%  Starts timer as soon as user is logged in!!.
void GarfunkelDBContext::setLoggedIn(bool loggedIn)
{
    if(_LoggedIn != loggedIn)
    {
        _LoggedIn = loggedIn;
        qDebug() << "GarfunkelDBContext::setLoggedIn: _LoggedIn="<<_LoggedIn;

        if(_LoggedIn)
        {

            //% Start/reset the logged in inactivity timer.
            loggedInTimer.start();
        }
        else
        {
         
            //%    User has/has been logged out, stop the timer.
            loggedInTimer.stop();
        }

        emit loggedInChanged();
    }
}


//%
//% USEFUL METHODS
//% 

//% Private Method
//%

//%
//%    setLastLoginDateDB():
//%    Method to set the last login date in the database to the current date.
//%
//%  
void GarfunkelDBContext::setLastLoginDateDB()
{
    /*
    const QString executeString1 = "SetLastLogin()";

    _gDB->executeStoredFunction(executeString1);

    //log that menu system entered
    const QString executeString2 = "AddEventToLog(15,1,-1,-1,-1,-1, -1, -1,'ui')";

    _gDB->executeStoredFunction(executeString2);
    */
    qDebug() << "Function to Log login Data into database  Unavailable for now!!"; 
}

//% Public Method
//%

//%
//%    registerUserLogin()
//%
//%    Method called from the UI indicating that the user has logged in.
Q_INVOKABLE void GarfunkelDBContext::registerUserLogin()
{
 
    //% Set the login date in the database.
    setLastLoginDateDB();
}


//%
//%  PRIVATE SLOTS
//%

//%
//%    getLastLoginDateDB()
//%    Method to get the last login data from the database.
//%
void GarfunkelDBContext::getLastLoginDateDB()
{
    ecolab::DB::DataSet dataSet;
    dataSet = _gDB->executeStoredFunction(QString("GetLastLogin()"));

    if(dataSet.GetNumberOfRows() == 1)
    {
        ecolab::DB::DataRow rowData(dataSet.GetFirstRow());

        const QString loginDate = _gDB->value(rowData, "lastlogin",  GarfunkelDB::String).toString();
        if(!loginDate.isEmpty())
        {
            
            //%    Split the date/time into date and time.
            const QStringList list = loginDate.split(" ");

            if(list.size() >= 1)
            {
                
                //%    Format and set the date.
                const QDate date = QDate::fromString(list.at(0), "yyyy-MM-dd");
                setLastLoginDate(date.toString("MM.dd.yyyy"));
                qDebug() << "GarfunkelDBContext::getLastLoginDateDB: Successfully setting last login time from DB";
            }
        }
    }
    else
    {
        qDebug() << "[DB] ERROR GetLastLogin() returned " << dataSet.GetNumberOfRows() << " rows. Expected 1.";
    }
}


//%
//% handleKeypress():
//% Method called everytime a user presses a key on the UI. This is used to
//% reset the inactivity timer while the user is logged in.
void GarfunkelDBContext::handleKeypress()
{
    // reset the timeout timer if user is logged in
    if(_LoggedIn)
    {
        //qDebug() << "GarfunkelDBContext::handleKeypress: Starting timer again";
        loggedInTimer.start();

    }
}

//%
//%   handleLoginTimeout():
//%   Method to handle a inactivity event while the user is logged in. If the
//%   user doesn't press any keys within a set period of time, log them out of
//%   the programming menus.
void GarfunkelDBContext::handleLoginTimeout()
{

     //% Forcibly log the user out.
    qDebug() << "GarfunkelDBContext::handleLoginTimeout: Timeout/Force logout...Logging the user out.";
    setLoggedIn(false);

    /*
    //log that menu system exited
    const QString executeString2 = "AddEventToLog(15,0,-1,-1,-1, -1, -1, -1,'ui')";
     _gDB->executeStoredFunction(executeString2);
    */
     qDebug() <<"Function not available for now!!";
}


