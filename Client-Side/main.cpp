// headers
#include <iostream>
#include "Temperature_Server.h"
#include "Network_abstract.h"
#include "Socket_Communication.h"
#include "Data_Parser_And_Converter.h"
#include "..\web-socket\easy-socket-master\include\masesk\EasySocket.hpp"
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <ctime> 
//#include <gtest/gtest.h>


// #define
#define IDENTIFER                                          "ServerMacId"
#define ATTRIBUTE                                           "Temperature"
#define PERIODIC_TIME_TO_GET_SENSOR_AVERAGE                 5
#define PERIODIC_TIME_TO_GET_SENSOR_ACCUMELATIVE_AVERAGE    5
#define timegm                                              _mkgmtime
#define TEST_OR_BUILD 0// 1 for Test - 0 for build

// structs and enums

// global variables
std::condition_variable cv;

// application function prototypes
float calculateAccumelatedAverages(std::vector<Temperature_Sensor>& temperatureServers);
bool comparTimestamp(tm timestamp);

// main
int main(int argc, char** argv) {

#if TEST_OR_BUILD
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    std::map<std::string, std::string> clientInfo;
    std::vector<Temperature_Sensor> temperatureServers;
    std::mutex mtx;
    Socket_Communication* socketConnection = socketConnection->getInestance();
    std::map<std::string, std::string> serverInfo1 = { {"serverChannel" , "broadcastingChannel"} , {"serverIp" , "127.0.0.1"} , {"serverPort" , "9000"} };
    std::thread nodeThread1(&Socket_Communication::listenToSpecificServer, socketConnection, serverInfo1);
    std::map<std::string, std::string> serverInfo2 = { {"serverChannel" , "broadcastingChannel"} , {"serverIp" , "127.0.0.1"} , {"serverPort" , "9500"} };
    std::thread nodeThread2(&Socket_Communication::listenToSpecificServer, socketConnection, serverInfo2);

    std::thread calculateTemperetureAvgThread([&]() {
        std::unique_lock<std::mutex> lck(mtx);
        while (true) {
            int sizeOfNodes = temperatureServers.size();
            for (int i = 0; i < sizeOfNodes; i++) {
                temperatureServers[i].calculateAverageTemperature();
                std::cout << "Avgrage of Node " << temperatureServers[i].getSensorSerialNumber() << " = " << temperatureServers[i].getAverageTemperature() << std::endl;
            }
            cv.wait_for(lck, std::chrono::seconds(PERIODIC_TIME_TO_GET_SENSOR_AVERAGE));
        }
    });

    std::thread calculateAccumelatedTemperetureAvgThread([&]() {
        float accumulatedAverage = 0.0;
        std::unique_lock<std::mutex> lck(mtx);

        while (true) {
            accumulatedAverage = calculateAccumelatedAverages(temperatureServers);
            std::cout << "Accumulated Average of Nodes = " << accumulatedAverage << std::endl;
            cv.wait_for(lck, std::chrono::seconds(PERIODIC_TIME_TO_GET_SENSOR_ACCUMELATIVE_AVERAGE));
        }
    });

    while (true) {
        socketConnection->getPayloadFromNetwork();
        std::map<std::string, std::string> responsPayload = Data_Parser_And_Converter::parseDataThenConvertToMap(",", ":", socketConnection->getPayload());

        std::string payloadIdentifire = responsPayload[IDENTIFER];
        bool isNodeFound = false;
        int sizeOfNodes = temperatureServers.size();
        for (int i = 0; i < sizeOfNodes; i++) {
            if (temperatureServers[i].getSensorSerialNumber() == payloadIdentifire) {
                isNodeFound = true;
                temperatureServers[i].setSensorReading(atof(responsPayload[ATTRIBUTE].c_str()));
            }
        }

        if (!isNodeFound) {
            Temperature_Sensor newNode;
            newNode.setSensorSerialNumber(responsPayload[IDENTIFER]);
            newNode.setSensorReading(atof(responsPayload[ATTRIBUTE].c_str()));
            temperatureServers.push_back(newNode);
        }
    }

    nodeThread1.join();
    nodeThread2.join();
    calculateTemperetureAvgThread.join();
    calculateAccumelatedTemperetureAvgThread.join();

#endif // TEST_OR_BUILD

}

//application functions implementation
float calculateAccumelatedAverages(std::vector<Temperature_Sensor>& temperatureServers) {
    float totalSum = 0;
    int validNode = 0;
    for (auto item : temperatureServers) {
        if (comparTimestamp(item.getSensorLastReadingTimestamp())) {
            validNode++;
            totalSum += item.getAverageTemperature();
        }
    }
    float acc = totalSum / validNode;
    float accumulatedAverage = acc > 0.0 ? acc : 0.0;
    return accumulatedAverage;
}

bool comparTimestamp(tm timestamp) {
    time_t now = time(0);
    tm currentTimeStamp = *gmtime(&now);
    if (difftime(timegm(&currentTimeStamp), timegm(&timestamp)) > 10) 
        return false;
    return true;
}


