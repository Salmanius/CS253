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
using std::stoi;
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
    void setClassName();
    int getClassName() const;
    void zeroOutFour();
    void zeroOutNine();
    void singleNormalize();
    void fourHistoLoad();
    void fourNormalize();
    void nineHistoLoad();
    void nineNormalize();
    double normHistoFour[4][64];
    double normHistoNine[9][64];
    
private:
    string fileName;
    int className;
    vector<int> rawVals;
    vector<int> histogram;
    vector<float> normalized;
    int histoFour[4][64];
    int histoNine[9][64];
    int readArg;
    int totalInts;
    int x;
    int y;
    //Histo 4 visualized as:
    //Q1 Q2
    //Q3 Q4
    
    //Histo 9 visualized as:
    //Q1 Q2 Q3
    //Q4 Q5 Q6
    //Q7 Q8 Q9
};
#endif
