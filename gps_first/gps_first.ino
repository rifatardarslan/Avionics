#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Bağlantı Pinleri
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// Nesneler
TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);

  Serial.println(F("----------------------------------------"));
  Serial.println(F("GPS DECODER BASLATILDI"));
  Serial.println(F("Veriler isleniyor, lutfen bekleyin..."));
  Serial.println(F("----------------------------------------"));
}

void loop() {
  // GPS'ten veri geldikçe karakter karakter oku ve decode et
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      displayInfo(); // Her yeni geçerli veri paketinde ekrana yaz
    }
  }

  // Bağlantı kontrolü (5 saniye veri gelmezse)
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(F("HATA: GPS modulu ile iletisim yok!"));
    Serial.println(F("Kablolari (RX/TX) kontrol edin."));
    while(true);
  }
}

void displayInfo() {
  // --- UYDU DURUMU ---
  Serial.print(F("Bagli Uydu Sayisi: "));
  if (gps.satellites.isValid()) {
    Serial.print(gps.satellites.value());
  } else {
    Serial.print(F("-"));
  }

  // --- KONUM DURUMU ---
  Serial.print(F(" | Konum: "));
  if (gps.location.isValid()) {
    // Konum bulunduysa koordinatları yaz
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(", "));
    Serial.print(gps.location.lng(), 6);
  } else {
    // Henüz konum bulunamadıysa
    Serial.print(F("ARANIYOR... (Sinyal Bekleniyor)"));
  }

  // --- SAAT/TARIH (Genelde konumdan önce gelir) ---
  Serial.print(F(" | Saat: "));
  if (gps.time.isValid()) {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
  } else {
    Serial.print(F("--:--:--"));
  }

  Serial.println(); // Alt satıra geç
}