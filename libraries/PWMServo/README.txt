http://arduiniana.org/libraries/pwmservo/

Arduino 0016 introduced a spanking new Servo library that makes it possible to control a Servo from any pin. The old library used PWM, which limited its use to pins 9 or 10.

Unfortunately, the new library uses an interrupt-based technology which breaks NewSoftSerial. If you’re building a project that needs Servo and Soft serial, you might try this library instead. (I didn’t write it; this is really just the old library renamed.)

[August, 2011 update]
Paul Stoffregen recently updated the library to include support for Teensy, Teensy++, Sanguino, and the Mega varieties and Arduino 1.xx.  This is really a nice and much appreciated improvement. Because of the additional timers that the Mega and Teensy processors provide, these platforms can support a third simultaneous servo.

Thanks Paul!

The pins that are available for controller servos vary from controller to controller, so here’s a tidy table showing you which pins are available:

Board                     SERVO_PIN_A   SERVO_PIN_B   SERVO_PIN_C
-----                     -----------   -----------   -----------
Arduino Uno, Duemilanove       9            10          (none)
Arduino Mega                  11            12            13
Sanguino                      13            12          (none)
Teensy 1.0                    17            18            15
Teensy 2.0                    14            15             4
Teensy++ 1.0 or 2.0           25            26            27

Download

Download the original PWMServo library (as it was shipped with pre-0016 Arduino). (This is useful mostly only for historical reasons.)
Download Paul’s version 2 library with Teensy, Teensy++, Mega, and Sanguino support. This version also supports Arduino 1.xx.