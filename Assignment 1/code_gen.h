#ifndef CODE_GEN_H_INCLUDED
#define CODE_GEN_H_INCLUDED
//#include "Identifier.h"

void statement();
char    *factor     ( void );
char    *term       ( void );
char    *expression ( void );
void expression_prime( void );
void opt_statements ( void );

extern char *newname( void       );
extern void freename( char *name );
extern FILE *fp;
//static vector< vector<Identifier> > ids;
//static int scope = 0;

#endif // CODE_GEN_H_INCLUDED
