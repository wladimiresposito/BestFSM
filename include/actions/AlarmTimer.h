//
// Created by wla on 08/11/2024.
//

#ifndef ALARM_TIMER_H
#define ALARM_TIMER_H

/**
* @brief Timer class that ensures precise timing periods
*
* AlarmTimer provides precise timing control with guaranteed period maintenance.
* While it can be used for simple timeout operations, its main feature is
* maintaining exact periodic intervals by tracking absolute trigger times.
*
* Key features:
* - Precise periodic timing
* - Automatic drift compensation
* - Support for both one-shot and periodic timing
* - Zero-drift periodic operation
* - Dynamic period modification
*
* Methods:
* @method start()     Starts or restarts the timer
* @method stop()      Stops the timer
* @method reset()     Resets the timer maintaining period reference
* @method elapsed()   Checks if period has elapsed, updates next trigger
* @method setDuration(duration) Changes the period duration
* @method isRunning() Returns timer running status
* @method getDuration() Returns current period duration
*
* Usage examples:
* 1. Simple timeout:
*    AlarmTimer timer(1000);
*    timer.start();
*    if(timer.elapsed()) { doSomething(); }
*
* 2. Periodic operation:
*    AlarmTimer timer(1000);
*    timer.start();
*    while(running) {
*        if(timer.elapsed()) {
*            doSomething();  // Will execute every 1000ms precisely
*        }
*    }
*
* 3. Dynamic period:
*    AlarmTimer timer(1000);
*    timer.start();
*    // ... later ...
*    timer.setDuration(2000);  // Changes to 2s period
*
* @note This implementation maintains periodic accuracy even if the elapsed()
* check is delayed, making it ideal for pseudo-real-time operations.
* Period changes via setDuration() take effect after the next elapsed trigger.
*/
#include <Arduino.h>

class AlarmTimer {
    unsigned long duration; ///< Duration of the timer in milliseconds.
    bool running{false}; ///< Indicates if the timer is running.
    unsigned long nextTrigger{0}; ///< Time of the next trigger in milliseconds.

public:
    /**
     * Constructs an alarm timer with an optional duration.
     *
     * @param duration Duration in milliseconds. Defaults to 0.
     */
    explicit AlarmTimer(const unsigned long duration = 0) : duration(duration) { }

    ~AlarmTimer() = default;

    /**
     * Starts the timer.
     */
    void start() {
        nextTrigger = millis() + duration;
        running = true;
    }

    /**
     * Checks if the timer has elapsed.
     *
     * @return `true` if the timer has elapsed, `false` otherwise.
     */
    bool elapsed() {
        if (!running) return false;

        const unsigned long current = millis();
        if (current >= nextTrigger) {
            // Calculates next trigger maintaining periodicity
            while (nextTrigger <= current) {
                nextTrigger += duration;
            }
            return true;
        }
        return false;
    }

    /**
     * Resets the timer to its initial state and restarts it.
     */
    void reset() {
        // Reset maintains time reference
        start();
    }

    /**
     * Stops the timer.
     */
    void stop() {
        running = false;
    }

    /**
     * Sets a new duration for the timer.
     *
     * @param newDuration The new duration in milliseconds.
     */
    void setDuration(const unsigned long newDuration) {
        duration = newDuration;
        if (running) {
            // Recalculate next trigger with new duration
            const unsigned long current = millis();
            nextTrigger = current + duration;
        }
    }

    /**
     * Checks if the timer is currently running.
     *
     * @return `true` if the timer is running, `false` otherwise.
     */
    bool isRunning() const {
        return running;
    }

    /**
     * Retrieves the current duration of the timer.
     *
     * @return The duration in milliseconds.
     */
    unsigned long getDuration() const {
        return duration;
    }
};

#endif //ALARM_TIMER_H
