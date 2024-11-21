Microcontroller C Language Project Programmed in Microchip Studio
Relay Control Program Based on Temperature

This project, built with an ATmega328P microcontroller, reads the voltage from a potential divider and converts it into a temperature value using an NTC thermistor. Buttons allow the user to set a threshold temperature at which the relay will activate.
The project includes a .pdsprj file that can be used to simulate the code along with the HEX file in Proteus.

Custom libraries created for this project include:
- Interrupt handling
- Analog-to-Digital Converter (ADC)
- 4-Digit 7-Segment LED Display
- Timer management

Materials:
- ATmega328P Nano
- 4-Digit 7-Segment LED display (common cathode)
- Resistors for the 4-Digit 7-Segment display
- Potential divider with a 10 kΩ NTC thermistor connected to VCC and a 10 kΩ resistor to ground
- Hardware debounce buttons
- Relay

Functionality:
The program operates using a finite state machine with the following states:
Startup: Displays "Hola" for 3 seconds.
Temperature Setting: Shows the current temperature. Buttons allow the user to increase or decrease the threshold temperature for activating the relay.
Monitoring: Displays messages based on the temperature:
- SET: Indicates the threshold has been set.
- HOT: Indicates the sensed temperature exceeds the threshold and activates the relay.
- COLD: Indicates the sensed temperature is below the threshold.
Stop Mode: Halts all operations and displays "STOP."
