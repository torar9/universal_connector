#ifndef CONFIG_HPP
#define CONFIG_HPP

/** \file config.hpp
 * This file holds config values such as server ip, delay values, pin values etc.
 */

/** Turns on or off debug logs in serial communication. */
#define DEBUG 1

/** @cond */
/************************************************
 *       Network and server communication
 ***********************************************/
/** @endcond */

/**< MQTT packet size in bytes. */
#define MQTT_PACKET_SIZE 256

/**< Quality of service (QoS) for MQTT publish communication. */
#define MQTT_PUB_QOS 1

/**< Quality of service (QoS) for MQTT subscribe communication. */
#define MQTT_SUB_QOS 1

/**< Connection timeout. */
#define MQTT_TIMEOUT 5000

static const char *soft_ap_ssid = "ESP32-INSYS";
static const char *soft_ap_password = "Heslo123123";

/**< Wi-Fi SSID. */
static String SSID = "Damian";

/**< Wi-Fi password. */
static String WIFI_PASSWD = "Ahoj123123";

/**< NTP server address. */
static String NTP_SERVER = "0.cz.pool.ntp.org";

/**< MQTT client ID. */
static String MQTT_ID = "esp32";

/**< MQTT server IP address. */
static String MQTT_SERVER = "192.168.0.38";

/**< MQTT server port. */
static const int MQTT_PORT = 1883;

/**< Station hostname in local network. */
static String HOSTNAME = "esp32";

/**< Topic name for logs. */
static String MQTT_LOG_TOPIC = "insys/log";

/**< Topic name for measured data. */
static String MQTT_DATA_TOPIC = "insys/data";

/**< Topic name for config subscription. */
static String MQTT_CONFIG_TOPIC = "insys/config";


/** @cond */
/************************************************
 *           Sleep mode, timings etc.
 ***********************************************/
/** @endcond */

/**< Holds amount of uS in second. */
#define uS_TO_S_FACTOR (uint64_t)1000000

/**< Default amount of seconds for station to sleep. */
#define TIME_TO_SLEEP_(uint64_t)60


/** @cond */
/************************************************
 *     Module/sensor, and MCU configuration
 ***********************************************/
/** @endcond */

/**< Baud rate for serial communication. */
#define SERIAL_SPEED 115200

/**< JSON document buffer size in bytes for measured data. */
#define JSON_DOC_SIZE_MEASUREMENTS 512

/**< JSON document buffer size in bytes for error report. */
#define JSON_DOC_SIZE_STATUS 192

/**
 * Sea level of current location of station.
 * Is used to calibrate sensors.
 */
#define SEA_LEVEL_PRESSURE 1034

/**
 * GMT offset in seconds.
 * Is used to set time from NTP seWho Will Save Us Nowrver.
 */
#define GMT_OFFSET_SEC 3600

/**
 * UTC daylight offset.
 * Is used to set time from NTP server.
 */
#define DAYLIGHT_OFFSET_SEC 3600
/*
const char HTML[] = "<!DOCTYPE html>\
<html>\
<head>\
<title>ESP32 config page</title>\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
</head>\
<body>\
<h1>ESP32 config page - Access Point</h1>\
<form method=\"get\">\
<label>Json config</label>\
<hr>\
<textarea rows=\"10\" cols=\"50\" name=\"config\" form=\"configForm\">{&#10;\
\"ssid\": \"\",&#10;\
\"passwd\": \"\",&#10;\
\"mqtt_server\": \"\",&#10;\
\"mqtt_id\": \"\",&#10;\
\"mqtt_topic\": \"\"&#10;\
}</textarea>\
<hr>\
<input type=\"submit\">\
</form>\
</body>\
</html>";*/

const char HTML[] = "<h1>ESP32 config page - Access Point</h1>\
<form action='action' method=\"post\" name=\"configForm\" id=\"configForm\">\
<label>Json config</label>\
<hr>\
<textarea id=\"config\" rows=\"10\" cols=\"50\" name=\"config\" form=\"configForm\">{&#10;\
\"ssid\": \"\",&#10;\
\"passwd\": \"\",&#10;\
\"mqtt_server\": \"\",&#10;\
\"mqtt_id\": \"\",&#10;\
\"mqtt_topic\": \"\"&#10;\
}</textarea>\
<hr>\
<input type=\"submit\">\
</form>";



/** @cond */
#if DEBUG
  #define DBG_SERIAL_BEGIN(x) Serial.begin(x);
  #define DBG_SERIAL_SETUP(x) Serial.begin(x);
  #define DBG_PRINTF2(x, y) Serial.printf(x, y);
  #define DBG_PRINTF3(x, y, z) Serial.printf(x, y, z);
  #define DBG_PRINT(x) Serial.print(x)
  #define DBG_PRINTDEC(x) Serial.print(x, DEC)
  #define DBG_PRINTLN(x) Serial.println(x)
  #define DBG_FLUSH() Serial.flush();
#else
  #define DBG_SERIAL_BEGIN(x)
  #define DBG_SERIAL_SETUP(X)
  #define DBG_PRINTF2(X, Y)
  #define DBG_PRINTF3(x, y, z)
  #define DBG_PRINT(x)
  #define DBG_PRINTDEC(x)
  #define DBG_PRINTLN(x)
  #define DBG_FLUSH()
#endif
/** @endcond */

#endif