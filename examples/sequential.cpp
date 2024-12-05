#include "sequential.h"

#include "fsm/FSM.h"
#include "fsm/StateTimeoutTransition.h"
#include "fsm/ImmediateTransition.h"

constexpr uint8_t LED1 = LED_BUILTIN_TX; ///< 30: Pin number for the LED TX.
constexpr uint8_t LED2 = LED_BUILTIN_RX; ///< 17: Pin number for the LED RX.
constexpr uint8_t LED3 = LED_BUILTIN ;   ///< 13: Pin number for the LED TBUILTIN..

FSM* seqFsm = nullptr;

AlarmTimer* timer1 = nullptr;
AlarmTimer* timer2 = nullptr;

void setupFsm() {
    auto initState = new State(2000); // 2 seconds
    auto led1State = new LedState(LED1, 1000); // 2 seconds
    auto led2State = new LedState(LED2, 1000); // 2 seconds
    auto led3State = new LedState(LED3, 1000); // 2 seconds

    initState->addTransition(new StateTimeoutTransition(led1State));
    led1State->addTransition(new StateTimeoutTransition(led2State));
    led2State->addTransition(new StateTimeoutTransition(led3State));
    led3State->addTransition(new StateTimeoutTransition(led1State));

      seqFsm = new FSM(led1State);
//      timer1 = new AlarmTimer(5000);
//      timer2 = new AlarmTimer(30000);
//      timer1->start();
}


void setup() {
    Serial.begin(9600);
    setupFsm();
    seqFsm->start();
}

void loop() {
//  if (timer1->elapsed()) {
//    Serial.println("timer1->elapsed()");
//    timer1->stop();
//    seqFsm->start();
//    timer2->start();
//  }

//  if (timer2->elapsed()) {
//    Serial.println("timer2->elapsed()");
//    seqFsm->stop();
//    timer2->stop();
//  }
  seqFsm->run();
}
