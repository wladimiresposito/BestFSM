#ifndef TRANSITION_H
#define TRANSITION_H

#include <Arduino.h>
#include "events/Event.h"
#include "fsm/State.h"

// Transition types
enum TransitionPriority : uint8_t {
    PRIORITY_TRANSITION    = 0,
    CONDITION_TRANSITION   = 1,
    EVENT_TRANSITION       = 2,
    TIMEOUT_TRANSITION     = 3,
    IMMEDIATE_TRANSITION   = 4
};
/**
 * @brief Base class for state transitions
 *
 * Manages transition between states in the FSM. Each transition has a target
 * state and can have its own EventSource. Transitions are typed and follow
 * a priority order when checked.
 *
 * Key features:
 * - Target state management
 * - Event source handling
 * - Transition priority system
 * - Last event tracking
 *
 * Usage:
 * @code
 * Transition* trans = new EventTransition(nextState);
 * currentState.addTransition(trans);
 * @endcode
 *
 * @note Transitions are owned by their state and shouldn't be deleted manually
 */

class Transition {
    State* nextState; ///< Pointer to the next state in the transition.
    State* ownerState{nullptr}; ///< Pointer to the owning state.
    Event* lastEvent{Event::none}; ///< The last event that triggered this transition.
    Transition* nextTransition{nullptr}; ///< Pointer to the next transition in the linked list.


protected:
    /**
     * Constructs a transition with a specified next state.
     *
     * @param next Pointer to the next state.
     */
    explicit Transition(State* next): nextState(next) { }

public:
    virtual ~Transition() = default;

    /**
     * Checks if the transition is triggered.
     *
     * @return `true` if the transition is triggered, `false` otherwise.
     */
    virtual bool isTriggered()  = 0;

    /**
     * Retrieves the priority of the transition.
     *
     * @return The transition priority as a `TransitionPriority` value.
     */
    virtual TransitionPriority getPriority() const = 0;

    /**
     * Sets the owning state of the transition.
     *
     * @param owner Pointer to the owning state.
     */
    void setOwner(State* owner) { ownerState = owner; }
    State* getOwner() const { return ownerState; }
    State* getNextState() const { return nextState; }

    Transition* getNext() const { return nextTransition; }
    void setNext(Transition *transition) { nextTransition = transition; }

    /**
     * Retrieves the last event that triggered this transition.
     *
     * @return Pointer to the triggering event.
     */
    Event *getLastEvent() const { return lastEvent; }
    void setLastEvent(Event *event) { lastEvent = event; }
};

#endif //TRANSITION_H