# ESP32 Smart Door with Fingerprint and Keypad

This repository contains the code and resources for building a smart door system using an ESP32 microcontroller, fingerprint sensor, keypad, and relay module. The system allows users to unlock the door using either their registered fingerprints or a passcode entered on the keypad.

## Hardware Requirements
- ESP32 microcontroller board
- Fingerprint sensor module (e.g., R307, GT-511C3, etc.)
- Keypad module
- Relay module
- 5V power supply
- Jumper wires
- Door lock mechanism

## Software Requirements
- Arduino IDE (Integrated Development Environment)
- ESP32 board support for Arduino IDE
- Libraries: Adafruit Fingerprint Sensor Library, Keypad Library

## Getting Started

1. Clone or download this repository to your local machine.
2. Connect the hardware components according to the circuit diagram provided in the repository.
3. Open the Arduino IDE and install the required libraries.
4. Connect your ESP32 board to your computer using a USB cable.
5. Select the appropriate board and port in the Arduino IDE.
6. Navigate to the downloaded repository and open the `Finger_Print.ino` and `Keypad.ino` file in the Arduino IDE.
7. Configure the necessary settings in the code, such as fingerprint IDs, passcode, etc.
8. Compile and upload the code to the ESP32 board by clicking on the "Upload" button in the IDE.

## Circuit Diagram

A circuit diagram illustrating the connections between the ESP32, fingerprint sensor, keypad, and relay module is provided in the repository. Ensure that the connections are made correctly to avoid any damage to the components.

## Usage

1. Power on the ESP32 board and ensure that it is connected to the Wi-Fi network if applicable.
2. Place your registered fingerprint on the sensor or enter the correct passcode on the keypad.
3. If the fingerprint or passcode is verified successfully, the relay will activate and unlock the door.
4. Modify the code as per your requirements, such as adding more fingerprints, changing the passcode, etc.

## Contributing

Contributions to this project are welcome. If you find any bugs or have suggestions for improvements, please open an issue or submit a pull request with your changes.

## License

This project is licensed under the [MIT License](LICENSE). Feel free to modify and distribute the code as per the terms of the license.

## Acknowledgments

This project was inspired by various smart door system tutorials and resources available online. Special thanks to the open-source community for their contributions.

## Contact

If you have any questions or need further assistance, feel free to contact me at chaonchom@outlook.com.

Enjoy building your ESP32 smart door with fingerprint and keypad unlocking capabilities!
