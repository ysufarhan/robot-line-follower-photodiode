// Pin kontrol motor
#define ENA 5    // Enable motor kiri (PWM)
#define IN1 6    // Arah motor kiri
#define IN2 7
#define ENB 9    // Enable motor kanan (PWM)
#define IN3 10   // Arah motor kanan
#define IN4 11

int speedMotor = 180;  // kecepatan (0–255)

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  Serial.println("Kontrol Motor Sederhana Siap!");
}

void loop() {
  // Contoh urutan gerak otomatis
  maju();
  delay(2000);

  kanan();
  delay(1000);

  kiri();
  delay(1000);

  berhenti();
  delay(2000);
}

// ====== FUNGSI MOTOR ======

void maju() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
  Serial.println("F");
}

void kanan() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speedMotor);
  analogWrite(ENB, 0);
  Serial.println("R");
}

void kiri() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, speedMotor);
  Serial.println("L");
}

void berhenti() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  Serial.println("S");
}
