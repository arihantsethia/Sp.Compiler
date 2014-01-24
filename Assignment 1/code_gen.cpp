#include "lex.h"
#include "code_gen.h"

using namespace std;

void statement() {
    /*  statements -> expression SEMI  |  expression SEMI statements  */
    int i;
    char *tempvar;
    string tempname;
    if(match( ID )) {
        tempname.assign(yytext, yytext + yyleng);
        ids[scope][tempname] = stackpos++;
        advance();
        if(match( EQUALS )) {
            advance();
            tempvar = expression();
            fprintf(fp,"mov [rbp+%d],%s\n",ids[scope][tempname], tempvar);
            freename(tempvar);
        } else {
            fprintf( stderr, "%sLine %d %s\':=\'%s expected\n",KBLU,yylineno,KRED,KNRM);
            exit(1);
        }
    } else if( match( IF )) {
        advance();
        expression_prime();
        if(match (THEN) ) {
            advance();
            statement();
        } else {
            fprintf( stderr, "%sLine %d %s\'then\'%s expected\n",KBLU,yylineno,KRED,KNRM);
            exit(1);
        }
    } else if( match( WHILE )) {
        advance();
        expression_prime();
        if(match (DO) ) {
            advance();
            statement();
        } else {
            fprintf( stderr, "%sLine %d %s\'do\'%s expected\n",KBLU,yylineno,KRED,KNRM);
            exit(1);
        }
    } else if( match( BEGIN )) {
        scope++;
        advance();
        opt_statements();
        if(match( END )) {
            ids[scope].clear();
            scope--;
            advance();
        } else {
            fprintf( stderr, "%sLine %d %s\'end\'%s expected\n",KBLU,yylineno,KRED,KNRM);
            exit(1);
        }
    }
    return;
}

char    *expression() {
    /* expression -> term expression'
     * expression' -> PLUS term expression' |  epsilon
     */

    char  *tempvar, *tempvar2;

    tempvar = term();
    while( match( PLUS ) || match(MINUS) ) {
        if(match(PLUS)) {
            advance();
            fprintf(fp,"push %s\n",tempvar);
            freename(tempvar);
            stackpos++;
            tempvar2 = term();
            stackpos--;
            fprintf(fp,"pop %s\n",tempvar=newname());
            fprintf(fp,"add %s,%s\n",tempvar,tempvar2);
            //fprintf(fp,"push %s\n",tempvar);
            //fprintf(fp,"    %s += %s\n", tempvar, tempvar2 );

        } else {
            advance();
            fprintf(fp,"push %s\n",tempvar);
            freename(tempvar);
            stackpos++;
            tempvar2 = term();
            stackpos--;
            fprintf(fp,"pop %s\n",tempvar=newname());
            fprintf(fp,"sub %s,%s\n",tempvar,tempvar2);
            //fprintf(fp,"    %s -= %s\n", tempvar, tempvar2 );
        }
        freename(tempvar2);
    }
    return tempvar;
}

char    *term() {
    char  *tempvar, *tempvar2;

    tempvar = factor();
    while( match(TIMES) || match(DIV) ) {
        if(match(TIMES)) {
            advance();
            fprintf(fp,"push %s\n",tempvar);
            freename(tempvar);
            stackpos++;
            tempvar2 = factor();
            stackpos--;
            fprintf(fp,"pop %s\n",tempvar=newname());
            fprintf(fp,"imul %s,%s\n",tempvar,tempvar2);
            // fprintf(fp,"    %s *= %s\n", tempvar, tempvar2 );
        } else {
            advance();
            fprintf(fp,"push %s\n",tempvar);
            freename(tempvar);
            stackpos++;
            tempvar2 = factor();
            stackpos--;
            fprintf(fp,"idiv %s,%s\n",tempvar,tempvar2);

            //fprintf(fp,"    %s /= %s\n", tempvar, tempvar2 );
        }
        freename( tempvar2 );
    }
    return tempvar;
}

char    *factor() {
    char *tempvar;

    if( match(NUM) ) {
        /* Print the assignment instruction. The %0.*s conversion is a form of
         * %X.Ys, where X is the field width and Y is the maximum number of
         * characters that will be printed (even if the string is longer). I'm
         * using the %0.*s to print the string because it's not \0 terminated.
         * The field has a default width of 0, but it will grow the size needed
         * to print the string. The ".*" tells printf() to take the maximum-
         * number-of-characters count from the next argument (yyleng).
         */

        fprintf(fp,"mov %s,%0.*s\n", tempvar = newname(), yyleng, yytext );
        advance();

    } else if(match(ID)) {
        int i,f=0;
        string tempname;
        tempname.assign(yytext, yytext + yyleng);
        for(i=scope;i>=0;i--){
            if(ids[i].find(tempname)!=ids[i].end()){
                fprintf(fp,"mov %s,[rbp + %d]\n", tempvar = newname(),ids[i][tempname] );
                f = 1;
                break;
            }
        }
        if(!f)
            fprintf( stderr, "%sLine %d %s\'%s'%s not defined\n",KBLU,yylineno,KRED,tempname.c_str(),KNRM);
        advance();
    } else if( match(LP) ) {
        advance();
        tempvar = expression();
        if( match(RP) )
            advance();
        else {
            fprintf( stderr, "%sLine %d %s\'\)\'%s expected\n",KBLU,yylineno,KRED,KNRM);
            exit(1);
        }
    } else {
        fprintf( stderr, "%sLine %d %s\'number or identifier\'%s expected\n",KBLU,yylineno,KRED,KNRM);
        exit(1);
    }

    return tempvar;
}

void expression_prime ( void ) {
    char *tempvar1 = expression();
    char *tempvar;
    if(match(GREATER)) {
        advance();
        tempvar = expression();
        fprintf(fp,"    %s > %s\n", tempvar1, tempvar );
    } else if(match(LESS)) {
        advance();
        tempvar = expression();
        fprintf(fp,"    %s < %s\n", tempvar1, tempvar );
    } else if(match(REQUALS)) {
        advance();
        tempvar = expression();
        fprintf(fp,"    %s = %s\n", tempvar1, tempvar );
    } else if(match(GTOET)) {
        advance();
        tempvar = expression();
        fprintf(fp,"    %s >= %s\n", tempvar1, tempvar );
    } else if(match(LTOET)) {
        advance();
        tempvar = expression();
        fprintf(fp,"    %s <= %s\n", tempvar1, tempvar );
    } else {
        fprintf( stderr, "%sLine %d %s\'Relational Operator\'%s expected\n",KBLU,yylineno,KRED,KNRM);
        exit(1);
    }
}

void opt_statements ( void ) {

    if(!match(END)) {
        while(1) {
            statement();
            if(!match(SEMI)) {
                break;
            } else {
                advance();
            }
            if(match(END)) {
                fprintf( stderr, "%sLine %d %s\'statement\'%s expected\n",KBLU,yylineno,KRED,KNRM);
                exit(1);
            }
        }
    }
}
