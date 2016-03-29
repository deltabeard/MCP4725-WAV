/*
 * Play WAV file from SD card to MCP4725 DAC.
 * 
 * Released under MIT License.
 * Copyright (c) 2016 Mahyar Koshkouei
 */
 
#define SD_CS_PIN 4

#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <SPI.h>
#include <SdFat.h>

Adafruit_MCP4725 dac;
SdFat sd;
SdFile file;

void setup() {
  Serial.begin(9600);
  
  Serial.print("Initializing SD card: ");
  if(!sd.begin(SD_CS_PIN, SPI_FULL_SPEED))
  {
    Serial.println("failed");
    sd.initErrorHalt();
  }
  Serial.println("done");
  
  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  dac.begin(0x60);

}

void loop() {
  int count = 0;

  Serial.println("Opening test.wav");
  
  // open wave file from sdcard
  if(!file.open("test.wav", O_READ))
  {
    sd.errorHalt("opening test.txt for read failed");
  }

  Serial.println("Playing test.wav");
  
  while(file.available())
  {
      dac.setVoltage(file.read()*4, false);
  }
  file.close();

  Serial.println("Finished playing.");
}
