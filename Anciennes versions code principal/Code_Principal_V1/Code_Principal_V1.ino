#include <Grove_I2C_Motor_Driver.h>

#define I2C_ADDRESS 0x0f

int signalPinC1 = 8;
int signalPinC2 = 4;
int signalPinLg = 7;
int signalPinLd = 6;


void moveForward() {
  Motor.speed(MOTOR1, 50);
  Motor.speed(MOTOR2, 44);
  
}

void stopMotors() {
  Motor.stop(MOTOR1);
  Motor.stop(MOTOR2);
}

void correctRight() {
  Motor.speed(MOTOR1, 50);
  Motor.speed(MOTOR2, 12);
}

void correctLeft() {
  Motor.speed(MOTOR1, 20);
  Motor.speed(MOTOR2, 44);
}

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
  if (digitalRead(signalPinLg)==LOW && digitalRead(signalPinC1)== HIGH && digitalRead(signalPinC2)== HIGH && digitalRead(signalPinLg)==LOW){
    Serial.println("Tout Droit");
    moveForward();
  }
  
  if (digitalRead(signalPinLg)==LOW && digitalRead(signalPinC1)== HIGH && digitalRead(signalPinC2)== LOW && digitalRead(signalPinLg)==LOW){
    Serial.println("A gauche");
    correctLeft();
  }
  
  if (digitalRead(signalPinLg)==LOW && digitalRead(signalPinC1)== LOW && digitalRead(signalPinC2)== HIGH && digitalRead(signalPinLg)==LOW){
    Serial.println("A droite");
    correctRight();
  }
  if (digitalRead(signalPinLg)==LOW && signalPinC1== LOW && digitalRead(signalPinC2)== LOW && digitalRead(signalPinLg)==LOW){
    Serial.println("Stop Machine");
    stopMotors();
  }
}


