#ifndef IPCEXCEPTION_H
#define IPCEXCEPTION_H

#include <exception>
#include <string>

class IPCException : public std::runtime_error
{
    public:
        IPCException(std::string const &s) : std::runtime_error(s) {}
};

#endif
