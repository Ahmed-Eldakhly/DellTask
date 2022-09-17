//haders
#include "Socket_Communication.h"
#include <iostream>
#include <string>
#include "../web-socket/easy-socket-master/include/masesk/EasySocket.hpp"

using namespace masesk;

Socket_Communication* Socket_Communication::socketConnectionInstance = nullptr;

Socket_Communication::Socket_Communication() {

}

static void getDataFromClient(std::string& receivedClientData, const std::string& data) {
    receivedClientData = data;
    
}
//done
Socket_Communication* Socket_Communication::getInestance() {
    if (!socketConnectionInstance)
        socketConnectionInstance = new Socket_Communication();
    return socketConnectionInstance;
}

bool Socket_Communication::establishConnection() {
    EasySocket socketManager;
    std::string receivedClientData;
    try {
        socketManager.socketListen(SERVER_CHANNEL, SERVER_PORT, &getDataFromClient, receivedClientData);
        std::cout<<"receivedClientData  = "<< receivedClientData<<std::endl;
        this->setPayload(receivedClientData);
        return true;
    }
    catch (...) {
        return false;
    }
}

bool Socket_Communication::sendPayloadThrowNetwork(std::map<std::string, std::string> protocolParameters, std::string payload) {

    EasySocket socketManager;
    try {
        socketManager.socketConnect(protocolParameters.find("clientChannel")->second, protocolParameters.find("clientIp")->second,
            stoi(protocolParameters.find("clientPort")->second));
        socketManager.socketSend(protocolParameters.find("clientChannel")->second, payload);
        socketManager.closeConnection(protocolParameters.find("clientChannel")->second);
        return true;
    }
    catch (...) {
        return false;
    }
}

