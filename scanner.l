%option yylineno
%{
#include <string>
#include <iostream>
#include "parser.hpp"
#include "ast.h"
#define SAVE_VALUE yylval.str = new std::string(yytext, yyleng)
#define TOK(t) (yylval.type = (t))

extern "C" int yywrap() {}

%}

%%

[ \t\n]							;
"func"							return TOK(FUNC);
"for"							return TOK(FOR);
"while"							return TOK(WHILE);
"if"							return TOK(IF);
"else"							return TOK(ELSE);
"print"							return TOK(PRINT);
[a-zA-Z_][a-zA-Z0-9_]*			SAVE_VALUE; return IDENTIFIER;
[+-]?[0-9]+\.[0-9]+				SAVE_VALUE; return DOUBLE;
[+-]?[0-9]+						SAVE_VALUE; return INTEGER;
"("								return TOK(L_PAREN);
")"								return TOK(R_PAREN);
"{"								return TOK(L_BRACKET);
"}"								return TOK(R_BRACKET);
"="								return TOK(EQ);
"=="							return TOK(COMP_EQ);
"!="							return TOK(COMP_NEQ);
"<"								return TOK(LESS_TH);
">"								return TOK(GREATER_TH);
"<="							return TOK(LESS_TH_OR_EQ);
">="							return TOK(GREATER_TH_OR_EQ);
"&&"							return TOK(AND);
"||"							return TOK(OR);
"+"								return TOK(PLUS);
"-"								return TOK(MINUS);
"/"								return TOK(DIVIDE);
"*"								return TOK(MULTIPLY);
"%"								return TOK(MOD);
";"								return TOK(SEMI_COLON);
","								return TOK(COMMA);
.								std::cout << "Unknown token."; yyterminate();

%%
