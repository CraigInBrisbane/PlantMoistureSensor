#include "ArduinoDeviceLibraries/FadingLED.h"

int PIN_Sensor =      A0;
int PIN_Power =       7;
int PIN_WarnLed =     8;

void setup() {
  // Setup PIN Modes.
  pinMode(PIN_Sensor, INPUT);
  pinMode(PIN_Power, OUTPUT);
  pinMode(PIN_WarnLed, OUTPUT);

  // Turn off the things so we can save some power.
  digitalWrite(PIN_Power, LOW);
  digitalWrite(PIN_WarnLED, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
