#ifndef GARFUNKEL_COMMTHREAD_H
#define GARFUNKEL_COMMTHREAD_H

#include <QThread>
#include <QTimer>

#include "CommManager.h"
#include "GarfunkelIPC.h"
#include "GarfunkelDB.h"

// forward declaration
class IPCCallback;
class GarfunkelCommandProcessor;
class GarfunkelIpc;

class GarfunkelCommThread : public QThread
{
    Q_OBJECT
public:

    GarfunkelCommThread(GarfunkelDB& gdb, CommManager::MCACommType, QObject *parent = 0);
    //% Don't use DataBase for now!!
    //GarfunkelCommThread(CommManager::MCACommType, QObject *parent = 0);
    ~GarfunkelCommThread();

    void secsleep(unsigned long sec)    { sleep(sec);   }
    void millisleep(unsigned long msec) { msleep(msec); }

signals:
    void timeout(bool timeout);

public slots:
    void                       _masterupdate();

protected:
    void run();
    void initMaster();
    void initSlave();
private:
//    SystemStatusMessage*       _systemStatusMessage;
    GarfunkelDB&              _gDB;  // reference to database object
    GarfunkelIpc      *       _ipc;
    GarfunkelCommandProcessor*  _cp;
    QTimer                     _timeoutTimer;
    QTimer                     _masterTimer;
    CommManager::MCACommType   _commType;
    bool                       _abort;
    bool                       _ipcTimeout;
    int                        _masterloop;

private slots:
    void                       _communicationTimeout();
    void                       _logTimeoutToDatabase(bool timeout);

};

#endif // GARFUNKEL_COMMTHREAD_H


