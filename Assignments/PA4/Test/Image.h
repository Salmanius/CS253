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
using std::pow;

class Image
{
public:
    Image(string fileName): fileName(fileName), totalInts(0), closestPairWiseSum(0.0){};
    int read();
    void histogramWriter(char c);
    void setClosestPair(string s);
    void setClosestPairWiseSum(double d);
    string getClosestPair() const;
    double getClosestPairWiseSum() const;
    double normAt(int i) const;
    string getFileName() const;
private:
    string fileName;
    vector<int> rawVals;
    vector<int> histogram;
    vector<float> normalized;
    int totalInts;
    int x;
    int y;
    //for compare
    string closestPair;
    double closestPairWiseSum;
};
#endif
