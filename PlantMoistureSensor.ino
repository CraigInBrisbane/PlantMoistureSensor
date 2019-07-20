#include "ArduinoDeviceLibraries/FadingLED.h"

int PIN_Sensor =      A0;
int PIN_Power =       7;
int PIN_WarnLED =     3;
int readValue =       0;

void setup() {
  
  //Serial.begin(9600);
  
  // Setup PIN Modes.
  pinMode(PIN_Sensor, INPUT);
  pinMode(PIN_Power, OUTPUT);
  pinMode(PIN_WarnLED, OUTPUT);

  // Turn off the things so we can save some power.
  digitalWrite(PIN_Power, LOW);
  digitalWrite(PIN_WarnLED, LOW);


  // Packet Soil was 355
  // Jeremy was 570 to 590, with nearly enough water.
  

  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PIN_Power, HIGH);
  digitalWrite(PIN_WarnLED, HIGH);
  delay(20);
  digitalWrite(PIN_WarnLED, LOW);
  readValue = analogRead(PIN_Sensor); 
  //Serial.print("Soil read value: ");
  //Serial.println(readValue);
  digitalWrite(PIN_Power, LOW);
  delay(2000);
}
