#define EOI		    0	/* End of input			*/
#define SEMI		1	/* ; 				*/
#define PLUS 		2	/* + 				*/
#define MINUS       3   /* -                */
#define TIMES       4   /* *                */
#define DIV		    5	/* / 				*/
#define LP		    6	/* (				*/
#define RP		    7	/* )				*/
#define NUM	        8	/* Decimal Number or Identifier */
#define ID          9
#define BEGIN       10
#define END         11
#define IF          12
#define THEN        13
#define WHILE       14
#define DO          15
#define EQUALS      16
#define GREATER     17
#define LESS        18
#define GTOET       19
#define LTOET       20
#define REQUALS     21

extern char *yytext;		/* in lex.c			*/
extern int yyleng;
extern int yylineno;

int match(int);
void advance(void);
bool is_number(char * s , int len);


#define KNRM  "\x1B[0m"
#define KRED  "\x1B[1;31m"
#define KGRN  "\x1B[1;32m"
#define KYEL  "\x1B[1;33m"
#define KBLU  "\x1B[1;34m"
#define KMAG  "\x1B[1;35m"
#define KCYN  "\x1B[1;36m"
#define KWHT  "\x1B[1;37m"
