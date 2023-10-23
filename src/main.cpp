#include "command.h"
#include <iostream>
int main(){
	string UserCommand;
	bool loop_control = true;

	char currentPath[MAX_PATH_SIZE];	
			
	if(GetCurrentDir(currentPath, sizeof(currentPath)) != nullptr){
		cout << "Current directory: " << currentPath << '\n';
	}
	
	while(loop_control){
		cin >> UserCommand;

		if(UserCommand == "back-"){
			BackToDirectory(currentPath);
		}
		//MoveToDirectory(UserCommand);
		//BackToDirectory(UserCommand);
		
		if(UserCommand == "exit"){
			loop_control = false;
		}
	}
	return 0;
}
