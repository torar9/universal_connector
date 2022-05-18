#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <WiFiClient.h>
#include <AsyncTCP.h>
#include <PubSubClient.h>
#include <Adafruit_MAX31865.h>
#include <ESPAsyncWebServer.h>

#include "Communicator.hpp"
#include "mySensors/HTU21DSensor.hpp"
#include "mySensors/PT1000Sensor.hpp"
#include "config.hpp"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
Communicator comm(mqttClient);
AsyncWebServer server(80);

// My sensors
HTU21DSensor htu21d;
PT1000Sensor pt1000(1000.0, 4015, 15);

TaskHandle_t loopTask;

bool isReady = false;

/**
 * @brief Configure network - conect to Wi-Fi as a client
 *
 */

void setupNetwok();
/**
 * @brief create Access point
 *
 */

void setupAP();
/**
 * @brief Callback function for MQTT
 *
 * @param topic MQTT topic which is sending data
 * @param message Byte array containing data
 * @param length Amount of bytes in message
 */
void callback(char *topic, byte *message, unsigned int length);

/**
 * @brief Handler function for MQTT loop() funtion
 *
 * @param parameter
 */
void loopHandler(void *parameter);

/**
 * @brief Web callback function for error 404
 *
 * @param request
 */
void notFound(AsyncWebServerRequest *request);

/**
 * @brief Web callback function for root webpage '/'
 *
 * @param request
 */
void onRoot(AsyncWebServerRequest *request);

/**
 * @brief Web callback function for handling form action
 *
 * @param request
 */
void onAction(AsyncWebServerRequest *request);

void setup()
{
#if DEBUG == 1
  DBG_SERIAL_BEGIN(SERIAL_SPEED);
  delay(2000);
#endif

  if (!htu21d.begin())
  {
    DBG_PRINTLN(F("Unable to init HTU sensor"));
  }

  if (!pt1000.begin(MAX31865_3WIRE))
  {
    DBG_PRINTLN("Unable to init MAX31865.");
  }
  // server.on("/", handle_root);

  setupAP();

  server.on("/", HTTP_GET, onRoot);
  server.on("/action", HTTP_POST, onAction);
  server.onNotFound(notFound);
  server.begin();

  DBG_PRINTLN("HTTP server started");

  xTaskCreatePinnedToCore(
      loopHandler, /* Function to implement the task */
      "web_task",  /* Name of the Wtask */
      10000,       /* Stack size in words */
      NULL,        /* Task input parameter */
      0,           /* Priority of the task */
      &loopTask,   /* Task handle. */
      0);          /* Core where the task should run */

  isReady = true;
  while (!isReady)
  {
    delay(1);
  }

  setupNetwok();
}

void loop()
{
  DynamicJsonDocument eventDoc(JSON_DOC_SIZE_MEASUREMENTS);
  JsonArray measurements = eventDoc.createNestedArray(F("measurements"));

  eventDoc["device_id"] = MQTT_ID;
  
  htu21d.measureAndStore();
  pt1000.measureAndStore();

  htu21d.storeInto(measurements);
  pt1000.storeInto(measurements);

  comm.uploadData(eventDoc, MQTT_DATA_TOPIC.c_str());

  delay(10000);
}

void setupNetwok()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    DBG_PRINTLN(F("Connecting to WiFi..."));
    WiFi.mode(WIFI_MODE_APSTA);
    WiFi.setHostname(HOSTNAME.c_str());
    WiFi.setAutoReconnect(true);
    WiFi.begin(SSID.c_str(), WIFI_PASSWD.c_str());
    WiFi.waitForConnectResult();

    if (WiFi.status() != WL_CONNECTED)
    {
      DBG_PRINTLN(F("Unable to connect to wifi"));
    }
    else
    {
      DBG_PRINTLN(F("Connected to WiFi."));
      DBG_PRINT(F("IPv4 address: "));
      DBG_PRINTLN(WiFi.localIP());

      if (WiFi.status() == WL_CONNECTED)
      {
        struct tm timeStr;

        configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER.c_str());
        getLocalTime(&timeStr);
      }

      mqttClient.setServer(MQTT_SERVER.c_str(), MQTT_PORT);
      mqttClient.setKeepAlive(60);
      mqttClient.setBufferSize(MQTT_PACKET_SIZE);
      mqttClient.setCallback(callback);
      mqttClient.connect(MQTT_ID.c_str());

      if (mqttClient.connected())
      {
        DBG_PRINTLN("MQTT client connected");
      }

      if (!mqttClient.subscribe(MQTT_CONFIG_TOPIC.c_str(), MQTT_SUB_QOS))
      {
        DBG_PRINTLN("Faield to subscripted to config topic");
      }
    }
  }
}

void setupAP()
{
  WiFi.mode(WIFI_MODE_AP);
  WiFi.setHostname(HOSTNAME.c_str());
  WiFi.softAP(soft_ap_ssid, soft_ap_password);
  DBG_PRINTLN(WiFi.softAPIP());
}

void callback(char *topic, byte *message, unsigned int length)
{
  comm.callback(topic, message, length);
}

void loopHandler(void *parameter)
{
  DBG_PRINTLN("Web task handler");
  while (true)
  {
    if (!isReady)
    {
      mqttClient.loop();
    }
  }
}

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

void onRoot(AsyncWebServerRequest *request)
{
  DBG_PRINTLN("on root");

  request->send(200, "text/html", HTML);
}

void onAction(AsyncWebServerRequest *request)
{
  if (!isReady)
  {
    DBG_PRINTLN("on action");

    int params = request->params();
    DBG_PRINTLN(params);

    DynamicJsonDocument document(JSON_DOC_SIZE_MEASUREMENTS);
    AsyncWebParameter *p = request->getParam(0);

    DBG_PRINTF3("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());

    deserializeJson(document, p->value());
    SSID = document[F("ssid")].as<String>();
    WIFI_PASSWD = document[F("passwd")].as<String>();
    MQTT_SERVER = document[F("mqtt_server")].as<String>();
    MQTT_ID = document[F("mqtt_id")].as<String>();
    MQTT_DATA_TOPIC = document[F("mqtt_topic")].as<String>();
    isReady = true;
  }

  request->send(200, "text/html", "Config succesfully set up.");
}