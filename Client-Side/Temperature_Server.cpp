//haders
#include "Temperature_Server.h"
#include "limits.h"
#include <cstdlib>
#include <iostream>


Temperature_Sensor::Temperature_Sensor() : temperatureDegreeArray{ 0 }{
    sensorType = "Temperature"; 
    currentReadingIndex = 0;
    temperatureDegree = 0.0;
    averageTemperature = 0.0;
}


void Temperature_Sensor::setSensorReading(float temperatureDegree) {
    this->temperatureDegree = temperatureDegree;
    setSensorLastReadingTimestamp();
    updateTemperatureArray();
}


void Temperature_Sensor::updateTemperatureArray() {
    if (currentReadingIndex == READING_ELEMENTS_NUMBER)
        currentReadingIndex = 0;
    temperatureDegreeArray[currentReadingIndex++] = temperatureDegree;
}

float Temperature_Sensor::getAverageTemperature() {
    return averageTemperature;
}

void Temperature_Sensor::calculateAverageTemperature() {
    float totalSum = 0;
    for (float item : temperatureDegreeArray)
        totalSum += item;

    averageTemperature = totalSum / READING_ELEMENTS_NUMBER;
}
