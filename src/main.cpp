#include "command.h"
#include <iostream>


int main(){
	string UserCommand;
	bool loop_control = true;

	char currentDir[MAX_PATH_SIZE];	
			
	if(GetCurrentDir(currentDir, sizeof(currentDir)) != nullptr){
		cout << "Current directory: " << currentDir << '\n';
	}
	
	while(loop_control){
		cin >> UserCommand;

		if(UserCommand == "back-")
			BackToDirectory();
		
		size_t pos = UserCommand.find("moveto-");
		if(pos != string :: npos)
			MoveToDirectory(UserCommand);
		

		if(UserCommand == "nowdir-")
			NowDir();

		if(UserCommand == "exit")
			loop_control = false;
	}
	return 0;
}
