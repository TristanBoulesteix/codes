#include <Grove_I2C_Motor_Driver.h>

#define I2C_ADDRESS 0x0f

const int UP = 100;
const int DOWN = 200;
const int  LEFT = 300;
const int RIGHT = 400;

char mapFromUs[7][4];
char destination[5]  = {'J', 'I', 'H', '0', '0'};

int index = 0;

int x = 3;
int y = 4;
int currentDirection = LEFT;

int compareX(int xCD) {
  int xCompared = xCD - x;

  return xCompared;
}

int compareY(int yCD) {
  int yCompared = yCD - y;

  return yCompared;
}

int getCoordinatesX(char c) {
  for (int i = 0; i < sizeof(mapFromUs); i++) {
    for (int j = 0; j < sizeof(mapFromUs[i]); j++) {
      if (mapFromUs[i][j] == c) {
        return i;
      }
    }
  }
}

int getCoordinatesY(char c) {
  for (int i = 0; i < sizeof(mapFromUs); i++) {
    for (int j = 0; j < sizeof(mapFromUs[i]); j++) {
      if (mapFromUs[i][j] == c) {
        return j;
      }
    }
  }
}

void moveForward(int cases) {
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, 88);
  delay(142 * cases);
  Motor.stop(MOTOR1);
  Motor.stop(MOTOR2);
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

void moveY(int yCD) {
  // Comparaison de nos coordonnées avec celles du point de destination
  if (compareY(yCD) > 0) {
    if (currentDirection == LEFT) {
      // 1/4 de tour vers la droite
      turnRight();
      moveForward(abs(compareY(yCD)));
      currentDirection = UP;
      y = y + abs(compareY(yCD));
    } else if (currentDirection == UP) {
      moveForward(abs(compareY(yCD)));
      currentDirection = UP;
      y = y + abs(compareY(yCD));
    } else if (currentDirection == RIGHT) {
      turnLeft();
      moveForward(abs(compareY(yCD)));
      currentDirection = UP;
      y = y + abs(compareY(yCD));
    } else if (currentDirection == DOWN) {
      turnRight();
      turnRight();
      moveForward(abs(compareY(yCD)));
      currentDirection = UP;
      y = y + abs(compareY(yCD));
    }
  } else if (compareY(yCD) < 0) {
    if (currentDirection == LEFT) {
      turnLeft();
      moveForward(abs(compareY(yCD)));
      currentDirection = DOWN;
      y = y - abs(compareY(yCD));
    } else if (currentDirection == UP) {
      turnRight();
      turnRight();
      moveForward(abs(compareY(yCD)));
      currentDirection = DOWN;
      y = y - abs(compareY(yCD));
    } else if (currentDirection == RIGHT) {
      turnRight();
      moveForward(abs(compareY(yCD)));
      currentDirection = DOWN;
      y = y - abs(compareY(yCD));
    } else if (currentDirection == DOWN) {
      moveForward(abs(compareY(yCD)));
      currentDirection = DOWN;
      y = y - abs(compareY(yCD));
    }
  } else if (compareY(yCD) == 0) {
    index++;
  }
}

void moveX(int xCD, int yCD) {
  // Comparaison de nos coordonnées avec celles du point de destination
  if (compareX(xCD) > 0) {
    if (currentDirection == LEFT) {
      // Demi-tour et avancer du nombre de cases nécessaires par la comparaison des xCD et x
      turnRight();
      turnRight();
      moveForward(abs(compareX(xCD)));
      currentDirection = RIGHT;
      x = x + abs(compareX(xCD));
    } else if (currentDirection == UP) {
      // 1/4 de tour à droite
      turnRight();
      moveForward(abs(compareX(xCD)));
      currentDirection = RIGHT;
      x = x + abs(compareX(xCD));
    } else if (currentDirection == RIGHT) {
      // Juste avancer
      moveForward(abs(compareX(xCD)));
      currentDirection = RIGHT;
      x = x + abs(compareX(xCD));
    } else if (currentDirection == DOWN) {
      // 1/4 de tour à gauche
      turnLeft();
      moveForward(abs(compareX(xCD)));
      currentDirection = RIGHT;
      x = x + abs(compareX(xCD));
    }
  } else if (compareX(xCD) < 0) {
    if (currentDirection == LEFT) {
      // Juste avancer
      moveForward(abs(compareX(xCD)));
      currentDirection = LEFT;
      x = x - abs(compareX(xCD));
    } else if (currentDirection == UP) {
      // 1/4 de tour à gauche
      turnLeft();
      moveForward(abs(compareX(xCD)));
      currentDirection = LEFT;
      x = x - abs(compareX(xCD));
    } else if (currentDirection == RIGHT) {
      // Demi-tour et avancer du nombre de cases nécessaires par la comparaison des xCD et x
      turnRight();
      turnRight();
      moveForward(abs(compareX(xCD)));
      currentDirection = LEFT;
      x = x - abs(compareX(xCD));
    } else if (currentDirection == DOWN) {
      // 1/4 de tour à droite
      turnRight();
      moveForward(abs(compareX(xCD)));
      currentDirection = LEFT;
      x = x - abs(compareX(xCD));
    }
  } else if (compareX(xCD) == 0) {
    moveY(yCD);
  }
}

void setup() {
  Motor.begin(I2C_ADDRESS);
  Serial.begin(9600);

  mapFromUs[0][4] = 'A';
  mapFromUs[2][4] = 'B';
  mapFromUs[5][4] = 'C';
  mapFromUs[7][4] = 'D';
  mapFromUs[0][2] = 'E';
  mapFromUs[2][2] = 'F';
  mapFromUs[5][2] = 'G';
  mapFromUs[7][2] = 'H';
  mapFromUs[0][0] = 'I';
  mapFromUs[2][0] = 'J';
  mapFromUs[5][0] = 'K';
  mapFromUs[7][0] = 'L';

  for (int i = 0; i < sizeof(mapFromUs); i++) {
    for (int j = 0; j < sizeof(mapFromUs[i]); j++) {
      if (mapFromUs[i][j] == NULL) {
        mapFromUs[i][j] = '0';
      }
    }
  }
}

void loop() {
  if (destination[index] != '0' || index <= sizeof(destination)) {
    // Définit le trajet entre une destination i et i+1
    char currentDestination = destination[index];
    int xCD = getCoordinatesX(currentDestination);
    int yCD = getCoordinatesY(currentDestination);

    moveX(xCD, xCD);
  } else if (destination[index] == '0' || index > sizeof(destination)) {
    turnLeft();
  }

  turnRight();
}

