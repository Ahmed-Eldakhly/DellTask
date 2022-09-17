// gaurd to prevent including file many time.
#pragma once

// headers
#include "Network_abstract.h"
#include "Socket_Communication_Config.h"
#include "string"

// class prototype
class Socket_Communication : public Network_abstract
{
    public:
        static Socket_Communication* getInestance();

        bool establishConnection();
        bool sendPayloadThrowNetwork(std::map<std::string, std::string> protocolParameters, std::string payload);

    protected:

    private:

        Socket_Communication();
        static Socket_Communication* socketConnectionInstance; 
};

