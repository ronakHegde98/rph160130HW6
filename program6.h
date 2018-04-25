#ifndef PROGRAM6_H
#define PROGRAM6_H
#include <stdint.h>

//this class will allow us to read the three headers which will occupt 
class BinaryFileHeader
{
public:
	uint32_t magicNumber;
	uint32_t versionNumber;
	uint64_t numRecords;

};

//this is the max amount a string could be
const int maxRecordStringLength = 25;


//this class will allow us to read the files and their lengths
class BinaryFileRecord
{
public:
	uint8_t strLength;
	char stringBuffer[maxRecordStringLength];
};


#endif
