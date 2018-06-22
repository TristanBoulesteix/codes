#include <Grove_I2C_Motor_Driver.h>

char inputBuffer[10];

void setup() {
  Serial.begin(9600);
  Serial.println("test running");
}

void loop() {
  while (true) {
    if (Serial.available() > 0) {
      Serial.readBytes(inputBuffer, 10);
      delay(5000);
      Serial.print("I got this ->");
      Serial.print(inputBuffer);
      Serial.println("<-");
      Motor.speed(MOTOR1, 50);
      Motor.speed(MOTOR2, 38);
    }
  }
}
