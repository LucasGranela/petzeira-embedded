// #ifdef EMBEDDED

#include <Arduino.h>
#include "petzeira.h"
#include "staticconfig.h"

Petzeira* petzeira = nullptr;

void setup() {
  #ifdef SERIAL_ENABLED
    Serial.begin(115200);

    while (!Serial);

    Serial.println("[MAIN - setup] - INFO: setting up");
  #endif

  petzeira = new Petzeira();
  petzeira->setup();
  petzeira->start();

  #ifdef SERIAL_ENABLED
    Serial.println("[MAIN - setup] - INFO: setup finished");
  #endif
}

void loop() {
  petzeira->loop();
}