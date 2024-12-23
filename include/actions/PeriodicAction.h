//
// Created by wla on 14/11/2024.
//

#ifndef PERIODIC_ACTION_H
#define PERIODIC_ACTION_H

#include "Action.h"
#include "AlarmTimer.h"

/**
* @brief Base class for periodic actions with precise timing
*
* PeriodicAction provides a framework for executing actions at precise intervals.
* It uses an enhanced AlarmTimer to ensure consistent periodic execution with
* minimal drift, making it suitable for pseudo-real-time operations.
*
* Features:
* - Precise periodic execution
* - Optional delay for first execution
* - Configurable number of executions
* - Automatic completion tracking
*
* Usage:
* @code
* class BlinkLed : public PeriodicAction {
*     BlinkLed(int pin) : PeriodicAction(1000, 500) {} // period: 1000ms, delay: 500ms, infinite
*     void action() override {
*         digitalWrite(pin, !digitalRead(pin));
*     }
* };
* @endcode
*
* @param period Duration between executions in milliseconds
* @param numberOfExecutions Number of times to execute (-1 for infinite)
* @param executeFirst If true, executes immediately before starting period
*
* @note This class is designed for scenarios requiring precise timing,
* such as sensor sampling, signal generation, or real-time control systems.
* The actual execution time of action() should be significantly shorter
* than the period to maintain timing accuracy.
*/

class PeriodicAction : public Action {
    unsigned long period; ///< Time period between executions in milliseconds.
    unsigned long delay{0}; ///< Initial delay before the first execution in milliseconds.
    AlarmTimer* timer; ///< Timer to manage periodic execution.
    int executionsLeft{-1}; ///< Number of remaining executions. `-1` indicates infinite.
    bool firstExecution{true}; ///< Indicates whether the action is being executed for the first time.
    bool delayed{false}; ///< Indicates whether the initial delay has been applied.


public:
    /**
     * Constructs a periodic action with a specified period.
     *
     * @param period Time period between executions in milliseconds.
     */
    explicit PeriodicAction(const unsigned long period): period(period), timer(new AlarmTimer(period)) { }

    /**
     * Constructs a periodic action with a period and initial delay.
     *
     * @param period Time period between executions in milliseconds.
     * @param delay Initial delay in milliseconds.
     */
    explicit PeriodicAction(const unsigned long period, const unsigned long delay)
        : period(period), delay{delay} {
        if (delay > 0) {
            timer = new AlarmTimer(delay);
        } else {
            timer = new AlarmTimer(period);
        }
    }

    /**
     * Constructs a periodic action with a period, delay, and limited executions.
     *
     * @param period Time period between executions in milliseconds.
     * @param delay Initial delay in milliseconds.
     * @param numberOfExecutions Total number of executions before stopping.
     */
    explicit PeriodicAction(const unsigned long period, const unsigned long delay, const int numberOfExecutions):
    period(period), delay{delay}, executionsLeft(numberOfExecutions) {
        if (delay > 0) {
            timer = new AlarmTimer(delay);
        } else {
            timer = new AlarmTimer(period);
        }
    }
    ~PeriodicAction() override = default;

    /**
     * Defines the specific behavior of the periodic action.
     *
     * Must be implemented by derived classes.
     */
     void action() override = 0;

    /**
     * Executes the periodic action if its timer has elapsed.
     */
    void execute() override {
        if (executionsLeft == 0) return;

        if (firstExecution) {
            firstExecution = false;
            //  there is no delay
            if (delay <= 0) {
                action();
                // if executionsLeft was started with -1 it will never decrement and will execute periodically
                if (executionsLeft > 0) {
                    executionsLeft--;
                }
                // now that I've run it, I can start the timer
                timer->start();
                return;
            }
            // as there is a delay, the timer is set for this delay
            timer->start();
        }

        // Now others executions
        // If there was a delay, it will be met here.
        if (timer->elapsed()) {  // AlarmTimer already ensures periodicity, no need to execute start() again
            action();
            if (executionsLeft > 0) {
                executionsLeft--;
            }
            if (!delayed && delay > 0) {
                delayed = true;
                timer->setDuration(period);
            }
            timer->start();
        }
    }

    /**
     * Checks if the action has finished all executions.
     *
     * @return `true` if no executions are left, `false` otherwise.
     */
    bool isFinished() const {
        return executionsLeft == 0;
    }

    /**
     * Checks if the action is still running.
     *
     * @return `true` if executions remain, `false` otherwise.
     */
    bool isRunning() const {
        return executionsLeft > 0;
    }
};

#endif //PERIODIC_ACTION_H
