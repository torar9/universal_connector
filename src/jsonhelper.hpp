#ifndef JSONHELPER_HPP
#define JSONHELPER_HPP

/** @cond */
#include <ArduinoJson.h>
/** @endcond */
#include "Status.hpp"
#include "Measurement.hpp"

/** \file jsonhelper.hpp
 * Contains functions for working with JSON document
 */

/**
 * Append measurements to JSON document
 * @param doc JSON document with data
 * @param event struct with measurement data
 */
void addEventToJSON(DynamicJsonDocument &doc, measurement_t &event);

/**
 * Append status to JSON document
 * @param doc JSON document with data
 * @param status struct with status data
 */
void addEventToJSON(DynamicJsonDocument &doc, status_t &status);

#endif