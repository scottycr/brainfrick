#pragma once

#include <string>
#include <iostream>

namespace tokenizer {

enum Symbol {
	// Command Operations
	PLUS, MINUS, LESS, GREATER, DOT, COMMA, 
	// Loop Operations
	OPENBRACKET, CLOSEBRACKET,
	// Misc.
	END, UNRECOGNIZED
};

std::ostream &operator << (std::ostream &out, const Symbol &s);

class Tokenizer {
private:
	std::string text;
	std::string fileName;
	
	unsigned pos;
	unsigned lastSymbolPos;
	unsigned lineNum;
	unsigned column;
public:
	Tokenizer(std::string s, std::string newFileName="");

	void outputError(std::string message, bool showLine=false, std::ostream &out=std::cerr);

	// Since Brainfrick ignores most symbols, 
	// this function helps the scanner ignore the right symbols. 
	inline bool notSymbol() {
		return !(
			text[pos] == '+' ||
			text[pos] == '-' ||
			text[pos] == '<' ||
			text[pos] == '>' ||
			text[pos] == '.' ||
			text[pos] == ',' ||
			text[pos] == '[' ||
			text[pos] == ']'
		);
	}

	void incPos(int value=1);

	inline bool isEmpty() { return text.empty(); } 
	inline bool canScan() { return pos < text.length(); }
	Symbol scan();
};

}