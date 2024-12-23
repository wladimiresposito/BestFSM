//
// Created by wla on 08/11/2024.
//

#ifndef STATE_H
#define STATE_H

#include "events/Event.h"
#include "actions/AlarmTimer.h"

/**
* @brief Base class for finite state machine states
*
* Represents a state in the FSM, managing its transitions and lifecycle.
* Each state can have multiple transitions and an optional timer.
*
* Key features:
* - Multiple transition support
* - Automatic state ID generation
* - Optional state timer
* - Lifecycle callbacks (onEnter, onExit, onUpdate)
*
* Usage example:
* @code
* class IdleState : public State {
*     void onEnter(Event* event) override {
*         // State initialization
*     }
*     void onExit() override {
*         // Cleanup before leaving state
*     }
*     void onUpdate() override {
*         // Periodic state update
*     }
* };
* @endcode
*
* @param timeout Optional timer duration (0 for no timer)
*
*/

class Transition;

/**
 * Represents a state within the finite state machine (FSM).
 *
 * Responsibilities:
 * - Manages transitions to other states based on specified conditions.
 * - Provides hooks (`onEnter`, `onExit`, `onUpdate`) for custom behavior during state lifecycle.
 * - Supports optional timeout functionality using a timer.
 *
 * Design Considerations:
 * - A state can have multiple transitions, evaluated in priority order.
 * - Transition management is facilitated using a linked list structure.
 *
 * Usage:
 * - Extend this class to create specific states with custom behavior.
 * - Use `addTransition` to link transitions to the state.
 * Usage example:
 * @code
 * class IdleState : public State {
 *     void onEnter(Event* event) override {
 *         // State initialization
 *     }
 *     void onExit() override {
 *         // Cleanup before leaving state
 *     }
 *     void onUpdate() override {
 *         // Periodic state update
 *     }
 * };
 * @endcode
 */
class State {
    static int8_t _ids; ///< Counter to assign unique IDs to states.
    int id{++_ids};     ///< Unique ID of the state.
    int8_t totalTransitions{0}; ///< Total number of transitions for this state.
    Transition* triggeredTransition{nullptr}; ///< Transition triggered during evaluation.
    AlarmTimer* stateTimer{nullptr}; ///< Timer for state timeout functionality.

    Transition* firstTransition{nullptr}; ///< Pointer to the first transition.
    Transition* lastTransition{nullptr};  ///< Pointer to the last transition.

public:
    /**
     * Constructs a state with an optional timeout duration.
     *
     * @param timeout Timeout duration in milliseconds. Defaults to 0 (no timeout).
     */
    explicit State(unsigned long timeout = 0);

    /**
     * Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~State() = default;

    /**
     * Adds a transition to the state.
     *
     * @param transition Pointer to the transition to add.
     * @return A pointer to this state for method chaining.
     */
    State* addTransition(Transition* transition);

    /**
     * Checks transitions for a triggered condition.
     *
     * @return Pointer to the triggered transition, or `nullptr` if none are triggered.
     */
    Transition* checkTransitions();

    /**
     * Retrieves the total number of transitions for this state.
     *
     * @return The total number of transitions.
     */
    int8_t getTotalTransitions() const { return totalTransitions; }

    /**
     * Retrieves the last triggered transition.
     *
     * @return Pointer to the last triggered transition, or `nullptr` if none.
     */
    Transition* getTriggeredTransition() const { return triggeredTransition; }

    /**
     * Checks whether the state's timer has elapsed.
     *
     * @return `true` if the timer has elapsed, `false` otherwise.
     */
    bool isTimerElapsed() const;

    /**
     * Starts the state's timer.
     */
    void startStateTimer() const;

    /**
     * Stops the state's timer.
     */
    void stopStateTimer() const;

    /**
     * Hook invoked when entering the state.
     *
     * @param event Pointer to the event triggering the transition. Can be `nullptr`.
     */
    virtual void onEnter(Event* event) const;

    /**
     * Hook invoked when exiting the state.
     *
     * @param event Pointer to the event triggering the transition. Can be `nullptr`.
     */
    virtual void onExit(Event* event) const;

    /**
     * Hook invoked during the state's update cycle.
     * Default implementation does nothing.
     */
    virtual void onUpdate() const { }

    /**
     * Retrieves the unique ID of the state.
     *
     * @return The state's unique ID.
     */
    int getId() const { return id; }

    /**
     * Equality operator to compare two states.
     *
     * @param other The state to compare against.
     * @return `true` if the states have the same ID, `false` otherwise.
     */
    bool operator==(const State& other) const { return id == other.id; }

    /**
     * Equality operator to compare the state with another state's pointer.
     *
     * @param other The state pointer to compare against.
     * @return `true` if the states have the same ID, `false` otherwise.
     */
    bool operator==(const State* other) const { return id == other->id; }

    // Disallow copy and assignment.
    State(const State&) = delete;
    State& operator=(const State&) = delete;

};


#endif // STATE_H