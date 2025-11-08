// Program: Dua Motor Maju (L293D + Arduino Nano)
// Enable A dan B dihubungkan langsung ke +5V
// Motor kiri: IN1 = D9, IN2 = D6
// Motor kanan: IN3 = D5, IN4 = D10

// Definisi pin motor
const int IN1 = 9;   // Motor kiri
const int IN2 = 6;
const int IN3 = 5;   // Motor kanan
const int IN4 = 10;

void setup() {
  // Set pin sebagai output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Motor maju
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void loop() {
  // Tidak ada perulangan, motor terus maju
}
