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
	struct State {
		int cols_used[SUDOKU_SIZE];
		int rows_used[SUDOKU_SIZE];
		int sectors_used[SUDOKU_SIZE];
		int (*board)[SUDOKU_SIZE][SUDOKU_SIZE];
	};

	State main;
	State backup;

    int backup_board[SUDOKU_SIZE][SUDOKU_SIZE];

	bool simpleSolve(int (*board)[SUDOKU_SIZE][SUDOKU_SIZE]);
	void saveState();
	void restoreState();

    int colGetUsed(int col);
    int rowGetUsed(int row);
    int sectorGetUsed(int row, int col);
    
    bool checkCol(int col);    
    bool checkRow(int row);
    bool checkSector(int row, int col);
};

#endif /*SUDOKUSOLVER_H*/
