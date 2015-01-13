/*
Tested with 
The circuit:
	* Sensor      Arduino	
        * GND	      GND	
        * VCC	      VCC (5-20V)	
        * OUT	      Digital pin 3
*/

const int PIR_PIN = 3;


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
  pinMode(PIR_PIN,INPUT);
}

void loop()
{
  
 
  
  boolean tripped = digitalRead(DIGITAL_INPUT_SENSOR) == HIGH

  Serial.print("Motion detected ? ");
  Serial.println(tripped);

  delay(1000);
}


