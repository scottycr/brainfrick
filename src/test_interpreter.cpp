#include <fstream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "interpreter.h"
#include "tokenizer.h"
#include "parser.h"
#include "celltable.h"

using namespace std;

using namespace interpreter;
using namespace tokenizer;
using namespace parser;
using namespace celltable;

stringstream strin;
ostringstream strout;
fstream fin;

TEST(Interpreter, HelloWorld) {
    fin.open("./examples/hello.bf");
    strout << fin.rdbuf();
    fin.close();

    Tokenizer t(strout.str(), "hello.bf");
    strout.str("");
    vector<Symbol> program;
    parse(t, program);

    CellTable ct;
    eval(program, ct, strout, strin);
    string expectedResult = "Hello World!\n";
    ASSERT_EQ(strout.str(), expectedResult);
}

TEST(Interpreter, Addition) {
    fin.open("./examples/addition.bf");
    strout << fin.rdbuf();
    fin.close();

    Tokenizer t(strout.str(), "addition.bf");
    strout.str("");
    vector<Symbol> program;
    parse(t, program);

    CellTable ct;
    eval(program, ct, strout, strin);
    string expectedResult = "7";
    (strout.str(), expectedResult);
}

TEST(Interpreter, Cat) {
    fin.open("./examples/cat.bf");
    strout << fin.rdbuf();
    fin.close();

    Tokenizer t(strout.str(), "cat.bf");
    strout.str("");
    vector<Symbol> program;
    parse(t, program);

    CellTable ct;
    // \3 is to inser Ctrl + C into the program 
    strin << "hello\3";
    eval(program, ct, strout, strin);
    string expectedResult = "hello\3";
    ASSERT_EQ(strout.str(), expectedResult);
}
