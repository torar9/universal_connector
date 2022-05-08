#ifndef GENERICSENSOR_HPP
#define GENERICSENSOR_HPP

#include <ArduinoJson.h>
#include "config.hpp"

class GenericSensor {
    public:
    virtual void measureAndStore() = 0;
    virtual void storeInto(DynamicJsonDocument& document) = 0;
    virtual void storeInto(JsonArray& arr) = 0;
};

#endif