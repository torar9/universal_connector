#include "HTU21DSensor.hpp"

HTU21DSensor::HTU21DSensor()
{
    document = new DynamicJsonDocument(JSON_DOC_SIZE_MEASUREMENTS);
}

float HTU21DSensor::getTemperature()
{
    return this->temperature;
}

float HTU21DSensor::getHumidity()
{
    return this->humidity;
}

const DynamicJsonDocument* HTU21DSensor::getDocument()
{
    return this->document;
}

void HTU21DSensor::measure()
{
    this->temperature = htu.readTemperature();
    this->humidity = htu.readHumidity();

    (*document)[F("sensor_name")] = this->SENSOR_NAME;
    (*document)[F("temperature")] = this->temperature;
    (*document)[F("humidity")] = this->humidity;
}