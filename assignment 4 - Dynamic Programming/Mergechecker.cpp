//DANIEL KIM - FINAL VER

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <bitset>
using namespace std;

//static global array
int MergeArray[1000][1000];

string MergeChecker(const string& str1, const string& str2, string& merge) {
    int a = str1.length();
    int b = str2.length();
    int c = merge.length();

    // Length of merge should be equal to the sum of the lengths of str1 and str2
    if (a + b != c) {
        return "0";
    }

    // If both strings are empty, then the merge is empty
    if (a == 0 && b == 0) {
        return "";
    }



    // Bottom-up dynamic programming approach
    //Iterate as 2D array 
    //set as 1 if the merge string matches str1
    //set as 2 if the merge string matches str2
    for (int i = 0; i <= a; ++i) {
        for (int j = 0; j <= b; ++j) {

            if (i == 0 && j == 0) {
                MergeArray[i][j] = 1;
            }

             if (i > 0 && str1[i - 1] == merge[i + j - 1] && MergeArray[i - 1][j] >= 1) {
                MergeArray[i][j] = 1;
            }if (j > 0 && str2[j - 1] == merge[i + j - 1] && MergeArray[i][j - 1] >= 1) {
                MergeArray[i][j] = 2;
            }
        }
    }
    
//Verify if the merge string is a valid merge of str1 and str2 by checking the [a][b] position of the array 
//While I don't technically need c and d as independent variables, I wanted to keep them as such for safety
    if (MergeArray[a][b] >= 1) {
        int c = a;
        int d = b;
//backtrack from the end of the merge string to the beginning
        while (c > 0 && d >= 0) {
            if (MergeArray[c][d] == 1) {
                merge[c + d - 1] = toupper(merge[c + d - 1]);
                c--;
            } else{
                d--;
            }
        }
        return merge;
    } else {
        return "0";
    }
}


int main() {
    // Declare variables
    string infile, outfile, str1, str2, mergeLine;

    // Prompt user for input file, output file, and starting vertex
    cout << "Enter the name of the input file: ";
    cin >> infile;
    cout << "Enter the name of the output file: ";
    cin >> outfile;

    ifstream inputfile(infile);
    ofstream outputfile(outfile);

    if (!inputfile.is_open()) {
        cout << "ERROR: INPUT FILE COULD NOT BE OPENED" << endl;
        return 1;
    }

    while (getline(inputfile, str1) && getline(inputfile, str2) && getline(inputfile, mergeLine)) {
    memset(MergeArray, 0, sizeof(MergeArray));
    
    string output = MergeChecker(str1, str2, mergeLine); 
    
    
    if (output == "0") { 
        outputfile << "*** NOT A MERGE ***\n";
    } else {
        outputfile << output << "\n";
    }
}
    // Close files
    inputfile.close();
    outputfile.close();

    return 0;
};