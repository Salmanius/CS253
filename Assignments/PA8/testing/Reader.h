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
    void printout(int i);
    void imagePopulate();
    void compare();
    void minSumCompare();
    void invSquareDiffCompare();
    void compareQuality();
    void fourCompare();
    void nineCompare();
    void perceptronStart();
    int extractClass(string s);
    int setD(int a, int i);
    int flagCheck();
    int selectedClassExists();
    
  
    
private:    
    string inputFile;
    vector<string> fileList;
    vector<Cluster> vCluster;
    vector<double> perceptron;
    int numFiles;
    int K;
    int selectedClass;
    int compareArg;
    double compareQualitySum;
    
};
#endif
