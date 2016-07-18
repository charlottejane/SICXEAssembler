#ifndef _PassOne_
#define _PassOne_

#include <fstream>
#include <iostream>
#include <sstream>
//#include "PassTwo.h"

class PassOne
{
public: 
	PassOne( std::string );
	~PassOne();
	void loadRegisters();
	void incrementLine();
	bool checkFileExists( const std::string& );
	void getFile( std::string, std::ifstream& );
	std::string getOpcode( std::string );
	void createRecord( int );
	void createHeaderRecord( std::string, std::string, std::string, unsigned short int, int );
	int	searchSymTab( std::string, int );
	void storeInSymTab( std::string, unsigned short int );
	void incrementLocationCounter();
	void incrementLocationCounter( int );	
	void incrementLocationCounter( int, int );
	int getProgramLength();

	int searchOpTab( std::string );
	void createIntermediateFile();
	void invalidOpcode( std:: string );
	void printSymTab();
	void createEndRecord( std::string, std::string );
	void createTextRecord( std::string, std::string, std::string );
	void createTextRecord( std::string, std::string );
	void generateObjectProgram();
	bool labelExists( std::string );
	void passOne( std::string );
	void passTwo( std::string );
	std::string getLabel( std::string );
	bool searchOPTAB( std::string );
	void directivesPassOne(  std::string, std::string );
	void directivesPassOne(  std::string, std::string, std::string );
	void setStartingAddress( std::string );
	int setStartAddress( std::string address );
	//unsigned int const program_length_;
	//static
	int program_length_;
	//void updatePassTwo( PassTwo& );


private:
	int operand_;
	int b_status;
	void initializeVariables();
	int line;
	std::string codeline_;
	std::string control_section_;
	unsigned short int program_address_;
	unsigned short int location_counter_;
	int symtab_object_counter_;
	int record_counter_;
	int seek_opcode_;
	int n_times_;
	int base_relative_, indirect_, index_, extended_, immediate_;
	std::string seekthis_nolabel_;
	int machine_code_;
	int optab_index_;
	void setNIXBPE(int, int, int, int, int, int);
	std::string restof_2_;
	int instruction_address_number_;
	unsigned long int memory_address_;
	long int N,I, X, B, P, E;
	std::string R1_,R2_;
	std::string tmp_immediate_;
	int tmp_immediate_val_;
	int sym_index_2_;
	std::string temp_format_2_;
	//int mod_count_;
	std::string opcode;
	//std::istringstream codeline( std::string );

};

#endif




