#include "Reader.h"


Reader::Reader(string files, int k): inputFile(files), numFiles(0), K(k){};

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

int Reader::kCheck(){
    if (K < 1) {
        cerr << "K must be greater than 0." << endl;
        return -1;
    }
    if (numFiles < K) {
        cerr << "K cannot be greater than number of files." << endl;
        return -1;
    }
    return 0;
}


void Reader::imagePopulate(){
    vCluster.reserve(numFiles);
    for (int i = 0; i < numFiles; i++){
        vCluster.push_back(Cluster(fileList[i]));
    }
}


void Reader::printout(){
    for (unsigned int i = 0; i < vCluster.size(); i++){ //loops through clusters
        for (int j = 0; j < vCluster[i].getNumImages(); j++){ //loops through images in each cluster
            cout << vCluster[i].imageAt(j).getFileName() + " ";
        }
        cout << endl;
    }
    
}

void Reader::compare(){
    int n = numFiles;
    int to = 0;
    int from = 0;
    double maxCompare = 0.0f;
    double minSum = 0.0f;
    while(n > K) {
        maxCompare = 0.0f;
        minSum = 0.0f;
        for (int i = 0; i < (n-1); i++){
            for (int j = i+1; j < n; j++){
                minSum = 0.0f;
                for (int k = 0; k < 64; k++) {//finding the minsum
                    if (vCluster[i].cNormAt(k) <= vCluster[j].cNormAt(k)){
                        minSum += vCluster[i].cNormAt(k);
                    }
                    else{
                        minSum += vCluster[j].cNormAt(k);
                    }
                }//checking to see if it found a higher minsum
                if (maxCompare < minSum){
                    maxCompare = minSum;
                    from = i; //saving which cluster to xfer the image to
                    to = j; //saving which cluster to remove the image from
                }
            }
        
        }
        //cout << "To: " << to << endl << "From: " << from << endl;
        n--;
        
        for (int c = 0; c < vCluster[from].getNumImages(); c++) {
            vCluster[to].addImage(vCluster[from].imageAt(c));
        }
        vCluster.erase(vCluster.begin()+from);
    
        for (int x = 0; x < numFiles; x++){
            vCluster[x].makeAverage();
        }
    }
    
    
}

int Reader::flagCheck(){
    for (unsigned int i = 0; i < vCluster.size(); i++){
        if (vCluster[i].getFlag() != 0){
            return -1;
        }
    }
    return 0;
}
