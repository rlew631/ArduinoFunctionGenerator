# ArduinoFunctionGenerator
The code in this repository was used to create a signal generator using an Arduino

The signal generator is able to produce a square wave, sine wave or linear ramp wave depending on which button is being pressed. The square wave uses a simple on/off logic, the sine wave uses a table which was generated in excel for the first half period (similar to the one attached), exported as a CSV and placed at the top of the code rather than importing another library.

If you look at the function diagram you can see that the negative portion of a given function is generated the same way as the positive region but by switching the transistor being used.

The circuit used two transistors to switch the pins that were serving as high and ground. There was also a capacitor used to smooth out the PWM signal to the transistor. The capacitor value was found by changing the values and viewing the output through an oscilloscope. Since the output frequency can be changed there is no single capacitance value which will work in all scenarios.
