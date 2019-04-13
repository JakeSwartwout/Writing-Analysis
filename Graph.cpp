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
void Graph::readInWord(string word, string previous){
  //find them
  Vertex* wrd = findVertex(word);
  Vertex* prev = findVertex(previous);

  //if it doesn't exist
  if(wrd == NULL){
    wrd = createWord();
  }

  createConnection(prev, wrd);
}

//prints all of the nodes and all of their connections
void displayEdges(){
  displayEdgesHelper(root);
}


//returns a word predicted from the word passed in
string Graph::predictWord(string word){
  //find the word
  Vertex* wrd = findVertex(word);

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
void Graph::deleteTrieHelper(trieNode*& root){
  //loop through the next letters
  for(int i = 0; i < root->nextLetters.size(); i++){
    //delete the next letters
    deleteTrieHelper(root->nextLetters[i]);
  }

  //delete the word
  delete root->v;

  //delete this
  delete root;

  //now its null
  root = NULL;
}


//searches through the trie to find the vertex, returns NULL if not found
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
      return NULL;
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
      if(root->nextLetters[i]->character == word[0]){
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
      newLetter.character = word[0];
      newLetter.word = NULL;
      trie->nextLetters.push_back(newLetter);
      //have it find it next time
    }
  }

  //now that the word is empty, it means we are at the correct trie node
  //create a new vertex here
  trie->word = new Vertex;
  trie->word->name = wordCopy;
}


//creates a connection or increases the count between the two words
void Graph::createConnection(Vertex* word1, Vertex* word2){
    int index = -1;
    for(int i = 0; i < word1->Edges.size(); i++){
        if(word1->Edges[i].v == word2)
            index = i;
    }
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
  if( root->word != NULL){
    cout << root->word->name << ": ";
    //print all of it's connections too
    for(int i = 0; i < root->word->Edges.size(); i++){
      cout << root->word->Edges[i].v->name << " ";
    }
  }

  //print all of its children
  for(int i = 0; i < root->nextLetters.size(); i++){
    displayEdgesHelper(root->nextLetters[i]);
  }
}
