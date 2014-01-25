#include "lex.h"

char* yytext = ""; /* Lexeme (not '\0'
					  terminated)              */
int yyleng   = 0;  /* Lexeme length.           */
int yylineno = 0;  /* Input line number        */

int lex(void)
{

	static char input_buffer[102004];
	char        *current;

	current = yytext + yyleng; /* Skip current
								 lexeme        */

	while(1)        /* Get the next one         */
	{
		while(!*current )
		{
			/* Get new lines, skipping any leading
			* white space on the line,
			* until a nonblank line is found.
			*/

			current = input_buffer;
			if(!gets(input_buffer))
			{
				*current = '\0' ;

				return EOI;
			}
			++yylineno;
			while(isspace(*current))
				++current;
		}
		for(; *current; ++current)
		{
			/* Get the next token */
			yytext = current;
			yyleng = 1;
			switch( *current )
			{
			case ';':
				return SEMI;
			case '+':
				return PLUS;
			case '-':
				return MINUS;
			case '*':
				return TIMES;
			case '/':
				return DIV;
			case '(':
				return LP;
			case ')':
				return RP;
			case '\n':
			case '\t':
			case ' ' :
				break;
			case ':':
				if(*(current+1) == '=')
				{
					yyleng=2;
					return EQUALS;
				}
				else
				{
					fprintf( stderr, "%s\'%c\'%s unknown\n",KRED,*current,KNRM);
					exit(1);
				}
			case '=':
				return REQUALS;
			case '>':
				if(*(current+1) == '=')
				{
					yyleng=2;
					return GTOET;
				}
				return GREATER;
			case '<':
				if(*(current+1) == '=')
				{
					yyleng=2;
					return LTOET;
				}
				return LESS;
			default:
				if(!isalnum(*current))
				{
					fprintf( stderr, "%s\'%c\'%s is not alpha-numeric\n",KRED,*current,KNRM);
					exit(1);
				}
				else
				{
					char* prev ;
					prev = current ;
					while(isalnum(*current))
						current++;
					yyleng = current - yytext;
					if(yyleng==2 && !strncmp("if",prev, 2))
						return IF ;
					else if(yyleng==2 && !strncmp("do",prev, 2))
						return DO ;
					else if(yyleng==3 && !strncmp("end",prev, 3))
						return END ;
					else if(yyleng==4 && !strncmp("then",prev, 4))
						return THEN ;
					else if(yyleng==5 && !strncmp("while",prev, 5))
						return WHILE ;
					else if(yyleng== 5 && !strncmp("begin",prev, 5))
						return BEGIN ;

					if(is_number(prev,yyleng))
						return NUM ;
					else if(isdigit(*prev))
					{
						fprintf( stderr, "This is not right character %s\'%c\'%s\n",KRED,*current,KNRM);
						exit(1);
					}
					else
						return ID ;
				}
				break;
			}
		}
	}
}


static int Lookahead = -1; /* Lookahead token  */

int match(int token)
{
	/* Return true if "token" matches the
	   current lookahead symbol.                */

	if(Lookahead == -1)
		Lookahead = lex();

	return token == Lookahead;
}

void advance(void)
{
	/* Advance the lookahead to the next
	   input symbol.                               */

	Lookahead = lex();
}

bool is_number(char * s , int len)
{
	int i = 0 ;
	bool ans = true ;
	for(i=0; i<len; i++)
		if(!isdigit(*(s+i)))
			ans = false ;
	return ans ;
}
