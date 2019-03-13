#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "operators.h"

bool checkDone(const shared_ptr<State> &state);
bool findDuplicate(shared_ptr<State> parent, shared_ptr<State> child);

shared_ptr<State> breadthFirstSearch(vector<shared_ptr<State>> &states);
shared_ptr<State> depthFirstSearch(vector<shared_ptr<State>> &states);

extern int nodes;
extern Position goal;

#endif