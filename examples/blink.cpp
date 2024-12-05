/**
* Example implementation of an FSM for controlling an LED.
 *
 * Responsibilities:
 * - Demonstrates state-based control for LED on/off behavior.
 * - Uses `StateTimeoutTransition` to switch between states based on time.
 */

#include "blink.h"
#include "fsm/StateTimeoutTransition.h"
#include "fsm/FSM.h"

constexpr unsigned long ON_TIME = 3000; ///< LED ON time in milliseconds.
constexpr unsigned long OFF_TIME = 1000; ///< LED OFF time in milliseconds.

auto stateOn = new LedOnState(ON_TIME); ///< State for LED ON.
auto stateOff = new LedOffState(OFF_TIME); ///< State for LED OFF.

auto toOff = new StateTimeoutTransition(stateOff); ///< Transition to LED OFF state.
auto toOn = new StateTimeoutTransition(stateOn); ///< Transition to LED ON state.

auto fsm = new FSM(stateOn); ///< FSM controlling the LED states.

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);

    stateOff->addTransition(toOn);
    stateOn->addTransition(toOff);

    fsm->start();
}

void loop() {
    fsm->run();
}
