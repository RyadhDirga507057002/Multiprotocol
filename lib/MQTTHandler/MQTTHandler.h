#pragma once
#include <WiFi.h>
#include <PubSubClient.h>
#include <Preferences.h>

class MQTTHandler
{
public:
    void init();
    void handle();
    bool isConnected();
    void publish(const char *topic, const char *payload);

private:
    void connectWiFi();
    void reconnect();

    WiFiClient wifiClient;
    PubSubClient client;
    Preferences preferences;

    String ssid;
    String password;
    String broker;
    int port;
    String espId;

    bool mqttFailed = false;
    unsigned long lastMqttRetry = 0;
    const unsigned long mqttRetryInterval = 60000;
};
