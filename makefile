all: connect

connect: connect.cpp
	g++ -IplayerSources -Ifunctions -Istructures -g -Wall -o connect connect.cpp structures/node.cpp structures/state.cpp functions/utility.cpp functions/mcts.cpp functions/play.cpp playerSources/player.cpp playerSources/ai.cpp playerSources/human.cpp playerSources/guiPlayer.cpp serverApp/serverConnect.cpp serverApp/coder.cpp -lm

clean:
	rm -f connect

#g++ -IplayerSources -Ifunctions -Istructures -IserverApp -g -Wall -o connect.exe connect.cpp structures/node.cpp structures/state.cpp functions/utility.cpp functions/mcts.cpp functions/play.cpp playerSources/player.cpp playerSources/ai.cpp playerSources/human.cpp playerSources/guiPlayer.cpp serverApp/serverConnect.cpp serverApp/coder.cpp -lm -lws2_32
