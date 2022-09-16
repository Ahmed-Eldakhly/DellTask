// gaurd to prevent including file many time.
#pragma once

// headers
#include "Sensor.h"

// class prototype
class Temperature_Sensor : public Sensor
{
    public:
        Temperature_Sensor();
        void generateTemperaturePeriodically();

    protected:

    private:
        float generateTemperature(int min, int max);
};

