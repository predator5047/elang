
#ifndef VALUE_H_
#define VALUE_H_

#include <string>

struct NFunctionDeclartion;

enum ValueType {
	VDouble, VInt, VBool, VVoid, VFunction, VString
};


struct Value {
	ValueType Type;
	union {
		long long IntValue;
		double DoubleValue;
		bool BoolValue;
		std::string *Str;
		NFunctionDeclartion *Func;
	};	

	Value();
	Value(ValueType t);
	~Value();

	Value Add(Value b);
	Value Substract(Value b);
	Value Multiply(Value b);
	Value Divide(Value b);

	const char* ToString();
	Value Comp_Eq(Value b);
	Value Comp_NotEq(Value b);
	Value Comp_LessThen(Value b);
	Value Comp_GreaterThen(Value b);
	Value Comp_LessThenOrEq(Value b);
	Value Comp_GreaterThenOrEq(Value b);
	Value Mod(Value b);
	Value And(Value b);
	Value Or(Value b);
};

#endif
