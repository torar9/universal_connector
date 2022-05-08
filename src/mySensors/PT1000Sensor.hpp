#ifndef PT1000Sensor_HPP
#define PT1000Sensor_HPP

#include <Adafruit_MAX31865.h>
#include "sensor/GenericSensor.hpp"
#include "../config.hpp"

class PT1000Sensor: public GenericSensor, public Adafruit_MAX31865
{
    private:
    float temp = NAN;
    float humidity = NAN;
    float nominal = 1000.0;
    float reference = 4200;
 
    public:

    PT1000Sensor(float nominal, float reference, int8_t spi_cs, int8_t spi_mosi, int8_t spi_miso, int8_t spi_clk);
    PT1000Sensor(float nominal, float reference, int8_t spi_cs);

    const char* SENSOR_NAME = "PT1000";

    float getTemperature();
    float getHumidity();
    void storeInto(DynamicJsonDocument& document);
    void storeInto(JsonArray& arr);

    void measureAndStore();
};

#endif