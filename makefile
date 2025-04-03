all: connect

connect: connect.cpp mcts.cpp ai.cpp
	g++ -g -Wall -o connect connect.cpp node.cpp state.cpp utility.cpp mcts.cpp play.cpp player.cpp ai.cpp human.cpp -lm

clean:
	rm -f connect
