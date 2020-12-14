CC = g++ -std=c++11
CFLAGS = -I./include 
SRC = src
LIB = lib

sudoku:
	${CC} -c ${SRC}/sudoku_generator.cpp -o generator.o ${CFLAGS}
	${CC} -c ${SRC}/sudoku_solver.cpp -o solver.o ${CFLAGS}
	ar cr ${LIB}/libsudoku_solver.a solver.o generator.o
	rm solver.o generator.o

example:
	${CC} -c ${SRC}/example.cpp -o example.o ${CFLAGS}
	${CC} example.o ${LIB}/libsudoku_solver.a -o example
	rm example.o

clean:
	rm example
    
