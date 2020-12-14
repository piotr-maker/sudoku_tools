#include "sudoku_generator.h"

SudokuGenerator::SudokuGenerator(int (*board)[SUDOKU_SIZE][SUDOKU_SIZE]) : m_board(board) {}

int SudokuGenerator::generate() {
	int count = 0;
	bool generated;

	srand(time(NULL));

	do {
		generated = true;
		for(int i = 0; i < SUDOKU_SIZE; i++) {
			used_in_row[i] = 0;
			used_in_col[i] = 0;
			used_in_square[i] = 0;
		}

		for(int r = 0; r < SUDOKU_SIZE; r++) {
			for(int c = 0; c < SUDOKU_SIZE; c+=3) {
				if(!setPart(r, c)) { generated = false; goto end;}
			}
		}

		end:
		count += 1;
	} while(!generated);

	return count;
}


bool SudokuGenerator::isValid() {
	int col[SUDOKU_SIZE];
	int row[SUDOKU_SIZE];
	int square[SUDOKU_SIZE];
	int value;

	for(int i = 0; i < SUDOKU_SIZE; i++) {
		col[i] = 0;
		row[i] = 0;
		square[i] = 0;
	}

	for(int r = 0; r < SUDOKU_SIZE; r++) {
		for(int c = 0; c < SUDOKU_SIZE; c++) {
			value = (*m_board)[r][c] - 1;
			col[c] |= (1<<value);
			row[r] |= (1<<value);
			square[SQUARE(r, c)] |= (1<<value);
		}
	}

	for(int i = 0; i < SUDOKU_SIZE; i++) {
		if((col[i] != 0x1FF) || (row[i] != 0x1FF) || (square[i] != 0x1FF)) return false; 
	}

	return true;
}

int SudokuGenerator::getRand(int used) {
	int temp, result;	
	int index = -1;
	int count = 0;

	for(int i = 0; i < SUDOKU_SIZE; i++) if(!(used & (1<<i))) {count+= 1; result = i;}
	if(count == 1) return result;
	else if(count == 0) return -1;
	temp = (rand() % count) + 1;

	do {
		index += 1;
		if(!(used & (1<<index))) temp -= 1;
	} while(temp > 0);

	result = index;
	return result;	
}


void SudokuGenerator::setValue(int row, int col, int val) {
	(*m_board)[row][col] = val + 1;
	used_in_row[row] |= (1<<val);
	used_in_col[col] |= (1<<val);
	used_in_square[SQUARE(row, col)] |= (1<<val);
}


bool SudokuGenerator::setPart(int row, int col) {
	int value;
	int mantadory = 0;
	int used;
	int temp;

	for(int i = 0; i < 3; i++) (*m_board)[row][col + i] = 0;

	if((row % 3) == 1 && col == 3) {
		mantadory = used_in_square[SQUARE(row, 6)] & ~used_in_row[row];
		for(int i = 0; i < SUDOKU_SIZE; i++) {
			if(mantadory & (1<<i)) {
				for(int j = 0; j < 3; j++) {
					if((!(used_in_col[col+j] & (1<<i))) && (*m_board)[row][col+j] == 0) temp = j;
				}

				setValue(row, col + temp, i); 
			}
		}
	}

	used = used_in_row[row] | used_in_square[SQUARE(row, col)];
	for(int i = 0; i < 3; i++) {
		if((*m_board)[row][col+i] != 0) continue;
		value = getRand(used | used_in_col[col+i]);
		if(value == -1) {
			int cur_index = col + i;
			int swap_index = cur_index;
			int swap;
			while(swap_index > 0) {
				swap_index -= 1;
				swap = (*m_board)[row][swap_index] - 1;
				if(!(used_in_col[cur_index] & (1<<swap))) {
					temp = getRand(used | used_in_col[swap_index]);
					if(temp != -1) {
						value = swap;
						used_in_square[SQUARE(row, swap_index)] &= ~(1<<swap);
						used_in_col[swap_index] &= ~(1<<swap);
						used_in_square[SQUARE(row, swap_index)] |= (1<<temp);
						used_in_col[swap_index] |= (1<<temp);
						used |= (1<<temp);
						(*m_board)[row][swap_index] = temp + 1;
						break;
					}
				}
			}
		}

		if(value == -1) return false;
		else {used |= (1<<value); setValue(row, col +i, value);}
	}

	return true;
}
