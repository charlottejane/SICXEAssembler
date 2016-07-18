#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "PassOne.h"
#include "PassTwo.h"
#include "SymbolTable.h"
#include "Record.h"
#include "OpcodeTable.h"

using namespace std;

PassOne::PassOne( string file )
{

	initializeVariables();
	//loadRegisters();
	ifstream sourcefile;
	getFile( file, sourcefile );
	
	while ( getline( sourcefile, codeline_))
	{
		if ( codeline_[0] == '.' )
			continue;
		opcode = getOpcode( codeline_);
		createRecord( line );


		cout << " SAY Bye!" <<endl;
		incrementLine();

	}
	sourcefile.close();

	//location_counter_ = program_address_;
	printSymTab();
	getProgramLength();

	cout << "Program Length: " <<  	getProgramLength();

	
	

	cout << "Printing intermediate file: " << endl;
	//createIntermediateFile();
	//passTwo( "intermediate.txt" );

	//cout << " poop: 5 " << endl;
	sourcefile.close();
	//generateObjectProgram();
};

int PassOne::getProgramLength()
{
	return program_length_ = location_counter_- program_address_;
};
void PassOne::getFile(string file, ifstream& sourcefile)
{
	const bool file_exists = checkFileExists( file );
	if ( !file_exists )
	{
		cerr << " File " << file << " not found. " << endl;
		exit(1);
	}
	else
	{
		sourcefile.open( file.c_str() );
	}
	
	
};

string PassOne::getOpcode( string codeline_i )
{
	istringstream codeline( codeline_i );
	string token[3];
	codeline >> token[0] >> token[1] >> token[2];
	
	if(token[1]== "START")
	{
		location_counter_ = setStartAddress( token[2] );
		createRecord( line );
	}
	
	if (token[2] == "")
	{
		cout << "Opcode: " << token[0] << endl 
		<<" Line " << dec << line << endl;
		
		if (searchOPTAB(token[0]))
		{
			createTextRecord( token[0],token[1]);
			incrementLocationCounter();
		}
		
		else if (!searchOPTAB(token[0]))
		{
			directivesPassOne( token[0], token[1] );
		}
		
		return token[0];

	}
	else 
	{
		cout << "Opcode: " << token[1] << "\t"
		<< "Label: " << getLabel( token[0] )<< endl 
		<<" Line " << line << endl;
		//getLabel( token[0]);

		//directivesPassOne( token[1], token[2] );
		if (searchOPTAB(token[1]))
		{
			createTextRecord(token[0], token[1], token[2]);
			incrementLocationCounter();
		}
		else if (!searchOPTAB(token[0]))
		{
			directivesPassOne( token[0], token[1], token[2] );
		}
		return token[1];
	}
};

string PassOne::getLabel( string token )
{
	if ( searchSymTab( token, symtab_object_counter_) == 1 )
	{
		cerr << "Duplicate label: " << token << endl
		<< "Line: " << dec << line << endl;
		exit(1);
	}
	else
	{
		storeInSymTab( token, location_counter_);
	}
	//printSymTab();

	return token;

};

int PassOne::setStartAddress( string address )
{
	istringstream start_address( address );
	start_address >> hex >> program_address_;
	return program_address_;
};

void PassOne::setStartingAddress( string address )
{
	istringstream start_address( address );
	start_address >> hex >> program_address_;
	location_counter_ = program_address_;
	cout << "LOCCTR: " << location_counter_;
};

bool PassOne::checkFileExists( const string& file )
{
	ifstream f(file.c_str() );
	return f.is_open();
};

void PassOne::incrementLine()
{
	line++;
	//cout << line;
};

void PassOne::directivesPassOne( string label, string directive, string operand )
{
	if ( directive == "START")
	{	
		setStartingAddress(operand);
		//control_section_ = label;
		createTextRecord( label, directive, operand );
		//createHeaderRecord( label, directive, operand, program_address_, b_status );
		cout << " SAY HEYYY!" <<endl;
		line++;
	}
		
	else if ( directive == "WORD" )
		incrementLocationCounter();
		
	else if ( directive == "RESW" )
	{
		istringstream number( operand );
		number >> operand_;
		incrementLocationCounter( 0, operand_ );
	} 
	
	else if ( directive == "RESB" )
	{
		istringstream number( operand );
		number >> operand_;
		incrementLocationCounter( operand_, 0 );
	}
	
	else if ( directive == "BYTE" )
	{
		operand = operand.substr(2,operand.length() - 3 );
		int number = operand.length();
		int x_number = 0;
		switch( operand[0] )
		{
		case 'C':
			incrementLocationCounter( number, 0 );
			break;
		case 'X':
			x_number =  ceil((float)number/2.0);
			incrementLocationCounter( x_number, 0 );
			break;
		}
	}
	
	else 
		cout << "test" << endl;
}

