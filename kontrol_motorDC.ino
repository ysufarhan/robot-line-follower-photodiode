// === Definisi Pin Motor ===
#define pin_pwm_motor_L 6     // ENA (L298N kiri)
#define pin_dir_motor_L 9     // IN1
#define pin_pwm_motor_R 5     // ENB (L298N kanan)
#define pin_dir_motor_R 10    // IN3

// === Variabel arah motor ===
boolean LEFT  = 0;
boolean RIGHT = 0;

// Fungsi untuk atur polaritas motor (kalau arah salah, ubah di sini)
void polaritasMotor(boolean left, boolean right)
{
  LEFT  = left;
  RIGHT = right;
}

// Fungsi utama untuk mengatur kecepatan & arah motor
void setMotor(int PWM_L, int PWM_R)
{
  // Set polaritas default (ubah sesuai arah putar motor)
  polaritasMotor(0, 1);

  // --- MOTOR KANAN ---
  if (RIGHT == 0) {
    if (PWM_R >= 0) {
      digitalWrite(pin_dir_motor_R, HIGH);   // arah maju
    } else {
      digitalWrite(pin_dir_motor_R, LOW);    // arah mundur
      PWM_R = -PWM_R; // ubah jadi positif
    }
    analogWrite(pin_pwm_motor_R, constrain(PWM_R, 0, 255));
  } 
  else { // Jika polaritas dibalik
    if (PWM_R >= 0) {
      digitalWrite(pin_dir_motor_R, LOW);
    } else {
      digitalWrite(pin_dir_motor_R, HIGH);
      PWM_R = -PWM_R;
    }
    analogWrite(pin_pwm_motor_R, constrain(PWM_R, 0, 255));
  }

  // --- MOTOR KIRI ---
  if (LEFT == 0) {
    if (PWM_L >= 0) {
      digitalWrite(pin_dir_motor_L, HIGH);   // arah maju
    } else {
      digitalWrite(pin_dir_motor_L, LOW);    // arah mundur
      PWM_L = -PWM_L;
    }
    analogWrite(pin_pwm_motor_L, constrain(PWM_L, 0, 255));
  } 
  else { // Jika polaritas dibalik
    if (PWM_L >= 0) {
      digitalWrite(pin_dir_motor_L, LOW);
    } else {
      digitalWrite(pin_dir_motor_L, HIGH);
      PWM_L = -PWM_L;
    }
    analogWrite(pin_pwm_motor_L, constrain(PWM_L, 0, 255));
  }
}

void setup() 
{
  // Inisialisasi pin
  pinMode(pin_pwm_motor_L, OUTPUT);
  pinMode(pin_dir_motor_L, OUTPUT);
  pinMode(pin_pwm_motor_R, OUTPUT);
  pinMode(pin_dir_motor_R, OUTPUT);

  // Tes motor
  setMotor(100, 100);   // maju pelan
  delay(2000);
  setMotor(150, -30);   // belok kanan
  delay(2000);
  setMotor(0, 0);       // stop
}

void loop() 
{
  // Kosong dulu
}
