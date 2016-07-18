Charlotte Wuennemann

What is it?
***********
This is an assembler that can be implemented in Dr. Leland Beck's theoretical 
machine SIC/XE.  It is a two pass assembler that can determine in two passes 
whether the assemble code is for a SIC or SIC/XE machine. The architecture of a 
Simplified Instruction Machine (SIC) comes in two flavors.  It a standard model 
that is upward compatible with the XE version.  


How to compile?
***************
g++ Assembler.cpp main.cpp

How to run?
***********
as2 

Architecture: 
Memory (SIC): 8-bit bytes, 3-byte words,1-byte addresses, words are addressed by
the location of their lowest numbered byte, 32,768 total bytes
Memory (SIC/XE): same as SIC, but with 1 megabyte total

Registers: 
* SIC
A, 0, accumulator for arithmetic operations
X, 1, index register for addressing
L, 2, linkage register for Jump to Subroutine (JSUB)
PC, 8, program counter for address of next instruction to be fetched to execute
SW, 9, status word for variety of reasons like Condition Code (CC)
* SIC/XE
B, 3, base register used for addressing
S, 4, general working register - no special use
T, 5, general working register - no special use
F, 6, floating-point accumulator (48 bits) 

Data Formats:
* SIC 
Integers, 24-bit binary numbers
Negative values, 2's complement representation
Characters, 8-bit ASCII
No floating point
* SIC/XE
Floating point, 48-bit
The fraction is the value between 0 and 1. Sssumed binary point is immediately 
before the high-order bit. Normalized floating point, high-order bit of the 
fraction must be 1. Exponent is an unsigned binary number between 0 and 2047.
f*2^(e-1024).  Sign is indicated by value of s (0 positive, 1 negative)

Instruction Formats:
* SIC
24-bit format
|opcode 8|x 1| address 15 
x is a flag bit used to indicate indexed-addressing mode.
* SIC/XE
Format 1, 1 byte, | op 8 |
Format 2, 2 bytes, | op 8 | r1 4 | r2 4 |
Format 3, 3 bytes, | op 8 | n | i | x | b | p | e |  disp 12 |
Format 4, 4 bytes, | op 8 | n | i | x | b | p | e |  address 20 |

Addressing Modes:
* SIC 
direct, x=0, TA = address
indirect, x=1, TA = address+(X)
(X) represents the contents of register X
* SIC/XE
base relative b=1, p=0, TA=(B) + disp, (0<= disp <= 4095)
program-counter relative b=0, p=1, TA=(PC) + disp, (-2048<= disp <=2047)
direct addressing, b=0, p=0, TA=address
indexed addressing, x=1,TA=(...) + (X)
immediate addressing, i=1, n=0, TA is the operand value
indirect addressing, i=0, n=1, word given by TA is the operand value
simple addressing, i=0 and n=0, or i=1 and n=1, TA is the location of operand


Instruction Set:
1. Store and load registers: LDA, LDX, STA, STX, etc
2. Integer arithmetic operation: ADD, SUB, MUL, DIV (all arithmetic operations 
use register A and a word in memory).
3. Condition code: COMP (compares the value in register A with a word in memory 
and sets a CC to indicate a result), JLT, JEQ (test the setting of CC and jump 
accordingly.
4. Subroutine linkage: JSUB, RSUB

Input and Output:
* SIC
1. Trasfer 1-byte at a time to or from the rightmost 8 bits of register A
2. Each device as a unique 8-bit code.
3. I/O instructions specify the device code as operand
4. TD, test device instruction on  device is ready to send/receive (< ready,
= not ready)
* SIC/XE
I/O channels that can be used toperform input and output while CPU is executing 
instructions


The Simple SIC Assember
***********************
Translates source program to object code. It converts mnemonic code to machine 
language and symbolic operands to machine addresses.  It builds machine
instructions in the proper format and converts data constance to their machine 
representation.  It writes the object program and assembly listing.

Pass 1:
1. Assign addresses to all statements in the program
2. Save the values (addresses) assigned to all labels for use in Pass 2.
3. Perform some processing of assembler directives (determine length of data
areas).

Pass 2:
1. Assemble intructions 
2. Generate data values defined by BYTE, WORD, etch
3. Perform processing of assembler directives not done during Pass 1
4. Write object program and assembly listing.


Data Structures
******************
1. OPTAB, Operation Code Table, used to look up mnemonic operation codes and 
translate into machine language
2. SYMTAB, Symbol Table, used to store values( addresses ) assigned to labels.
3. LOCCTR, Location Counter, used to variable to help assign addresses. 
Initialized ast START statement.
4. 

