#ifndef COMMUNICATOR_HPP
#define COMMUNICATOR_HPP

/** @cond */
#include <PubSubClient.h>
#include <ArduinoJson.h>
/** @endcond */

#include "config.hpp"

class Communicator
{
private:
    PubSubClient &client;

public:
    Communicator(PubSubClient &client);
    /**
     * Callback function for MQTT client
     * @param toopic MQTT topic name
     * @param payload content
     */
    void callback(char* topic, byte* message, unsigned int length);

    /**
     * Function for uploading measurment data to MQTT topic on server.
     * @param doc Address of JSON document with data.
     * @param topic MQTT topic name.
     * @return Wherever or not upload was successful.
     */
    bool uploadData(DynamicJsonDocument &doc, const char *topic);
};
#endif