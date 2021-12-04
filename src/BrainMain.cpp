#include <fstream>
#include <sstream>

#include "BrainTokenizer.hpp"
#include "BrainParser.hpp"
#include "BrainCellTable.hpp"
#include "BrainInterpreter.hpp"

using namespace std;

int main(int argc, char **argv) {
	if (argc < 2) {
        cerr << "You need to provide a file name." << endl;
        return -1;
    }

	ostream *userOut = &cout;
	ofstream fout;
	size_t size = 30000;

	for (int i=2; i<argc; i++) {
		string argvi(argv[i]);
		if (argvi == "-o" || argvi == "-output") {
			if (i + 1 < argc) {
				i++;
				fout.open(argv[i]);
				userOut = &fout;
			} else {
				cerr << "You need to provide an output file." << endl;
				return -1;
			}
		} else if (argvi == "-ts" || argvi == "-table-size") {
			if (i + 1 < argc) {
				i++;
				argvi = string(argv[i]);
				try {
					size = stoul(argvi);
				} catch (const invalid_argument &ia) {
					cerr << argvi << " is not a valid size." << endl;
					return -1;
				}
				
			} else {
				cerr << "You need to provide a valid size." << endl;
				return -1;
			}
		}
	}

	string fileName(argv[1]);
	fstream in;
	in.open(fileName);
	ostringstream sstr;
	sstr << in.rdbuf();
	
	Tokenizer t(sstr.str(), fileName);

	if (t.isEmpty()) cerr << fileName << " is either empty or does not exist." << endl;

	vector<Symbol> program;

	if (parse(t, program)) {
		CellTable ct(size);
		eval(program, ct, *userOut);
		if (fout.is_open()) fout.close();
		return 0;
	}

	if (fout.is_open()) fout.close();

	return -1;
}