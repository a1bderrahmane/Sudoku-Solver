#ifndef SUDOKU_H
#define SUDOKU_H

#define SIZE 9 // Defines the size of the Sudoku grid as 9x9

#include <iostream>
#include <vector>

using namespace std;

class Sudoku
{
public:
    // Constructor
    Sudoku();

    // Destructor
    ~Sudoku();

    // Function to print the Sudoku grid
    void print(vector<vector<int>> &grid) const;

    // Function to construct the binary matrix representation of the Sudoku grid
    void constructBinaryMatrix(vector<vector<int>> &binaryMatrix);

    // Function that modifies the binary matrix to take into account the clue
    // int i and int j are the indexes of the clue in the grid
    // the clue is the number at grid[i][j]
    void addClue(int i, int j, int clue, vector<vector<int>> &binaryMatrix);

    // Function that will translate the exact cover problem solution to a Sudoku solution
    void SolvePuzzle(vector<int>&rowIDs,vector<int>& values);

private:
    // Function to add cell constraints to the binary matrix
    void addCellConstraint(vector<vector<int>> &binaryMatrix);

    // Function to add row constraints to the binary matrix
    void addRowConstraint(vector<vector<int>> &binaryMatrix);

    // Function to add column constraints to the binary matrix
    void addColumnConstraint(vector<vector<int>> &binaryMatrix);

    // Function to add block constraints to the binary matrix
    void addBlockConstraint(vector<vector<int>> &binaryMatrix);

    // Function to get the block number based on the cell's position
    int getBlockNumber(int i, int j) const;

    // Using the clue we do the modifications of the binary matrix
    void changeCellConstraint(int i, int j, int clue, vector<vector<int>> &binaryMatrix);
    void changeRowConstraint(int i, int j, int clue, vector<vector<int>> &binaryMatrix);
    void changeColumnConstraint(int i, int j, int clue, vector<vector<int>> &binaryMatrix);
    void changeBlockConstraint(int i, int j, int clue, vector<vector<int>> &binaryMatrix);
};

#endif // SUDOKU_H