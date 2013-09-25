#include "radio.h"
#include "ioCC2541.h"
#include "hal_types.h"
//==================defines============================

uint8 txfifo_len;
uint8 testarr[128];

//========================Prototypes=====================================
void load_txfifo(uint8 *, uint8);
uint8* arr_load_test();
int delay(); //for testing


//=======================public======================================
/**
 * /brief load data (max 128 bytes) into the TXFIFO
 */
void load_txfifo(uint8 *data, uint8 len) {
  uint8 i;
  for (i = 0; i < len; i++) {
    RFD = data[i];
  }
} 

void toggle_led() {
  P1_0 ^= 1;
}

uint8* arr_load_test() {
  uint8 i;
  for (i = 0; i < 10; i++) {
    testarr[i] = 0x01;
  }
  return testarr;
}

/************************
void main() {
  radio_init(); // Reset FIFO, set LED pins, enable LLE
  radio_setup(); // Setting up the channels, sync words etc.
  mac_timer_init();
  if (CHIPID == chip_2541){
    toggle_led(); //Checking LED1
    
    // test load and send fifo
    txfifo_len = arr_load_test();
    load_txfifo(testarr, txfifo_len);
    
    if (LLESTAT & LLE_SYNC_SEARCH) {  //Worked last time: means that it is active Rxing
      toggle_led();
    }
    
    if (RFTXFLEN == 10) {   //TXFIFO payload size is 10!
      toggle_led();
    }
    RFST = CMD_TX_TEST;
    if (RFERRF & BIT5) {   //There is an LLEERR
      toggle_led();
    }
    
    RFST = CMD_TX;
    if (RFERRF & BIT4) {   //There is an LLEERR
      toggle_led();
    }
    
    if (RFFSTATUS & BIT7) {   //Checking that TXFIFO is available
      toggle_led();
    }
    
    RFST = CMD_TX_TEST;
    while(!(RFSTAT & TX_ACTIVE));
    if (RFIRQF1 & BIT4) {  //Checking if empty packet received
      toggle_led();
    }
    if (LLESTAT & LLE_SYNC_SEARCH) {  //Worked last time: means that it is active Rxing
      toggle_led();
    }
    if (RFSTAT & SFD) {  //Either sync word sent or sync word received
      toggle_led();
    }
    while(1) {
      while(!(RFST == 0x00));
      RFST = CMD_TX;
      if (RFSTAT & TX_ACTIVE) {
        toggle_led();
      }
      delay(1000);
    }
  } else if (CHIPID == chip_2540) {
    toggle_led();
    RFST = CMD_RX;
    
    if (RFSTAT & SFD) {  //Either sync word sent or sync word received
      toggle_led();
    }
    if (LLESTAT & LLE_SYNC_SEARCH) {  //Worked last time: means that it is active Rxing
      toggle_led();
    }
    while(1) {
      RFST = CMD_RX;
        toggle_led();
      
      delay(1000);
    }
  }
}
********************/


/*For testing purposes */
int delay() {
  int c = 1, d = 1;
  for (c = 1; c < 1000 ; c++)
     for (d = 1; d < 1000 ; d++)
     {}
  return 0;
}



