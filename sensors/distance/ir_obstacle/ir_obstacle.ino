/*
Tested with FC-51 (bangggod sku093479)
 The circuit:
 * VCC voltage is 3.3V to 5V converter (which can be directly connected to 5V single-chip microcontroller and 3.3V)
 * GND external GND
 * OUT of small plate digital output interface (0 and 1)
 
 FC-51 parameters
 The sensor module light is adaptable to the environment, it has a pair of infrared transmitting and receiving tube, tube infrared emit a certain frequency, when detecting direction meet with obstacles (reflecting surface), reflected infrared receiving tube, after the comparator circuit processing, green indicator will light up, at the same time signal output interface to output digital signal (a low level signal), can be through the potentiometer knob adjust the detection distance, effective distance range 2 ~ 30cm, working voltage is 3.3V to 5V. The sensor detection range can be through the potentiometer to adjust and have small interference, easy to assemble, easy to use, etc, can be widely used in robot obstacle avoidance, obstacle avoidance car, line count, and black and white line tracking and so on many occasions.
 Module Parameter:
 1. When the module detects obstacles in front of the signal, the green indicator on the circuit board light level and at the same time the OUT port output low level signal, the detection module from 2 ~ 30cm, 35°detection Angle, test distance can be adjusted through the potentiometer, adjustable potentiometer clockwise, the detection distance increases; Counter-clockwise tuning potentiometer, detection distance is reduced.
 2. Sensors, active infrared reflection detection, therefore the reflectivity and shape of the target is the key of the detection range. White one black detection range, minimum maximum; Small area of the object distance, large distance.
 3. The sensor module output port OUT can be directly connected to the microcontroller IO port can, also can drive a 5v relay directly; Connection mode: the VCC - VCC; GND - GND; The OUT - the IO
 4. The comparator USES the LM393, working stability;
 */

const int OUT_PIN = 7;

int val;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);

  pinMode(OUT_PIN,INPUT);
}

void loop()
{

  val = digitalRead(OUT_PIN);

  Serial.print("Sensor result : ");
  Serial.print(val);
  if (val == HIGH){
    Serial.print(" clear");
  } 
  else {
    Serial.print(" obstacle");
  }

  Serial.println();

  delay(1000);
}

