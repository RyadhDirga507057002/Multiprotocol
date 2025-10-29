#pragma once
#include "MQTTHandler.h"
#include "SerialHandler.h"
#include "IOHandler.h"

class MultiProtocol {
public:
    void init();
    void run();
    void save();
    
private:
    MQTTHandler mqttHandler;
    SerialHandler serialHandler;
    IOHandler ioHandler{0x20, 21, 22}; // Contoh alamat I2C dan pin SDA/SCL
};