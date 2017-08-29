#include "Cluster.h"

Cluster::Cluster(string s, int arg): fileName(s), arg3(arg), numImages(0){
    build();
    flag = read();
    if (flag == 0) {
        hStart();
    }
}

void Cluster::build(){
    images.push_back(Image(fileName, arg3));
    numImages++;
}

void Cluster::hStart(){
    switch (arg3) {
        case 1: //making normHistoAverage equal to the first item.
            //cout << "hStart() running arg:" << arg3 << endl;
            normHistoAverage.resize(64);
            for (int i = 0; i < 64; i++){
                normHistoAverage[i] = images[0].normAt(i);
            }
            break;
        case 2: {//need to set all the averages
            //cout << "hStart() running arg:" << arg3 << endl;
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 64; j++){
                    clusterNorm4Average[i][j] = images[0].normHistoFour[i][j];
                }
            }
            break;
        }
        case 3: //pixel 1 of image 1 plus pixel one of image 2 then divide both by # of images
            //cout << "hStart() running arg:" << arg3 << endl;
            rawAverage.resize(128*128);
            for (int j = 0; j < 128*128; j++){
                rawAverage[j] = images[0].rawAt(j);
            }
            break;
    }
}


void Cluster::makeAverage(){
    //Need to account for other types of comparing
    switch (arg3) {
        case 1: {//Averaging the norm Histograms together
            //cout << "makeAverage() running arg:" << arg3 << endl;
            double sum = 0.0f;
            int size = images.size();
            if (size > 1){
                for (int i = 0; i < 64; i++) {
                    sum = 0.0f;
                    for (int j = 0; j < size; j++) {
                        sum += images[j].normAt(i);
                    }
                    sum = sum/size;
                    normHistoAverage[i] = sum;
                }
            }
            break;
        }
        case 2: {//averaging the 4 histograms 
            //cout << "makeAverage() running arg:" << arg3 << endl;
            double sum = 0.0f;
            int size = images.size();
            if (size > 1){
                 for (int h = 0; h < 4; h++){ 
                    for (int i = 0; i < 64; i++) {
                        sum = 0.0f;
                        for (int j = 0; j < size; j++) {
                            sum += images[j].normHistoFour[h][i];
                        }
                        sum = sum/size;
                        clusterNorm4Average[h][i] = sum;
                    }
                 }
            }
            
            break;
        }
        case 3: {//averaging the raw data together.
            //cout << "makeAverage() running arg:" << arg3 << endl;
            double sum = 0.0f;
            int size = images.size();
            if (size > 1){
                for (int i = 0; i < (128*128); i++){
                    sum = 0.0f;
                    for (int j = 0; j < size; j++){
                        sum += images[j].rawAt(i);
                    }
                    sum = sum/size;
                    rawAverage[i] = sum;
                }
            }
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
