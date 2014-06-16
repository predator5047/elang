#include <iostream>
#include <cstdio>
#include "ast.h"

extern int yyparse();
extern FILE *yyin;
extern NBlock *program;

int main(int argc, char **argv) {
	using namespace std;

	if (argc == 2) {
		FILE *input = fopen(argv[1], "r");
		if (input) {
			yyin = input;
			yyparse();
			fclose(input);
		}
	} else {
		yyparse();
	}

	program->Interpret();

	return 0;
}
