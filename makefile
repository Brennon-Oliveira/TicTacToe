all:
	g++ TicTacToe.cpp -o TicTacToe.o -lraylib -lGL -lm -pthread -ldl
	./TicTacToe.o
