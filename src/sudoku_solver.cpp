#include <sudoku_solver.h>

SudokuSolver::SudokuSolver(int (*board)[SUDOKU_SIZE][SUDOKU_SIZE]) {
	this->main.board = board;
    for(int i = 0; i < SUDOKU_SIZE; i++) { 
        this->main.used_in_row[i] = this->rowGetUsed(i);
        this->main.used_in_col[i] = this->colGetUsed(i);
        if(i % 3 == 0) {
            for(int j = 0; j <= 6; j+=3) this->main.used_in_square[SQUARE(i, j)] = this->sectorGetUsed(i, j);
        }
    }
}


void SudokuSolver::solve() {
	bool solved;
	int used;
	int count;
	int value;

    solved = this->simpleSolve(this->main.board);
	if(!solved) this->saveState();
	for(int r = 0; r < SUDOKU_SIZE; r++) {
		for(int c = 0; c < SUDOKU_SIZE; c++) {
			count = 0;
			used = this->main.used_in_row[r] | this->main.used_in_col[c] | this->main.used_in_square[SQUARE(r, c)];
			for(int i = 0; i < SUDOKU_SIZE; i++) if(!(used & (1<<i))) {count += 1; value = i;}
			if(count == 2) {
				(*this->main.board)[r][c] = value + 1;
				this->main.used_in_col[c] |= (1<<value);
				this->main.used_in_row[r] |= (1<<value);
				this->main.used_in_square[SQUARE(r, c)] |= (1<<value);
				solved = this->simpleSolve(this->main.board);
				if(solved) goto end;
				else this->restoreState();
			}  
		}
	}

	end:;
}


bool SudokuSolver::simpleSolve(int (*board)[SUDOKU_SIZE][SUDOKU_SIZE]) {
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
        	    if((*this->main.board)[r][c] == 0) {
        	        count = 0;
        	        used = this->main.used_in_row[r] | this->main.used_in_col[c] | this->main.used_in_square[SQUARE(r, c)];
        	        for(int i = 0; i < SUDOKU_SIZE; i++) if(!(used & (1<<i))) {count += 1; value = i;} 
        	        if(count == 1) {
        	            (*this->main.board)[r][c] = value + 1;
        	            this->main.used_in_row[r] |= (1<<value);
        	            this->main.used_in_col[c] |= (1<<value);
        	            this->main.used_in_square[SQUARE(r, c)] |= (1<<value);
						simple = true;
        	        } else solved = false;
        	    }
        	}
    	}
    }

	return solved;
}

void SudokuSolver::saveState() {
	for(int r = 0; r < SUDOKU_SIZE; r++) {
		this->backup.used_in_col[r] = this->main.used_in_col[r];
		this->backup.used_in_row[r] = this->main.used_in_row[r];
		this->backup.used_in_square[r] = this->main.used_in_square[r];
		for(int c = 0; c < SUDOKU_SIZE; c++) backup_board[r][c] = (*this->main.board)[r][c];
	}
}

void SudokuSolver::restoreState() {
	for(int r = 0; r < SUDOKU_SIZE; r++) {
		this->main.used_in_col[r] = this->backup.used_in_col[r];
		this->main.used_in_row[r] = this->backup.used_in_row[r];
		this->main.used_in_square[r] = this->backup.used_in_square[r];
		for(int c = 0; c < SUDOKU_SIZE; c++) (*this->main.board)[r][c] = backup_board[r][c];
	}
}

int SudokuSolver::colGetUsed(int col) {
    int used = 0;

    for(int r = 0; r < SUDOKU_SIZE; r++)
        if((*this->main.board)[r][col]) used |= (1<<((*this->main.board)[r][col])-1); 
    return used;
}


int SudokuSolver::rowGetUsed(int row) {
    int used = 0;

    for(int c = 0; c < SUDOKU_SIZE; c++)
        if((*this->main.board)[row][c]) used |= (1<<((*this->main.board)[row][c])-1); 
    return used;
}


int SudokuSolver::sectorGetUsed(int row, int col) {
    int used = 0;
    col = col / COLS_IN_SEC * COLS_IN_SEC;
    row = row / COLS_IN_SEC * COLS_IN_SEC;
    
    for(int r = row; r < row + COLS_IN_SEC; r++) {
        for(int c = col; c < col + COLS_IN_SEC; c++) {
            if((*this->main.board)[r][c]) used |= (1<<((*this->main.board)[r][c])-1);
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
		if(this->main.used_in_col[col] & (1<<i)) continue;
		count = 0;
		for(int r = 0; r < SUDOKU_SIZE; r++) {
			if((*this->main.board)[r][col] != 0) continue;
			used = this->main.used_in_row[r] | this->main.used_in_col[col] | this->main.used_in_square[SQUARE(r, col)];
			if(!(used & (1<<i))) {
				count += 1;
				row_index = r;
			}
		}

		if(count == 1) {
			(*this->main.board)[row_index][col] = i + 1;
            this->main.used_in_row[row_index] |= (1<<(i));
            this->main.used_in_col[col] |= (1<<(i));
            this->main.used_in_square[SQUARE(row_index, col)] |= (1<<(i));
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
		if(this->main.used_in_row[row] & (1<<i)) continue;
		count = 0;
		for(int c = 0; c < SUDOKU_SIZE; c++) {
			if((*this->main.board)[row][c] != 0) continue;
			used = this->main.used_in_row[row] | this->main.used_in_col[c] | this->main.used_in_square[SQUARE(row, c)];
			if(!(used & (1<<i))) {
				count += 1;
				col_index = c;
			}
		}

		if(count == 1) {
			(*this->main.board)[row][col_index] = i + 1;
            this->main.used_in_row[row] |= (1<<(i));
            this->main.used_in_col[col_index] |= (1<<(i));
            this->main.used_in_square[SQUARE(row, col_index)] |= (1<<(i));
			found = true;
		}
	}

	return found;
}


bool SudokuSolver::checkSector(int row, int col) {
    int col_index;
    int row_index;
    int sector = SQUARE(row, col);
    int count[SUDOKU_SIZE];
    int used;
	bool found = false;

    for(int i = 0; i < SUDOKU_SIZE; i++) count[i] = 0;

    for(int i = 0; i < SUDOKU_SIZE; i++) {
        if(this->main.used_in_square[sector] & (1<<i)) continue;
        for(int r = 0; r < COLS_IN_SEC; r++) {
            for(int c = 0; c < COLS_IN_SEC; c++) {
                if((*this->main.board)[row + r][col + c] != 0) continue;
                used = this->main.used_in_row[row + r] | this->main.used_in_col[col + c] | this->main.used_in_square[sector];
                if(!(used & (1<<i))) {
                    count[i] += 1;
                    row_index = row + r;
                    col_index = col + c;
                }
            }
        }

        if(count[i] == 1) {
            (*this->main.board)[row_index][col_index] = i + 1;
            this->main.used_in_row[row_index] |= (1<<(i));
            this->main.used_in_col[col_index] |= (1<<(i));
            this->main.used_in_square[sector] |= (1<<(i));
			found = true;
        }
    }

	return found;
}
