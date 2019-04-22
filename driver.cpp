#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include "Graph.hpp"

using namespace std;

void printMenu(){
    cout << "||1. Read in file          ||" << endl;
    cout << "||2. Open Saved data       ||" << endl;
    cout << "||3. Save current data     ||" << endl;
    cout << "||4. Display current data  ||" << endl;
    cout << "||5. Make random prediction||" << endl;
    cout << "||6. Predict most common   ||" << endl;
    cout << "||7. Predict least common  ||" << endl;
    cout << "||8. Investigate word      ||" << endl;
    cout << "||9. Quit                  ||" << endl;
}


int main(){
  //to have truly random predictions
  srand(time(NULL));

  cout << "Read-o-matic 5000 online." << endl;

  //Main variable declaration. stringInput, intInput and the fileReader
  ifstream fileReader;
  string sInput;
  string dataSave;
  int iInput;
  Graph graph;
  bool keepRunning = true;

  //main loop, prompts user to select and option repeatedly
  while(keepRunning){
    //show the menu
    printMenu();
    //get their choice
    cin >> iInput;
    cin.ignore();
    //evaluate the choice
    switch (iInput){

      case 1://read in file
          cout << "Enter the file name you would like me to look at." << endl;
          getline(cin, sInput);
          fileReader.open("Writing Samples\\" + sInput);
          if(!fileReader.fail()){
              //Read pairs of words.
              graph.readInFile(fileReader);
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
          graph.readInSaveFile("Save Files\\" + dataSave);
          break;

      case 3: //save current data
          cout << "Enter the name of the data file that you would like me to save your current session in." <<endl;
          cin.ignore();
          getline(cin, dataSave);
          graph.saveToFile("Save Files\\" + dataSave);
          break;

      case 4: //display current data
          graph.displayEdges();
          break;

      case 5: //make random prediction
          cout << "Using probability to predict the next word" << endl;
          sInput = graph.promptWord();
          if(sInput == ""){
            break;
          }
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

      case 6: //predict the most common
          cout << "Predicting the most common word:" << endl;
          sInput = graph.promptWord();
          if(sInput == ""){
            break;
          }
          //tell the user how it works
          cout << "Hit enter to generate another word." << endl;
          cout << "Press any other key and then enter to exit" << endl;
          cout << sInput << endl;
          //loop to print the words
          do{
            sInput = graph.predictBestWord(sInput);
            cout << sInput;
            //just to have them enter anything
            getline(cin, dataSave);
          } while(dataSave == "");
          cout << endl;
          break;

      case 7: //predict the least common
          cout << "Predicting the least common word:" << endl;
          sInput = graph.promptWord();
          if(sInput == ""){
            break;
          }
          //tell the user how it works
          cout << "Hit enter to generate another word." << endl;
          cout << "Press any other key and then enter to exit" << endl;
          cout << sInput << endl;
          //loop to print the words
          do{
            sInput = graph.predictWorstWord(sInput);
            cout << sInput;
            //just to have them enter anything
            getline(cin, dataSave);
          } while(dataSave == "");
          cout << endl;
          break;

      case 8: //investigate word
          cout << "Investigating a single word:" << endl;
          cout << "Which word would you like to learn about?" << endl;
          sInput = graph.promptWord();
          if(sInput != ""){
            graph.printEdges(sInput);
          }
          break;

      case 9: //quit
          cout << "Goodbye! " << endl;
          keepRunning = false;
          break;

      default:
          cout << "Please enter a number for your selection." << endl;
          break;
    }
  }
}
