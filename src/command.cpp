#include "command.h"
#include <iostream>
#include <sys/stat.h>  // For stat() function
#include <windows.h>
#include <iostream>

// Add these lines to include necessary headers
#define Megabyte 0x100000
#define Gigabyte 0x40000000
#ifdef _WIN32
#include <windows.h>  // For Windows-specific functions
#endif

//char PathBuffer[MAX_PATH_SIZE];
char currentPath[MAX_PATH_SIZE];

//Buffer to hold the file path and file name
std::string SourceFilePath;
std::string FileBuffer;

	
//Containers to hold the Directories, files, filenames;
namespace DynamicDataStructures{
	std::vector<std::string> directories;
	std::vector<std::string> file_names;
	std::vector<std::string> files;
	std::unordered_map<std::string, std::string> filewithDirectory;
	std::unordered_map<std::string, std::unordered_set<std::string>> FileMappingWithDirectory;
	std::unordered_map<std::string, bool> CheckIfVisited;
};

bool isDirectory(const char* path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0) {
        return false;  //It's not a directory then return false
    }
    return S_ISDIR(statbuf.st_mode) != 0;
}


void listOfFilesAndDirectories(const char* basePath) {
    // Open the directory
    using namespace DynamicDataStructures;
    DIR* dir = opendir(basePath);

    if (!dir) {
        std::cerr << "Error opening directory" << '\n';
        return;
    }

    struct dirent* entry;
	while ((entry = readdir(dir))) {
		if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
			std::string_view basePathView(basePath);
			std::string_view entryName(entry->d_name);
			// Construct the full path for the current item
			std::string fullPath = std::string(basePathView) + "/" + std::string(entryName);

			//For Caching
			if(CheckIfVisited[fullPath] == false) {
				if (isDirectory(fullPath.c_str())) {
					// It's a directory visit the directory recursively
					listOfFilesAndDirectories(fullPath.c_str());

				} else {
					FileMappingWithDirectory[std::string(entryName)].insert(fullPath);
				
				}
			} else{
				CheckIfVisited[fullPath] = true;
			
			}
		}
	}
	closedir(dir);
}


void ScanDirectory(){

	using namespace DynamicDataStructures;

	GetCurrentDir(currentPath, sizeof(currentPath));
	const char* basePath = currentPath;

	auto start = std::chrono::high_resolution_clock::now();
	listOfFilesAndDirectories(basePath);	
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
	std::cout << elapsed << "s"; 
	return;
}

//Get the Back Directory
void BackToDirectory() {

	GetCurrentDir(currentPath, sizeof(currentPath));

	std::string StringConversionOfPath(currentPath);
	size_t LastBackSlash = StringConversionOfPath.find_last_of('\\');
	
	if (LastBackSlash != std::string::npos) {
		std::string newPath = StringConversionOfPath.substr(0, LastBackSlash);
		if(newPath == "C:"){
			newPath = newPath + "\\";
			chdir(newPath.c_str());
		}
		chdir(newPath.c_str());
	}
	return ;
}

//Get the current directory
void NowDir(){

	if(GetCurrentDir(currentPath, sizeof(currentPath)) != nullptr){
		std::cout << "Current directory: " << currentPath << '\n';
	}	
}


void MakeFile(std::string UserCommand){

	size_t pos = UserCommand.find("mkfile ");
	int fd;

	if(pos != std::string::npos){
		
		std::string file = UserCommand.substr(pos + 7);
		const char* newFile = file.c_str();
		
		fd = open(newFile ,O_RDWR | O_CREAT  ,0644);
		if(fd  == -1){
			perror("Message : ");
			exit(EXIT_FAILURE);
		}
	}	
	close(fd);
	return ;
}

	
void MoveToDirectory(std::string UserCommand){

	GetCurrentDir(currentPath, sizeof(currentPath));
	size_t pos = UserCommand.find("mvt ");
		
	if(pos != std::string::npos){

		std::string dir = UserCommand.substr(pos + 4);
		std::string newdir = std::string(currentPath) + '\\' + dir; 
			
 		chdir(newdir.c_str());
	}
	return;
}
	

