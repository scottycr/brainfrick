#pragma once

#include <string>
#include <iostream>

using namespace std;

enum Symbol {
	PLUS, MINUS, 
	LESS, GREATER, 
	COMMA, DOT, 
	OPENBRACKET, CLOSEBRACKET,
	TOP, END,
	UNRECOGNIZED
};

class Token {
	string value;
	Symbol symbol;
	public:
	Token(Symbol newSymbol=UNRECOGNIZED, string newValue=""){
		symbol = newSymbol;
		value = newValue;
	}

	inline Symbol const getSymbol() { return symbol; }
	inline string const getValue() { return value; }

	bool operator ==(const Token &other) {
		if (other.symbol!=symbol) return false;
		return other.value==value;
	}

	inline bool operator !=(const Token &other) {
		return !(*this==other);
	}

	friend ostream & operator << (ostream &out, const Token &tok) {
		switch(tok.symbol) {
			case PLUS: out << "Token: Plus"; break;
			case MINUS: out << "Token: Minus"; break;
			case LESS: out << "Token: Less"; break;
			case GREATER: out << "Token: Greater"; break;
			case COMMA: out << "Token: Comma"; break;
			case DOT: out << "Token: Dot"; break;
			case OPENBRACKET: out << "Token: Open Bracket"; break;
			case CLOSEBRACKET: out << "Token: Closed Bracket"; break;
			case TOP: out << "Token: TOP"; break;
			case END: out << "Token: END"; break;
			case UNRECOGNIZED: out << "Token: Unrecognized"; break;
		}
		return out;
	}
};

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

	inline string const getText() { return text; }
	inline unsigned const getPosition() { return pos; }

	// Since Brainfrick ignores most symbols, 
	// this function helps the scanner ignore the right symbols. 
	inline bool const notSymbol() {
		return !(
			text[pos]=='+' ||
			text[pos]=='-' ||
			text[pos]=='<' ||
			text[pos]=='>' ||
			text[pos]==',' ||
			text[pos]=='.' ||
			text[pos]=='[' ||
			text[pos]==']'
		);
	}

	void incPos(int value=1) {
		pos += value;
		column += value;
	}

	inline bool canScan() const { return pos < text.length(); }
	Token scan() {
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
			return Token(PLUS);
		} else if (text[pos]=='-') {
			incPos();
			lastSymbolPos = pos;
			return Token(MINUS);
		} else if (text[pos]=='<') {
			incPos();
			lastSymbolPos = pos;
			return Token(LESS);
		} else if (text[pos]=='>') {
			incPos();
			lastSymbolPos = pos;
			return Token(GREATER);
		} else if (text[pos]==',') {
			incPos();
			lastSymbolPos = pos;
			return Token(COMMA);
		} else if (text[pos]=='.') {
			incPos();
			lastSymbolPos = pos;
			return Token(DOT);
		} else if (text[pos]=='[') {
			incPos();
			lastSymbolPos = pos;
			return Token(OPENBRACKET);
		} else if (text[pos]==']') {
			incPos();
			lastSymbolPos = pos;
			return Token(CLOSEBRACKET);
		}

		if (!canScan()) return Token(END);

	  	outputError("Unrecognized Token: " + text[pos]);
	  	return Token(UNRECOGNIZED);
	}
};
