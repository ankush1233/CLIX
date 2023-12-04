#include "command.h"
#include <iostream>
#include <windows.h>

int main(){
	std::string UserCommand;
	bool loop_control = true;
	char currentDir[MAX_PATH_SIZE];	

	while(loop_control){

		if(GetCurrentDir(currentDir, sizeof(currentDir)) != nullptr){
			std::cout << "\033[" << "33" << "m" << currentDir << "\033[0m";
			std::cout << "~>";
		}
		
		getline(std::cin, UserCommand, '\n');

		if (UserCommand == " ") {

        }else {
			if (UserCommand == "back") {
		       	BackToDirectory();
		        std::cout << '\n';

		    } else if (UserCommand == "nd") {
		        NowDir();
		        std::cout << '\n';

		    } else if (UserCommand == "exit") {
		        loop_control = false;

		    } else if (UserCommand == "clear") {
		        system("cls");

		    } else if (UserCommand == "scandir") {
		        ScanDirectory();
		        std::cout << '\n';

		    } else if (UserCommand == "driveconfig") {
		        DiskConfiguration();
		        std::cout << '\n';

		    } else if (UserCommand.find("mvt ") == 0) {
		        MoveToDirectory(UserCommand);
		        std::cout << '\n';

		    } else if (UserCommand.find("mkfile ") == 0) {
		        MakeFile(UserCommand);
		        std::cout << '\n';

		    } else if (UserCommand.find("find ") == 0) {
		        FindFile(UserCommand);
		        std::cout << '\n';

		    } else if (UserCommand.find("setdrive ") == 0) {
		        SetDrive(UserCommand);
		        std::cout << '\n';

		    } else if (UserCommand.find("copy ") == 0 || UserCommand.find("paste") == 0) {
		        CopyFiles(UserCommand);
		        std::cout << '\n';

		    } else if (UserCommand.find("ef ") == 0){
		        EraseFile(UserCommand);
		        std::cout << '\n';

		    } else if (UserCommand.find("ed ") == 0){
		    	EraseDirectory(UserCommand);
		    	std::cout << '\n';

		    } else if (UserCommand == "readdir"){
		    	ReadDirectory();
		    	std::cout << '\n';

		    } else if (UserCommand.find("rename ") == 0) {
		    	Rename(UserCommand);
		    	std::cout << '\n';		
		    
		    } else if(UserCommand == "showwin") {
		    	ShowWin();
		    	std::cout << '\n';
		    } else {
		    	std::cout << "Invalid Command!!\n\n";
		    }
		}		
	}
	return 0;
}
