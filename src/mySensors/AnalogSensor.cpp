#include "AnalogSensor.hpp"

AnalogSensor::AnalogSensor(int pinNumber): pinNumber(pinNumber)
{
}

AnalogSensor::AnalogSensor(int pinNumber, int resolution): pinNumber(pinNumber), resolution(resolution)
{
}


void AnalogSensor::storeInto(DynamicJsonDocument& document)
{
    document[F("sensor_name")] = SENSOR_NAME;
    document[F("analogValue")] = analogValue;
}

void AnalogSensor::storeInto(JsonArray& arr)
{
    JsonObject measurement = arr.createNestedObject();

    measurement[F("sensor_name")] = SENSOR_NAME;
    measurement[F("analogValue")] = analogValue;
}

void AnalogSensor::measureAndStore()
{
    this->analogValue = analogRead(this->pinNumber);
}