#include <iostream>
#include "PassTwo.h"
#include "PassOne.h"
#include "Assembler.h"
using namespace std;



int main(int argc, char * argv[]) {
    if (argc !=2){
        cout <<"USAGE: as2 FILEPATH_TO_ASM_SRC" <<endl;
        return 1;
    }
    string path(argv[1]);
   // Assembler sourcefilein(path);
   PassOne source_filein(path);
   int length =  source_filein.getProgramLength();
   // source_filein.printSymTab();
   cout << hex << length;
   PassTwo intermediate_filein( "intermediate.txt" );
    return 0;
    
}