#include "lex.h"
#include "code_gen.h"

FILE * fp;

int main (int argc, char *argv) {
    fp = fopen ("a.asm", "w+");
    fprintf(fp,"global _start\nsection .text\n_start:\n");
    statement ();
    if(!match(EOI)) {
        fprintf( stderr, "%sLine %d %s\'EOI\'%s expected\n",KBLU,yylineno,KRED,KNRM);
        exit(1);
    }
    fprintf(fp," mov rax,60\nmov rdi,0\nsyscall\n");
    fclose(fp);
    system("nasm -f elf64 -o a.o a.asm");
    system("ld -o a.out a.o");
    remove( "a.o" );
    return 0;
}
/*nasm -f elf64 -o hello64.o hello64.nasm */
/*ld -o hello64 hello64.o*/
/*./hello64*/
