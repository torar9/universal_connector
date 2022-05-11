#include "Communicator.hpp"
#include "config.hpp"

Communicator::Communicator(PubSubClient &client) : client(client)
{
}

void Communicator::callback(char *topic, byte *message, unsigned int length)
{
    DBG_PRINTLN("Callback function activated");

    if(strcmp(topic, MQTT_CONFIG_TOPIC.c_str()) == 0)
    {
        DynamicJsonDocument doc(JSON_DOC_SIZE_MEASUREMENTS);
        DBG_PRINTLN(MQTT_CONFIG_TOPIC);

        deserializeJson(doc, message, length);

        JsonObject obj = doc.as<JsonObject>();

        SSID = obj[F("ssid")].as<String>();
        WIFI_PASSWD = obj[F("passwd")].as<String>();
        MQTT_SERVER = obj[F("mqtt_server")].as<String>();
        MQTT_ID = obj[F("mqtt_id")].as<String>();;
        MQTT_DATA_TOPIC = obj[F("mqtt_topic")].as<String>();
    }
}

bool Communicator::uploadData(DynamicJsonDocument &doc, const char *topic)
{
    if (!doc.isNull())
    {
        char buffer[MQTT_PACKET_SIZE];
        size_t n = serializeJson(doc, buffer);

        client.publish(topic, buffer);
        return client.endPublish();
    }

    return false;
}