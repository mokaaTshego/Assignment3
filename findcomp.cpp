#include "PGMImageProcessor.h"
using namespace std;
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <set>
#include <bits/stdc++.h>
//("sloan_image.pgm");
int main(int argc, char const *argv[]){

    MKXTSH013 :: PGMImageProcessor pgmImageProcessor;
    int min = 3;
    int max;
    int threshold =128;
    string input;
    string output;
    string outputColor;
    bool print = false;
    bool write = false;
    bool writeColor = false;
    bool filter = false;
    //bool extract = false;
    string flag;
    int a = 1;

    while(a < argc-1){
        flag = argv[a];
        if(flag == "-w"){
             write = true;
             output = argv[++a];
             ++a;
        }
        else if (flag == "-c"){
             writeColor = true;
             outputColor = argv[++a];
             ++a;
        }
        else if(flag == "-s") {
            filter= true;
            min = std::stoi(argv[++a]);
            cout<<"Minimum value :"<< min <<endl;
            max = std::stoi(argv[++a]);
            cout<<"Maximum value :"<< max <<endl;
            ++a;
        }
        else if(flag =="-t"){
            threshold = std::stoi(argv[++a]);
            cout<<"Threshold :"<< threshold <<endl;
            ++a;

        }
        else if(flag == "-p"){
            print = true;
            ++a;


        }
        else{

            cout<< "Wrong Input." << argv[a] << endl;
            break;


        }
    }

        input = argv[argc-1];
        bool suc = pgmImageProcessor.readFile(input);
        if (suc){ // file opened

            cout << "Reading image : " << input << std::endl;
            cout << "Extracted:     " <<pgmImageProcessor.extractComponents((unsigned char)threshold, min)<< endl; //extracted components
            if(write){//able to write file
                bool written = pgmImageProcessor.writeComponents(output);
                if (written){
                    cout << "File written:  true" << endl;
                }
                else{
                    cout << "File written:  false" << endl;
                }

            }
            if (writeColor){ //write components in colours
                bool written = pgmImageProcessor.ColouredComponents(outputColor);
                if (written){
                    cout << "Colour file written:  true" << endl;
                }
                else{
                    cout << "Colour file written:  false" << endl;
                }
            }
            if(filter){ //filter components by size
                cout << "Filtered:      " <<pgmImageProcessor.filterComponentsBySize(min,max)<< endl;}

        else{
        std::cout << "Unable to read image : " << input << std::endl;
        }
    return 0;
}
}