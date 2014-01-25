#! /usr/bin/python

from serial import *
import struct
from ctypes import *
from pynetworktables import *
import commands
import re
command = 1

#time.sleep(10)

while(command):
	#return_val = "string"
	return_val = commands.getoutput('ping -c 1 10.20.53.2')
	print return_val
	#prog = re.compile('Destination\sHost\sUnreachable')
	match = re.search("Destination\sHost\sUnreachable",return_val)
	if(match):
		command = 1
		time.sleep(5)
	else:
		command = 0

print "got a successful ping back!"	

def ByteToHex( byteStr ):
	return ''.join( [ "%02X" % ord(x) for x in byteStr ] )

def convert( s ):
	i = int(s,16)
	cp = pointer(c_int(i))
	fp = cast(cp, POINTER(c_float))
	return fp.contents.value



ip = "10.20.53.2"

NetworkTable.SetIPAddress(ip)
NetworkTable.SetClientMode()
NetworkTable.Initialize()

time.sleep(10)

table = NetworkTable.GetTable(u'T7')

ser = Serial('/dev/ttyUSB0',115200)
#ser.port = "/dev/ttyUSB0" # may be called something different
#ser.baudrate = 115200 # may be different
ser.open()
cmd = '\x7F\x01\x83'
isRecieved = True
isSent = False
response = ""

#table.PutString(u'ScriptAlive',u'no')
#print "outside the wall"
while(ser.isOpen()):
	#print "in the flesh"
	#table.PutString(u'ScriptAlive',u'yes')
	#if ser.isOpen():
	if isRecieved:
		ser.write(cmd)
		isSent = True
		isRecieved = False
	response += ByteToHex(ser.read(ser.inWaiting()))
	#response += ser.read(ser.inWaiting())
	#if response != "":
	#	print response
	if isSent and response.__len__() == 16:
		#print "unmodified: "+response
		#response = response[3:7]
		response = response[6:14]
		#print "angle only: "+response
		#print (float.fromhex(response)/1000)
	        table.PutNumber(u'angle',(float.fromhex(response)/1000))
		#print (struct.unpack(">fff",response) / 1000)
		#print response#ByteToHex(response)
		#print struct.unpack(">f",response)[0]
		#print struct.unpack('!f',response.decode('hex'))[0]
		#print float(response)
                #print "angle in float: %f" fromhex(response)/1000
		response =""
		isRecieved = True
		isSent = False
		time.sleep(0.025)
