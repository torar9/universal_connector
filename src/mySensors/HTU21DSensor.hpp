#ifndef HTU21DSENSOR_HPP
#define HTU21DSENSOR_HPP

#include <Adafruit_HTU21DF.h>
#include "sensor/GenericSensor.hpp"
#include "../config.hpp"

extern Adafruit_HTU21DF htu;

class HTU21DSensor: public GenericSensor
{
    private:
    DynamicJsonDocument* document;
    float temperature = NAN;
    float humidity = NAN;

    public:
    const char* SENSOR_NAME = "HTU21D";

    HTU21DSensor();

    float getTemperature();
    float getHumidity();

    const DynamicJsonDocument* getDocument();
    void measure();
};

#endif