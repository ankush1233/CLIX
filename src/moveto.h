#ifndef _MOVETO_H
#define _MOVETO_H

#include <string>
#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <cstdlib>

#ifndef _WIN32 //For Windows Like Systems
#include <dirent.h>

#define GetCurrentDir getcwd
#define MAX_PATH_SIZE _MAX_PATH

#else
#include <unistd.h> //For Unix-Like System

#define GetCurrentDir _getcwd
#define MAX_PATH_SIZE 4096

#endif

void ChangeDirectory(const char*);