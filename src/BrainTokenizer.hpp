#pragma once

#include <string>
#include <iostream>

using namespace std;

enum Symbol {
	PLUS, MINUS, 
	LESS, GREATER, 
	COMMA, DOT, 
	OPENBRACKET, CLOSEBRACKET,
	END, UNRECOGNIZED
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
	int lineNum;
	int column;
public:
	Tokenizer(string s, string newFileName=""){
		text = s;
		fileName = newFileName;
		pos = 0;
		lineNum = 1;
		column = 1;
	}

	inline void outputError(string message) {
	  	cerr << fileName <<':' << lineNum << ':' << column << ": error: " << message <<endl;
	}

	inline string const getText() { return text; }
	inline unsigned const getPosition() { return pos; }

	// Since Brainfrick ignores most symbols, 
	// the function below helps the scanner ignore the right symbols. 
	inline bool const canIgnoreChar(const char &c) {
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

	inline bool canParse() const { return pos < text.length(); }
	Token parse() {
		while (
			(text[pos]==' ' || text[pos]=='\t' || text[pos]=='\n' || canIgnoreChar(text[pos])) && 
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
			return Token(PLUS);
		} else if (text[pos]=='-') {
			incPos();
			return Token(MINUS);
		} else if (text[pos]=='<') {
			incPos();
			return Token(LESS);
		} else if (text[pos]=='>') {
			incPos();
			return Token(GREATER);
		} else if (text[pos]==',') {
			incPos();
			return Token(COMMA);
		} else if (text[pos]=='.') {
			incPos();
			return Token(DOT);
		} else if (text[pos]=='[') {
			incPos();
			return Token(OPENBRACKET);
		} else if (text[pos]==']') {
			incPos();
			return Token(CLOSEBRACKET);
		}

		if (!canParse()) return Token(END);

	  	outputError("Unrecognized Token: " + text[pos]);
	  	return Token(UNRECOGNIZED);
	}
};
