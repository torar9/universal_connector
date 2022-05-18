#ifndef HTU21DSENSOR_HPP
#define HTU21DSENSOR_HPP

#include <Adafruit_HTU21DF.h>
#include <Adafruit_HTU21DF.h>
#include "sensor/GenericSensor.hpp"

/**
 * @brief Analog sensor
 * 
 */
class AnalogSensor: public GenericSensor
{
    private:
    int pinNumber;
    int resolution = 4095;
    float analogValue = 0;

    public:
    const char* SENSOR_NAME = "Analog";

    AnalogSensor(int pinNumber);
    AnalogSensor(int pinNumber, int resolution);

    void measureAndStore();
    void storeInto(DynamicJsonDocument& document);
    void storeInto(JsonArray& arr);
};

#endif