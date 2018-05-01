#ifndef GARFUNKEL_IPC_H
#define GARFUNKEL_IPC_H

#include <map>
#include <string>

#include <QVariant>
#include <eipc.h>

class IPCCallback;
class QVariant;
class GarfunkelCommandProcessor;

class  GarfunkelIpc
{
    public:
        GarfunkelIpc(const std::string& from, const std::string& to);
        ~GarfunkelIpc();

        void sendStringMessage(const std::string &message);
        void receiveStringMessage(std::string &message);
        int  receiveESPCommandWithValidation();

        bool isMessageAvailable();
        int  processMessage();

        void registerCallback(const std::string &command, IPCCallback *fPtr);
        void setCommandProcessor(GarfunkelCommandProcessor* cp) { _cp = cp; }
        static void printMessage(const char*, std::string&);

    signals:
        void setSystemStatus(int status);

    public slots:

    private:
        GarfunkelCommandProcessor*  _cp;
        int                   _parseNameValuePair(std::string &message, std::string &nbame, std::string &value);
        int                   _convertToInt(const std::string &str);
        double                _convertToDouble(const std::string &str);
        bool                  _convertToBool(const std::string &str);
        ecolab::IPC           _ipc;
};

#endif // GARFUNKEL_IPC_H 

