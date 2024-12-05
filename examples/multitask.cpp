#include "multitask.h"

#include "fsm/FSM.h"
#include "fsm/StateTimeoutTransition.h"

FSM* task1 = nullptr;
FSM* task2 = nullptr;
FSM* task3 = nullptr;

/**
 * Sets up and starts three finite state machines (FSMs) for controlling LED states.
 *
 * Each FSM controls the on and off sequences of an LED, with predefined durations
 * for being on and off. The FSMs use time-based transitions to alternate between states.
 *
 * LED1:
 * - Led1OnState: Remains on for 2 seconds.
 * - Led1OffState: Remains off for 1 second.
 * - Transitions:
 *   - Led1OnState transitions to Led1OffState via StateTimeoutTransition.
 *   - Led1OffState transitions to Led1OnState via StateTimeoutTransition.
 *
 * LED2:
 * - Led2OnState: Remains on for 4 seconds.
 * - Led2OffState: Remains off for 2 seconds.
 * - Transitions:
 *   - Led2OnState transitions to Led2OffState via StateTimeoutTransition.
 *   - Led2OffState transitions to Led2OnState via StateTimeoutTransition.
 *
 * LED3:
 * - Led3OnState: Remains on for 1 second.
 * - Led3OffState: Remains off for 0.5 second.
 * - Transitions:
 *   - Led3OnState transitions to Led3OffState via StateTimeoutTransition.
 *   - Led3OffState transitions to Led3OnState via StateTimeoutTransition.
 *
 * Each task corresponding to an FSM is started to begin the LED control operations.
 */
void setupFsm() {
    auto led1OnState = new Led1OnState(2000); // 2 seconds
    auto led1OffState = new Led1OffState(1000); // 1 second
    led1OnState->addTransition(new StateTimeoutTransition(led1OffState));
    led1OffState->addTransition(new StateTimeoutTransition(led1OnState));
    task1 = new FSM(led1OnState);

    auto led2OnState = new Led2OnState(4000); // 4 seconds
    auto led2OffState = new Led2OffState(2000); // 2 seconds
    led2OnState->addTransition(new StateTimeoutTransition(led2OffState));
    led2OffState->addTransition(new StateTimeoutTransition(led2OnState));
    task2 = new FSM(led2OnState);

    auto led3OnState = new Led3OnState(1000); // 1 seconds
    auto led3OffState = new Led3OffState(500); // 0.5 seconds
    led3OnState->addTransition(new StateTimeoutTransition(led3OffState));
    led3OffState->addTransition(new StateTimeoutTransition(led3OnState));
    task3 = new FSM(led3OnState);

    task1->start();
    task2->start();
    task3->start();
}

void runAllFsm() {
    task1->run();
    task2->run();
    task3->run();
}

void setup() {
    Serial.begin(9600);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);

    setupFsm();
}

void loop() {
    runAllFsm();
}
