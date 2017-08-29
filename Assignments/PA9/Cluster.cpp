#include "Cluster.h"

Cluster::Cluster(string s): fileName(s), numImages(0){
    build();
    flag = read();
    if (flag == 0) {
        hStart();
    }
}

void Cluster::build(){
    images.push_back(Image(fileName));
    numImages++;
}

void Cluster::hStart(){
    normHistoAverage.resize(64);
    for (int i = 0; i < 64; i++){
        normHistoAverage[i] = images[0].normAt(i);
    }
}


void Cluster::makeAverage(){
    double sum = 0.0f;
    int size = images.size();
    if (size > 1){
        for (int i = 0; i < 64; i++) {
            sum = 0.0f;
            for (int j = 0; j < size; j++) {
                sum += images.at(j).normAt(i);
            }
            sum = sum/size;
            normHistoAverage[i] = sum;
        }
    }
    
}


Image Cluster::imageAt(int i) {
    return images[i];
}

int Cluster::getNumImages() const{
    return numImages;
}

int Cluster::read(){
    if (images[0].read() != 0){
        return -1;
    }
    return 0;
}

void Cluster::resetNumImages(){
    numImages = 0;
}

double Cluster::cNormAt(int i) const{
    return normHistoAverage[i];
}

double Cluster::cRawAt(int i) const{
    return rawAverage[i];
}

void Cluster::addImage(Image im){
    images.push_back(im);
    numImages++;
}

int Cluster::getFlag(){
    return flag;
}

int Cluster::getClassNum() const{
    string temp;
    temp = fileName.substr(5,1);
    return (stoi(temp));
}

string Cluster::getClassName() const{
    return fileName;
}
