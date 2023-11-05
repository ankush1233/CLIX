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
#include <thread>
#include <sys/stat.h>

using namespace std;

#ifndef _WIN32 //For Windows Like Systems
#include <windows.h>
#define GetCurrentDir getcwd
#define MAX_PATH_SIZE _MAX_PATH

#else
#include <unistd.h> //For Unix-Like System

#define GetCurrentDir _getcwd
#define MAX_PATH_SIZE 4096
#endif

void MoveToDirectory(string);
void changeDirectory(const char*);
void NowDir();
void BackToDirectory();
void MakeFile(string);
void ReadDirectory();
void listOfFilesAndDirectories(const char*, vector<string>&, vector<string>&, vector<string>&);
void FindFile(string);
bool isDirectory(const char*);
#endif

