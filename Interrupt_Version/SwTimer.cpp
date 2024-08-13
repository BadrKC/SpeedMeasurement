#include <SPI.h>

#define CAN_2515

const int SPI_CS_PIN = 9; // Define the Chip Select (CS) pin for SPI communication

#ifdef CAN_2515
#include "mcp2515_can.h" // Include the MCP2515 CAN library
mcp2515_can CAN(SPI_CS_PIN); // Initialize the CAN object with the CS pin
#endif

// Variables for time tracking and sensor readings
volatile unsigned long pulses = 0;         // To count the number of pulses (volatile because it's used in an ISR)
unsigned long lastTime = 0;                // To store the last time a sample was taken
const int sensorPin = 3;                   // Pin connected to the speed sensor
const int resolution = 20;                 // Resolution of the sensor (number of pulses per revolution)
const unsigned long sampleTime = 1000;     // Sample time of 1 second (in milliseconds)

// Wheel measurements and speed calculations
const float wheelDiameterCm = 6.65;        // Diameter of the wheel in centimeters
const float wheelCircumferenceCm = PI * wheelDiameterCm;  // Circumference of the wheel in centimeters
const float wheelCircumferenceM = wheelCircumferenceCm / 100.0;  // Circumference in meters
const float wheelCircumferenceKm = wheelCircumferenceCm / 100000.0;  // Circumference in kilometers

float speedKmh = 0.0;                      // To store the calculated speed in km/h
float speedms = 0.0;                       // To store the calculated speed in m/s

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud
  pinMode(sensorPin, INPUT); // Set the sensor pin as input
  attachInterrupt(digitalPinToInterrupt(sensorPin), countPulse, RISING); // Attach interrupt for pulse counting

  Serial.println("Welcome");

  // Initialize CAN bus at 500kbps and check if initialization is successful
  while (CAN_OK != CAN.begin(CAN_500KBPS)) {
    Serial.println("CAN init fail, retry...");
    delay(100);
  }
  Serial.println("CAN init ok!");
}

// Interrupt Service Routine (ISR) for pulse counting
void countPulse() { 
  pulses++; // Increment the pulse count
}

void loop() {
  // Measure the time since the last sample
  unsigned long currentTime = millis();
   
  // Calculate and display RPM and speed every sample time
  if (currentTime - lastTime >= sampleTime) {
    noInterrupts();  // Disable interrupts temporarily to safely read the pulse count
    unsigned long pulsesCount = pulses;
    pulses = 0;  // Reset the pulse count for the next interval
    interrupts();  // Re-enable interrupts

    // Calculate RPM and speed
    float rpm = (pulsesCount * 60) / (sampleTime / 1000.0) / resolution;  // Calculate RPM
    speedKmh = (rpm * wheelCircumferenceKm * 60);  // Calculate speed in km/h
    speedms = (rpm * wheelCircumferenceM / 60);    // Calculate speed in m/s

    // Print the results to the Serial monitor
    Serial.print("Total pulses in last interval: ");
    Serial.print(pulsesCount);
    Serial.print(" \t Rotation Speed: ");
    Serial.print(rpm);
    Serial.print(" RPM");
    Serial.print(" \t Speed in Km/h: ");
    Serial.print(speedKmh, 2);  // Print with 2 decimal places
    Serial.print(" Km/h");
    Serial.print(" \t Speed in m/s: ");
    Serial.print(speedms, 2);  // Print with 2 decimal places
    Serial.println(" m/s");

    // Prepare data for CAN transmission
    byte canData[8] = {
      byte(rpm), 
      byte(speedKmh), byte(int(speedKmh * 100) % 100),  // Split speedKmh into integer and fractional parts
      byte(speedms), byte(int(speedms * 100) % 100),    // Split speedms into integer and fractional parts
      byte(pulsesCount >> 8), byte(pulsesCount & 0xFF), // Split pulse count into high and low bytes
      0x77  // An arbitrary byte, possibly used as a flag or identifier
    };

    // Send the data on the CAN bus and check for errors
    byte sndStat = CAN.sendMsgBuf(0xBB, 0, 8, canData);
    if (sndStat == CAN_OK) {
      Serial.println("CAN BUS sendMsgBuf ok!");
    } else {
      Serial.println("Error sending CAN message. Error code: " + String(sndStat));
    }

    // Update the last time a sample was taken
    lastTime = currentTime;  
  }
}
