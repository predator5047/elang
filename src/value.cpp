
#include "value.h"

#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#define MEMBER_OP_IMPL(name, op) \
Value Value::name(Value b) { \
	Value val; \
	switch (Type) { \
		case VString: \
			val = StringOperation(*this, b, #op); \
			break; \
		case VDouble:\
			val.Type = VDouble; \
			if (b.Type == VInt) {\
				val.DoubleValue = DoubleValue op (double)b.IntValue; \
			} else if (b.Type == VBool) { \
				val.DoubleValue = DoubleValue op (double)b.BoolValue; \
			} else {\
				val.DoubleValue = DoubleValue op b.DoubleValue;\
			}\
			break;\
		case VInt:\
			if (b.Type == VInt) {\
				val.Type = VInt; \
				val.IntValue = IntValue op b.IntValue; \
			} else if (b.Type == VBool) { \
				val.Type = VInt; \
				val.IntValue = IntValue op (int)b.BoolValue; \
			} else {\
				val.Type = VDouble; \
				val.DoubleValue = (double)IntValue op b.DoubleValue;\
			}\
			break;\
		case VBool:\
			if (b.Type == VInt) {\
				val.Type = VInt; \
				val.IntValue = BoolValue op b.IntValue; \
			} else if (b.Type == VBool) { \
				val.Type = VBool; \
				val.BoolValue = BoolValue op b.BoolValue; \
			} else {\
				val.Type = VDouble; \
				val.DoubleValue = (double) BoolValue op b.DoubleValue;\
			}\
			break;\
		default: \
				 std::cout << "Non algebric value\n"; \
				 exit(6); \
				 break; \
	}\
	return val;\
}

#define MEMBER_LOGICAL_OP_IMPL(name, op) \
Value Value::name(Value b) { \
	Value val(VBool); \
	switch (Type) { \
		case VDouble:\
			if (b.Type == VInt) {\
				val.BoolValue = DoubleValue op (double)b.IntValue; \
			} else if (b.Type == VBool) { \
				val.BoolValue = DoubleValue op (double)b.BoolValue; \
			} else {\
				val.BoolValue = DoubleValue op b.DoubleValue;\
			}\
			break;\
		case VInt:\
			if (b.Type == VInt) {\
				val.BoolValue = IntValue op (double)b.IntValue; \
			} else if (b.Type == VBool) { \
				val.BoolValue = IntValue op (double)b.BoolValue; \
			} else {\
				val.BoolValue = IntValue op b.DoubleValue;\
			}\
			break;\
		case VBool:\
			if (b.Type == VInt) {\
				val.BoolValue = BoolValue op (double)b.IntValue; \
			} else if (b.Type == VBool) { \
				val.BoolValue = BoolValue op (double)b.BoolValue; \
			} else {\
				val.BoolValue = BoolValue op b.DoubleValue;\
			}\
			break;\
		default: \
				 std::cout << "Non algebric value\n"; \
				 exit(6); \
				 break; \
	}\
	return val;\
}


Value::Value() {

}

Value::Value(ValueType t) : Type(t) {

}




Value::~Value() {

}

Value StringOperation(Value a, Value b, const std::string& op) {
	Value val(VString);
	if (op == "+") {
		char buffer[140] = {};
		if (b.Type == VDouble) {
			sprintf(buffer, "%f", b.DoubleValue);
		} else if (b.Type == VInt) {
			sprintf(buffer, "%lld", b.IntValue);
		} else if (b.Type == VString) {
			sprintf(buffer, "%s", b.Str->c_str());
		}
		val.Str = new std::string(*a.Str + buffer);
	} else {
		std::cout << "Can only use + operator to add string.\n";
		exit(22);
	}
	return val;
}

MEMBER_OP_IMPL(Add, +);
MEMBER_OP_IMPL(Substract, -);
MEMBER_OP_IMPL(Multiply, *);
MEMBER_OP_IMPL(Divide, /);
MEMBER_LOGICAL_OP_IMPL(Comp_Eq, ==);
MEMBER_LOGICAL_OP_IMPL(Comp_NotEq, !=);
MEMBER_LOGICAL_OP_IMPL(Comp_LessThen, <);
MEMBER_LOGICAL_OP_IMPL(Comp_LessThenOrEq, <=);
MEMBER_LOGICAL_OP_IMPL(Comp_GreaterThen, >);
MEMBER_LOGICAL_OP_IMPL(Comp_GreaterThenOrEq, >=);
MEMBER_LOGICAL_OP_IMPL(And, &&);
MEMBER_LOGICAL_OP_IMPL(Or, ||);

Value Value::Mod(Value b) {
	Value v(VInt);
	v.IntValue = IntValue % b.IntValue;
	return v;	
}

const char* Value::ToString() {
	std::stringstream ss;
	switch (Type) {
		case VDouble:
			ss << DoubleValue;
			break;
		case VInt:
			ss << IntValue;
			break;
		case VBool:
			ss << BoolValue;
			break;
		case VVoid:
			ss << "void";
			break;
		case VFunction:
		 	ss << Func; 
			break;
		case VString:
			ss << *Str;
	}
	return ss.str().c_str();
}


