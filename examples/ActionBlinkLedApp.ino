/**
* Example implementation of a periodic action to blink an LED.
 *
 * Responsibilities:
 * - Configures an LED pin and manages its blinking using a periodic action.
 *
 * Design Considerations:
 * - Relies on `ActionBlinkLed` for the periodic blinking logic.
 */
#include "ActionBlinkLed.h"

constexpr uint8_t LED_PIN = 13; ///< Pin number for the LED.

auto actionBlinkLed = new ActionBlinkLed(LED_PIN, 500); ///< Instance of `ActionBlinkLed`.

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    actionBlinkLed->execute();
}
