//
// Created by wla on 15/11/2024.
//
#include "fsm/EventTransition.h"
#include "fsm/FSM.h"
#include "FakeSerialButtonEventSource.h"
#include "fsm/State.h"
#include "fsm/StateTimeoutTransition.h"
#include "fsm/ImmediateTransition.h"

/**
 * Example demonstrating an FSM reacting to serial button events.
 *
 * Responsibilities:
 * - Manages state transitions based on button press/release events.
 * - Sends characters over serial output based on state.
 */

constexpr unsigned long SEND_TIMEOUT = 500;  // 0.5s timeout after sending

// States
class State0 final : public State {  // Initial state
public:
   State0() : State() {}  // One transition to S1

   void onEnter(Event* event) const override { }
};

class State1WaitA final : public State {  // Wait 'A'
public:
   State1WaitA() : State() { }  // One transition to S2
   void onEnter(Event* event) const override { }
};

class State2SendA final : public State {  // Send 'A'
public:
   State2SendA() : State(SEND_TIMEOUT) { }  // One transition to S2Wait

   void onEnter(Event* event) const override {
       Serial.print('A');
       State::onEnter(event);  // Start timer
   }
};

class State2WaitS final : public State {  // Wait 'S'
public:
   State2WaitS() : State() { }  // One transition to S3Send
   void onEnter(Event* event) const override { }
};

class State3SendS final : public State {  // Send 'S'
public:
   State3SendS() : State(SEND_TIMEOUT) { }  // One transition to S3Wait

   void onEnter(Event* event) const override {
       Serial.print('S');
       State::onEnter(event);  // Start timer
   }
};

class State3WaitL final : public State {  // Wait 'L'
public:
   State3WaitL() : State() { }  // One transition to S4Send
   void onEnter(Event* event) const override { }
};

class State4SendL final : public State {  // Send 'L'
public:
   State4SendL() : State(SEND_TIMEOUT) { }  // One transition to S4Wait

   void onEnter(Event* event) const override {
       Serial.print('L');
       State::onEnter(event);  // Start timer
   }
};

class State4WaitK final : public State {  // Wait 'K'
public:
   State4WaitK() : State() { }  // One transition to S5
};

class State5SendK final : public State {  // Send 'K' and back to S1
public:
   State5SendK() : State() { }  // One transition back to S1

   void onEnter(Event* event) const override {
       Serial.print('K');
   }
};

// Event Sources (with no timeout)
auto eventSourceA = new FakeSerialButtonEventSource('A', 'S');
auto eventSourceL = new FakeSerialButtonEventSource('L', 'K');

// Global states
auto s0 = new State0();
auto s1WaitA = new State1WaitA();
auto s2SendA = new State2SendA();
auto s2WaitS = new State2WaitS();
auto s3SendS = new State3SendS();
auto s3WaitL = new State3WaitL();
auto s4SendL = new State4SendL();
auto s4WaitK = new State4WaitK();
auto s5SendK = new State5SendK();

FSM* setupFSM() {
   // S0 -> S1 (automatic after init)
   s0->addTransition(new ImmediateTransition(s1WaitA));

   // S1 -> S2Send (on 'A' received)
   s1WaitA->addTransition(new EventTransition(
      s2SendA,
      Event::buttonPressed,
      eventSourceA));

   // S2Send -> S2Wait (after timeout)
   const auto t3 = new StateTimeoutTransition(s2WaitS);
   s2SendA->addTransition(t3);

   // S2Wait -> S3Send (on 'S' received)
   s2WaitS->
         addTransition(new EventTransition(s3SendS, Event::buttonReleased, eventSourceA))->
         // S3Send -> S3Wait (after timeout)
         addTransition(new StateTimeoutTransition(s3WaitL)) ;

   // S3Wait -> S4Send (on 'L' received)
   s3WaitL->addTransition(new EventTransition(
      s4SendL,
      Event::buttonPressed,
      eventSourceL));

   // S4Send -> S4Wait (after timeout)
   s4SendL->addTransition(new StateTimeoutTransition(s4WaitK));

   // S4Wait -> S5 (on 'K' received)
   s4WaitK->addTransition(new EventTransition(
      s5SendK,
      Event::buttonReleased,
      eventSourceL));

   // S5 -> S1 (automatic after sending 'K')
   s5SendK->addTransition(new ImmediateTransition(s0));

   const auto fsm = new FSM(s0);
   fsm->start();

   return fsm;
}

/*
Serial.begin(9600, SERIAL_8N1);
SERIAL_[Data][Parity][Stop]
- Data: 5,6,7,8,9 bits
- Parity: N(none), E(even), O(odd)
- Stop: 1,2 bits

Exemplos:
SERIAL_8N1 (default): 8 bits, no parity, 1 stop bit
SERIAL_8E1: 8 bits, even parity, 1 stop bit
SERIAL_8O1: 8 bits, odd parity, 1 stop bit
SERIAL_8N2: 8 bits, no parity, 2 stop bits
SERIAL_7E1: 7 bits, even parity, 1 stop bit
 */
// Setup FSM
//Transitions built using new, all transitions anonymous
FSM* fsm;
void setup() {
   Serial.begin(9600, SERIAL_7N2);

   fsm = setupFSM();
   // Start FSM
   fsm->start();
}

void loop() {
   fsm->run();
}
