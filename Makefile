CC = g++ -std=c++11
CFLAGS = -I./include 
SRC = src
LIB = lib

sudoku:
	${CC} -c ${SRC}/sudoku_solver.cpp -o sudoku.o ${CFLAGS}
	ar cr ${LIB}/libsudoku_solver.a sudoku.o
	rm sudoku.o

	#${CC} -c ${SRC}/sudoku_cell.cpp -o cell.o ${CFLAGS}
	#ar cr ${LIB}/libsudoku_solver.a sudoku.o cell.o
	#rm sudoku.o cell.o

example:
	${CC} -c ${SRC}/example.cpp -o example.o ${CFLAGS}
	${CC} example.o ${LIB}/libsudoku_solver.a -o example
	rm example.o

clean:
	rm example
    
