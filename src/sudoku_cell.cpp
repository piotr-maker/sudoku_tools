#include <sudoku_cell.h>

SudokuCell::SudokuCell() {;}

int SudokuCell::count() { return m_count; }

void SudokuCell::setUsed(int used) {
    m_used = used;
    m_count = 0;
    for(int i = 0; i < SUDOKU_SIZE; i++) if(m_used & (1<<i)) m_count += 1; 
}

void SudokuCell::use(int value) {
    if(value <= SUDOKU_SIZE && value > 0) {
        value -= 1;
        if(!(m_used & (1<<value))) {
            m_used |= (1<<value);
            m_count -= 1;
        }
    }
}

int SudokuCell::value() {
    if(m_count == 1) {
        for(int i = 0; i < SUDOKU_SIZE; i++) {
            if(m_used & (1<<i)) return i + 1;
        }
    }
    
    return 0;
}
