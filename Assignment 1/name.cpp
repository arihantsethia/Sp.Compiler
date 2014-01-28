#include "header.h"
#include "lex.h"
#include "name.h"

char  *Names[] = { "%rax", "%rbx", "%rcx", "%rdx","%r8","%r9","%r10","%r11","%r12","%r13","%r14","%r15" }; //, "esi", "edi"
char  **Namep  = Names;

map<string,int> registers ;
int registerCount=0;

char  *newname()
{
	if( Namep >= &Names[ sizeof(Names)/sizeof(*Names) ] )
	{
		fprintf( stderr, "%d: Expression too complex\n", yylineno );
		exit( 1 );
	}
	int count =0;
	while(registers[*Namep]){
		if( Namep >= &Names[ sizeof(Names)/sizeof(*Names) ] ){
			*Namep = Names[0];
			count++;
			if(count==2){
				fprintf( stderr, "%d: Expression too complex\n", yylineno );
				exit( 1 );
			}
		}
		*Namep++;
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
