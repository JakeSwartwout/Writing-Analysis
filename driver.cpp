#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "Graph.hpp"

using namespace std;

void printMenu();
void printPairsOfWords(ifstream *fileReader);
string cleanWord(string word);

int main(int argv, const char *argc[]){
    //File recieved in for data
    if(argv == 2){




    }
    //No file recieved, make one on quit
    else if(argv == 1){
        cout << "Read-o-matic 5000 online." << endl;
        //Main variabe declaration. stringInput, intInput and the fileReader
        ifstream fileReader;
        string sInput;
        int iInput;
        bool keepRunning = true;
        //Main While loop
        while(keepRunning){
            printMenu();
            cin >> iInput;
            switch (iInput)
            {
                case 1:
                    cout << "Enter the file name you would like me to look at." << endl;
                    cin >> sInput;
                    cin.ignore();
                    fileReader.open(sInput);
                    if(!fileReader.fail()){
                        //Read pairs of words.
                        printPairsOfWords(&fileReader);

                    }
                    else{
                        cout << "Filereader has failed, the text document name was spelled incorrecty or doesn't exist." << endl;
                        fileReader.close();
                    }
                    break;
                case 2:

                    break;
                case 3:
                    cout << "Goodbye! " << endl;
                    keepRunning = false;
                    break;

                default:
                    cout << "Please enter a number for your selection." << endl;
                    break;
            }
        }

    }
    else{
        cout << "Please either enter a filename to read in data, or nothing at all to start..." << endl;
        return -1;
    }
}

void printMenu(){
    cout << "||1. Read in file     ||" << endl;
    cout << "||2. Some other Option||" << endl;
    cout << "||3. Quit             ||" << endl;
}
void printPairsOfWords(ifstream *fileReader){
    string current, previous;
    getline(*fileReader, previous, ' ');
    while(getline(*fileReader, current, ' ')){
        cout << cleanWord(previous) << " >> " << cleanWord(current) << endl;
        previous = current;
    }
    cout << "Printed all word combinations " << endl;
    (*fileReader).close();
}
//To be implemented Later
string cleanWord(string word){
    string returnString = word;
    if(word[word.length() -1] == ',' || word[word.length() -1] == '.')
        returnString = word.substr(0, word.length() - 1);
    transform(returnString.begin(), returnString.end(), returnString.begin(), ::tolower);
    return returnString;
}