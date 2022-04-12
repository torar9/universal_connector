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

/**< Wi-Fi SSID. */
#define SSID "Damian"

/**< Wi-Fi password. */
#define WIFI_PASSWD "Ahoj123123"

/**< NTP server address. */
#define NTP_SERVER "0.cz.pool.ntp.org"

/**< MQTT client ID. */
#define MQTT_ID "esp32"

/**< MQTT client name. */
#define MQTT_NAME "esp32"

/**< MQTT server IP address. */
#define MQTT_SERVER "192.168.0.38"

/**< MQTT server port. */
#define MQTT_PORT 1883 

/**< Station hostname in local network. */
#define HOSTNAME "esp32"

/**< MQTT packet size in bytes. */
#define MQTT_PACKET_SIZE 512

/**< Topic name for logs. */
#define LOG_TOPIC "insys/log"

/**< Topic name for measured data. */
#define DATA_TOPIC "insys/data"

/**< Topic name for error reports. */
#define REPORT_TOPIC "insys/report"

/**< Quality of service (QoS) for MQTT publish communication. */
#define MQTT_PUB_QOS 1

/**< Quality of service (QoS) for MQTT subscribe communication. */
#define MQTT_SUB_QOS 1

/**< Connection timeout. */
#define MQTT_TIMEOUT 5000


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



/** @cond */
#if DEBUG
  #define DBG_SERIAL_BEGIN(x) Serial.begin(x);
  #define DBG_SERIAL_SETUP(x) Serial.begin(x);
  #define DBG_PRINTF(x, y) Serial.printf(x, y);
  #define DBG_PRINT(x) Serial.print(x)
  #define DBG_PRINTDEC(x) Serial.print(x, DEC)
  #define DBG_PRINTLN(x) Serial.println(x)
  #define DBG_FLUSH() Serial.flush();
#else
  #define DBG_SERIAL_BEGIN(x)
  #define DBG_SERIAL_SETUP(X)
  #define DBG_PRINTF(X, Y)
  #define DBG_PRINT(x)
  #define DBG_PRINTDEC(x)
  #define DBG_PRINTLN(x)
  #define DBG_FLUSH()
#endif
/** @endcond */

#endif