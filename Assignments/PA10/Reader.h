#ifndef READER_INCLUDED
#define READER_INCLUDED

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <fstream>
using std::ifstream;
#include <sstream>
using std::istringstream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <math.h>
using std::pow;
#include <algorithm>
using std::find;
#include <limits>


#include "Image.h"
#include "Cluster.h"
#include "Perceptron.h"

class Reader
{
public:
    Reader(string trainingFiles, string testingFiles, int k);
    int fileLister();
    int testFileLister();
    int kCheck();
    void printout();
    void imagePopulate();
    void compare();
    int extractClass(string s);
    int flagCheck();
    int perceptronStart();
    void perceptronPrint();
  
    
private:    
    string trainingFiles;
    string testingFiles;
    vector<string> fileList;
    vector<string> testingFilesList;
    vector<Cluster> vCluster;
    vector<Cluster> testingCluster;
    vector<Perceptron> perceptronList;
    vector<int> foundClasses;
    int numFiles;
    int testingNumFiles;
    int K;
    
};
#endif
