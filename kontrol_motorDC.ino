#define IN1 9
#define IN2 6
#define IN3 5
#define IN4 10

boolean LEFT = 0;
boolean RIGHT = 0;

void polaritasMotor(boolean left, boolean right) {
  LEFT = left;
  RIGHT = right;
}

void setMotor(int PWM_L, int PWM_R) {
  polaritasMotor(1, 0);

  if (RIGHT == 0) {
    if (PWM_R > 0) { digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); }
    else if (PWM_R < 0) { digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); }
    else { digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); }
  } else {
    if (PWM_R > 0) { digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); }
    else if (PWM_R < 0) { digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); }
    else { digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); }
  }

  if (LEFT == 0) {
    if (PWM_L > 0) { digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); }
    else if (PWM_L < 0) { digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); }
    else { digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); }
  } else {
    if (PWM_L > 0) { digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); }
    else if (PWM_L < 0) { digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); }
    else { digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); }
  }
}

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  setMotor(1, 1); delay(2000);
  setMotor(1, -1); delay(600);
  setMotor(1, 1); delay(2000);
  setMotor(-1, 1); delay(600);
  setMotor(1, -1); delay(1000);
  setMotor(0, 0);
}

void loop() {}
