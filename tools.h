#ifndef TOOLS_H
#define TOOLS_H

#include <string>
using namespace std;

static void replaceAll(string& str, const string& from, const string& to) {
	if(from.empty())
		return;

	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

static size_t findClosingBrace(const string& text, const size_t& openingBracePos) {
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

static size_t findNumEnd(const string& text, const size_t& numBegin) {
	if(text[numBegin] >= '0' && text[numBegin] <= '9') {
		return findNumEnd(text, numBegin+1);
	}
	return numBegin - 1;
}

#endif // TOOLS_H
