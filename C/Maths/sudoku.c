#include <stdio.h>
#include <math.h>

// Function to check if a number can be placed in the Sudoku grid at a particular position
int canplace(int mat[][9], int i, int j, int n, int no)
{
    // Checking if the number already exists in the same row or column
    for (int x = 0; x < n; x++)
    {
        if (mat[x][j] == no || mat[i][x] == no)
        {
            return 0;
        }
    }

    // Determining the starting index of the current sub-grid
    int rn = sqrt(n);
    int sx = (i / rn) * rn;
    int sy = (j / rn) * rn;

    // Checking if the number already exists in the sub-grid
    for (int x = sx; x < sx + rn; x++)
    {
        for (int y = sy; y < sy + rn; y++)
        {
            if (mat[x][y] == no)
            {
                return 0;
            }
        }
    }

    return 1;
}

// Function to solve the Sudoku puzzle
int solvesudoku(int mat[][9], int i, int j, int n)
{
    // Base case: If we have reached the last row, print the Sudoku solution
    if (i == n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%d ", mat[i][j]);
            }
            printf("\n");
        }
        return 1; // Return 1 to indicate a solution is found
    }

    // If we have reached the last column, move to the next row
    if (j == n)
    {
        return solvesudoku(mat, i + 1, 0, n);
    }

    // If the current cell already contains a number, move to the next column
    if (mat[i][j] != 0)
    {
        return solvesudoku(mat, i, j + 1, n);
    }

    // Try placing numbers from 1 to n in the current empty cell
    for (int no = 1; no <= n; no++)
    {
        if (canplace(mat, i, j, n, no))
        {
            mat[i][j] = no; // Place the number in the current cell

            // Recursively solve the Sudoku puzzle for the next cell
            int could = solvesudoku(mat, i, j + 1, n);
            if (could)
            {
                return 1; // Return 1 if a solution is found
            }
        }
    }

    // If no number can be placed in the current cell, backtrack
    mat[i][j] = 0;
    return 0;
}

int main()
{
    int mat[10][9];
    int n;
    scanf("%d", &n);

    // Input the Sudoku grid
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &mat[i][j]);
        }
    }

    solvesudoku(mat, 0, 0, n); // Solve the Sudoku puzzle

    return 0;
}
