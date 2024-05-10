#include "X.h"
using namespace std;



X::X()
{
    // Allocation of memory to the header
    header = new Node();
}

int X::getRight(int i)
{
    int res = (i + 1) % nCol;
    return res;
}
int X::getLeft(int i)
{
    int res;
    if (i - 1 >= 0)
        res = i - 1;
    else
        res = nCol - 1;
    return res;
}
int X::getDown(int i)
{
    int res = (i + 1) % (nRow + 1);
    return res;
}
int X::getUp(int i)
{
    int res;
    if (i - 1 == -1)
        res = nRow - 1;
    else
        res = i - 1;
    return res;
}

void X::setRowsColumns(int row, int column)
{
    this->nRow = row;
    this->nCol = column;
}

// Representation of the problem in the form of a grid of Nodes (One big mesh of Nodes linked from all 4 sides)
Node *X::createGrid(vector<vector<int>>& problemMatrix, Node *(&Matrix)[MAX_ROW + 1][MAX_COL])
{
    // We will add a row for the headers
    for (int i = 0; i <= nRow; i++)
    {
        for (int j = 0; j < nCol; j++)
        {
            if (problemMatrix[i][j] == 1)
            {
                // We indicate the column's header
                Matrix[i][j]->column = Matrix[0][j];
                Matrix[i][j]->colId = j;
                Matrix[i][j]->rowId = i;

                // Increment the node count for the column header if not the first row
                if (i > 0)
                {
                    Matrix[0][j]->nodeCount++;
                }

                // Set the right pointer of the current node to the next node with value 1 in the same row
                int b = j;
                do
                {
                    b = getRight(b);
                } while (problemMatrix[i][b] == 0 && b != j);
                Matrix[i][j]->right = Matrix[i][b];

                // Set the left pointer of the current node to the previous node with value 1 in the same row
                b = j;
                do
                {
                    b = getLeft(b);
                } while (problemMatrix[i][b] == 0 && b != j);
                Matrix[i][j]->left = Matrix[i][b];

                // Set the up pointer of the current node to the node above with value 1 in the same column
                int a = i;
                do
                {
                    a = getUp(a);
                } while (problemMatrix[a][j] == 0 && a != i);
                Matrix[i][j]->up = Matrix[a][j];

                // Set the down pointer of the current node to the node below with value 1 in the same column
                a = i;
                do
                {
                    a = getDown(a);
                } while (problemMatrix[a][j] == 0 && a != i);
                Matrix[i][j]->down = Matrix[a][j];
            }
        }
    }

    // Set the header's right pointer to the first node in the grid
    header->right = Matrix[0][0];
    // Set the header's left pointer to the last node in the grid
    header->left = Matrix[0][nCol - 1];
    // Set the left pointer of the first node to the header
    Matrix[0][0]->left = header;
    // Set the right pointer of the last node to the header
    Matrix[0][nCol - 1]->right = header;

    // Return the header of the grid
    return header;
}

// This function will cover the column we want to hide
// It will eventually cover also all the links this column has with the other columns
void X::cover(Node *target)
{
    // We use the column header to hide the whole column
    target = target->column;

    // the header of the column is hided
    (target->left)->right = target->right;
    (target->right)->left = target->left;

    // We create a temporary Node
    // We will use it to make the traversal of the column
    // We will do here the rows traversal
    Node *i = target->down;
    // while we don't get back to where we started
    while (i != target)
    {
        // We create another temporary Node that we will use to do the traversal of the connected Nodes at the same row
        Node *j = i->right;
        // while we're not back to where we started
        while (j != i)
        {
            // We hide here the nodes connected horizontally
            j->column->nodeCount--;
            (j->down)->up = j->up;
            (j->up)->down = j->down;
            j = j->right;
        }
        i = i->down;
    }
}


// This function will reinsert back the column we have hided earlier
// This is possible because the nodes of the column are still connected vertically
// We need to connect back the nodes horizontally
void X::uncover(Node *target)
{
    target = target->column;
    // temporary node to the traversal vertically
    Node *i = target->up;
    while (i != target)
    {
        // temporary node to do the traversal horizontally
        Node *j = i->left;
        while (j != i)
        {
            // We start by incrementing the number of nodes in the column
            j->column->nodeCount++;
            // connect back the nodes horizontally
            (j->up)->down = j;
            (j->down)->up = j;

            j = j->left;
        }
        i = i->up;
    }
    // the column header is back to its place
    (target->left)->right = target;
    (target->right)->left = target;
}

// Function to print the solution
void X::printSolution(vector<struct Node *> &Solution)
{
    ofstream outFile("Solution.txt");  // Create an output file stream

    if (!outFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    outFile << "Solution to the problem: " <<endl;
    int idx = 0;
    int length = Solution.size();
    
    for (auto &it : Solution)
    {
        outFile << it->rowId;
        if (idx != length - 1)
            outFile << " U "; // "U" is used to separate values
        else
            outFile <<endl;
        idx++;
    }

    outFile.close();  // Close the file
}

// Function to find the column containing the least number of nodes
Node *X::getMinColumn()
{
    // Start from the header's right node
    Node *h = header->right;
    // Initialize the minimum column to the first column
    Node *min_col = h;
    // Move to the second column
    h = h->right;

    // Loop through all columns starting from the second one
    do
    {
        // If the current column has fewer nodes than the current minimum column
        if (h->nodeCount < min_col->nodeCount)
        {
            // Update the minimum column to the current column
            min_col = h;
        }
        // Move to the next column
        h = h->right;
        // Continue until we reach the header node again, indicating a full loop
    } while (h != header);

    // Return the column with the minimum number of nodes
    return min_col;
}

// the Principal function
void X::search(int k, vector<struct Node *> &Solution)
{
    // cout<<"k ="<<k<<endl;
    // If there are no more new elements to explore
    // we print the current solution
    if ((header->right) == header)
    {
        printSolution(Solution);
        return;
    }
    // We determinastically select the column with the least number of nodes
    Node *column = getMinColumn();
    // The column selected is covered
    cover(column);
    Node *r = column->down;
    while (r != column)
    {
        // The node is added to the solution vector
        Solution.push_back(r);
        Node *j = r->right;
        while (j != r)
        {
            // we cover all the elements connected to the node selected
            cover(j);
            j = j->right;
        }
        // recursively do the same thing
        search(k + 1, Solution);
        // If no solution is found
        // We do the backtracking
        r = Solution.back();
        Solution.pop_back();
        column = r->column;
        j = r->left;
        while (j != r)
        {
            uncover(j);
            j = j->left;
        }
        r = r->down;
    }
    uncover(column);
}

X::~X()
{
    // We free the memory allocted previously to header
    delete header;
}

