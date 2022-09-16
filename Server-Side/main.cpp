// headers
#include <iostream>
#include "limits.h"
#include "Temperature_Sensor.h"
#include "Network_abstract.h"
#include "Socket_Communication.h"
#include "Data_Parser_And_Converter.h"
#include "Clients.h"
#include "vector"
#include <map>
#include <string>
#include <thread>
#include <condition_variable>
#include <utility>
// #include <gtest/gtest.h>


// #define
#define TEST_OR_BUILD 0// 1 for Test - 0 for build

// structs and enums

// global variables
std::condition_variable cv;


// main
int main(int argc, char** argv)
{
#if TEST_OR_BUILD
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    std::vector<Clients> clients;

    Temperature_Sensor temperatureSensor;
    Socket_Communication* socketConnection = Socket_Communication::getInestance();
    std::map<std::string, std::string> socketDataConvertedToMap;

    std::thread sendDataToClientsThread([&]() {
        float currentTemperature;
        std::string ServerMacId = SERVER_MAC_ID;
        std::map<std::string, std::string> clientInfo = { {"clientChannel" , "wait"} , {"clientIp" , "wait"} , {"clientPort" , "wait"}};
        std::string payload;
        std::mutex mtx;
        std::unique_lock<std::mutex> lck(mtx);

        while (true) {
            std::cout << "Now, gonna send temperature to all clients" << std::endl;
            // get current temperature had been sent by sensor
            currentTemperature = temperatureSensor.getSensorReading();
            // form the server payload to be sent to each client
            payload = "ServerMacId:" + ServerMacId + ",Temperature:" + std::to_string(currentTemperature);

            for (auto it = clients.begin(); it != clients.end(); ) {
                clientInfo.find("clientChannel")->second = it->getClientChannel();
                clientInfo.find("clientIp")->second = it->getClientIp();
                clientInfo.find("clientPort")->second = it->getClientPort();
                if (socketConnection->sendPayloadThrowNetwork(clientInfo, payload))
                    ++it;
                else
                    clients.erase(it++);
            }
            cv.wait_for(lck, std::chrono::seconds(1));
        }

        });
    // get new temperature each specific time (her is one second)
    std::thread setTemperaturePeriodically(&Temperature_Sensor::generateTemperaturePeriodically, &temperatureSensor);

    // main logic to listen to any new client that need temperature
    while (true) {
        if (socketConnection->establishConnection()) {
            socketDataConvertedToMap = Data_Parser_And_Converter::parseDataThenConvertToMap("," , ":" , socketConnection->getPayload());
            bool clientIsExist = false;
            std::string newClientMacId = socketDataConvertedToMap.find("clientMacId")->second;
            for (auto it = clients.begin(); it != clients.end(); it++)
                if (it->getClientMacId() == newClientMacId)
                    clientIsExist = true;
            if (!clientIsExist) {
                Clients newClient(socketDataConvertedToMap.find("clientChannel")->second, socketDataConvertedToMap.find("clientIp")->second, socketDataConvertedToMap.find("clientMacId")->second, stoi(socketDataConvertedToMap.find("clientPort")->second));
                clients.push_back(newClient);
            }
        }
    }

    setTemperaturePeriodically.join();
    sendDataToClientsThread.join();
#endif // TEST_OR_BUILD
}
