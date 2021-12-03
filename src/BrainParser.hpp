#pragma once

#include <vector>

#include "BrainTokenizer.hpp"

/*	Source: https://rosettacode.org/wiki/BNF_Grammar#Brainf.2A.2A.2A
	
BNF Notation for Brainf***:
	Code ::= Command Code | <NONE>
 	Command ::= "+" | "-" | "<" | ">" | "," | "." | "[" Code "]" | <ANY> */

/* Modified BNF for Brainfrick:
	Command Operation 	::= "+" | "-" | "<" | ">" | "," | "."
	Command 			::= Command Operation | "[" Command Operation "]"
*/

inline bool commandOperation(Token &next) {
	return (
		next == PLUS 		||
		next == MINUS		||
		next == GREATER 	||
		next == LESS 		||
		next == COMMA		||
		next == DOT
	);
}

bool command(Tokenizer &t, vector<Token> &program) {
	Token next;
	if (t.canScan()) {
		next = t.scan();
		vector<Token> tmp;
		while (next != CLOSEBRACKET && t.canScan()) {
			tmp.push_back(next);
			if (next == OPENBRACKET) {
				vector<Token> tmp2;
				if (command(t, tmp2)) {
					for (auto t : tmp2) tmp.push_back(t);
				} else {
					return false;
				}
			}
			next = t.scan();
		}

		if (next != CLOSEBRACKET) {
			t.outputError("Expected a ']' at end of input", true);
			return false;
		}

		tmp.push_back(next);
		program = tmp;
		return true;
	}

	t.outputError("Reached end of file");
	return false;
}

bool parse(Tokenizer &t, vector<Token> &program) {
	Token next;
	vector<Token> tmp;
	while (t.canScan()) {
		next = t.scan();
		if (commandOperation(next)) {
			tmp.push_back(next);
		} else if (next == OPENBRACKET) {
			tmp.push_back(next);
			vector<Token> tmp2;
			if (command(t, tmp2)) {
				for (auto t : tmp2) tmp.push_back(t);
			} else {
				return false;
			}
		}
	}

	next = t.scan();
	if (next == END) {
		program = tmp;
		return true;
	}

	return false;
}