#include "altdir.h"

using namespace std;

void changeDirectory(const  char* path){
	
	if(chdir(path) != 0){
		cerr << "Error: Unable to change directory to " << path << '\n';
	}
}
