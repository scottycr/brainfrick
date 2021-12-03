#pragma once

#include <vector>

#include "BrainTokenizer.hpp"

/*	Source: https://rosettacode.org/wiki/BNF_Grammar#Brainf.2A.2A.2A
	
BNF Notation for Brainf***:
	Code ::= Command Code | <NONE>
 	Command ::= "+" | "-" | "<" | ">" | "," | "." | "[" Code "]" | <ANY> */

inline bool isSimpleOp(Token &next) {
	return (
		next == PLUS 		||
		next == MINUS		||
		next == GREATER 	||
		next == LESS 		||
		next == COMMA		||
		next == DOT
	);
}

bool loop(Tokenizer &t, vector<Token> &program) {
	Token next;
	if (t.canScan()) {
		next = t.scan();
		vector<Token> tmp;
		while (next != CLOSEBRACKET && t.canScan()) {
			if (next != OPENBRACKET) {
				tmp.push_back(next);
			} else {
				vector<Token> tmp2;
				if (loop(t, tmp2)) {
					for (auto t : tmp2) tmp.push_back(t);
				} else {
					return false;
				}
			}
		}

		if (next != CLOSEBRACKET) {
			t.outputError("No closing bracket found.");
			return false;
		}

		program = tmp;
		return true;
	}

	t.outputError("Not a valid loop.");
	return false;
}

bool parse(Tokenizer &t, vector<Token> &program) {
	Token next;
	vector<Token> tmp;
	while (t.canScan()) {
		next = t.scan();
		if (isSimpleOp(next)) {
			tmp.push_back(next);
		} else if (next == OPENBRACKET) {
			tmp.push_back(next);
			vector<Token> tmp2;
			if (loop(t, tmp2)) {
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

	t.outputError("EOF was not reached.");
	return false;
}