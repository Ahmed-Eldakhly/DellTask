//headers
#include "Temperature_Sensor_Tests.h"
#include "Temperature_Sensor.h"
#include "../gtest/gtest.h"

Temperature_Sensor_Tests::Temperature_Sensor_Tests() {
	RUN_ALL_TESTS();
}

TEST(GenerateTemperature, PositiveGenerateTemperature) {
    Temperature_Sensor temperatureSensor;
    float min = 10;
    float max = 40;
    float testedTemperature = temperatureSensor.generateTemperature(min, max);
    EXPECT_GE(testedTemperature, min);
    EXPECT_LE(testedTemperature, max);
}

TEST(GenerateTemperature, NegativeGenerateTemperature) {
    Temperature_Sensor temperatureSensor;
    float min = -40;
    float max = -10;
    float testedTemperature = temperatureSensor.generateTemperature(min, max);
    EXPECT_GE(testedTemperature, min);
    EXPECT_LE(testedTemperature, max);
}
