#ifndef PROGRAM6_H
#define PROGRAM6_H

#include <stdint.h>


class BinaryFileHeader
{


public:
	uint32_t magicNumber;
	uint32_t versionNumber;
	uint32_t numRecords;

};


const int maxRecordStringLength = 25;

class BinaryFileRecord
{
public:
	uint8_t strLength;
	char stringBuffer[maxRecordStringLength];
	double myVal;
};














#endif
