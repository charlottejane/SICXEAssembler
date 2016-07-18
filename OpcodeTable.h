#ifndef _OpcodeTable_
#define _OpcodeTable_
#define OPTABSIZE 59

struct OpTab {
	std::string mnemonic;
    int opcode;
    int oformat;
    bool sicxeonly;
};

const OpTab optab[OPTABSIZE] = {
	{"ADD", 0x18, 3, false},    //......1
	{"ADDF", 0x58, 3, true},    //......2
	{"ADDR", 0x90, 2, true},    //......3
	{"AND", 0x40, 3, false},    //......4
	{"CLEAR", 0xB4, 2, true},   //......5
	{"COMP", 0x28, 3, false},   //......6
	{"COMPF", 0x88, 3, true},   //......7
	{"COMPR", 0xA0, 2, true},   //......8
	{"DIV", 0x24, 3, false},    //......9
	{"DIVF", 0x64, 3, true},    //......10
	{"DIVR", 0x9C, 2, true},    //......11
	{"FIX", 0xC4, 1, true},     //......12
	{"FLOAT", 0xC0, 1, true},   //......13
	{"HIO", 0xF4, 1, true},     //......14
	{"J", 0x3C, 1, false},      //......15
	{"JEQ", 0x30, 3, false},    //......16
    {"JGT", 0x34, 3, false},    //......17
    {"JLT", 0x38, 3, false},    //......18
    {"JSUB", 0x48, 3, false},   //......19
    {"LDA", 0x00, 3, false},    //......20
    {"LDB", 0x68, 3, true},     //......21
    {"LDCH", 0x50, 3, false},   //......22
    {"LDF", 0x70, 3, true},     //......23
    {"LDL", 0x08, 3, false},    //......24
    {"LDS", 0x6C, 3, true},     //......25
    {"LDT", 0x74, 3, true},     //......26
    {"LDX", 0x04, 3, false},    //......27
    {"LPS", 0xD0, 3, true},     //......28
    {"MUL", 0x20, 3, false},    //......29
    {"MULF", 0x60, 3, true},    //......30
    {"MULR", 0x98, 2, true},    //......31
    {"NORM", 0xC8, 1, true},    //......32
    {"OR", 0x44, 3, false},     //......33
    {"RD", 0xD8, 3, false},     //......34
    {"RMO", 0xAC, 2, true},     //......35
    {"RSUB", 0x4C, 3, false},   //......36
    {"SHIFTL", 0xA4, 2, true},  //......37
    {"SHIFTR", 0xA8, 2, true},  //......38
    {"SIO", 0xF0, 1, true},     //......39
    {"SSK", 0xEC, 3, true},     //......40
    {"STA", 0x0C, 3, false},    //......41
    {"STB", 0x78, 3, true},     //......42
    {"STCH", 0x54, 3, false},   //......43
    {"STF", 0x80, 3, true},     //......44
    {"STI", 0xD4, 3, true},     //......45
    {"STL", 0x14, 3, false},    //......46
    {"STS", 0x7C, 3, true},     //......47
    {"STSW", 0xE8, 3, false},   //......48
    {"STT", 0x84, 3, true},     //......49
    {"STX", 0x10, 3, false},    //......50
    {"SUB", 0x1C, 3, false},    //......51
    {"SUBF", 0x5C, 3, true},    //......52
    {"SUBR", 0x94, 2, true},    //......53
    {"SVC", 0xB0, 2, true},     //......54
    {"TD", 0xE0, 3, false},     //......55
    {"TIO", 0xF8, 1, true},     //......56
    {"TIX", 0x2C, 3, false},    //......57
    {"TIXR", 0xB8, 2, true},    //......58
    {"WD", 0xDC, 3, false}      //......59

};
#endif