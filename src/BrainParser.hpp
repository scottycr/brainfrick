#pragma once

#include <iostream>

#include "BrainTokenizer.hpp"
#include "BrainAST.hpp"

/*	Source: https://rosettacode.org/wiki/BNF_Grammar#Brainf.2A.2A.2A
	
BNF Notation for Brainf***:
	Code ::= Command Code | <NONE>
 	Command ::= "+" | "-" | "<" | ">" | "," | "." | "[" Code "]" | <ANY> */
bool expression(Tokenizer &t, Node *AST) {
	Token next = t.parse();
	if (
		next.getSymbol() == PLUS 	||
		next.getSymbol() == MINUS 	||
		next.getSymbol() == LESS 	||
		next.getSymbol() == GREATER ||
		next.getSymbol() == COMMA	||
		next.getSymbol() == DOT
	) {
		AST->setToken(next);
		Node *tmp = new Node(Token(TOP));
		if (expression(t, tmp)) {
			AST->addNode(tmp);
			return true;
		};
		delete tmp;
	} else if (next.getSymbol()==OPENBRACKET) {
		Node *tmp2 = new Node(Token(TOP));
		if (expression(t, tmp2)) {
			next=t.parse();
			if (next.getSymbol()==CLOSEBRACKET) {
                AST->shallowCopy(tmp2);
				return true;
			} 
		}
		delete tmp2;
	}

	if (next.getSymbol()==END) {
		AST->setToken(END);
		return true;
	}

    t.outputError("Expression not found");
    return false; // Probably should generate an error message.
}