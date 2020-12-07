#ifndef SUDOKUCELL_H
#define SUDOKUCELL_H

#include <settings.h>

class SudokuCell {
public:
	SudokuCell();
    int count();
    void setUsed(int used);
    void use(int value);
	int value();

private:
    int m_used = 0;
    int m_count = SUDOKU_SIZE;
};

#endif /*SUDOKUCELL_H*/
