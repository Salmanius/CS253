#include "Reader.h"

//Reader::Reader(string files): inputFile(files), numFiles(0){};

int Reader::fileLister()
{
    ifstream targetFile(inputFile);
    fileList.reserve(100);
    string tempName = "";
    targetFile >> tempName;
    if (!targetFile.fail()){
        if (targetFile.fail()){
            cerr << "File is empty or incorrectly formatted." << endl;
            targetFile.close();
            return -1;
        }
        while (true){
            if (targetFile.eof()){
               //cout << "EOF check HIT" << endl;
               break; 
            }
            if (targetFile.fail()){
                cerr << "Bad input" << endl;
                targetFile.close();
                return -1;     
            }
            
            fileList.push_back(tempName);
            numFiles++;
            targetFile >> tempName;
        }
        targetFile.close();
        if (numFiles < 2) {
            cerr << "Not enough files given in input file." << endl;
            return -1;
        }
        return 0;
    }
    else {//error file could not be openned
       cerr << "File could not be opened." << endl;
       return -1; 
    }
    return 0;
}

void Reader::imagePopulate(){
    images.reserve(numFiles);
    for (int i = 0; i < numFiles; i++){
        images.push_back(Image(fileList[i]));
    }
}

int Reader::readList(){
    for (int i = 0; i < numFiles; i++){
        if (images[i].read() != 0){
            return -1;
        }
    }
    return 0;
}


void Reader::printout(){
    cout << "Numfiles = " << numFiles << endl;
    int size = fileList.size();
    for (int i = 0; i < size; i++){
            cout << fileList[i] << endl;
    }
}

//you compute the pairwise minimum and then take the sum of the minima. Note that this will still produce a value between 0 and 1

void Reader::compare(){
    double minSum = 0.0f;
    for (int i = 0; i < (numFiles-1); i++){
        for (int j = i+1; j < numFiles; j++){
            minSum = 0.0f;
            for (int k = 0; k < 64; k++) {
                //finding minsum of the pair
                if (images[i].normAt(k) <= images[j].normAt(k)) {
                    minSum += images[i].normAt(k);
                }
                else{
                    minSum += images[j].normAt(k);
                }
                //cout << "minSum for file " << i << " and file " << j << " at index " << k << " is " << minSum << endl;
                //now to either throw it out or store it
                if (images[i].getClosestPairWiseSum() < minSum){
                    images[i].setClosestPairWiseSum(minSum);
                    images[i].setClosestPair(images[j].getFileName());
                }
                if (images[j].getClosestPairWiseSum() < minSum){
                    images[j].setClosestPairWiseSum(minSum);
                    images[j].setClosestPair(images[i].getFileName());
                }
                
            }
        }
        
    }
}

void Reader::printPairs(){
    for (int i = 0; i < numFiles; i++){
        cout << images[i].getFileName() << " " 
             << images[i].getClosestPair() << " "
             << images[i].getClosestPairWiseSum() << endl;
    }
}
