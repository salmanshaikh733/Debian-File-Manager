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
    //must have 3 args
    if (argc == 3) {


        //get the name and location
        std::string file1=argv[1];
        std::string location=argv[2];
        //create the manager and find the file
        FileManager manager =FileManager(file1);
        std::ofstream filestream;
        //call the copy function store return value to determine if success
        int output=manager.Copy(filestream);
        FileManager fileM=FileManager("copy"+file1);
        //if 0 output successful
        if(output==0){
            fileM.renameFile(location);
        }
        //error message
        else {
            std::cout<<"error";
        }
    }
    //invalid args
    else {
        std::cout<<"Error invalid arguments";
    }

    return 0;

}