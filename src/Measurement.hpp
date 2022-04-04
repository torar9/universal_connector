#ifndef MEASUREMENT_HPP
#define MEASUREMENT_HPP

#include <string>
#include <sps30.h>
#include <ArduinoJson.h>

/** \file datastruct.hpp
 * Holds structure for measurement data
 */

/** \struct
 * This struct is used to hold measured data.
 */
typedef struct
{
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

class Measurement
{
private:
public:
  static void addDataToDocument(DynamicJsonDocument &doc, measurement_t &data);
};

#endif