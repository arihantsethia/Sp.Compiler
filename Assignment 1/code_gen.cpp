#include "header.h"
#include "lex.h"
#include "code_gen.h"

using namespace std;

void statement()
{
	/*  statements -> expression SEMI  |  expression SEMI statements  */
	int i,f;
	char *tempvar;
	string tempname;
	if(match( ID ))
	{
		tempname.assign(yytext, yytext + yyleng);
		for(i=scope,f=0; i>=0; i--)
		{
			if(ids[i].find(tempname)!=ids[i].end())
			{
				f = 1;
				break;
			}
		}
		if(!f)
		{
			ids[scope][tempname] = stackpos;
			stackpos +=8;
		}
		advance();
		if(match( EQUALS ))
		{
			advance();
			tempvar = expression();
			if(!f)
                fprintf(fp,"pushq\t%s\n", tempvar);
            else{
                fprintf(fp,"movq\t%s,-%d(%rbp)\n", tempvar,ids[i][tempname]);
            }
			freename(tempvar);
		}
		else
		{
			fprintf( stderr, "%sError : Line %d %s\':=\'%s expected\n",KBLU,yylineno,KRED,KNRM);
			exit(1);
		}
	}
	else if( match( IF ))
	{

		advance();
        int d = _count++;
        expression_prime(d);

		if(match (THEN) )
		{
			advance();
			statement();
			fprintf(fp,".L%d:\n",d);
		}
		else
		{
			fprintf( stderr, "%sError : Line %d %s\'then\'%s expected\n",KBLU,yylineno,KRED,KNRM);
			exit(1);
		}
	}
	else if( match( WHILE ))
	{
		advance();
		int d , _d ;
		_d = _count++ ;
		 d = _count++ ;
		fprintf(fp,".L%d:\n",_d);

		expression_prime(d);

		if(match (DO) )
		{
			advance();
			statement();
			fprintf(fp,"jmp\t.L%d\n",_d);
            fprintf(fp,".L%d:\n",d);

		}
		else
		{
			fprintf( stderr, "%sError : Line %d %s\'do\'%s expected\n",KBLU,yylineno,KRED,KNRM);
			exit(1);
		}
	}
	else if( match( BEGIN ))
	{
		scope++;
		scopep[scope] = stackpos;
		advance();
		opt_statements();
		if(match( END ))
		{
		    tempvar=newname();
		    while(scopep[scope]<stackpos){
                stackpos-=8;
                fprintf(fp,"popq\t%s\n", tempvar );
		    }
		    freename(tempvar);
			ids[scope].clear();
			scope--;
			advance();
		}
		else
		{
			fprintf( stderr, "%sError : Line %d %s\'end\'%s expected\n",KBLU,yylineno,KRED,KNRM);
			exit(1);
		}
	}
	return;
}

char    *expression()
{
	/* expression -> term expression'
	 * expression' -> PLUS term expression' |  epsilon
	 */

	char  *tempvar, *tempvar2;

	tempvar = term();
	while( match( PLUS ) || match(MINUS) )
	{
	    bool flag= false;
		if(match(PLUS))
		{
			advance();
			if(registerCount == RCOUNT ){
                fprintf(fp,"pushq\t%s\n",tempvar);
                flag = true;
                freename(tempvar);
                stackpos+=8;
			}
			tempvar2 = term();
			if(flag){
                fprintf(fp,"popq\t%s\n",tempvar=newname());
                stackpos-=8;
			}
			fprintf(fp,"addq\t%s,%s\n",tempvar2,tempvar);
			//fprintf(fp,"push %s\n",tempvar);
			//fprintf(fp,"    %s += %s\n", tempvar, tempvar2 );

		}
		else
		{
			advance();
			if(registerCount == RCOUNT ){
                fprintf(fp,"pushq\t%s\n",tempvar);
                flag = true;
                freename(tempvar);
                stackpos+=8;
			}
			tempvar2 = term();
			if(flag){
                fprintf(fp,"popq\t%s\n",tempvar=newname());
                stackpos-=8;
			}
			fprintf(fp,"subq\t%s,%s\n",tempvar2,tempvar);
			//fprintf(fp,"    %s -= %s\n", tempvar, tempvar2 );
		}
		freename(tempvar2);
	}
	return tempvar;
}

