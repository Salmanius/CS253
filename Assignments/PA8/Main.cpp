/*
 * Chris Cochran
 * October 2016
 * CS253
 * Programming Assignment #6
 */

#include "Reader.h"
#include "Image.h"

const int argNum = 3;

int main(int argc, char *argv[]) {
        
        if (argc < argNum) {
            cerr << "Not enough input args given "<< endl;
            return -1;
        } else if (argc > argNum) {
            cerr << "Too many input args given" << endl;
            return -1;
        }
//         int arg3 = strtol(argv[3], NULL, 10);
//         if (arg3 < 1 || arg3 > 4){
//             cerr << "Third arguement incorrect. Only options 1, 2, 3 and 4 are allowed." << endl;
//             return -1;
//         }
        Reader r(argv[1], strtol(argv[2], NULL, 10), 1); //arg3
        if (r.fileLister()== -1){
	    return -1;
        }
        //if (r.kCheck()== -1){
        //    return -1;
        //}
        if (r.selectedClassExists() == -1){
            return -1;
        }
        r.imagePopulate();
        if (r.flagCheck()== -1){
            return -1;
        }
        r.perceptronStart();
        //r.compare();
        //r.printout(0);
        r.printout(2);
        
        return 0;
}
