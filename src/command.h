#ifndef _COMMAND_H
#define _COMMAND_H

#include <string>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <dirent.h>
#include <cstring>
#include <chrono>
#include <mutex>
#include <thread>
#include <sys/stat.h>
#include <cctype>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <cwchar>

#ifndef _WIN32 //For Windows Like Systems
#include <windows.h>
#define GetCurrentDir getcwd
#define MAX_PATH_SIZE _MAX_PATH

#else
#include <unistd.h> //For Unix-Like System
#define GetCurrentDir _getcwd
#define MAX_PATH_SIZE 4096
#endif

void MoveToDirectory(std::string);
void changeDirectory(const char*);
void NowDir(void);
void BackToDirectory(void);
void MakeFile(std::string);
void ScanDirectory();
void listOfFilesAndDirectories(const char*);
void FindFile(std::string);
bool isDirectory(const char*);
void DiskConfiguration(void);
void SetDrive(std::string);
void CopyFiles(std::string);
void PasteFile(std::string, std::string);
void EraseFile(std::string);
void EraseDirectory(std::string);
void EraseDirectoryRecursively(const char*);
void ReadDirectory();
void ColorizeText(const std::string&, const std::string&);
void Rename(std::string);
void help(void);
void ShowWin(void);
#endif

