String header = "6500|TOTO EST LA|3633";
String id = "";
String checksum = "";
String instruction;
int check;


int calcCheckSum(String message) {
  int checkSum;
  for (int i = 0; i < message.length(); i++) {
    checkSum = checkSum + (((int) message.charAt(i)) * i);
  }
  Serial.println(checkSum);
  return checkSum;
}


void setup() {
  Serial.begin(9600);
}

void loop() {
  if (header != "") {
    Serial.println("Message recu");
    int a = 0;
    for ( int i = 0; i < header.length(); i++) {
      if (header.charAt(i) == '|') {
        a++;
        i++;
      }
      if (a == 0) {
        id += header.charAt(i);
      } else if (a == 1) {
        instruction += header.charAt(i);
      } else if (a == 2) {
        checksum += header.charAt(i);

      }
    }
    check = calcCheckSum(instruction);
    if (id == String(6500)) {
      if (checksum == String(check)) {
        Serial.println("Message correct");
        Serial.println(instruction);
      } else {
        Serial.println("Error different checksum");
        Serial.println(checksum);
      }
    } else {
      Serial.println("Error different ID");
      Serial.println(id);
    }
  } else {
    Serial.println("Message corrompu"); // Affiche le message
  }
  delay(30000);
}