char    *term()
{
	char  *tempvar, *tempvar2;

	tempvar = factor();
	while( match(TIMES) || match(DIV) )
	{
	    bool flag=false;
		if(match(TIMES))
		{
			advance();
			if(registerCount == RCOUNT ){
                fprintf(fp,"pushq\t%s\n",tempvar);
                flag = true;
                freename(tempvar);
                stackpos+=8;
			}
			tempvar2 = factor();
			if(flag){
                fprintf(fp,"popq\t%s\n",tempvar=newname());
                stackpos-=8;
			}
			fprintf(fp,"imulq\t%s,%s\n",tempvar2,tempvar);
			// fprintf(fp,"    %s *= %s\n", tempvar, tempvar2 );
		}
		else
		{
			advance();
			if(registerCount == RCOUNT ){
                fprintf(fp,"pushq\t%s\n",tempvar);
                flag = true;
                freename(tempvar);
                stackpos+=8;
			}
			tempvar2 = factor();
			if(flag){
                fprintf(fp,"popq\t%s\n",tempvar=newname());
                stackpos-=8;
			}
			stringstream fout;
			if(registers["%rax"] == true && !strcmp("%rax",tempvar) ){
                fprintf(fp,"pushq\t%rax\n");
                fout<<"popq\t%rax\n";
			}
            if(registers["%rdx"] == true && !strcmp("%rdx",tempvar2)){
                fprintf(fp,"pushq\t%rdx\n");
                fout<<"popq\t%rdx\n";
            }
            if(strcmp("%rax",tempvar))
                fprintf(fp,"movq\t%s, %rax\n",tempvar);
            fprintf(fp,"movq\t%rax, %rdx\n");
            fprintf(fp,"sarq\t$63, %rdx\n");
			fprintf(fp,"idivq\t%s\n",tempvar2);
			if(!strcmp("%rax",tempvar))
                fprintf(fp,"movq\t%rax, %s \n",tempvar);
			fprintf(fp,"%s",fout.str().c_str());
		}
		freename( tempvar2 );
	}
	return tempvar;
}

char    *factor()
{
	char *tempvar;

	if( match(NUM) )
	{
		/* Print the assignment instruction. The %0.*s conversion is a form of
		 * %X.Ys, where X is the field width and Y is the maximum number of
		 * characters that will be printed (even if the string is longer). I'm
		 * using the %0.*s to print the string because it's not \0 terminated.
		 * The field has a default width of 0, but it will grow the size needed
		 * to print the string. The ".*" tells printf() to take the maximum-
		 * number-of-characters count from the next argument (yyleng).
		 */

		fprintf(fp,"movq\t$%0.*s,%s\n" , yyleng, yytext, tempvar = newname());
		advance();

	}
	else if(match(ID))
	{
		int i,f=0;
		string tempname;
		tempname.assign(yytext, yytext + yyleng);
		for(i=scope; i>=0; i--)
		{
			if(ids[i].find(tempname)!=ids[i].end())
			{
				fprintf(fp,"movq\t-%d(%rbp), %s\n", ids[i][tempname],tempvar = newname() );
				f = 1;
				break;
			}
		}
		if(!f){
			fprintf( stderr, "%sError : Line %d %s'%s'%s not defined\n",KBLU,yylineno,KRED,tempname.c_str(),KNRM);
            exit(1);
		}
		advance();
	}
	else if( match(LP) )
	{
		advance();
		tempvar = expression();
		if( match(RP) )
			advance();
		else
		{
			fprintf( stderr, "%sError : Line %d %s')'%s expected\n",KBLU,yylineno,KRED,KNRM);
			exit(1);
		}
	}
	else
	{
		fprintf( stderr, "%sError : Line %d %s'number or identifier'%s expected\n",KBLU,yylineno,KRED,KNRM);
		exit(1);
	}

	return tempvar;
}

void expression_prime ( int d )
{
	char *tempvar1 = expression();
	char *tempvar;
	if(match(GREATER))
	{
		advance();
		tempvar = expression();
        fprintf(fp,"cmp\t%s, %s\n", tempvar, tempvar1 );
        fprintf(fp,"jle .L%d\n",d);
	}
	else if(match(LESS))
	{
		advance();
		tempvar = expression();
        fprintf(fp,"cmp\t%s, %s\n", tempvar, tempvar1 );
        fprintf(fp,"jge .L%d\n",d);
	}
	else if(match(REQUALS))
	{
		advance();
		tempvar = expression();
        fprintf(fp,"cmp\t%s, %s\n", tempvar, tempvar1 );
        fprintf(fp,"jne .L%d\n",d);
	}
	else if(match(GTOET))
	{
		advance();
		tempvar = expression();
        fprintf(fp,"cmp\t%s, %s\n", tempvar, tempvar1 );
        fprintf(fp,"jl .L%d\n",d);
	}
	else if(match(LTOET))
	{
		advance();
		tempvar = expression();
        fprintf(fp,"cmp\t%s, %s\n", tempvar, tempvar1 );
        fprintf(fp,"jg .L%d\n",d);
	}
	else
	{
		fprintf( stderr, "%sError : Line %d %s'Relational Operator'%s expected\n",KBLU,yylineno,KRED,KNRM);
		exit(1);
	}
}

void opt_statements ( void )
{

	if(!match(END))
	{
		while(1)
		{
			statement();
			if(!match(SEMI))
			{
				break;
			}
			else
			{
				advance();
			}
			if(match(END))
			{
				fprintf( stderr, "%sError : Line %d %s'statement'%s expected\n",KBLU,yylineno,KRED,KNRM);
				exit(1);
			}
		}
	}
}
