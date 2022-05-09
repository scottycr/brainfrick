#pragma once 

#include <vector>
#include <iostream>

namespace celltable {

class CellTable {
private:
	std::vector<char> cells;
	char *ptr;
public:
	CellTable(size_t size=30000);

	inline void add() { (*ptr)++; }
	inline void minus() { (*ptr)--; }
	inline void movePtrLeft() { ptr--; }
	inline void movePtrRight() { ptr++; }
	inline void print(std::ostream &out=std::cout) { out << *ptr; }
	inline void input(std::istream &in=std::cin) { in.get(*ptr); }
	inline bool ptrIsNotZero() { return *ptr; }
};

}
