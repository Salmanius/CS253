#include "Histogram.h"

//return guide:
//0: all went well
//-1: file could not be openned
//-2: bad input
//-3: invalid range
//-4: empty file/bad format
//-5: bad header
//-6: bad dimensions
//-7: wrong max val
//-8 not enough pixels for x*y
int Histogram::histogrammer(std::string s)
{
    ifstream targetFile(s);
    histogramV.resize(64);
    int rawVal;    
    int rangedVal;
    totalInts = 0;
    x = 0;
    y = 0;
    const int imageMaxValue = 255;
    
    if (!targetFile.fail()){
        if (targetFile.fail()){
            cerr << "File is empty or incorrectly formatted." << endl;
            targetFile.close();
            return -4;
        }
        char c;
        targetFile.get(c);
        if (c != 'P') {
            cerr << "Header does not begin with P2." << endl;
            targetFile.close();
            return -5;
        } 
        targetFile.get(c);
        if (c != '2'){
            cerr << "Header does not begin with P2." << endl;
            targetFile.close();
            return -5;
        } 
        targetFile >> x;
        targetFile >> y;
        targetFile >> rawVal;
        if (targetFile.fail()){
            cerr << "File is incorrectly formatted with respect to dimensions" << endl;
            targetFile.close();
            return -6;
        }
        if (rawVal != imageMaxValue) {
            cerr << "Image max value is incorrect. Should be " << imageMaxValue << endl;
            targetFile.close();
            return -7;
        }
        targetFile >> rawVal;
        while (true){
            //cout << rawVal << endl;
            if (targetFile.eof()){
               //cout << "EOF check HIT" << endl;
                if (totalInts != (x*y)){
                        cerr << "Pixel count does not equal x*y" << endl;
                        targetFile.close();
                        return -8;
                }
                targetFile.close();
                return 0; 
            }
            if (targetFile.fail()){
                cerr << "Bad input (not an integer)" << endl;
                targetFile.close();
                return -2;     
            }
                
            if ((rawVal > 255) || (rawVal < 0)){
                cerr << "Bad input (not in range): " << rawVal << endl;
                targetFile.close();
                return -3;
            }
            //calculations if it passes all the correct input tests
            totalInts++;
            rangedVal = floor(rawVal/4);
            histogramV[rangedVal]++;
            targetFile >> rawVal;
        }
        targetFile.close();
    }
    else {//error file could not be openned
       cerr << "File could not be opened." << endl;
       return -1; 
    }
    
    return 0;
    
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
