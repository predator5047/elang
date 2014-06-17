/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_HOME_ALEXANDRU_DOCUMENTS_ELANG_SRC_PARSER_HPP_INCLUDED
# define YY_YY_HOME_ALEXANDRU_DOCUMENTS_ELANG_SRC_PARSER_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
/* Line 2058 of yacc.c  */
#line 1 "parser.y"
 #include "ast.h" 

/* Line 2058 of yacc.c  */
#line 49 "/home/alexandru/Documents/elang/src/parser.hpp"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     INTEGER = 259,
     DOUBLE = 260,
     EQ = 261,
     COMP_EQ = 262,
     COMP_NEQ = 263,
     LESS_TH = 264,
     GREATER_TH = 265,
     LESS_TH_OR_EQ = 266,
     GREATER_TH_OR_EQ = 267,
     PLUS = 268,
     MINUS = 269,
     DIVIDE = 270,
     MULTIPLY = 271,
     MOD = 272,
     SEMI_COLON = 273,
     COMMA = 274,
     FUNC = 275,
     L_PAREN = 276,
     R_PAREN = 277,
     L_BRACKET = 278,
     R_BRACKET = 279,
     PRINT = 280,
     IF = 281,
     ELSE = 282,
     FOR = 283,
     WHILE = 284,
     AND = 285,
     OR = 286,
     NOT = 287
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 22 "parser.y"

	int type;
	NIdentifier *ident;
	NExpresion *exp;
	Node *node;
	NBlock *block;
	NAssigmentExpresion *as_exp;
	ExpressionList *exp_list;
	IdentifierList *ident_list;
	std::string *str;


/* Line 2058 of yacc.c  */
#line 109 "/home/alexandru/Documents/elang/src/parser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_HOME_ALEXANDRU_DOCUMENTS_ELANG_SRC_PARSER_HPP_INCLUDED  */
