#include "code_gen.h"
#include "lex.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main ()
{
    statement ();
    if(!match(EOI)){
       fprintf( stderr, "%sLine %d %s\'EOI\'%s expected\n",KBLU,yylineno,KRED,KNRM);
       exit(1);
    }
    return 0;
}
