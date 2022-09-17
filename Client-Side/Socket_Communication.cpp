//haders
#include "Socket_Communication.h"
#include <iostream>
#include <string>
#include "../web-socket/easy-socket-master/include/masesk/EasySocket.hpp"

using namespace masesk;

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
static void getDataFromServer(std::string& receivedClientData, const std::string& data) {
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
/// <param name="protocolParameters"></param>
/// <returns></returns>
bool Socket_Communication::establishConnection(std::map<std::string, std::string> protocolParameters) {
    EasySocket socketManager;;
    std::string serverChannel = protocolParameters.find("serverChannel")->second;
    std::string serverIp = protocolParameters.find("serverIp")->second;
    int serverPort = stoi(protocolParameters.find("serverPort")->second);
    try {
        socketManager.socketConnect(serverChannel, serverIp, serverPort);
        std::string clientInfoAsString = "clientMacId:";
        clientInfoAsString.append(CLIENT_MAC_ID).append(",clientChannel:").append(CLIENT_CHANNEL).append(",clientPort:").append(std::to_string(CLIENT_PORT)).append(",clientIp:").append(CLIENT_IP);
        socketManager.socketSend(serverChannel, clientInfoAsString);
        socketManager.closeConnection(serverChannel);
        return true;
    }
    catch (...) {
        return false;
    }
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool Socket_Communication::getPayloadFromNetwork() {
    EasySocket socketManager;
    try {
        std::string receivedPayload;
        socketManager.socketListen(CLIENT_CHANNEL, CLIENT_PORT, &getDataFromServer, receivedPayload);
        setPayload(receivedPayload);
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
void Socket_Communication::listenToSpecificServer(std::map<std::string, std::string> protocolParameters) {
    std::string serverChannel = protocolParameters.find("serverChannel")->second;
    std::string serverIp = protocolParameters.find("serverIp")->second;
    int serverPort = stoi(protocolParameters.find("serverPort")->second);
    std::condition_variable cv;
    std::unique_lock<std::mutex> lck(mtx);

    int triersFlag = 0;
    while (triersFlag < 5) {
        std::cout << "Try to connct ...." << std::endl;
        if (!this->establishConnection(protocolParameters)) {
            std::cout << "Retry to connect with server : " << serverIp << ":" << serverPort << std::endl;
            triersFlag++;
            cv.wait_for(lck, std::chrono::seconds(5));
        }
        else {
            std::cout << "Conncted to server: " << serverIp << ":" << serverPort << std::endl;
            break;
        }
    }
    if (triersFlag == 5) 
        std::cout << "The node with channel name: " << serverChannel << " and url : " << serverIp << ":" << serverPort << " is not available now" << std::endl;
}

