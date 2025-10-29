#pragma once
#include <Arduino.h>
#include <Wire.h>

class IOHandler {
public:
    IOHandler(uint8_t address, int sda, int scl);

    bool begin();
    void pinMode(uint8_t pin, uint8_t mode);
    void digitalWrite(uint8_t pin, uint8_t value);
    int  digitalRead(uint8_t pin);

private:
    uint8_t _address;
    int _sda, _scl;
    uint8_t _outputState; // simpan state output saat ini
    uint8_t _ddr;         // 1=output, 0=input

    bool writeByte(uint8_t value);
    bool readByte(uint8_t &value);
};