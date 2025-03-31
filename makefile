all: connect

connect: connect.cpp state.cpp node.cpp
	g++ -g -Wall -o connect connect.cpp node.cpp state.cpp

clean:
	rm -f connect
