//headers
#include "Temperature_Server_Tests.h"
#include "Temperature_Server.h"
#include "../gtest/gtest.h"

/// <summary>
/// 
/// </summary>
Temperature_Server_Tests::Temperature_Server_Tests() {
	RUN_ALL_TESTS();
}

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST(AverageTemprature, PositiveAvaregeTemperatureFloat) {
    Temperature_Sensor temperatureserver;
    temperatureserver.setSensorReading(1);
    temperatureserver.setSensorReading(2);
    temperatureserver.setSensorReading(3);
    temperatureserver.setSensorReading(3);
    temperatureserver.setSensorReading(2);
    temperatureserver.calculateAverageTemperature();
    ASSERT_DOUBLE_EQ(11/5, temperatureserver.getAverageTemperature());
}

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST(AverageTemprature, PositiveAvaregeTemperatureInt) {
    Temperature_Sensor temperatureserver;
    temperatureserver.setSensorReading(1);
    temperatureserver.setSensorReading(2);
    temperatureserver.setSensorReading(3);
    temperatureserver.setSensorReading(4);
    temperatureserver.setSensorReading(5);
    temperatureserver.calculateAverageTemperature();
    ASSERT_DOUBLE_EQ(3, temperatureserver.getAverageTemperature());
}
