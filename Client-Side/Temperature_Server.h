// gaurd to prevent including file many time.
#pragma once

// headers
#include "Sensor.h"
#include "Temperature_Server_Config.h"

// class prototype
class Temperature_Sensor : public Sensor
{
public:
    Temperature_Sensor();
    void calculateAverageTemperature();
    void setSensorReading(float temperatureDegree);
    float getAverageTemperature();
    void updateTemperatureArray();

protected:

private:
    float temperatureDegree;
    float temperatureDegreeArray[READING_ELEMENTS_NUMBER];
    int currentReadingIndex;
    float averageTemperature;
};