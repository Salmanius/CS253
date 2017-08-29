#ifndef READER_INCLUDED
#define READER_INCLUDED

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <iomanip>
using std::fixed;
using std::setprecision;
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <vector>
using std::vector;

#include "Image.h"


class Reader
{
public:
    Reader(string files): inputFile(files), numFiles(0){};
    int fileLister();
    void printout();
    void imagePopulate();
    int readList();
    void compare();
    void printPairs();
    //compare images functions
private:    
    string inputFile;
    vector<string> fileList;
    vector<Image> images;
    int numFiles;
};
#endif
