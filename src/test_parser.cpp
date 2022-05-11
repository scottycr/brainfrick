#include <gtest/gtest.h>

#include "parser.h"
#include "tokenizer.h"

using namespace std;

using namespace parser;
using namespace tokenizer;

TEST(Parsing, CommandOperation) {
    Symbol s = PLUS;
    ASSERT_TRUE(commandOperation(s));
    s = MINUS;
    ASSERT_TRUE(commandOperation(s));
    s = GREATER;
    ASSERT_TRUE(commandOperation(s));
    s = LESS;
    ASSERT_TRUE(commandOperation(s));
    s = DOT;
    ASSERT_TRUE(commandOperation(s));
    s = COMMA;
    ASSERT_TRUE(commandOperation(s));
    s = END;
    ASSERT_FALSE(commandOperation(s));
}

TEST(Parsing, ValidProgram) {
    Tokenizer t("++.");
    vector<Symbol> program;
    ASSERT_TRUE(parse(t, program));
}

TEST(Parsing, InvalidProgram) {
    Tokenizer t("[] [++.", "gtest_mock_file");
    vector<Symbol> program;
    ASSERT_FALSE(parse(t, program));
    t = Tokenizer("[] ++.]", "gtest_mock_file");
    ASSERT_FALSE(parse(t, program));
}
