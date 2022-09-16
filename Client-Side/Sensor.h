// gaurd to prevent including file many time.
#pragma once

// headers
#include <string>
#include <iostream>
#include <ctime>

// class prototype
class Sensor
{
	public:
		Sensor();
		void setSensorName(std::string sensorName);
		std::string getSensorName();
		void setSensorSerialNumber(std::string sensorType);
		std::string getSensorSerialNumber();
		virtual void setSensorReading(float sensorReading);
		float getSensorReading();
		void setSensorLastReadingTimestamp();
		tm getSensorLastReadingTimestamp();

	protected:
		std::string sensorName;
		std::string sensorSerialNumber;
		std::string sensorType;
		float sensorReading;
		tm lastReadingTimeStamp;
	private:

};

