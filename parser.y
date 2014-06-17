%code requires { #include "ast.h" }

%{

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "ast.h"

extern int yylex();
extern int yylineno;

void yyerror(const char *s) {
	std::cout << "Error near line " << yylineno << " " << s << "\n"; 
}

NBlock *program;

%}

%union{
	int type;
	NIdentifier *ident;
	NExpresion *exp;
	Node *node;
	NBlock *block;
	NAssigmentExpresion *as_exp;
	ExpressionList *exp_list;
	IdentifierList *ident_list;
	std::string *str;
}

%token <str> IDENTIFIER INTEGER DOUBLE STRING
%token <type> EQ COMP_EQ COMP_NEQ 
%token <type> LESS_TH GREATER_TH
%token <type> LESS_TH_OR_EQ GREATER_TH_OR_EQ
%token <type> PLUS MINUS DIVIDE MULTIPLY MOD
%token <type> SEMI_COLON COMMA
%token <type> FUNC
%token <type> L_PAREN R_PAREN
%token <type> L_BRACKET R_BRACKET
%token <type> PRINT
%token <type> IF ELSE
%token <type> FOR WHILE
%token <type> AND OR NOT

%left COMMA
%right EQ
%left OR
%left AND
%left COMP_EQ COMP_NEQ
%left LESS_TH LESS_TH_OR_EQ GREATER_TH GREATER_TH_OR_EQ
%left PLUS MINUS
%left DIVIDE MULTIPLY MOD

%type <ident> Identifier
%type <exp> Expression Constant IfElseExpression Function_Declaration PrintExpresion BinaryExpresion
%type <block> Program Block Expressions
%type <ident_list> Function_Args_Declartion
%type <exp_list> Call_Args

%start Program

%%


Program: Expressions { program = $1; }
;

Expressions: Expression { $$ = new NBlock(); $$->expresions.push_back($1); }
		   | Expressions Expression { $$->expresions.push_back($2); }
;

Expression: Identifier EQ Expression { $$ = new NAssigmentExpresion($1, $3); }
		  | Identifier L_PAREN Call_Args R_PAREN { $$ = new NFunctionCall($1, *$3); delete $3; }
		  | Identifier { $$ = $1; }
		  | Constant { $$ = $1; }
		  | PrintExpresion { $$ = $1; }
		  | Function_Declaration { $$ = $1; }
		  | BinaryExpresion { $$ = $1; }
		  | L_PAREN Expression R_PAREN { $$ = $2; }
		  | IfElseExpression {  $$ = $1; }
		  | FOR Expression SEMI_COLON Expression SEMI_COLON Expression Block { $$ = new NForExpresion($2, $4, $6, $7); }
		  | WHILE Expression Block { $$ = new NWhileExpresion($2, $3); }
		  | Block { $$ = $1; }
;

Block: L_BRACKET Expressions R_BRACKET { $$ = $2; }
;

PrintExpresion: PRINT L_PAREN Call_Args R_PAREN { $$ = new NPrintExpresion(*$3); delete $3; }
;

Function_Declaration: FUNC Identifier L_PAREN Function_Args_Declartion R_PAREN Block { $$ = new NFunctionDeclartion($2, *$4, $6); delete $4; }
;

Function_Args_Declartion: { $$ = new IdentifierList(); } 
						| Identifier { $$ = new IdentifierList(); $$->push_back($1); }
						| Function_Args_Declartion COMMA Identifier { $1->push_back($3);  }
;

Call_Args: { $$ = new ExpressionList(); }
		 | Expression { $$ = new ExpressionList(); $$->push_back($1); }
		 | Call_Args COMMA Expression { $1->push_back($3); }
;


IfElseExpression: IF Expression Block ELSE Block { $$ = new NIfElseExpresion($2, $3, $5);  }
;

Constant: DOUBLE { $$ = new NDouble(atof($1->c_str())); delete $1; }
		| INTEGER { $$ = new NInteger(atoi($1->c_str())); delete $1; }
		| STRING { $$ = new NString($1); }
;

BinaryExpresion: Expression MINUS Expression { $$ = new NBinaryOparator($1, $2, $3); }
		| Expression PLUS Expression { $$ = new NBinaryOparator($1, $2, $3); }
		| Expression MULTIPLY Expression { $$ = new NBinaryOparator($1, $2, $3); }
		| Expression MOD Expression { $$ = new NBinaryOparator($1, $2, $3); }
		| Expression DIVIDE Expression { $$ = new NBinaryOparator($1, $2, $3); }
		| Expression LESS_TH Expression { $$ = new NBinaryOparator($1, $2, $3); }
		| Expression LESS_TH_OR_EQ Expression { $$ = new NBinaryOparator($1, $2, $3); }
		| Expression GREATER_TH Expression { $$ = new NBinaryOparator($1, $2, $3); }
		| Expression GREATER_TH_OR_EQ Expression { $$ = new NBinaryOparator($1, $2, $3); }
		| Expression COMP_EQ  Expression { $$ = new NBinaryOparator($1, $2, $3); }
		| Expression COMP_NEQ  Expression { $$ = new NBinaryOparator($1, $2, $3); }
		| Expression AND  Expression { $$ = new NBinaryOparator($1, $2, $3); }
		| Expression OR  Expression { $$ = new NBinaryOparator($1, $2, $3); }
;

Identifier: IDENTIFIER { $$ = new NIdentifier(*$1); delete $1; }
;

