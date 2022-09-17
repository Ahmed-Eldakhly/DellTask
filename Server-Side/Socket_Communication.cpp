//haders
#include "Socket_Communication.h"
#include <iostream>
#include <string>
#include "../web-socket/easy-socket-master/include/masesk/EasySocket.hpp"

using namespace masesk;

/// <summary>
/// 
/// </summary>
Socket_Communication* Socket_Communication::socketConnectionInstance = nullptr;

/// <summary>
/// 
/// </summary>
Socket_Communication::Socket_Communication() {

}

/// <summary>
/// 
/// </summary>
/// <param name="receivedClientData"></param>
/// <param name="data"></param>
static void getDataFromClient(std::string& receivedClientData, const std::string& data) {
    receivedClientData = data;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
Socket_Communication* Socket_Communication::getInestance() {
    if (!socketConnectionInstance)
        socketConnectionInstance = new Socket_Communication();
    return socketConnectionInstance;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool Socket_Communication::establishConnection() {
    EasySocket socketManager;
    std::string receivedClientData;
    try {
        socketManager.socketListen(SERVER_CHANNEL, SERVER_PORT, &getDataFromClient, receivedClientData);
        return true;
    }
    catch (...) {
        return false;
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="protocolParameters"></param>
/// <param name="payload"></param>
/// <returns></returns>
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

