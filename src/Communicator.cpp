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

        String ssid = obj[F("ssid")];
        SSID = ssid;
        String passwd = obj[F("passwd")];
        WIFI_PASSWD = passwd;
        String mqtt_server = obj[F("mqtt_server")];
        MQTT_SERVER = mqtt_server;
        String mqtt_id = obj[F("mqtt_id")];
        MQTT_ID = mqtt_id;
        String mqtt_topic = obj[F("mqtt_topic")];
        MQTT_DATA_TOPIC = mqtt_topic;
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