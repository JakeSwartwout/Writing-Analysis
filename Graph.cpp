#include "Graph.hpp"
#include <vector>
#include <list>
#include <iostream>
using namespace std;



Graph::Graph(){
  root = new trieNode;
  root->word = new Vertex;
  root->word->name = "START";
}

Graph::~Graph(){
  deleteTrieHelper(root);
}

//readInWord, but from the save file (known frequency number)
void Graph::readInSaveWord(string word, string previous, int count){
    Vertex* wrd = findVertex(word);
    Vertex* prev = findVertex(previous);

    if(wrd == NULL){
    wrd = createWord(word);
    }

    Edge toBePushed;
    toBePushed.frequency = count;
    toBePushed.v = wrd;
    prev->Edges.push_back(toBePushed);
}

//reads in entire saved file (calls read in save word function)
void Graph::readInSaveFile(string fileName){
    ifstream reader;
    reader.open(fileName);
    if (!reader.is_open()){
        cout << "ERROR: File could not be opened." <<endl;
        return;
    }
    string temp;
    getline (reader, temp);
    stringstream word;
    cout << "The description for this saved file is: " << endl << temp << endl;
    root = new trieNode;
    string newWord;
    string prev;
    int wordFreq;
    while (getline(reader, temp)){
        word.str("");
        word << temp;
        temp.clear();
        getline(word, temp,',');
        prev = temp;
        createWord(temp);
        while (getline(word,temp,',')){
            newWord = temp;
            getline(word,temp,',');
            wordFreq = stoi(temp);
            readInSaveWord(newWord, prev, wordFreq);   
        }
    }
    reader.close();
    cout << "The save file was successfully accessed. Please continue." <<endl;
}
//writes the graph to a file

void saveHelper(trieNode* node, ofstream &writer){
    if (node==NULL){
        return;
    }
    //if node points to a word, save that into new line on file then save edge list; (if edge list is empty?)
    if (node->word!=NULL){
        writer << "\n" << node->word << ",";
        int tempSize = node->word->Edges.size();
        for (int i=0; i< tempSize; i++){
            writer << node->word->Edges[i].v->name << "," << node->word->Edges[i].frequency << ",";
        }
    }
    int size = node->nextLetters.size();
    for (int i=0; i<size; i++){
        saveHelper(node->nextLetters[i], writer);
    }
}


void Graph::saveToFile(string fileName){
    ofstream writer;
    writer.open(fileName);
    if (!writer.is_open()){
        cout << "ERROR: File did not open. Cannot save." << endl;
        return;
    }
    cout << "Please create a short description of this file: " << endl;
    string des;
    cin.ignore();
    getline(cin,des);
    writer << des;
    saveHelper(root, writer);    
    cout << "The file is saved, Thanks!" << endl;
    writer.close();
    return;
}


//deals with finding the word, then adds a node if needed and calls createConnection
void Graph::readInWord(string previous, string word){
  //find them
  Vertex* prev = findVertex(previous);
  Vertex* wrd = findVertex(word);
  

  //if it doesn't exist
  if(prev == nullptr){
    prev = createWord(previous);
  }
  if(wrd == nullptr){
    wrd = createWord(word);
  }
  
  //cout << "Got to here" << endl;
  createConnection(prev, wrd);
  //cout << "Completed connections" << endl;
}

//prints all of the nodes and all of their connections
void Graph::displayEdges(){
  for(int i = 0; i < root->nextLetters.size(); i++)
    displayEdgesHelper(root->nextLetters[i]);
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
void Graph::createConnection(Vertex* word1, Vertex* word2){
    int index = -1;
    //cout << "Here" << endl;
    
      //cout << "Print true" << endl;
    //cout << "Edge " << word1->Edges.size();

    for(int i = 0; i < word1->Edges.size(); i++){
        if(word1->Edges[i].v == word2)
            index = i;
    }
    //cout << "Hello" << endl;
    if(index >= 0){
        word1->Edges[index].frequency ++;
        bool keepSort = true;
        for(int i = index - 1; i > -1 && index > -1; i--){
            if(word1->Edges[index].frequency > word1->Edges[i].frequency){
                Edge temp = word1->Edges[index];
                word1->Edges[i] = word1->Edges[index];
                word1->Edges[index] = temp;
                index--;
            }
            else
                i = -1;
        }
    }
    else{
        Edge toBePushed;
        toBePushed.frequency = 1;
        toBePushed.v = word2;
        word1->Edges.push_back(toBePushed);
    }
}


//recursively goes through the trie to display all of the vertices
void Graph::displayEdgesHelper(trieNode* root){
  //print this word if it exists
  if( root->word != nullptr){
    cout << root->word->name << ": ";
    //print all of it's connections too
    for(int i = 0; i < root->word->Edges.size(); i++){
      cout << root->word->Edges[i].v->name << " ";
    }
    cout << endl;
  }

  //print all of its children
  for(int i = 0; i < root->nextLetters.size(); i++){
    displayEdgesHelper(root->nextLetters[i]);
  }
  //cout << endl;
}
