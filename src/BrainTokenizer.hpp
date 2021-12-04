#pragma once

#include <string>
#include <iostream>

using namespace std;

enum Symbol {
	// Command Operations
	PLUS, MINUS, LESS, GREATER, DOT, COMMA, 
	// Loop Operations
	OPENBRACKET, CLOSEBRACKET,
	// Misc.
	END, UNRECOGNIZED
};

ostream &operator << (ostream &out, const Symbol &s) {
	switch(s) {
		case PLUS: out << "Symbol: Plus"; break;
		case MINUS: out << "Symbol: Minus"; break;
		case LESS: out << "Symbol: Less"; break;
		case GREATER: out << "Symbol: Greater"; break;
		case DOT: out << "Symbol: Dot"; break;
		case COMMA: out << "Symbol: Comma"; break;
		case OPENBRACKET: out << "Symbol: Open Bracket"; break;
		case CLOSEBRACKET: out << "Symbol: Closed Bracket"; break;
		case END: out << "Symbol: END"; break;
		case UNRECOGNIZED: out << "Symbol: Unrecognized"; break;
	}
	return out;
}

class Tokenizer{
private:
	string text;
	string fileName;
	
	unsigned pos;
	unsigned lastSymbolPos;
	unsigned lineNum;
	unsigned column;
public:
	Tokenizer(string s, string newFileName=""){
		text = s;
		fileName = newFileName;
		pos = 0;
		// Used for error messages.
		lastSymbolPos = 0;
		lineNum = 1;
		column = 1;
	}

	inline void outputError(string message, bool showLine=false, ostream &out=cerr) {
		out << fileName << ':' << lineNum << ':' << column << ": error: " << message << endl;
		if (showLine) {
			unsigned line = 1;
			unsigned startPos = 0;

			while (line != lineNum) {
				while (text[startPos] != '\n') startPos++;
				line++;
			}

			// Makes sure startPos tracks the character after the '\n'.
			// Want startPos to be 0 if the error is on line 1.
			if (line != 1) startPos++;

			string errorPrefix = "    " + to_string(lineNum) + " | ";
			string errorLine = text.substr(startPos, lastSymbolPos);
			out << errorPrefix << errorLine << endl;
			// 2 is used so the '|' character can print without messing up the formatting.
			for (unsigned i=0; i<errorPrefix.length()-2; i++)
				out << ' ';
			out << '|';
			for (unsigned i=0; i<(lastSymbolPos-startPos); i++)
				out << ' ';
			out << '^' << endl;
		}
	}

	// Since Brainfrick ignores most symbols, 
	// this function helps the scanner ignore the right symbols. 
	inline bool const notSymbol() {
		return !(
			text[pos]=='+' ||
			text[pos]=='-' ||
			text[pos]=='<' ||
			text[pos]=='>' ||
			text[pos]=='.' ||
			text[pos]==',' ||
			text[pos]=='[' ||
			text[pos]==']'
		);
	}

	void incPos(int value=1) {
		pos += value;
		column += value;
	}

	inline bool canScan() const { return pos < text.length(); }
	Symbol scan() {
		while (
			(text[pos]==' ' || text[pos]=='\t' || text[pos]=='\n' || notSymbol()) && 
			pos<text.size()
		) {
		   	if (text[pos]=='\n') {
			 	lineNum++;
			 	column = 1;
		   	}
	    	incPos();
	    }

	    if (text[pos]=='+') {
			incPos();
			lastSymbolPos = pos;
			return PLUS;
		} else if (text[pos]=='-') {
			incPos();
			lastSymbolPos = pos;
			return MINUS;
		} else if (text[pos]=='<') {
			incPos();
			lastSymbolPos = pos;
			return LESS;
		} else if (text[pos]=='>') {
			incPos();
			lastSymbolPos = pos;
			return GREATER;
		} else if (text[pos]=='.') {
			incPos();
			lastSymbolPos = pos;
			return DOT;
		} else if (text[pos]==',') {
			incPos();
			lastSymbolPos = pos;
			return COMMA;
		} else if (text[pos]=='[') {
			incPos();
			lastSymbolPos = pos;
			return OPENBRACKET;
		} else if (text[pos]==']') {
			incPos();
			lastSymbolPos = pos;
			return CLOSEBRACKET;
		}

		if (!canScan()) return END;

		// Since Brainfrick ignores almost every character this theoretically should never be reached. 
		// However, just in case it does it shall remain here.
	  	outputError("Unrecognized Symbol: " + text[pos]);
	  	return UNRECOGNIZED;
	}
};
