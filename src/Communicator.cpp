#include "Communicator.hpp"

Communicator::Communicator(MQTTClient &client) : client(client)
{
}

void Communicator::callback(String &topic, String &payload)
{
    log("Callback function activated");
}

bool Communicator::uploadData(DynamicJsonDocument &doc, char *topic)
{
    if (!doc.isNull())
    {
        String output;
        char buffer[MQTT_PACKET_SIZE];
        size_t n = serializeJson(doc, buffer);

        return client.publish(topic, buffer, n, MQTT_PUB_QOS);
    }

    return false;
}

void Communicator::log(const char *message, bool newLine, const char *topic)
{
#if DEBUG
    if (client.connected())
    {
        if (!client.publish(topic, message, (unsigned)strlen(message), MQTT_PUB_QOS))
            DBG_PRINTLN("Failed to send log message...");
    }

    (newLine) ? DBG_PRINTLN(message) : DBG_PRINT(message);
#endif
}