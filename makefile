all: ticTacToe.x

ticTacToe.x: skrod_ticTacToe.o
	g++ -o ticTacToe.x skrod_ticTacToe.o
skrod_ticTacToe.o: skrod_ticTacToe.cpp
	g++ -c skrod_ticTacToe.cpp
clean:
	rm -rf *.o
	rm -rf *~
	rm -rf *.x
