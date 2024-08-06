# SpeedMeasurement

## Description
SpeedMeasurement is an Arduino project that measures rotation speed using an MH Infrared Speed Sensor Module. It calculates various speed metrics and features CAN bus integration for data transmission, making it suitable for automotive or industrial applications requiring real-time speed monitoring.

## Features
- Uses MH Infrared Speed Sensor Module for pulse detection
- Measures rotation speed in RPM
- Calculates speed in km/h and m/s
- Integrates with CAN bus for data transmission
- Multiple versions available:
  1. Basic version without interrupts
  2. Version using interrupts for improved accuracy
  3. Version using hardware timer for precise measurements
- Serial output for debugging and monitoring

## Hardware Requirements
- Arduino board (compatible with CAN bus)
- MH Infrared Speed Sensor Module
- CAN bus module

## Software Dependencies
- Arduino IDE
- CAN bus library Seeed-Studio/Seeed_Arduino_CAN: Seeed Arduino CAN-BUS library - MCP2518FD&MCP2515&MCP2551 (github.com)

## Installation
1. Clone this repository or download the source code.
2. Open the desired `.ino` file in Arduino IDE (basic, interrupt, or timer version).
3. Install the required CAN bus library.
4. Upload the sketch to your Arduino board.

## Usage
1. Connect the MH Infrared Speed Sensor Module to the specified input pin.
2. Connect the CAN bus module to the appropriate pins on the Arduino.
3. Power up the Arduino.
4. The sensor will start measuring rotation speed and transmitting data over the CAN bus.
5. Monitor the Serial output for real-time measurements and debugging information.

## Configuration
- Adjust `sampleTime` to change the measurement interval.
- Modify `wheelCircumferenceKm` and `wheelCircumferenceM` to match your specific application.
- Update the CAN message ID and data format as needed for your system.

## Version Differences
1. Basic Version: Simple polling method, suitable for low-speed applications.
2. Interrupt Version: Uses interrupts for more accurate pulse counting, better for higher speeds.
3. Hardware Timer Version: Utilizes a hardware timer for precise timing, ideal for high-speed or high-precision requirements.

## Contributing
Contributions to improve SpeedMeasurement are welcome. Please feel free to submit a Pull Request.

## License
MIT License

Copyright (c) [2024] [Badr_Kacemi]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Contact
BadrKC
Badrkacemi.20@gmail.com