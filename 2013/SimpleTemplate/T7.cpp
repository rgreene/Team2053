/*----------------------------------------------------------------------------*/
/* Copyright (c) Team 2053 2013. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "T7.h"
#include "WPILib.h"
#include "SerialPort.h"
#include <sstream>
#include <stdio.h>
#include <string>



/**
 * Construct an instance of an T7.
 * 
 * @param baudRate is 115200 by defaul with 8 data bits
 */
T7::T7()
{
	
	serial = new SerialPort(115200,8);
}

/* Remove memory allocations */
T7::~T7()
{
	delete serial;
	delete bufferIn;
}

/*int T7::SetDamping(int damping)
{
	int size;
	char bufferOut[]
}

char T7::CalculateChecksum()
{
	
}
*/

bool T7::ReceiveSetDampingRequest()
{
	int size;
	size = serial->GetBytesReceived();
	
	if(size > 4)
	{
		serial->Read(*bufferIn,size);
		//printf("received: ");
		//for(int i = 0; i < size; i++)
		//{
		//	printf("%02X",*bufferIn[i]);
		//}
		//printf("\n");
		return true;
	}
	else
	{
		return false;
	}
}

void T7::SendSetDampingRequest(int damping)
{
	int damp = damping;
	unsigned char cmd[5];
	long upInt;
    cmd[0] = 0x7F;
    cmd[1] = 0x04;
    cmd[2] = 0x8B;
    upInt = damp / 256;
    damp = damp % 256;
    cmd[3] = (unsigned char) upInt;
    cmd[4] = damp;
    long checksum = 0;
    checksum += cmd[0] + cmd[1] + cmd[2] + cmd[3] + cmd[4];
    checksum = ((checksum*(-1)) % 256)+1;
    cmd[5] = (unsigned char) checksum;
    ///printf("sending setDamping cmd: ");
    //for(int i = 0; i < 6; i++)
    //{
    //   printf("%02X ",cmd[i]);
    //}
    //printf("\n");
    char cmds[5];
    for(int i = 0; i < 6; i++)
    {
    	cmds[i] = (char)cmd[i];
    }
	serial->Write(cmds,6);
}


float T7::ReceiveGetAngleRequest()
{
//	while(size < 8 && serialTimer->Timer::Get() <= 0.03)
//	{
//	}
	int size;
	size = serial->GetBytesReceived();
	if(size > 7)
	{
		serial->Read(*bufferIn,size);
		std::string unpacked = unpack_hex(*bufferIn,3,size-1);
	
		//printf("unpacked: %s\n",unpacked.c_str());
		
		stringstream ss;
		unsigned long unsignedLong;
		signed long signedLong;
	
		ss << unpacked;
		
		ss >> std::hex >> unsignedLong;

		//printf("unsigned long %lu\n",unsignedLong);
		
		signedLong = (signed long)unsignedLong;
		//printf("signed long %ld\n",signedLong);
		float degree = ((float)signedLong) / 1000.0;
		printf("angle: %.4f\n",degree);
		return degree;
	}
	else
	{
		//printf("Size is: %d\n", size);
		return 0.0;
	}
}

void T7::SendGetAngleRequest()
{
	char bufferOut[2];
	bufferOut[0] = 0x7F;
	bufferOut[1] = 0x01;
	bufferOut[2] = 0x83;
	serial->Write(bufferOut,3);
}

std::string T7::unpack_hex(char *buffer,int offset,int size)
{
	char lowMask = 0x0F;
	char highMask = 0xF0;
	char lowHalf;
	char highHalf;
	
	stringstream ss;
	std::string unpacked;
	
	for(int i=offset;i<size;i++)
	{
		lowHalf = buffer[i] & lowMask;
		highHalf = (buffer[i] & highMask)>>4;
		//printf("high half: %X low half: %X\n",highHalf,lowHalf);
		ss << (char)returnASCII(highHalf);
		ss << (char)returnASCII(lowHalf);
	}
	ss >> unpacked;
	//printf("string: %s\n",unpacked.c_str());
	NetworkTable::GetTable("T7")->PutString("T7",unpacked);
	
	return unpacked;
}
int T7::returnASCII(char ch)
{
	switch(ch)
	{
		case 0x00:
			return 48;
		case 0x01:
			return 49;
		case 0x02:
			return 50;
		case 0x03:
			return 51;
		case 0x04:
			return 52;
		case 0x05:
			return 53;
		case 0x06:
			return 54;
		case 0x07:
			return 55;
		case 0x08:
			return 56;
		case 0x09:
			return 57;
		case 0x0A:
			return 65;
		case 0x0B:
			return 66;
		case 0x0C:
			return 67;
		case 0x0D:
			return 68;
		case 0x0E:
			return 69;
		case 0x0F:
			return 70;
		default:
			return 48;
	}
}



