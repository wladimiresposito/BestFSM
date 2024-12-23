/**
* Example demonstrating the use of a scheduler with periodic actions.
 *
 * Responsibilities:
 * - Schedules and executes `ActionLedOn` and `ActionLedOff` actions.
 *
 * Design Considerations:
 * - Utilizes `Scheduler` for periodic execution of actions.
 */

#include "blinkAction.h"
#include "actions/Scheduler.h"

auto actionLedOn = new ActionLedOn(); ///< Action for turning LED ON.
auto actionLedOff = new ActionLedOff(); ///< Action for turning LED OFF.
auto scheduler = new Scheduler(); ///< Scheduler managing the actions.

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    scheduler->addAction(actionLedOn)->addAction(actionLedOff);
}

void loop() {
    scheduler->run();
}
