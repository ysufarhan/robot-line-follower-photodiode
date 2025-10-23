#include <EEPROM.h>

// Konfigurasi pin selector multiplexer
#define selectorA 4
#define selectorB 3
#define selectorC 2
#define sensor A0

// Kombinasi bit untuk 8 channel (A, B, C)
boolean A[8] = {1, 1, 1, 1, 0, 0, 0, 0};
boolean B[8] = {1, 1, 0, 0, 1, 1, 0, 0};
boolean C[8] = {1, 0, 1, 0, 1, 0, 1, 0};

// Urutan channel fisik ke urutan logis
int channelMapping[8] = {3, 0, 1, 2, 6, 5, 7, 4};

unsigned int readSensor[8];
int threshold = 500;  // contoh nilai ambang
int i;

void setup() {
  Serial.begin(9600);

  pinMode(selectorA, OUTPUT);
  pinMode(selectorB, OUTPUT);
  pinMode(selectorC, OUTPUT);
  pinMode(sensor, INPUT);
}

void loop() {
  read_sensor();

  // Tampilkan hasil pembacaan di Serial Monitor
  Serial.print("Data Sensor: ");
  for (i = 0; i < 8; i++) {
    Serial.print(readSensor[i]);
    Serial.print(" ");
  }
  Serial.println();

  delay(1000);
}

void read_sensor() {
  for (i = 0; i < 8; i++) {
    // Pilih channel multiplexer
    digitalWrite(selectorA, A[i]);
    digitalWrite(selectorB, B[i]);
    digitalWrite(selectorC, C[i]);
    delay(20);

    // Baca nilai dari channel fisik tertentu,
    // lalu simpan ke urutan logis sesuai mapping
    int logicalIndex = channelMapping[i];
    readSensor[logicalIndex] = analogRead(sensor);

    // Contoh penggunaan threshold (opsional)
    if (readSensor[logicalIndex] > threshold) {
      // Misal: simpan atau kirim data
    }
  }
}
