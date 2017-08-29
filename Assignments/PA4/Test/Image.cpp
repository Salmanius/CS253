#include "Image.h"

int Image::read(){
    ifstream targetFile(fileName);
    rawVals.reserve(10000);
    histogram.resize(64);  
    int rawInput;
    int rangedVal;
    totalInts = 0;
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
        if (x < 1 || y < 1){
            cerr << "Incorrect dimensions" << endl;
            return -6;
        }
        targetFile >> rawInput ;
        if (targetFile.fail()){
            cerr << "File is incorrectly formatted with respect to dimensions" << endl;
            targetFile.close();
            return -6;
        }
        if (rawInput != imageMaxValue) {
            cerr << "Image max value is incorrect. Should be " << imageMaxValue << endl;
            targetFile.close();
            return -7;
        }
        targetFile >> rawInput;
        while (true){
            //cout << rawInput << endl;
            if (targetFile.eof()){
               //cout << "EOF check HIT" << endl;
                if (totalInts != (x*y)){
                        cerr << "Pixel count does not equal x*y" << endl;
                        targetFile.close();
                        return -8;
                }
                normalized.resize(64);
                for (int i = 0; i < 64; i++) {
                    normalized[i] = histogram[i]/(float)totalInts;
                }
                targetFile.close();
                return 0; 
            }
            if (targetFile.fail()){
                cerr << "Bad input (not an integer)" << endl;
                targetFile.close();
                return -2;     
            }
                
            if ((rawInput > 255) || (rawInput < 0)){
                cerr << "Bad input (not in range): " << rawInput << endl;
                targetFile.close();
                return -3;
            }
            //calculations if it passes all the correct input tests
            totalInts++;
            rawVals.push_back(rawInput);
            rangedVal = floor(rawInput/4);
            histogram[rangedVal]++;
            targetFile >> rawInput;
        }
        //finished loading into the histogram. Normalizing to seperate vector
        targetFile.close();
        
    }
    else {//error file could not be openned
       cerr << "File could not be opened." << endl;
       return -1; 
    }
    
    return 0;
}


void Image::histogramWriter(char c){
    if (c == 'h') {
        for (int i = 0;i < 64;i++){
                cout << histogram[i] << " ";
        }
    }
    else if (c == 'n') {
        for (int i = 0;i < 64;i++){
                cout << normalized[i] << " ";
        }
    }
}

string Image::getFileName() const {
    return fileName;
}

double Image::normAt(int i) const{
    return normalized[i];
}

void Image::setClosestPair(string s){
    closestPair = s;
}

void Image::setClosestPairWiseSum(double d){
    closestPairWiseSum = d;
}

string Image::getClosestPair() const {
    return closestPair;
}

double Image::getClosestPairWiseSum() const {
    return closestPairWiseSum;
}
