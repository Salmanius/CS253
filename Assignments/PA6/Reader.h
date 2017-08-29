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
#include <math.h>
using std::pow;

#include "Image.h"
#include "Cluster.h"

class Reader
{
public:
    Reader(string files, int k, int arg);
    int fileLister();
    int kCheck();
    void printout();
    void imagePopulate();
    void compare();
    void minSumCompare();
    void invSquareDiffCompare();
    void fourCompare();
    int flagCheck();
  
    
private:    
    string inputFile;
    vector<string> fileList;
    vector<Cluster> vCluster;
    int numFiles;
    int K;
    int compareArg;
};
#endif
