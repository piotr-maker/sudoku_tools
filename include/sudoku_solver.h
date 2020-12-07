#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#define SUDOKU_SIZE 9
#define COLS_IN_SEC 3

#define SECTOR(row,column)	(((row/3) * 3) + (column/3))

#include <cstdio>

class SudokuSolver {
public:
	SudokuSolver(int (*board)[SUDOKU_SIZE][SUDOKU_SIZE]);
	void solve();

private:
    int (*m_board)[SUDOKU_SIZE][SUDOKU_SIZE];

    int col_used[SUDOKU_SIZE];
    int row_used[SUDOKU_SIZE];
    int sector_used[SUDOKU_SIZE];

    int colGetUsed(int col);
    int rowGetUsed(int row);
    int sectorGetUsed(int row, int col);
    
    bool checkCol(int col);    
    bool checkRow(int row);
    bool checkSector(int row, int col);
};

#endif /*SUDOKUSOLVER_H*/