void FindFile(std::string UserCommand) {
	
	using namespace DynamicDataStructures;

    size_t pos = UserCommand.find("find ");
    struct stat fileStat;
    
    std::string tab = " ";
    std::string totalSpacesize = " ";

    if (pos != std::string::npos) {
        std::string f_name = UserCommand.substr(pos + 5);

        for(auto i = 0; i<f_name.size(); i++) {
        	totalSpacesize = totalSpacesize + tab;
        }

        std::cout << "[FILE]" << totalSpacesize << " [SIZE]" << totalSpacesize <<"[DIR]"<<"\n";

    	if(FileMappingWithDirectory.find(f_name) != FileMappingWithDirectory.end()){

    		for (const auto& path : FileMappingWithDirectory[f_name]) {
    			if (stat(path.c_str(), &fileStat) == 0){
    				float accurateFileSize = static_cast<float>((fileStat.st_size)/1024.0);
    				//std::cout << "Last modified time: " << ctime(&fileStat.st_mtime);
        			std::cout << f_name << "\t" << accurateFileSize << " KB" << '\t' << path <<'\n';
        		}
    		}
    	}
    }
    return;
}


void DiskConfiguration(){

	GetCurrentDir(currentPath, sizeof(currentPath));

	std::string DiskPath = std::string(currentPath);
	std::string Disk = DiskPath.substr(0, 3);
	
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

		std::cout << "Total space on " << Drive << "  " << totalSpaceGB << "GB" << '\n';
		std::cout << "Free space on " << Drive  << "   " << freeSpaceGB << "GB" << '\n';

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
	std::cout << '\n';
	return;
}


void SetDrive(std::string UserCommand){

	std::string Drive = UserCommand.substr(9);
	Drive = Drive + ":\\";
	const char* DriveBuffer = Drive.c_str();

	if(SetCurrentDirectory(DriveBuffer) == 0){
		std::cerr << "Unable to change Drive " << '\n';
	}
	return ;
}


void CopyFiles(std::string UserCommand){
	size_t pos = UserCommand.find("c ");

	if(pos != std::string::npos) {

		GetCurrentDir(currentPath, sizeof(currentPath));
		FileBuffer = UserCommand.substr(2);

		std::string CurrentPathString(currentPath);
		CurrentPathString = CurrentPathString + "\\" + FileBuffer;

		SourceFilePath = CurrentPathString;
	} 
	else{

		if(UserCommand.find("p") != std::string::npos && (!SourceFilePath.empty())){

			PasteFile(SourceFilePath, FileBuffer);
		}
		else{

			std::cerr << "Unable to PasteFile \n";
		}
	}
	return;
}


void PasteFile(std::string SourceFilePath, std::string FileBuff){

	GetCurrentDir(currentPath, sizeof(currentPath));
	std::string DestinationFilePath(currentPath);
	DestinationFilePath = DestinationFilePath + "\\" + FileBuff;

	const char* SourceFilePathPaste = SourceFilePath.c_str();
	const char* DestinationFilePathPaste = DestinationFilePath.c_str();
	
	std::ifstream sourceFile(SourceFilePathPaste, std::ios::binary);
    std::ofstream destinationFile(DestinationFilePathPaste, std::ios::binary);

    if (!sourceFile) {
        std::cerr << "Error opening source file: " << SourceFilePathPaste << '\n';
        return;
    }
    if (!destinationFile) {
        std::cerr << "Error opening destination file: " << DestinationFilePathPaste << '\n';
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
   	
   	sourceFile.close();
	destinationFile.close();

    std::cout << "File copy operation completed" << '\n';
    return ;
}


void EraseFile(std::string UserCommand){

	std::string FileBuff = UserCommand.substr(3);
	const char* File = FileBuff.c_str();

	char agree;
	std::cout << "Warning the file will get removed permanently!! Are you sure to remove it? (Y/N) : ";
	std::cin.get(agree);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << '\n';

	if(agree == 'Y' || agree == 'y'){
		if(remove(File) == 0){
			std::cout << "File Erased Successfully\n";
		
		} else{
			std::cerr << "Unable to EraseFile\n";		
		}
	}
	return ;
}


void EraseDirectory(std::string UserCommand){

	GetCurrentDir(currentPath, sizeof(currentPath));
	FileBuffer = UserCommand.substr(3);

	std::string stringCurrentPathpush(currentPath);
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
			
			std::string fullPath = std::string(basePath) + "/" + std::string(entry->d_name);
			
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



