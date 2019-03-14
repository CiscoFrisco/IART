#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "operators.h"

bool checkDone(const shared_ptr<State> &state);
bool findDuplicate(shared_ptr<State> parent, shared_ptr<State> child);

shared_ptr<State> breadthFirstSearch(shared_ptr<State> &start);
shared_ptr<State> depthFirstSearch(shared_ptr<State> &start);
shared_ptr<State> greedySearch(shared_ptr<State> &start);

extern int nodes;
extern Position goal;

#endif