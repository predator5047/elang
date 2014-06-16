
#include "value.h"

#include <sstream>
#include <iostream>
#include <cstdlib>

#define MEMBER_OP_IMPL(name, op) \
Value Value::name(Value b) { \
	Value val; \
	switch (Type) { \
		case VDouble:\
			val.Type = VDouble;\
			if (b.Type == VInt || b.Type == VBool) {\
				val.DoubleValue = DoubleValue op (double)b.IntValue; \
			} else {\
				val.DoubleValue = DoubleValue op b.DoubleValue;\
			}\
			break;\
		case VInt:\
			if (b.Type == VInt || b.Type == VBool) {\
				val.Type = VInt; \
				val.IntValue = IntValue op b.IntValue; \
			} else {\
				val.DoubleValue = (double)IntValue op b.DoubleValue;\
			}\
			break;\
		case VBool:\
			if (b.Type == VInt || b.Type == VBool) {\
				val.Type = VInt;\
				val.IntValue = IntValue op b.IntValue; \
			} else {\
				val.Type = VDouble;\
				val.DoubleValue = (double)IntValue op b.DoubleValue;\
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
			if (b.Type == VInt || b.Type == BoolValue) {\
				val.BoolValue = DoubleValue op (double)b.IntValue; \
			} else {\
				val.BoolValue = DoubleValue op b.DoubleValue;\
			}\
			break;\
		case VInt:\
			if (b.Type == VInt || b.Type == BoolValue) {\
				val.BoolValue = IntValue op b.IntValue; \
			} else {\
				val.BoolValue = (double)IntValue op b.DoubleValue;\
			}\
			break;\
		case VBool:\
			if (b.Type == VInt || b.Type == BoolValue) {\
				val.BoolValue = IntValue op b.IntValue; \
			} else {\
				val.BoolValue = (double)IntValue op b.DoubleValue;\
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
	//std::cout << (v.IntValue = IntValue % b.IntValue) << "\n";
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
	}
	return ss.str().c_str();
}


