#include "algorithms.h"

#include <queue>
#include <stack>

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

shared_ptr<State> breadthFirstSearch(shared_ptr<State> &start)
{
	queue<shared_ptr<State>> states;

	states.push(start);
	++nodes;

	shared_ptr<State> res;

	while (states.size() != 0)
	{
		shared_ptr<State> actual = states.front();
		states.pop();

		if (checkDone(actual))
		{
			res = actual;
			break;
		}

		for (int i = 0; i < operators.size(); ++i)
		{
			shared_ptr<State> new_state(new State);
			actual->clone(*new_state);
			new_state->parent = actual;
			new_state->cost = actual->cost + 1;

			if (operators[i](new_state) && !findDuplicate(actual, new_state))
			{
				states.push(new_state);
				++nodes;
			}
		}
	}

	return res;
}

shared_ptr<State> depthFirstSearch(shared_ptr<State> &start)
{
	stack<shared_ptr<State>> states;

	states.push(start);
	++nodes;

	shared_ptr<State> res;

	while (states.size() != 0)
	{
		shared_ptr<State> actual = states.top();
		states.pop();

		if (checkDone(actual))
		{
			res = actual;
			break;
		}

		for (int i = 0; i < operators.size(); ++i)
		{
			shared_ptr<State> new_state(new State);
			actual->clone(*new_state);
			new_state->parent = actual;
			new_state->cost = actual->cost + 1;

			if (operators[i](new_state) && !findDuplicate(actual, new_state))
			{
				states.push(new_state);
				++nodes;
			}
		}
	}

	return res;
}

shared_ptr<State> greedySearch(shared_ptr<State> &start)
{
	priority_queue<shared_ptr<State>> states;

	start->h();
	states.push(start);
	++nodes;

	shared_ptr<State> res;

	while (states.size() != 0)
	{
		shared_ptr<State> actual = states.top();
		states.pop();

		if (checkDone(actual))
		{
			res = actual;
			break;
		}

		for (int i = 0; i < operators.size(); ++i)
		{
			shared_ptr<State> new_state(new State);
			actual->clone(*new_state);
			new_state->parent = actual;
			new_state->cost = actual->cost + 1;

			if (operators[i](new_state) && !findDuplicate(actual, new_state))
			{
				start->h();
				states.push(new_state);
				++nodes;
			}
		}
	}

	return res;
}

shared_ptr<State> aStarSearch(shared_ptr<State> &start)
{
	priority_queue<shared_ptr<State>, vector<shared_ptr<State>>, aStarCompare> states;

	start->h();
	states.push(start);
	++nodes;

	shared_ptr<State> res;

	while (states.size() != 0)
	{
		shared_ptr<State> actual = states.top();
		states.pop();

		if (checkDone(actual))
		{
			res = actual;
			break;
		}

		for (int i = 0; i < operators.size(); ++i)
		{
			shared_ptr<State> new_state(new State);
			actual->clone(*new_state);
			new_state->parent = actual;
			new_state->cost = actual->cost + 1;

			if (operators[i](new_state) && !findDuplicate(actual, new_state))
			{
				start->h();
				states.push(new_state);
				++nodes;
			}
		}
	}

	return res;
}

shared_ptr<State> uniformCostSearch(shared_ptr<State> &start)
{
	priority_queue<shared_ptr<State>, vector<shared_ptr<State>>, uniformCostCompare> states;

	start->h();
	states.push(start);
	++nodes;

	shared_ptr<State> res;

	while (states.size() != 0)
	{
		shared_ptr<State> actual = states.top();
		states.pop();

		if (checkDone(actual))
		{
			res = actual;
			break;
		}

		for (int i = 0; i < operators.size(); ++i)
		{
			shared_ptr<State> new_state(new State);
			actual->clone(*new_state);
			new_state->parent = actual;
			new_state->cost = actual->cost + 1;

			if (operators[i](new_state) && !findDuplicate(actual, new_state))
			{
				states.push(new_state);
				++nodes;
			}
		}
	}

	return res;
}

shared_ptr<State> iterativeDeepeningSearch(shared_ptr<State> &start)
{
	stack<shared_ptr<State>> states;
	shared_ptr<State> res;
	int depth = 1;

	while (1)
	{
		states.push(start);
		++nodes;

		while (states.size() != 0)
		{
			shared_ptr<State> actual = states.top();
			states.pop();

			if (checkDone(actual))
			{
				res = actual;
				return res;
			}

			if(actual->cost == depth)
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
					++nodes;
				}
			}
		}

		nodes = 0;
		++depth;
	}

	return res;
}