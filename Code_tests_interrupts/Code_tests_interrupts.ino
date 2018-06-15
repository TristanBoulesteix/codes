#include <Grove_I2C_Motor_Driver.h>

// default I2C address is 0x0f
#define I2C_ADDRESS 0x0f

// Initialize all line finder
int pinLineLeft = 7;
int pinLineCenterLeft = 8;
int pinLineCenterRight = 4;
int pinLineRight = 3;

// Initialize IR
#define IR_PROXIMITY_SENSOR A1
#define ADC_REF 5

// Interruptions
// http://www.locoduino.org/spip.php?article64



void setup() {
  Motor.begin(I2C_ADDRESS);
  //attachInterrupt(
}

void loop() {
  Serial.begin(9000);

  pinMode(pinLineLeft, INPUT);
  pinMode(pinLineCenterLeft, INPUT);
  pinMode(pinLineCenterRight, INPUT);
  pinMode(pinLineRight, INPUT);

  
  // move();
  //turnLeft();
  //turnRight();

}

void move() {
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, 100);
}

void turnLeft() {
  Motor.stop(MOTOR1);
}

void turnRight() {
  Motor.stop(MOTOR2);
}

void stopEverything() {
  Motor.stop(MOTOR1);
  Motor.stop(MOTOR2);
}

