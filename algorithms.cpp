#include "algorithms.h"

#include <queue>
#include <stack>

/* Checks all state antecessors for a duplicate state
 * Returns true in case any duplicate is found, false otherwise */
bool findDuplicate(shared_ptr<State> parent, shared_ptr<State> child)
{
	while (parent != nullptr)
	{
		if (parent == child)
			return true;

		parent = parent->parent;
	}

	return false;
}

/* Breadth First Search Algorithm
 * Uses a queue to store nodes    */
shared_ptr<State> breadthFirstSearch(shared_ptr<State> &start)
{
	queue<shared_ptr<State>> states;

	states.push(start);
	++expanded_nodes;

	while (states.size() != 0)
	{
		shared_ptr<State> actual = states.front();
		states.pop();
		++analyzed_nodes;

		if (checkDone(actual))
			return actual;

		for (int i = 0; i < operators.size(); ++i)
		{
			shared_ptr<State> new_state(new State);
			actual->clone(*new_state);

			if (operators[i](new_state) && !findDuplicate(actual, new_state))
			{
				new_state->parent = actual;
				new_state->cost = actual->cost + 1;
				states.push(new_state);
				++expanded_nodes;
			}
		}
	}

	return nullptr;
}

/* Depth First Search Algorithm
 * Uses a stack to store nodes    */
shared_ptr<State> depthFirstSearch(shared_ptr<State> &start)
{
	stack<shared_ptr<State>> states;

	states.push(start);
	++expanded_nodes;

	while (states.size() != 0)
	{
		shared_ptr<State> actual = states.top();
		states.pop();
		++analyzed_nodes;

		if (checkDone(actual))
			return actual;

		for (int i = 0; i < operators.size(); ++i)
		{
			shared_ptr<State> new_state(new State);
			actual->clone(*new_state);

			if (operators[i](new_state) && !findDuplicate(actual, new_state))
			{
				new_state->parent = actual;
				new_state->cost = actual->cost + 1;
				states.push(new_state);
				++expanded_nodes;
			}
		}
	}

	return nullptr;
}

/* Greedy Search Algorithm
 * Uses a priority queue to store nodes
 * Priority queue is sorted using state heuristic */
shared_ptr<State> greedySearch(shared_ptr<State> &start)
{
	priority_queue<shared_ptr<State>,vector<shared_ptr<State>>, greedyCompare> states;

	start->h();
	states.push(start);
	++expanded_nodes;

	while (states.size() != 0)
	{
		shared_ptr<State> actual = states.top();
		states.pop();
		++analyzed_nodes;

		if (checkDone(actual))
			return actual;

		for (int i = 0; i < operators.size(); ++i)
		{
			shared_ptr<State> new_state(new State);
			actual->clone(*new_state);

			if (operators[i](new_state) && !findDuplicate(actual, new_state))
			{
				new_state->parent = actual;
				new_state->cost = actual->cost + 1;
				new_state->h();
				states.push(new_state);
				++expanded_nodes;
			}
		}
	}

	return nullptr;
}

/* A Star Search Algorithm
 * Uses a priority queue to store nodes
 * Priority queue is sorted using state heuristic + state cost */
shared_ptr<State> aStarSearch(shared_ptr<State> &start)
{
	priority_queue<shared_ptr<State>, vector<shared_ptr<State>>, aStarCompare> states;

	start->h();
	states.push(start);
	++expanded_nodes;

	while (states.size() != 0)
	{
		shared_ptr<State> actual = states.top();
		states.pop();
		++analyzed_nodes;

		if (checkDone(actual))
			return actual;

		for (int i = 0; i < operators.size(); ++i)
		{
			shared_ptr<State> new_state(new State);
			actual->clone(*new_state);

			if (operators[i](new_state) && !findDuplicate(actual, new_state))
			{
				new_state->parent = actual;
				new_state->cost = actual->cost + 1;
				new_state->h();
				states.push(new_state);
				++expanded_nodes;
			}
		}
	}

	return nullptr;
}

/* Uniform Cost Search Algorithm
 * Uses a priority queue to store nodes
 * Priority queue is sorted using state cost */
shared_ptr<State> uniformCostSearch(shared_ptr<State> &start)
{
	priority_queue<shared_ptr<State>, vector<shared_ptr<State>>, uniformCostCompare> states;

	start->h();
	states.push(start);
	++expanded_nodes;

	while (states.size() != 0)
	{
		shared_ptr<State> actual = states.top();
		states.pop();
		++analyzed_nodes;

		if (checkDone(actual))
			return actual;

		for (int i = 0; i < operators.size(); ++i)
		{
			shared_ptr<State> new_state(new State);
			actual->clone(*new_state);

			if (operators[i](new_state) && !findDuplicate(actual, new_state))
			{
				new_state->parent = actual;
				new_state->cost = actual->cost + 1;
				states.push(new_state);
				++expanded_nodes;
			}
		}
	}

	return nullptr;
}

/* Iterative Deepening Search Algorithm
 * Uses a stack to store nodes
 * Starts with depth 1 which is incremented by 1 until a solution is found */
shared_ptr<State> iterativeDeepeningSearch(shared_ptr<State> &start)
{
	stack<shared_ptr<State>> states;
	int depth = 1;

	while (1)
	{
		states.push(start);
		++expanded_nodes;

		while (states.size() != 0)
		{
			shared_ptr<State> actual = states.top();
			states.pop();
			++analyzed_nodes;

			if (checkDone(actual))
				return actual;

			if (actual->cost == depth)
				continue;

			for (int i = 0; i < operators.size(); ++i)
			{
				shared_ptr<State> new_state(new State);
				actual->clone(*new_state);
				new_state->parent = actual;
				new_state->cost = actual->cost + 1;

				if (operators[i](new_state) && !findDuplicate(actual, new_state))
				{
					states.push(new_state);
					++expanded_nodes;
				}
			}
		}

		expanded_nodes = 0;
		analyzed_nodes = 0;
		++depth;
	}

	return nullptr;
}