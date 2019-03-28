#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "operators.h"

bool checkDone(const shared_ptr<State> &state);
bool findDuplicate(shared_ptr<State> parent, shared_ptr<State> child);

shared_ptr<State> breadthFirstSearch(shared_ptr<State> &start);
shared_ptr<State> depthFirstSearch(shared_ptr<State> &start);
shared_ptr<State> greedySearch(shared_ptr<State> &start);
shared_ptr<State> aStarSearch(shared_ptr<State> &start);
shared_ptr<State> uniformCostSearch(shared_ptr<State> &start);
shared_ptr<State> iterativeDeepeningSearch(shared_ptr<State> &start);

extern int expanded_nodes;
extern int analyzed_nodes;
extern Position goal;

#endif