#include "MQTTHandler.h"

void MQTTHandler::init()
{
    preferences.begin("config", true);
    ssid = preferences.getString("ssid", "");
    password = preferences.getString("password", "");
    broker = preferences.getString("broker", "broker.hivemq.com");
    port = preferences.getString("port", "1883").toInt();
    espId = preferences.getString("espId", "esp32");
    preferences.end();

    Serial.println("[MQTT INIT] SSID: " + ssid + ", Broker: " + broker + ":" + String(port) + ", ESP ID: " + espId);

    connectWiFi();

    client.setClient(wifiClient);
    client.setServer(broker.c_str(), port);
}

void MQTTHandler::connectWiFi()
{
    if (ssid == "")
    {
        Serial.println("[WiFi] SSID Error");
        return;
    }

    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.print("[WiFi] Connecting");

    for (int i = 0; i < 10; i++)
    {
        if (WiFi.status() == WL_CONNECTED)
            break;
        Serial.print(".");
        vTaskDelay(1000);
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("[WiFi] Connected. IP: " + WiFi.localIP().toString());
    }
    else
    {
        Serial.println("[WiFi] Failed to connect.");
    }
}

void MQTTHandler::handle()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}

bool MQTTHandler::isConnected()
{
    return client.connected();
}

void MQTTHandler::publish(const char *topic, const char *payload)
{
    if (client.connected())
    {
        client.publish(topic, payload);
    }
}

void MQTTHandler::reconnect()
{
    if (millis() - lastMqttRetry < mqttRetryInterval)
        return;

    Serial.println("[MQTT] Attempting connection to broker...");

    if (client.connect(espId.c_str()))
    {
        Serial.println("[MQTT] Connected");
        mqttFailed = false;
    }
    else
    {
        Serial.println("[MQTT] Failed. Code: " + String(client.state()));
        mqttFailed = true;
        lastMqttRetry = millis();
    }
}
