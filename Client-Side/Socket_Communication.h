// gaurd to prevent including file many time.
#pragma once

// headers
#include "Network_abstract.h"
#include "Socket_Communication_Config.h"
#include <string>
#include <mutex>

// class prototype
class Socket_Communication : public Network_abstract
{
    public:
        static Socket_Communication* getInestance();
        std::mutex mtx;
  
        void listenToSpecificServer(std::map<std::string, std::string> protocolParameters);
        bool establishConnection(std::map<std::string, std::string> protocolParameters);
       
    protected:

    private:
        Socket_Communication();
        static Socket_Communication* socketConnectionInstance; 

        bool getPayloadFromNetwork();
};

