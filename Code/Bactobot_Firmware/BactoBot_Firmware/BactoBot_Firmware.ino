// Fixed sequence: M1 CW 40s, M3 CCW 40s, M2 CCW 20s then CW 20s

// Motor 1 pins
const int M1_RPWM = 2;
const int M1_LPWM = 3;
const int M1_R_EN = 22;
const int M1_L_EN = 23;

// Motor 2 pins
const int M2_RPWM = 4;
const int M2_LPWM = 5;
const int M2_R_EN = 24;
const int M2_L_EN = 25;

// Motor 3 pins
const int M3_RPWM = 6;
const int M3_LPWM = 7;
const int M3_R_EN = 26;
const int M3_L_EN = 27;

// Motor speed (0-255)
const int motorSpeed = 200;

// Simple timing variables
unsigned long startTime = 0;

void setup() {
  // Initialize all pins as outputs
  pinMode(M1_RPWM, OUTPUT);
  pinMode(M1_LPWM, OUTPUT);
  pinMode(M1_R_EN, OUTPUT);
  pinMode(M1_L_EN, OUTPUT);
  
  pinMode(M2_RPWM, OUTPUT);
  pinMode(M2_LPWM, OUTPUT);
  pinMode(M2_R_EN, OUTPUT);
  pinMode(M2_L_EN, OUTPUT);
  
  pinMode(M3_RPWM, OUTPUT);
  pinMode(M3_LPWM, OUTPUT);
  pinMode(M3_R_EN, OUTPUT);
  pinMode(M3_L_EN, OUTPUT);
  
  // Enable all motors
  digitalWrite(M1_R_EN, HIGH);
  digitalWrite(M1_L_EN, HIGH);
  digitalWrite(M2_R_EN, HIGH);
  digitalWrite(M2_L_EN, HIGH);
  digitalWrite(M3_R_EN, HIGH);
  digitalWrite(M3_L_EN, HIGH);
  
  // Initialize serial
  Serial.begin(9600);
  Serial.println("Motor Control Started - Arduino Mega");
  
  // Start timing
  startTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;
  
  // Reset after 40 seconds
  if (elapsedTime >= 40000) {
    startTime = currentTime; // Use currentTime instead of millis() again
    Serial.println("Cycle restarted");
    return; // Exit this loop iteration to start fresh
  }
  
  // Motor 1: Always CW for full 40 seconds
  analogWrite(M1_RPWM, motorSpeed);
  analogWrite(M1_LPWM, 0);
  
  // Motor 3: Always CCW for full 40 seconds
  analogWrite(M3_RPWM, 0);
  analogWrite(M3_LPWM, motorSpeed);
  
  // Motor 2: CCW for first 20 seconds, then CW for next 20 seconds
  if (elapsedTime < 20000) {
    // First 20 seconds: Motor 2 CCW
    analogWrite(M2_RPWM, 0);
    analogWrite(M2_LPWM, motorSpeed);
    
    // Debug output at specific intervals
    if (elapsedTime == 0 || (elapsedTime > 0 && elapsedTime % 5000 < 50)) {
      Serial.print("Time: ");
      Serial.print(elapsedTime/1000);
      Serial.println("s - M1=CW, M2=CCW, M3=CCW");
    }
  } else {
    // Next 20 seconds: Motor 2 CW
    analogWrite(M2_RPWM, motorSpeed);
    analogWrite(M2_LPWM, 0);
    
    // Debug output at specific intervals
    if ((elapsedTime >= 20000 && elapsedTime < 20050) || (elapsedTime > 20000 && (elapsedTime - 20000) % 5000 < 50)) {
      Serial.print("Time: ");
      Serial.print(elapsedTime/1000);
      Serial.println("s - M1=CW, M2=CW, M3=CCW");
    }
  }
}

