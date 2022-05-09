#include <string>
#include <iostream>

#include "tokenizer.h"

using namespace std;

using namespace tokenizer;

ostream &tokenizer::operator<< (ostream &out, const Symbol &s) {
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

Tokenizer::Tokenizer(string s, string newFileName){
    text = s;
    fileName = newFileName;
    pos = 0;
    // Used for error messages.
    lastSymbolPos = 0;
    lineNum = 1;
    column = 1;
}

void Tokenizer::outputError(string message, bool showLine, ostream &out) {
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

void Tokenizer::incPos(int value) {
    pos += value;
    column += value;
}

Symbol Tokenizer::scan() {
    // Accounts for a comment loop.
    // A comment loop is a loop that is at the very start of a file.
    // This should be ignored by the interpreter.
    if (pos == 0 && text[pos] == '[') {
        incPos();
        // Accounts for nested bracket loops.
        unsigned bracketsFound = 0;
        unsigned bracketsNeeded = 1;

        while (bracketsFound != bracketsNeeded) {
            if (text[pos] == '[') bracketsNeeded++;
            else if (text[pos] == ']') bracketsFound++;
            incPos();
        }
    }
    while (
        (text[pos] == ' ' || text[pos] == '\t' || text[pos] == '\n' || notSymbol()) && 
        canScan()
    ) {
        if (text[pos]=='\n') {
            lineNum++;
            column = 1;
        }
        incPos();
    }

    if (text[pos] == '+') {
        incPos();
        lastSymbolPos = pos;
        return PLUS;
    } else if (text[pos] == '-') {
        incPos();
        lastSymbolPos = pos;
        return MINUS;
    } else if (text[pos] == '<') {
        incPos();
        lastSymbolPos = pos;
        return LESS;
    } else if (text[pos] == '>') {
        incPos();
        lastSymbolPos = pos;
        return GREATER;
    } else if (text[pos] == '.') {
        incPos();
        lastSymbolPos = pos;
        return DOT;
    } else if (text[pos] == ',') {
        incPos();
        lastSymbolPos = pos;
        return COMMA;
    } else if (text[pos] == '[') {
        incPos();
        lastSymbolPos = pos;
        return OPENBRACKET;
    } else if (text[pos] == ']') {
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
