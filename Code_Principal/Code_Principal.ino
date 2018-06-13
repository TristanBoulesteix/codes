#include <Grove_I2C_Motor_Driver.h>

#define I2C_ADDRESS 0x0f

int signalPin = 8;

void setup() {
  Motor.begin(I2C_ADDRESS);
  Serial.begin(9600);
  pinMode(signalPin, INPUT);
}

void loop() {
  delay(200);
  if (HIGH == digitalRead(signalPin)) {
    moveForward();
    turnRight();
    Serial.println("black");
  } else {

    Serial.println("white");
    stopMotors();
  }
}

void moveForward() {
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, 88);
  delay(2200);
}

void stopMotors() {
  Motor.stop(MOTOR1);
  Motor.stop(MOTOR2);
}

void turnLeft() {
  Motor.speed(MOTOR1, -100);
  delay(535);
}

void turnRight() {
  Motor.speed(MOTOR2, -88);
  delay(515);
}

