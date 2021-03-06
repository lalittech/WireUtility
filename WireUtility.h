#include "Arduino.h"
/** @file WireUtility.h
	This file content function to help to debug wire interface on component.

*/

int WireTest(TwoWire &ScanWire, int address);

/** dump a 8 bit address data memory map from addreg up to (addreg+size)
*/
 void dump(HardwareSerial &MySerial,TwoWire &ScanWire, int adddev,int addreg, int size);
 
/** read a 8 bit address data(addreg)
*/
int readRegister(HardwareSerial &MySerial,TwoWire &ScanWire,int adddev,int addreg);
/** read a 16 bit address data(addreg)
*/
int readMem2(TwoWire &ScanWire,int adddev,int addreg);
/** read a 24 bit address data(addreg)
*/
int readMem3(TwoWire &ScanWire,int adddev,int addreg);

/** scan a 7 bit device address. and stop after 1st find, use scanNext to get next.
*/
int scan(HardwareSerial &MySerial,TwoWire &ScanWire);
/** scan next 7 bit device address.
if a 10bit device is found it can scanNext10bits
*/
int scanNext(HardwareSerial &MySerial,TwoWire &ScanWire);
/** scan next 10 bit device address.
*/
int scanNext10bits(HardwareSerial &MySerial,TwoWire &ScanWire);

/** perform a reset of all device on the line that manage Software Reset Call

The Software Reset address (SWRST Call) must be used with
R/W = logic 0. so  do a frame with address : 0x0 and write 0b00000110
*/
void wireResetAllDevices(TwoWire &MyWire);

