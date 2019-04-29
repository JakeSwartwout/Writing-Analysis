# Writing-Analysis
Data Structures Final Project 2019, but still the best project there'll ever be

This program reads .txt files into a graph to make a predictive text generator. Words are stored in a trie (letter tree), with a vector of Edges. Each edge has a weight and pointer to a vertex, signifying how often a word comes after another word. There is functionality to save the tree into a file, as to only require reading in long documents once. There is a more in depth explanation in the uploaded "Final Report.pdf" file

## Work Distribution:
Dorothea: All save functionality

Spas: Entire driver file, clean function (to remove punctuation and capitalization), and addConnection function

Jake: Rough .hpp file, some of the basic functions in graph.cpp, lots of debugging
