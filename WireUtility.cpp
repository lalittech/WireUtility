// --------------------------------------
// i2c_scanner
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not known.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning WireUtility_addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    http://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but WireUtility_address scans now to 127.
//    A sensor seems to use WireUtility_address 120.
// 
// version 6, based on previous job create library WireUtility
// (c) zoubata
// This sketch tests the standard 7-bit WireUtility_addresses
// Devices with higher bit WireUtility_address might not be seen properly.
//
//https://www.i2c-bus.org/WireUtility_addressing/

#include <Wire.h>
#include <WireUtility.h>



int  WireUtility_address;
int scan(HardwareSerial &MySerial,TwoWire &ScanWire)
{
 // ScanWire.begin(123);
  ScanWire.begin();
  
  WireUtility_address = 1;
  return scanNext(MySerial,ScanWire);
}
//1111 0XX
int scanNext10bits(HardwareSerial &MySerial,TwoWire &ScanWire)
{
  byte error;
 

  MySerial.println("Scanning...");

   for(; WireUtility_address <= 0x7BFF; WireUtility_address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the WireUtility_address.
    ScanWire.beginTransmission(WireUtility_address>>7);
	ScanWire.write(WireUtility_address&0x7f);
    error = ScanWire.endTransmission();

    if (error == 0)
    {
      MySerial.print("I2C device found at WireUtility_address 0x");
      MySerial.print(WireUtility_address,HEX);
      MySerial.println("  !");

	WireUtility_address++;
	return WireUtility_address-1;    
    }
    else if (error==4) 
    {
      MySerial.print("Unknow error at WireUtility_address 0x");
      if (WireUtility_address<16) 
        MySerial.print("0");
      MySerial.println(WireUtility_address,HEX);
    }    
  }
  return 0;
}
int scanNext(HardwareSerial &MySerial,TwoWire &ScanWire)
{
  byte error;
  int nDevices;

if (WireUtility_address>=0x7800)
 return scanNext10bits(MySerial,ScanWire);
  nDevices = 0;
  for(; WireUtility_address < 127; WireUtility_address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the WireUtility_address.
    ScanWire.beginTransmission(WireUtility_address);
    error = ScanWire.endTransmission();

    if (error == 0)
    {
      MySerial.print("I2C device found at WireUtility_address 0x");
      if (WireUtility_address<16) 
        MySerial.print("0");
      MySerial.print(WireUtility_address,HEX);
      MySerial.println("  !");

	  if (WireUtility_address==0x0)  	 MySerial.println(" 0000000 0 / 0000000 1 General Call(0) or a Start Byte(1)");
 if (WireUtility_address==0x1)  	 MySerial.println(" 0000001 X CBUS Addresses");
 if (WireUtility_address==0x2)  	 MySerial.println(" 0000010 X Reserved for Different Bus Formats");
 if (WireUtility_address==0x3)  	 MySerial.println(" 0000011 X Reserved for future purposes");
 if (WireUtility_address&0xFC==0x4)  	 MySerial.println(" 00001XX X High-Speed Master Code");
 if (WireUtility_address&0xFC==0x78)  	 {
		MySerial.println("11110XX X 10-bit Slave Addressing :  11110XX X xxxxxxxx");
			WireUtility_address=0x7800;
		return scanNext10bits(MySerial,ScanWire);
	}
 if (WireUtility_address&0xFC==0x7C)  	 MySerial.println("11111XX X Reserved for future purposes");
 
    WireUtility_address++;
	return WireUtility_address-1;     
    }
    else if (error==4) 
    {
      MySerial.print("Unknow error at WireUtility_address 0x");
      if (WireUtility_address<16) 
        MySerial.print("0");
      MySerial.println(WireUtility_address,HEX);
    }    
  }
  return 0;
}




int readRegister(HardwareSerial &MySerial,TwoWire &ScanWire,int adddev,int addreg){
  int error;
	// read the current GPINTEN
	if (adddev>128)
	{
	ScanWire.beginTransmission(adddev>>7);
	
	ScanWire.write(addreg&0x7f);
	}
	else
	{
	ScanWire.beginTransmission(adddev);
	
	}
	ScanWire.write(addreg);
	error = ScanWire.endTransmission();
	
        
        if(error == 2)
          MySerial.print("Address error");
        if(error == 3)
          MySerial.print("Nack or error");
      
   
	ScanWire.requestFrom(adddev, 1);
	return ScanWire.read();	
}
int readMem2(HardwareSerial &MySerial,TwoWire &ScanWire,int adddev,int addreg){
  int error;
	// read the current GPINTEN
	if (adddev>128)
	{
	ScanWire.beginTransmission(adddev>>7);
	
	ScanWire.write(addreg&0x7f);
	}
	else
	{
	ScanWire.beginTransmission(adddev);
	
	}
	ScanWire.write((addreg>>8)&0xff);
	ScanWire.write(addreg&0xff);
	error = ScanWire.endTransmission();
	
        
        if(error == 2)
          MySerial.print("Address error");
        if(error == 3)
          MySerial.print("Nack or error");
      
   
	ScanWire.requestFrom(adddev, 1);
	return ScanWire.read();	
}

int readMem3(HardwareSerial &MySerial,TwoWire &ScanWire,int adddev,int addreg){
  int error;
	// read the current GPINTEN
	if (adddev>128)
	{
	ScanWire.beginTransmission(adddev>>7);
	
	ScanWire.write(addreg&0x7f);
	}
	else
	{
	ScanWire.beginTransmission(adddev);	
	}
	ScanWire.write((addreg>>16)&0xff);
	ScanWire.write((addreg>>8)&0xff);
	ScanWire.write(addreg&0xff);
	error = ScanWire.endTransmission();
	
        
        if(error == 2)
          MySerial.print("Address error");
        if(error == 3)
          MySerial.print("Nack or error");
      
   
	ScanWire.requestFrom(adddev, 1);
	return ScanWire.read();	
}

void dump(HardwareSerial &MySerial,TwoWire &ScanWire, int adddev,int addreg, int size)
{
for(int i=addreg;i<addreg+size;i++)
{

 MySerial.print("D 0x");
  MySerial.print(adddev,16);
 MySerial.print(", @ 0x");
  MySerial.print(i,16);
 MySerial.print("= 0x");
  MySerial.print(readRegister(ScanWire,adddev,i),16);
 
 MySerial.println("");
}
}