void PassOne::directivesPassOne( string directive, string operand )
{
	if ( directive == "END" )
	{
		createEndRecord( directive, operand );
		cout<< "We are done here " << endl;
		createIntermediateFile();
		
	}
	else if ( directive == "WORD" )
		incrementLocationCounter();
		
	else if ( directive == "RESW" )
	{
		istringstream number( operand );
		number >> operand_;
		incrementLocationCounter( 0, operand_ );
	} 
	
	else if ( directive == "RESB" )
	{
		istringstream number( operand );
		number >> operand_;
		incrementLocationCounter( operand_, 0 );
	}
	
	else if ( directive == "BYTE" )
	{
		operand = operand.substr(2,operand.length() - 3 );
		int number = operand.length();
		int x_number = 0;
		switch( operand[0] )
		{
		case 'C':
			incrementLocationCounter( number, 0 );
			break;
		case 'X':
			x_number =  ceil((float)number/2.0);
			incrementLocationCounter( x_number, 0 );
			break;
		}
	}
	
	else 
		cout << "test" << endl;
		
};
		

void PassOne::createRecord( int line )
{
	record[record_counter_].Record_codeline = line;
    record[record_counter_].Record_address = location_counter_;
};

int PassOne::searchSymTab(std:: string labelname, int symtabsize)
{
	int found = -1;
	int i;
	for ( i = 1 ; i < symtabsize ; i++)
	{
		if( symtabObj[i].symbol == labelname )
		{
			return found = 1;
		}
	}
	return found;
};
void PassOne::storeInSymTab( std::string label, unsigned short int location )
{
	symtabObj[symtab_object_counter_].symbol = label;
	symtabObj[symtab_object_counter_].value = location;
	symtab_object_counter_++;

};

bool PassOne::searchOPTAB( string token )
{
	for (int i = 0; i < OPTABSIZE; i++ )
	{
		if ( optab[i].mnemonic == token )
			return true;
	}
	return false;
};
int PassOne::searchOpTab(std::string restoftoken){
	int i;
	for( i = 0; i < OPTABSIZE; i++ )
	{
		if ( optab[i].mnemonic == restoftoken )
		{
			return i;
			break;
		}
	}
	return -1;
};
void PassOne::incrementLocationCounter()
{
	location_counter_ += 3;
};

void PassOne::incrementLocationCounter( int x )
{
	location_counter_ += x;
};

void PassOne::incrementLocationCounter( int add_x, int mul_y )
{
	location_counter_ = location_counter_ + add_x + 3*(mul_y);
};

void PassOne::createIntermediateFile()
{
	ofstream intermediatefile( "intermediate.txt" );
	int i;
	for ( i = 0; i < record_counter_; i++ )
	{
		intermediatefile << right << setw(6) << setfill( '0' ) 
		<< hex << record[i].Record_address
		<< setw(10) << setfill(' ') << record[i].label 
		<< setw(10) << setfill(' ') << record[i].instruction 
		<< setw(10) << setfill(' ') << record[i].operand << endl;
	}
};

void PassOne::invalidOpcode(string badopcode)
{
	cerr << "*************************" << endl
	<< "Error: Bad Opcode : " << badopcode << endl
	<< "Line: " << dec << line << endl
	<< "*************************" << endl;
};

void PassOne::printSymTab()
{
	ofstream SYMTAB("SYMTAB.txt");
	
	int i;
	for ( i=0; i < symtab_object_counter_; i++)
	{
		SYMTAB << left << setw(10) << setfill(' ') << symtabObj[i].symbol << "\t" 
		<< right << hex << setw(6) << setfill('0') << symtabObj[i].value << endl;
	}	

};

void PassOne::createEndRecord( std::string token0, std::string token1 )
{
	record[record_counter_].Record_address = location_counter_;
    record[record_counter_].instruction = token0;
    record[record_counter_].operand = token1;
    record_counter_++;
};

void PassOne::createHeaderRecord( std::string token0, std::string token1, std::string token2, unsigned short int address, int b_status )
{
	record[record_counter_].Record_address = address;
	record[record_counter_].label = token0;
    record[record_counter_].instruction = token1;
    record[record_counter_].operand = token2;
    record[record_counter_].addressingmode = b_status;
    record_counter_++;

};

void PassOne::createTextRecord( std::string token0, std::string token1, std::string token2 )
{
	record[record_counter_].label = token0;
    record[record_counter_].instruction = token1;
    record[record_counter_].operand = token2;
    record_counter_++;

};


void PassOne::createTextRecord( std::string token1, std::string token2 )
{
	record[record_counter_].instruction = token1;
    record[record_counter_].operand = token2;
    record_counter_++;


};


bool PassOne::labelExists( string token )
{
	if ( token != "")
		return true;
	else 
		return false;
};


void PassOne::loadRegisters()
{
	//SymTab symtabObj[1000];
	symtabObj[0].symbol="A";
	symtabObj[1].symbol="X";
	symtabObj[2].symbol="L";
	symtabObj[3].symbol="B";
	symtabObj[4].symbol="S";
	symtabObj[5].symbol="T";
	symtabObj[6].symbol="F";
	symtabObj[7].symbol="_";
	symtabObj[8].symbol="PC";
	symtabObj[9].symbol="SW";
	
	symtabObj[0].value=0;
	symtabObj[1].value=1;
	symtabObj[2].value=2;
	symtabObj[3].value=3;
	symtabObj[4].value=4;
	symtabObj[5].value=5;
	symtabObj[6].value=6;
	symtabObj[7].value=7;
	symtabObj[8].value=8;
	symtabObj[9].value=9;
};

void PassOne::initializeVariables()
{
	location_counter_ = 0;
	b_status = 0;
	//mod_count_=0;
	symtab_object_counter_ = 0;
	line = 0;
	record_counter_ = 0;
};

PassOne::~PassOne(){};
