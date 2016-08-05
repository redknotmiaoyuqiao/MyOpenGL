#include "Utils.h"
#include <fstream>

void error_out(string file, unsigned int linenum)
{
		cout << file << ":" << linenum << endl;
}

bool ReadShaderFile(const char* pFileName, string& outFile)
{
		ifstream f(pFileName);

		bool ret = false;

		if (f.is_open()) {
				string line;
				while (getline(f, line)) {
						outFile.append(line);
						outFile.append("\n"); 
				}

				f.close();

				ret = true;
		}
		else {
				ErrorOut();
		}

		return ret;
}