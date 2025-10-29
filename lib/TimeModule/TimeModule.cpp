#include "TimeModule.h"
#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void TimeModule::init()
{
  Wire.begin();
  vTaskDelay(1);
  if (!rtc.begin())
  {
    Serial.println("[RTC] Couldn't find");
    while (1)
      ;
  }
    Serial.println("[RTC] Found!");
    update();
    Serial.println("[RTC] Current time: " + getFormattedTime());

  if (rtc.lostPower())
  {
    Serial.println("[RTC] lost power, setting time!");
    preferences.begin("config", true);

    String dateStr = preferences.getString("date", ""); // format: YYYY-MM-DD
    String timeStr = preferences.getString("time", ""); // format: HH:MM

    // Parsing tanggal
    int year = dateStr.substring(0, 4).toInt();  // "2025"
    int month = dateStr.substring(5, 7).toInt(); // "07"
    int day = dateStr.substring(8, 10).toInt();  // "02"

    // Parsing waktu
    int hour = timeStr.substring(0, 2).toInt();   // "12"
    int minute = timeStr.substring(3, 5).toInt(); // "10"

    Serial.println("[RTC] Setting to: " + dateStr + " " + timeStr);

    // Atur waktu ke RTC
    rtc.adjust(DateTime(year, month, day, hour, minute, 0));

    preferences.end();

    // syncTimeFromRTC();
    Serial.println("[RTC] initialized and time synced.");

    // rtc.adjust(DateTime(2023, 10, 1, 0, 0, 0)); // Set to current date and time
  }
}

void TimeModule::syncTimeFromRTC()
{
  DateTime now = rtc.now();
  struct tm timeinfo;
  timeinfo.tm_year = now.year() - 1900;
  timeinfo.tm_mon = now.month() - 1;
  timeinfo.tm_mday = now.day();
  timeinfo.tm_hour = now.hour();
  timeinfo.tm_min = now.minute();
  timeinfo.tm_sec = now.second();
  time_t t = mktime(&timeinfo);
  struct timeval tv = {.tv_sec = t};
  settimeofday(&tv, nullptr);
}

void TimeModule::update()
{
  syncTimeFromRTC();
}

String TimeModule::getFormattedTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
    return "00-00-0000 00:00:00";
  char buffer[32];
  strftime(buffer, sizeof(buffer), "%H:%M:%S %Y-%m-%d", &timeinfo);

  return String(buffer);
}

time_t TimeModule::getUnixTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    return 0; // Gagal mendapatkan waktu, return 0 sebagai default
  }
  return mktime(&timeinfo);
}

String TimeModule::getUnixTimeString()
{
  return String(getUnixTime());
}