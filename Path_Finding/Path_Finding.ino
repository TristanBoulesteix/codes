#include <Grove_I2C_Motor_Driver.h>

#define I2C_ADDRESS 0x0f

char mapFromUs[7][4];
char destination[5]  = {'J', 'I', 'H', '0', '0'};

int index = 0;

int x = 3;
int y = 4;

void compareX(int xCD){
	int xCompared
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

void moveForward() {
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, 88);
  delay(142);
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
  // Définit le trajet entre une destination i et i+1
  char currentDestination = destination[index];
  int xCD = getCoordinatesX(currentDestination);
  int yCD = getCoordinatesY(currentDestination);


  // Comparaison de nos coordonnées avec celles du point de destination



}

