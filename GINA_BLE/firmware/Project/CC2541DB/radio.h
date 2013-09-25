/**
\brief Cross-platform declaration "radio" bsp module.

\author Thomas Watteyne <watteyne@eecs.berkeley.edu>, February 2012.
*/

#ifndef __RADIO_H
#define __RADIO_H

#include "hal_types.h"

//=========================== variables =======================================

//=========================== prototypes ======================================

// BIT definitions.
#define BIT7        0x80
#define BIT6        0x40
#define BIT5        0x20
#define BIT4        0x10
#define BIT3        0x08
#define BIT2        0x04
#define BIT1        0x02
#define BIT0        0x01

// admin
void load_txfifo(uint8 *, uint8);
uint8* arr_load_test();
void toggle_led();
int delay();


#endif
