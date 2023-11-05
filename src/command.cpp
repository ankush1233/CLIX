#include "command.h"
#include <iostream>
#include <sys/stat.h>  // For stat() function
#ifdef _WIN32
#include <windows.h>  // For Windows-specific functions
#endif


using namespace std;

//char PathBuffer[MAX_PATH_SIZE];
char currentPath[MAX_PATH_SIZE];
vector<string> file_names;
vector<string> files;	
// void FindFile(const char* PathToFile){	

// 	return;
// }

bool isDirectory(const char* path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0) {
        return false;  // Unable to get file info, assume it's not a directory
    }
    return S_ISDIR(statbuf.st_mode) != 0;
}

void listOfFilesAndDirectories(const char* basePath, vector<std::string>& directories, vector<std::string>& files, vector<string>& file_names) {
    // Open the directory
    DIR* dir = opendir(basePath);

    if (!dir) {
        std::cerr << "Error opening directory" << std::endl;
        return;
    }

    struct dirent* entry;
	while ((entry = readdir(dir))) {
		if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {

			// Construct the full path for the current item
			std::string fullPath = std::string(basePath) + "/" + std::string(entry->d_name);

			if (isDirectory(fullPath.c_str())) {
				// It's a directory, so add it to the directories vector and recurse into it
				directories.push_back(fullPath);
				listOfFilesAndDirectories(fullPath.c_str(), directories, files, file_names);

			} else {
				// It's a file, so add it to the files vector
				file_names.push_back(string(entry->d_name));
				files.push_back(fullPath);
			}

		}
	}
	closedir(dir);
}



void changeDirectory(const  char* path){

	if(chdir(path) != 0){
		cerr << "Error: Unable to change directory to " << path << '\n';
	}
	return ;
}


void MoveToDirectory(string UserCommand){
	
	size_t pos = UserCommand.find("moveto-");
		
	if(pos != string :: npos){

		string dir = UserCommand.substr(pos + 7);
		string newdir = std::string(currentPath) + '\\' + dir; 
			
 		const char* newDirectory = newdir.c_str();
    	changeDirectory(newDirectory);


		if (GetCurrentDir(currentPath, sizeof(currentPath)) != nullptr) {
    			std::cout << "Current directory: " << currentPath << std::endl;
		}	
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
}

void MakeFile(string UserCommand){
	size_t pos = UserCommand.find("mkfile-");

	if(pos != string :: npos){
		
		string file = UserCommand.substr(pos + 7);
		const char* newFile = file.c_str();
		
		int fd = open(newFile ,O_RDWR | O_CREAT  ,0644);
		if(fd  == -1){
			perror("open");
			exit(EXIT_FAILURE);
		}

	}	
	return ;
}
	
void ReadDirectory(){
	
	vector<string> directories;

	
	GetCurrentDir(currentPath, sizeof(currentPath));
	const char* basePath = currentPath;
	listOfFilesAndDirectories(basePath, directories, files, file_names);	
	
/*
	//...................Loading[########........]...................//
	cout << "Directories : " << '\n';
	for(const string& directory : directories){
		cout << directory << " " << "[DIR]" << '\n';
	}

	// cout << "Files : " << '\n';
	// for(const string& file : files){
	// 	cout << file << " " << "[FILES]" << '\n';
	// }

	cout << "Files Names : " << '\n';
	for(const string& file_name : file_names){
		cout << file_name << " " << "[FILES NAME]" << '\n';
	}	
			*/
	return;
}	

// void FindFile(string UserCommand){
// 	size_t pos = UserCommand.find("find-");
// 	struct stat fileStat;
// 	const char* filenameforsize;

// 	if(pos != string :: npos){
// 		string f_name = UserCommand.substr(pos + 5);
// 		cout << "Number of files : " << file_names.size() << '\n';

// 		for(auto i = 0; i<file_names.size(); i++){
// 			if((f_name == file_names[i])){
// 				f_name = file_names[i];
// 				filenameforsize = f_name.c_str();

// 				if(stat(filenameforsize, &fileStat) == 0){
// 					cout << "File found : " << f_name << " Size" << fileStat.st_size << "bytes" <<'\n';
// 				}
// 			}

// 		}
// 	}
// 	return;
// }

void FindFile(string UserCommand) {
    size_t pos = UserCommand.find("find-");
    struct stat fileStat;

    if (pos != string::npos) {
        string f_name = UserCommand.substr(pos + 5);
        cout << "Number of files: " << file_names.size() << '\n';

        for (const string& file : files) {
            // Extract the filename from the full path
            size_t lastSlashPos = file.find_last_of("/\\");
            if (lastSlashPos != string::npos) {
                string filename = file.substr(lastSlashPos + 1);
                if (filename == f_name) {
                    if (stat(file.c_str(), &fileStat) == 0) {
                        cout << "File found: " << filename << " [SIZE] " << fileStat.st_size << " bytes" << '\n';
                    }
                }
            }
        }
    }
}
