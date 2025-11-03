#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Preferences.h>
#include "main_config.h"

class SerialHandler {
public:
    void init();
    void handle232();
    void handle485();
    String getData232();
    String getData485();

private:
    Preferences preferences;
    SoftwareSerial SerialRS232{RXD2, TXD2};  
    SoftwareSerial SerialRS485{RXD1, TXD1};  

    String bufferRS232;
    String bufferRS485;
};
