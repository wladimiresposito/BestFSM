/**
 * Event source for debounced button inputs.
 *
 * Responsibilities:
 * - Processes raw button events with debounce logic.
 * - Generates press and release events for a single button or two-button setups.
 */

#ifndef DEBOUNCED_BUTTON_EVENT_SOURCE_H
#define DEBOUNCED_BUTTON_EVENT_SOURCE_H

#include "events/BaseEventSource.h"
#include "DebounceStates.h"
#include "events/RawButtonEventSource.h"
#include "fsm/EventTransition.h"
#include "fsm/StateTimeoutTransition.h"
#include "fsm/FSM.h"

class DebouncedButtonEventSource final : public BaseEventSource {
    uint8_t pin; ///< Pin number connected to the button.

    RawButtonEventSource* rawButton; ///< Event source for raw button inputs.
    FSM* debounceFsm; ///< FSM handling debounce logic.

    WaitPressState* waitPress; ///< State for waiting for a button press.
    DebouncingState* debouncing; ///< State for handling debounce.
    PressedState* pressed; ///< State for a pressed button.

    enum ButtonState {
        UNPRESSED,
        PRESSED
    };

    ButtonState buttonState; ///< Current debounced button state.
    ButtonState lastState; ///< Previous debounced button state.

    /**
     * @brief Creates a finite state machine (FSM) for handling button press events.
     *
     * The FSM consists of three states: waitPress, debouncing, and pressed. The transitions
     * between these states are triggered by button press events and timeouts.
     *
     * @return FSM* A pointer to the constructed FSM starting in the waitPress state.
     */
    FSM* getFSM() {
        // Transition from waitPress to debouncing state when a buttonPressed event occurs.
        waitPress->addTransition(new EventTransition(debouncing, Event::buttonPressed, rawButton));

        // Transition from debouncing to pressed state based on a timeout event.
        debouncing->addTransition(new StateTimeoutTransition(pressed));

        // Transition from pressed back to waitPress state when a buttonReleased event occurs.
        pressed->addTransition(new EventTransition(waitPress, Event::buttonReleased, rawButton));

        // Create the FSM starting in the waitPress state.
        FSM* theFsm = new FSM(waitPress);
        return theFsm;
    }

public:
    /**
     * Constructs a debounced button event source.
     *
     * @param pin Pin number connected to the button.
     * @param debounceTime Debounce duration in milliseconds.
     */
    explicit DebouncedButtonEventSource(const uint8_t pin, const unsigned long debounceTime = DEBOUNCE_TIME):
          pin{pin},
          rawButton{new RawButtonEventSource(pin)},
          buttonState{UNPRESSED},
          lastState{UNPRESSED} {

        waitPress  = new WaitPressState();
        debouncing = new DebouncingState(debounceTime);
        pressed    = new PressedState();

        debounceFsm = getFSM();
        debounceFsm->start();

    }

    /**
     * Retrieves the current button event.
     *
     * Behavior:
     * - Generates `buttonPressed` or `buttonReleased` events based on the debounce state.
     *
     * @return Pointer to the generated event or `Event::none` if no event occurred.
     */
    Event* getEvent() override {
        debounceFsm->run();

        buttonState = (debounceFsm->getCurrentState() == pressed) ? PRESSED : UNPRESSED;

        if (buttonState != lastState) {
            lastState = buttonState;
            return (buttonState == PRESSED) ?
                   Event::buttonPressed->setByteValue(pin) :
                   Event::buttonReleased->setByteValue(pin);
        }

        return Event::none;
    }

    /**
     * Retrieves the pin number connected to the button.
     *
     * @return The pin number.
     */
    uint8_t getPin() const { return pin; }
};

#endif
