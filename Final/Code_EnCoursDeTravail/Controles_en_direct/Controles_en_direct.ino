#include <Grove_I2C_Motor_Driver.h>
#include <VirtualWire.h>
#define I2C_ADDRESS 0x0f

//Constants
const int STRAIGHT = 100;
const int TURN = 200;
const int LEFT = 210;
const int RIGHT = 220;
const int DOWN = 230;
const int CORRECT = 300;
const int PROBLEM = 404;
const int LISTEN = 500;

// Integer
int RF_RX_PIN = 2;
int signalPinC1 = 8;
int signalPinC2 = 4;
int signalPinLg = 7;
int signalPinLd = 6;
int statut = STRAIGHT;
int statutT;
int cherche = 0;
int check;
int turn = 0;
int tourner = 0;
int index = 0;

//Structure
typedef struct header {
  String id;
  String instruction = "LLL";
  String checksum;
} messageHeader;

//header
messageHeader comparatif;

//String
String msg;


/*______________________________________________________________________________________________________________________________________________________________*/
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
  Motor.speed(MOTOR2, -44);
  Serial.println("CR");
}

void correctLeft() {
  Motor.speed(MOTOR1, -50);
  Motor.speed(MOTOR2, 44);
  Serial.println("CL");
}

void turnLeft() {
  Motor.speed(MOTOR1, -100);
  Motor.speed(MOTOR2, 50);
  Serial.println("TL");
}

void turnRight() {
  Motor.speed(MOTOR1, 50);
  Motor.speed(MOTOR2, -100);
  Serial.println("TR");
}

int calcCheckSum(String message) {
  int checkSum;
  for (int s = 0; s < message.length(); s++) {
    checkSum = checkSum + (((int) message.charAt(s)) * (s + 1));
  }
  Serial.println(checkSum);
  return checkSum;
}

void doInstruction(int type) {
  if (comparatif.instruction.charAt(index) == 'A' && type == 0) {
    statut = STRAIGHT;
  }
  if (comparatif.instruction.charAt(index) == 'A' && type == 1) {
    statut = CORRECT;
    statutT = LEFT;
  }
  if (comparatif.instruction.charAt(index) == 'A' && type == 2) {
    statut = CORRECT;
    statutT = RIGHT;
  }
  else if (comparatif.instruction.charAt(index) == 'H') {
    statut = STRAIGHT;
  }
  else if (comparatif.instruction.charAt(index) == 'L') {
    statut = TURN;
    statutT = LEFT;
  }
  else if (comparatif.instruction.charAt(index) == 'R') {
    statut = TURN;
    statutT = RIGHT;
  }
  index ++;
  if (index > sizeof(comparatif.instruction)) {
    statut = PROBLEM;
  }
}

