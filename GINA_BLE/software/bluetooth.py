import serial,struct,os,time

def initserial():
  bt = serial.Serial()
  if os.name == 'posix':
  	bt.port = "/dev/tty.usbmodemfa131"
  else:
  	bt.port = "COM3"
  bt.baudrate = 115200
  bt.open()
  return bt


def initdevice(bt):
  initcom = '\x01' #command
  initcom = initcom+'\x00\xFE' #GAP_DeviceInit
  initcom = initcom+struct.pack('B',struct.calcsize('BB16s16sL'))+struct.pack('BB16s16sL',8,3,'\x00','\x00',1) #ProfileRole,MaxScanRsp,IRK,CSRK,SignCounter
  
  bt.write(initcom)
  print "Sent device init command!"
  bt.read(size=56)

def set_connection_interval(bt):
  stparam='\x01' #command
  stparam=stparam+'\x30\xFE' #0xFE30 GAP_Set_Parameter
  stparam=stparam+'\x03' #Data Length
  stparam=stparam+'\x02' #Set Max Conn Interval
  stparam=stparam+'\xF4\x01' #Set 20 msec
  bt.write(stparam)
  paramev = bt.read(9)
  return paramev
  
def device_discovery(bt):
  disccom='\x01' #command
  disccom=disccom+'\x04\xFE' # 0xFE GAP_DeviceDiscoveryRequest
  disccom=disccom+'\x03' # Datalength
  disccom=disccom+'\x03' #Mode (all)
  disccom=disccom+'\x01' #Enable Name Mode
  disccom=disccom+'\x00' #Disable Whitelist
  bt.write(disccom)
  bt.read(9) #Clear out GAP_HCI_ExtentionCommandStatus
  time.sleep(1)
  while(1):
  	if bt.read(1) == '\x04':
  		if bt.read(1) == '\xFF':
  			bt.read(1)
  			if bt.read(1) == '\x01':
  				if bt.read(1) == '\x06':
  					break
  bt.read(1)
  numdev = struct.unpack('<B',bt.read(1))
  bt.read(2)
  i=0
  addr = ()
  addrstr = []
  while(i != numdev[0]):
  #Read addresses
  	newaddrstr = bt.read(6)
  	addrstr = (addrstr,newaddrstr)
  	addr = addr + (struct.unpack('6s',newaddrstr))
  	i = i+1
  	#print "Address:" + str(addr[i-1])
  	if (bt.inWaiting() > 0):
  		bt.read(2)
  
  #print "Addresses found"
  
  return numdev[0], addr
  
def link(bt, address):
  #Start the Link
  lincom = '\x01' #command
  lincom = lincom + '\x09\xFE' #GAP_EstablishLinkRequest
  lincom = lincom + '\x09' #Data Length 9
  lincom = lincom + '\x00' #Whitelist and other options we don't need for now
  lincom = lincom + '\x00'
  lincom = lincom + '\x00'
  lincom = lincom + address #Link to address
  bt.write(lincom)
  #Start reading the status events generated from the link
  bt.read(9) #GAP_Status
  bt.read(22) #GAP_Establish_Link
  #Wait 1 second before next link: cannot link to two devices within the same connection interval
  time.sleep(1)
  
def read_packet(bt):
  if bt.read(1) == '\x04':
    if bt.read(1) == '\xFF':
    #Makes sure we only read from the start of the received packet
    #Errors occur when the acceleration and gyro data coincidentally give 04FF (Trivial to fix, just include the ATT event ID)
      length = struct.unpack('<B',bt.read(1))
      if bt.read(1) == '\x1B':
        if bt.read(1) == '\x05':
          bt.read(1)
          connhandle = struct.unpack('<BB',bt.read(2))
          bt.read(3)
          valstr = '<'
          valstrlen = length[0]-8
          while (valstrlen != 0):
            valstr = valstr + 'B'
            valstrlen = valstrlen-1
          values = struct.unpack(valstr,bt.read(length[0]-8))
          past_time = final_ms_time
          xacc = accscale(getvalues(values[0],values[1]))
          yacc = accscale(getvalues(values[2],values[3]))
          zacc = accscale(getvalues(values[4],values[5]))
          xgyr = gyrscale(getvalues(values[8],values[9]))
          ygyr = gyrscale(getvalues(values[10],values[11]))
          zgyr = gyrscale(getvalues(values[12],values[12]))
          xmag = magscale(getvalues(values[15],values[14]))
          ymag = magscale(getvalues(values[17],values[16]))
          zmag = magscale(getvalues(values[19],values[18]))
          temperature = tempscale(getvalues(values[6],values[7]))
          return xacc, yacc, zacc, xgyr, ygyr, zgyr, xmag, ymag, zmag, temperature
  return 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

def getvalues(a,b):
  if (((a*256 + b) & (1<<15))!= 0):
    return ((a*256 + b) - (1<<16))
  else:
    return (a*256 + b)
	
def accscale(a):
  return a*39.2266/65535

def gyroscale(a):
  return a*3.14*2000./(65535*180)

def magscale(a):
  return a*2452./65535
  
def tempscale(a):
  return a/340. + 35
