// headers
#include "Sensor.h"
/// <summary>
/// 
/// </summary>
Sensor::Sensor() {

}

/// <summary>
/// 
/// </summary>
/// <param name="sensorName"></param>
void Sensor::setSensorName(std::string sensorName) {
	this->sensorName = sensorName;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::string Sensor::getSensorName() {
	return this->sensorName;
}

/// <summary>
/// 
/// </summary>
/// <param name="sensorSerialNumber"></param>
void Sensor::setSensorSerialNumber(std::string sensorSerialNumber) {
	this->sensorSerialNumber = sensorSerialNumber;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::string Sensor::getSensorSerialNumber() {
	return this->sensorSerialNumber;
}

/// <summary>
/// 
/// </summary>
/// <param name="sensorReading"></param>
void Sensor::setSensorReading(float sensorReading) {
	this->sensorReading = sensorReading;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float Sensor::getSensorReading() {
	return this->sensorReading;
}
