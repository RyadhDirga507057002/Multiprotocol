#pragma once
#include <Arduino.h>
#include <MQTTHandler.h>
#include <SerialHandler.h>
#include <IOHandler.h>
#include <StorageModule.h>
#include <TimeModule.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "Preferences.h"

class MultiProtocol
{
public:
    void init();
    void run();
    void save();

private:
    Preferences preferences;
    StorageModule storage;
    TimeModule time;
    MQTTHandler mqtt;
    SerialHandler serial;
    SemaphoreHandle_t logMutex;
    IOHandler io{0x20, 21, 22}; // Contoh alamat I2C dan pin SDA/SCL
};