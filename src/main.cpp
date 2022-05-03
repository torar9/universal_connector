
#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <Arduino.h>
#include <Wire.h>
#include <MQTT.h>
#include <WiFi.h>
#include <Adafruit_HTU21DF.h>
#include <Adafruit_MAX31865.h>
#include <Adafruit_Sensor.h>

#include "Communicator.hpp"
#include "Measurement.hpp"
#include "config.hpp"

MQTTClient mqttClient(MQTT_PACKET_SIZE);
Communicator comm(mqttClient);
WiFiClient wifiClient;
Adafruit_HTU21DF htu = Adafruit_HTU21DF();

void setupNetwok();

void messageReceived(String &topic, String &payload);

void setup()
{
#if DEBUG == 1
  Serial.begin(SERIAL_SPEED);
#endif

  if (!htu.begin())
  {
    DBG_PRINTLN(F("Unable to init HTU sensor"));
  }
  setupNetwok();
}

void loop()
{
  DynamicJsonDocument eventDoc(JSON_DOC_SIZE_MEASUREMENTS);
  measurement_t data;

  float temp = htu.readTemperature();
  float hum = htu.readHumidity();

  DBG_PRINT("Temperature: ");
  DBG_PRINTLN(temp);

  DBG_PRINT("Humidity: ");
  DBG_PRINTLN(hum);
  delay(2000);
}

void setupNetwok()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    DBG_PRINTLN(F("Connecting to WiFi..."));
    WiFi.mode(WIFI_MODE_STA);
    WiFi.setHostname(HOSTNAME);
    WiFi.setAutoReconnect(true);
    WiFi.begin(SSID, WIFI_PASSWD);
    WiFi.waitForConnectResult();

    if (WiFi.status() != WL_CONNECTED)
    {
      DBG_PRINTLN(F("Unable to connect to wifi"));
    }
    else
    {
      DBG_PRINTLN(F("Connected to WiFi."));
      DBG_PRINT(F("IPv4 address: "));
      DBG_PRINTLN(wifiClient.localIP());

      mqttClient.begin(MQTT_SERVER, MQTT_PORT, wifiClient);
      mqttClient.setTimeout(MQTT_TIMEOUT);
      mqttClient.onMessage(messageReceived);
      mqttClient.connect(MQTT_ID);
    }
  }
}

void messageReceived(String &topic, String &payload)
{
  Serial.println("incoming: " + topic + " - " + payload);
}