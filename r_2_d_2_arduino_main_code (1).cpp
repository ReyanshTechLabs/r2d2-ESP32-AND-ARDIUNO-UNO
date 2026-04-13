/*
  R2-D2 SYSTEM
  --------------------------------------
  FILE 1: Arduino UNO (Motor + PIR)
  FILE 2: ESP32 MASTER (Bluetooth Controller)

  Upload THIS section to ESP32
*/

// ===== ESP32 MASTER CODE =====
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

char incoming;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("R2D2-ESP32"); // Bluetooth name

  Serial.println("ESP32 Master Ready");
}

void loop() {
  // Read from phone via Bluetooth
  if (SerialBT.available()) {
    incoming = SerialBT.read();

    Serial.print("BT Command: ");
    Serial.println(incoming);

    // Send to Arduino UNO via Serial
    Serial.write(incoming);
  }

  // Read from Arduino (like PIR alerts)
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');

    Serial.print("UNO: ");
    Serial.println(msg);

    // Send alert back to phone
    SerialBT.println(msg);
  }
}

/*
  -------- HOW IT WORKS --------

  PHONE (Bluetooth App)
        ↓
      ESP32  →  Arduino UNO  → Motors
        ↑
     Sensor Alerts (PIR)

  -------- COMMANDS --------
  F = Forward
  B = Backward
  L = Left
  R = Right
  S = Stop

*/
