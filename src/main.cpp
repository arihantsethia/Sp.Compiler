#include "header.h"
#include "lex.h"
#include "code_gen.h"
#include "name.h"

FILE * fp;

int main (int argc, char *argv)
{
	registers["%rax"]= false;
	registers["%rbx"]= false;
	registers["%rcx"]= false;
	registers["%rdx"]= false;
	registers["%r8"]= false;
	registers["%r9"]= false;
	registers["%r10"]= false;
	registers["%r11"]= false;
	registers["%r12"]= false;
	registers["%r13"]= false;
	registers["%r14"]= false;
	registers["%r15"]= false;

	fp = fopen ("a.s", "w+");
	fprintf(fp,".LC0: \n\t.string	\"%%lld\\n\" \n\t.text \n\t.globl	main\n\t.type	main, @function \n");
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
