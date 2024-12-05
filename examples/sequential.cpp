#include "sequential.h"

#include "fsm/FSM.h"
#include "fsm/StateTimeoutTransition.h"
#include "fsm/ImmediateTransition.h"

constexpr uint8_t LED1 = LED_BUILTIN_TX; ///< 30: Pin number for the LED TX.
constexpr uint8_t LED2 = LED_BUILTIN_RX; ///< 17: Pin number for the LED RX.
constexpr uint8_t LED3 = LED_BUILTIN ;   ///< 13: Pin number for the LED TBUILTIN..

FSM* seqFsm = nullptr;

void setupFsm() {
    auto led1State = new LedState(LED1, 1000); // 2 seconds
    auto led2State = new LedState(LED2, 1000); // 2 seconds
    auto led3State = new LedState(LED3, 1000); // 2 seconds

    led1State->addTransition(new StateTimeoutTransition(led2State));
    led2State->addTransition(new StateTimeoutTransition(led3State));
    led3State->addTransition(new StateTimeoutTransition(led1State));

    seqFsm = new FSM(led1State);
}


void setup() {
    Serial.begin(9600);
    setupFsm();
    seqFsm->start();
}

void loop() {
  seqFsm->run();
}
