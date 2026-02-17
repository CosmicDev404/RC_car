#include <IRremote.h>

const int recv = 2;

IRrecv irrecv(recv);
decode_results results;

// Motor pins
const int m1L = 3, m1R = 4;
const int m2L = 5, m2R = 6;

// LEDs
const int leftLED = 9;
const int rightLED = 11;

// Movement state
int state = 0;   // default = STOP

unsigned long timer = 0;
const unsigned long runTime = 3000; // 3 seconds

// ===================================

void setup() {

  pinMode(m1L, OUTPUT);
  pinMode(m1R, OUTPUT);
  pinMode(m2L, OUTPUT);
  pinMode(m2R, OUTPUT);

  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);

  Serial.begin(9600);

  irrecv.enableIRIn(); // start IR receiver
}

// ===================================

void loop() {

  // ---- READ REMOTE ----
  if (irrecv.decode(&results)) {

    unsigned long cmd = results.value;

    if (cmd != 0xFFFFFFFF) {

      // FORWARD
      if (cmd == 0x2FD9867) {
        state = 1;
        timer = millis();
      }

      // BACKWARD
      else if (cmd == 0x2FDB847) {
        state = 2;
        timer = millis();
      }

      // LEFT
      else if (cmd == 0x2FD42BD) {
        state = 3;
        timer = millis();
      }

      // RIGHT
      else if (cmd == 0x2FD02FD) {
        state = 4;
        timer = millis();
      }

      // STOP BUTTON
      else if (cmd == 0x2FD847B) {
        state = 0;
      }

      // UNKNOWN BUTTON → STOP (default safety)
      else {
        state = 0;
      }
    }

    irrecv.resume();
  }

  // ---- AUTO STOP TIMER ----
  if (millis() - timer > runTime) {
    state = 0;
  }

  // ---- MOVEMENT CONTROL ----

  // FORWARD
  if (state == 1) {
    digitalWrite(m1L, HIGH);
    digitalWrite(m1R, LOW);
    digitalWrite(m2L, HIGH);
    digitalWrite(m2R, LOW);
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, LOW);
  }

  // BACKWARD
  else if (state == 2) {
    digitalWrite(m1L, LOW);
    digitalWrite(m1R, HIGH);
    digitalWrite(m2L, LOW);
    digitalWrite(m2R, HIGH);
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, LOW);
  }

  // LEFT
  else if (state == 3) {
    digitalWrite(m1L, HIGH);
    digitalWrite(m2R, HIGH);
    digitalWrite(leftLED, HIGH);
    digitalWrite(rightLED, LOW);
  }

  // RIGHT
  else if (state == 4) {
    digitalWrite(m1R, HIGH);
    digitalWrite(m2L, HIGH);
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, HIGH);
  }

  // DEFAULT → STOP
  else {
    digitalWrite(m1L, LOW);
    digitalWrite(m1R, LOW);
    digitalWrite(m2L, LOW);
    digitalWrite(m2R, LOW);
    digitalWrite(leftLED, HIGH);
    digitalWrite(rightLED, HIGH);
  }
}
