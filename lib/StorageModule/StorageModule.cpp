#include "StorageModule.h"
#include <SD.h>

File logFile;

void StorageModule::init()
{
  if (!SD.begin(SD_CS_PIN))
  {
    Serial.println("[SD] SD init failed!");
    cardOK = false;
    return;
  }
  cardOK = true;
  Serial.println("[SD] card initialized.");
}

void StorageModule::logData(const String &data)
{
  if (!cardOK)
    return;
  logFile = SD.open("/log.txt", FILE_APPEND);
  if (logFile)
  {
    logFile.println(data);
    logFile.close();
  }
  else
  {
    Serial.println("[SD] Failed to open log.txt");
  }
}

String StorageModule::readFile(const char *filename, int lineCount)
{
  File file = SD.open(filename, FILE_READ);
  if (!file)
  {
    return String("Gagal membuka file: ") + filename;
  }

  String result = "";
  String remaining = "";
  String lineBuffer = "";
  int currentLine = 0;

  while (file.available())
  {
    char c = file.read();

    if (c == '\n' || c == '\r')
    {
      if (lineBuffer.length() > 0)
      {
        if (currentLine < lineCount)
        {
          result += lineBuffer + '\n';
        }
        else
        {
          remaining += lineBuffer + '\n';
        }
        lineBuffer = "";
        currentLine++;
      }

      // Jika \r diikuti \n, skip \n
      if (c == '\r' && file.peek() == '\n')
      {
        file.read();
      }
    }
    else
    {
      lineBuffer += c;
    }
  }

  // Tangani baris terakhir jika tidak diakhiri newline
  if (lineBuffer.length() > 0)
  {
    if (currentLine < lineCount)
    {
      result += lineBuffer + '\n';
    }
    else
    {
      remaining += lineBuffer + '\n';
    }
  }

  file.close();

  // Tulis ulang file hanya jika ada baris tersisa
  SD.remove(filename);
  File newFile = SD.open(filename, FILE_WRITE);
  if (newFile)
  {
    newFile.print(remaining);
    newFile.close();
  }

  return result;
}

void StorageModule::manage()
{
  // Optional: bisa buat rotasi log, cek ukuran file, dsb
}