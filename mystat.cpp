//
// Created by salman on 2019-10-03.
//

#include<iostream>
#include <fstream>
#include<grp.h>
#include<vector>
#include<pwd.h>
#include<unistd.h>
#include<time.h>
#include "FileManager.h"


int main(int argc, char *argv[]) {
    //check to see if 2 args
    if (argc == 2) {
        //get file name
        std::string fileName=argv[1];
        //create file manager
        FileManager file = FileManager(fileName);

        //make sure regular file type
        if (file.getType() == "regular file") {
            //output all information
            std::cout << "\nFile name is " << file.getName();
            std::cout << "\nFile type is " << file.getType();
            std::cout << "\nFile size is " << file.getSize();
            std::cout << "\nFile owner id is " << file.getOwnerID();
            std::cout << "\nFile owner name is " << file.getOwnerName();
            std::cout << "\nFile group id is " << file.getGroupID();
            std::cout << "\nFile group name is " << file.getGroupName();
            std::cout << "\nFile block size " << file.getBlockSize();
            std::cout << "\nFile permissions " << file.getPermissions();
            std::cout << "\nFile access time " << file.getAccessTime();
            std::cout << "\nFile change time" << file.getChangeTime();
            std::cout << "\nFile mod time " << file.getModTime();
        }
        //if directory
        if(file.getType()=="directory"){
            file.Expand();
            std::vector<FileManager> children =file.getChildren();
            for(int i=0; i<children.size(); i++){
                std::cout<<"\t"<<children[i].getName();
                std::cout<<"\t"<<children[i].getType();
                std::cout<<"\t"<<children[i].getSize();
                std::cout<<"\t"<<children[i].getOwnerID();
                std::cout<<"\t"<<children[i].getOwnerName();
                std::cout<<"\t"<<children[i].getGroupName();
                std::cout<<"\t"<<children[i].getGroupID();
                std::cout<<"\t"<<children[i].getPermissions();
                std::cout<<"\t"<<children[i].getAccessTime();
                std::cout<<"\t"<<children[i].getChangeTime();
                std::cout<<"\t"<<children[i].getModTime();
            }
        }
    }

    //if invalid args
    else {

        std::cout<<"Error invalid args";
    }
    return 0;
}