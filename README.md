# Connect 4 Database Project

This project is intended as a proof-of-concept. Can we use a database to improve the Monte Carlo Tree Search (MCTS) algorithm?

To run this program, simply run `python main.py`.

This project isn't finished, but it works. It is structured like so:
1. A C++ backend, running the actual algorithm and handling game logic
2. A Python frontend, handling GUI and player interaction
3. A Python server, handling requests for game information
4. A MongoDB database, storing saved simulations

## Backend

The backend is split into functions, structures, and players. If you wanted to create your own player, you should inherit the `Player` class.

The MCTS algorithm functions can be found under the `mcts` files. These files rely on the `play` and `utility` files.

The AI sends it's turn information to the front end via standard out, therefore, all other output should be sent to standard error.

## Frontend

The frontend is a simple Python GUI that take the input from the player. While the AI is taking its turn, it will not respond to input. Humans can take their turn by clicking on the respective column.

The frontend starts the backend as a subprocess, with command line arguments. These can be altered to change who is playing (human or AI). Check the backend file `connect.cpp` for more information. Feel free to mess around with the C_VALUE and NUM_SIMS being passed in. See [UCB](#ucb) below.

Because the backend is a subprocess, the frontend has total control of it, and terminates it at the end of each game.

The frontend also starts the server. It was convenient for the purposes of this application, but would change in production.

## Server

The Server handles requests from the backend (the AI, specifically) to pull or push data from the database. Currently, the AI only pushes "the best" decision at every branch of the tree, and pulls down the entire tree.

The nodes of the MCTS tree are compressed into 7 bytes for the board, and 8 bytes for wins/count. These are then encoded into base64 before being thrown into JSON and a POST HTTP request.

When receiving, the nodes are put in reverse. They are pulled out of the GET response, out of JSON, decoded from base64, and then uncompressed back into 42 bytes for the board, and 8 bytes for wins/count.

The server is running on Flask. The frontend also starts the server (for proof of concept) but it would never be this way in actual production. I will likely change this soon.

The server will need to clean the database, but it currently does not. In a production environment, this could be replaced with an AWS lambda.

## Database

This program uses MongoDB. It establishes a connection in the server, using my credentials. You are welcome to add your own credential file to test/play with this program. This program takes very litle space in the database (that was one of my challenges) and the free tier has been sufficient. In a production environment, this would be replaced with AWS DynamoDB.

## Tools

This folder contains test files and bash files for running calculations. It is not used in the actual program.

## UCB

The selection equation for this MCTS is Upper Confidence Bound (UCB). This equation takes a constant value C, which must be fine tuned. One of the challenges with MCTS is finding a proper C.

Normally, one can Binary Search or Grid Search to find a good value. However, the C value is directely correlated with the number of simulations. If the database is used to store simulations, the C value must change accordingly. This suddenly becomes an incredibly challenging problem!

This program does not change C as it goes along, or from game to game. However, this could be added in the future to make the AI better.

## What's next

The following may be implemented in the future:
- Fixed Simulation Bug
- A changing C value according to number of games
- More nodes stored in the database
- The Database cleaned by the server occasionally
- The Server running independently from the frontend
- Perhaps redetermine what part of the tree is "most important" to store
- Clean up the code
- Optimizations from end of tree
- Redo logic about "opponent states" in tree

## Questions, Bugs, Comments

There is one bug in simulating games, which I will go find and fix at some point.

Feel free to reach out to me with any bugs or questions at devinfrandsen2@gmail.com