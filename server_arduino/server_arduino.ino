
int lock=8;
void setup() {
  pinMode(lock, OUTPUT);
  digitalWrite(lock, HIGH);
  Serial.begin(115200);
}

void loop() {
    while (!Serial.available()) {};
    //reading the answer to a string
    String a= Serial.readString();
    
    if (a=="open\r\n") {
      digitalWrite(lock, LOW);
    };
    if (a=="close\r\n") {
      digitalWrite(lock, HIGH);
    };
}
