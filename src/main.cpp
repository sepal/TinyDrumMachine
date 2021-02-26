#include <Arduino.h>
#include <Audio.h>
#include <uClock.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "AudioSampleBd.h"
#include "AudioSampleSd.h"
#include "AudioSampleCh.h"

#define STEP_MAX_SIZE      16

uint16_t _step_length = STEP_MAX_SIZE;

// Make sure all above sequencer data are modified atomicly only
// eg. ATOMIC(_sequencer[0].accent = true); ATOMIC(_step_length = 7);
uint8_t _tmpSREG;
#define ATOMIC(X) _tmpSREG = SREG; cli(); X; SREG = _tmpSREG;
uint16_t _step = 0;

// GUItool: begin automatically generated code
AudioPlayMemory          playChn2;       //xy=319,633
AudioPlayMemory          playChn3;       //xy=319,667
AudioPlayMemory          playChn4;       //xy=319,700
AudioPlayMemory          playChn1;       //xy=320,599
AudioMixer4              mixerMain;         //xy=558,644
AudioOutputI2S           out;           //xy=754,646
AudioConnection          patchCord1(playChn2, 0, mixerMain, 1);
AudioConnection          patchCord2(playChn3, 0, mixerMain, 2);
AudioConnection          patchCord3(playChn4, 0, mixerMain, 3);
AudioConnection          patchCord4(playChn1, 0, mixerMain, 0);
AudioConnection          patchCord5(mixerMain, 0, out, 0);
AudioConnection          patchCord6(mixerMain, 0, out, 1);
AudioControlSGTL5000     audioShield;     //xy=478,1043
// GUItool: end automatically generated code

void ClockOut16PPQN(uint32_t * tick) {
  _step = *tick % _step_length;
  Serial.println(_step);

  switch(_step) {
    case 0:
      playChn2.play(AudioSampleBd);
      playChn1.play(AudioSampleCh);
    break;
    case 1:
      playChn1.play(AudioSampleCh);
    break;
    case 2:
      playChn1.play(AudioSampleCh);
    break;
    case 3:
      playChn1.play(AudioSampleCh);
    break;
    case 4:
      playChn1.play(AudioSampleCh);
      playChn3.play(AudioSampleSd);
    break;
    case 5:
      playChn2.play(AudioSampleBd);
    break;
    case 6:
      playChn1.play(AudioSampleCh);
    break;
    case 7:
      playChn1.play(AudioSampleCh);
    break;
    case 8:
      playChn2.play(AudioSampleBd);
      playChn1.play(AudioSampleCh);
    break;
    case 9:
      playChn1.play(AudioSampleCh);
    break;
    case 10:
      playChn1.play(AudioSampleCh);
    break;
    case 11:
      playChn1.play(AudioSampleCh);
    break;
    case 12:
      playChn1.play(AudioSampleCh);
      playChn3.play(AudioSampleSd);
    break;
    case 13:
      playChn1.play(AudioSampleCh);
    break;
    case 14:
      playChn2.play(AudioSampleCh);
    break;
    case 15:
      playChn1.play(AudioSampleCh);
      playChn3.play(AudioSampleSd);
    break;
  }
}

void setup() {
  Serial.begin(9600);
  AudioMemory(10);

  audioShield.enable();
  audioShield.volume(0.5);

  mixerMain.gain(0, 0.4);
  mixerMain.gain(1, 0.4);
  mixerMain.gain(2, 0.4);
  mixerMain.gain(3, 0.4);

  uClock.init();
  uClock.setClock16PPQNOutput(ClockOut16PPQN);
  uClock.setTempo(90);

  uClock.start();
}

void loop() {
  // put your main code here, to run repeatedly:
}