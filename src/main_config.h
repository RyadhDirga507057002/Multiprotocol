#ifndef MAIN_CONFIG_H
#define MAIN_CONFIG_H

#include <Arduino.h>

//-----------------Device Configuration-----------------//
#define DEVICE_NAME "MultiProtocolDevice"
#define FIRMWARE_VERSION "1.0.0"

//-----------------Network Configuration-----------------//
#define WIFI_SSID "MultiProtocol"
#define WIFI_PASSWORD "12345678"
#define SERIAL_BAUDRATE 115200

//-----------------MQTT Configuration-----------------//
#define MQTT_BROKER "mqtt.example.com"
#define MQTT_PORT 1883

//-----------------LoRa Configuration-----------------//
#define LORA_FREQUENCY 915E6
#define LORA_SS_PIN 18
#define LORA_RST_PIN 14
#define LORA_DIO0_PIN 26
#define LORA_BANDWIDTH 125E3
#define LORA_SPREADING_FACTOR 7
#define LORA_CODING_RATE 512

//-----------------I2C Configuration-----------------//
#define I2C_ADDRESS 0x20
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22

//-----------------Storage Configuration-----------------//
#define SD_CS_PIN 5 // Ganti sesuai wiring
#define LOG_FILE "datalog.txt"

//-----------------RS232/RS485 Configuration-----------------//
#define RXD2 26
#define TXD2 25
#define RXD1 14
#define TXD1 27

#endif