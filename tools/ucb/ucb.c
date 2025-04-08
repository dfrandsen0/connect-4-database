#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    if(argc < 4) {
	printf("usage: ./ucb <count> <wins> <totalGames> <const>\n");
	exit(1);
    }

    int count = atoi(argv[1]);
    int wins = atoi(argv[2]);
    int totalGames = atoi(argv[3]);
//    double cVal = atol(argv[4]);
    double cVal = atof(argv[4]);

    double ucb = ((double)wins / (double)count) + (cVal * sqrt(log((double)totalGames) / (double)count));

    printf("%f\n", ucb);


    return 0;
}
