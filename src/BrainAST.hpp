#pragma once

#include <vector>
#include <iostream>

#include "BrainTokenizer.hpp"

int indent=0;

class Node {
private:
    Token token;
    vector<Node *> children;
public:
    Node(Token newToken, Node *right=nullptr, Node *left=nullptr) {
        token = newToken;
        if (right != nullptr) children.push_back(right);
        if (left != nullptr) children.push_back(left);
    }
    inline void setToken(Token tok) { token = tok; }
    void shallowCopy (Node *other) {
        children.clear();
        token=other->token;
        for (auto c : other->children) children.push_back(c);
    }

    inline void addNode(Node *newNode) { children.push_back(newNode); }
    friend ostream &operator <<(ostream &out, Node *current) {
        if (indent > 0) out << '+';
        for (int i=1; i<indent; i++) out << '-';
        out << current->token << endl;
        indent += 2;
        for (auto c : current->children) out << c;
        indent -= 2;
        return out;
    }

    Node *getChild(unsigned i) {
        if (i<children.size()) return children[i];
        else return nullptr; 
    }

    void postFix(ostream &out=cout) {
        for (auto c : children)
            c->postFix(out);
        out << '[' << token << "] ";
    }

	// For later...
	// void eval() {}
};