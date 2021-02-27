#include <Arduino.h>
#include <Audio.h>
#include <uClock.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "Adafruit_NeoTrellis.h"
#include "AudioSampleBd.h"
#include "AudioSampleSd.h"
#include "AudioSampleCh.h"
#include "AudioSampleOh.h"
#include "Sequencer.h"

// Make sure all above sequencer data are modified atomicly only
// eg. ATOMIC(_sequencer[0].accent = true); ATOMIC(_step_length = 7);
uint8_t _tmpSREG;
#define ATOMIC(X) _tmpSREG = SREG; cli(); X; SREG = _tmpSREG;

Sequencer sequencer;


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

#define TRELLIS_X 4
#define TRELLIS_Y 8
const uint8_t TRELLIS_NUM_PIXELS = TRELLIS_Y * TRELLIS_X;
//create a matrix of trellis panels
Adafruit_NeoTrellis trellis_array[TRELLIS_X/4][TRELLIS_Y/4] = {
  
  { Adafruit_NeoTrellis(0x2F), Adafruit_NeoTrellis(0x2E) }
  
};


Adafruit_MultiTrellis trellis((Adafruit_NeoTrellis *)trellis_array, TRELLIS_Y/4, TRELLIS_X/4);

void ClockOut16PPQN(uint32_t * tick) {
  sequencer.step(tick);
}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return seesaw_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return seesaw_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return seesaw_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  return 0;
}

TrellisCallback blink(keyEvent evt){
  // Serial.println(evt.bit.NUM);
  // // Check is the pad pressed?
  // if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
  //   trellis.setPixelColor(evt.bit.NUM, seesaw_NeoPixel::Color(255, 255, 255)); //on rising
  // } else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
  // // or is the pad released?
  //   trellis.setPixelColor(evt.bit.NUM, 0); //off falling
  // }

  // // Turn on/off the neopixels!
  // trellis.show();

  return 0;
}

SequencerCallback seqEvent(uint8_t note) {
  Serial.println(note);
  return 0;
}

uint16_t get_pixel_num(uint16_t x, uint16_t y) {
  return (x > 3 ? 1 : 0) * 12 + x + (y * 4);
}

uint8_t note_to_pixel_num(uint8_t note) {
  switch (note) {
    case 48:
      return 3;
    case 50:
      return 2;
    case 52:
      return 1;
    case 53:
      return 0;
  }
  return 0;
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

  trellis.begin();

  for(int i=0; i<TRELLIS_NUM_PIXELS; i++){
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
    trellis.registerCallback(i, blink);
  }

  for (uint8_t i=0; i<sequencer.step_len; i++) {
    if (sequencer._sequence[i] != 0) {
      uint8_t y = note_to_pixel_num(sequencer._sequence[i]);
      uint16_t n = get_pixel_num(i, y);
      
      trellis.setPixelColor(n, seesaw_NeoPixel::Color(128,0,128));
    }
  }

  trellis.show();

  sequencer.registerCallback(seqEvent);
}

void loop() {
  trellis.read();
  for (int i=0; i<MAX_CHANNELS; i++) {
        if (sequencer._stack[i] != 0) {
               switch (sequencer._stack[i]) {
              case 48:
                playChn1.play(AudioSampleBd);
              break;
              case 50:
                playChn2.play(AudioSampleSd);
              break;
              case 52:
                playChn3.play(AudioSampleCh);
              break;
              case 53:
                playChn3.play(AudioSampleOh);
              break;
            }
            sequencer._stack[i] = 0;
        }
    }
}
