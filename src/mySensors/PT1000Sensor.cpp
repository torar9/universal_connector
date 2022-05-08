#include "PT1000Sensor.hpp"

PT1000Sensor::PT1000Sensor(float nominal, float reference, int8_t spi_cs, 
int8_t spi_mosi, int8_t spi_miso, int8_t spi_clk): nominal(nominal), reference(reference), Adafruit_MAX31865(spi_cs, spi_mosi, spi_miso, spi_clk)
{

}
PT1000Sensor::PT1000Sensor(float nominal, float reference, int8_t spi_cs): nominal(nominal), reference(reference), Adafruit_MAX31865(spi_cs)
{
}

float PT1000Sensor::getTemperature()
{
    return this->temp;
}

float PT1000Sensor::getHumidity()
{
    return this->humidity;
}

void PT1000Sensor::storeInto(DynamicJsonDocument& document)
{
    document[F("sensor_name")] = SENSOR_NAME;
    document[F("temperature")] = temp;
}

void PT1000Sensor::storeInto(JsonArray& arr)
{
    JsonObject measurement = arr.createNestedObject();

    measurement[F("sensor_name")] = SENSOR_NAME;
    measurement[F("temperature")] = temp;
}

void PT1000Sensor::measureAndStore()
{
    this->temp = this->temperature(nominal, reference);
}