#pragma once
#include "Sensor.h"
class Temperature_Sensor : public Sensor
{
    public:
        Temperature_Sensor();
        void generateTemperaturePeriodically();

    protected:

    private:
        float generateTemperature(int min, int max);
};

