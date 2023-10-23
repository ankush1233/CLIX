#include "command.h"
#include <iostream>
#include <string>
using namespace std;

//char PathBuffer[MAX_PATH_SIZE];
char currentPath[MAX_PATH_SIZE];


void changeDirectory(const  char* path){

	if(chdir(path) != 0){
		cerr << "Error: Unable to change directory to " << path << '\n';
	}
	return ;
}


void MoveToDirectory(string UserCommand){
		size_t pos = UserCommand.find("moveto-");
			
		if(pos != string :: npos){
			//char currentPath[MAX_PATH_SIZE];	
				
			/*if(GetCurrentDir(currentPath, sizeof(currentPath)) != nullptr){
				cout << "Current directory: " << currentPath << '\n';
			}*/
				
			string dir = UserCommand.substr(pos + 7);
			string newdir = std::string(currentPath) + '\\' + dir; 
				
	 		const char* newDirectory = newdir.c_str();
	    	changeDirectory(newDirectory);


			if (GetCurrentDir(currentPath, sizeof(currentPath)) != nullptr) {
	    			std::cout << "Current directory: " << currentPath << std::endl;
			}	

	    	//open("ankus.txt", O_RDWR | O_CREAT, 0644);
				
		}
	return;
}

void BackToDirectory() {
		
		GetCurrentDir(currentPath, sizeof(currentPath));

		string StringConversionOfPath(currentPath);
		size_t LastBackSlash = StringConversionOfPath.find_last_of('\\');

		if (LastBackSlash != string::npos) {
    		string newPath = StringConversionOfPath.substr(0, LastBackSlash);
    		const char* newDirectory = newPath.c_str();

    		changeDirectory(newDirectory);
    		//char PathBuffer[MAX_PATH_SIZE];

    		if (GetCurrentDir(currentPath, sizeof(currentPath)) != nullptr) {
        		cout << "After back: " << currentPath << '\n';
    		}

		}
    	return ;
}


void NowDir(){

		if(GetCurrentDir(currentPath, sizeof(currentPath)) != nullptr){
			cout << "Current directory: " << currentPath << '\n';
		}

	return ;
}

