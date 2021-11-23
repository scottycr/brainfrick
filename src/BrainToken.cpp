#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <iomanip>

using namespace std;

/*	Source: https://rosettacode.org/wiki/BNF_Grammar#Brainf.2A.2A.2A
	
	BNF Notation for Brainf***:
	Code ::= Command Code | <NONE>
 	Command ::= "+" | "-" | "<" | ">" | "," | "." | "[" Code "]" | <ANY> */

enum Symbol {
	PLUS, MINUS, LESS, GREATER, LESSEQUAL, GREATEREQUAL, COMMA, DOT,
	UNRECOGNIZED
};

class Token {
	string value;
	Symbol symbol;
	public:
	Token(Symbol newSymbol=UNRECOGNIZED,string newValue=""){
		symbol=newSymbol;
		value=newValue;
	}
	Symbol getSymbol() {
		return symbol;
	}
	string getValue() {
		return value;
	}
	bool operator ==(const Token &other) {
		if (other.symbol!=symbol) return false;
		return other.value==value;
	}
	bool operator !=(const Token &other) {
		return !(*this==other);
	}
	friend ostream & operator << (ostream &out, const Token &tok) {
		switch(tok.symbol) {
			case UNRECOGNIZED:  out << "Token: Unrecognized" ; break;
			case PLUS: out << "Token: Plus" ; break;
			case MINUS: out << "Token: Minus" ; break;
			case LESS: out << "Token: Less" ; break;
			case GREATER: out << "Token: Greater" ; break;
			case LESSEQUAL: out << "Token: LessEqual" ; break;
			case GREATEREQUAL: out << "Token: GreaterEqual" ; break;
			case COMMA: out << "Token: Comma" ; break;
			case DOT: out << "Token: Dot" ; break;
		}
		return out;
	}
};

class Tokenizer{
	string text;
	unsigned pos;
	static regex REGEXID;
	string filename;
	int linenum;
	int column;
	public:
	Tokenizer(string s){
		pos=0;
		text=s;
		setFilename();
	}
	void setFilename(string newFilename="") {
		linenum=1;
		column=1;
		filename=newFilename;		
	}
	void outputError(string message,ostream &out=cerr) {
	  cerr <<  filename <<':' << linenum << ':' << column << ": error: " << message <<endl;
	}
	string getText() {
		return text;
	}
	unsigned getPosition() {
		return pos;
	}
	Token peek(bool debug=false) {
		int tempLinenum=linenum;
		int tempPos=pos;
		int tempColumn=column;
		Token t=parse(debug);
		linenum=tempLinenum;
		pos=tempPos;
		column=tempColumn;
		return t;
	}
	void incPos(int value=1) {
		pos+=value;
		column+=value;
	}
	Token parse(bool debug=false) {
	   smatch sm;
	   bool removed=true;
	   while (removed) {
		 removed=false;
	     while ((text[pos]==' ' || text[pos]=='\t' || text[pos]=='\n') &&
			  pos<text.size()) {
		   removed=true;
		   if (text[pos]=='\n') {
			 linenum++;
			 column=0;
		   }
	       incPos();
	     }
	     if (text[pos]=='/' && text[pos+1]=='*') {
		   removed=true;
		   cout << "Multi line Comment" << endl;
		   while (!(text[pos]=='*' && text[pos+1]=='/') && (pos+1)<text.size())
		     incPos();
		   incPos(2);
	     }
	     if (text[pos]=='/' && text[pos+1]=='/') {
		   removed=true;
		   cout << "Single line Comment" << endl;
		   while (text[pos]!='\n' && pos<text.size())
		     incPos();
	     }
       } 
//       cout << text[pos] ;
	   //if (debug) 
	     cout << "Remaining Text "<< text.substr(pos) << endl;
	     if (text[pos]=='+') {
			 incPos();
			 return Token(PLUS);
		 }else if (text[pos]=='-') {
			 incPos();
			 return Token(MINUS);
		 }else if (text[pos]=='<') {
			 incPos();
			 return Token(LESS);
		 }else if (text[pos]=='<') {
			incPos();
			if (text[pos]=='=') {
			  incPos();
			  return Token(LESSEQUAL);
			}	
		 }else if (text[pos]=='>') {
			 incPos();
			 return Token(GREATER);
		 }else if (text[pos]=='>') {
			incPos();
			if (text[pos]=='=') {
			  incPos();
			  return Token(GREATEREQUAL);
			}
		 }else if (text[pos]==',') {
			 incPos();
			 return Token(COMMA);
		 }else if (text[pos]=='.') {
			 incPos();
			 return Token(DOT);
		 }
	  outputError("Unrecognized Token");
	  return Token(UNRECOGNIZED);
	}
};
regex Tokenizer::REGEXID=regex("[a-zA-Z]+");




























