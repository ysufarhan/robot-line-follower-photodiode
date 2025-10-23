#include <EEPROM.h>

// Urutan channel fisik: ch(3, 0, 1, 2, 6, 5, 7, 4)
boolean A[8] = {1, 1, 1, 1, 0, 0, 0, 0};
boolean B[8] = {1, 1, 0, 0, 1, 1, 0, 0};  
boolean C[8] = {1, 0, 1, 0, 1, 0, 1, 0};

// Mapping urutan fisik ke urutan logis
int channelMapping[8] = {3, 0, 1, 2, 6, 5, 7, 4};

#define selectorA 4
#define selectorB 3
#define selectorC 2
#define sensor A0

#define EEPROM_CALIBRATION_FLAG 0
#define EEPROM_MIN_VALUES 10
#define EEPROM_MAX_VALUES 50
#define EEPROM_CALIBRATION_VALUES 90

unsigned int maxValue[8] = {0};
unsigned int minValue[8] = {1023};
unsigned int calibration[8];
byte dataSensorbyte = 0b00000000;

bool calibrationDone = false;

void loadCalibration();
void calculateThreshold();
void saveCalibration();
void readSensor();
void calibrateBlack();
void calibrateWhite();

void setup() {
  Serial.begin(9600);
  
  pinMode(selectorA, OUTPUT);
  pinMode(selectorB, OUTPUT);
  pinMode(selectorC, OUTPUT);
  pinMode(sensor, INPUT);
  
  if (EEPROM.read(EEPROM_CALIBRATION_FLAG) == 0xAA) {
    loadCalibration();
    calibrationDone = true;
  } else {
    Serial.println("CALIBRATE: Press 'w' for WHITE or 'b' for BLACK");
  }
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    if (command == 'b') {
      calibrateBlack();
    } else if (command == 'w') {
      calibrateWhite();
    }
  }
  
  if (calibrationDone) {
    readSensor();
    delay(50);
  }
}

void readSensor() {
  dataSensorbyte = 0b00000000;
  
  for(int logical_ch = 0; logical_ch < 8; logical_ch++) {
    int physical_ch = channelMapping[logical_ch];
    
    digitalWrite(selectorA, A[physical_ch]);
    digitalWrite(selectorB, B[physical_ch]);
    digitalWrite(selectorC, C[physical_ch]);
    delay(5); // Tambah delay agar pembacaan stabil

    int sensorValue = analogRead(sensor);

    if(sensorValue > calibration[logical_ch]) {
      dataSensorbyte |= (1 << (7 - logical_ch)); // Sensor kanan di bit 0
    }
  }

  for(int i = 7; i >= 0; i--) {
    Serial.print(bitRead(dataSensorbyte, i));
  }
  Serial.println();
}

void calibrateBlack() {
  for(int i = 0; i < 8; i++) {
    maxValue[i] = 0;
  }
  
  unsigned long startTime = millis();
  while(millis() - startTime <= 3000) {
    for(int logical_ch = 0; logical_ch < 8; logical_ch++) {
      int physical_ch = channelMapping[logical_ch];
      
      digitalWrite(selectorA, A[physical_ch]);
      digitalWrite(selectorB, B[physical_ch]);
      digitalWrite(selectorC, C[physical_ch]);
      delay(5);

      int sensorValue = analogRead(sensor);
      if(sensorValue > maxValue[logical_ch]) {
        maxValue[logical_ch] = sensorValue;
      }
    }
  }
  
  calculateThreshold();
  calibrationDone = true;
}

void calibrateWhite() {
  for(int i = 0; i < 8; i++) {
    minValue[i] = 1023;
  }
  
  unsigned long startTime = millis();
  while(millis() - startTime <= 3000) {
    for(int logical_ch = 0; logical_ch < 8; logical_ch++) {
      int physical_ch = channelMapping[logical_ch];
      
      digitalWrite(selectorA, A[physical_ch]);
      digitalWrite(selectorB, B[physical_ch]);
      digitalWrite(selectorC, C[physical_ch]);
      delay(5);

      int sensorValue = analogRead(sensor);
      if(sensorValue < minValue[logical_ch]) {
        minValue[logical_ch] = sensorValue;
      }
    }
  }
  
  calculateThreshold();
  calibrationDone = true;
}

void calculateThreshold() {
  for(int i = 0; i < 8; i++) {
    calibration[i] = (maxValue[i] + minValue[i]) / 2;
  }
  
  saveCalibration();
}

void saveCalibration() {
  EEPROM.write(EEPROM_CALIBRATION_FLAG, 0xAA);
  
  for (int i = 0; i < 8; i++) {
    EEPROM.put(EEPROM_MIN_VALUES + i * 2, minValue[i]);
    EEPROM.put(EEPROM_MAX_VALUES + i * 2, maxValue[i]);
    EEPROM.put(EEPROM_CALIBRATION_VALUES + i * 2, calibration[i]);
  }
}

void loadCalibration() {
  for (int i = 0; i < 8; i++) {
    EEPROM.get(EEPROM_MIN_VALUES + i * 2, minValue[i]);
    EEPROM.get(EEPROM_MAX_VALUES + i * 2, maxValue[i]);
    EEPROM.get(EEPROM_CALIBRATION_VALUES + i * 2, calibration[i]);
  }
}
