//Author: Andrew Kwong

#include <iocc2541.h>
#include "i2c.h"

uint8_t dev_addr_write;
uint8_t dev_addr_read;

//Function for waiting until I2CSTAT gives the value I want
void waitI2CStat(uint8_t status_bits)
{
  uint8_t status;
  status = I2CSTAT;
while (I2CSTAT != status_bits);
}

//Writes reg_setting to reg_addr specified on MPU
void i2c_write_register(uint8_t dev_addr,uint8_t reg_addr,uint8_t reg_setting)
{
//Find device address write:
 dev_addr_write = (dev_addr*2)|0x00;

// Sent start condition and wait for it to be received
I2CCFG = I2C_SR;
waitI2CStat(SR_SENT);

// Send Device Address
I2CDATA = dev_addr_write;
I2CCFG = I2C_DO;
waitI2CStat(SLAW_ACK_SENT);

// Send Register address
I2CDATA = reg_addr;
I2CCFG = I2C_DO;
waitI2CStat(DATA_ACK_SENT);

// Send Register Value
I2CDATA = reg_setting;
I2CCFG = I2C_DO;
waitI2CStat(DATA_ACK_SENT);

// Send Stop Condition
I2CCFG=I2C_SP;
}

//Read I2C registers
void i2c_read_registers(uint8_t dev_addr,uint8_t reg_addr,uint8_t numBytes, uint8_t* spaceToWrite)
{
//Find device addresses
dev_addr_write = (dev_addr*2)|0x00;
dev_addr_read = (dev_addr*2)|0x01;
 
// Sent start condition and wait for it to be received
I2CCFG = I2C_SR;
waitI2CStat(SR_SENT);

// Send Device Address
I2CDATA = dev_addr_write;
I2CCFG = I2C_DO;
waitI2CStat(SLAW_ACK_SENT);

// Send Register address
I2CDATA = reg_addr;
I2CCFG = I2C_DO;
waitI2CStat(DATA_ACK_SENT);
      
// Send Restart condition
I2CCFG = I2C_SR;
waitI2CStat(RS_SENT);

// Send Device Address Read
I2CDATA = dev_addr_read;
I2CCFG = I2C_DO;
waitI2CStat(SLAR_ACK_SENT);

while(numBytes>1)
{
// Do Continued Transfer
I2CCFG=I2C_CO;
waitI2CStat(DATA_ACK_RECV);
*spaceToWrite = I2CDATA;
spaceToWrite++;
numBytes--;
}

//Do Final Transfer
I2CCFG=I2C_DO;
waitI2CStat(DATA_NACK_RECV);
*spaceToWrite = I2CDATA;

// Send Stop Condition
I2CCFG=I2C_SP;
}