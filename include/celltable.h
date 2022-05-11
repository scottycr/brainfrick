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

    // Used to verify cell contents in tests.
    // Not used in the interpreter.
    inline char getCell(size_t index) { return cells.at(index); }
    inline char* getCellPtr(size_t index) { return &cells.at(index); }
    inline size_t getSize() { return cells.size(); }
    inline char* getPtr() { return ptr; }

	inline void add() { (*ptr)++; }
	inline void minus() { (*ptr)--; }
	inline void movePtrLeft() { ptr--; }
	inline void movePtrRight() { ptr++; }
	inline void print(std::ostream &out=std::cout) { out << *ptr; }
	inline void input(std::istream &in=std::cin) { in.get(*ptr); }
	inline bool ptrIsNotZero() { return *ptr; }
};

}
