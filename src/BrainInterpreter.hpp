#pragma once

#include <vector>

#include "BrainTokenizer.hpp"
#include "BrainCellTable.hpp"

using namespace std;

void eval(
	vector<Symbol> &program,
	CellTable &ct, 
	ostream &out=cout,
	istream &in=cin,
	unsigned index=0
) {
	unsigned j = 0;
	// Accounts for nested bracket loops.
	unsigned bracketsFound = 0;
	unsigned bracketsNeeded = 0;
	for (unsigned i=index; i<program.size(); i++) {
		switch (program[i]) {
			case PLUS: ct.add(); break;
			case MINUS: ct.minus(); break;
			case LESS: ct.movePtrLeft(); break;
			case GREATER: ct.movePtrRight(); break;
			case DOT: ct.print(out); break;
			case COMMA: ct.input(in); break;
			case OPENBRACKET:
				if (ct.ptrIsNotZero()) {
					while (ct.ptrIsNotZero()) {
						eval(program, ct, out, in, i+1);
					}
				}
				j = i + 1;
				bracketsFound = 0;
				bracketsNeeded = 1;
				// Skips over the code that shouldn't be executed.
				while (bracketsFound != bracketsNeeded) {
					if (program[j] == OPENBRACKET) bracketsNeeded++;
					else if (program[j] == CLOSEBRACKET) bracketsFound++;
					j++;
				}
				i = j - 1;
				break;
			case CLOSEBRACKET:
				if (ct.ptrIsNotZero()) i = index-1;
				// Breaks out of the function
				else return;
				break;
			default:
				continue;
		}
	}
}