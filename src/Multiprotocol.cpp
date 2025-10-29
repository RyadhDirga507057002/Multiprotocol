#include "MultiProtocol.h"

void MultiProtocol::init() {
    io.begin();
    mqtt.init();
    serial.init();
    time.init();
    storage.init();
    logMutex = xSemaphoreCreateMutex();

    
}

void MultiProtocol::run() {
    
}

void MultiProtocol::save() {
    // Implementasi penyimpanan konfigurasi jika diperlukan
}