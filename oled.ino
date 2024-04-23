#include <Wire.h>
#include "SSD1306Wire.h"  // legacy: #include "SSD1306.h"
#include <FastLED.h>
#define LED_PIN 4   //led pin  ws2812b
#define NUM_LEDS 3  //total no. of  rgb led in parallel ws2812b

CRGB leds[NUM_LEDS];

#define buzzer 12  // buzzer

SSD1306Wire display(0x3c, SDA, SCL);  // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h

void setup() {
  // put your setup code here, to run once:
  // Debug console
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  leds[0] = CRGB(255, 0, 0);
  FastLED.show();
  delay(100);
  leds[1] = CRGB(255, 0, 0);
  FastLED.show();
  delay(100);
  leds[2] = CRGB(255, 0, 0);
  FastLED.show();
  delay(100);

  display.init();
  display.flipScreenVertically();
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(2, 10, "       BharatIoT   ");
  display.drawString(2, 30, "      Development      ");
  display.drawString(2, 48, "         Board      ");

  display.display();
  delay(2000);
  leds[0] = CRGB(0, 255, 0);
  FastLED.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  leds[1] = CRGB(0, 255, 0);
  FastLED.show();
  delay(50);

  delay(1000);
  leds[1] = CRGB(255, 0, 0);
  FastLED.show();
  delay(50);
  delay(1000);
}
