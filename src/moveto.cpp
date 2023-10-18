#include "moveto.h"

using namespace std;

void ChangeDirectory(const char* path){
	if(chdir(path) != 0)
		cerr << "Error : Unable to change directory to " << path << '\n';
}
