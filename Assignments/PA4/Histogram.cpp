#include "Histogram.h"

int Histogram::histogrammer(std::string s)
{
    
}
void Histogram::normalizer() {
      normalizedV.resize(64);
      for (int i = 0; i < 64; i++) {
            normalizedV[i] = histogramV[i]/(float)totalInts;
      }
}


vector<float> Histogram::getNormalized() const {
    return normalizedV;
}

vector<int> Histogram::getHistogram() const{
    return histogramV;
}

int Histogram::getX() const {
        return x;
}

int Histogram::getY() const {
        return y;  
}

void Histogram::histogramWriter(char c){
    if (c == 'h') {
        for (int i = 0;i < 64;i++){
                cout << histogramV[i] << " ";
        }
    }
    else if (c == 'n') {
        for (int i = 0;i < 64;i++){
                cout << normalizedV[i] << " ";
        }
    }
}
