#include "Measurement.hpp"

void Measurement::addDataToDocument(DynamicJsonDocument &doc, measurement_t &data)
{
    doc[F("altitude")] = data.altitude;
    doc[F("humidity")] = data.humidity;
    doc[F("pressure")] = data.pressure;
    doc[F("time")] = data.time;
    doc[F("gasResistance")] = data.gasResistance;
    doc[F("temperature")] = data.temperature;
    doc[F("batteryLevel")] = data.batteryLevel;
    doc[F("voltage")] = data.voltage;
    doc[F("mc10p0")] = data.spsData.mc_10p0;
    doc[F("mc1p0")] = data.spsData.mc_1p0;
    doc[F("mc2p5")] = data.spsData.mc_2p5;
    doc[F("mc4p0")] = data.spsData.mc_4p0;
    doc[F("nc0p5")] = data.spsData.nc_0p5;
    doc[F("nc10p0")] = data.spsData.nc_10p0;
    doc[F("nc1p0")] = data.spsData.nc_1p0;
    doc[F("nc2p5")] = data.spsData.nc_2p5;
    doc[F("nc4p0")] = data.spsData.nc_4p0;
    doc[F("typicalParticleSize")] = data.spsData.typical_particle_size;
}