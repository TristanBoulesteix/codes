#include <Grove_I2C_Motor_Driver.h>

#define I2C_ADDRESS 0x0f

int signalPinC1 = 8;
int signalPinC2 = 4;
int signalPinLg = 7;
int signalPinLd = 6;

void setup() {
  Motor.begin(I2C_ADDRESS);
  Serial.begin(9600);
  pinMode(signalPinC1, INPUT);
  pinMode(signalPinC2, INPUT);
  pinMode(signalPinLg, INPUT);
  pinMode(signalPinLd, INPUT);
  delay(200);
}

void loop() {
  if (digitalRead(signalPinC1)== HIGH && digitalRead(signalPinC2)== HIGH){
    Serial.println("Tout Droit");
    moveForward();
  }
  
  if (digitalRead(signalPinC1)== HIGH && digitalRead(signalPinC2)== LOW){
    Serial.println("A gauche");
    turnLeft();
  }
  
  if (digitalRead(signalPinC1)== LOW && digitalRead(signalPinC2)== HIGH){
    Serial.println("A droite");
    turnRight();
  }
  if (digitalRead(signalPinC1)== LOW && digitalRead(signalPinC2)== LOW){
    stopMotors();
  }
  
}

void moveForward() {
  Motor.speed(MOTOR1, 50);
  Motor.speed(MOTOR2, 44);
  
}

void stopMotors() {
  Motor.stop(MOTOR1);
  Motor.stop(MOTOR2);
}

void turnRight() {
  Motor.speed(MOTOR1, 50);
  Motor.speed(MOTOR2, 12);
}

void turnLeft() {
  Motor.speed(MOTOR1, 20);
  Motor.speed(MOTOR2, 44);
}

