//headers
#include "Application_Functions_Tests.h"
#include "../gtest/gtest.h"
#include "Temperature_Server.h"
#include <vector>
#include <ctime> 

//extern functions
extern float calculateTemperetureAccumelativeCoreLogic(std::vector<Temperature_Sensor> temperatureServers);
extern bool comparTimestamp(tm timestamp);

//class implementation
Application_Functions_Tests::Application_Functions_Tests() {
	RUN_ALL_TESTS();
}

//test cases
TEST(AccumelaredAverage, PositiveAccumelaredAvgTemperature) {
    std::vector<Temperature_Sensor> servers;
    Temperature_Sensor temperatureServer;
    for(int i = 1; i < 6; i++)
        temperatureServer.setSensorReading(i);
    temperatureServer.setSensorLastReadingTimestamp();
    temperatureServer.calculateAverageTemperature();
    servers.push_back(temperatureServer);

    ASSERT_EQ(3, calculateTemperetureAccumelativeCoreLogic(servers));
}

TEST(AccumelaredAverage, PositiveAccumelaredForTwoServers) {
    std::vector<Temperature_Sensor> servers;
    Temperature_Sensor temperatureServer;
    Temperature_Sensor temperatureServer2;
    for (int i = 1; i < 6; i++) {
        temperatureServer.setSensorReading(i);
        temperatureServer2.setSensorReading(i * 2);
    }  
    temperatureServer.setSensorLastReadingTimestamp();
    temperatureServer.calculateAverageTemperature();
    temperatureServer2.setSensorLastReadingTimestamp();
    temperatureServer2.calculateAverageTemperature();
    servers.push_back(temperatureServer);
    servers.push_back(temperatureServer2);

    ASSERT_DOUBLE_EQ(4.5, calculateTemperetureAccumelativeCoreLogic(servers));
}

TEST(AccumelaredAverage, PositiveAccumelaredNoServers) {
    std::vector<Temperature_Sensor> servers;
    EXPECT_DOUBLE_EQ(0.0, calculateTemperetureAccumelativeCoreLogic(servers));
}


TEST(TimestampTests, PositiveTimestamp) {
    Temperature_Sensor temperatureServer;
    temperatureServer.setSensorLastReadingTimestamp();
    ASSERT_TRUE(comparTimestamp(temperatureServer.getSensorLastReadingTimestamp()));
}

TEST(TimestampTests, NegatineTimestamp) {
    time_t now = time(0);
    tm* currentTimeStamp = localtime(&now);
    // go to last day
    --(currentTimeStamp->tm_mday); 
    // get last day time
    time_t lastDay = mktime(currentTimeStamp);
    tm* lastDayTimeStamp = localtime(&lastDay);
    ASSERT_FALSE(comparTimestamp(*lastDayTimeStamp));
}

