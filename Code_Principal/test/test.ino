#include <Grove_I2C_Motor_Driver.h>

#define I2C_ADDRESS 0x0f

//Constants
const int STRAIGHT = 100;
const int TURN = 200;
const int LEFT = 210;
const int UP = 220;
const int RIGHT = 230;
const int DOWN = 240;
const int PROBLEM = 300;
const int CORRECT = 400;


// Integer
int signalPinC1 = 8;
int signalPinC2 = 4;
int signalPinLg = 6;
int signalPinLd = 2;
int statut = STRAIGHT;
int statutT;


int getNextRightDirection(int direction) {
  direction = direction + 10;

  if (direction > 240) {
    return 210;
  } else {
    return direction;
  }
}

int getNextLeftDirection(int direction) {
  direction = direction - 10;

  if (direction < 210) {
    return 240;
  } else {
    return direction;
  }
}

void moveForward() {
  Motor.speed(MOTOR1, 50);
  Motor.speed(MOTOR2, 44);
  Serial.println("moveForward");
}

void stopMotors() {
  Motor.stop(MOTOR1);
  Motor.stop(MOTOR2);
  Serial.println("stop");
}

void correctRight() {
  Motor.speed(MOTOR1, 50);
  Motor.speed(MOTOR2, 14);
  Serial.println("CR");
}

void correctLeft() {
  Motor.speed(MOTOR1, 20);
  Motor.speed(MOTOR2, 44);
  Serial.println("CL");
}

void turnLeft() {
  Motor.speed(MOTOR1, -50);
  Motor.speed(MOTOR2, 44);
  Serial.println("TL");
}

void turnRight() {
  Motor.speed(MOTOR1, 50);
  Motor.speed(MOTOR2, -44);
  Serial.println("TR");
}

void state() {
  if (statut == STRAIGHT) {
    if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == LOW && digitalRead(signalPinC2) == LOW && digitalRead(signalPinLd) == LOW) {
      //a long terme passé cette possibilité à recherche de ligne
       Serial.println("recherche de ligne");
    } else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == LOW && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == LOW) {
      // etat de redressement sur la ligne DROITE
      Serial.println("redressement droit");
    } else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == LOW && digitalRead(signalPinLd) == LOW) {
      // etat de redressement sur la ligne GAUCHE
      Serial.println("redressement gauche");
    } else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == HIGH) {
      // etat de tourner à droite
      Serial.println("tourner à droite");
    } else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == LOW) {
      // avancement normal
      Serial.println("tout droit");
    } else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == HIGH) {
      //etat de direction aléatoire entre tout droit et à droite
      Serial.println("tout droit droite");

    } else if (digitalRead(signalPinLg) == HIGH && digitalRead(signalPinC1) == LOW && digitalRead(signalPinC2) == LOW && digitalRead(signalPinLd) == LOW)    {
      //etat de direction aléatoire entre à gauche et à droite
      Serial.println("gauche droite");

    } else if (digitalRead(signalPinLg) == HIGH && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == LOW) {
      //etat de tourner à gauche
      Serial.println("tourner gauche");
    } else if (digitalRead(signalPinLg) == HIGH && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == HIGH)  {
      //Etat de tourner à gauche ou à droite ou bien continué d'aller tout droit
      //Set le statut à TURN ou STRAIGHT statut
      //set le statutT à LEFT ou RIGHT uniquement si TURN est selectionné
      Serial.println("gauche tout droit droite");

  }
  /*______________________________________________________________________________________________________________________________________________*/
  if (statut == TURN) {
    Serial.println("turn");
  }
  /*______________________________________________________________________________________________________________________________________________*/
  if ( statut == CORRECT) {
    iSerial.println("correct");
  }
  /*______________________________________________________________________________________________________________________________________________*/
  if (statut == PROBLEM) {
    stopMotors();
  }
}



void setup() {
  Motor.begin(I2C_ADDRESS);
  pinMode(signalPinC1, INPUT);
  pinMode(signalPinC2, INPUT);
  pinMode(signalPinLg, INPUT);
  pinMode(signalPinLd, INPUT);
  Serial.begin(9600);
  randomSeed(analogRead(2));
  delay(200);
}


void loop() {
  state ();
  Serial.print(statut);
}

