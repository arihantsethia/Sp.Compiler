#include "header.h"
#include "lex.h"
#include "code_gen.h"

FILE * fp;

int main (int argc, char *argv)
{
	fp = fopen ("a.s", "w+");
	fprintf(fp,".LC0: \n\t.string	\"%%d\" \n\t.text \n\t.globl	main\n\t.type	main, @function \n");
	fprintf(fp,"main: \n.LFB0: \n");
	fprintf(fp,"pushq\t%rbp\nmovq\t%rsp, %rbp\n");
	statement ();
	if(!match(EOI))
	{
		fprintf( stderr, "%sError : Line %d %s\'EOI\'%s expected\n",KBLU,yylineno,KRED,KNRM);
		exit(1);
	}
	fprintf(fp,"leave\nret\n");
	fclose(fp);
	system("gcc a.s");
	return 0;
}
/*nasm -f elf64 -o hello64.o hello64.nasm */
/*ld -o hello64 hello64.o*/
/*./hello64*/
