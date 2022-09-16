//haders
#include "Temperature_Sensor.h"
#include "Temperature_Sensor_Config.h"
#include <condition_variable>


Temperature_Sensor::Temperature_Sensor() {
    sensorType = "Temperature";  
}


float Temperature_Sensor::generateTemperature(int min, int max) {
    return (static_cast <float> (rand()) / RAND_MAX) * static_cast <float> (max - min) + min;
}

void Temperature_Sensor::generateTemperaturePeriodically() {
    
    std::condition_variable cv;

    float newTemperature;
    std::mutex mtx;
    std::unique_lock<std::mutex> uni_lck(mtx);

    while (true) {
        newTemperature = generateTemperature(MIN_TEMPERATURE_SENSOR, MAX_TEMPERATURE_SENSOR);
        setSensorReading(newTemperature);
        cv.wait_for(uni_lck, std::chrono::seconds(PERIODIC_TIME_STEP));
    }
}
