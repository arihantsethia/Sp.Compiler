#pragma once
#include<string>
class FRONT
{
public:
	//vector<string> list ;

	char* yytext ;    /* Lexeme (not '\0' terminated)               */
	int   yyleng   ;   /* Lexeme length.                             */
	int   yylineno  ;   /* Input line number                          */
	char  *Names[20] ;   
	char  **Namep  ; 
	 int Lookahead  ;      
	int  length ;
	FRONT(void);
	~FRONT(void);
	
	bool is_number( char* s, int len) ;
	int     lex         ( void );
	int     match       ( int  );
	void    advance     ( void );
	char    *factor     ( void );
	char    *div          (void) ;
	char    *term       ( void );
	char    *expression ( void );
	void    statements  ( void );
	char    *newname    ( void );
	void    freename    ( char* ); 

};

