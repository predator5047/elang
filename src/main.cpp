#include <iostream>
#include <cstdio>
#include "ast.h"

extern int yyparse();
extern NBlock *program;

int main(int argc, char **argv) {
	yyparse();

	program->Interpret();

	return 0;

}
