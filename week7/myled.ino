#include <LedToggle.h>

LedToggle led(LED_BUILTIN);

void setup() {
}

void loop() {
  led.toggle();
  delay(500);
}
