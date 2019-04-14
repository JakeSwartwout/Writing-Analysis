#include "Graph.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;



Graph::Graph(){
  root = new trieNode;
  root->word = new Vertex;
  root->word->name = "START";
}

Graph::~Graph(){
  deleteTrieHelper(root);
}

//deals with finding the word, then adds a node if needed and calls createConnection
//assumes the previous is START if not found
void Graph::readInWord(string previous, string word){
  //find them
  Vertex* prev = findVertex(previous);
  Vertex* wrd = findVertex(word);


  //if it's the first word
  if(prev == nullptr){
    prev = root->word;
  }
  //if it hasn't been read yet
  if(wrd == nullptr){
    wrd = createWord(word);
  }

  //create or increase the connection by 1
  createConnection(prev, wrd, 1);
}

//just like readInWord, but for save words.
//creates a new node if previous is not found
void Graph::readInSaveWord(string previous, string word, int count){
  cout << "Reading in save word \'" << previous << "\' and \'" << word << "\' at \'" << count << "\'" << endl;

  //find them
  Vertex* prev = findVertex(previous);
  Vertex* wrd = findVertex(word);


  //if it's the first word
  if(prev == nullptr){
    prev = createWord(word);
  }
  //if it hasn't been read yet
  if(wrd == nullptr){
    wrd = createWord(word);
  }

  //create or increase the connection by 1
  createConnection(prev, wrd, count);
}

//reads in entire saved file (calls read in save word function)
void Graph::readInSaveFile(string fileName){
    //create a reader
    ifstream reader;
    reader.open(fileName);
    if (!reader.is_open()){
        cout << "ERROR: File could not be opened." <<endl;
        return;
    }

    //get the description
    string temp;
    getline (reader, temp);
    stringstream word;
    cout << "The description for this saved file is: " << endl << temp << endl;

    //start reading in
    string newWord;
    string prev;
    int wordFreq;
    while (getline(reader, temp)){
        cout << "the line is " << "\"" << temp << "\"" << endl;
        word.clear();
        word << temp;
        //get the word
        getline(word, temp, ':');
        prev = temp;
        //read in the connections
        while(getline(word,temp,'*')){ //first just the word
            newWord = temp;
            //then the number
            getline(word,temp,',');
            wordFreq = stoi(temp);
            readInSaveWord(prev, newWord, wordFreq);
        }
    }
    reader.close();
    cout << "The save file was successfully accessed. Please continue." <<endl;
}

void Graph::saveHelper(trieNode* node, ofstream &writer){
    if (node == nullptr){
        return;
    }
    //if node points to a word, save that into new line on file then save edge list; (if edge list is empty?)
    if (node->word != nullptr){
        writer << "\n" << node->word->name << ":";
        int tempSize = node->word->Edges.size();
        for (int i=0; i< tempSize; i++){
            writer << node->word->Edges[i].v->name << "*" << node->word->Edges[i].frequency << ",";
        }
    }
    int size = node->nextLetters.size();
    for (int i=0; i<size; i++){
        saveHelper(node->nextLetters[i], writer);
    }
}


//writes the graph to a file
void Graph::saveToFile(string fileName){
    //create a writer
    ofstream writer;
    writer.open(fileName);
    if (!writer.is_open()){
        cout << "ERROR: File did not open. Cannot save." << endl;
        return;
    }

    //add a description
    cout << "Please create a short description of this file: " << endl;
    string des;
    cin.ignore();
    getline(cin,des);
    writer << des;

    //save to the file
    //but skip the root
    for(int i = 0; i < root->nextLetters.size(); i++){
      saveHelper(root->nextLetters[i], writer);
    }


    cout << "The file is saved, Thanks!" << endl;
    writer.close();
    return;
}


//prints all of the nodes and all of their connections
void Graph::displayEdges(){
  //for(int i = 0; i < root->nextLetters.size(); i++)
    //displayEdgesHelper(root->nextLetters[i]);
  displayEdgesHelper(root);
}


//returns a word predicted from the word passed in
string Graph::predictWord(string word){
  //find the word
  Vertex* wrd = findVertex(word);

  //make sure it exists
  if(wrd == nullptr){
    cout << "Word does not exist!" << endl;
    return "ERROR";
  }

  //sum the total connections
  int totalConnections = 0;
  for(int i = 0; i < wrd->Edges.size(); i++){
    totalConnections += wrd->Edges[i].frequency;
  }

  //pick one
  int choice = rand() % totalConnections;

  //go find it
  for(int i = 0; i < wrd->Edges.size(); i++){
    //count down
    choice -= wrd->Edges[i].frequency;
    //until you reach the choice
    if(choice <= 0){
      return wrd->Edges[i].v->name;
    }
  }
}


