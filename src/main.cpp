#include <iostream>
#include <cstdio>
#include "ast.h"

extern int yyparse();
extern FILE *yyin;
extern NBlock *program;

int main(int argc, char **argv) {
	if (argc == 2) {
		FILE *in = fopen(argv[1], "r");
		if (in) {
			yyin = in;
			yyparse();
			fclose(in);
		}		
	} else {
		yyparse();
	}

	program->Interpret();

	return 0;

}
