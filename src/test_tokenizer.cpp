#include <string>
#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

#include "tokenizer.h"

using namespace std;

using namespace tokenizer;

TEST(TokenizerScanSymbols, Plus) {
    Tokenizer t("+");
    ASSERT_EQ(t.scan(), PLUS);
}

TEST(TokenizerScanSymbols, Minus) {
    Tokenizer t("-");
    ASSERT_EQ(t.scan(), MINUS);
}

TEST(TokenizerScanSymbols, Less) {
    Tokenizer t("<");
    ASSERT_EQ(t.scan(), LESS);
}

TEST(TokenizerScanSymbols, Greater) {
    Tokenizer t(">");
    ASSERT_EQ(t.scan(), GREATER);
}

TEST(TokenizerScanSymbols, Dot) {
    Tokenizer t(".");
    ASSERT_EQ(t.scan(), DOT);
}

TEST(TokenizerScanSymbols, Comma) {
    Tokenizer t(",");
    ASSERT_EQ(t.scan(), COMMA);
}

TEST(TokenizerScanSymbols, OpenBracket) {
    Tokenizer t(" [");
    ASSERT_EQ(t.scan(), OPENBRACKET);
}

TEST(TokenizerScanSymbols, CloseBracket) {
    Tokenizer t("]");
    ASSERT_EQ(t.scan(), CLOSEBRACKET);
}

TEST(TokenizerScanSymbols, End) {
    Tokenizer t(" ");
    ASSERT_EQ(t.scan(), END);
}

TEST(TokenizerScan, IgnoreCommentLoop) {
    Tokenizer t("[This is a comment loop] +");
    ASSERT_EQ(t.scan(), PLUS);
}

TEST(TokenizerScan, IgnoreNonTokens) {
    Tokenizer t("Ignores everything but ,");
    ASSERT_EQ(t.scan(), COMMA);
}