/*______________________________________________________________________________________________________________________________________________________________*/
void state() {
  if (statut == LISTEN) {
    byte header[VW_MAX_MESSAGE_LEN];
    byte taille_message = VW_MAX_MESSAGE_LEN;
    // N.B. La constante VW_MAX_MESSAGE_LEN est fournie par la lib VirtualWire
    // On attend de recevoir un message
    vw_wait_rx();
    if (vw_get_message(header, &taille_message)) {
      Serial.println("Message recu");
      msg = String((char*)header);
      Serial.println(msg);
      int a = 0;
      for ( int i = 0; i < msg.length(); i++) {
        if (msg.charAt(i) == '|') {
          a++;
          i++;
        }
        if (a == 0) {
          comparatif.id += msg.charAt(i);
          Serial.println(comparatif.id);
        } else if (a == 1) {
          comparatif.instruction += msg.charAt(i);
        } else if (a == 2) {
          comparatif.checksum += msg.charAt(i);
        }
      }
      check = calcCheckSum(comparatif.instruction);
      if (comparatif.id == String(6500)) {
        if (comparatif.checksum == String(check))
        {
          Serial.println("Message Correct");
          Serial.println(comparatif.instruction);
        } else {
          Serial.println("Error different checksum");
          Serial.println(comparatif.checksum);

        }
      } else {
        Serial.println("Error different ID");
        Serial.println(comparatif.id);
      }
    } else {
      Serial.println("Message corrompu"); // Affiche le message
    }
    comparatif.id = "";
    comparatif.checksum = "";
    comparatif.instruction = "";

  }
  /*______________________________________________________________________________________________________________________________________________*/
  if (statut == STRAIGHT) {
    if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == LOW && digitalRead(signalPinC2) == LOW && digitalRead(signalPinLd) == LOW) {//0000
      // recherche de ligne
      cherche += 1;
      moveForward();
      //if (cherche > 50) {
      // statut = PROBLEM;
      //}

    } else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == LOW && digitalRead(signalPinC2) == LOW && digitalRead(signalPinLd) == HIGH) {//0001
      // etat de tourner à droite
      doInstruction(0);

    } else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == LOW && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == LOW) {//0010
      // etat de redressement sur la ligne DROITE
      statut = CORRECT;
      statutT = RIGHT;

    } else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == LOW && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == HIGH) { //0011
      //etat possible pour aller tout droit ou à droite
      doInstruction(0);

    } else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == LOW && digitalRead(signalPinLd) == LOW) {//0100
      // etat de redressement sur la ligne GAUCHE
      statut = CORRECT;
      statutT = LEFT;

    } else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == LOW && digitalRead(signalPinLd) == HIGH) {//0101
      // tourner à droite ou corriger la trajectoire et continuer tout droit
      doInstruction(1);

    } else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == LOW) {//0110
      // avancement normal
      cherche = 0;
      turn += 1;
      statut = STRAIGHT;
      moveForward();
      if (tourner == 1 && turn > 80) {
        tourner = 0;
        turn = 0;
      }

    } else if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == HIGH) {//0111
      //etat de direction aléatoire entre tout droit et à droite
      doInstruction(0);

    }  else if (digitalRead(signalPinLg) == HIGH && digitalRead(signalPinC1) == LOW && digitalRead(signalPinC2) == LOW && digitalRead(signalPinLd) == LOW) {//1000
      //etat de tourner à gauche
      doInstruction(0);

    } else if (digitalRead(signalPinLg) == HIGH && digitalRead(signalPinC1) == LOW && digitalRead(signalPinC2) == LOW && digitalRead(signalPinLd) == HIGH) { //1001
      //etat de direction aléatoire entre à gauche et à droite
      doInstruction(0);
    } else if (digitalRead(signalPinLg) == HIGH && digitalRead(signalPinC1) == LOW && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == LOW) {//1010
      //tourner à gauche ou corriger la trajectoire
      doInstruction(2);

    } else if (digitalRead(signalPinLg) == HIGH && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == LOW && digitalRead(signalPinLd) == LOW) {//1100
      //tourner à gauche ou corriger la trajectoire à gauche
      doInstruction(1);

    } else if (digitalRead(signalPinLg) == HIGH && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == LOW) {//1110
      //etat de direction aléatoire entre à gauche et tout droit
      doInstruction(0);

    } else if (digitalRead(signalPinLg) == HIGH && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == HIGH) { //1111
      //Etat de tourner à gauche ou à droite ou bien continué d'aller tout droit
      doInstruction(0);

    }
    else {
      statut = PROBLEM;
    }
  }

  /*______________________________________________________________________________________________________________________________________________*/
  if (statut == TURN) {
    if (statutT == RIGHT && tourner == 0) {
      turnRight();
      if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == LOW) {
        statut = STRAIGHT;
        statutT = 0;
        tourner = 1;
      }

    } else if (statutT == LEFT && tourner == 0) {
      turnLeft();
      if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == LOW) {
        statut = STRAIGHT;
        statutT = 0;
        tourner = 1;
      }
    }
  }

  /*______________________________________________________________________________________________________________________________________________*/
  if ( statut == CORRECT) {
    if (statutT == RIGHT)
    {
      correctRight();
      turn++;
      if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == LOW) {
        statut = STRAIGHT;
        statutT = 0;
      }

    } else if (statutT == LEFT)
    {
      correctLeft();
      turn++;
      if (digitalRead(signalPinLg) == LOW && digitalRead(signalPinC1) == HIGH && digitalRead(signalPinC2) == HIGH && digitalRead(signalPinLd) == LOW) {
        statut = STRAIGHT;
        statutT = 0;
      }
    }
  }

  /*______________________________________________________________________________________________________________________________________________*/
  if (statut == PROBLEM) {
    stopMotors();
  }
}
/*______________________________________________________________________________________________________________________________________________________________*/
void setup() {
  Motor.begin(I2C_ADDRESS);
  pinMode(signalPinC1, INPUT);
  pinMode(signalPinC2, INPUT);
  pinMode(signalPinLg, INPUT);
  pinMode(signalPinLd, INPUT);
  Serial.begin(9600);
  vw_set_rx_pin(RF_RX_PIN);
  // Initialisation de la bibliothèque VirtualWire
  // Vous pouvez changez les broches RX/TX/PTT avant vw_setup() si nécessaire
  vw_setup(2000);
  vw_rx_start(); // On peut maintenant recevoir des messages
  delay(200);
}


void loop() {
  state ();
}

