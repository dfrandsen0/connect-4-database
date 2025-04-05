#ifndef CONFIG_H_
#define CONFIG_H_

// Connect 4 Nodes
#define NUM_CHILDREN	7
#define NUM_COLUMNS	7
#define NUM_ROWS	6
#define WIN_LENGTH	4
#define MIDDLE_ROW	3
#define MIDDLE_COLUMN	3

// MCTS Constants
#define DEFAULT_C_VALUE		1.414213562
#define DEFAULT_NUM_SIMS	1000

enum NodeFinished {
  UNFINISHED,
  WIN,
  LOSE
};

enum PlayerType {
  HUMAN,
  AI
};

#endif
