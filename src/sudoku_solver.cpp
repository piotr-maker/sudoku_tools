#include <sudoku_solver.h>

SudokuSolver::SudokuSolver(int (*board)[SUDOKU_SIZE][SUDOKU_SIZE]) : m_board(board) {
    for(int i = 0; i < SUDOKU_SIZE; i++) { 
        this->row_used[i] = this->rowGetUsed(i);
        this->col_used[i] = this->colGetUsed(i);
        if(i % 3 == 0) {
            for(int j = 0; j <= 6; j+=3) this->sector_used[SECTOR(i, j)] = this->sectorGetUsed(i, j);
        }
    }
}


void SudokuSolver::solve() {
    int value;
    int count;
    int used;
    bool simple = true;
	bool solved;

    while(simple) {
		simple = false;
		solved = true;
    	for(int r = 0; r < SUDOKU_SIZE; r++) {
			if(this->checkRow(r)) simple = true;
        	for(int c = 0; c < SUDOKU_SIZE; c++) {
        	    if((r % 3) == 0 && (c % 3) == 0) if(this->checkSector(r, c)) simple = true;
				if(r == 0) if(this->checkCol(c)) simple = true;
        	    if((*m_board)[r][c] == 0) {
        	        count = 0;
        	        used = row_used[r] | col_used[c] | sector_used[SECTOR(r, c)];
        	        for(int i = 0; i < SUDOKU_SIZE; i++) if(!(used & (1<<i))) {count += 1; value = i;} 
        	        if(count == 1) {
        	            (*m_board)[r][c] = value + 1;
        	            row_used[r] |= (1<<value);
        	            col_used[c] |= (1<<value);
        	            sector_used[SECTOR(r, c)] |= (1<<value);
						simple = true;
        	        } else solved = false;
        	    }
        	}
    	}
    }
}


int SudokuSolver::colGetUsed(int col) {
    int used = 0;

    for(int r = 0; r < SUDOKU_SIZE; r++)
        if((*m_board)[r][col]) used |= (1<<((*m_board)[r][col])-1); 
    return used;
}


int SudokuSolver::rowGetUsed(int row) {
    int used = 0;

    for(int c = 0; c < SUDOKU_SIZE; c++)
        if((*m_board)[row][c]) used |= (1<<((*m_board)[row][c])-1); 
    return used;
}


int SudokuSolver::sectorGetUsed(int row, int col) {
    int used = 0;
    col = col / COLS_IN_SEC * COLS_IN_SEC;
    row = row / COLS_IN_SEC * COLS_IN_SEC;
    
    for(int r = row; r < row + COLS_IN_SEC; r++) {
        for(int c = col; c < col + COLS_IN_SEC; c++) {
            if((*m_board)[r][c]) used |= (1<<((*m_board)[r][c])-1);
        }
    }    
    
    return used;
}


bool SudokuSolver::checkCol(int col) {
	int used;
	int count;
	int row_index;
	bool found = false;

	for(int i = 0; i < SUDOKU_SIZE; i++) {
		if(col_used[col] & (1<<i)) continue;
		count = 0;
		for(int r = 0; r < SUDOKU_SIZE; r++) {
			if((*m_board)[r][col] != 0) continue;
			used = row_used[r] | col_used[col] | sector_used[SECTOR(r, col)];
			if(!(used & (1<<i))) {
				count += 1;
				row_index = r;
			}
		}

		if(count == 1) {
			(*m_board)[row_index][col] = i + 1;
            row_used[row_index] |= (1<<(i));
            col_used[col] |= (1<<(i));
            sector_used[SECTOR(row_index, col)] |= (1<<(i));
			found = true;
		}
	}

	return found;
}


bool SudokuSolver::checkRow(int row) {
	int used;
	int count;
	int col_index;
	bool found = false;

	for(int i = 0; i < SUDOKU_SIZE; i++) {
		if(row_used[row] & (1<<i)) continue;
		count = 0;
		for(int c = 0; c < SUDOKU_SIZE; c++) {
			if((*m_board)[row][c] != 0) continue;
			used = row_used[row] | col_used[c] | sector_used[SECTOR(row, c)];
			if(!(used & (1<<i))) {
				count += 1;
				col_index = c;
			}
		}

		if(count == 1) {
			(*m_board)[row][col_index] = i + 1;
            row_used[row] |= (1<<(i));
            col_used[col_index] |= (1<<(i));
            sector_used[SECTOR(row, col_index)] |= (1<<(i));
			found = true;
		}
	}

	return found;
}


bool SudokuSolver::checkSector(int row, int col) {
    int col_index;
    int row_index;
    int sector = SECTOR(row, col);
    int count[SUDOKU_SIZE];
    int used;
	bool found = false;

    for(int i = 0; i < SUDOKU_SIZE; i++) count[i] = 0;

    for(int i = 0; i < SUDOKU_SIZE; i++) {
        if(sector_used[sector] & (1<<i)) continue;
        for(int r = 0; r < COLS_IN_SEC; r++) {
            for(int c = 0; c < COLS_IN_SEC; c++) {
                if((*m_board)[row + r][col + c] != 0) continue;
                used = row_used[row + r] | col_used[col + c] | sector_used[sector];
                if(!(used & (1<<i))) {
                    count[i] += 1;
                    row_index = row + r;
                    col_index = col + c;
                }
            }
        }

        if(count[i] == 1) {
            (*m_board)[row_index][col_index] = i + 1;
            row_used[row_index] |= (1<<(i));
            col_used[col_index] |= (1<<(i));
            sector_used[sector] |= (1<<(i));
			found = true;
        }
    }

	return found;
}
