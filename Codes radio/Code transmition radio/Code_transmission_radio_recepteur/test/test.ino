String header = "6900|DROITE|3654";
String id = "";
String checksum = "";
String instruction;

void setup() {
  Serial.begin(9600);
  Serial.println("salut");
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
  } else {
    Serial.println("Message corrompu"); // Affiche le message
  }
  Serial.println(id);
  Serial.println(instruction);
  Serial.println(checksum);
  delay(30000);
}
