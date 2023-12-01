#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;

// MergeArray is a global variable to prevent stack overflow
int MergeArray[1000][1000] = {0};

// MergeChecker function 
// returns 0 when found out to be not a merge 
// returns the merge string if it is a merge 
string MergeChecker(const string& str1, const string& str2, string& merge) {
    int a = str1.length();
    int b = str2.length();
    int c = merge.length();
    string result = "";

    // Length of merge should be equal to the sum of the lengths of str1 and str2
    if (a + b != c) {
        return "0";
    }

    // If both strings are empty, then the merge is empty
    if (a == 0 && b == 0) {
        return "";
    }

    // Bottom-up dynamic programming approach 
    for (int i = 0; i <= a; ++i) {
        for (int j = 0; j <= b; ++j) {

            if (i == 0 && j == 0) {
                MergeArray[i][j] = 1;

                // If characters from both str1 and str2 match the current character in merge
                // and the diagonal (top-left) cell is 1, set MergeArray[i][j] to 1.
            }if (i > 0 && j > 0 && str1[i - 1] == merge[i + j - 1] && str2[j - 1] == merge[i + j - 1] && MergeArray[i - 1][j] == 1) {
                MergeArray[i][j] = 1;

                // If the character from str1 matches the current character in merge
                // and the cell above is 1, set MergeArray[i][j] to 1.
            } else if (i > 0 && str1[i - 1] == merge[i + j - 1] && MergeArray[i - 1][j] == 1) {
                MergeArray[i][j] = 1;
                result += toupper(str1[i - 1]);

                // If the character from str2 matches the current character in merge
                // and the cell to the left is 1, set MergeArray[i][j] to 1.
            } else if (j > 0 && str2[j - 1] == merge[i + j - 1] && MergeArray[i][j - 1] == 1) {
                MergeArray[i][j] = 1;
                result += str2[j - 1];

            }
        }
    }

    // Check if the last cell is equal to 1, indicating a valid merge
    if (MergeArray[a][b] == 1) {
        return result;
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

    string output = MergeChecker(str1, str2, mergeLine); 
    memset(MergeArray, 0, sizeof(MergeArray));
    
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