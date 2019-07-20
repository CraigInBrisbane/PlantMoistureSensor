#include "ArduinoDeviceLibraries/SoilSensor.h"

// Configurable settings.
int   PIN_Sensor =        A0;     // PIN to which the Sensor Signal wire is connected.
int   PIN_Power =         7;      // PIN which we will power the sensor from. Not using 5V, to lessen corrosion and allow for power saving (Switch off and on)
int   PIN_WarnLED =       3;      // PIN to which the LED Indicator will connect. This will flash when the sensor is below a definded value.
bool  DebugMode =         true;   // If Debug is enabled, we will be logging data to the serial port.
int   PollingInterval =   1000;   // Time in milliseconds when the sensor will be polled for a reading.
int   LowLevelReading =   580;    // The low value which will enable the warning LED. i.e. The low value for "Plant needs water!"

// Define the Soil Sensor and variable for the last value.
SoilSensor                sensor;
int SensorValue =         0;
bool IsWarningState =     false;


void setup() {

  if(DebugMode)
    Serial.begin(9600);
  
  sensor.Init(PIN_Sensor, PIN_Power, PollingInterval);
  sensor.SetDebugMode(DebugMode);
  
  // Setup the indicator LED.
  pinMode(PIN_WarnLED, OUTPUT);

  // Packet Soil was 355
  // Jeremy was 570 to 590, with nearly enough water.
 
}

void loop() {

  // Check the sensor value.
  int newVal = sensor.Update();
  
  if(DebugMode) {
    Serial.print("Recieved value from sensor: ");
    Serial.println(newVal);
  }

  if(newVal != -1) { // Sensor returns -1 if it thinks it doesn't need to read yet, or isn't setup.
  
    if(newVal != SensorValue) {
      SensorValue = newVal;
    
      // Are we entering a warning state?    
      if(SensorValue <= LowLevelReading && IsWarningState == false) {
        if(DebugMode) {
          Serial.println("Low level detected. Enabling Warning LED");
        }
        IsWarningState = true;
        digitalWrite(PIN_WarnLED, HIGH);
      }
    
      // Are we exiting a warning state?    
      if(SensorValue > LowLevelReading && IsWarningState) {    
        if(DebugMode) { 
          Serial.println("Low level no longer detected. Disabling Warning LED");
        }
        IsWarningState=false;
        digitalWrite(PIN_WarnLED, LOW);  
      }   
    }
  }
  
}
