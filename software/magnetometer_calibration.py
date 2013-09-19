#!/usr/bin/python

import time, sys
import motetalk as motetalk
from motetalk import cmd, packetify, setpwm
import input_functions as inpf
import numpy as np
import scipy as sp
import process_pos as pos
import quats as qt

from visual import *
import math

def startup(m):
  m.sendbase(cmd.radio(int(chan)))

  m.sendheli(cmd.flags(cmd.ledmode_cnt + cmd.tick))
  m.sendheli(cmd.mode(cmd.mode_imu_loop))

  m.sendbase(cmd.flags(cmd.ledmode_cnt + cmd.notick))
  m.sendbase(cmd.mode(cmd.mode_sniff))

def end(m):
  m.sendbase(cmd.mode(cmd.mode_spin))
  m.end()
  


if __name__=="__main__":
	#initialize motetalk/serial port stuff
	sport = "COM5" #raw_input('port \n')
	chan = "15" #raw_input('Channel to sniff \n')
	filename = raw_input('Log file to write to \n')
	log = open(filename + ".txt", 'w')
	#log2 = open(filename + "2.txt", 'w')
	
	m = motetalk.motetalk("xH","n",sport,None)
	startup(m)
	
	sys.stderr.write( "Sniffing...\n")
	try:
		(arr, t, crc) = m.nextline()
		(arr, t, crc) = m.nextline()
		(arr, t, crc) = m.nextline()
	except: 
		pass
		
	parse = False;
	
	i=0
	
	#initialize everything here
	accel = inpf.array3_init()
	gyro = inpf.array3_init()
	marg = inpf.array3_init()
	therm = inpf.array1_init()
	time_arr = inpf.array1_init()

	tstart  = 0
	axstart = 0
	aystart = 0
	azstart = 0
	vx      = 0
	vy      = 0
	vz      = 0
	x       = 0
	y       = 0
	z       = 0
	state   = 0
	p		= 0
	q		= [1,0,0,0]
	margpkt = inpf.make_array3pkt(0,0,0)
	j = 0
	while 1:
		rate (2000)
		#receive packet
		(arr, t, crc) = m.nextline(parse)
		#unpack packet into list
		arr = map(ord, arr)
		#check if packet error: checks packet length and crc, hard-coded method
		if len(arr) > 28:
			if ((arr[22] * 256 + arr[23]) == (sum(arr) - arr[22] - arr[23] - arr[24] - arr[25] - arr[26] - arr[27] - arr[28])):
				#separates packets into values, puts things into caches/buffers
				(ax, ay, az, gx, gy, gz, mx, my, mz, temp) = inpf.preparepkt(arr)
				accel = inpf.pushpkt(inpf.make_array3pkt(ax,ay,az),accel)
				gyro = inpf.pushpkt(inpf.make_array3pkt(gx,gy,gz),gyro)
				if ((mx == 0) and (my == 0) and (mz == 0)):
					marg= inpf.pushpkt(margpkt, marg)
				else:
					margpkt = inpf.make_array3pkt(mx,my,mz)
					marg = inpf.pushpkt(margpkt, marg)
				therm = inpf.pushpkt(inpf.make_array1pkt(temp), therm)
				time_arr = inpf.pushpkt(inpf.make_array1pkt(t), time_arr)
				#Get initial values for quaternion recalibration
				if (i<50):
					i+=1
				elif (i == 50):
					i+=1
					a_ini = np.sum(accel,0)/accel.shape[0]
					mag_ini = np.sum(marg,0)/marg.shape[0]
					(m_ini, q) = qt.initialize_q(a_ini, mag_ini)
				else:
					log.write(str("%20.6f"%time_arr[25]) + " " + str(marg[25,0]) + " " + str(marg[25,1]) + " " + str(marg[25,2]) + "\n")