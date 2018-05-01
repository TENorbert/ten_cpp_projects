#include <QStringList>
#include <QDate>
#include <QApplication>

#include "aquanomicscontext.h"
#include "menudatamodel.h"
//#include "videotypes.h"

/*!
    AquanomicsContext constructor.

    \param[in]  db      Pointer to the database instance.
    \param[in]  parent  Optional QObject parent instance.

    \param[out] None

    \return     None
*/
AquanomicsContext::AquanomicsContext(AquanomicsDB *db, QDeclarativeContext *context, QObject *parent) :
    QObject(parent), mDB(db), mContext(context)
{

    mVideosEnabled = true;
    mDemoMode = false;
    mLastLoginDate = "";
    mLoggedIn = false;
    loggedInTimer.setInterval(1000 * LOGIN_TIMEOUT_SECONDS);   // default timeout is 5 minutes

    /*
        Update the database driven values when the table updates.
    */
    connect(mDB, SIGNAL(controllerDataUpdated()), this, SLOT(getLastLoginDateDB()));
    //connect(mDB, SIGNAL(videosUpdated()), this, SLOT(getVideoList()));

    /*
        Fetch the last login date from the database.
    */
    getLastLoginDateDB();

    /*
        Receive an alert every time the user presses a button on the UI. This is used to detect for inactivity while the user is logged into the programming menu.
    */
    connect(qApp, SIGNAL(keypress()), this, SLOT(handleKeypress()));

    /*
        If inactivity is detected, and our timer fires, log the user out.
    */
    connect(&loggedInTimer, SIGNAL(timeout()), this, SLOT(handleLoginTimeout()));

    getVideoList();
   // mContext->setContextProperty("helpMenuVideos", &mHelpMenuVideos);
}

/*!
    ApexContext destructor.

    \param[in]  None

    \param[out] None

    \return     None
*/
AquanomicsContext::~AquanomicsContext()
{
    /*
        Empty.
    */
}

/*!
    Method to get the last login data from the database.

    \param[in]  None

    \param[out] None

    \return     None
*/
void AquanomicsContext::getLastLoginDateDB()
{
    ecolab::DB::DataSet dataSet;
    dataSet = mDB->executeStoredFunction(QString("GetLastLogin()"));

    if(dataSet.GetNumberOfRows() == 1)
    {
        ecolab::DB::DataRow rowData(dataSet.GetFirstRow());

        const QString loginDate = mDB->value(rowData, "lastlogin",  AquanomicsDB::String).toString();
        if(!loginDate.isEmpty())
        {
            /*
                Split the date/time into date and time.
            */
            const QStringList list = loginDate.split(" ");

            if(list.size() >= 1)
            {
                /*
                    Format and set the date.
                */
                const QDate date = QDate::fromString(list.at(0), "yyyy-MM-dd");
                setLastLoginDate(date.toString("MM.dd.yyyy"));
                qDebug() << "AquanomicsContext::getLastLoginDateDB: Successfully setting last login time from DB";
            }
        }
    }
    else
    {
        qDebug() << "[DB] ERROR GetLastLogin() returned " << dataSet.GetNumberOfRows() << " rows. Expected 1.";
    }
}

/*!
    Method to set the last login date in the database to the current date.

    \param[in]  None

    \param[out] None

    \return     None
*/
void AquanomicsContext::setLastLoginDateDB()
{
    const QString executeString1 = "SetLastLogin()";

    mDB->executeStoredFunction(executeString1);

    //log that menu system entered
    const QString executeString2 = "AddEventToLog(15,1,-1,-1,-1,-1, -1, -1,'ui')";

    mDB->executeStoredFunction(executeString2);
}

/*!
    Method called everytime a user presses a key on the UI. This is used to
    reset the inactivity timer while the user is logged in.

    \param[in]  None

    \param[out] None

    \return     None
*/
void AquanomicsContext::handleKeypress()
{
    /*
        If a user is logged in, reset the timeout timer.
    */
    if(mLoggedIn)
    {
    	//qDebug() << "AquanomicsContext::handleKeypress: Starting timer again";
        loggedInTimer.start();

    }
}

/*!
    Method to handle a inactivity event while the user is logged in. If the
    user doesn't press any keys within a set period of time, log them out of
    the programming menus.

    \param[in]  None

    \param[out] None

    \return     None
*/
void AquanomicsContext::handleLoginTimeout()
{
    /*
        Forcibly log the user out.
    */
	qDebug() << "AquanomicsContext::handleLoginTimeout: Timeout/Force logout...Logging the user out.";
    setLoggedIn(false);
    //log that menu system exited
    const QString executeString2 = "AddEventToLog(15,0,-1,-1,-1, -1, -1, -1,'ui')";
     mDB->executeStoredFunction(executeString2);
}

/*!
    Method to log an event to the EventDataLog showing that a user logged into
    the Status screen.

    \param[in]  None

    \param[out] None

    \return     None
*/
void AquanomicsContext::logLogoutTime()
{
    const QString executeString = "AddEventToLog(15,0,-1,-1,-1,-1,-1,-1,'ui')";
    mDB->executeStoredFunction(executeString);
}

/*!
    Method to log an event to the EventDataLog showing that a user played a
    video.

    \param[in]  databaseId      The database id (VideoID) of the video.
    \param[in]  tabletVideoId   The tablet video id (TabletVideoId) of the video.

    \param[out] None

    \return     None
*/
void AquanomicsContext::logVideoPlay(int databaseId, int tabletVideoId)
{
}

/*!
    Method to get the list of help vidoes from the database.

    \param[in]  None

    \param[out] None

    \return     None
*/
void AquanomicsContext::getVideoList()
{
#if 0
    ecolab::DB::DataSet dataSet;

    mHelpMenuVideos.reset();

    dataSet = mDB->executeStoredFunction("GetVideosByType(" + QString::number(VIDEO_TYPE_HELP_MENU) + ")");

    int numRows = dataSet.GetNumberOfRows();
    if(numRows > 0)
    {
        for(int row = 0; row < numRows; ++row)
        {
            ecolab::DB::DataRow rowData(dataSet.GetRow(row));
            QVariant tmp;

            tmp =  mDB->value(rowData, "VideoName",  AquanomicsDB::String);
            QString name = tmp.toString();

            tmp = mDB->value(rowData, "VideoID", AquanomicsDB::Int);
            int index = tmp.toInt();

            tmp = mDB->value(rowData, "TabletVideoID", AquanomicsDB::Int);
            int tabletVideoId = tmp.toInt();

            tmp = mDB->value(rowData, "VideoPath",  AquanomicsDB::String);
            QString path = tmp.toString();

            tmp = mDB->value(rowData, "StringID",AquanomicsDB::Int);
            int stringId = tmp.toInt();

            mHelpMenuVideos.addMenuData(VideoData(index, name, path, stringId, tabletVideoId));
        }
    }
    else
    {
        qDebug() << "[DB] ERROR: GetVideos() returned no vidoes.";
    }
#endif
}
