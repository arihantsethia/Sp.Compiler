#include <cstdio>
#include <cstdlib>
#include "lex.h"

char  *Names[] = { "%rax", "%rbx", "%rcx", "%rdx" }; //, "esi", "edi"
char  **Namep  = Names;
char  *newname()
{
	if( Namep >= &Names[ sizeof(Names)/sizeof(*Names) ] )
	{
		fprintf( stderr, "%d: Expression too complex\n", yylineno );
		exit( 1 );
	}
	registerCount++;
	return( *Namep++ );
}

void freename(char    *s)
{
	if( Namep > Names ){
		*--Namep = s;
        registerCount--;
	}
	else
		fprintf(stderr, "%d: (Internal error) Name stack underflow\n",
				yylineno );
}
