#ifndef IMAGE_INCLUDED
#define IMAGE_INCLUDED


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
using std::floor;

class Image
{
public:
    Image(string s, int arg);
    int read();
    void histogramPrint(int i);
    double normAt(int i) const;
    int rawAt(int i) const;
    string getFileName() const;
    void zeroOut();
    void singleNormalize();
    void fourHistoLoad();
    void fourNormalize();
    double normHistoFour[4][64];
    
private:
    string fileName;
    vector<int> rawVals;
    vector<int> histogram;
    vector<float> normalized;
    int histoFour[4][64];
    int readArg;
    int totalInts;
    int x;
    int y;
    //visualized as:
    //Q1 Q2
    //Q3 Q4
};
#endif
