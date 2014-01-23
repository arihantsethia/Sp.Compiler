#include "code_gen.h"
#include "lex.h"
#include <iostream>
#include <cstdio>

using namespace std;

int main ()
{
    statement ();
    if(!match(EOI)){
        fprintf(stderr," Error : End of File Expected \n");
    }
    return 0;
}
