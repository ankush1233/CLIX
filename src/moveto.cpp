#include "moveto.h"
#include "altdir.h"
using namespace std;

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
}
