#pragma once
#include <Arduino.h>
#include <Preferences.h>

class TimeModule
{
public:
  void init();
  void update();
  String getFormattedTime();
  String getUnixTimeString();
  time_t getUnixTime();

private:
  void syncTimeFromRTC();
  Preferences preferences;
};
