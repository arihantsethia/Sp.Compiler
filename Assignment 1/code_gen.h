#ifndef CODE_GEN_H_INCLUDED
#define CODE_GEN_H_INCLUDED

void statement();
char    *factor     ( void );
char    *term       ( void );
char    *expression ( void );
char    *expression_prime ( void );
void opt_statements ( void );

extern char *newname( void       );
extern void freename( char *name );

#endif // CODE_GEN_H_INCLUDED
