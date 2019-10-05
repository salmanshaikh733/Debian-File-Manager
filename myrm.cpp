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

    //for loop to traverse args
    for(int i =0; i<argc; i++){
        //go through each args create file manager and delete file
        FileManager rmFile =FileManager(argv[i]);
        rmFile.removeFile();
    }
    return 0;

}