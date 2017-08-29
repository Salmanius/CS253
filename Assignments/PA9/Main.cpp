/*
 * Chris Cochran
 * October 2016
 * CS253
 * Programming Assignment #6
 */

#include "Reader.h"
#include "Image.h"

const int argNum = 4;

int main(int argc, char *argv[]) {
        //First arg = training set (file of names of depth files)
        //Second arg = test set (file of depth image names)
        //Third arg = K;
        if (argc < argNum) {
            cerr << "Not enough input args given "<< endl;
            return -1;
        } else if (argc > argNum) {
            cerr << "Too many input args given" << endl;
            return -1;
        }
        Reader r(argv[1], argv[2], strtol(argv[3], NULL, 10)); 
        if (r.fileLister()== -1){
            return -1;
        }
        if (r.testFileLister()== -1){
            return -1;
        }
        if (r.kCheck()== -1){
            return -1;
        }
        r.imagePopulate();
        if (r.perceptronStart() == -1){
            return -1;
        }
        //r.perceptronPrint();
        if (r.flagCheck()== -1){
            return -1;
        }
        r.compare();
        r.printout();
        
        return 0;
}
