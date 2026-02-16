#include <IRremote.h>

const int recv = 2; // IR Receiver pin
const int m1L = 3, m1R = 4, m2L = 5, m2R = 6; // Motor pins
const int leftLED = 9, rightLED = 11;

int state = 0; // 0:stop, 1:fwd, 2:back, 3:left, 4:right
unsigned long timer = 0;
const unsigned long runTime = 3000; // Auto-stop after 3s

void setup() {
  IrReceiver.begin(recv);
  pinMode(m1L, OUTPUT); pinMode(m1R, OUTPUT);
  pinMode(m2L, OUTPUT); pinMode(m2R, OUTPUT);
  pinMode(leftLED, OUTPUT); pinMode(rightLED, OUTPUT);
}

void loop() {
  // 1. Check for IR signals
  if (IrReceiver.decode()) {
    unsigned long cmd = IrReceiver.decodedIRData.command;

    if (cmd == 0x18)      state = 1; // UP (Update these hex codes
    else if (cmd == 0x52) state = 2; // DOWN based on your specific
    else if (cmd == 0x8)  state = 3; // LEFT remote's output)
    else if (cmd == 0x5A) state = 4; // RIGHT
    else if (cmd == 0x1C) state = 0; // OK/STOP

    timer = millis(); // Reset timer on every valid press
    IrReceiver.resume();
  }

  // 2. Safety Timeout
  if (millis() - timer > runTime) state = 0;

  // 3. Execute Movement
  if (state == 1) { // Forward
    digitalWrite(m1L, HIGH); digitalWrite(m1R, LOW);
    digitalWrite(m2L, HIGH); digitalWrite(m2R, LOW);
    digitalWrite(leftLED, HIGH); digitalWrite(rightLED, HIGH);
  } 
  else if (state == 2) { // Backward
    digitalWrite(m1L, LOW);  digitalWrite(m1R, HIGH);
    digitalWrite(m2L, LOW);  digitalWrite(m2R, HIGH);
    digitalWrite(leftLED, HIGH); digitalWrite(rightLED, HIGH);
  } 
  else if (state == 3) { // Left turn
    digitalWrite(m1L, HIGH); digitalWrite(m2R, HIGH);
    digitalWrite(leftLED, HIGH); digitalWrite(rightLED, LOW);
  } 
  else if (state == 4) { // Right turn
    digitalWrite(m1R, HIGH); digitalWrite(m2L, HIGH);
    digitalWrite(leftLED, LOW);  digitalWrite(rightLED, HIGH);
  } 
  else { // Stop
    digitalWrite(m1L, LOW);  digitalWrite(m1R, LOW);
    digitalWrite(m2L, LOW);  digitalWrite(m2R, LOW);
    digitalWrite(leftLED, HIGH); digitalWrite(rightLED, HIGH);
  }
}
