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
#define MAXIMUM_TIME_BEFORE_DROP_THE_SERVER                 10
#define timegm                                              _mkgmtime
#define TEST_OR_BUILD 0// 1 for Test - 0 for build

// structs and enums

// global variables
std::condition_variable cv;

// application function prototypes
void calculateTemperetureAvg(std::vector<Temperature_Sensor>& temperatureServers , std::mutex& mtx);
void calculateTemperetureAccumelativeAvgs(std::vector<Temperature_Sensor>& temperatureServers, std::mutex& mtx);
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
    // try to connect to servers inside new threads
    std::map<std::string, std::string> serverInfo1 = { {"serverChannel" , "broadcastingChannel"} , {"serverIp" , "127.0.0.1"} , {"serverPort" , "9000"} };
    std::thread serverThread1(&Socket_Communication::listenToSpecificServer, socketConnection, serverInfo1);
    std::map<std::string, std::string> serverInfo2 = { {"serverChannel" , "broadcastingChannel"} , {"serverIp" , "127.0.0.1"} , {"serverPort" , "9500"} };
    std::thread serverThread2(&Socket_Communication::listenToSpecificServer, socketConnection, serverInfo2);
    // calculate temperature average for  each server
    std::thread calculateTemperetureAvgThread(calculateTemperetureAvg, temperatureServers, mtx);
    // calculate avg of all avgs from all active servers
    std::thread calculateAccumelatedTemperetureAvgThread(calculateTemperetureAccumelativeAvgs, temperatureServers, mtx);
    // main logic to get all new readings from all servers
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

    serverThread1.join();
    serverThread2.join();
    calculateTemperetureAvgThread.join();
    calculateAccumelatedTemperetureAvgThread.join();

#endif // TEST_OR_BUILD

}

//application functions implementation
// calculate average for each server logic
void calculateTemperetureAvg(std::vector<Temperature_Sensor>& temperatureServers, std::mutex& mtx) {
    std::unique_lock<std::mutex> lck(mtx);
    while (true) {
        int sizeOfNodes = temperatureServers.size();
        for (int i = 0; i < sizeOfNodes; i++) {
            temperatureServers[i].calculateAverageTemperature();
            std::cout << "Avgrage of the temperature server: " << temperatureServers[i].getSensorSerialNumber() << " = " << temperatureServers[i].getAverageTemperature() << std::endl;
        }
        cv.wait_for(lck, std::chrono::seconds(PERIODIC_TIME_TO_GET_SENSOR_AVERAGE));
    }
}
// calculate average of all averages from all servers logic
void calculateTemperetureAccumelativeAvgs(std::vector<Temperature_Sensor>& temperatureServers, std::mutex& mtx) {
    float accumulatedAverage = 0.0;
    float totalSum;
    int validNode;
    std::unique_lock<std::mutex> lck(mtx);

    while (true) {
        totalSum = 0;
        validNode = 0;
        for (auto item : temperatureServers) {
            if (comparTimestamp(item.getSensorLastReadingTimestamp())) {
                validNode++;
                totalSum += item.getAverageTemperature();
            }
        }
        float accumulatedAverage = totalSum / validNode;
        std::cout << "Accumulated Average of temperature servers = " << accumulatedAverage << std::endl;
        cv.wait_for(lck, std::chrono::seconds(PERIODIC_TIME_TO_GET_SENSOR_ACCUMELATIVE_AVERAGE));
    }
}
// compare between two time stamps
bool comparTimestamp(tm timestamp) {
    time_t now = time(0);
    tm currentTimeStamp = *gmtime(&now);
    if (difftime(timegm(&currentTimeStamp), timegm(&timestamp)) > MAXIMUM_TIME_BEFORE_DROP_THE_SERVER)
        return false;
    return true;
}


