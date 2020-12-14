#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <settings.h>
#include <cstdio>

class SudokuSolver {
public:
	SudokuSolver(int (*board)[SUDOKU_SIZE][SUDOKU_SIZE]);
	void solve();

private:
	struct State {
		int used_in_col[SUDOKU_SIZE];
		int used_in_row[SUDOKU_SIZE];
		int used_in_square[SUDOKU_SIZE];
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
