#ifndef UTILITY_H_
#define UTILITY_H_

#include "state.h"
#include "node.h"

class Utility {
public:
    static State* makeEmptyState();
    static double calcUcb(Node* node, double lnParentCount, double cValue);
    static void printState(char** state);
};

#endif
