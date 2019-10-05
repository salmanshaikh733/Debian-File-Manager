//
// Created by salman on 2019-10-03.
//

//
// Created by salman on 2019-10-03.
//

#include<iostream>
#include<grp.h>
#include<vector>
#include<pwd.h>
#include<unistd.h>
#include<time.h>
#include <fstream>
#include "FileManager.h"
//define main
int main(int argc, char *argv[]) {
    //if only one args
    if (argc == 1) {
        std::string name = ".";
        FileManager fileManager = FileManager(name);
        //check to see if it is a directory
        if (fileManager.getType() == "directory") {
            //expand into vector
            fileManager.Expand();
            //create vector with sub files
            std::vector<FileManager> vector1 = fileManager.getChildren();
            //loop through vector and output children names
            for (int i = 0; i < vector1.size(); i++) {
                if (i==6){
                    std::cout << "\t"<<vector1[i].getName() << std::endl;
                }
                //loop through vector and output children names
                std::cout << "\t"<<vector1[i].getName() ;

            }
        }
    }

    //if 2 args ls -1
    if (argc == 2 && argv[1]) {
        std::string name = argv[1];
        //if -l
        //list the contents of the directory
        if (name != "-l") {
            FileManager fileManager = FileManager(name);
            if (fileManager.getType() == "directory") {
                fileManager.Expand();
                //expand and go thourgh directory as vector and output name
                std::vector<FileManager> vector = fileManager.getChildren();
                for (int i = 0; i < vector.size(); i++) {
                    if (i==6){
                        std::cout << "\t"<<vector[i].getName() << std::endl;
                    }
                    //loop through vector and output children names
                    std::cout << "\t"<<vector[i].getName() ;
                }
            }
            //if just regular file output name
            if (fileManager.getType() == "regular file") {
                std::cout << fileManager.getName();
            }

            //if ls -l
        } else {
            FileManager manager = FileManager(".");
            if (manager.getType() == "directory") {
                manager.Expand();
                //if ls -l then output permissions
                std::vector<FileManager> vector1 = manager.getChildren();
                for (int i = 0; i < vector1.size(); i++) {
                    std::cout << "" << vector1[i].getName();
                    std::cout << "\t" << vector1[i].getPermissions();
                    std::cout << "\t" << vector1[i].getOwnerName();
                    std::cout << "\t" << vector1[i].getGroupName();
                    std::cout << "\t" << vector1[i].getSize();
                    std::cout << "\t" << vector1[i].getAccessTime();
                }

            }

        }

    }

    return 0;
}
