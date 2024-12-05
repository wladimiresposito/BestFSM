#ifndef SEQUENTIAL_H
#define SEQUENTIAL_H

#include <Arduino.h>
#include "fsm/State.h"

#undef FSM_DEBUG_STATE
#include "fsm/FSMDebug.h"

class LedState final : public State {
  uint8_t pin;

public:
    explicit LedState(const uint8_t led, const long timeout) : State(timeout), pin{led} {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }

    void onEnter(Event* event) const override {
        FSM_DEBUG_STATE_PRINT("on: ");
        FSM_DEBUG_STATE_PRINTLN(pin);
        digitalWrite(pin, HIGH);
        State::onEnter(event);
    }

    void onExit(Event* event) const override {
    	FSM_DEBUG_STATE_PRINT("off:");
        FSM_DEBUG_STATE_PRINTLN(pin);
    	digitalWrite(pin, LOW);
   		State::onExit(event);
    }

};

#endif


