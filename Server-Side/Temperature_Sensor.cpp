//haders
#include "Temperature_Sensor.h"
#include <condition_variable>


Temperature_Sensor::Temperature_Sensor() {
    sensorType = "Temperature";  
}


float Temperature_Sensor::generateTemperature(int min, int max) {
    return (static_cast <float> (rand()) / RAND_MAX) * static_cast <float> (max - min) + min;
}

void Temperature_Sensor::generateTemperaturePeriodically() {
    
    std::condition_variable cv;

    float newTemp;
    std::mutex mtx;
    std::unique_lock<std::mutex> lck(mtx);

    while (true) {
        newTemp = generateTemperature(30, 40);
        setSensorReading(newTemp);
        cv.wait_for(lck, std::chrono::seconds(1));
    }
}
