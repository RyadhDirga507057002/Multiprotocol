#include "MultiProtocol.h"

void MultiProtocol::init()
{
    io.begin();
    mqtt.init();
    serial.init();
    time.init();
    storage.init();
    logMutex = xSemaphoreCreateMutex();
}

void MultiProtocol::run()
{
    if (mqtt.isConnected() && (xSemaphoreTake(logMutex, portMAX_DELAY)))
    {
        String data = storage.readFile("log.txt", 1);
        String topic = "MultiProtocol/";
        mqtt.publish(topic.c_str(), data.c_str());
    }
    else
    {
        // LoRa
    }
}

void MultiProtocol::save()
{
    serial.handle232();
    serial.handle485();
    time.update();

    String new232 = serial.getData232();
    if (new232.length() > 0)
    {
        last232Data = new232;
    }

    String new485 = serial.getData485();
    if (new485.length() > 0)
    {
        last485Data = new485;
    }

    String logEntry = time.getFormattedTime() + ",RS232:" + last232Data + ",RS485:" + last485Data + "\n";

    if (new232.length() > 0 || new485.length() > 0 && xSemaphoreTake(logMutex, portMAX_DELAY))
    {
        storage.logData(logEntry);
        xSemaphoreGive(logMutex);
    }
}