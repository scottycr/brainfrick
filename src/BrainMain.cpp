#include <fstream>
#include <sstream>

#include "BrainTokenizer.hpp"
#include "BrainParser.hpp"
#include "BrainCellTable.hpp"
#include "BrainInterpreter.hpp"

using namespace std;

int main() {
	fstream in;
	in.open("hello.bf");
	ostringstream sstr;
	sstr << in.rdbuf();
	
	Tokenizer t(sstr.str(), "hello.bf");
	vector<Symbol> program;

	if (parse(t, program)) {
		CellTable ct;
		eval(program, ct);
		return 0;
	}

	return 1;
}