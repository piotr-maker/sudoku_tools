#ifndef SUDOKUGENERATOR_H
#define SUDOKUGENERATOR_H

#include <settings.h>
#include <ctime>
#include <cstdlib>

class SudokuGenerator {
public:
	SudokuGenerator(int (*board)[SUDOKU_SIZE][SUDOKU_SIZE]);
	int generate();
	bool isValid();
	
private:
	int (*m_board)[SUDOKU_SIZE][SUDOKU_SIZE];
	int used_in_row[SUDOKU_SIZE];
	int used_in_col[SUDOKU_SIZE];
	int used_in_square[SUDOKU_SIZE];

	int getRand(int used);
	void setValue(int row, int col, int val);
	bool setPart(int row, int col);
};

#endif /*SUDOKUGENERATOR_H*/
