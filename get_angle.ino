/* ANGLE MEASUREMENT WITH TWO SHARP GP2Y0A21YK0F SENSORS
 * Engineer: Carlos Agorreta
 * Date: 29/04/2019
 * This test will consist on measurng the analog output of the distance sensor in order to obtain its characteristic curve.
 * Approximate values: 80 cm (0.4 V), 10 cm (2.2 V). An op amp in non-inverting operation with gain of 2 
 * may be applied to increase resolution.
 * Arduino UNO has a 10 bit ADC at 5V, that means values 0 (0 mV) to 1023 (5000 mV) a resolution of 4.9 mV per LSB
 * With the measured voltage for a given distance, a linear regression will be performed to obtain
 * its distance function depending on its voltage and determine its linearity for a given range.
 */
 #include <math.h>    // (no semicolon), for the atan function
 unsigned char analogPin = 3, analogPin2 = 0, count = 0;
 double val = 0,val2 = 0, V = 0, V2=0, distance=0, distance2=0, sensorsdistance = 5.71, angle=0;
 /*distance is given in cm*/
void setup() {
  Serial.begin(9600);          //  setup serial
  Serial.println("Distance sensor demo");
  Serial.println("Readings:");
  delay(100); //delays 100 ms to obtain a stable value
}

void loop() {
  for (count = 0 ; count<10; count++) // read the input pin 10 times
  {
  val = val+analogRead(analogPin);  //accumulate value  
  val2=val2+analogRead(analogPin2);
  delay(50); //wait 50 ms per count
  }
  val = val/10; //average value of 10 measures
  val2 = val2/10;
  V = (val/204.8);
  V2 = (val2/204.8);
  /*Serial.print("Voltage 1: ");
  Serial.println(V,4);             // print float number, approximate voltage with a 4.9 mV error.
  Serial.print(" Volts");
  Serial.println();
  Serial.print("Voltage 2: ");
  Serial.println(V2,4);             // print float number, approximate voltage with a 4.9 mV error.
  Serial.print(" Volts");
  Serial.println();*/ // we don't need to print the measured voltage anymore
  val=(1/V);
  val2=(1/V2);
  distance = val*28.361-1.7044; //measured approximation
  distance2 = val2*28.361-1.7044;
  String stringOne = "Distance 1: ";
  String stringTwo = " cm";
  String stringThree = stringOne + distance + stringTwo;
  Serial.println(stringThree);  
  stringOne = "Distance 2: ";
  stringThree = stringOne + distance2 + stringTwo;
  Serial.println(stringThree); 
  if(distance>=distance2)
  {
  distance = distance - distance2;
  }
  else 
  {
    distance = (distance2-distance);
    }
    angle = (atan2 (distance, sensorsdistance))*180/M_PI; //obtain angle by trigonometry
  stringOne = "Angle: ";
  stringTwo = " degrees";
  stringThree = stringOne + angle + stringTwo;
  Serial.println(stringThree);  
  Serial.println();  
  val=0; //reinitialize values
  val2=0;
}
/*
 * According to datahsheet, 20 cm = 1.3 V, 10 cm = 2.3 V, 7 cm = 3V, 50 cm = 0.6 V. So an identification table with margins
 * can be performed instead of doing any signal processing by hardware or software.
 * With the first test, for a range of 10 cm to 25 cm, for an inverse voltage the following linear equation has been found
 * with a R^2 of 0.9997: distance(voltage) = 0.0352·voltage+0.0603
 */
