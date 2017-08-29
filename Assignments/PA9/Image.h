#ifndef IMAGE_INCLUDED 
#define IMAGE_INCLUDED


#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <string>
using std::string;
using std::stoi;
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector;
#include <math.h>
using std::floor;

class Image
{
public:
    Image(string s);
    int read();
    void histogramPrint(int i);
    double normAt(int i) const;
    int rawAt(int i) const;
    string getFileName() const;
    void setClassName();
    int getClassName() const;
    void singleNormalize();
    
private:
    string fileName;
    int className;
    vector<int> rawVals;
    vector<int> histogram;
    vector<float> normalized;
    int totalInts;
    int x;
    int y;
    
};
#endif
