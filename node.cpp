#include "node.h"
#include "config.h"

Node::Node() {}

Node::Node(State* state) {
    this->state = state;

    for(int i = 0; i < NUM_CHILDREN; i++) {
	this->children[i] = nullptr;
    }
}

State* Node::getState() {
    return this->state;
}

void Node::setState(State* state) {
    this->state = state;
}

int Node::getCount() {
    return this->count;
}

void Node::incCount() {
    this->count++;
}

void Node::setCount(int count) {
    this->count = count;
}

int Node::getWins() {
    return this->wins;
}

void Node::incWins() {
    this->wins++;
}

void Node::setWins(int wins) {
    this->wins = wins;
}


Node** Node::getChildren() {
    return this->children;
}
