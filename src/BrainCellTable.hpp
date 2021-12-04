#pragma once 

#include <vector>
#include <iostream>

using namespace std;

class CellTable {
private:
	vector<char> cells;
	char *ptr;
public:
	CellTable(size_t size=30000) {
		cells = vector<char>(size, 0);
		ptr = &cells[0];
	}

	inline void add() { (*ptr)++; }
	inline void minus() { (*ptr)--; }
	inline void movePtrLeft() { ptr--; }
	inline void movePtrRight() { ptr++; }
	inline void print(ostream &out=cout) { out << *ptr; }
	inline void input(istream &in=cin) { in.get(*ptr); }
	inline bool ptrIsNotZero() { return *ptr; }
};