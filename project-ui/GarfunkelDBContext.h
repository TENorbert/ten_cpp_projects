#ifndef AQUANOMICSCONTEXT_H
#define AQUANOMICSCONTEXT_H

#include <QObject>
#include <QDebug>
#include <QDate>
#include <QDeclarativeContext>
#include <QTimer>

#include "aquanomicsdb.h"
#include "menudatamodel.h"

class DateTime;

/*!
    The number of seconds of inactivity while the user is in the programming menu before logging them out.
*/
#define LOGIN_TIMEOUT_SECONDS   (int)(15 * 60) //15 minute

/*!
    AquanomicsContext class.

*/
class AquanomicsContext: public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool videosEnabled READ videosEnabled NOTIFY videosEnabledChanged)
    Q_PROPERTY(bool demoMode READ demoMode WRITE setDemoMode NOTIFY demoModeChanged)

    Q_PROPERTY(QString lastLoginDate READ lastLoginDate NOTIFY lastLoginDateChanged)
    Q_PROPERTY(bool loggedIn READ loggedIn WRITE setLoggedIn NOTIFY loggedInChanged)

public:
    /*!
        AquanomicsContext constructor.
    */
    AquanomicsContext(AquanomicsDB *db, QDeclarativeContext *context, QObject *parent = 0);

    /*!
        AquanomicsContext destructor.
    */
    ~AquanomicsContext();

    bool videosEnabled() const { return mVideosEnabled; }

    void setVideosEnabled(bool videosEnabled)
    {
        if(videosEnabled != mVideosEnabled)
        {
            mVideosEnabled = videosEnabled;
            emit videosEnabledChanged();
        }
    }

    /*!
        Method to return whether demo mode is on or off.

        \param[in]  None

        \param[out] None

        \return     Whether or not demo mode is enabled.
    */
    bool demoMode() const { return mDemoMode; }

    /*!
        Method to enable demo mode.

        Demo mode will enable the wash/rinse machine inputs and spin the wash
        dispense status icon. This also enabled the toggle alarm softkey to
        simulate an alarm.

        \param[in]  demoMode    Whether to enable or disable demo mode.

        \param[out] None

        \return     None
    */
    void setDemoMode(bool demoMode)
    {
        if(demoMode != mDemoMode)
        {
            mDemoMode = demoMode;
            emit demoModeChanged();

            /*
                If demo mode is on, show some icons.
            */
/*            if(demoMode)
            {
                setWashMachineInput(true);
                setWashDispenseStatus(true);
                setRinseMachineInput(true);
                setRinseDispenseStatus(false);
            }
            else
            {
                setWashMachineInput(false);
                setWashDispenseStatus(false);
                setRinseMachineInput(false);
                setRinseDispenseStatus(false);
            }*/
        }
    }

    /*!
        Method to return the date of the last login on the controller.

        \param[in]  None

        \param[out] None

        \return     The date of the last login on the controller.
    */
    QString lastLoginDate() const { return mLastLoginDate; }

    /*!
        Method to set the date of the last login on the controller.

        \param[in]  date    The date of the last login.

        \param[out] None

        \return     None
    */
    void setLastLoginDate(QString date)
    {
        if(mLastLoginDate != date)
        {
            mLastLoginDate = date;
            emit lastLoginDateChanged();
        }
    }


    /*!
        Method called from the UI indicating that the user has logged in.

        \param[in]  None

        \param[out] None

        \return     None
    */
    Q_INVOKABLE void registerUserLogin()
    {
        /*
            Set the login date in the database.
        */
        setLastLoginDateDB();
    }

    /*!
        Method to return whether the user is logged in or not.

        \param[in]  None

        \param[out] None

        \return     Whether the user is logged in or not.
    */
    bool loggedIn() const { return mLoggedIn; }

    /*!
        Method to set whether the user is logged in.

        \param[in]  loggedIn    Whether the user is logged in or not.

        \param[out] None

        \return     None
    */
    void setLoggedIn(bool loggedIn)
    {
        if(mLoggedIn != loggedIn)
        {
            mLoggedIn = loggedIn;
            qDebug() << "AquanomicsContext::setLoggedIn: mLoggedIn="<<mLoggedIn;

            if(mLoggedIn)
            {
                /*
                    Start/reset the logged in inactivity timer.
                */
                loggedInTimer.start();
            }
            else
            {
                /*
                    User has/has been logged out, stop the timer.
                */
                loggedInTimer.stop();
            }

            emit loggedInChanged();
        }
    }

signals:

    void videosEnabledChanged();

    /*!
        Signal to notify that the demo mode has changed.
    */
    void demoModeChanged();


    /*!
        Signal to notify that the last login date has changed.
    */
    void lastLoginDateChanged();

    /*!
        Signal indicating that the user has logged in or out of the UI.
    */
    void loggedInChanged();

public slots:

    /*!
        Slot to log an event to the EventDataLog showing that a user logged
        out the TM menu.
    */
    void logLogoutTime();

    /*!
        Slot to log en event to the EventDataLog showing that a video was played.
    */
    void logVideoPlay(int databaseId, int tabletVideoId);

private:
    AquanomicsDB *mDB;                        //!< Pointer to the database instance.
    QDeclarativeContext *mContext;      //!< Pointer to the root declarative context.

    bool mVideosEnabled;                //!< Whether or not vidoes are enable.
    bool mDemoMode;                     //!< Whether or not demo mode is enabled.

    QString mLastLoginDate;             //!< The date of the last login on the controller, set from the database.

    bool mLoggedIn;                     //!< This holds whether the user is logged into the programming menus.
    QTimer loggedInTimer;               //!< Timer to detect for keypress inactivity while the user is logged in.

   //MenuDataModel<VideoData> mHelpMenuVideos;   //!< Data model for help videos.

    /*!
        Method to store the current date as the last login date in the database.
    */
    void setLastLoginDateDB();

private slots:
    /*!
        Method to get the last login date from the database.
    */
    void getLastLoginDateDB();

    /*!
        Slot to handle a keypress, this is only used to reset the inactivity timer for the UI.
    */
    void handleKeypress();

    /*!
        Slot to act on a timeout of the login inactivity timeout timer.
    */
    void handleLoginTimeout();

    /*!
        Slot to get the list of help videos from the database.
    */
    void getVideoList();
};

#endif //AQUANOMICSCONTEXT_H
