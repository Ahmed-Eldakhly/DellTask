// gaurd to prevent including file many time.
#pragma once

// headers
#include <string>
#include <iostream>

// class prototype
class Sensor
{
	public:
		Sensor();
		void setSensorName(std::string sensorName);
		std::string getSensorName();
		void setSensorSerialNumber(std::string sensorType);
		std::string getSensorSerialNumber();
		void setSensorReading(float sensorReading);
		float getSensorReading();

	protected:

	private:
		std::string sensorName;
		std::string sensorSerialNumber;
		std::string sensorType;
		float sensorReading;
};

