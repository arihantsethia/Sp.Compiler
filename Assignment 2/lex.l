D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{
	#include <stdio.h>
	#include "lex.h"
%}
%%
[ \t\n]					;
";"						return SEMI ;
"="					 	return EQUALS ;
"=="					return REQUALS ;
"!="					return NEQUAL ;
"<"						return LESS	 ;
"<="					return LTOET ;
">"						return GREATER ;
">="					return GTOET ;
"("						return LP ;
")"						return RP ;
"{"						return LB ;
"}"						return RB ;
"+"						return PLUS ;
"-"						return MINUS ;
"*"						return TIMES ;
"/"						return DIV ;
"if"					return IF ;
"then"					return THEN ;
"while"					return WHILE_LOOP ;
"do"					return DO_LOOP ;
"int"					return INT ;
"float"					return FLOAT ;
"double"				return DOUBLE ;
"char"					return CHAR ;
"short"					return SHORT ;
"break"					return BREAK ;
"for"					return FOR ;
"continue"				return CONTINUE ;
"extern"				return EXTERN ;
"void"					return VOID ;
"main"					return MAIN ;
"return"				return RETURN ;
[_a-zA-Z][_a-zA-Z0-9]*  return ID ;
[0-9]+\.[0-9]*		  	return DOUBLE ;
[0-9]+				  	return NUM ;
.						{ /* ignore bad characters */ }
%%

yywrap() {
	return(1);
}