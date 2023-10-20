#include "moveto.h"
#include "altdir.h"

void NowDirectory(string UserCommand){
	if(UserCommand == "nowdir-"){
		if(GetCurrentDir(currentPath, sizeof(currentPath)) != nullptr){
			cout << "Current directory: " << currentPath << '\n';
		}
	}

}