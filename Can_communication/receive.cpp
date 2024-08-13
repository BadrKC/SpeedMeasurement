#include <SPI.h>
#include <mcp2515_can.h> // Include the MCP2515 CAN library

const int SPI_CS_PIN = 9; // Define the Chip Select (CS) pin for SPI
mcp2515_can CAN_RECEIVE(SPI_CS_PIN); // Initialize the CAN object with the CS pin

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud

  // Initialize CAN bus at 500kbps, retry if initialization fails
  while (CAN_OK != CAN_RECEIVE.begin(CAN_500KBPS)) {
    Serial.println("CAN_RECEIVE init fail, retry...");
    delay(100);
  }
  Serial.println("CAN_RECEIVE init ok!"); // Print success message
}

void loop() {
  unsigned char len = 0; // Length of the received data
  unsigned char buf[8]; // Buffer to hold received data

  if (CAN_MSGAVAIL == CAN_RECEIVE.checkReceive()) { // Check for received data
    CAN_RECEIVE.readMsgBuf(&len, buf); // Read data: len = data length, buf = data bytes

    // Print message ID and length
    Serial.print("ID: ");
    Serial.print(CAN_RECEIVE.getCanId(), HEX);
    Serial.print("  Data Length: ");
    Serial.println(len);

    // Print each byte of the received data
    Serial.print("  Frame: ");
    for (int i = 0; i < len; i++) {
      Serial.print(buf[i], HEX);
      Serial.print("\t");
    }
    Serial.println();
    Serial.println("-------------------------------"); // Separator for clarity
  }
}
