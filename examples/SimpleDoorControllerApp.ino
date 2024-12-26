//
// Created by wla on 24/12/24.
//

#include "SimpleDoorController.h"
#include "fsm/StateTimeoutTransition.h"

// Create global states
LockedState* lockedState = new LockedState();
UnlockedState* unlockedState = new UnlockedState();
OpeningState* openingState = new OpeningState();
ClosingState* closingState = new ClosingState();

DoorEventSource* doorEventSource = new DoorEventSource();

// Transitions
// Define them in setupTransitions(), referencing the states
void setupTransitions() {
    // locked -> unlocked if lockToggleEvent is triggered
    lockedState->addTransition(new EventTransition(unlockedState, lockToggleEvent, doorEventSource));

    // unlocked -> locked if lockToggleEvent is triggered
    // but let's do that from the closing state
    // we can also do direct transitions from unlocked to locked if we prefer
    // for this example, let's say you have to press "Close" to lock
    // so the lock button toggles lock/unlock,
    // the open button toggles open/close.

    // unlocked -> opening if openToggleEvent is triggered
    unlockedState->addTransition(new EventTransition(openingState, openToggleEvent, doorEventSource));

    // opening -> unlocked after 3 seconds
    openingState->addTransition(new StateTimeoutTransition(unlockedState));

    // unlocked -> closing if openToggleEvent is triggered again
    // re-press the open button to close
    // or define a separate close button event. We'll reuse the same for simplicity
    unlockedState->addTransition(new EventTransition(closingState, openToggleEvent, doorEventSource));

    // closing -> locked after 3 seconds
    closingState->addTransition(new StateTimeoutTransition(lockedState));
}

// FSM pointer
FSM* doorFsm = nullptr;

void setup() {
    Serial.begin(9600);
    pinMode(LOCK_BUTTON_PIN, INPUT_PULLUP);
    pinMode(OPEN_BUTTON_PIN, INPUT_PULLUP);
    pinMode(LOCK_LED_PIN, OUTPUT);

    // Setup transitions
    setupTransitions();

    // Create an FSM with locked as the initial state
    doorFsm = new FSM(lockedState);
    doorFsm->start();
}

void loop() {
    // Check for button presses
    checkButtons();

    // Run the FSM
    doorFsm->run();
}