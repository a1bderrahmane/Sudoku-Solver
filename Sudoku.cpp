#include "Sudoku.h"
using namespace std;

Sudoku::Sudoku() {}

Sudoku::~Sudoku(){};


void Sudoku::constructBinaryMatrix(vector<vector<int>> &binaryMatrix)
{
    addCellConstraint(binaryMatrix);
    addRowConstraint(binaryMatrix);
    addColumnConstraint(binaryMatrix);
    addBlockConstraint(binaryMatrix);
}

// This function is used to add the cell's constraint
// Each cell must be an integer between 1 and 9
void Sudoku::addCellConstraint(vector<vector<int>> &binaryMatrix)
{
    int c = 0;
    int ligne = 0;
    for (int i = 0; i < SIZE; i++, c++)
    {
        if (c > 0)
            c--; // decrement by 1 in order not to have a double incrementation of c every time we increment i
        for (int j = 0; j < SIZE; j++, c++)
        {
            for (int k = ligne; k < ligne + 9; k++) // The lines are incremented by 9
            {
                // We fill the binary matrix
                binaryMatrix[k][c] = 1;
            }
            ligne += SIZE;
        }
    }
}

void Sudoku::addRowConstraint(vector<vector<int>> &binaryMatrix)
{
    int offset = 81;
    int ligne = 0;
    int c = 0;
    for (int i = 0; i < SIZE; i++, c += SIZE)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = ligne; k < ligne + 9; k++) // The lines are incremented by 9
            {
                // We fill the binary matrix
                binaryMatrix[k][offset + c + (k % 9)] = 1;
            }
            ligne += SIZE;
        }
    }
}

void Sudoku::addColumnConstraint(vector<vector<int>> &binaryMatrix)
{
    int offset = 162;
    int ligne = 0;
    int c = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = ligne; k < ligne + 9; k++, c++) // The lines are incremented by 9
            {
                // We fill the binary matrix
                binaryMatrix[k][offset + c] = 1;
            }
            ligne += SIZE;
        }
        c = 0;
    }
}

void Sudoku::addBlockConstraint(std::vector<std::vector<int>> &binaryMatrix)
{
    int offset = 243;
    int ligne = 0;
    int c = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int block = getBlockNumber(i, j);
            c = block * SIZE;
            for (int k = ligne; k < ligne + 9; k++, c++) // The lines are incremented by 9
            {
                // We fill the binary matrix
                binaryMatrix[k][offset + c] = 1;
            }
            ligne += SIZE;
        }
    }
}

int Sudoku::getBlockNumber(int i, int j) const
{
    int blockSide = 3; // Side length of each block in a 9x9 Sudoku
    int blockRow = i / blockSide;
    int blockCol = j / blockSide;
    int blockNumber = blockRow * blockSide + blockCol;
    return blockNumber;
}

void Sudoku::addClue(int i, int j, int clue, vector<vector<int>> &binaryMatrix)
{
    changeCellConstraint(i, j, clue, binaryMatrix);
    changeRowConstraint(i, j, clue, binaryMatrix);
    changeColumnConstraint(i, j, clue, binaryMatrix);
    changeBlockConstraint(i, j, clue, binaryMatrix);
}

void Sudoku::changeCellConstraint(int i, int j, int clue, vector<vector<int>> &binaryMatrix)
{
    int colonne = i * SIZE + j;
    int ligne = colonne * SIZE;
    for (int k = ligne; k < ligne + SIZE; k++)
    {
        if (k % SIZE != clue - 1)
        {
            binaryMatrix[k][colonne] = 0;
        }
    }
}

void Sudoku::changeRowConstraint(int i, int j, int clue, vector<vector<int>> &binaryMatrix)
{
    int offset = 81;
    for (int c = 0; c < SIZE; c++)
    {

        int colonne = (i * SIZE);
        int ligne = (i * SIZE + c) * SIZE;
        for (int k = ligne; k < ligne + SIZE; k++, colonne++)
        {
            if (c != j && colonne % SIZE == clue - 1)
            {
                binaryMatrix[k][offset + colonne] = 0;
            }
            else if (colonne % SIZE != clue - 1 && c == j)
            {
                binaryMatrix[k][offset + colonne] = 0;
            }
        }
    }
}

void Sudoku::changeColumnConstraint(int i, int j, int clue, vector<vector<int>> &binaryMatrix)
{
    int offset = 162; // Offset accounts for other types of constraints in the binary matrix

    for (int r = 0; r < SIZE; r++)
    {
        // Calculate the start of the row in the binary matrix for each row r at column j
        int ligne = (r * SIZE + j) * SIZE;

        for (int val = 0; val < SIZE; val++)
        {                                         // Iterate over all possible values 1-9 (0-8 zero-indexed)
            int index = ligne + val;              // Row index in the binary matrix
            int column = offset + j * SIZE + val; // Column in the binary matrix for the value

            // Clear out possibilities for other numbers in the same column
            if ((r != i && val == clue - 1) || (r == i && val != clue - 1))
            {
                binaryMatrix[index][column] = 0;
            }
        }
    }
}

void Sudoku::changeBlockConstraint(int i, int j, int clue, vector<vector<int>> &binaryMatrix)
{
    int offset = 243; // Assuming this offset is used for block constraints
    int myBlock = getBlockNumber(i, j);

    for (int r = 0; r < SIZE; r++)
    {
        for (int c = 0; c < SIZE; c++)
        {
            if (getBlockNumber(r, c) == myBlock)
            {
                int ligne = (r * SIZE + c) * SIZE; // Calculate the start of the row in the binary matrix

                for (int val = 0; val < SIZE; val++)
                {
                    int index = ligne + val;                    // Row index in the binary matrix
                    int column = offset + myBlock * SIZE + val; // Column in the binary matrix for the block constraint

                    if (r == i && c == j)
                    {
                        // If it's the cell where the clue is placed, we set only the correct clue
                        if (val != clue - 1)
                        {
                            binaryMatrix[index][column] = 0;
                        }
                    }
                    else
                    {
                        // Clear the clue value from all other cells in the block
                        if (val == clue - 1)
                        {
                            binaryMatrix[index][column] = 0;
                        }
                    }
                }
            }
        }
    }
}

void Sudoku::SolvePuzzle(vector<int> &rowIDs, vector<int> &values)
{
    int val = 0;
    for (auto &row : rowIDs)
    {
        val = (row) % 9;
        values.push_back(val);
    }
}