#include <Grove_I2C_Motor_Driver.h>

#define I2C_ADDRESS 0x0f

int signalPinC1 = 8;
int signalPinC2 = 4;
int signalPinLg = 6;
int signalPinLd = 2;

void setup() {
  Motor.begin(I2C_ADDRESS);
  Serial.begin(9600);
  pinMode(signalPinC1, INPUT);
  pinMode(signalPinC2, INPUT);
  pinMode(signalPinLg, INPUT);
  pinMode(signalPinLd, INPUT);
  
}

void loop() {
  delay(200);
  if (digitalRead(signalPinC1)== HIGH && digitalRead(signalPinC2)== HIGH){
    Serial.println("Tout Droit");
    //moveForward();
    //turnRight();
  }
  
  if (digitalRead(signalPinC1)== HIGH && digitalRead(signalPinC2)== LOW){
    Serial.println("A gauche");
  }
  
  if (digitalRead(signalPinC1)== LOW && digitalRead(signalPinC2)== HIGH){
    Serial.println("A droite");
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

