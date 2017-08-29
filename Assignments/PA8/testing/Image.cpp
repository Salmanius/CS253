#include "Image.h"

Image::Image(string s, int arg): fileName(s), readArg(arg), totalInts(0){};

int Image::read(){
    ifstream targetFile(fileName);
    rawVals.reserve(10000);
    histogram.resize(64);  
    int rawInput;
    int rangedVal;
    totalInts = 0;
    const int imageMaxValue = 255;
    setClassName();
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
        if (x != 128 || y != 128){
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
                //cout << "EOF check HIT" << "rawinput=" << rawInput << " totalInts= " << totalInts << endl;		
                if (x*y == 1 && (rawInput > 0 && rawInput < 256)){
                    totalInts++;
                } 
                if (totalInts != (x*y)){
                    cerr << "Pixel count does not equal x*y" << endl;
                    targetFile.close();
                    return -8;
                }
                switch(readArg) {
                    case 1: 
                        singleNormalize();
                        //histogramPrint(1);
                        break;
                    case 2:
                        zeroOutFour();
                        fourHistoLoad();
                        fourNormalize();
                        //histogramPrint(4);
                        break;
                    case 3: //case 3 has no use here as it is a comparison method on the raw data.
                        break;
                    case 4: 
                        zeroOutNine();
                        nineHistoLoad();
                        nineNormalize();
                        break;
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

void Image::singleNormalize(){
    //cout << "singleNormalize" << endl;
    normalized.resize(64);
    for (int i = 0; i < 64; i++) {
        normalized[i] = histogram[i]/(float)totalInts;
    }    
}

void Image::fourHistoLoad(){
    //cout << "fourNormalize" << endl;
    int x = 0;
    int y = 0;
    int rangedVal;
    //cout << "X:" << x << " Y:" << y << endl;
    for (int i = 0; i < 128*128; i++) {
        
        rangedVal = floor(rawVals[i]/4);
        //cout << "X:" << x << " Y:" << y;
        if ((x >= 0 && x < 64) && (y >= 0 && y < 64)){ //quadrant 1
            histoFour[0][rangedVal]++;
        }
        else if ((x >= 64 && x <= 127) && (y >= 0 && y <= 63)){ //quadrant 2
            histoFour[1][rangedVal]++;
        }
        else if ((x >= 0 && x <= 63) && (y >= 64 && y <= 127)){ //quadrant 3
            histoFour[2][rangedVal]++;
        }
        else if ((x >= 64 && x <= 127) && (y >= 64 && y <= 127)){ //quadrant 4
            histoFour[3][rangedVal]++;
        }
        x++;
        if (x == 128){
            x = 0;
            y++;
        }
        
    }
}




void Image::fourNormalize(){
    for (int h = 0; h < 4; h++){
        for (int i = 0; i < 64; i++){
            normHistoFour[h][i] = histoFour[h][i]/((float)totalInts/4);
        }
    }
}



void Image::nineHistoLoad(){
    //cout << "nineNormalize" << endl;
    int x = 0;
    int y = 0;
    int rangedVal;
    //cout << "X:" << x << " Y:" << y << endl;
    for (int i = 0; i < 128*128; i++) {
        
        rangedVal = floor(rawVals[i]/4);
        //cout << "X:" << x << " Y:" << y;
        if ((x >= 0 && x <= 42) && (y >= 0 && y <= 42)){ //quadrant 1
            histoNine[0][rangedVal]++;
        }
        else if ((x >= 43 && x <= 85) && (y >= 0 && y <= 42)){ //quadrant 2
            histoNine[1][rangedVal]++;
        }
        else if ((x >= 86 && x <= 127) && (y >= 0 && y <= 42)){ //quadrant 3
            histoNine[2][rangedVal]++;
        }
        else if ((x >= 0 && x <= 42) && (y >= 43 && y <= 85)){ //quadrant 4
            histoNine[3][rangedVal]++;
        }
        else if ((x >= 43 && x <= 85) && (y >= 43 && y <= 85)){ //quadrant 5
            histoNine[4][rangedVal]++;
        }
        else if ((x >= 86 && x <= 127) && (y >= 43 && y <= 85)){ //quadrant 6
            histoNine[5][rangedVal]++;
        }
        else if ((x >= 0 && x <= 42) && (y >= 86 && y <= 127)){ //quadrant 7
            histoNine[6][rangedVal]++;
        }
        else if ((x >= 43 && x <= 85) && (y >= 86 && y <= 127)){ //quadrant 8
            histoNine[7][rangedVal]++;
        }
        else if ((x >= 86 && x <= 127) && (y >= 86 && y <= 127)){ //quadrant 9
            histoNine[8][rangedVal]++;
        }
        
        x++;
        if (x == 128){
            x = 0;
            y++;
        }
        
    }
}




void Image::nineNormalize(){
    for (int h = 0; h < 9; h++){
        for (int i = 0; i < 64; i++){
            normHistoNine[h][i] = histoNine[h][i]/((float)totalInts/9);
        }
    }
}




void Image::histogramPrint(int i){ //not updated for 9 histo
    switch (i) {
        case 1:
            for (int i = 0;i < 64;i++){
                cout << histogram[i] << " ";
            }
            break;
        case 2:
            for (int i = 0;i < 64;i++){
                cout << normalized[i] << " ";
            }
            break;
        case 3:
            for (int h = 0; h < 4; h++) {
                cout << "Quadrant " << h+1 << endl;
                for (int i = 0;i < 64;i++){
                    cout << histoFour[h][i] << " ";
                }
                cout << endl;
            }
            break;
        case 4:
            for (int h = 0; h < 4; h++) {
                cout << "Quadrant " << h+1 << endl;
                for (int i = 0;i < 64;i++){
                    cout << normHistoFour[h][i] << " ";
                }
            }
            break;
    }
    cout << endl << endl;
}

string Image::getFileName() const {
    return fileName;
}

double Image::normAt(int i) const{
    return normalized[i];
}

int Image::rawAt(int i) const{
    return rawVals[i];
}

void Image::setClassName() {
    string cN = fileName.substr(5,1);
    className = stoi(cN);   
    
}

int Image::getClassName() const{
    return className;
}

void Image::zeroOutFour(){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 64; j++){
            histoFour[i][j] = 0;
            normHistoFour[i][j] = 0;
        }
    }
}

void Image::zeroOutNine(){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 64; j++){
            histoNine[i][j] = 0;
            normHistoNine[i][j] = 0;
        }
    }
}
