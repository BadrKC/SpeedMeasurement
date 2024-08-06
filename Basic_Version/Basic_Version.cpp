#include <SPI.h>

#define CAN_2515

const int SPI_CS_PIN = 9;
// const int CAN_INT_PIN = 2;

#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif

// Variables for time tracking and sensor readings
unsigned long lastTime = 0;                // To store the last time measured
const int sensorPin = 8;                   // Pin connected to the speed sensor
const int resolution = 20;                 // Resolution of the sensor (number of pulses per revolution)
int rpm = 0;                               // To store the calculated RPM
uint32_t  pulses = 0;                         // To count the number of pulses
// uint8_t sensorValue = 0;                    // To read the current sensor value
uint8_t acutalState = 0;                    // To store the current state of the sensor
uint8_t oldState = 0;                       // To store the previous state of the sensor
const unsigned long sampleTime = 3000;     // Sample time of 1 second (in milliseconds)

// Wheel measurements and speed calculations
const float wheelDiameterCm = 6.65;        // Diameter of the wheel in centimeters
const float wheelCircumferenceCm = PI * wheelDiameterCm;  // Circumference of the wheel in centimeters
const float wheelCircumferenceM = wheelCircumferenceCm / 100.0;  // Circumference of the wheel in meters
const float wheelCircumferenceKm = wheelCircumferenceCm / 100000.0;  // Circumference of the wheel in kilometers
float speedKmh = 0.0000;                   // To store the calculated speed in km/h
float speedms = 0.0000;                    // To store the calculated speed in m/s

void setup() {
  SERIAL_PORT_MONITOR.begin(9600);
  pinMode(sensorPin, INPUT);   // Set the sensor pin as input
  Serial.println("Welcome ");

  // Initialize CAN bus communication
  while (CAN_OK != CAN.begin(CAN_500KBPS)) {             // init can bus : baudrate = 500k always keep it same to the Rpi CAN interface
      SERIAL_PORT_MONITOR.println("CAN init fail, retry...");
      delay(100);
  }
  SERIAL_PORT_MONITOR.println("CAN init ok!");
}

unsigned char data[8] = {0xAb, 0xBc, 0xCd, 0xde, 0xef, 0xff, 0x99, 0x77};

void loop() {
  // Measure the time since the last sample
  unsigned long currentTime = millis();
   
  // Read the current state of the sensor
  acutalState = digitalRead(sensorPin);
  
  // Check if the sensor state has changed
  if (acutalState != oldState) {
    pulses += acutalState;  // Increment pulse count if state has changed
    Serial.print("Pulses are: ");
    Serial.println(pulses);
    oldState = acutalState;  // Update the old state to the current state
  }

  // Calculate and display RPM and speed every second
  if (currentTime - lastTime >= sampleTime) {
    rpm = ((pulses * 60) / (sampleTime / 1000)) / resolution;  // Calculate RPM
    speedKmh = (rpm * wheelCircumferenceKm * 60);  // Convert RPM to speed in km/h
    speedms = (rpm * wheelCircumferenceM / 60);  // Convert RPM to speed in m/s

    // Print the results to the Serial monitor
    Serial.print("The number of pulses is: ");
    Serial.print(pulses);
    Serial.print(" \t Rotation Speed: ");
    Serial.print(rpm);
    Serial.print(" RPM");
    Serial.print(" \t Speed in Kmh: ");
    Serial.print(speedKmh);
    Serial.println(" Km/h");
    Serial.print(" \t Speed in ms: ");
    Serial.print(speedms);
    Serial.println(" m/s");

    // Prepare data for CAN transmission
    unsigned char data[8] = {rpm, speedKmh, speedms, 0xde, 0xef, 0xff, 0x99, 77};

    CAN.sendMsgBuf(0xBB, 0, 8, data); // Send the data on the CAN bus

    SERIAL_PORT_MONITOR.println("CAN BUS sendMsgBuf ok!"); // Print a success message

    pulses = 0;  // Reset pulse count
    lastTime = currentTime;  // Update the last time
  }
}