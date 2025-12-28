#include <SoftwareSerial.h>

SoftwareSerial loraSerial(10, 11); // RX, TX
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

  uint8_t config[] = {0xC0, 0x00, 0x01, 0x1A, 0x17, 0x44};
  loraSerial.write(config, sizeof(config));
  delay(500);

  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
  delay(100);
  
  randomSeed(analogRead(0)); // Her seferinde farklı sayılar üretmesi için
  Serial.println("Verici Hazir! Rastgele sayilar gonderiliyor...");
}

void loop() {
  int sayi = random(1, 11); // 1 ile 10 arasında sayı üretir
  loraSerial.print(sayi); 
  
  Serial.print("Gonderilen Sayi: ");
  Serial.println(sayi);
  
  delay(5000); // 5 saniye bekle
}