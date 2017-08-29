#include "Perceptron.h"

Perceptron::Perceptron(int cn, const vector<Cluster>& vClusters, const vector<Cluster>& tClusters): className(cn), clusters(vClusters), testingClusters(tClusters){
    setup();
    train();
};

void Perceptron::setup(){
    data.resize(64);
    d = 1;
    bias = 0;
}

int Perceptron::getClassName() const{
    return className;
}



void Perceptron::train(){
    //cout << "Perceptron " << className << endl;
    int numFiles = clusters.size();
    double b;
    double y;
    double tempTotal;
    for(int e = 0; e < 100; e++){ //100 epochs
        for (int i = 0; i < numFiles; i++){ //each image
            if (className == clusters.at(i).getClassNum()){
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
                tempTotal += data.at(n) * clusters.at(i).cNormAt(n);
            }
            y = b + tempTotal;
            for(int w = 0; w < 64; w++){ //each node inside the perceptron
                //calculate y, y = b + sum(0-63 of w[i] * h[i])
                data.at(w) = data.at(w) + (d - y)*clusters.at(i).cNormAt(w); 
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
        tempTotal += data.at(n) * testingClusters.at(i).cNormAt(n);
    }
    
    return b + tempTotal;
}

void Perceptron::printout(){
    cout << "Perceptron #" << className << ": " << endl;
    for (int i = 0; i < 64; i++){
        cout << data.at(i) << " ";
    }
    cout << endl << "Bias: " << bias << endl;
    
}

