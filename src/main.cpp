#include <Arduino.h>
#include "MultiProtocol.h"
#include <esp_task_wdt.h>

MultiProtocol multiProtocol;

void TaskRun(void *pvParameters)
{
  esp_task_wdt_add(NULL);
  while (1)
  {
    multiProtocol.run();
    esp_task_wdt_reset();            // Reset watchdog timer
    vTaskDelay(pdMS_TO_TICKS(1500)); // Delay 1 second
  }
}

void TaskSave(void *pvParameters)
{
  esp_task_wdt_add(NULL);
  while (1)
  {
    multiProtocol.save();
    esp_task_wdt_reset();            // Reset watchdog timer
    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay 1 second
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

