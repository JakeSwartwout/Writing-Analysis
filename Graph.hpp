#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
using namespace std;

struct Vertex;

/*This is the struct for the adjacent vertices for each
Vertex in the graph. */
struct Edge
{
    Vertex *v;
    int frequency;
};

/*this is the struct for each Vertex in the graph. */
struct Vertex
{
    string name;
    vector<Edge> Edges; //stores edges to adjacent vertices
};

struct trieNode{
  char character;
  vector<trieNode*> nextLetters;
  Vertex* word;
};


class Graph
{
  public:
    Graph();
    ~Graph();
    //deals with finding the word, then adds a node if needed and calls createConnection
    void readInWord(string previous, string word);
    //exactly the same as readInWord, except that it increments it by a count, rather than by 1
    void readInSaveWord(string previous, string word, int count);
    //reads in entire saved file (calls read in save word function)
    void readInSaveFile(string fileName);
    //writes the graph to a file
    void saveToFile(string fileName);
    //prints all of the nodes and all of their connections
    void displayEdges();
    //returns a word predicted from the word passed in
    string predictWord(string word);
    //clean the word for direct insertion into the graph
    string cleanWord(string &word);
    //if the word is in the graph or not
    bool inGraph(string word);


  private:
    //the trie that holds all of the vertices
    trieNode* root;

    //recursively deletes the tree
    void deleteTrieHelper(trieNode*& root);
    //searches through the trie to find the Vertex, returns nullptr if not found
    Vertex* findVertex(string word);
    //creates a new Vertex with the word
    Vertex* createWord(string word);
    //creates a connection or increases the count between the two words
    void createConnection(Vertex* fromWord, Vertex* toWord, int frequency);
    //recursively goes through the trie to display all of the vertices
    void displayEdgesHelper(trieNode* root);
    //helps recursively traverse the tree to print to a file
    void saveHelper(trieNode* node, ofstream &writer);
};

#endif // GRAPH_HPP
