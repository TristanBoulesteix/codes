#include <Grove_I2C_Motor_Driver.h>

#define I2C_ADDRESS 0x0f

//Constants
const int STRAIGHT = 100;
const int TURN = 200;
const int LEFT = 210;
const int RIGHT = 220;
const int PROBLEM = 300;
const int CORRECT = 400;


// Integer
int signalPinC1 = 8;
int signalPinC2 = 4;
int signalPinLg = 6;
int signalPinLd = 2;
int statut = STRAIGHT;
int statutT;

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
  Motor.speed(MOTOR2, 14);
}

void correctLeft() {
  Motor.speed(MOTOR1, 20);
  Motor.speed(MOTOR2, 44);
}

void turnLeft() {
  Motor.speed(MOTOR1, -50);
  Motor.speed(MOTOR2, 44);
}

void turnRight() {
  Motor.speed(MOTOR1, 50);
  Motor.speed(MOTOR2, -44);
}

void state() {
  if (statut == STRAIGHT)
  {
    if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == LOW && digitalRead(signalPinC2) == LOW && digitalRead(signalPinLd) == LOW)
    {
      //a long terme passé cette possibilité à recherche de ligne
      moveForward();
    }

    else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == LOW && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == LOW)
    {
      // etat de redressement sur la ligne DROITE
      statut = CORRECT;
      statutT = RIGHT;
    }

    else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == LOW && digitalRead(signalPinLd) == LOW)
    {
      // etat de redressement sur la ligne GAUCHE
      statut = CORRECT;
      statutT = LEFT;
    }
    else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == HIGH)
    {
      // etat de tourner à droite
      statut = TURN;
      statutT = RIGHT;
    }
    else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == LOW)
    {
      // avancement normal
      moveForward();
    }    else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == HIGH)    {
      //etat de direction aléatoire entre tout droit et à droite
    }    else if (digitalRead(signalPinLg) == HIGH && digitalRead(signalPinC1) == LOW && digitalRead(signalPinC2) == LOW && digitalRead(signalPinLd) == LOW)    {
      //etat de direction aléatoire entre à gauche et à droite
      statut = TURN;
      // passe la statutT à la valeur trouvé avec l'aléatoire
    } else if (digitalRead(signalPinLg) == HIGH && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == LOW) {
      //etat de tourner à gauche
      statut = TURN;
      statutT = LEFT;
    } else if (digitalRead(signalPinLg) == HIGH && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == HIGH)  {
      //Etat de tourner à gauche ou à droite ou bien continué d'aller tout droit
      //Set le statut à TURN ou STRAIGHT statut
      //set le statutT à LEFT ou RIGHT uniquement si TURN est selectionné
    } else {
      statut = PROBLEM;
    }

  } else if (statut == TURN) {
    if (statutT == RIGHT) {
		turnRight();
		
		if (digitalRead(signalPinLg) == HIGH && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == HIGH){
			statut = STRAIGHT;
		}
    } else if (statutT == LEFT) {
      turnLeft();
	  
	  if (digitalRead(signalPinLg) == HIGH && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == HIGH){
			statut = STRAIGHT;
		}
    } else {
      statut == PROBLEM;
    }
  }  else if ( statut == CORRECT) {
	  if (statutT == RIGHT){
		  turnRight();
	  }
  }
}



void setup() {
  Motor.begin(I2C_ADDRESS);
  pinMode(signalPinC1, INPUT);
  pinMode(signalPinC2, INPUT);
  pinMode(signalPinLg, INPUT);
  pinMode(signalPinLd, INPUT);
  Serial.begin(9600);
  delay(200);
}


void loop() {
  state ();
}

