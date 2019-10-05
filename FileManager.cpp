//
// Created by salman on 2019-10-03.
//

#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <fstream>
#include <cstring>
#include "FileManager.h"
#include <dirent.h>
#include <time.h>

//using namespace std;
//constructor for class
FileManager::FileManager(std::string name) {

    //initialize variables
    FileName = name;
    const char *charName = FileName.c_str();
    struct stat st;
    stat(charName, &st);

    //swtich statement to determine file type found on documentation website
    switch (st.st_mode & S_IFMT) {
        case S_IFBLK:
            Type = "block device";
            break;
        case S_IFCHR:
            Type = ("character device");
            break;
        case S_IFDIR:
            Type = ("directory");
            break;
        case S_IFIFO:
            Type = ("FIFO/pipe");
            break;
        case S_IFLNK:
            Type = ("symlink");
            break;
        case S_IFREG:
            Type = ("regular file");
            break;
        case S_IFSOCK:
            Type = ("socket");
            break;
        default:
            Type = ("unknown?");
            break;
    };
    //set rest of instance variables
    errorNum = 0;
    size = st.st_size;
    ownerID = st.st_uid;
    groupId = st.st_gid;
    permissions = st.st_mode;


    struct passwd *pwd;
    pwd = getpwuid(getuid());
    ownerName = pwd->pw_name;


    struct group *grp;
    blockSize = st.st_blksize;
    //cast time type to constant
    accessTime = ctime(reinterpret_cast<const time_t *>(&st.st_atim));
    modificationTime = ctime(reinterpret_cast<const time_t *>(&st.st_mtim));
    statusChangeTime = ctime(reinterpret_cast<const time_t *>(&st.st_ctim));
}

//getters and setters
std::string FileManager::getName() {
    //std::cout<<FileName;
    return FileName;
}

std::string FileManager::getType() {
    return Type;
}

int FileManager::getSize() {
    return size;
}

std::string FileManager::getOwnerName() {
    return ownerName;
}

int FileManager::getOwnerID() {
    return ownerID;
}

int FileManager::getGroupName() {
    return groupName;
}

int FileManager::getGroupID() {
    return groupId;
}

int FileManager::getPermissions() {
    return permissions;
}

std::string FileManager::getModTime() {
    return modificationTime;
}

std::string FileManager::getAccessTime() {
    return accessTime;
}

std::string FileManager::getChangeTime() {
    return statusChangeTime;
}

int FileManager::getBlockSize() {
    return blockSize;
}

int FileManager::getErrorNum() {
    return errorNum;
}

std::vector<FileManager> FileManager::getChildren() {
    return children;
}

void FileManager::setErrorNum(int num) {
    errorNum = num;
}



//rename function
int FileManager::renameFile(std::string newFileName) {
    //get old name and new name convert to char from string
    char oldName[FileName.length() + 1];
    char newName[newFileName.length() + 1];
    //copy into char array
    strcpy(oldName, FileName.c_str());
    strcpy(newName, newFileName.c_str());

    //call function
    int output = rename(oldName, newName);
    FileName = newFileName;
    //check to see if it worked
    if (output == 0) {
        std::cout << "success";
        return 0;
    } else {
        std::cout << "failure";
        errorNum = errno;
        return -1;
    }

}
//remove file function
int FileManager::removeFile() {
    //convert string to char array
    char fileName[FileName.length() + 1];
    strcpy(fileName, FileName.c_str());
    //call fucntion
    int output = unlink(fileName);

    //check output 0 or -1
    if (output == 0) {
        std::cout << "success";
    } else {
        errorNum = errno;
        std::cout << "failure";
    }
}

//compare two files
int FileManager::compareFile(FileManager fileName) {

    //get the block size
    char file1[blockSize];
    char file2[blockSize];
    //create the streams
    std::ifstream file_one;
    std::ifstream file_two;
    //open the files
    file_one.open(FileName);
    file_two.open(fileName.getName());

    //while not end of file compare
    while (!file_one.eof() && !file_two.eof()) {
        //output streams into respective files
        file_one >> *file1;
        file_two >> *file2;

        //compare the file streams
        if (*file1 != *file2) {
            return -1;
        }
    }
    //close files
    file_one.close();
    file_two.close();
    errorNum = errno;
    return 0;
}


//expand function, store
void FileManager::Expand() {

    //check to see if directory
    if (Type == "directory") {

        //use the DIR type to open the specified directory
        DIR *directory = opendir(FileName.c_str());
        struct dirent *dir;
        //if directory not empty
        if (directory != NULL) {
            //read the directory
            while ((dir = readdir(directory)) != NULL) {
                //create a new file type for the directory children
                FileManager *fileManager = new FileManager(dir->d_name);
                //add to end of vector
                children.push_back(*fileManager);
            }
            //errorNum = errno;
            int closeDir = closedir(directory);
            if (closeDir == 0) {
                //success in closing
            } else {  
                errorNum = errno;//error in clsosing
            }
        } else {
            errorNum = errno;
        }

    } else {
        errorNum = ENOTSUP;
        //return error
    }

}


//copy files
int FileManager::Copy(std::ofstream &file) {
    //declare file stream
    std::ifstream fileStream;
    //char to hold file data of the blocksize of the file
    char fileData[blockSize];
//   if regular file then proceed otherwise return error message
    if (Type == "regular file") {
        fileStream.open(FileName);
        //do not skip anything
        fileStream >> std::noskipws;
        //open the file
        file.open("copy" + FileName);
        //while not end of stream
        while (!fileStream.eof()) {
            //take the file stream and store into fileData pointer
            fileStream >> *fileData;
            if (fileStream.good()) {
                //output the data
                std::cout <<fileData;
                file << *fileData;
            }
        }
        //close the file and stream
        fileStream.close();
        file.close();
        return 0;
    //else output error
    } else {
        errorNum = errno;
        //fileStream.close();
        file.close();
        std::cout << "COULD NOT COPY";
    }
}

//destructor
FileManager::~FileManager() {
    //std::cout << "\nDESTRUCTED";
}