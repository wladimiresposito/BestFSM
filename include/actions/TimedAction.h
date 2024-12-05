// TimedAction.h
//
// Created by wla on 14/11/2024.
//

#ifndef TIMED_ACTION_H
#define TIMED_ACTION_H

#include "Action.h"
#include "AlarmTimer.h"

/**
 * Represents an action that executes once after a specified time interval.
 *
 * Responsibilities:
 * - Tracks a single execution after a timer elapses.
 *
 * Design Considerations:
 * - Combines the `AlarmTimer` for tracking elapsed time with a single-execution mechanism.
 */
class TimedAction : public Action {
    AlarmTimer timer; ///< Timer to manage the action's execution interval.
    bool executed{false}; ///< Indicates whether the action has been executed.
    bool timerStarted{false}; ///< Indicates whether the timer has been started.


public:
    /**
     * Constructs a timed action with a specified interval.
     *
     * @param interval Time interval in milliseconds before the action executes.
     */
    explicit TimedAction(const long interval): timer(interval) { }

    /**
     * Defines the specific behavior of the timed action.
     *
     * Must be implemented by derived classes.
     */
    void action() override = 0;

    /**
     * Executes the action if the timer has elapsed.
     */
    void execute() override {
        if (!timerStarted) {
            timer.start();
            timerStarted = true;
        }

        if (!executed && timer.elapsed()) {
            action();
            executed = true;
            timer.stop();
        }
    }

    /**
     * Checks if the action has been executed.
     *
     * @return `true` if the action has been executed, `false` otherwise.
     */
    bool isExecuted() const {
        return executed;
    }
};

#endif // TIMED_ACTION_H