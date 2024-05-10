#include <iostream>
#include <vector>
#include "Sudoku.h"
#include "X.h"
#define MAX_ROW 729
#define MAX_COL 324
#define SIZE 9
using namespace std;

void printBinaryMatrix(std::vector<std::vector<int>> &binaryMatrix)
{
    for (const auto &row : binaryMatrix)
    {
        for (size_t col =0; col < binaryMatrix[0].size(); ++col)
        {
            if (row[col] == 1)
            {
                // Print in bold green
                std::cout << "\033[1;32m" << row[col] << "\033[0m";
            }
            else
            {
                // Print in default terminal color
                std::cout << row[col] ;
            }
        }
        std::cout << std::endl;
    }
}

int main()
{

    // the matrix of the Nodes
    Node *Matrix[MAX_ROW + 1][MAX_COL ];

    vector<struct Node *> Solution;

    int nRow = BINARY_ROWS;
    int nCol = BINARY_COLUMNS;
    X algoX = X();
    algoX.setRowsColumns(BINARY_ROWS, BINARY_COLUMNS);
    for (int i = 0; i <= nRow; i++)
    {
        for (int j = 0; j < nCol; j++)
        {
            Matrix[i][j] = new Node();
        }
    }

    Sudoku Solver = Sudoku();

    std::vector<std::vector<int>> grid(SIZE, std::vector<int>(SIZE, 0));

    std::vector<std::vector<int>> binaryMatrix(BINARY_ROWS, std::vector<int>(BINARY_COLUMNS, 0));
    vector<int> head{};
    for (int i = 0; i < binaryMatrix[0].size(); i++)
    {
        head.push_back(1);
    }
   

    Solver.constructBinaryMatrix(binaryMatrix);
    Solver.addClue(0, 3, 6, binaryMatrix);
    Solver.addClue(1, 8, 2, binaryMatrix);
    Solver.addClue(2, 5, 1, binaryMatrix);
    Solver.addClue(2, 8, 9, binaryMatrix);
    Solver.addClue(3, 6, 4, binaryMatrix);
    Solver.addClue(4, 0, 5, binaryMatrix);
    Solver.addClue(4, 3, 1, binaryMatrix);
    Solver.addClue(4, 8, 3, binaryMatrix);
    Solver.addClue(6, 1, 4, binaryMatrix);
    Solver.addClue(6, 8, 7, binaryMatrix);
    Solver.addClue(7, 0, 6, binaryMatrix);
    Solver.addClue(8, 7, 5, binaryMatrix);
    Solver.addClue(0, 2, 3, binaryMatrix);
    Solver.addClue(0, 4, 8, binaryMatrix);
    Solver.addClue(1, 3, 4, binaryMatrix);
    Solver.addClue(2, 6, 5, binaryMatrix);
    Solver.addClue(3, 2, 1, binaryMatrix);
    Solver.addClue(4, 5, 9, binaryMatrix);
    Solver.addClue(5, 0, 7, binaryMatrix);
    Solver.addClue(5, 8, 8, binaryMatrix);
    Solver.addClue(6, 4, 2, binaryMatrix);
    Solver.addClue(7, 5, 3, binaryMatrix);
    Solver.addClue(8, 1, 9, binaryMatrix);
    binaryMatrix.insert(binaryMatrix.begin(), head);
    // printBinaryMatrix(binaryMatrix);
    algoX.createGrid(binaryMatrix, Matrix);

    algoX.search(0, Solution);
    // // We need to liberate all the memory cases we have allocated during the whole process
    // // create 4-way linked matrix
    for (int i = 0; i <= nRow; i++)
    {
        for (int j = 0; j < nCol; j++)
        {
            delete Matrix[i][j];
        }
    }
    return 0;
}