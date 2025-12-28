#include <SoftwareSerial.h>

SoftwareSerial loraSerial(10, 11); // RX, TX
int M0 = 7; 
int M1 = 8;

// Değişkenler (Basınç değişkeni eklendi)
float bmeSicaklik, bmeNem, bmeBasinc;
float mpuX, mpuY, mpuZ;

void setup() {
  pinMode(M0, OUTPUT); pinMode(M1, OUTPUT);
  digitalWrite(M0, HIGH); digitalWrite(M1, HIGH);
  delay(100);
  
  Serial.begin(9600);
  loraSerial.begin(9600);
  
  // Konfigürasyon
  uint8_t config[] = {0xC0, 0x00, 0x01, 0x1A, 0x17, 0x44};
  loraSerial.write(config, sizeof(config));
  delay(500);
  
  digitalWrite(M0, LOW); digitalWrite(M1, LOW);
  Serial.println("--- SISTEM HAZIR (Basinc Destekli) ---");
}

void loop() {
  if (loraSerial.available()) {
    String gelenPaket = loraSerial.readStringUntil('\n');
    gelenPaket.trim(); // Boşlukları temizle

    // Veri boş mu kontrol et
    if (gelenPaket.length() > 0) {
      
      // Virgüllerin yerini buluyoruz (Artık 5 virgül aramalıyız)
      int ind1 = gelenPaket.indexOf(',');
      int ind2 = gelenPaket.indexOf(',', ind1 + 1);
      int ind3 = gelenPaket.indexOf(',', ind2 + 1); // Basınç verisinin sonu
      int ind4 = gelenPaket.indexOf(',', ind3 + 1);
      int ind5 = gelenPaket.indexOf(',', ind4 + 1); // Yeni eklenen virgül

      // Veriyi parçalayıp Float'a çeviriyoruz
      
      // [BME280 VERİLERİ]
      // 1. Sıcaklık
      bmeSicaklik = gelenPaket.substring(0, ind1).toFloat();
      
      // 2. Nem
      bmeNem = gelenPaket.substring(ind1 + 1, ind2).toFloat();

      // 3. Basınç (YENİ EKLENEN)
      bmeBasinc = gelenPaket.substring(ind2 + 1, ind3).toFloat();
      
      // [MPU9250 VERİLERİ] - İndeksler kaydı
      // 4. X Ekseni
      mpuX = gelenPaket.substring(ind3 + 1, ind4).toFloat();
      
      // 5. Y Ekseni
      mpuY = gelenPaket.substring(ind4 + 1, ind5).toFloat();
      
      // 6. Z Ekseni
      mpuZ = gelenPaket.substring(ind5 + 1).toFloat();

      // --- EKRANA YAZDIRMA ---
      Serial.println("\n========= YENI VERI PAKETI =========");
      
      Serial.println("[ Kategori 1: ORTAM (BME280) ]");
      Serial.print("  Sicaklik : "); Serial.print(bmeSicaklik); Serial.println(" C");
      Serial.print("  Nem      : %"); Serial.println(bmeNem);
      Serial.print("  Basinc   : "); Serial.print(bmeBasinc); Serial.println(" hPa");

      Serial.println("[ Kategori 2: HAREKET (MPU9250) ]");
      Serial.print("  X Ekseni : "); Serial.println(mpuX);
      Serial.print("  Y Ekseni : "); Serial.println(mpuY);
      Serial.print("  Z Ekseni : "); Serial.println(mpuZ);
      
      Serial.println("====================================");
    }
  }
}