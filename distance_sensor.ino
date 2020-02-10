/*DISTANCE SENSOR SHARP GP2Y0A21YK0F TEST
 * Engineer: Carlos Agorreta
 * Date: 29/04/2019
 * This test will consist on measuring the analog output of the distance sensor in order to obtain its characteristic curve.
 * Approximate values: 80 cm (0.4 V), 10 cm (2.2 V). An op amp in non-inverting operation with gain of 2 
 * may be applied to increase resolution.
 * Arduino UNO has a 10 bit ADC at 5V, that means values 0 (0 mV) to 1023 (5000 mV) a resolution of 4.9 mV per LSB
 * With the measured voltage for a given distance, a linear regression will be performed to obtain
 * its distance function depending on its voltage and determine its linearity for a given range.
 */
 int analogPin = 3;
 float val = 0, V = 0, distance=0;
void setup() {
  Serial.begin(9600);          //  setup serial
  Serial.println("Distance sensor demo");
  Serial.println("Readings:");
  delay(100); //delays 100 ms to obtain a stable value
}

void loop() {
  val = analogRead(analogPin);    // read the input pin
  V = (val/204.8);
  Serial.print("Voltage: ");
  Serial.println(V,1);             // print float number, approximate voltage with a 4.9 mV error.
  Serial.print(" Volts");
  Serial.println();
  val=(1/V);
  distance = val*28.361-1.7044;
  Serial.print("Distancce: ");
  Serial.println(distance,1);             // print float number
  Serial.print(" cm");
  Serial.println();
  delay(500); //delay to get slower values printed and more stable ones
}
/*
 * According to datahsheet, 20 cm = 1.3 V, 10 cm = 2.3 V, 7 cm = 3V, 50 cm = 0.6 V. So an identification table with margins
 * can be performed instead of doing any signal processing by hardware or software.
 * With the first test, for a range of 10 cm to 25 cm, for an inverse voltage the following linear equation has been found
 * with a R^2 of 0.9997: distance(voltage) = 0.0352·voltage+0.0603
 */
