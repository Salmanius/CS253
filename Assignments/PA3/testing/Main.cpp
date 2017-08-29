/*
 * Chris Cochran
 * September 2016
 * CS253
 * Programming Assignment #1
 */

#include "Histogram.h"



int main(int argc, char *argv[]) {
        //const string fileType = ".pgm";
    
        if (argc < 3) {
            cerr << "Not enough input files given "<< endl;
            return -1;
        } else if (argc > 3) {
            cerr << "Too man input files given" << endl;
            return -1;
        }
        /*
        size_t found;
        for (int k = 1; k < 3; k++) {
                string t = argv[k];
                found = t.find(fileType);
                if (found==std::string::npos) {
                        cerr << "File " << k << " not of filetype: " << fileType << endl;
                        return -1;
                }
        }
        */
        Histogram h;
        Histogram h2;
        int hState = h.histogrammer(argv[1]);
        int h2State = h2.histogrammer(argv[2]);
        if (hState != 0 || h2State != 0){
            return -1;
        }
        if (h.getX() != h2.getX() || h.getY() != h2.getY()){
                cerr << "Incompatible sizes. Cannot compare images." << endl;
                return -1;
        }
        
        h.normalizer();
        h2.normalizer();
        //cout << "\nNormalized 1:" << endl;
        //h.histogramWriter('n');
        //cout << "\nNormalized 2:" << endl;
        //h2.histogramWriter('n');
        
        
        vector<float> v1 = h.getNormalized();
        vector<float> v2 = h2.getNormalized();
        
        //first output
        //minima summing
        float minSum = 0.0f;
        for (int m = 0; m < 64; m++) {
            if (v1[m] <= v2[m]) {
                minSum += v1[m];
            }
            else{
                minSum += v2[m];
            }
        }
        cout << minSum << endl;
        /*int temp =0;
        for (int s = 0; s < 64; s++){
            // first pixel minus 2nd pixel, square result, add to sum
            temp = hV1[s] - hV2[s];
            squaredSum += pow(temp,2);
        }   */
        ifstream targetFile1(argv[1]);
        ifstream targetFile2(argv[2]);
        int temp = 0;
        long squaredSum = 0;
        string tempS;
        int tempI = 0;
        int fInt1 = 0;
        int fInt2 = 0;
        targetFile1 >> tempS;
        targetFile2 >> tempS;
        targetFile1 >> tempI;
        targetFile1 >> tempI;
        targetFile1 >> tempI;
        targetFile2 >> tempI;
        targetFile2 >> tempI;
        targetFile2 >> tempI;
        
        while (true){
            if (targetFile1.eof()){
                    break;
            }
            targetFile1 >> fInt1;
            //cout << "File1:" << fInt1 << endl;
            targetFile2 >> fInt2;
            if (targetFile1.eof()){
                    break;
            }
            //cout << "File2:" << fInt2 << endl;
            temp = fInt1 - fInt2;
            squaredSum += pow(temp,2);
        }
        
        cout << squaredSum << endl;
        return 0;
}
