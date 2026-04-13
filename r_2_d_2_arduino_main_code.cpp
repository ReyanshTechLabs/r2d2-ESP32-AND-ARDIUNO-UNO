/*
  R2-D2 UNO MAIN CODE (Optimized)
  Arduino UNO + L293D + PIR + ESP32
*/

#include <SoftwareSerial.h>

// ESP32 Serial
SoftwareSerial espSerial(7, 8); // RX, TX

// Motor Pins
#define ENA 5
#define IN1 2
#define IN2 3
#define ENB 6
#define IN3 4
#define IN4 9

// PIR Sensor
#define PIR_PIN 10

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(PIR_PIN, INPUT);

  stopMotors();

  Serial.println("R2-D2 UNO READY");
}

void loop() {
  checkPIR();
  readESP32();
}

// -------- MOTOR CONTROL --------
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// -------- PIR SENSOR --------
void checkPIR() {
  if (digitalRead(PIR_PIN) == HIGH) {
    Serial.println("Motion Detected");
    espSerial.println("MOTION");
  }
}

// -------- ESP32 COMMANDS --------
void readESP32() {
  if (espSerial.available()) {
    char cmd = espSerial.read();

    switch (cmd) {
      case 'F': forward(); break;
      case 'B': backward(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      case 'S': stopMotors(); break;
      default: stopMotors(); break;
    }
  }
}
