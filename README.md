
# CLIX

A command Line interface Xplorer or you can say a Command Line Inerface file explorer.
## Run Locally

Clone the project

```bash
  $ git clone https://github.com/ankush1233/CLIX.git
```

Go to the project directory

```bash
  $ cd CLIX
```

Build the Code: 
Use mingw32-make to compile the code. Run the following command in your terminal:

```bash
  $ mingw32-make all
```

 Navigate to build directory

 ```bash
  $ cd build
```
 Run the CLIX File Explorer in git bash
 ```bash
  $ ./myprogram.exe
```
 Run the CLIX in command prompt
 ```bash
  $ .\myprogram
```

# Guide For Commands 


Command: back
Description: Move to the parent directory.

Command: nd
Description: Display the current working directory.

Command: exit
Description: Exit the program.

Command: clear
Description: Clear the console screen.

Command: scandir
Description: Scan and display the contents of the current directory.

Command: driveconfig
Description: Display information about the available drives.

Command: mvt <destination>
Description: Move to the specified directory. Example: mvt C:\Example\Directory

Command: mkfile <filename>
Description: Create a new file in the current directory. Example: mkfile NewFile.txt

Command: find <filename>
Description: Search for a file in the current directory and its subdirectories. Example: find Example.txt

Command: setdrive <drive letter>
Description: Set the current drive. Example: setdrive D:

copy/paste (CopyFiles):
Command: copy <source> <destination> or paste
Description: Copy files from the source directory to the destination directory or paste previously copied files.
ef (EraseFile):

Command: ef <filename>
Description: Delete a file in the current directory. Example: ef OldFile.txt

ed (EraseDirectory):
Command: ed <directory>
Description: Delete a directory and its contents. Example: ed OldDirectory

readdir:
Command: readdir
Description: Read and display the contents of the current directory.

Invalid Command:
Description: Displayed when the entered command is not recognized.

