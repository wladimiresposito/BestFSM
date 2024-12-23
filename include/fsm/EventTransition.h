//
// Created by wla on 08/11/2024.
//

#ifndef EVENT_TRANSITION_H
#define EVENT_TRANSITION_H

#include "Transition.h"
#include "events/BaseEventSource.h"
/**
 * @brief Event-based transition
 *
 * Transition that triggers based on specific events.
 * Has medium priority in transition checking.
 *
 * Key features:
 * - Event matching
 * - EventSource support
 * - Medium transition priority
 *
 * Usage:
 * @code
 * state->addTransition(new EventTransition(
 *     nextState,
 *     ButtonSource::buttonPressed()
 * ));
 * @endcode
 */
class EventTransition : public Transition {
    const Event* expectedEvent; ///< The event that triggers the transition.
    BaseEventSource* eventSource; ///< Source generating the events.


public:
    /**
     * Constructs an event transition.
     *
     * @param next Pointer to the next state.
     * @param event Pointer to the expected event.
     * @param source Pointer to the event source.
     */
    explicit EventTransition(State* next, const Event* event, BaseEventSource* source)
        : Transition(next), expectedEvent(event), eventSource(source) { }

    TransitionPriority getPriority() const override { return EVENT_TRANSITION; }

    bool isTriggered() override {
        // If there is not an expected event, return true
        // Event will never be nullptr, it will always have a value or Event::none
        // let's check the event
        Event *event = eventSource->getEvent();
        if (expectedEvent && event == expectedEvent) {
            setLastEvent(event);
            return true;
        }
        return false;
    }
};

#endif //EVENT_TRANSITION_H
