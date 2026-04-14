#include <Arduino.h>

const int doNow_pin = 10;
const int signalTimer_pin = 9;

unsigned long runInterval = 10000;
unsigned long cooldownInterval = 5000;

unsigned long prevMillisInterval = 0;
unsigned long prevMillisCooldown = 0;

int to_fro_Flag = 0;
int cooldown_state = 0;   // 0 = cooldown, 1 = run

void toFunction();
void froFunction();

void setup() {
  Serial.begin(9600);
  pinMode(signalTimer_pin, OUTPUT);
  pinMode(doNow_pin, INPUT_PULLUP);

  prevMillisCooldown = millis();  // start in cooldown
}

void loop() {
  unsigned long now = millis();

  if (cooldown_state == 0) {
    digitalWrite(signalTimer_pin, LOW);

    if (now - prevMillisCooldown >= cooldownInterval) {
      digitalWrite(signalTimer_pin, HIGH);
      cooldown_state = 1;
      prevMillisInterval = now;   // start run timer
    }
  }

  else if (cooldown_state == 1) {
    while (digitalRead(doNow_pin) == HIGH) {   // kept as requested
      if (to_fro_Flag % 2 == 0) {
        toFunction();
      }
      else if (to_fro_Flag % 2 == 1) {
        froFunction();
      }

      if (millis() - prevMillisInterval >= runInterval) {
        cooldown_state = 0;
        to_fro_Flag = to_fro_Flag + 1;
        prevMillisCooldown = millis();   // start cooldown timer
        break;
      }
    }

    // optional: if pin stops being HIGH, leave run mode or keep it armed
    if (digitalRead(doNow_pin) != HIGH) {
      // choose behavior here if needed
    }
  }
}

void toFunction() {
  Serial.println("TO");
  delay(500);
}

void froFunction() {
  Serial.println("FRO");
  delay(500);
}