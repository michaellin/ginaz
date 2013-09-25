#include "led.h"
#include "ioCC2541.h"

//=========== prototypes =============
void led1_init();
void led1_toggle();

//=========== public =================
void led1_init() {
  P0SEL |= BIT4;
  P1DIR |= (BIT0 | BIT4); //Change this from P1DIR
  P0_1 &= 0;
}

void led1_toggle() {
  P1_0 ^= 1;
}