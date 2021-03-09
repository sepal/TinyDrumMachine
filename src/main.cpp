#include <Arduino.h>
#include <Audio.h>
#include <uClock.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "Adafruit_NeoTrellis.h"
#include "Sequencer.h"
#include "Sampler.h"
#include "Grid.h"
#include "SequencerInput.h"

// Make sure all above sequencer data are modified atomicly only
// eg. ATOMIC(_sequencer[0].accent = true); ATOMIC(_step_length = 7);
uint8_t _tmpSREG;
#define ATOMIC(X)  \
  _tmpSREG = SREG; \
  cli();           \
  X;               \
  SREG = _tmpSREG;

#define FLASH_CHIP_SELECT  6

Sequencer sequencer;
Sampler sampler;

AudioOutputI2S out;
AudioConnection patchCord5(*sampler.getOutput(), 0, out, 0);
AudioConnection patchCord6(*sampler.getOutput(), 0, out, 1);
AudioControlSGTL5000 audioShield;
Grid grid;
SequencerInput seqInput(&sequencer, &grid);

void ClockOut16PPQN(uint32_t *tick)
{
  sequencer.step(tick);
}

SequencerCallback seqEvent(uint8_t note)
{
  Serial.println(note);
  return 0;
}

void setup()
{
  SPI.setSCK(14);  // Audio shield has SCK on pin 14
  SPI.setMOSI(7);  // Audio shield has MOSI on pin 7

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
  Serial.println("grid.begin");
  grid.begin();

  Serial.println("grid.registerhandler");
  grid.registerHandler(&seqInput);

  Serial.println("sequencer.registerCallback");
  sequencer.registerCallback(seqEvent);
  Serial.println("ready");
}

void loop()
{
  grid.read();
  for (uint8_t i = 0; i < MAX_VOICES; i++)
  {
    if (sequencer._stack[i] != NULL)
    {
      uint8_t pitch = sequencer._stack[i]->pitch;
      sampler.play(pitch);
      sequencer._stack[i] = NULL;
    }
  }
}
