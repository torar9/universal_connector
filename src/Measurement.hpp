#ifndef MEASUREMENT_HPP
#define MEASUREMENT_HPP

/** @cond */
#include <string>
#include <sps30.h>
#include <ArduinoJson.h>

#include "config.hpp"
/** @endcond */

/** \file Measurement.hpp
 * Holds structure for measurement data
 */

/** \struct
 * This struct is used to hold measured data.
 */
typedef struct
{
  char* device_id;
  float humidity = NAN;       /**< Humidity level in % */
  char *time;                 /**< Time in "yyyy-MM-dd HH:mm:ss" format*/
  float batteryLevel = NAN;   /**< Battery level in % */
  float temperature = NAN;    /**< Temperature  in °C */
  float pressure = NAN;       /**< Pressure in hpa */
  float altitude = NAN;       /**< Altitude in meters */
  uint32_t gasResistance = 0; /**< Gas resistance */
  uint32_t voltage = 0;       /**< Voltage level in V */
  sps30_measurement spsData;
} measurement_t;

typedef enum
{
    PRESSURE = (1),
    TEMPERATURE = (2),
    VOLTAGE = (3)
} sensor_type_t;

class Measurement
{
private:
public:
  static void addDataToDocument(DynamicJsonDocument &doc, measurement_t &data);
};

#endif