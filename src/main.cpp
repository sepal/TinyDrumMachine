#include <Arduino.h>
#include <Audio.h>
#include <uClock.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <lcdgfx.h>
#include "Adafruit_NeoTrellis.h"
#include "Sequencer.h"
#include "Sampler.h"
#include "Grid.h"
#include "SequencerInput.h"
#include "FiveWaySwitch.h"

#define FLASH_CHIP_SELECT  6

DisplaySSD1306_128x64_I2C display(-1);

Sequencer sequencer;
Sampler sampler;

AudioOutputI2S out;
AudioConnection patchCord5(*sampler.getOutput(), 0, out, 0);
AudioConnection patchCord6(*sampler.getOutput(), 0, out, 1);
AudioControlSGTL5000 audioShield;
Grid grid;
FiveWaySwitch fiveWaySwitch;
SequencerInput seqInput(&sequencer, &grid);

void ClockOut16PPQN(uint32_t *tick)
{
  sequencer.step(tick);
}

void setup()
{
  // Audio shield has SCK on pin 14
  SPI.setSCK(14);
  // Audio shield has MOSI on pin 7
  SPI.setMOSI(7);

  fiveWaySwitch.begin();

  Serial.begin(9600);
  AudioMemory(10);

  // Start SerialFlash
  if (!SerialFlash.begin(FLASH_CHIP_SELECT)) {
    while (1) {
      Serial.println(F("Cannot access SPI Flash chip"));
      delay (1000);
    }
  }

  audioShield.enable();
  audioShield.volume(0.5);

  uClock.init();
  uClock.setClock16PPQNOutput(ClockOut16PPQN);
  uClock.setTempo(90);

  uClock.start();
  grid.begin();

  grid.registerHandler(&seqInput);
  grid.show();

  sequencer.registerInstrument(&sampler);

  display.begin();
  display.setFixedFont(ssd1306xled_font8x16);
  display.clear();
  display.printFixed(0, 8, "SEQ");
  Serial.println("ready");
}

void loop()
{
  grid.read();
  sequencer.update();
}
