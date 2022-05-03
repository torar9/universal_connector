#ifndef GENERICSENSOR_HPP
#define GENERICSENSOR_HPP

#include <ArduinoJson.h>
#include "config.hpp"

class GenericSensor {
    public:
    const char* SENSOR_NAME;
    virtual const DynamicJsonDocument* getDocument() = 0;
    virtual void measure() = 0;
};

#endif