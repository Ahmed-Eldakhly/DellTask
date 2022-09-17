//haders
#include "Temperature_Sensor.h"
#include "Temperature_Sensor_Config.h"
#include <condition_variable>

/// <summary>
/// 
/// </summary>
Temperature_Sensor::Temperature_Sensor() {
    sensorType = "Temperature";  
}

/// <summary>
/// 
/// </summary>
/// <param name="min"></param>
/// <param name="max"></param>
/// <returns></returns>
float Temperature_Sensor::generateTemperature(int min, int max) {
    return (static_cast <float> (rand()) / RAND_MAX) * static_cast <float> (max - min) + min;
}

/// <summary>
/// 
/// </summary>
void Temperature_Sensor::generateTemperaturePeriodically() {

    float newTemperature;
    std::mutex mtx;
    std::unique_lock<std::mutex> uni_lck(mtx);
    std::condition_variable cv;

    while (true) {
        newTemperature = generateTemperature(MIN_TEMPERATURE_SENSOR, MAX_TEMPERATURE_SENSOR);
        setSensorReading(newTemperature);
        cv.wait_for(uni_lck, std::chrono::seconds(PERIODIC_TIME_STEP));
    }
}
