#include "Image.h"

Image::Image(string s): fileName(s), totalInts(0){};

int Image::readNew(){ //SLOWER THAN OLD
    ifstream is(fileName);
    istringstream targetBuffer;
    histogram.resize(64);  
    string rawInput;
    int rawI;
    int rangedVal;
    totalInts = 0;
    //const int imageMaxValue = 255;
    setClassName();
    if (is) {
        // get length of file:
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);

        char * buffer = new char [length];
        // read data as a block:
        is.read (buffer,length);

        if (!is){
            cerr << "error: only " << is.gcount() << " could be read";
        }
        is.close();
        targetBuffer.str(buffer);
        targetBuffer >> rawInput; //getting rid of P2
        targetBuffer >> rawInput; //getting rid of x
        targetBuffer >> rawInput; //getting rid of y
        targetBuffer >> rawInput; //getting rid of maxVal
        targetBuffer >> rawInput; //getting next for actual use
        for(int i = 0; i < 16348; i++){
            //cout << rawInput << endl;
            rawI = stoi(rawInput);
            totalInts++;
            rangedVal = floor(rawI/4);
            histogram[rangedVal]++;
            targetBuffer >> rawInput;
        }
        /*
        while(targetBuffer){ //Slightly slower than above
            try{
                rawI = stoi(rawInput);
            }
            catch (std::exception const & e){
                break;
            }
            totalInts++;
            rangedVal = floor(rawI/4);
            histogram[rangedVal]++;
            targetBuffer >> rawInput;
        }
         * */
        singleNormalize();
        delete[] buffer;
        
    }
    else {//error file could not be openned
       cerr << "File could not be opened." << endl;
       return -1; 
    }
    
    return 0;
}


int Image::readOld(){ //amazingly faster than new. I am thinking it is STOI
    ifstream targetFile(fileName);
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
                singleNormalize();
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



void Image::histogramPrint(int i){
    for (int i = 0;i < 64;i++){
        cout << histogram[i] << " ";
    }
    cout << endl << endl;
}

string Image::getFileName() const {
    return fileName;
}

double Image::normAt(int i) const{
    return normalized[i];
}

void Image::setClassName() {
    string cN = fileName.substr(5,1);
    className = stoi(cN);   
}

int Image::getClassName() const{
    return className;
}


