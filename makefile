all: play

play: connect.cpp state.cpp node.cpp
	g++ -g -Wall -o play connect.cpp node.cpp state.cpp

clean:
	rm -f play
