#ifndef _Record_
#define _Record_

struct Record{
	unsigned int Record_codeline;
	unsigned long int Record_address;
	long int objectcode;
	std:: string label, instruction, operand;
	int addressingmode;
	int format;	
};

Record record[100];
#endif