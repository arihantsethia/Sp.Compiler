#include "FRONT.h"
#include<vector>
#include<string>
#include "var.h"
#include<math.h>

FRONT::FRONT(void)
{
	
	yytext   = "";    /* Lexeme (not '\0' terminated)               */
	yyleng   = 0 ;   /* Lexeme length.                             */
	yylineno = 0 ;   /* Input line number                          */

	int intVar = 10;

	Names[0] = "t0" ;
	Names[1] = "t1" ;
	Names[2] = "t2" ;
	Names[3] = "t3" ;
	Names[4] = "t4" ;
	Names[5] = "t5" ;
	Names[6] = "t6" ;
	Names[7] = "t7" ;
	Namep  = Names;  
	Lookahead = -1 ;      

}

bool FRONT:: is_number(char * s , int len)
{
    int i = 0 ;
	bool ans = true ;
    for(i=0;i<len;i++)
		if(!isdigit(*(s+i))) 
			ans = false ;
    return ans ;
}

int FRONT:: lex(void)
{
	//printf("We are in lex\n") ;
    static char input_buffer[1024];
    char        *current;
	
    current = yytext + yyleng; /* Skip current          lexeme        */

    while(1)
    {                  /* Get the next one         */
        
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
            yylineno++;
            
            while(isspace(*current))
                current++;
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
				case '=':
					return EQUAL ;
				case '\n':
                case '\t':
                case ' ' :
                    break;
                

                default:
                if(!isalnum(*current))
                    fprintf(stderr, "This is not right character <%c>\n", *current);
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
					       fprintf(stderr, "This is not right character <%c>\n", *current);	
					else
						return ID ;
			
				}
				
                break;
            }
        }
    }
}

int FRONT:: match(int token)
{
    /* Return true if "token" matches the  current lookahead symbol.                */

    if(Lookahead == -1)
        Lookahead = lex();

    return token == Lookahead;
}

void FRONT::advance(void)
{
     /* Advance the lookahead to the next input symbol.                               */
    Lookahead = lex();
}

void FRONT:: statements()
{
    /*  statements -> id = expression  |  if expression else statements | do expression while statements | begin opt end  */
    //printf("we are in statement   %c \n",yytext) ;
    char *tempvar;

    while( !match(EOI) )
    {
		if(match(ID))
		{
			advance() ;
			if(match(EQUAL))
			{
				advance();
				tempvar = expression() ;
				if( match( SEMI ) )
					advance();
				else
					fprintf( stderr, "semicolon missing\n", yylineno );
				// now we have to assign values to it

			}else
			{
				fprintf( stderr, "equal mising\n", yylineno );
			}

		}else if(match(WHILE))
		{
				advance() ;
				tempvar = expression() ;
				if(match(DO))
				{
					advance() ;
					statements() ;
				}
		}
		else if(match(IF))
		{
			advance() ;
			tempvar = expression() ;
			if(match(THEN))
			{
				advance() ;
				statements() ;
			}else
			{
					fprintf( stderr, "no then\n", yylineno );
			}
		}else if(match(BEGIN))
		{
			advance() ;
			while(!match(END))
			{
				statements() ;
				advance() ;
			}
			advance() ;
		}
        else
		{
			expression() ;
			if(match(SEMI))
				advance() ;
			else
				fprintf( stderr, "EXPRESSION MUST END WITH SEMICOLON\n", yylineno );
		}
     }
}

char* FRONT::expression()
{
    /* expression -> term expression'
     * expression' -> PLUS term expression' |  epsilon
     */

    //printf("we are in expression   %c \n",yytext) ;

    char  *tempvar, *tempvar2;

    tempvar = term();
    while( match( PLUS ) || match(MINUS) )
    {
		if(match(PLUS))
		{
			advance();
			tempvar2 = term();
			printf("    %s += %s\n", tempvar, tempvar2 );
		}	
		else
		{
			advance();
			tempvar2 = term();
			printf("    %s -= %s\n", tempvar, tempvar2 );
		}	
        freename( tempvar2 );
    }
    return tempvar;
}


char* FRONT::term()
{
    char  *tempvar, *tempvar2 ;

    tempvar = div();
    while( match( TIMES ) )
    {
        advance();
        tempvar2 = div();
        printf("    %s *= %s\n", tempvar, tempvar2 );
        freename( tempvar2 );
    }

    return tempvar;
}

char* FRONT::div()
{
    char  *tempvar, *tempvar2 ;

    tempvar = factor();
    while( match(DIV) )
    {
        advance();
        tempvar2 = factor();
        printf("    %s /= %s\n", tempvar, tempvar2 );
        freename( tempvar2 );
    }

    return tempvar;
}

char* FRONT::factor()
{
    char *tempvar;

    if( match(NUM))
    {
	/* Print the assignment instruction. The %0.*s conversion is a form of
	 * %X.Ys, where X is the field width and Y is the maximum number of
	 * characters that will be printed (even if the string is longer). I'm
	 * using the %0.*s to print the string because it's not \0 terminated.
	 * The field has a default width of 0, but it will grow the size needed
	 * to print the string. The ".*" tells printf() to take the maximum-
	 * number-of-characters count from the next argument (yyleng).
	 */

        printf("    %s = %0.*s\n", tempvar = newname(), yyleng, yytext );
        advance();
    }else if(match(ID))
	{
	    printf("    %s = %0.*s\n", tempvar = newname(), yyleng, yytext );
  
		advance() ;
	
	}else if( match(LP) )
    {
        advance();
        tempvar = expression();
        if( match(RP) )
            advance();
        else
            fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno );
    }
    else
	fprintf( stderr, "%d: Number or identifier expected\n", yylineno );

    return tempvar;
}



   
char* FRONT::newname()   
{   
    if( Namep >= &Names[ sizeof(Names)/(sizeof(*Names)) ] )   
    {   
        fprintf( stderr, ": Expression too complex\n");   
        //exit( 1 );   
    }
    //fprintf( stderr, "%d: you reach here\n", yylineno );   
    return( *Namep++ );   
}  
   
void FRONT::freename(char *s)   
{   
    if( Namep > Names )   
    *--Namep = s;   
    else   
    fprintf(stderr, "%d: (Internal error) Name stack underflow\n",   
                                yylineno );   
}   




FRONT::~FRONT(void)
{
}
