#ifndef ABSTRACT_IPCMESSAGE_H
#define ABSTRACT_IPCMESSAGE_H
#include <iostream>
#include <QtCore>
#include "ecolab.h"

    // forward declaration
    class IPCCommand;
    class GarfunkelIpc;

    class AbstractIPCMessage : public virtual QObject
    {
        Q_OBJECT

        public:
            AbstractIPCMessage(GarfunkelIpc* ipc);
            virtual ~AbstractIPCMessage();

            virtual bool processMessage(IPCCommand& command, std::string& response) = 0;
            virtual bool sendMessage(int&);
            
            // methods to create and convert
            bool  createESPString(std::string& dataToConvert);
            bool  convertESPString(std::string& dataToConvert);
        protected:
            bool           _rcvAll(std::string& msg);
            void           _setLoopCount(int x) { _loopcount = x; }
            void           _setSleepFactor(int x) { _sleep_factor = x; }
            //void           _setPduStarterString(const char *);
            //void           _setAddressInstance(const char *);
            std::string    _ACK;
            std::string    _NACK;
            GarfunkelIpc*        _ipc;
            QString        _address_instance;
            std::string     _pdu_starter_string;
            int            _loopcount;    // for _recvAll timing
            int            _sleep_factor; // for _recvAll timing

    };
    
#endif





