#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "BrainTokenizer.hpp"
#include "BrainAST.hpp"
#include "BrainParser.hpp"

using namespace std;

int main() {
	fstream in;
	in.open("hello.bf");
	ostringstream sstr;
	sstr << in.rdbuf();
	
	Tokenizer t(sstr.str(), "test.bf");
	Node *AST = new Node(Token(TOP));

	if (expression(t, AST)) {
		cout << "Let's go!" << endl;
		cout << AST << endl;
	} else {
		cout << "Nope" << endl;
	}

	return 0;
}