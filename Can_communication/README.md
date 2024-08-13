# CAN-BUS Communication with Arduino

This project demonstrates how to send and receive CAN (Controller Area Network) frames using an Arduino with the MCP2515 CAN-BUS shield. The project includes two separate programs: one for sending CAN frames (`send.cpp`) and another for receiving CAN frames (`receive.cpp`).

## Setup

### Hardware Requirements
- Arduino (e.g., Uno, Mega)
- MCP2515 CAN-BUS Shield
- SPI communication enabled
- CAN-BUS transceiver (to connect to a CAN network)

### Software Requirements
- Arduino IDE
- [MCP2515 library](https://github.com/coryjfowler/MCP_CAN_lib)

### Wiring
Connect the MCP2515 CAN-BUS Shield to the Arduino as follows:
- **SPI_CS_PIN (CS)**: Pin 9 on Arduino
- **SPI communication**: Connect SPI pins (MISO, MOSI, SCK) accordingly

## Code Overview

### `send.cpp`

This code sends a predefined CAN frame every 2 seconds on the CAN bus.

#### Key Functions:
- **Setup**: Initializes the CAN bus at a baud rate of 500kbps and verifies successful initialization.
- **Loop**: Continuously sends an 8-byte CAN frame with ID `0x7` and prints a success message to the serial monitor.

### `receive.cpp`

This code listens for incoming CAN frames and prints the received data to the serial monitor.

#### Key Functions:
- **Setup**: Initializes the CAN bus at 500kbps and verifies successful initialization.
- **Loop**: Continuously checks for incoming CAN frames, reads the data, and displays the CAN ID, data length, and the frame data in hexadecimal format.

## Usage

1. **Send CAN Frame**:
   - Upload `send.cpp` to an Arduino connected to the MCP2515 CAN-BUS shield.
   - The Arduino will send a CAN frame every 2 seconds.

2. **Receive CAN Frame**:
   - Upload `receive.cpp` to another Arduino connected to the MCP2515 CAN-BUS shield.
   - The Arduino will print any received CAN frames to the serial monitor.

Ensure both Arduinos are connected to the same CAN network and have a terminating resistor if required.
