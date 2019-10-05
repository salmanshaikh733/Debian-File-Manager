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

int main(int argc, char *argv[]) {
    //check to see if valid num of args
    if (argc == 3) {
        //get old name and new name
        std::string oldName=argv[1];
        std::string newName=argv[2];
        //create file manager with old name
        FileManager file =FileManager(oldName);
        //rename with new name
        file.renameFile(newName);
    }
    //output if not 3 args
    else {
        std::cout<<"Error invalid arguments";
    }

    return 0;

}