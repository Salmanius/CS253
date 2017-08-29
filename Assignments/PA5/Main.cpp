/*
 * Chris Cochran
 * October 2016
 * CS253
 * Programming Assignment #5
 */

#include "Reader.h"
#include "Image.h"

int main(int argc, char *argv[]) {
    
        if (argc < 3) {
            cerr << "Not enough input files given "<< endl;
            return -1;
        } else if (argc > 3) {
            cerr << "Too many input files given" << endl;
            return -1;
        }
        Reader r(argv[1], strtol(argv[2], NULL, 10));
        if (r.fileLister()== -1){
	    return -1;
        }
        if (r.kCheck()== -1){
            return -1;
        }
        r.imagePopulate();
        if (r.flagCheck()== -1){
            return -1;
        }
        r.compare();
        r.printout();

        return 0;
}
