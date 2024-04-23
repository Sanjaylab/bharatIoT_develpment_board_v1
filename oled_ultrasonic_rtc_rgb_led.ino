#include <Wire.h>
#include "SSD1306Wire.h"  // legacy: #include "SSD1306.h"
#include <FastLED.h>
#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };


const int trigPin = 32;
const int echoPin = 33;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

#define LED_PIN 4   //led pin  ws2812b
#define NUM_LEDS 1  //total no. of  rgb led in parallel ws2812b

CRGB leds[NUM_LEDS];

#define buzzer 12  // buzzer

SSD1306Wire display(0x3c, SDA, SCL);  // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h

void setup() {
  // put your setup code here, to run once:
  // Debug console
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input

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
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");

    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void loop() {

  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  String d_time = String(now.day()) + "-" + String(now.month()) + "-" + String(now.year()) + "  " + String(now.hour()) + "-" + String(now.minute()) + "-" + String(now.second());
  // put your main code here, to run repeatedly:
  Serial.println(d_time);

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distanceCm = duration * SOUND_SPEED / 2;

  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;

  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);

  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.drawString(1, 10, "BharatIoT Development board");
  display.drawString(1, 30, "distanceCm:" + String(distanceCm));
  // display.drawString(1, 48, d_time);

  display.display();
  delay(10);
  leds[1] = CRGB(0, 255, 0);
  FastLED.show();
  delay(50);
}
