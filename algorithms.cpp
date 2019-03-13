#include "algorithms.h"

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

shared_ptr<State> breadthFirstSearch(vector<shared_ptr<State>> &states)
{
	shared_ptr<State> res;

	while (states.size() != 0)
	{
		if (checkDone(states[0]))
		{
			res = states[0];
			break;
		}

		for (int i = 0; i < operators.size(); ++i)
		{
			shared_ptr<State> new_state(new State);
			states[0]->clone(*new_state);
			new_state->parent = states[0];

			if (operators[i](new_state) && !findDuplicate(states[0], new_state))
			{
				states.push_back(new_state);
				++nodes;
			}
		}

		states.erase(states.begin());
	}

	return res;
}

shared_ptr<State> depthFirstSearch(vector<shared_ptr<State>> &states)
{
	shared_ptr<State> res;

	while (states.size() != 0)
	{
		if (checkDone(states[0]))
		{
			res = states[0];
			break;
		}

		for (int i = 0; i < operators.size(); ++i)
		{
			shared_ptr<State> new_state(new State);
			states[0]->clone(*new_state);
			new_state->parent = states[0];

			if (operators[i](new_state) && !findDuplicate(states[0], new_state))
			{
				states.insert(states.begin() + 1, new_state);
				++nodes;
			}
		}

		states.erase(states.begin());
	}

	return res;
}