#ifndef LEX_H_INCLUDED
#define LEX_H_INCLUDED

extern char *yytext;
extern int yyleng;
extern int yylineno;
extern int Lookahead;

int yylex(void);
bool is_identifier(string);
bool is_num(string);
bool is_string(string s);
bool is_double(string s);
int match(int);
void advance(void);

#endif
