#include <stdio.h>
#include <sudoku_solver.h>

void print(int board[SUDOKU_SIZE][SUDOKU_SIZE]) {
	int separators = COLS_IN_SEC + 1;
	int row;
	int col;

    for(int r = 0; r < SUDOKU_SIZE + separators; r++) {
		for(int c = 0; c < SUDOKU_SIZE + separators; c++) {
			row = r - (r / 4 + 1);
			col = c - (c / 4 + 1);
			if(r % 4) {
				if(c % 4 == 0) printf(" | ");
				else if(board[row][col]) printf(" %d ", board[row][col]);
				else printf("   ");
			} else printf(" - ");
		}
		printf("\n");
	}
}

int board_medium[SUDOKU_SIZE][SUDOKU_SIZE] = { 
    {0,1,0, 0,0,0, 0,7,0},
    {0,4,0, 0,1,0, 0,9,0},
    {0,8,0, 9,0,2, 0,3,0},
    {0,6,0, 0,0,0, 0,8,0},
    {0,0,5, 0,0,0, 2,0,0},
    {8,0,0, 4,0,7, 0,0,6},
    {0,7,0, 0,0,0, 0,5,0},
    {0,0,2, 8,0,5, 4,0,0},
    {0,0,0, 7,0,9, 0,0,0}
};

int board_hard[SUDOKU_SIZE][SUDOKU_SIZE] = { 
    {3,0,5, 0,0,6, 9,0,0},
    {1,0,0, 0,0,0, 0,0,0},
    {4,9,0, 0,0,2, 0,0,5},
    {0,0,3, 1,8,0, 0,9,7},
    {0,0,0, 0,7,0, 0,0,0},
    {7,1,0, 0,2,5, 4,0,0},
    {9,0,0, 7,0,0, 0,2,8},
    {0,0,0, 0,0,0, 0,0,4},
    {0,0,6, 2,0,0, 5,0,9}
};

int board_very_hard[SUDOKU_SIZE][SUDOKU_SIZE] = { 
    {0,0,9, 0,0,0, 0,0,1},
    {0,0,5, 1,8,0, 0,7,0},
    {0,4,0, 0,0,2, 0,0,0},
    {0,0,0, 0,0,0, 5,3,0},
    {9,6,0, 0,0,4, 8,0,0},
    {0,0,0, 0,0,0, 6,9,0},
    {0,8,0, 0,0,5, 0,0,0},
    {0,0,4, 2,3,0, 0,6,0},
    {0,0,1, 0,0,0, 0,0,3}
};

int board_hardest[SUDOKU_SIZE][SUDOKU_SIZE] = { 
    {8,0,0, 0,0,0, 0,0,0},
    {0,0,3, 6,0,0, 0,0,0},
    {0,7,0, 0,9,0, 2,0,0},
    {0,5,0, 0,0,7, 0,0,0},
    {0,0,0, 0,4,5, 7,0,0},
    {0,0,0, 1,0,0, 0,3,0},
    {0,0,1, 0,0,0, 0,6,8},
    {0,0,8, 5,0,0, 0,1,0},
    {0,9,0, 0,0,0, 4,0,0}
};

int main(){
	print(board_hard);
    SudokuSolver solver(&board_hard);
    solver.solve();
    printf("\n");
    print(board_hard);
	return 0;
}
