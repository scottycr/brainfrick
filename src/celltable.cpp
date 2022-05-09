#include <vector>

#include "celltable.h"

using namespace std;

using namespace celltable;

CellTable::CellTable(size_t size) {
    cells = vector<char>(size, 0);
	ptr = &cells[0];
}
