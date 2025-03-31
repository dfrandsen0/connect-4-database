all: clean connect

connect: connect.cpp state.cpp node.cpp
	g++ -g -Wall -o connect connect.cpp node.cpp state.cpp utility.cpp mcts.cpp

clean:
	rm -f connect
