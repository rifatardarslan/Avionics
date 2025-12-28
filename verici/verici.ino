#include <SoftwareSerial.h>

SoftwareSerial loraSerial(10, 11); // RX, TX
int M0 = 7;
int M1 = 8;

void setup() {
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  
  // ADIM 1: Ayar Modu (M0=1, M1=1)
  digitalWrite(M0, HIGH);
  digitalWrite(M1, HIGH);
  delay(100);

  Serial.begin(9600);
  loraSerial.begin(9600);

  // Ayar Komutu: Adres 1, Kanal 23
  uint8_t config[] = {0xC0, 0x00, 0x01, 0x1A, 0x17, 0x44};
  loraSerial.write(config, sizeof(config));
  delay(500);

  // ADIM 2: Normal Mod (M0=0, M1=0)
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
  delay(100);
  Serial.println("Verici Hazir!");
}

void loop() {
  loraSerial.print("Naber"); 
  Serial.println("Veri gonderildi:");
  delay(5000);
}