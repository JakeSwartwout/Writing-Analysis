#include "Graph.hpp"
#include <vector>
#include <list>
#include <iostream>
using namespace std;



Graph::Graph(){
  root = NULL;
}

Graph::~Graph(){
  deleteTrieHelper(trieNode* root);
}


//deals with finding the word, then adds a node if needed and calls createConnection
void readInWord(string word, string previous){
  //find them
  vertex* wrd = findVertex(word);
  vertex* prev = findVertex(previous);

  //if it doesn't exist
  if(wrd == NULL){
    wrd = createWord();
  }

  createConnection(wrd, prev);
}

//prints all of the nodes and all of their connections
void displayEdges(){
  displayEdgesHelper(root);
}


//returns a word predicted from the word passed in
string predictWord(string word){
  //find the word
  vertex* wrd = findVertex(word);

  //make sure it exists
  if(wrd == NULL){
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
    choice -= wrd->Edges[i].frenquency;
    //until you reach the choice
    if(choice <= 0){
      return wrd->Edges[i].v->name;
    }
  }
}



//Private

//recursively deletes the tree
void deleteTrieHelper(trieNode*& root){
  //loop through the next letters
  for(int i = 0; i < root->nextLetters.size(); i++){
    //delete the next letters
    deleteTrieHelper(root->nextLetters[i]);
  }

  //delete the word
  delete vertex;

  //delete this
  delete root;

  //now its null
  root = NULL;
}


//searches through the trie to find the vertex, returns NULL if not found
vertex* findVertex(string word){
  trieNode* trie = root;

  //go through the word
  while(word != ""){
    bool found = false;
    //find the next letter
    for(int i = 0; i < root->nextLetters.size(); i++){
      if(root->nextLetters[i]->character == word[0]){
        found = true;
        //shorten the word
        word = word.substr(1);
        //go to that node
        root = root->nextLetters[i];
        //break out of the for loop
        break;
      }
    }
    //if they didn't find the letter
    if( !found ){
      return NULL;
    }
  }
  return root->word;
}

//creates a new vertex with the word
vertex* createWord(string word){
  //go through the trie
  trieNode* trie = root;
  string wordCopy = word;

}


//creates a connection or increases the count between the two words
void createConnection(vertex* word1, vertex* word2);
//recursively goes through the trie to display all of the vertices
void displayEdgesHelper(trieNode* root);
