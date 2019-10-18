#include "termtree.h"
using namespace std;

#define ERROR_TERM {result = term(); return;}
#define IS_NUM(x) ((x) >= '0' && (x) <= '9')
#define IS_SYM(x) (((x) >= 'A' && (x) <= 'Z') || ((x) >= 'a' && (x) <= 'z'))
#define IS_ABSTR_OP(x) ((x) == '!')
#define IS_APPLC_OP(x) ((x) == '(' || (x) == '[')

term::term(const valc::termType& _tt, const std::vector<term>& _ch, const int _value) :
	type(_tt),
	children(_ch),
	value(_value)
{}

void valc::buildTermTree(const string& raw, term& result) {
	size_t index = 0;

	while(index < raw.size()) {
		if(IS_NUM(raw[index])) {
			result = term(termType::VARIABLE, stoi(raw.substr(index, findNumEnd(raw, index)+1)));
			return;
		}

		if(IS_SYM(raw[index])) {
			result = term(termType::UNBOUND_SYMBOL, vector<term>(), 'A');
			return;
		}

		if(IS_ABSTR_OP(raw[index])) {
			++index;
			term child;

			if(IS_NUM(raw[index])) {
				child = term(valc::termType::VARIABLE, stoi(raw.substr(index, findNumEnd(raw, index)+1)));
			}
			else if(IS_SYM(raw[index])) {
				child = term(valc::termType::UNBOUND_SYMBOL, raw[index]);
			}
			else if(IS_ABSTR_OP(raw[index])) { // less strict syntax: chain abstractions
				buildTermTree(raw.substr(index, raw.size()), child);
			}

			result = term(valc::termType::ABSTRACTION, {child});
			return;
		}

		if(IS_APPLC_OP(raw[index])) {
			// find lval

			// find rval
		}

		ERROR_TERM
	}
}
