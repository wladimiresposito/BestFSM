//
// Created by wla on 24/12/24.
//

#ifndef SIMPLE_DOOR_CONTROLLER_H
#define SIMPLE_DOOR_CONTROLLER_H
/****************************************************
 * DoorController.ino
 *
 * Demonstrates an automated door FSM with states:
 * - Locked
 * - Unlocked
 * - Opening
 * - Closing
 *
 * Transitions are triggered by events (button presses).
 ****************************************************/

#include <Arduino.h>
#include "fsm/FSM.h"
#include "fsm/EventTransition.h"

// Suppose we have two push buttons for demonstration:
// 1) Lock/Unlock
// 2) Open/Close
// In a real system, these might be separate or more sophisticated inputs.

constexpr uint8_t LOCK_BUTTON_PIN    = 2;
constexpr uint8_t OPEN_BUTTON_PIN    = 3;
constexpr uint8_t LOCK_LED_PIN       = 13;  // LED to show door locked/unlocked

// We'll simulate two events for lock/unlock and open/close
// We'll do a raw read for simplicity or you can use DebouncedButtonEventSource
bool wasLockButtonPressed = false;
bool wasOpenButtonPressed = false;

/**
 * Helper function to check for button presses.
 * In real usage, consider debouncing or the library's DebouncedButtonEventSource.
 */
void checkButtons() {
    static bool lastLockState = HIGH;
    static bool lastOpenState = HIGH;

    bool currentLockState = digitalRead(LOCK_BUTTON_PIN);
    bool currentOpenState = digitalRead(OPEN_BUTTON_PIN);

    // On rising edge
    if (lastLockState == LOW && currentLockState == HIGH) {
        wasLockButtonPressed = true;
    }
    if (lastOpenState == LOW && currentOpenState == HIGH) {
        wasOpenButtonPressed = true;
    }

    lastLockState = currentLockState;
    lastOpenState = currentOpenState;
}

// Let's define our custom events
Event* lockToggleEvent = new Event(EventType::EVENT_CUSTOM, 1);
Event* openToggleEvent = new Event(EventType::EVENT_CUSTOM, 2);

// We'll track door states in 4 classes:
class LockedState : public State {
public:
    void onEnter(Event* ev) const override {
        Serial.println("Door is now LOCKED");
        digitalWrite(LOCK_LED_PIN, HIGH);  // LED ON for locked
        State::onEnter(ev);
    }
};

class UnlockedState : public State {
public:
    void onEnter(Event* ev) const override {
        Serial.println("Door is now UNLOCKED");
        digitalWrite(LOCK_LED_PIN, LOW); // LED OFF for unlocked
        State::onEnter(ev);
    }
};

class OpeningState : public State {
public:
    void onEnter(Event* ev) const override {
        Serial.println("Door is OPENING...");
        // In a real system, you'd drive a motor here
        State::onEnter(ev);
    }
    // Let's say for simplicity we automatically transition back to Unlocked after 3 seconds
};

class ClosingState : public State {
public:
    void onEnter(Event* ev) const override {
        Serial.println("Door is CLOSING...");
        // In a real system, you'd drive a motor here
        State::onEnter(ev);
    }
    // Similarly, we'd transition to Locked after 3 seconds or a sensor event
};

// We'll define an event source check function
class DoorEventSource : public BaseEventSource {
public:
    Event* getEvent() override {
        // If the lock button was pressed:
        if (wasLockButtonPressed) {
            wasLockButtonPressed = false;
            return lockToggleEvent;
        }
        // If the open button was pressed:
        if (wasOpenButtonPressed) {
            wasOpenButtonPressed = false;
            return openToggleEvent;
        }
        return Event::none;
    }
};

#endif //SIMPLE_DOOR_CONTROLLER_H
