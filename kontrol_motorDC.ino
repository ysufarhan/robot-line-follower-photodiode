// Program Robot dengan PWM Control (disesuaikan dengan L293D)
// Motor kiri: IN1 = D9 (PWM), IN2 = D6 (DIR)
// Motor kanan: IN3 = D5 (DIR), IN4 = D10 (PWM)

// Definisi pin motor
#define pin_pwm_motor_L 9    // IN1 - PWM motor kiri
#define pin_dir_motor_L 6    // IN2 - Arah motor kiri
#define pin_dir_motor_R 5    // IN3 - Arah motor kanan
#define pin_pwm_motor_R 10   // IN4 - PWM motor kanan

boolean RIGHT = 0;
boolean LEFT  = 0;

void polaritasMotor(boolean left, boolean right)
{
  LEFT  = left;
  RIGHT = right;
}

void setMotor(int PWM_L, int PWM_R)
{
  // Set polaritas motor (0 = normal, 1 = terbalik)
  polaritasMotor(0, 1);

  // Kontrol Motor Kanan
  if(RIGHT == 0)
  {
    if(PWM_R > 0)
    {
      digitalWrite(pin_dir_motor_R, LOW);
    }
    else
    {
      digitalWrite(pin_dir_motor_R, HIGH);
      PWM_R = 255 + PWM_R;
    }
    analogWrite(pin_pwm_motor_R, PWM_R);
  }
  else
  {
    if(PWM_R > 0)
    {
      digitalWrite(pin_pwm_motor_R, LOW);
    }
    else
    {
      digitalWrite(pin_pwm_motor_R, HIGH);
      PWM_R = 255 + PWM_R;
    }
    analogWrite(pin_dir_motor_R, PWM_R);
  }

  // Kontrol Motor Kiri
  if(LEFT == 0)
  {
    if(PWM_L > 0)
    {
      digitalWrite(pin_dir_motor_L, LOW);
    }
    else
    {
      digitalWrite(pin_dir_motor_L, HIGH);
      PWM_L = 255 + PWM_L;
    }
    analogWrite(pin_pwm_motor_L, PWM_L);
  }
  else
  {
    if(PWM_L > 0)
    {
      digitalWrite(pin_pwm_motor_L, LOW);
    }
    else
    {
      digitalWrite(pin_pwm_motor_L, HIGH);
      PWM_L = 255 + PWM_L;
    }
    analogWrite(pin_dir_motor_L, PWM_L);
  }
}

void setup() 
{
  // Set semua pin sebagai output
  pinMode(pin_pwm_motor_L, OUTPUT);
  pinMode(pin_dir_motor_L, OUTPUT);
  pinMode(pin_pwm_motor_R, OUTPUT);
  pinMode(pin_dir_motor_R, OUTPUT);
  
  // Gerakan robot mengikuti pola program teman
  setMotor(100, 100); // Maju lurus
  delay(2000);
  
  setMotor(100, 0);   // Belok kanan
  delay(300);
  
  setMotor(0, 0);     // Stop
  delay(1000);
  
  setMotor(100, 100); // Maju lurus
  delay(3000);
  
  setMotor(0, 100);   // Belok kiri
  delay(350);
  
  setMotor(0, 0);     // Stop
  delay(1000);
  
  setMotor(100, 100); // Maju lurus
  delay(2000);
  
  setMotor(100, -10); // Putar di tempat (kanan)
  delay(650);
  
  setMotor(0, 0);     // Stop
  delay(3000);
}

void loop() {
  // Kosong - robot hanya menjalankan sequence sekali di setup()
}
