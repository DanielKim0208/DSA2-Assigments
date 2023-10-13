
//Daniel Kim
//I got chatGPT help for the chrono function 
//I got help from google SDE to look up input.clear() and input.seekg(0) functions
//I got help from Taaseen Jahan, who took this course last semester for some parts of spellcheck logic I found challenging 

#include "hash.h"
#include <string>
#include <iostream> 
#include <fstream>
#include <algorithm> 
#include <ctime>
#include <chrono>
#include <vector>
#include <cctype>
#include <sstream>
using namespace std;
using namespace std::chrono;


//This part loads the dictionary into hashTable
hashTable loadDict(string &dict)
{ 
    //defining necessary variables and input stream
    int size = 0;
    ifstream input(dict);
    string entry; 
    string item;

    //measure the size of the table by counting number of items 
    while(getline(input, item)){
        size++;
    }

    //Create hashtable of the size
    hashTable dictHash = hashTable(size);

    //Nontrivial Google SGE help start 
    input.clear();
	input.seekg(0);
    //nontrivial Google SGE help end

    //Insert the lowercased Items into the dictionary Hashtable. 
    while (getline(input, item)) {
        transform(item.begin(), item.end(), item.begin(), ::tolower);
        dictHash.insert(item);
    }

    return dictHash;
}


//function to check if the given word is in the dictionary
bool dictCheck(string &word, hashTable &dict) {

//If a seperator " ", return true
    if (word.empty()) {
        return true; 
//If in the dictionary, return true
    } else if(dict.contains(word)) {
        return true;
//else, return false
    }else{
        return false;
    }
}

void spellcheck(string &inputFile, string &outputFile, hashTable &dict) {

    // Open input and output files
    ifstream input(inputFile);
    ofstream output(outputFile);
    //error message in case can't open I/O files
    if (!input.is_open() || !output.is_open()) {
        cerr << "Failed to open input or output file." << endl;
        return;
    }

    string line;
    int lineNo = 0;

    while (getline(input, line)) {
        // Transform all the line string to lowercase in order to make it case-insensitive 
        transform(line.begin(), line.end(), line.begin(), ::tolower);

        //Look for the letters that are not alphanumeric, dash or atstrophie and convert them into the seperators
        for (int i = 0; i < line.size(); i++) {
            if (!isalnum(line[i]) && line[i] != '-' && line[i] != '\'') {
                line[i] = ' '; 
            }
        }

        // defining variables
        string word;
        bool ignore = false;

        // Use the seperator conversion process above to start string streaming the input into different words
        istringstream iss(line);

        //While there are still words left in the file
        while (iss >> word) {

            // Check if the word contains a digit, and turn on the ignore boolean if so
            for (char c : word) {
                if (isdigit(c)) {
                    ignore = true; // Ignore words with digits
                    break;
                }
            }


            // Check for long words and unknown words that does not contain digits
            //lineno +1 since the first line is line 1
            if (word.length() > 20 && !ignore) {
                output << "Long word at line " << lineNo + 1 << ", starts: " << word.substr(0, 20) << endl;
            } else {
            //use the dictCheck function and probe words 
            //If not present in the dictionary hashtable print the
                if (dictCheck(word,dict)==false && ignore==false) {
                    output << "Unknown word at line " << lineNo + 1 << ": " << word << endl;
                }
            }
        }

        //After processing each line, go to the next line
        lineNo++;
    }

    // Close the input and output files
    input.close();
    output.close();
}




int main(){
    //defining variables, hashtable and chrono timepoint for time measurements
    string dict_file;
    string inputFile; 
    string outputFile; 
    string dict_testFile;
    string dict_inProgram;
    hashTable dict;
    steady_clock::time_point dict_start, dict_end, check_start, check_end;

    //Handling user interactions
    
    cout << "Please name the dictionary file" <<endl; 
    cin >> dict_file; 
    cout << "Please name the input file to be checked"<<endl; 
    cin >> inputFile;
    cout << "Please name the output file for results"<<endl; 
    cin >> outputFile;


    //Beginning of nontrivial ChatGPT help 
    //stamp the start time 
  dict_start = steady_clock::now();

    //load the dictionary using the loadDict feature
	dict = loadDict(dict_file);

    //stamp the end time
	dict_end = steady_clock::now();

    //endTime - startTime for time taken 
	duration<double> timeDiff_dict = duration_cast<duration<double>>(dict_end - dict_start);
	cout << "Dictionary load Time(s): " << timeDiff_dict.count() << endl;
    //End of nontrivial chatGPT help 
      //dictTest(testFile,dict); 

    //Code above have registered the dictionary as dict. 
    //I now need to utilize spellcheck; 
    //same time stamping feature

    check_start = steady_clock::now();  
    spellcheck(inputFile,outputFile,dict);
    check_end = steady_clock::now();
    duration<double> timeDiff_check = duration_cast<duration<double>>(check_end - check_start);
    cout << "Spell check process Time(s): " << timeDiff_check.count() << endl;
}