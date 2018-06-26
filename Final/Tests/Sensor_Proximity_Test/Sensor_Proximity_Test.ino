#define IR_PROXIMITY_SENSOR A1 // Analog input pin that  is attached to the sensor
#define ADC_REF 5//reference voltage of ADC is 5v.If the Vcc switch on the Seeeduino
//board switches to 3V3, the ADC_REF should be 3.3
float voltage;//the sensor voltage, you can calculate or find the distance
// to the reflective object according to the figures
//on page 4 or page 5 of the datasheet of the GP2Y0A21YK.

void setup()
{
  // initialise serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop()
{
  // >440 = very close
  // <440 = too close or more than 80 cm
  voltage = analogRead(IR_PROXIMITY_SENSOR);
  Serial.print("sensor voltage  = " );
  Serial.println(voltage);
  // wait 500 milliseconds before the next loop
  delay(500);
}
