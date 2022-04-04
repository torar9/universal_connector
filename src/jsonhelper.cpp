#include "jsonhelper.hpp"

void addEventToJSON(DynamicJsonDocument &doc, measurement_t &event)
{
    doc[F("altitude")] = event.altitude;
    doc[F("humidity")] = event.humidity;
    doc[F("pressure")] = event.pressure;
    doc[F("time")] = event.time;
    doc[F("gasResistance")] = event.gasResistance;
    doc[F("temperature")] = event.temperature;
    doc[F("batteryLevel")] = event.batteryLevel;
}

void addEventToJSON(DynamicJsonDocument &doc, status_t &status)
{
    doc[F("cardAvailable")] = status.cardAvailable;
    doc[F("bmeAvailable")] = status.bmeAvailable;
    doc[F("rtcAvailable")] = status.rtcAvailable;
    doc[F("spsAvailable")] = status.spsAvailable;
    doc[F("problemOccured")] = status.problemOccured;
}