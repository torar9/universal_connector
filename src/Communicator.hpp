#ifndef COMMUNICATOR_HPP
#define COMMUNICATOR_HPP

#include <MQTTClient.h>
#include <ArduinoJson.h>

#include "config.hpp"

class Communicator
{
private:
    MQTTClient &client;

public:
    Communicator(MQTTClient &client);
    /**
     * Callback function for MQTT client
     * @param toopic MQTT topic name
     * @param payload content
     */
    void callback(String &topic, String &payload);

    /**
     * Function for uploading measurment data to MQTT topic on server.
     * @param doc JSON document with data.
     * @param topic MQTT topic name.
     * @return Wherever or not upload was successful.
     */
    bool uploadData(DynamicJsonDocument &doc, char *topic);

    /**
     * Is used to print log output to serial communication.
     * If connection to server is available log is also sent to MQTT topic.
     * @param message Content of log
     * @param newLine Whetever or not print log to new line in serial communication DEFAULT VALUE = true.
     * @param topic MQTT topic name DEFAULT VALUE = LOG_TOPIC.
     */
    void log(const char *message, bool newLine = true, const char *topic = LOG_TOPIC);
};
#endif