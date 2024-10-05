#include <DHT.h>

// Definisi pin dan tipe sensor
#define DHTPIN 2          // Pin untuk sensor DHT22 terhubung
#define DHTTYPE DHT22     // Jenis sensor DHT

// Inisialisasi sensor DHT
DHT dht(DHTPIN, DHTTYPE);

const int humidifierPin = 8; // Pin kontrol untuk relay humidifier
const int humidityThresholdLow = 40; // Batas bawah kelembapan (%)
const int humidityThresholdHigh = 60; // Batas atas kelembapan (%)

void setup() {
  Serial.begin(9600);      // Memulai komunikasi serial
  dht.begin();             // Memulai sensor DHT22
  pinMode(humidifierPin, OUTPUT); // Mengatur pin humidifier sebagai output
  digitalWrite(humidifierPin, LOW); // Matikan humidifier saat awal
}

void loop() {
  // Baca kelembapan dari sensor DHT22
  float humidity = dht.readHumidity();
  
  // Periksa apakah pembacaan dari sensor berhasil
  if (isnan(humidity)) {
    Serial.println("Gagal membaca data dari sensor DHT22!");
    return;
  }

  // Kontrol humidifier berdasarkan kelembapan
  if (humidity < humidityThresholdLow) {
    digitalWrite(humidifierPin, HIGH); // Nyalakan relay untuk humidifier
    Serial.println("Humidifier ON");
  } else if (humidity > humidityThresholdHigh) {
    digitalWrite(humidifierPin, LOW); // Matikan relay untuk humidifier
    Serial.println("Humidifier OFF");
  }

  // Tampilkan nilai kelembapan di Serial Monitor
  Serial.print("Kelembapan: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(2000); // Tunggu selama 2 detik sebelum pembacaan ulang
}
