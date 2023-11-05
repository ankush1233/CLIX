#include "command.h"
#include <iostream>


int main(){
	string UserCommand;
	bool loop_control = true;
	char currentDir[MAX_PATH_SIZE];	

	while(loop_control){
		
		if(GetCurrentDir(currentDir, sizeof(currentDir)) != nullptr){
			cout << currentDir << "~>";
		}
		
		//cin >> UserCommand;
		std::getline(std::cin, UserCommand, '\n');
		if (UserCommand == " ") {

        }else {

			if(UserCommand == "back"){
				BackToDirectory();
				cout << '\n';
			}
			
			size_t pos = UserCommand.find("moveto ");
			if(pos != string :: npos){
				MoveToDirectory(UserCommand);
				cout << '\n';
			}
			

			if(UserCommand == "nowdir"){
				NowDir();
				cout << '\n';
			}

			if(UserCommand == "exit"){
				loop_control = false;
			}
			
			if(UserCommand == "clr"){
				system("cls");
			}
			
			pos = UserCommand.find("mkfile ");
			if(pos != string :: npos){
				MakeFile(UserCommand);
				cout << '\n';	
			}

			if(UserCommand == "scandir"){
				ReadDirectory();
				cout << '\n';
			}
				
			pos = UserCommand.find("find ");
			if(pos != string :: npos){
				FindFile(UserCommand);
				cout << '\n';
			}

			if(UserCommand == "diskconfig"){
				DiskConfiguration();
				cout << '\n';
			}

		}
	}
	return 0;
}
