#include <fstream>
#include <sstream>

#include "BrainTokenizer.hpp"
#include "BrainParser.hpp"

using namespace std;

int main() {
	fstream in;
	in.open("hello.bf");
	ostringstream sstr;
	sstr << in.rdbuf();
	
	Tokenizer t(sstr.str(), "test.bf");
	vector<Token> program;

	if (parse(t, program)) {
		cout << "Let's go!" << endl;
		for (auto &t : program) cout << t << endl;
	} else {
		cout << "Nope" << endl;
	}

	return 0;
}