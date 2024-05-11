#ifndef X_H
#define X_H
#include <iostream>
#include <algorithm>
#include<vector>
#include <array>
#include <fstream>
#include "Sudoku.h"
#define BINARY_COLUMNS 324
#define BINARY_ROWS 729
#define MAX_ROW 729
#define MAX_COL 324
#define SIZE 9

using namespace std;

// Data structure to represent The circular linked list
typedef struct Node
{
    Node *up;
    Node *down;
    Node *right;
    Node *left;
    Node *column;
    int rowId;     // To store the row index
    int colId;     // to store thre column index
    int nodeCount; // To store number of Nodes in each column
} Node;

class X
{
public:
    struct Node *header;
    X();
    Node *createGrid(vector<vector<int>>& problemMAtrix, Node *(&Matrix)[MAX_ROW + 1][MAX_COL ]);
    void search(int k, vector<struct Node *> &Solution,ofstream & outFile);
    ~X();
    void setRowsColumns(int row, int column);

private:
    int nCol = 324;
    int nRow = 726;

    void cover(Node *target);
    void uncover(Node *target);
    void printSolution(vector<struct Node *> &Solution,ofstream & outFile);
    Node *getMinColumn();
    int getUp(int i);
    int getDown(int i);
    int getLeft(int i);
    int getRight(int i);
};
#endif