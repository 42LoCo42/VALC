#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
	VALC - Variable-agnostic Lambda Calculus

	Syntax of a term:
	<term> ::= !(lval) | (<lval>)(<rval>)
	<lval> ::= <term> | <variable>
	<rval> ::= <lval> | <symbol>
	<variable> ::= [0-Infinity]
	<symbol> ::= [A-Z] | [a-z]

	Example: Lx.Ly.Lz.(xz)(yz)
 */


void replaceAll(std::string& str, const string& from, const string& to) {
	if(from.empty())
		return;

	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

size_t findClosingBrace(const string& text, const size_t& openingBracePos) {
	char openingBraceChar = text[openingBracePos];
	char closingBraceChar;

	switch(openingBraceChar) {
	case '(': closingBraceChar = ')'; break;
	case '[': closingBraceChar = ']'; break;
	case '{': closingBraceChar = '}'; break;
	case '<': closingBraceChar = '>'; break;
	default: return text.size(); // return impossible index
	}

	size_t closingBracePos;
	uint scope = 0;
	for(closingBracePos = openingBracePos; closingBracePos < text.size(); ++closingBracePos) {
		if(text[closingBracePos] == openingBraceChar) {
			++scope;
		}
		else if(text[closingBracePos] == closingBraceChar) {
			--scope;
			if(scope == 0)
				break;
		}
	}

	return closingBracePos;
}

int main() {
	string test = "(fhs((a)(aa)))()";
	cout << findClosingBrace(test, 4) << endl;
}
