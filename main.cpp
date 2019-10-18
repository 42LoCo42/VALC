#include <iostream>
#include "termtree.h"

using namespace std;

/*
	VALC - Variable-agnostic Lambda Calculus

	Syntax of a term:
	<term> ::= !(lval) | (<lval>)(<rval>)
	<lval> ::= <term> | <variable>
	<rval> ::= <lval> | <symbol>
	<variable> ::= [0-Infinity]
	<symbol> ::= [A-Z] | [a-z]

	Example 0: Lx.x -> !0
	Example 1: Lx.Ly.x -> !(!(1))
	Less strict: !!1
	Example 2: Lf.(Lx.xx)(Lx.f(xx)) -> !((!((0)(x)))(!((1)((0)(0)))))
	Less strict: !((!(0 0))(!(1(0 0))))
	Example 3: Lx.Ly.Lz.(xz)(yz) -> !(!(!(((2)(0))((1)(0)))))(x)(y)(z)
	Less strict: !!!((2 0)(1 0))xyz
 */

int main() {
	string test = "!!a";
	term res;
	valc::buildTermTree(test, res);
}
