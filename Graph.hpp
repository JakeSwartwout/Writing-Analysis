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
    int distance;
};

/*this is the struct for each vertex in the graph. */
struct vertex
{
    string name;
    vector<Edge> Edges; //stores edges to adjacent vertices
};

struct trieNode{
  char character;
  list<trieNode*> next;
  vertex* word;
};


class Graph
{
  public:
    Graph();
    ~Graph();
    //either increases the word's frequency or creates a new one and connects it
    void readInWord(string word, string previous);
    //prints all of the nodes and all of their connections
    void displayEdges();

  private:
    trieNode* root;

    vertex *findVertex(std::string name);
    //creates a new vertex with the word
    void addWord(string word);
    //creates a connection or increases the count between the two words
    void createConnection(vertex* word1, vertex* word2);

};

#endif // GRAPH_HPP
