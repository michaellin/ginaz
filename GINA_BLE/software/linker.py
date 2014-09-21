import bluetooth as ble
import serial,struct
import time
import os,sys

bt = ble.initserial()
ble.initdevice(bt)

ble.set_connection_interval(bt)

(numdev, addresses) = ble.device_discovery(bt)

j=0
while (j != numdev):
  j = j+1
  ble.link(bt, addresses[j])

while (bt.isOpen()):
  (xacc, yacc, zacc, xgyr, ygyr, zgyr, xmag, ymag, zmag, temperature) = ble.read_packet(bt)
