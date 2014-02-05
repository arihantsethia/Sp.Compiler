#include<stdio.h>
extern int yylex() ;
extern char *yytext ;
extern int yyleng ;
int main()
{
	int i =  0 ;

	while(i++ <= 60)
	{
		int d = yylex();
		printf("%d\n",d) ;
	}

	return 0 ;
}