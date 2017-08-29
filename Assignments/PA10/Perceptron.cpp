#include "Perceptron.h"

Perceptron::Perceptron(int cn, const vector<Cluster>& vClusters, const vector<Cluster>& tClusters): className(cn), clusters(vClusters), testingClusters(tClusters), bias(0), d(1){
    train();
};

void Perceptron::train(){
    //cout << "Perceptron " << className << endl;
    int numFiles = clusters.size();
    data.resize(64);
    double b;
    double y;
    double tempTotal;
    for(int e = 0; e < 100; e++){ //100 epochs
        for (int i = 0; i < numFiles; i++){ //each image
            if (className == clusters[i].getClassNum()){
                d = 1;
            }
            else {
                d = -1;
            }
            //cout << "Perceptron " << className << " passed check with fileName: " << clusters.at(i).getClassNum() << endl;
            //cout << className << ":" << clusters.at(i).getClassNum() << " || "; 
            b = bias;
            tempTotal = 0;
            for(int n = 0; n < 64; n++){ //each node inside the histograms
                //calculate sum(0-63 of w[i] * h[i])
                tempTotal += data[n] * clusters[i].cNormAt(n);
            }
            y = b + tempTotal;
            for(int w = 0; w < 64; w++){ //each node inside the perceptron
                //calculate y, y = b + sum(0-63 of w[i] * h[i])
                data[w] = data[w] + (d - y)*clusters[i].cNormAt(w); 
            }
        
            //update bias, b = b + (d-y)
            //cout << "B:" << b << endl;
            bias = b + (d - y);
            
        }
    }
}

double Perceptron::test(int i){
    double b = bias;
    double tempTotal = 0;
    for(int n = 0; n < 64; n++){ //each node inside the histograms
        //calculate sum(0-63 of w[i] * h[i])
        tempTotal += data[n] * testingClusters[i].cNormAt(n);
    }
    
    return b + tempTotal;
}

int Perceptron::getClassName() const{
    return className;
}


void Perceptron::printout(){
    cout << "Perceptron #" << className << ": " << endl;
    for (int i = 0; i < 64; i++){
        cout << data[i] << " ";
    }
    cout << endl << "Bias: " << bias << endl;
    
}

