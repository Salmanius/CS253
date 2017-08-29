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
using std::size_t;
#include <math.h>
using std::floor;
using std::pow;
#include <vector>
using std::vector;

class Histogram
{
public:
    int histogrammer(string s);
    void normalizer();
    void histogramWriter(char c);
    vector<float> getNormalized() const;
    vector<int> getHistogram() const;
    int getX() const;
    int getY() const;
    
private:
    int totalInts;
    vector<int> histogramV;
    vector<float> normalizedV;
    int x;
    int y;
    
};
