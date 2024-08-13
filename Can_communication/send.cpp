// demo: CAN-BUS Shield, send data
// loovee@seeed.cc

#include <SPI.h>

#define CAN_2515

const int SPI_CS_PIN = 9; // Define the Chip Select (CS) pin for SPI

#ifdef CAN_2515
#include "mcp2515_can.h" // Include the MCP2515 CAN library
mcp2515_can CAN(SPI_CS_PIN); // Initialize the CAN object with the CS pin
#endif

void setup() {
    SERIAL_PORT_MONITOR.begin(9600); // Start serial communication at 9600 baud

    // Initialize CAN bus at 500kbps, retry if initialization fails
    while (CAN_OK != CAN.begin(CAN_500KBPS)) {
        SERIAL_PORT_MONITOR.println("CAN init fail, retry...");
        delay(100);
    }
    SERIAL_PORT_MONITOR.println("CAN init ok!"); // Print success message
}

unsigned char data[8] = {0xAb, 0xBc, 0xCd, 0xde, 0xef, 0xff, 0x99, 0x77}; // Data to send

void loop() {
    CAN.sendMsgBuf(0x7, 0, 8, data); // Send the data on the CAN bus with ID 0x7
    delay(2000); // Wait for 2 seconds
    SERIAL_PORT_MONITOR.println("CAN BUS sendMsgBuf ok!"); // Print a success message
}
