#ifndef TERMTREE_H
#define TERMTREE_H

#include <vector>
#include "tools.h"

struct term;

namespace valc {
enum termType {
	ABSTRACTION,
	APPLICATION,
	VARIABLE,
	UNBOUND_SYMBOL,
	//BOUND_SYMBOL, TODO: until symbol definition is added
	EMPTY,
	INVALID
};

void buildTermTree(const std::string& raw, term& result);
}

struct term {
	valc::termType type = valc::termType::INVALID;

	/** termtype::ABSTRACTION has one, termtype::APPLICATION has two */
	std::vector<term> children {};

	/** for the other termTypes */
	int value;

	term(const valc::termType& _tt, const std::vector<term>& _ch, const int _value);
	term(const valc::termType& _tt, const std::vector<term>& _ch) : term(_tt, _ch, 0) {}
	term(const valc::termType& _tt, const int _value) : term(_tt, std::vector<term>(), _value) {}
	term() : term(valc::termType::INVALID, 0) {}
};

#endif // TERMTREE_H
