#include "HTU21DSensor.hpp"

void HTU21DSensor::storeInto(DynamicJsonDocument& document)
{
    document[F("sensor_name")] = SENSOR_NAME;
    document[F("temperature")] = temperature;
    document[F("humidity")] = humidity;
}

void HTU21DSensor::storeInto(JsonArray& arr)
{
    JsonObject measurement = arr.createNestedObject();
    
    measurement[F("sensor_name")] = SENSOR_NAME;
    measurement[F("temperature")] = temperature;
    measurement[F("humidity")] = humidity;
}

void HTU21DSensor::measureAndStore()
{
    this->temperature = this->readTemperature();
    this->humidity = this->readHumidity();
}