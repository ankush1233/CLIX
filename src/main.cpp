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
			if (UserCommand == "back") {
		        BackToDirectory();
		        cout << '\n';
		    } else if (UserCommand == "nowdir") {
		        NowDir();
		        cout << '\n';
		    } else if (UserCommand == "exit") {
		        loop_control = false;
		    } else if (UserCommand == "clr") {
		        system("cls");
		    } else if (UserCommand == "scandir") {
		        ReadDirectory();
		        cout << '\n';
		    } else if (UserCommand == "driveconfig") {
		        DiskConfiguration();
		        cout << '\n';
		    } else if (UserCommand.find("moveto ") == 0) {
		        MoveToDirectory(UserCommand);
		        cout << '\n';
		    } else if (UserCommand.find("mkfile ") == 0) {
		        MakeFile(UserCommand);
		        cout << '\n';
		    } else if (UserCommand.find("find ") == 0) {
		        FindFile(UserCommand);
		        cout << '\n';
		    } else if (UserCommand.find("setdrive ") == 0) {
		        SetDrive(UserCommand);
		        cout << '\n';
		    } else if (UserCommand.find("c ") == 0 || UserCommand.find("p") == 0) {
		        CopyFiles(UserCommand);
		        cout << '\n';
		    } else {
		        // Handle unrecognized command here.
		        cout << "Unrecognized command: " << UserCommand << '\n';
		    }
		}		
	}
	return 0;
}
