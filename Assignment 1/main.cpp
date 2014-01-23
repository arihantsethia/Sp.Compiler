#include "lex.h"
#include "code_gen.h"

int main () {
    printf("global _start\nsection .text\n_start:\n");
    statement ();
    if(!match(EOI)) {
        fprintf( stderr, "%sLine %d %s\'EOI\'%s expected\n",KBLU,yylineno,KRED,KNRM);
        exit(1);
    }
    printf(" mov rax,60\nmov rdi,0\nsyscall\n");
    return 0;
}


/*nasm -f elf64 -o hello64.o hello64.nasm */
/*ld -o hello64 hello64.o*/
/*./hello64*/
