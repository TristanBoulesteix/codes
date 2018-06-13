#include <Grove_I2C_Motor_Driver.h>

#define pin 7
#define I2C_ADDRESS 0x0f

int cran = 0;

void setup() {
  Serial.begin(9600);
  Motor.begin(I2C_ADDRESS);
  attachInterrupt(digitalPinToInterrupt(3), test, RISING);

  
}

void loop() {
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, 88);
  delay(1000);
  Serial.println(cran);
  Serial.println("1 seconde");
  cran = 0;
}

void test() {
  cran++;
}

