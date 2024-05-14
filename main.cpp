#include <iostream>
#include <vector>
#include <algorithm>
#include "Sudoku.h"
#include "X.h"
#define MAX_ROW 729
#define MAX_COL 324
#define SIZE 9
using namespace std;

// Function that would help visualize the binary matrix format
void printBinaryMatrix(vector<vector<int>> &binaryMatrix)
{
    for (const auto &row : binaryMatrix)
    {
        for (size_t col = 0; col < binaryMatrix[0].size(); ++col)
        {
            if (row[col] == 1)
            {
                // Print in bold green
                cout << "\033[1;32m" << row[col] << "\033[0m";
            }
            else
            {
                // Print in default terminal color
                cout << row[col];
            }
        }
        cout << endl;
    }
}

int main()
{

    // the matrix that will contain the Nodes
    Node *Matrix[MAX_ROW + 1][MAX_COL];
    
    // The matrix that will be containing the solution of the problem
    vector<struct Node *> Solution;

    int nRow = BINARY_ROWS;
    int nCol = BINARY_COLUMNS;
    X algoX = X();
    // Allocating memory to the matrix nodes
    algoX.setRowsColumns(BINARY_ROWS, BINARY_COLUMNS);
    for (int i = 0; i <= nRow; i++)
    {
        for (int j = 0; j < nCol; j++)
        {
            Matrix[i][j] = new Node();
        }
    }

    
    Sudoku Solver = Sudoku();
    
    // Initialize the binary matrix with 0's
    vector<vector<int>> binaryMatrix(BINARY_ROWS, vector<int>(BINARY_COLUMNS, 0));
    vector<int> head{};
    // Fill the header row with 1's
    for (size_t i = 0; i < binaryMatrix[0].size(); i++)
    {
        head.push_back(1);
    }
    // Fill the binary matrix according to the constraints of a Sudoku puzzle
    Solver.constructBinaryMatrix(binaryMatrix);

    // Adding the clues manually for the moment
    // Example of Sudoku clues
    
    Solver.addClue(0, 0, 1, binaryMatrix);
    Solver.addClue(0, 2, 7, binaryMatrix);
    Solver.addClue(0, 5, 6, binaryMatrix);
    Solver.addClue(0, 6, 4, binaryMatrix);

    Solver.addClue(1, 1, 2, binaryMatrix);
    Solver.addClue(1, 2, 5, binaryMatrix);
    Solver.addClue(1, 8, 8, binaryMatrix);

    Solver.addClue(2, 1, 6, binaryMatrix);
    Solver.addClue(2, 5, 1, binaryMatrix);
    Solver.addClue(2, 7, 7, binaryMatrix);

    Solver.addClue(3, 1, 5, binaryMatrix);
    Solver.addClue(3, 2, 3, binaryMatrix);
    Solver.addClue(3, 7, 2, binaryMatrix);
    Solver.addClue(3, 8, 9, binaryMatrix);

    Solver.addClue(4, 0, 6, binaryMatrix);
    Solver.addClue(4, 1, 1, binaryMatrix);
    Solver.addClue(4, 5, 9, binaryMatrix);
    Solver.addClue(4, 6, 8, binaryMatrix);

    Solver.addClue(5, 3, 6, binaryMatrix);
    Solver.addClue(5, 5, 2, binaryMatrix);
    Solver.addClue(5, 8, 7, binaryMatrix);

    Solver.addClue(6, 2, 1, binaryMatrix);
    Solver.addClue(6, 4, 9, binaryMatrix);
    Solver.addClue(6, 5, 3, binaryMatrix);
    Solver.addClue(6, 6, 2, binaryMatrix);

    Solver.addClue(7, 2, 8, binaryMatrix);

    Solver.addClue(8, 1, 4, binaryMatrix);
    Solver.addClue(8, 4, 7, binaryMatrix);
    Solver.addClue(8, 5, 8, binaryMatrix);
    Solver.addClue(8, 6, 5, binaryMatrix);
    Solver.addClue(8, 7, 9, binaryMatrix);
    Solver.addClue(8, 8, 1, binaryMatrix);

    // Add the column headers to the binary matrix
    binaryMatrix.insert(binaryMatrix.begin(), head);
    // // create 4-way linked matrix
    algoX.createGrid(binaryMatrix, Matrix);
    ofstream outFile("Solution.txt"); // Create an output file stream
    if (!outFile.is_open())
    {
        cerr << "Failed to open the file." << endl;
    }
    // Search for the solutions using X Algorithm
    algoX.search(0, Solution, outFile);
    // Close the file
    outFile.close(); 

    // // We need to liberate all the memory  we have allocated during the whole process
    for (int i = 0; i <= nRow; i++)
    {
        for (int j = 0; j < nCol; j++)
        {
            delete Matrix[i][j];
        }
    }
    return 0;
}