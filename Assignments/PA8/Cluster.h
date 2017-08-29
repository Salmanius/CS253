#ifndef CLUSTER_INCLUDED
#define CLUSTER_INCLUDED

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


class Cluster
{
public:
    Cluster(string s, int arg);
    void makeAverage();
    void build();
    int read();
    Image imageAt(int i);
    double cNormAt(int i) const;
    int getNumImages() const;
    void resetNumImages();
    void addImage(Image im);
    int findMax();
    int getFlag();
    void hStart();
    double cRawAt(int i) const;
    double clusterNorm4Average[4][64];
    double clusterNorm9Average[9][64];
    
private:   
    string fileName;
    int flag;
    int arg3;
    int numImages;
    vector<Image> images;
    vector<double> normHistoAverage;
    vector<double> rawAverage;
};
#endif
