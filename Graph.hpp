#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <list>
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
  list<trieNode*> nextLetters;
  vertex* word;
};


class Graph
{
  public:
    Graph();
    ~Graph();
    //deals with finding the word, then adds a node if needed and calls createConnection
    void readInWord(string word, string previous);
    //prints all of the nodes and all of their connections
    void displayEdges();
    //returns a word predicted from the word passed in
    string predictWord(string word);

  private:
    //the trie that holds all of the vertices
    trieNode* root;

    //searches through the trie to find the vertex
    vertex* findVertex(string word);
    //creates a new vertex with the word
    void createWord(string word);
    //creates a connection or increases the count between the two words
    void createConnection(vertex* word1, vertex* word2);
};

#endif // GRAPH_HPP
