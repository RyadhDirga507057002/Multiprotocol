#include "MultiProtocol.h"

void MultiProtocol::init() {
    mqttHandler.init();
    serialHandler.init();
    if (ioHandler.begin()) {
        Serial.println("[MultiProtocol] IOHandler initialized successfully.");
    } else {
        Serial.println("[MultiProtocol] IOHandler initialization failed.");
    }
}

void MultiProtocol::run() {
    serialHandler.handle232();
    serialHandler.handle485();
    mqttHandler.handle();
}

void MultiProtocol::save() {
    // Implementasi penyimpanan konfigurasi jika diperlukan
}