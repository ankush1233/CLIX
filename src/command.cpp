#include "command.h"
#include <iostream>
#include <sys/stat.h>  // For stat() function
#ifdef _WIN32
#include <windows.h>  // For Windows-specific functions
#endif


using namespace std;

//char PathBuffer[MAX_PATH_SIZE];
char currentPath[MAX_PATH_SIZE];
	
namespace DynamicDataStructures{
	vector<string> directories;
	vector<string> file_names;
	vector<string> files;
	unordered_map<string, string> filewithDirectory;
};

bool isDirectory(const char* path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0) {
        return false;  // Unable to get file info, assume it's not a directory
    }
    return S_ISDIR(statbuf.st_mode) != 0;
}

void listOfFilesAndDirectories(const char* basePath, vector<std::string>& directories, vector<std::string>& files, vector<string>& file_names) {
    // Open the directory
    using namespace DynamicDataStructures;
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
	
	size_t pos = UserCommand.find("moveto ");
		
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
	size_t pos = UserCommand.find("mkfile ");

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
	using namespace DynamicDataStructures;

	GetCurrentDir(currentPath, sizeof(currentPath));
	const char* basePath = currentPath;

	DynamicDataStructures::directories.clear();
	DynamicDataStructures::file_names.clear();
	DynamicDataStructures::files.clear();

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

void FindFile(string UserCommand) {
	using namespace DynamicDataStructures;

    size_t pos = UserCommand.find("find ");
    struct stat fileStat;
    string tab = " ";
    string totalSpacesize = " ";
    if (pos != string::npos) {
        string f_name = UserCommand.substr(pos + 5);

        for(auto i = 0; i<f_name.size(); i++){
        	totalSpacesize = totalSpacesize + tab;
        }

        cout << "Number of files: " << file_names.size() << '\n';
        cout << "[FILE]" << totalSpacesize << " [SIZE]" << totalSpacesize <<"[DIR]"<<"\n";
        for (const string& file : files) {
            // Extract the filename from the full path
            size_t lastSlashPos = file.find_last_of("/\\");

            if (lastSlashPos != string::npos) {
                string filename = file.substr(lastSlashPos + 1);
                string directoryOfFile = file.substr(0, lastSlashPos);
                filewithDirectory[directoryOfFile] = filename;
                
                if (f_name == filename) {
                    if (stat(file.c_str(), &fileStat) == 0) {
                    	float accurateFileSize = static_cast<float>((fileStat.st_size)/1024.0);
                        cout << filename << "\t" << accurateFileSize << " KB" << '\t' << directoryOfFile <<'\n'; 
                    }
                }
            }
        }
    }
    return;
}

void DiskConfiguration(){

	GetCurrentDir(currentPath, sizeof(currentPath));
	string DiskPath = string(currentPath);
	string Disk = DiskPath.substr(0, 3);
	const char* Drive = Disk.c_str();
	DWORD sectorsPerCluster, bytesPerSector, freeClusters, totalClusters;
	bool check;
	check = GetDiskFreeSpaceA(Drive, &sectorsPerCluster, &bytesPerSector, &freeClusters, &totalClusters);
	if (check) {
		ULONGLONG freeSpaceBytes = (ULONGLONG)freeClusters * sectorsPerCluster * bytesPerSector;
		ULONGLONG totalSpaceBytes = (ULONGLONG)totalClusters * sectorsPerCluster * bytesPerSector;
		double gigabyte = 1024 * 1024 * 1024; // 1 GB is 1024 MB, 1 MB is 1024 KB, 1 KB is 1024 bytes

		double freeSpaceGB = (double)freeSpaceBytes / gigabyte;
		double totalSpaceGB = (double)totalSpaceBytes / gigabyte;

		cout << "Total space on " << Drive << "  " << totalSpaceGB << "GB" << '\n';
		cout << "Free space on " << Drive  << "   " << freeSpaceGB << "GB" << '\n';

		double disk_percentage = ((freeSpaceGB) / (totalSpaceGB)) * 100;
		std::cout << "Percentage Used :   " <<disk_percentage << "%" <<'\n';
		int bar_size = (40*(disk_percentage))/100;

		std::cout << Drive;
		std::cout << "[";
		for (auto i = 0; i < (40 - bar_size); i++) {
			std::cout << "#";
		}
		for (auto i = 0; i < bar_size; i++) {
			std::cout << ".";
		}
		std::cout << "]";
	}
	cout << '\n';
	return;
}