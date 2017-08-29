/*
 * Chris Cochran
 * September 2016
 * CS253
 * Programming Assignment #1
 */

#include "Reader.h"
#include "Image.h"

int main(int argc, char *argv[]) {
    
        if (argc < 2) {
            cerr << "Not enough input files given "<< endl;
            return -1;
        } else if (argc > 2) {
            cerr << "Too man input files given" << endl;
            return -1;
        }
        Reader r(argv[1]);
        r.fileLister();
        //r.printout();
        r.imagePopulate();
        if (r.readList() != 0) {
            //cerr << "Error!" << endl;
            return -1;
        }
        r.compare();
        r.printPairs();        
        
        return 0;
}
