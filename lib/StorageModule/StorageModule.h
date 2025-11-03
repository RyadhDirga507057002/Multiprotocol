#pragma once
#include <Arduino.h>
#include <SD.h>
#include "main_config.h"

class StorageModule {
public:
  void init();
  void manage();
  void logData(const String& data);
  String readFile(const char* filename,int lineCount);
private:
  void checkCard();
  bool cardOK = false;

};
