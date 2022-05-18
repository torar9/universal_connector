#ifndef GENERICSENSOR_HPP
#define GENERICSENSOR_HPP

#include <ArduinoJson.h>
#include "config.hpp"

/**
 * @brief Generic sensor class
 * 
 */
class GenericSensor {
    public:
    /**
     * @brief measure and store measured data
     * 
     */
    virtual void measureAndStore() = 0;

    /**
     * @brief Save stored data into json document
     * 
     * @param document Json document into which data is stored
     */
    virtual void storeInto(DynamicJsonDocument& document) = 0;

    /**
     * @brief Save stored data into json array
     * 
     * @param arr Json array into which data is stored
     */
    virtual void storeInto(JsonArray& arr) = 0;
};

#endif