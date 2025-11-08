// === Definisi Pin Motor (L293D) ===
// Motor kiri
#define IN1 9   // arah 1
#define IN2 6   // arah 2
// Motor kanan
#define IN3 5   // arah 1
#define IN4 10  // arah 2

// === Variabel arah motor ===
boolean LEFT  = 0;
boolean RIGHT = 0;

// Fungsi untuk mengatur polaritas motor (kalau arah terbalik, ubah di sini)
void polaritasMotor(boolean left, boolean right)
{
  LEFT  = left;
  RIGHT = right;
}

// Fungsi untuk mengatur arah motor (tanpa PWM, karena ENA & ENB langsung ke +5V)
void setMotor(int PWM_L, int PWM_R)
{
  // polaritas default
  polaritasMotor(0, 1);

  // --- MOTOR KANAN ---
  if (RIGHT == 0) {
    if (PWM_R >= 0) {
      digitalWrite(IN3, HIGH);   // maju
      digitalWrite(IN4, LOW);
    } else {
      digitalWrite(IN3, LOW);    // mundur
      digitalWrite(IN4, HIGH);
    }
  } 
  else { // polaritas dibalik
    if (PWM_R >= 0) {
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else {
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
  }

  // --- MOTOR KIRI ---
  if (LEFT == 0) {
    if (PWM_L >= 0) {
      digitalWrite(IN1, HIGH);   // maju
      digitalWrite(IN2, LOW);
    } else {
      digitalWrite(IN1, LOW);    // mundur
      digitalWrite(IN2, HIGH);
    }
  } 
  else { // polaritas dibalik
    if (PWM_L >= 0) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    } else {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
  }
}

void setup() 
{
  // Inisialisasi pin
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Tes motor seperti program 1 versi L293D
  setMotor(1, 1);     // maju
  delay(2000);
  setMotor(1, -1);    // belok kanan
  delay(2000);
  setMotor(0, 0);     // stop
}

void loop() 
{
  // Kosong dulu
}
