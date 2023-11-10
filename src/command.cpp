#include "command.h"
#include <iostream>
#include <sys/stat.h>  // For stat() function
#include <windows.h>
#include <iostream>

// Add these lines to include necessary headers
#define Megabyte 0x100000
#ifdef _WIN32
#include <windows.h>  // For Windows-specific functions
#endif


using namespace std;

//char PathBuffer[MAX_PATH_SIZE];
char currentPath[MAX_PATH_SIZE];

//Buffer to hold the file path and file name
string SourceFilePath;
string FileBuffer;

	
//Containers to hold the Directories, files, filenames;
namespace DynamicDataStructures{
	vector<string> directories;
	vector<string> file_names;
	vector<string> files;
	unordered_map<string, string> filewithDirectory;
};


bool isDirectory(const char* path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0) {
        return false;  //It's not a directory
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
				// It's a directory visit the directory recursively
				directories.push_back(fullPath);
				listOfFilesAndDirectories(fullPath.c_str(), directories, files, file_names);

			} else {
				// It's a file, so add it to the files vector and do a recursive call
				file_names.push_back(string(entry->d_name));
				files.push_back(fullPath);
			}

		}
	}
	closedir(dir);
}


//Change Directory function for all
void changeDirectory(const  char* path){

	if(chdir(path) != 0){
		cerr << "Error: Unable to change directory to " << path << '\n';
	}
	return ;
}


void MoveToDirectory(string UserCommand){

	GetCurrentDir(currentPath, sizeof(currentPath));
	size_t pos = UserCommand.find("mvt ");
		
	if(pos != string :: npos){

		string dir = UserCommand.substr(pos + 4);
		string newdir = string(currentPath) + '\\' + dir; 
			
 		const char* newDirectory = newdir.c_str();
    	changeDirectory(newDirectory);

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

	}
	return ;
}

//Get the current directory
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
			perror("Message : ");
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


void SetDrive(string UserCommand){

	string Drive = UserCommand.substr(9);
	Drive = Drive + ":\\";
	const char* DriveBuffer = Drive.c_str();

	if(SetCurrentDirectory(DriveBuffer) == 0){
		cerr << "Unable to change Drive " << '\n';
	}
	return ;
}


void CopyFiles(string UserCommand){
	size_t pos = UserCommand.find("c ");

	if(pos != string :: npos) {

		GetCurrentDir(currentPath, sizeof(currentPath));
		FileBuffer = UserCommand.substr(2);

		string CurrentPathString(currentPath);
		CurrentPathString = CurrentPathString + "\\" + FileBuffer;

		SourceFilePath = CurrentPathString;
	} 
	else{

		if(UserCommand.find("p") != string::npos && (!SourceFilePath.empty())){

			PasteFile(SourceFilePath, FileBuffer);
		}
		else{

			cerr << "Unable to PasteFile \n";
		}
	}
	return;
}


void PasteFile(string SourceFilePath, string FileBuff){

	GetCurrentDir(currentPath, sizeof(currentPath));
	string DestinationFilePath(currentPath);
	DestinationFilePath = DestinationFilePath + "\\" + FileBuff;

	const char* SourceFilePathPaste = SourceFilePath.c_str();
	const char* DestinationFilePathPaste = DestinationFilePath.c_str();
	
	ifstream sourceFile(SourceFilePathPaste, ios::binary);
    ofstream destinationFile(DestinationFilePathPaste, ios::binary);

    if (!sourceFile) {
        std::cerr << "Error opening source file: " << SourceFilePathPaste << std::endl;
        return;
    }
    if (!destinationFile) {
        std::cerr << "Error opening destination file: " << DestinationFilePathPaste << std::endl;
        return;
    }

    const int buffer_size = 4096;
    char buffer[buffer_size];

    auto start = std::chrono::high_resolution_clock::now();
    long long totalBytesCopied = 0;
    long long previousBytesCopied = 0;

    while (!sourceFile.eof()) {

        sourceFile.read(buffer, buffer_size);
        std::streamsize bytesRead = sourceFile.gcount();
        destinationFile.write(buffer, bytesRead);
        totalBytesCopied += bytesRead;

        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();

        if (elapsed >= 1) {
            double speed = static_cast<double>(totalBytesCopied - previousBytesCopied);
            speed = speed/Megabyte;
            std::cout << "Copying... " << ((totalBytesCopied)/Megabyte) << " MB, Speed: " << speed << " Mbps" << std::endl;
            start = now;
            previousBytesCopied = totalBytesCopied;
        }     
    }

    cout << "File copy operation completed" << std::endl;
    return ;
}


void EraseFile(string UserCommand){

	string FileBuff = UserCommand.substr(3);
	const char* File = FileBuff.c_str();

	char agree;
	cout << "Warning the file will get removed permanently!! Are you sure to remove it? (Y/N) : ";
	cin >> agree;
	cout << '\n';

	if(agree == 'Y' || agree == 'y'){
		if(remove(File) == 0){
			cout << "File Erased Successfully\n";
		
		} else{
			cerr << "Unable to EraseFile\n";
		
		}
	}

	return ;
}


void EraseDirectory(string UserCommand){

	GetCurrentDir(currentPath, sizeof(currentPath));
	FileBuffer = UserCommand.substr(3);

	string stringCurrentPathpush(currentPath);
	stringCurrentPathpush = stringCurrentPathpush + "\\" + FileBuffer;

	const char* basePath = stringCurrentPathpush.c_str();
	
	EraseDirectoryRecursively(basePath);
	return;
}


void EraseDirectoryRecursively(const char* basePath){

	DIR* dir = opendir(basePath);

    if (!dir) {
        std::cerr << "Error opening directory" << std::endl;
        return;
    }

	struct dirent *entry;

	while((entry = readdir(dir)) != NULL){
		if(strcmp(entry -> d_name, ".") != 0 && strcmp(entry ->d_name, "..") != 0){
			
			string fullPath = string(basePath) + "/" + string(entry->d_name);
			
			if(isDirectory(fullPath.c_str())){
				EraseDirectoryRecursively(fullPath.c_str());
			
			} else{
				remove(fullPath.c_str());	

			}
		}
	}

	closedir(dir);
	rmdir(basePath);
}


