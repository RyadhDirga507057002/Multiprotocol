#include <Arduino.h>
#include "MultiProtocol.h"
#include <esp_task_wdt.h>

MultiProtocol multiProtocol;

void TaskRun(void *pvParameters) {
    esp_task_wdt_init(30, true); // Inisialisasi watchdog dengan timeout 30 detik
    multiProtocol.init();

    while (true) {
        esp_task_wdt_reset(); // Reset watchdog
        multiProtocol.run();
        vTaskDelay(10 / portTICK_PERIOD_MS); // Delay untuk menghindari penggunaan CPU 100%
    }
}

void TaskSave(void *pvParameters) {
    while (true) {
        vTaskDelay(60000 / portTICK_PERIOD_MS); // Simpan setiap 60 detik
        multiProtocol.save();
    }
}

void setup() {
    Serial.begin(115200);
    multiProtocol.init();
    esp_task_wdt_init(30, true); // Inisialisasi watchdog dengan timeout 30 detik   
    xTaskCreatePinnedToCore(TaskRun, "TaskRun", 8192, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(TaskSave, "TaskSave", 4096, NULL, 1, NULL, 1);

}

void loop() {
}

