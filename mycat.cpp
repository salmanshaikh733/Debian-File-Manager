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
    //define stream
    std::ofstream stream;
    //loop through arugments
    for (int i = 1; i < argc; i++) {
        FileManager fManager = FileManager(argv[i]);
        //if regular file type output
        if (fManager.getType() == "regular file") {
            fManager.Copy(stream);
        }
        stream.close();
    }

    return 0;
}
