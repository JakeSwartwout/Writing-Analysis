#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include "Graph.hpp"

using namespace std;

//functions will be defined below main
void printMenu();
void readInFile(ifstream &fileReader, Graph &graph);

int main(){
  srand(time(NULL));

  cout << "Read-o-matic 5000 online." << endl;
  //Main variabe declaration. stringInput, intInput and the fileReader
  ifstream fileReader;
  string sInput;
  string dataSave;
  int iInput;
  Graph graph;
  bool keepRunning = true;
  //Main While loop
  while(keepRunning){
    printMenu();
    cin >> iInput;
    switch (iInput){
      case 1://read in file
          cout << "Enter the file name you would like me to look at." << endl;
          cin >> sInput;
          cin.ignore();
          fileReader.open(sInput);
          if(!fileReader.fail()){
              //Read pairs of words.
              readInFile(fileReader, graph);
              cout << "Finished reading in the file" << endl;
          }
          else{
              cout << "Filereader has failed, the text document name was spelled incorrecty or doesn't exist." << endl;
              fileReader.close();
          }
          break;
      case 2: //open saved data
          cout << "Enter the name of the saved data file that you would like me to retrieve." <<endl;
          cin >> dataSave;
          graph.readInSaveFile(dataSave);
          break;
      case 3: //save current data
          cout << "Enter the name of the data file that you would like me to save your current session in." <<endl;
          cin >> dataSave;
          graph.saveToFile(dataSave);
          break;
      case 4: //display current data
          graph.displayEdges();
          break;
      case 5: //make prediction
          cout << "What word would you like to start with?" << endl;
          cin >> sInput;
          //make sure it is in the graph
          while( !graph.inGraph(sInput) ){
            cout << "That word isn't in the graph, try again" << endl;
            cin >> sInput;
          }
          //clear cin
          cin.ignore();
          //tell the user how it works
          cout << "Hit enter to generate another word." << endl;
          cout << "Press any other key and then enter to exit" << endl;
          cout << sInput << endl;
          //loop to print the words
          do{
            sInput = graph.predictWord(sInput);
            cout << sInput;
            //just to have them enter anything
            getline(cin, dataSave);
          } while(dataSave == "");
          cout << endl;
          break;
      case 6: //quit
          cout << "Goodbye! " << endl;
          keepRunning = false;
          break;

      default:
          cout << "Please enter a number for your selection." << endl;
          break;
    }
  }
}

void printMenu(){
    cout << "||1. Read in file        ||" << endl;
    cout << "||2. Open Saved data     ||" << endl;
    cout << "||3. Save current data   ||" << endl;
    cout << "||4. Display current data||" << endl;
    cout << "||5. Make prediction     ||" << endl;
    cout << "||6. Quit                ||" << endl;
}

//take an open file reader and graph and read everything into the graph
void readInFile(ifstream &fileReader, Graph &graph){
    string current, previous;
    //get the first word
    getline(fileReader, previous, ' ');
    //clean it
    graph.cleanWord(previous);
    //link it to the start
    graph.readInWord("START", previous);

    //prep to string stream
    stringstream ss;
    string line;

    //read in the rest of the lines
    while(getline(fileReader, line)){
      //make sure the line isn't empty
      if(line == "")
        continue;
      //empty the stream
      ss.clear();
      //give it the line
      ss << line;
      //read the words
      while(getline(ss, current, ' ')){
        //clean the word
        graph.cleanWord(current);
        //make sure it isn't empty
        if(current == "")
          continue;
        //add it in
        graph.readInWord(previous, current);
        //move to the next word
        previous = current;
      }
    }
    fileReader.close();
}
