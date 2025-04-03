all: connect

connect: connect.cpp mcts.cpp play.cpp utility.cpp
	g++ -g -Wall -o connect connect.cpp node.cpp state.cpp utility.cpp mcts.cpp play.cpp -lm

clean:
	rm -f connect
