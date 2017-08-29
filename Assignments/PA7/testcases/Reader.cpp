#include "Reader.h"


Reader::Reader(string files, int k, int arg): inputFile(files), numFiles(0), K(k), compareArg(arg){};

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
        vCluster.push_back(Cluster(fileList[i], compareArg));
    }
}


void Reader::printout(int i){
    switch (i) {
        case 0: {
            for (unsigned int i = 0; i < vCluster.size(); i++){ //loops through clusters
                for (int j = 0; j < vCluster[i].getNumImages(); j++){ //loops through images in each cluster
                    cout << vCluster[i].imageAt(j).getFileName() + " ";
                }
                cout << endl;
            }
            break;
        }
        case 1:
            cout << compareQualitySum << endl;
            break;
    }
}

void Reader::compare(){
    switch (compareArg){
        case 1:
            minSumCompare();
            break;
        case 2:
            fourCompare();
            break;
        case 3:
            invSquareDiffCompare();
            break;
        case 4:
            nineCompare();
            break;
    }
    compareQuality();
    
}

void Reader::minSumCompare(){
    //cout << "Min sum Compare" << endl;
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
        //cout << "similarity measure: " << maxCompare << endl;
        for (int c = 0; c < vCluster[from].getNumImages(); c++) {
            vCluster[to].addImage(vCluster[from].imageAt(c));
        }
        vCluster.erase(vCluster.begin()+from);
    
        for (int x = 0; x < numFiles; x++){
            vCluster[x].makeAverage();
        }
    }
}

void Reader::fourCompare(){
    int n = numFiles;
    int to = 0;
    int from = 0;
    double maxCompare = 0.0f;
    double minSum = 0.0f;
    while(n > K) {
        maxCompare = 0.0f;
        minSum = 0.0f;
        for (int i = 0; i < (n-1); i++){ //comparing i to j clusters
            for (int j = i+1; j < n; j++){
                minSum = 0;
                //cout << "inside j" << endl;
                for (int h = 0; h < 4; h++){
                    //cout << "inside h" << endl;
                    for (int k = 0; k < 64; k++) {//finding the minsum by going through the histogram
                        //cout << "inside k" << endl;
                        if (vCluster[i].clusterNorm4Average[h][k] < vCluster[j].clusterNorm4Average[h][k]){
                            minSum += vCluster[i].clusterNorm4Average[h][k];
                        }
                        else{
                            minSum += vCluster[j].clusterNorm4Average[h][k];
                        }
                    }
                }
                minSum = minSum/4;
                if (maxCompare < minSum){//checking to see if it found a higher minsum
                    maxCompare = minSum;
                    from = i; //saving which cluster to xfer the image to
                    to = j; //saving which cluster to remove the image from
                }
                
            }
        
        }
        //cout << "To: " << to << endl << "From: " << from << endl;
        n--;
        //cout << "similarity measure: " << maxCompare << endl;
        for (int c = 0; c < vCluster[from].getNumImages(); c++) {
            vCluster[to].addImage(vCluster[from].imageAt(c));
        }
        vCluster.erase(vCluster.begin()+from);
    
        for (int x = 0; x < numFiles; x++){
            vCluster[x].makeAverage();
        }
    }

}

void Reader::invSquareDiffCompare(){
    //cout << "invSquareDiffCompare()" << endl;
    // HIGHER THE NUM THE BETTER
    int n = numFiles;
    int to = 0;
    int from = 0;
    double maxCompare = 0.0f;
    double squaredSum = 0.0f;
    double diff = 0.0f;
    double invSquareDiff = 0.0f;
    while(n > K) {
        maxCompare = 0.0f;
        squaredSum = 0.0f;
        for (int i = 0; i < (n-1); i++){ //Part of the comparing without any repeats.
            for (int j = i+1; j < n; j++){
                squaredSum = 0.0f;
                for (int k = 0; k < (128*128); k++) {//finding the squared sum
                    diff = vCluster[i].cRawAt(k) - vCluster[j].cRawAt(k);
                    squaredSum += pow(diff,2);
                }//checking to see if it found a higher invSquareDiff
                invSquareDiff = 1/(squaredSum + 1);
                if (maxCompare < invSquareDiff){
                    maxCompare = invSquareDiff;
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


void Reader::nineCompare(){
    int n = numFiles;
    int to = 0;
    int from = 0;
    double maxCompare = 0.0f;
    double minSum = 0.0f;
    while(n > K) {
        maxCompare = 0.0f;
        minSum = 0.0f;
        for (int i = 0; i < (n-1); i++){ //comparing i to j clusters
            for (int j = i+1; j < n; j++){
                minSum = 0;
                //cout << "inside j" << endl;
                for (int h = 0; h < 9; h++){
                    //cout << "inside h" << endl;
                    for (int k = 0; k < 64; k++) {//finding the minsum by going through the histogram
                        //cout << "inside k" << endl;
                        if (vCluster[i].clusterNorm9Average[h][k] < vCluster[j].clusterNorm9Average[h][k]){
                            minSum += vCluster[i].clusterNorm9Average[h][k];
                        }
                        else{
                            minSum += vCluster[j].clusterNorm9Average[h][k];
                        }
                    }
                }
                minSum = minSum/4;
                if (maxCompare < minSum){//checking to see if it found a higher minsum
                    maxCompare = minSum;
                    from = i; //saving which cluster to xfer the image to
                    to = j; //saving which cluster to remove the image from
                }
                
            }
        
        }
        //cout << "To: " << to << endl << "From: " << from << endl;
        n--;
        //cout << "similarity measure: " << maxCompare << endl;
        for (int c = 0; c < vCluster[from].getNumImages(); c++) {
            vCluster[to].addImage(vCluster[from].imageAt(c));
        }
        vCluster.erase(vCluster.begin()+from);
    
        for (int x = 0; x < numFiles; x++){
            vCluster[x].makeAverage();
        }
    }
}

void Reader::compareQuality(){
    int numClusters = vCluster.size();
    compareQualitySum = 0.0;
    int totalMaxCount = 0;
    int totalCount = 0;
    for (int i = 0; i < numClusters; i++) {
        //cout << "i= " << i << " vCluster[i].findMax()=" << vCluster[i].findMax() << endl;
        totalMaxCount += vCluster[i].findMax();
        totalCount += vCluster[i].getNumImages();
    }
    //cout << "totalMaxCount: " << totalMaxCount << endl;
    //cout << "totalCount: " << totalCount << endl;
    compareQualitySum = (double) totalMaxCount / (double) totalCount;
}

int Reader::flagCheck(){
    for (unsigned int i = 0; i < vCluster.size(); i++){
        if (vCluster[i].getFlag() != 0){
            return -1;
        }
    }
    return 0;
}
