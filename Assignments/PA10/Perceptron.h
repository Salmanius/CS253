#ifndef PERCEPTRON_INCLUDED
#define PERCEPTRON_INCLUDED


#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;

#include "Cluster.h"

class Perceptron
{
public:
    Perceptron(int cn, const vector<Cluster>& vClusters, const vector<Cluster>& tClusters);
    void train();
    double test(int i);
    int getClassName() const;
    void printout();
    
private:
    vector<double> data;
    int className;
    const vector<Cluster>& clusters; // reference to the vector of clusters for training
    const vector<Cluster>& testingClusters; //reference to the vector of clusters for testing
    double bias;
    int d; // setting to 1 as each perceptron is targeted at a secific class
    
};
#endif