//clean the word for direct insertion into the graph
string Graph::cleanWord(string &word){
  //remove tabs before
  while(word[0] == '\t'){
    word = word.substr(1);
  }
  //tab from the end
  while(word[word.length() - 1] == '\t'){
    word = word.substr(0, word.length() - 1);
  }

  //remove punctuation from the start
  while(ispunct(word[0]))
    word = word.substr(1);

  //remove punctuation from the end
  while(ispunct(word[word.length() -1]))
    word = word.substr(0, word.length() - 1);

  //make it lowercase
  transform(word.begin(), word.end(), word.begin(), ::tolower);

  return word;
}


//if the word is in the graph or not
bool Graph::inGraph(string word){
  return findVertex(word) != nullptr;
}



//Private

//recursively deletes the tree
void Graph::deleteTrieHelper(trieNode*& root){
  //loop through the next letters
  for(int i = 0; i < root->nextLetters.size(); i++){
    //delete the next letters
    deleteTrieHelper(root->nextLetters[i]);
  }

  //delete the word
  delete root->word;

  //delete this
  delete root;

  //now its null
  root = nullptr;
}


//searches through the trie to find the vertex, returns nullptr if not found
Vertex* Graph::findVertex(string word){
  trieNode* trie = root;

  //go through the word
  while(word != ""){
    bool found = false;
    //find the next letter
    for(int i = 0; i < trie->nextLetters.size(); i++){
      if(trie->nextLetters[i]->character == word[0]){
        found = true;
        //shorten the word
        word = word.substr(1);
        //go to that node
        trie = trie->nextLetters[i];
        //break out of the for loop
        break;
      }
    }
    //if they didn't find the letter
    if( !found ){
      return nullptr;
    }
  }
  return trie->word;
}

//creates a new vertex with the word
Vertex* Graph::createWord(string word){
  //go through the trie
  trieNode* trie = root;
  string wordCopy = word;

  //go through the word
  while(word != ""){
    bool found = false;
    //find the next letter
    for(int i = 0; i < trie->nextLetters.size(); i++){
      if(trie->nextLetters[i]->character == word[0]){
        found = true;
        //shorten the word
        word = word.substr(1);
        //go to that node
        trie = trie->nextLetters[i];
        //break out of the for loop
        break;
      }
    }
    //if they didn't find the letter
    if( !found ){
      //make a new node
      trieNode* newLetter = new trieNode;
      newLetter->character = word[0];
      newLetter->word = nullptr;
      trie->nextLetters.push_back(newLetter);
      //have it find it next time
    }
  }

  //now that the word is empty, it means we are at the correct trie node
  //create a new vertex here
  trie->word = new Vertex;
  trie->word->name = wordCopy;
  return trie->word;
}


//creates a connection or increases the count between the two words
void Graph::createConnection(Vertex* word1, Vertex* word2, int frequency){

    int index;
    //look for the word
    for(index = 0; index < word1->Edges.size(); index++){
        if(word1->Edges[index].v == word2)
            break;
    }

    //if we found it
    if(index < word1->Edges.size()){
        //increase its frequency
        word1->Edges[index].frequency ++;
    }
    //otherwise, add a new word
    else{
        Edge toBePushed;
        toBePushed.frequency = frequency;
        toBePushed.v = word2;
        word1->Edges.push_back(toBePushed);
    }

    //sort it up the list
    for(int i = index - 1; i > -1 && index > -1; i--){
        //if a swap is needed
        if(word1->Edges[index].frequency > word1->Edges[i].frequency){
            Edge temp = word1->Edges[index-1];
            word1->Edges[i] = word1->Edges[index];
            word1->Edges[index] = temp;
            index--;
        }
        //otherwise, quit
        else
            break;
    }
}


//recursively goes through the trie to display all of the vertices
void Graph::displayEdgesHelper(trieNode* root){
  //do not need a base case, since will only print
  //existing children

  //print this word if it exists
  if( root->word != nullptr){
    cout << root->word->name << ": ";
    //print all of it's connections too
    for(int i = 0; i < root->word->Edges.size(); i++){
      cout << root->word->Edges[i].v->name << "(";
      cout << root->word->Edges[i].frequency << ") ";
    }
    cout << endl;
  }

  //print all of its children
  for(int i = 0; i < root->nextLetters.size(); i++){
    displayEdgesHelper(root->nextLetters[i]);
  }
}
