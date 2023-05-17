#include <Arduino.h>
#include "petzeira.hpp"

Petzeira* petzeira = nullptr;

void setup() {
  Serial.begin(9600);

  //Waiting for Serial Monitor to open
  while (!Serial); 

  petzeira = new Petzeira();
  petzeira->setup();
}

void loop() {
  delay(1000);
}