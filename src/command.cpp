#include "command.h"
#include <iostream>
#include <string>
using namespace std;


void changeDirectory(const  char* path){

	if(chdir(path) != 0){
		cerr << "Error: Unable to change directory to " << path << '\n';
	}
	return ;
}


void MoveToDirectory(string UserCommand){
		size_t pos = UserCommand.find("moveto-");
			
		if(pos != string :: npos){
			char currentPath[MAX_PATH_SIZE];	
				
			if(GetCurrentDir(currentPath, sizeof(currentPath)) != nullptr){
				cout << "Current directory: " << currentPath << '\n';
			}
				
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

string BackToDirectory(char* currentPath) {
	char PathBuffer[MAX_PATH_SIZE];
	string StringConversionOfCurrentPath(currentPath);
	size_t LastBackSlash = StringConversionOfCurrentPath.find_last_of('\\');

    	if (LastBackSlash != string::npos) {
        	string newPath = StringConversionOfCurrentPath.substr(0, LastBackSlash);
        	const char* newDirectory = newPath.c_str();

        	changeDirectory(newDirectory);

        if (GetCurrentDir(PathBuffer, sizeof(PathBuffer)) != nullptr) {
            	cout << "After back: " << PathBuffer << '\n';
        }

        // Update the currentPath variable
        strcpy(currentPath, PathBuffer);
    }

    // Return the new path
    //return string(PathBuffer);
}


void NowDir(string& UserCommand){

	char currentPath[MAX_PATH_SIZE];
	if(UserCommand == "nowdir-"){
		if(GetCurrentDir(currentPath, sizeof(currentPath)) != nullptr){
			cout << "Current directory: " << currentPath << '\n';
		}
	}
	return ;
}

