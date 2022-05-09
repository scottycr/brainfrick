#pragma once

#include <vector>

#include "tokenizer.h"
#include "celltable.h"

namespace interpreter {

void eval(
	std::vector<tokenizer::Symbol> &program,
	celltable::CellTable &ct, 
	std::ostream &out=std::cout,
	std::istream &in=std::cin,
	unsigned index=0
);

}
