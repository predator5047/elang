
#ifndef AST_H_
#define AST_H_

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include "value.h"

struct NExpresion;
struct NIdentifier;

typedef std::vector<NExpresion*> ExpressionList;
typedef std::vector<NIdentifier*> IdentifierList;

struct Node {
	
	virtual Value Interpret() {
		Value v;
		v.Type = VVoid;
		return v;
	}
	
	virtual ~Node() {

	}
};

struct NExpresion : Node {
};

struct NBlock : NExpresion {
	ExpressionList expresions;
	Value Interpret();

	~NBlock();
};

struct NPrintExpresion : NExpresion {
	ExpressionList expresions;	
	NPrintExpresion(const ExpressionList& ls) : expresions(ls) {
		
	}

	Value Interpret() {
		for (int i = 0; i < expresions.size(); i++) {
			Value v = expresions[i]->Interpret();
			std::cout << v.ToString() << " ";
		}
		std::cout << "\n";
		Value v;
		v.Type = VVoid;
		return v;
	}
};
struct NIfElseExpresion : NExpresion {
	NExpresion *expresion;
	NBlock *if_body, *else_body;
	NIfElseExpresion(NExpresion *ex1, NBlock *b1, NBlock *b2);
	Value Interpret();
	~NIfElseExpresion();
};

struct NForExpresion : NExpresion {
	NExpresion *expr1, *expr2, *expr3;
	NBlock *body;
	NForExpresion(NExpresion *e1, NExpresion *e2,NExpresion *e3, NBlock *body);

	Value Interpret();

	~NForExpresion();
};

struct NWhileExpresion : NExpresion {
	NExpresion *exp;	
	NBlock *body;
	NWhileExpresion(NExpresion *e, NBlock *b);
	Value Interpret();
	~NWhileExpresion();
};

struct NAssigmentExpresion : NExpresion {
	NIdentifier *identifier;
	NExpresion *expresion;
	
	NAssigmentExpresion(NIdentifier *ident, NExpresion *exp);

	Value Interpret();

	~NAssigmentExpresion();

};

struct NBinaryOparator : NExpresion {
	NExpresion *left, *right;
	int op;

	NBinaryOparator(NExpresion *l, int op, NExpresion *r);
	Value Interpret();

	~NBinaryOparator();
};

struct NInteger : NExpresion {
	long long value;
	NInteger(long long n);
	Value Interpret();

};

struct NDouble : NExpresion {
	double value;
	NDouble(double n);
	Value Interpret();
};

struct NIdentifier : NExpresion {
	std::string name;

	NIdentifier(const std::string& s);
	Value Interpret();
};

struct NFunctionDeclartion : NExpresion {
	NIdentifier *name;
	IdentifierList arguments;
	NBlock *body;	

	NFunctionDeclartion(NIdentifier *n, const IdentifierList& ls, NBlock *b);
	Value Interpret();

	~NFunctionDeclartion();
};

struct NFunctionCall : NExpresion {
	NIdentifier *name;
	ExpressionList arguments;	

	NFunctionCall(NIdentifier *n, const ExpressionList& args);
	Value Interpret();

	~NFunctionCall();
};

#endif
