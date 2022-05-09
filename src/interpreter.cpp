#include <vector>

#include "interpreter.h"
#include "tokenizer.h"
#include "celltable.h"

using namespace std;

using namespace interpreter;
using namespace tokenizer;
using namespace celltable;

void interpreter::eval(
	vector<Symbol> &program,
	CellTable &ct, 
	ostream &out,
	istream &in,
	unsigned index
) {
	unsigned j, bracketsFound, bracketsNeeded;
	for (unsigned i=index; i<program.size(); i++) {
		switch (program[i]) {
			case PLUS: ct.add(); break;
			case MINUS: ct.minus(); break;
			case LESS: ct.movePtrLeft(); break;
			case GREATER: ct.movePtrRight(); break;
			case DOT: ct.print(out); break;
			case COMMA: ct.input(in); break;
			case OPENBRACKET:
				while (ct.ptrIsNotZero()) eval(program, ct, out, in, i+1);

				// Temporary index counter 
				j = i + 1;

				// Accounts for nested bracket loops.
				bracketsFound = 0;
				bracketsNeeded = 1;

				// Skips over the code that shouldn't be executed.
				while (bracketsFound != bracketsNeeded) {
					if (program[j] == OPENBRACKET) bracketsNeeded++;
					else if (program[j] == CLOSEBRACKET) bracketsFound++;
					j++;
				}

				// Accounts for the increment of i happening right after.
				i = j - 1;
				break;
			case CLOSEBRACKET:
				// Accounts for the increment of i happening right after.
				if (ct.ptrIsNotZero()) i = index - 1;
				// Breaks out of the function to return to the OPENBRACKET case.
				else return;
				break;
			default:
				continue;
		}
	}
}