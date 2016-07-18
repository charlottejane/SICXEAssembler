#ifndef _PassTwo_
#define _PassTwo_
#include <fstream>
#include <iostream>
#include <sstream>
//#include "PassOne.h"

using namespace std;
//class PassOne;

class PassTwo// : public PassOne
{
public:
	//PassTwo():PassOne()
	PassTwo( std::string );
	~PassTwo();
	void getFile(string , ifstream& );
	bool checkFileExists( const string& );
	//void createListing( string );
	void createListing( int );
	void createHeaderListing( string address, string label, string operand );
	void getProgramLength();
	void calculateObjectCode();
	int searchOPTAB( string );


private:
	void initializeVariables();
	string getMachineCode( string );
	unsigned int mod_count_, line;
	int program_length;
	string record_line_;
	string intermediate_line_;
	//const Program_length_;
    string object_code_; // should be unsigned long int
    
    //PassOne *ptr;




	//void loadRegisters();
};
#endif