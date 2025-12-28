#include <SoftwareSerial.h>

SoftwareSerial loraSerial(10, 11);
int M0 = 7;
int M1 = 8;

void setup() {
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  
  digitalWrite(M0, HIGH);
  digitalWrite(M1, HIGH);
  delay(100);

  Serial.begin(9600);
  loraSerial.begin(9600);

  // Ayar Komutu: Adres 1, Kanal 23 (Verici ile ayni)
  uint8_t config[] = {0xC0, 0x00, 0x01, 0x1A, 0x17, 0x44};
  loraSerial.write(config, sizeof(config));
  delay(500);

  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
  delay(100);
  Serial.println("Alici Hazir...");
}

void loop() {
  if (loraSerial.available()) {
    String data = loraSerial.readString();
    Serial.print("Gelen Mesaj: ");
    Serial.println(data);
  }
}