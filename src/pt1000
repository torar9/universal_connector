#include <Arduino.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MAX31865.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <Adafruit_HTU21DF.h>

#define RREF 4015.0
#define RNOMINAL 1000.0

Adafruit_HTU21DF htu = Adafruit_HTU21DF();
Adafruit_MAX31865 thermo = Adafruit_MAX31865(15);


#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme; // I2C

void setup()
{
  Serial.begin(9600);
  Serial.println("Serial start");
  delay(2000);

  if (!thermo.begin(MAX31865_3WIRE))
  {
    Serial.println("Unable to init MAX31865.");
  }

  if (!htu.begin())
  {
    Serial.println("Unable to init HTU21D.");
  }

  if (!bme.begin())
  {
    Serial.println("Unable to init BME680.");
  }

  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  thermo.setWires(MAX31865_3WIRE);
}

void loop()
{
  unsigned long endTime = bme.beginReading();
  if (endTime == 0) {
    Serial.println(F("Failed to begin reading :("));
    return;
  }
  Serial.print(F("Reading started at "));
  Serial.print(millis());
  Serial.print(F(" and will finish at "));
  Serial.println(endTime);

  delay(50); // This represents parallel work.
  // There's no need to delay() until millis() >= endTime: bme.endReading()
  // takes care of that. It's okay for parallel work to take longer than
  // BME680's measurement time.

  // Obtain measurement results from BME680. Note that this operation isn't
  // instantaneous even if milli() >= endTime due to I2C/SPI latency.
  if (!bme.endReading()) {
    Serial.println(F("Failed to complete reading :("));
    return;
  }

  uint16_t rtd = thermo.readRTD();

  Serial.print("RTD value: ");
  Serial.println(rtd);
  float ratio = rtd;
  ratio /= 32768;
  Serial.print("Ratio = ");
  Serial.println(ratio, 8);
  Serial.print("Resistance = ");
  Serial.println(RREF * ratio, 8);
  Serial.print("Temperature TP-1000= ");
  Serial.println(thermo.temperature(RNOMINAL, RREF));

  Serial.print("Temperature HTU21D= ");
  Serial.println(htu.readTemperature());

  Serial.print("Temperature BME680= ");
  Serial.println(bme.readTemperature());

  // Check and print any faults
  uint8_t fault = thermo.readFault();
  if (fault)
  {
    Serial.print("Fault 0x");
    Serial.println(fault, HEX);
    if (fault & MAX31865_FAULT_HIGHTHRESH)
    {
      Serial.println("RTD High Threshold");
    }
    if (fault & MAX31865_FAULT_LOWTHRESH)
    {
      Serial.println("RTD Low Threshold");
    }
    if (fault & MAX31865_FAULT_REFINLOW)
    {
      Serial.println("REFIN- > 0.85 x Bias");
    }
    if (fault & MAX31865_FAULT_REFINHIGH)
    {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open");
    }
    if (fault & MAX31865_FAULT_RTDINLOW)
    {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open");
    }
    if (fault & MAX31865_FAULT_OVUV)
    {
      Serial.println("Under/Over voltage");
    }
    thermo.clearFault();
  }

  Serial.println();
  Serial.flush();
  delay(1000);
}