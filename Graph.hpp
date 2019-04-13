#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>

struct vertex;

/*This is the struct for the adjacent vertices for each
vertex in the graph. */
struct Edge
{
    vertex *v;
    int frequency;
};

/*this is the struct for each vertex in the graph. */
struct vertex
{
    string name;
    vector<Edge> Edges; //stores edges to adjacent vertices
};

struct trieNode{
  char character;
  vector<trieNode*> nextLetters;
  vertex* word;
};


class Graph
{
  public:
    Graph();
    ~Graph();
    //deals with finding the word, then adds a node if needed and calls createConnection
    void readInWord(string word, string previous);
    //exactly the same as readInWord, except that it increments it by a count, rather than by 1
    void readInSaveWord(string word, string previous, int count);
    //reads in entire saved file (calls read in save word function)
    void readInSaveFile(string word, string previous, int count);
    //writes the graph to a file
    void saveToFile(string fileName);
    //prints all of the nodes and all of their connections
    void displayEdges();
    //returns a word predicted from the word passed in
    string predictWord(string word);

  private:
    //the trie that holds all of the vertices
    trieNode* root;

    //recursively deletes the tree
    void deleteTrieHelper(trieNode*& root);
    //searches through the trie to find the vertex, returns NULL if not found
    vertex* findVertex(string word);
    //creates a new vertex with the word
    vertex* createWord(string word);
    //creates a connection or increases the count between the two words
    void createConnection(vertex* word1, vertex* word2);
    //recursively goes through the trie to display all of the vertices
    void displayEdgesHelper(trieNode* root);
};

#endif // GRAPH_HPP
