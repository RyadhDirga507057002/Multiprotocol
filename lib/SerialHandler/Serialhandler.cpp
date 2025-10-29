#include "SerialHandler.h"

void SerialHandler::init()
{
    preferences.begin("config", true);
    int baudRS232 = preferences.getString("rs232", "9600").toInt();
    int baudRS485 = preferences.getString("rs485", "9600").toInt();
    preferences.end();

    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);

    SerialRS232.begin(baudRS232);
    SerialRS485.begin(baudRS485);

    Serial.printf("[RS232 INIT] %d bps\n", baudRS232);
    Serial.printf("[RS485 INIT] %d bps\n", baudRS485);
}

void SerialHandler::handle232() {
  static String tempLine = "";
    while (SerialRS232.available())
    {
        char c = SerialRS232.read();

        if (c == '\r' || c == '\n')
        {
            if (tempLine.length() > 0)
            {
                bufferRS232 = tempLine;
                // Serial.println("[RS485 RECEIVED] " + bufferRS485);
                tempLine = "";
            }
        }
        else
        {
            tempLine += c;
            if (tempLine.length() > 512)
                tempLine = "";
        }
    }
}

String SerialHandler::getData232() { return bufferRS232; }

void SerialHandler::handle485()
{
    static String tempLine = "";
    while (SerialRS485.available())
    {
        char c = SerialRS485.read();

        if (c == '\r' || c == '\n')
        {
            if (tempLine.length() > 0)
            {
                bufferRS485 = tempLine;
                // Serial.println("[RS485 RECEIVED] " + bufferRS485);
                tempLine = "";
            }
        }
        else
        {
            tempLine += c;
            if (tempLine.length() > 512)
                tempLine = "";
        }
    }
}

String SerialHandler::getData485() { return bufferRS485; }
