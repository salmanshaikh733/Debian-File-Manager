//
// Created by salman on 2019-10-03.
//

#ifndef INC_3307INDIVIDUALASSIGNMENT_FILEMANAGER_H
#define INC_3307INDIVIDUALASSIGNMENT_FILEMANAGER_H

#include<vector>
#include<string>
#include<time.h>


//using namespace std;

class FileManager {


    //make the variables private so they cannot be accessed by other methods.
private:

    std::string FileName;
    std::string Type;
    int size;
    std::string ownerName;
    int ownerID;
    int groupId;
    int groupName;
    int permissions;

    std::string accessTime;
    std::string modificationTime;
    std::string statusChangeTime;

    int blockSize;
    std::vector<FileManager> children;
    int errorNum;


    //make the constructor and make all the getter and setters public so they can be used to access the attributes and change them.
public:
    //constructor for the class initialize everthing using the stat function.
    FileManager(std::string name);

    //getters and setters
    std::string getName();

    std::string getType();

    int getSize();
    std::string getOwnerName();
    int getOwnerID();
    int getGroupName();

    int getGroupID();

    int getPermissions();

    std::string getModTime();

    std::string getAccessTime();

    std::string getChangeTime();
    int getBlockSize();
    int getErrorNum();
//vector to store directory contents
    std::vector<FileManager> getChildren();
//error num
    void setErrorNum(int num);

    //destructor method
    ~FileManager();

    //rename function
    int renameFile(std::string newFileName);

    //remove function
    int removeFile();
//compare file
    int compareFile(FileManager fileName);
//expand directory
    void Expand();
//copy file
    int Copy(std::ofstream &file);

};


#endif //INC_3307INDIVIDUALASSIGNMENT_FILEMANAGER_H
