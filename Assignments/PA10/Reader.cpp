#include "Reader.h"


Reader::Reader(string trfiles, string tefiles, int k): trainingFiles(trfiles), testingFiles(tefiles), numFiles(0), testingNumFiles(0), K(k){};

int Reader::fileLister(){
    ifstream is(testingFiles, ifstream::binary);
    istringstream targetBuffer;
    testingFilesList.reserve(1000);
    string temp = "";
    if (is) {
        // get length of file:
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);

        char * buffer = new char [length];
        // read data as a block:
        is.read (buffer,length);

        if (!is){
            cerr << "files not read properly." << endl;
        }
        is.close();
        targetBuffer.str(buffer);
        targetBuffer >> temp;
        while (targetBuffer){
            fileList.push_back(temp);
            numFiles++;
            targetBuffer >> temp;
            
            int tempClassName = extractClass(temp);
            if (!foundClasses.empty()){ //if there is some other item in found Classes we need to check and make sure we cant double pushing the same class
                if (!(find(foundClasses.begin(), foundClasses.end(), tempClassName) != foundClasses.end())){ // did not find className so push
                    foundClasses.push_back(tempClassName);
                }
            }
            else{//if found classes is empty then of course no dupes will be pushed
                foundClasses.push_back(tempClassName);
            }//now we will know how many perceptrons to make
            
        }
        if (numFiles < 2) {
            cerr << "Not enough files given in input file." << endl;
            return -1;
        }
        delete[] buffer;
    }
    
    return 0;
}

int Reader::testFileLister(){
    //ifstream targetBuffer(testingFiles);
    ifstream is(testingFiles, ifstream::binary);
    istringstream targetBuffer;
    testingFilesList.reserve(1000);
    string temp = "";
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
        targetBuffer >> temp;
        while (targetBuffer){
            testingFilesList.push_back(temp);
            testingNumFiles++;
            targetBuffer >> temp;
        }
        if (testingNumFiles < 2) {
            cerr << "Not enough files given in input file." << endl;
            return -1;
        }
        delete[] buffer;
    }
    return 0;
}

int Reader::perceptronStart(){
    int numPerceptrons = foundClasses.size();
    if (numPerceptrons < 2){
        return -1;
    }
    for(int i = 0; i < numPerceptrons; i++){
        //cout << "Pushing class name: " << i << endl; 
        perceptronList.push_back(Perceptron(i+1, vCluster, testingCluster));
    }
    return 0;
}


    
int Reader::kCheck(){
    if (K < 1) {
        cerr << "K must be greater than 0." << endl;
        return -1;
    }
    if (testingNumFiles < K) {
        cerr << "K cannot be greater than number of files." << endl;
        return -1;
    }
    return 0;
}


void Reader::imagePopulate(){
    vCluster.reserve(numFiles);
    testingCluster.reserve(testingNumFiles);
    for (int i = 0; i < numFiles; i++){
        vCluster.push_back(Cluster(fileList[i]));
    }
    for (int j = 0; j < testingNumFiles; j++){
        testingCluster.push_back(Cluster(testingFilesList[j]));
    }
}



void Reader::compare(){
    double e = 0.01; // use to get all in own class groups
    int n = testingNumFiles;
    int numP = perceptronList.size();
    int to = 0;
    int from = 0;
    double maxCompare = 0;
    double sum = 0;
    while(n > K) {
        maxCompare = 0;
        for (int i = 0; i < (n-1); i++){
            for (int j = i+1; j < n; j++){
                sum = 0.0;
                for (int p = 0; p < numP; p++){
                    //cout << "Perceptron " << p << ": testing images " << i << " and " << j << endl;
                    double yI = perceptronList[p].test(i);
                    double yJ = perceptronList[p].test(j);
                    //cout << "yI:" << yI << " yJ:" << yJ << "||";
                    double diff = yI - yJ;
                    //cout << diff << "||";
                    double squaredDiff = pow(diff,2);
                    sum += (1/(squaredDiff + e));
                    //cout << sum << " || ";
                }//checking to see if it found a higher compareSum
                //cout << sum << endl;
                if (maxCompare < sum){
                    maxCompare = sum;
                    from = j; //saving which cluster to xfer the image to
                    to = i; //saving which cluster to remove the image from
                }
            }
        
        }
        //cout << "To: " << to << endl << "From: " << from << endl;
        n--;
        int numFrom = testingCluster[from].getNumImages();
        for (int c = 0; c < numFrom; c++) {
            //cout << "To className:" << testingCluster[to].getClassName() << endl;
            //cout << "From className: " << testingCluster[from].getClassName() << endl;
            testingCluster[to].addImage(testingCluster[from].imageAt(c));
        }
        
        testingCluster.erase(testingCluster.begin()+from);
        int tsize = testingCluster.size();
        for (int t = 0; t < tsize; t++){//NEED ONLY ONLYs RECALCULATE ONES THAT CHANGED
            testingCluster[t].makeAverage();
        }
        
    }
    
}


void Reader::perceptronPrint(){
    int pNum = perceptronList.size();
    for (int i = 0; i < pNum; i++){
        perceptronList[i].printout();
    }
}



int Reader::extractClass(string fname){
    string temp;
    temp = fname.substr(5,1);
    return (stoi(temp));
}


int Reader::flagCheck(){
    for (unsigned int i = 0; i < vCluster.size(); i++){
        if (vCluster[i].getFlag() != 0){
            return -1;
        }
    }
    for (unsigned int i = 0; i < testingCluster.size(); i++){
        if (testingCluster[i].getFlag() != 0){
            return -1;
        }
    }
    return 0;
}

void Reader::printout(){
    for (unsigned int i = 0; i < testingCluster.size(); i++){ //loops through clusters
        for (int j = 0; j < testingCluster[i].getNumImages(); j++){ //loops through images in each cluster
            cout << testingCluster[i].imageAt(j).getFileName() + " ";
        }
        cout << endl << endl;
    }
}

