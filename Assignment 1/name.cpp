#include "header.h"
#include "lex.h"

char  *Names[] = { "%rax", "%rbx", "%rcx", "%rdx","%r8","%r9","%r10","%r11","%r12","%r13","%r14","%r15" }; //, "esi", "edi"
char  **Namep  = Names;
char  *newname()
{
	if( Namep >= &Names[ sizeof(Names)/sizeof(*Names) ] )
	{
		fprintf( stderr, "%d: Expression too complex\n", yylineno );
		exit( 1 );
	}
	registerCount++;
	registers[*Namep] = true;
	return( *Namep++ );
}

void freename(char    *s)
{
	if( Namep > Names ){
	    registers[s] = false;
		*--Namep = s;
        registerCount--;
	}
	else
		fprintf(stderr, "%d: (Internal error) Name stack underflow\n",
				yylineno );
}
