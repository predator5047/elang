#include "ast.h"
#include "parser.hpp"

typedef std::vector<std::map<std::string, Value> > VariablesListMap;

VariablesListMap Variables(1);

void AddVariable(const std::string& name, const Value& val) {
	VariablesListMap::reverse_iterator it = Variables.rbegin();	

	for (; it != Variables.rend(); ++it) {
		if (it->find(name) != it->end()) {
			(*it)[name] = val;
			return;
		}
	}
	Variables[Variables.size() - 1][name] = val;
}

Value GetVariable(const std::string& name) {

	VariablesListMap::reverse_iterator it = Variables.rbegin();	

	for (; it != Variables.rend(); ++it) {
		if (it->find(name) != it->end()) {
			return (*it)[name];
		}
	}

	std::cout << "Error variable : " << name << " was not decleared.\n";
	exit(1);
	
	return Value();
}

NAssigmentExpresion::NAssigmentExpresion(NIdentifier *ident, NExpresion *exp) : identifier(ident), expresion(exp) {

}

Value NAssigmentExpresion::Interpret() {
	Value val = expresion->Interpret();

	Variables[Variables.size() - 1][identifier->name] = val;
	
	return val;
}

NAssigmentExpresion::~NAssigmentExpresion() {
	delete identifier;
	delete expresion;
}

NBinaryOparator::NBinaryOparator(NExpresion *l, int op_, NExpresion *r) : left(l), op(op_), right(r) {
}

Value NBinaryOparator::Interpret() {
	Value left_val = left->Interpret();
	Value right_val = right->Interpret();
	switch (op) {
		case PLUS:
			return left_val.Add(right_val);
		case MINUS:
			return left_val.Substract(right_val);
		case MULTIPLY:
			return left_val.Multiply(right_val);
		case DIVIDE:
			return left_val.Divide(right_val);
		case MOD:
			return left_val.Mod(right_val);
		case COMP_EQ:
			return left_val.Comp_Eq(right_val);
		case COMP_NEQ:
			return left_val.Comp_NotEq(right_val);
		case LESS_TH:
			return left_val.Comp_LessThen(right_val);
		case LESS_TH_OR_EQ:
			return left_val.Comp_LessThenOrEq(right_val);
		case GREATER_TH:
			return left_val.Comp_GreaterThen(right_val);
		case GREATER_TH_OR_EQ:
			return left_val.Comp_GreaterThenOrEq(right_val);
		case AND:
			return left_val.And(right_val);
		case OR:
			return left_val.Or(right_val);
	}


	return Value(VVoid);
}

NBinaryOparator::~NBinaryOparator() {
	delete left;
	delete right;
	
}

NInteger::NInteger(long long n) : value(n) {

}

Value NInteger::Interpret() {
	Value v;
	v.Type = VInt;
	v.IntValue = value;
	return v;	
}

NDouble::NDouble(double n) : value(n) {
	
}

Value NDouble::Interpret() {
	Value v;
	v.Type = VDouble;
	v.DoubleValue = value;
	return v;	
}

NIdentifier::NIdentifier(const std::string& s) : name(s) {

}

Value NIdentifier::Interpret() {
	return GetVariable(name);
}


NFunctionDeclartion::NFunctionDeclartion(NIdentifier *n, const IdentifierList& ls, NBlock *b) : name(n), arguments(ls), body(b) {
	Value v(VFunction);
	v.Func = this;
	AddVariable(n->name, v);
}


Value NFunctionDeclartion::Interpret() {
	Value val(VFunction);
	val.Func = this;
	return val;
}


NFunctionDeclartion::~NFunctionDeclartion() {
	delete name;
	for (int i = 0; i < arguments.size(); i++) {
		delete arguments[i];
	}
	delete body;
}

NFunctionCall::NFunctionCall(NIdentifier *n, const ExpressionList& args) : name(n), arguments(args) {

}

Value NFunctionCall::Interpret() {
	Value v = GetVariable(name->name);
	NFunctionDeclartion *func = v.Func;

	if (v.Type != VFunction) {
		std::cout << "Error " << name->name << " is not a function";
		exit(8);
	}

	if (arguments.size() != func->arguments.size()) {
		std::cout << "Error " << func->name->name << " called with incorect number of arguments\n";
		exit(9);
	}

	std::vector<Value> vals;

	for (int i = 0; i < arguments.size(); i++) {
		vals.push_back(arguments[i]->Interpret());
	}

	Variables.push_back(std::map<std::string, Value>());

	for (int i = 0; i < arguments.size(); i++) {
		Variables[Variables.size() - 1][func->arguments[i]->name] = vals[i];
	}

	Value last_val;
	for (int i = 0; i < func->body->expresions.size(); i++) {
		last_val = func->body->expresions[i]->Interpret();
	}

	Variables.pop_back();
	
	return last_val;
	
}
	

NFunctionCall::~NFunctionCall() {
	delete name;
	for (int i = 0; i < arguments.size(); i++) {
		delete arguments[i];
	}
}


NBlock::~NBlock() {
	for (int i = 0; i < expresions.size(); i++) {
		delete expresions[i];
	}
}

Value NBlock::Interpret() {
	Value last_val;

	for (int i = 0; i < expresions.size(); i++) {
		last_val = expresions[i]->Interpret();
	}


	return last_val;
}



NIfElseExpresion::NIfElseExpresion(NExpresion *ex, NBlock *b1, NBlock *b2)
	: expresion(ex), if_body(b1), else_body(b2) {

}

Value NIfElseExpresion::Interpret() {
	Value v = expresion->Interpret();
	if (v.Type != VBool) {
		std::cout << "Error if condition must be a boolean.\n";
		exit(11);
	}

	if (v.BoolValue == true) {
		return if_body->Interpret();
	}

	return else_body->Interpret();
}

NIfElseExpresion::~NIfElseExpresion() {
		delete expresion;
		delete if_body;
		delete else_body;
}

NForExpresion:: NForExpresion(NExpresion *e1, NExpresion *e2,NExpresion *e3, NBlock *b) 
		: expr1(e1), expr2(e2), expr3(e3), body(b) {
	
}

Value NForExpresion::Interpret() {
	Value last_value;
	
	for (expr1->Interpret(); expr2->Interpret().BoolValue == true; expr3->Interpret()) {
		last_value = body->Interpret();	
	}

	return last_value;
}


NForExpresion::~NForExpresion() {
	delete expr1;
	delete expr2;
	delete expr3;
	delete body;
}

NWhileExpresion::NWhileExpresion(NExpresion *e, NBlock *b) : exp(e), body(b) {
	
}

Value NWhileExpresion::Interpret() {
	Value last_value;
	while (exp->Interpret().BoolValue == true) {
		last_value = body->Interpret();
	}
	return last_value;
}

NWhileExpresion::~NWhileExpresion() {
	delete exp;
	delete body;
}

