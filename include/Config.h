#ifndef _PIN_CONFIG_H_
#define _PIN_CONFIG_H_


// Display settings.
#define LCD_TYPE DisplaySSD1351_128x128x16_SPI
#define PIN_LCD_RESET 30
#define PIN_LCD_CS 26
#define PIN_LCD_DC 28

// 5 way switch settings.
#define PIN_5W_SWITCH_RIGHT 0
#define PIN_5W_SWITCH_UP 1
#define PIN_5W_SWITCH_LEFT 2
#define PIN_5W_SWITCH_DOWN 3
#define PIN_5W_SWITCH_CENTER 4

// Encoder pins.
#define PIN_ENCODER_BUTTON 14
#define PIN_ENCODER_A 15
#define PIN_ENCODER_B 16

// BUTTON pins.
#define PIN_BUTTON_LEFT 5
#define PIN_BUTTON_MID 9
#define PIN_BUTTON_RIGHT 17

// Audio board pins & settings.
#define PIN_AUDIO_MEM 6
#define PIN_AUDIO_SD 10

#endif