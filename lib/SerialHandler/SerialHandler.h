#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Preferences.h>

class SerialHandler {
public:
    void init();
    void handle232();
    void handle485();
    String getData232();
    String getData485();

private:
    static const int RXD2 = 26; // RS232 RX
    static const int TXD2 = 25; // RS232 TX
    static const int RXD1 = 14; // RS485 RX
    static const int TXD1 = 27; // RS485 TX

    Preferences preferences;
    SoftwareSerial SerialRS232{RXD2, TXD2};  
    SoftwareSerial SerialRS485{RXD1, TXD1};  

    String bufferRS232;
    String bufferRS485;
};
