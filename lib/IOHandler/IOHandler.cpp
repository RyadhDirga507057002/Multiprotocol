#include "IOHandler.h"

IOHandler::IOHandler(uint8_t address, int sda, int scl)
    : _address(address), _sda(sda), _scl(scl), _outputState(0xFF), _ddr(0x00) {}

bool IOHandler::begin() {
    Wire.begin(_sda, _scl);

    // Tes tulis dan baca 0xFF
    if (!writeByte(0xFF)) return false;
    uint8_t val;
    if (!readByte(val)) return false;

    // Tes pola 0xAA
    if (!writeByte(0xAA)) return false;
    if (!readByte(val)) return false;
    if (val != 0xAA) {
        Serial.printf("[PCF8574] Test Error: Expected 0xAA, got 0x%02X\n", val);
        return false;
    }

    // Restore ke default HIGH semua
    writeByte(0xFF);

    Serial.println("[PCF8574] Test OK");
    return true;
}

void IOHandler::pinMode(uint8_t pin, uint8_t mode) {
    if (pin > 7) return;

    if (mode == OUTPUT) {
        _ddr |= (1 << pin);
        _outputState &= ~(1 << pin); // default LOW
    } else {
        _ddr &= ~(1 << pin);
        _outputState |= (1 << pin); // HIGH untuk input pull-up
    }
    writeByte(_outputState);
}

void IOHandler::digitalWrite(uint8_t pin, uint8_t value) {
    if (pin > 7) return;
    if (value == HIGH) {
        _outputState |= (1 << pin);
    } else {
        _outputState &= ~(1 << pin);
    }
    writeByte(_outputState);
}

int IOHandler::digitalRead(uint8_t pin) {
    if (pin > 7) return LOW;
    uint8_t val;
    if (!readByte(val)) return LOW;
    return (val & (1 << pin)) ? HIGH : LOW;
}

bool IOHandler::writeByte(uint8_t value) {
    Wire.beginTransmission(_address);
    Wire.write(value);
    return (Wire.endTransmission() == 0);
}

bool IOHandler::readByte(uint8_t &value) {
    if (Wire.requestFrom(_address, (uint8_t)1) != 1) return false;
    value = Wire.read();
    return true;
}
