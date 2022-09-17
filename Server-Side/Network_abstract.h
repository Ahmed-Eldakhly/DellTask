// gaurd to prevent including file many time.
#pragma once

// headers
#include <string>
#include <iostream>
#include <map>

// class prototype
class Network_abstract
{
    public:
        Network_abstract();
        virtual bool establishConnection() = 0;
        virtual bool sendPayloadThrowNetwork(std::map<std::string , std::string> protocolParameters, std::string payload) = 0;
        std::string getPayload();
        void setPayload(std::string payload);

    protected:
        std::string payload;

    private:
};

