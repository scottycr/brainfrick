#include <vector>

#include "tokenizer.h"

/*	Source: https://rosettacode.org/wiki/BNF_Grammar#Brainf.2A.2A.2A
	
BNF Notation for Brainf***:
	Code ::= Command Code | <NONE>
 	Command ::= "+" | "-" | "<" | ">" | "," | "." | "[" Code "]" | <ANY> */

/* Modified BNF for Brainfrick:
	Command Operation 	::= "+" | "-" | "<" | ">" | "," | "."
	Command 			::= Command Operation | "[" Command Operation "]"
*/

namespace parser {

bool commandOperation(tokenizer::Symbol &next);

bool command(tokenizer::Tokenizer &t, std::vector<tokenizer::Symbol> &program);
bool parse(tokenizer::Tokenizer &t, std::vector<tokenizer::Symbol> &program);

}
