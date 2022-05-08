#ifndef HTU21DSENSOR_HPP
#define HTU21DSENSOR_HPP

#include <Adafruit_HTU21DF.h>
#include <Adafruit_HTU21DF.h>
#include "sensor/GenericSensor.hpp"

class HTU21DSensor: public GenericSensor, public Adafruit_HTU21DF
{
    private:
    float temperature = NAN;
    float humidity = NAN;

    public:
    const char* SENSOR_NAME = "HTU21D";

    void measureAndStore();
    void storeInto(DynamicJsonDocument& document);
    void storeInto(JsonArray& arr);
};

#endif