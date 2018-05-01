#include "GarfunkelCommThread.h"

#include <string>

#include <QVariant>
#include <QDebug>
#include <QTime>

#include "CommManager.h"
#include "GarfunkelCommandProcessor.h"
#include "GarfunkelIPC.h"

//% Don't Talk to DB for Now
//GarfunkelCommThread::GarfunkelCommThread(CommManager::MCACommType commtype, QObject *parent) 
//    : QThread(parent), _commType(commtype),   _abort(false), _ipcTimeout(false), _ipc(NULL), _cp(NULL), _masterloop(0)
GarfunkelCommThread::GarfunkelCommThread(GarfunkelDB& gdb, CommManager::MCACommType commtype, QObject *parent) 
    : QThread(parent), _gDB(gdb), _commType(commtype),   _abort(false), _ipcTimeout(false), _ipc(NULL), _cp(NULL), _masterloop(0)
{
    if(CommManager::MCA_MASTER == _commType)
    {
        //qDebug() << "[GarfunkelCommThread] thread created as MCA_MASTER ";
    }
    if(CommManager::MCA_SLAVE == _commType)
    {
        //qDebug() << "[GarfunkelCommThread] thread created as MCA_SLAVE ";
    }

}
GarfunkelCommThread::~GarfunkelCommThread() 
{
    _abort = true;
    wait();
    // delete messages too
    delete _cp;
    delete _ipc;

    //qDebug() << "[GarfunkelCommThread] thread destroyed";
}
void
GarfunkelCommThread::initMaster() 
{
    std::string to;
    std::string from;
    from = "GarfunkelUIMaster";
    to   = "GarfunkelMCASlave";
    _ipc = new GarfunkelIpc(from,to); 
    _cp = new GarfunkelCommandProcessor(_ipc,_commType, this);
    setPriority(QThread::TimeCriticalPriority);
}

void
GarfunkelCommThread::initSlave() 
{
    std::string to;
    std::string from;
    from = "GarfunkelUISlave";
    to   = "GarfunkelMCAMaster";
    _ipc = new GarfunkelIpc(from,to); 
    _cp = new GarfunkelCommandProcessor(_ipc,_commType, this);
    // 
    //    Timeout after 30 seconds of no IPC messages.
    // 
    _timeoutTimer.setInterval(1000 * 30);
    connect(&_timeoutTimer, SIGNAL(timeout()), this, SLOT(_communicationTimeout()));
    _timeoutTimer.start();
    //connect(this, SIGNAL(timeout(bool)), this, SLOT(_logTimeoutToDatabase(bool)));
}

void 
GarfunkelCommThread::_communicationTimeout() 
{
    //qDebug() << "[GarfunkelCommThread] IPC timeout..";
    emit timeout(true);
}
void 
GarfunkelCommThread::_masterupdate() 
{
//    qDebug() << "[GarfunkelCommThread] MASTER THREAD LOOPS =" << _masterloop ;
}

void 
GarfunkelCommThread::run() 
{
    if(CommManager::MCA_MASTER == _commType)
    {

        initMaster();
        //
        // MASTER RUN METHOD HAS OWN EVENT LOOP 
        //
        exec();
        //qDebug() << "[MASTER GarfunkelCommThread] ENTERING MAIN LOOP";
#ifdef LOOP
        for(;;)
        {
            // Our process loop gets signals from the main thread and processes them
            // in the CommandProcessor.
            usleep(50000);
            _masterloop++;
        }
#endif
    }
    else
    {
        //
        // SLAVE RUN METHOD - INIT THE SLAVE
        //
        initSlave();
        for(;;)
        {
            // Get messages from the MCA and process them
            int messagesProcessed = 0;
            int loops = 0;
            while (!_abort) {
                while (_ipc->isMessageAvailable()) 
                {
                    try {
//                        qDebug() << "[GarfunkelCommThread] MessageAvailable";
                        _ipc->receiveESPCommandWithValidation();
                        messagesProcessed++;
                    } catch (std::exception &e) {
                        qDebug() << "[GarfunkelCommThread] caught exception " << e.what();
                    }

                }

                _gDB.callDatabaseCallbacks();

                //
                //  DEBUG: Every 5 minutes dump the number of messages we received. This serves three purposes:
                //      1) that this thread is still running
                //      2) that our number of IPC messages is going up
                //      3) difference in IPC messages received  should be constant between debug statements
                //
                loops++;
                if (loops >= 6000) {
                    loops = 0;
                    //qDebug() << "[GarfunkelCommThread] processed" 
                    //         << messagesProcessed << "messages. time:" 
                    //         << QTime::currentTime().toString();
                }

                usleep(50000);
            }// end while
        } // end for
    }// end else
}

//%
//% Method to log an event to the database if no IPC messages are being received.
//%
//% \param[in]  timeout Whether or not the IPC timer has timed out.
//%
//% \param[out] None
//%
//% \return     None
//%


void  GarfunkelCommThread::_logTimeoutToDatabase(bool timeout)
{
    //
    //  Only log if the timeout state has changed.
    //
    if(_ipcTimeout != timeout)
    {
        _ipcTimeout = timeout;
        //qDebug() << "[GarfunkelCommThread] Logging IPC timeout to database.";
#ifdef SUPPORTED_IN_GARFUNKEL_gDB
        const QString executeString = "AddEventToLog(5,8," +
            QString((timeout ? "1" : "0")) +
            ",0,0,0,'ui')";

        _gDB.executeStoredFunction(executeString);
#endif
    }
}

