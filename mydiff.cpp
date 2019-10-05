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

int main(int argc, char *argv[]) {
    if(argc==3){
        //get the input
        std::string name1=argv[1];
        std::string name2=argv[1];
        //create the files
        FileManager file1=FileManager(name1);
        FileManager file2=FileManager(name2);

        //check to see if right type
        int output;
        if(file1.getType()=="regular file"&&file2.getType()=="regular file"){
            //compare files
            output=file1.compareFile(file2);
        }
        else {
            std::cout<<"invliad file input";
        }
        //if 0 same file if not different files
        if(output==0){
            std::cout<<"Same files";
        }
        else {
            std::cout<<"Files not the same";
        }

    }



    return 0;
}
