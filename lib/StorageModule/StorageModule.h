#pragma once
#include <Arduino.h>

class StorageModule {
public:
  void init();
  void manage();
  void logData(const String& data);
  String readFile(const char* filename,int lineCount);
private:
  void checkCard();
  bool cardOK = false;

  #define SD_CS_PIN 5  // Ganti sesuai wiring
};
