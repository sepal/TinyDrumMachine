#include <Arduino.h>
#include <Audio.h>
#include <uClock.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <lcdgfx.h>
#include "Adafruit_NeoTrellis.h"
#include <Encoder.h>

#include "FiveWaySwitch.h"
#include "Sequencer.h"
#include "DrumkitSampleEngine.h"
#include "Grid.h"
#include "SequencerInput.h"
#include "Stealth57.h"
#include "Menu.h"
#include "Pages.h"
#include "ADSRPage.h"
#include "Encoder.h"
#include "EncoderHandler.h"

#define FLASH_CHIP_SELECT 6

DisplaySSD1327_128x128_I2C display(-1);
AudioControlSGTL5000 audioShield;

Sequencer sequencer;
DrumkitSampleEngine drumkitSampler;

AudioOutputI2S out;
AudioConnection patchCord5(*drumkitSampler.getOutput(), 0, out, 0);
AudioConnection patchCord6(*drumkitSampler.getOutput(), 0, out, 1);
Grid grid;
FiveWaySwitch fiveWaySwitch;
SequencerInput seqInput(&sequencer, &grid);
EncoderHandler* encoderHandler = 0;
int32_t encoder_last_pos;

Page* pages[1] = {
  new ADSRPage(&display, &drumkitSampler),
};
Menu menu(&display, pages, 1);

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


  Serial.begin(9600);
  delay(2000);
  AudioMemory(10);

  // Start SerialFlash
  if (!SerialFlash.begin(FLASH_CHIP_SELECT))
  {
    while (1)
    {
      Serial.println(F("Cannot access SPI Flash chip"));
      delay(1000);
    }
  }

  audioShield.enable();
  audioShield.volume(0.5);

  uClock.init();
  uClock.setClock16PPQNOutput(ClockOut16PPQN);
  uClock.setTempo(90);

  uClock.start();
  display.begin();
  display.setFixedFont(stealth5710x8);

  grid.begin();
  grid.registerHandler(&seqInput);
  grid.show();

  sequencer.registerAudioEngine(&drumkitSampler);


  fiveWaySwitch.begin();
  menu.begin();
  fiveWaySwitch.registerEventHandler(&menu);

  menu.updatePageScreen();

  Serial.println("Ready!");
}


void loop()
{
  grid.read();
  sequencer.update();
  fiveWaySwitch.update();
  menu.update();
}
