//!
//! CommManager is an object intended to manager communications connections.
//!
//! CommManager  defines MCACommType used in building CommThreads that process certain
//! types of messages between the MCA and the UI. It might eventually be a factory for
//! building communications threads.
//!
//!
#ifndef COMM_MANAGER_H
#define COMM_MANAGER_H

#include <QtCore>


class CommManager 
{

    public:
        enum MCACommType { MCA_SLAVE = 1, MCA_MASTER = 2 };

        CommManager();
        virtual ~CommManager();
        

    private:

};
#endif