/** read 8 bits register at address addr on device from i2C called MyWire at address _i2caddr
*/
uint8_t wireRead8(TwoWire &MyWire, uint8_t _i2caddr, uint8_t addr);
/** read 16 bits register at address addr on device from i2C called MyWire at address _i2caddr
*/
uint16_t wireRead16(TwoWire &MyWire, uint8_t _i2caddr, uint8_t addr);
/** read 32 bits register at address addr on device from i2C called MyWire at address _i2caddr
*/
uint32_t wireRead32(TwoWire &MyWire, uint8_t _i2caddr, uint8_t addr);
/** write 8 bits register at address addr on device from i2C called MyWire at address _i2caddr
*/
void wireWrite8(TwoWire &MyWire,uint8_t _i2caddr,uint8_t addr, uint8_t d);
/** write 16 bits register at address addr on device from i2C called MyWire at address _i2caddr
*/
void wireWrite16(TwoWire &MyWire,uint8_t _i2caddr,uint8_t addr, uint16_t d);
/** write 32 bits register at address addr on device from i2C called MyWire at address _i2caddr
*/
void wireWrite32(TwoWire &MyWire,uint8_t _i2caddr,uint8_t addr, uint32_t d);
/*
liste of several chip address :

#define NE5751_I2C_ADDRESS       0b1000000
#define NE5751_I2C_ADDRESS       0b1000001
#define PCA1070_I2C_ADDRESS      0b100010
#define PCA1070_I2C_ADDRESS      0b100011
#define PCA8510_I2C_ADDRESS      0b1011101
#define PCA8516_I2C_ADDRESS      0b1011101
#define PCA8516_I2C_ADDRESS      0b1100010
#define PCA8516_I2C_ADDRESS      0b1100011
#define PCB5020_I2C_ADDRESS      0b11000
#define PCB5020_I2C_ADDRESS      0b11001
#define PCB5021_I2C_ADDRESS      0b11000
#define PCB5021_I2C_ADDRESS      0b11001
#define PCB5032_I2C_ADDRESS      0b11000
#define PCB5032_I2C_ADDRESS      0b11001
#define PCD3311_I2C_ADDRESS      0b100100
#define PCD3311_I2C_ADDRESS      0b100101
#define PCD3312_I2C_ADDRESS      0b100100
#define PCD3312_I2C_ADDRESS      0b100101
#define PCD4430_I2C_ADDRESS      0b100000
#define PCD4430_I2C_ADDRESS      0b100001
#define PCD4440_I2C_ADDRESS      0b1101110
#define PCD4440_I2C_ADDRESS      0b1101111
#define PCD5002_I2C_ADDRESS      0b100111
#define PCF1810_I2C_ADDRESS      0b11100
#define PCF1810_I2C_ADDRESS      0b11101
#define PCF1810_I2C_ADDRESS      0b11110
#define PCF1810_I2C_ADDRESS      0b11111
#define PCF8566_I2C_ADDRESS      0b111101
#define PCF8566_I2C_ADDRESS      0b111110
#define PCF8570_I2C_ADDRESS      0b1010000
#define PCF8570_I2C_ADDRESS      0b1010001
#define PCF8570_I2C_ADDRESS      0b1010010
#define PCF8570_I2C_ADDRESS      0b1010011
#define PCF8570_I2C_ADDRESS      0b1010100
#define PCF8570_I2C_ADDRESS      0b1010101
#define PCF8570_I2C_ADDRESS      0b1010110
#define PCF8570_I2C_ADDRESS      0b1010111
#define PCF8570_I2C_ADDRESS      0b1011000
#define PCF8570_I2C_ADDRESS      0b1011001
#define PCF8570_I2C_ADDRESS      0b1011010
#define PCF8570_I2C_ADDRESS      0b1011011
#define PCF8570_I2C_ADDRESS      0b1011100
#define PCF8570_I2C_ADDRESS      0b1011101
#define PCF8570_I2C_ADDRESS      0b1011110
#define PCF8570_I2C_ADDRESS      0b1011111
#define PCF8571_I2C_ADDRESS      0b1010000
#define PCF8571_I2C_ADDRESS      0b1010001
#define PCF8571_I2C_ADDRESS      0b1010010
#define PCF8571_I2C_ADDRESS      0b1010011
#define PCF8571_I2C_ADDRESS      0b1010100
#define PCF8571_I2C_ADDRESS      0b1010101
#define PCF8571_I2C_ADDRESS      0b1010110
#define PCF8571_I2C_ADDRESS      0b1010111
#define PCF8573_I2C_ADDRESS      0b1101000
#define PCF8573_I2C_ADDRESS      0b1101001
#define PCF8573_I2C_ADDRESS      0b1101010
#define PCF8573_I2C_ADDRESS      0b1101011
#define PCF8574_I2C_ADDRESS      0b100000
#define PCF8574_I2C_ADDRESS      0b100001
#define PCF8574_I2C_ADDRESS      0b100010
#define PCF8574_I2C_ADDRESS      0b100011
#define PCF8574_I2C_ADDRESS      0b100100
#define PCF8574_I2C_ADDRESS      0b100101
#define PCF8574_I2C_ADDRESS      0b100110
#define PCF8574_I2C_ADDRESS      0b100111
#define PCF8574A_I2C_ADDRESS      0b111000
#define PCF8574A_I2C_ADDRESS      0b111001
#define PCF8574A_I2C_ADDRESS      0b111010
#define PCF8574A_I2C_ADDRESS      0b111011
#define PCF8574A_I2C_ADDRESS      0b111100
#define PCF8574A_I2C_ADDRESS      0b111101
#define PCF8574A_I2C_ADDRESS      0b111110
#define PCF8576_I2C_ADDRESS      0b111000
#define PCF8576_I2C_ADDRESS      0b111001
#define PCF8577_I2C_ADDRESS      0b111010
#define PCF8577A_I2C_ADDRESS      0b111011
#define PCF8578_I2C_ADDRESS      0b111100
#define PCF8579_I2C_ADDRESS      0b111100
#define PCF8580_I2C_ADDRESS      0b1010000
#define PCF8580_I2C_ADDRESS      0b1010001
#define PCF8580_I2C_ADDRESS      0b1010010
#define PCF8580_I2C_ADDRESS      0b1010011
#define PCF8580_I2C_ADDRESS      0b1010100
#define PCF8580_I2C_ADDRESS      0b1010101
#define PCF8580_I2C_ADDRESS      0b1010110
#define PCF8580_I2C_ADDRESS      0b1010111
#define PCF8581_I2C_ADDRESS      0b1010000
#define PCF8581_I2C_ADDRESS      0b1010001
#define PCF8581_I2C_ADDRESS      0b1010010
#define PCF8581_I2C_ADDRESS      0b1010011
#define PCF8581_I2C_ADDRESS      0b1010100
#define PCF8581_I2C_ADDRESS      0b1010101
#define PCF8581_I2C_ADDRESS      0b1010110
#define PCF8581_I2C_ADDRESS      0b1010111
#define PCF8582_I2C_ADDRESS      0b1010000
#define PCF8582_I2C_ADDRESS      0b1010001
#define PCF8582_I2C_ADDRESS      0b1010010
#define PCF8582_I2C_ADDRESS      0b1010011
#define PCF8582_I2C_ADDRESS      0b1010100
#define PCF8582_I2C_ADDRESS      0b1010101
#define PCF8582_I2C_ADDRESS      0b1010110
#define PCF8582_I2C_ADDRESS      0b1010111
#define PCF8583_I2C_ADDRESS      0b1010000
#define PCF8583_I2C_ADDRESS      0b1010001
#define PCF8591_I2C_ADDRESS      0b1001000
#define PCF8591_I2C_ADDRESS      0b1001001
#define PCF8591_I2C_ADDRESS      0b1001010
#define PCF8591_I2C_ADDRESS      0b1001011
#define PCF8591_I2C_ADDRESS      0b1001100
#define PCF8591_I2C_ADDRESS      0b1001101
#define PCF8591_I2C_ADDRESS      0b1001110
#define PCF8591_I2C_ADDRESS      0b1001111
#define SAA1064_I2C_ADDRESS      0b111000
#define SAA1064_I2C_ADDRESS      0b111001
#define SAA1064_I2C_ADDRESS      0b111010
#define SAA1064_I2C_ADDRESS      0b111011
#define SAA1135_I2C_ADDRESS      0b10001
#define SAA1136_I2C_ADDRESS      0b11100
#define SAA1137_I2C_ADDRESS      0b100000
#define SAA1137_I2C_ADDRESS      0b100001
#define SAA1770_I2C_ADDRESS      0b11110
#define SAA1770_I2C_ADDRESS      0b11111
#define SAA4700_I2C_ADDRESS      0b10000
#define SAA4700_I2C_ADDRESS      0b10001
#define SAA5240_I2C_ADDRESS      0b10000
#define SAA5240_I2C_ADDRESS      0b10001
#define SAA5240_I2C_ADDRESS      0b10010
#define SAA5241_I2C_ADDRESS      0b10001
#define SAA5243_I2C_ADDRESS      0b10001
#define SAA5244_I2C_ADDRESS      0b10001
#define SAA5244_I2C_ADDRESS      0b10010
#define SAA5246_I2C_ADDRESS      0b10001
#define SAA5252_I2C_ADDRESS      0b10100
#define SAA7152_I2C_ADDRESS      0b1011001
#define SAA7186_I2C_ADDRESS      0b1011100
#define SAA7186_I2C_ADDRESS      0b1011110
#define SAA7192_I2C_ADDRESS      0b1110000
#define SAA7192_I2C_ADDRESS      0b1110001
#define SAA7194_I2C_ADDRESS      0b100000
#define SAA7194_I2C_ADDRESS      0b100001
#define SAA7199_I2C_ADDRESS      0b1011000
#define SAA7199_I2C_ADDRESS      0b1011001
#define SAA7250_I2C_ADDRESS      0b11000
#define SAA7250_I2C_ADDRESS      0b11001
#define SAA9020_I2C_ADDRESS      0b10100
#define SAA9020_I2C_ADDRESS      0b10101
#define SAA9020_I2C_ADDRESS      0b10110
#define SAA9020_I2C_ADDRESS      0b10111
#define SAA9041_I2C_ADDRESS      0b10001
#define SAA9065_I2C_ADDRESS      0b1011111
#define SAB3028_I2C_ADDRESS      0b100110
#define SAB3035_I2C_ADDRESS      0b1100000
#define SAB3035_I2C_ADDRESS      0b1100001
#define SAB3035_I2C_ADDRESS      0b1100010
#define SAB3035_I2C_ADDRESS      0b1100011
#define SAB3035_I2C_ADDRESS      0b1100100
#define SAB3035_I2C_ADDRESS      0b1100101
#define SAB3035_I2C_ADDRESS      0b1100110
#define SAB3035_I2C_ADDRESS      0b1100111
#define SAB3036_I2C_ADDRESS      0b1100000
#define SAB3036_I2C_ADDRESS      0b1100001
#define SAB3036_I2C_ADDRESS      0b1100010
#define SAB3036_I2C_ADDRESS      0b1100011
#define SAB3036_I2C_ADDRESS      0b1100100
#define SAB3036_I2C_ADDRESS      0b1100101
#define SAB3036_I2C_ADDRESS      0b1100110
#define SAB3036_I2C_ADDRESS      0b1100111
#define SAB3037_I2C_ADDRESS      0b1100000
#define SAB3037_I2C_ADDRESS      0b1100001
#define SAB3037_I2C_ADDRESS      0b1100010
#define SAB3037_I2C_ADDRESS      0b1100011
#define SAB3037_I2C_ADDRESS      0b1100100
#define SAB3037_I2C_ADDRESS      0b1100101
#define SAB3037_I2C_ADDRESS      0b1100110
#define SAB3037_I2C_ADDRESS      0b1100111
#define SAB9070_I2C_ADDRESS      0b10010
#define SAF1134_I2C_ADDRESS      0b10000
#define SAF1134_I2C_ADDRESS      0b10001
#define SAF1134_I2C_ADDRESS      0b10010
#define SAF1134_I2C_ADDRESS      0b10011
#define SAF1135_I2C_ADDRESS      0b10000
#define SAF1135_I2C_ADDRESS      0b10011
#define SAF1135_I2C_ADDRESS      0b10011
#define TDA1551_I2C_ADDRESS      0b1101100
#define TDA2518_I2C_ADDRESS      0b1011100
#define TDA6360_I2C_ADDRESS      0b1000010
#define TDA6360_I2C_ADDRESS      0b1000011
#define TDA8415_I2C_ADDRESS      0b1000010
#define TDA8416_I2C_ADDRESS      0b1000010
#define TDA8416_I2C_ADDRESS      0b1011010
#define TDA8417_I2C_ADDRESS      0b1000010
#define TDA8420_I2C_ADDRESS      0b1000000
#define TDA8420_I2C_ADDRESS      0b1000001
#define TDA8421_I2C_ADDRESS      0b1000000
#define TDA8421_I2C_ADDRESS      0b1000001
#define TDA8424_I2C_ADDRESS      0b1000001
#define TDA8425_I2C_ADDRESS      0b1000001
#define TDA8425_I2C_ADDRESS      0b1000010
#define TDA8426_I2C_ADDRESS      0b1000001
#define TDA8440_I2C_ADDRESS      0b1000010
#define TDA8440_I2C_ADDRESS      0b1001000
#define TDA8440_I2C_ADDRESS      0b1001001
#define TDA8440_I2C_ADDRESS      0b1001010
#define TDA8440_I2C_ADDRESS      0b1001011
#define TDA8440_I2C_ADDRESS      0b1001100
#define TDA8440_I2C_ADDRESS      0b1001101
#define TDA8440_I2C_ADDRESS      0b1001110
#define TDA8440_I2C_ADDRESS      0b1001111
#define TDA8443_I2C_ADDRESS      0b1101000
#define TDA8443_I2C_ADDRESS      0b1101001
#define TDA8443_I2C_ADDRESS      0b1101010
#define TDA8443_I2C_ADDRESS      0b1101011
#define TDA8443_I2C_ADDRESS      0b1101100
#define TDA8443_I2C_ADDRESS      0b1101101
#define TDA8443_I2C_ADDRESS      0b1101110
#define TDA8443_I2C_ADDRESS      0b1101111
#define TDA8444_I2C_ADDRESS      0b100000
#define TDA8444_I2C_ADDRESS      0b100001
#define TDA8444_I2C_ADDRESS      0b100010
#define TDA8444_I2C_ADDRESS      0b100011
#define TDA8444_I2C_ADDRESS      0b100100
#define TDA8444_I2C_ADDRESS      0b100101
#define TDA8444_I2C_ADDRESS      0b100110
#define TDA8444_I2C_ADDRESS      0b100111
#define TDA8480_I2C_ADDRESS      0b1000010
#define TDA8480_I2C_ADDRESS      0b1000011
#define TDA8540_I2C_ADDRESS      0b1001000
#define TDA8540_I2C_ADDRESS      0b1001001
#define TDA8540_I2C_ADDRESS      0b1001010
#define TDA8540_I2C_ADDRESS      0b1001011
#define TDA8540_I2C_ADDRESS      0b1001100
#define TDA8540_I2C_ADDRESS      0b1001101
#define TDA8540_I2C_ADDRESS      0b1001110
#define TDA8540_I2C_ADDRESS      0b1001111
#define TDA8940_I2C_ADDRESS      0b1000010
#define TDA8960_I2C_ADDRESS      0b1000000
#define TDA9860_I2C_ADDRESS      0b1000001
#define TEA6000_I2C_ADDRESS      0b1100001
#define TEA6100_I2C_ADDRESS      0b1100001
#define TEA6320_I2C_ADDRESS      0b1000000
#define TEA6330_I2C_ADDRESS      0b1000000
#define TSA5510_I2C_ADDRESS      0b1100000
#define TSA5510_I2C_ADDRESS      0b1100001
#define TSA5510_I2C_ADDRESS      0b1100010
#define TSA5510_I2C_ADDRESS      0b1100011
#define TSA5510_I2C_ADDRESS      0b1100100
#define TSA5510_I2C_ADDRESS      0b1100101
#define TSA5510_I2C_ADDRESS      0b1100110
#define TSA5510_I2C_ADDRESS      0b1100111
#define TSA5511_I2C_ADDRESS      0b1100000
#define TSA5511_I2C_ADDRESS      0b1100001
#define TSA5511_I2C_ADDRESS      0b1100010
#define TSA5511_I2C_ADDRESS      0b1100011
#define TSA5511_I2C_ADDRESS      0b1100100
#define TSA5511_I2C_ADDRESS      0b1100101
#define TSA5511_I2C_ADDRESS      0b1100110
#define TSA5511_I2C_ADDRESS      0b1100111
#define TSA5512_I2C_ADDRESS      0b1100000
#define TSA5512_I2C_ADDRESS      0b1100001
#define TSA5512_I2C_ADDRESS      0b1100010
#define TSA5512_I2C_ADDRESS      0b1100011
#define TSA5512_I2C_ADDRESS      0b1100100
#define TSA5512_I2C_ADDRESS      0b1100101
#define TSA5512_I2C_ADDRESS      0b1100110
#define TSA5512_I2C_ADDRESS      0b1100111
#define TSA5514_I2C_ADDRESS      0b1100000
#define TSA5514_I2C_ADDRESS      0b1100001
#define TSA5514_I2C_ADDRESS      0b1100010
#define TSA5514_I2C_ADDRESS      0b1100011
#define TSA5514_I2C_ADDRESS      0b1100100
#define TSA5514_I2C_ADDRESS      0b1100101
#define TSA5514_I2C_ADDRESS      0b1100110
#define TSA5514_I2C_ADDRESS      0b1100111
#define TSA5519_I2C_ADDRESS      0b1100000
#define TSA5519_I2C_ADDRESS      0b1100001
#define TSA5519_I2C_ADDRESS      0b1100010
#define TSA5519_I2C_ADDRESS      0b1100011
#define TSA5519_I2C_ADDRESS      0b1100100
#define TSA5519_I2C_ADDRESS      0b1100101
#define TSA5519_I2C_ADDRESS      0b1100110
#define TSA5519_I2C_ADDRESS      0b1100111
#define TSA6057_I2C_ADDRESS      0b1100010
#define TSA6057_I2C_ADDRESS      0b1100011
#define TSA6060_I2C_ADDRESS      0b1100010
#define TSA6060_I2C_ADDRESS      0b1100011
#define TSA6061_I2C_ADDRESS      0b1100010
#define TSA6061_I2C_ADDRESS      0b1100011
#define UMA1000_I2C_ADDRESS      0b1101100
#define UMA1000_I2C_ADDRESS      0b1101101
#define UMA1000_I2C_ADDRESS      0b1101110
#define UMA1000_I2C_ADDRESS      0b1101111
#define UMA1009_I2C_ADDRESS      0b1100000
#define UMA1009_I2C_ADDRESS      0b1100001
#define UMA1009_I2C_ADDRESS      0b1100010
#define UMA1009_I2C_ADDRESS      0b1100011
#define UMA1009_I2C_ADDRESS      0b1100100
#define UMA1009_I2C_ADDRESS      0b1100101
#define UMA1009_I2C_ADDRESS      0b1100110
#define UMA1009_I2C_ADDRESS      0b1100111
#define UMA1010_I2C_ADDRESS      0b1100000
#define UMA1010_I2C_ADDRESS      0b1100001
#define UMA1010_I2C_ADDRESS      0b1100010
#define UMA1010_I2C_ADDRESS      0b1100011
#define UMA1010_I2C_ADDRESS      0b1100100
#define UMA1010_I2C_ADDRESS      0b1100101
#define UMA1010_I2C_ADDRESS      0b1100110
#define UMA1010_I2C_ADDRESS      0b1100111
*/
