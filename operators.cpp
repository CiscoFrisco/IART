#include "operators.h"

bool up(shared_ptr<State> &state)
{
	if (state->pos2.i == -1 && state->pos2.j == -1)
	{
		Position pos1;
		Position pos2;

		pos1.i = state->pos1.i - 2;
		pos1.j = state->pos1.j;

		pos2.i = state->pos1.i - 1;
		pos2.j = state->pos1.j;

		if (possible.find(pos1) != possible.end() && possible.find(pos2) != possible.end())
		{
			state->pos1 = pos1;
			state->pos2 = pos2;
			return true;
		}

		return false;
	}

	if (state->pos1.i == state->pos2.i)
	{
		Position pos1;
		Position pos2;

		pos1.i = state->pos1.i - 1;
		pos1.j = state->pos1.j;

		pos2.i = state->pos2.i - 1;
		pos2.j = state->pos2.j;

		if (possible.find(pos1) != possible.end() && possible.find(pos2) != possible.end())
		{
			state->pos1 = pos1;
			state->pos2 = pos2;
			return true;
		}

		return false;
	}

	if (state->pos1.j == state->pos2.j)
	{
		Position pos1;
		Position pos2;

		pos1.i = state->pos1.i - 1;
		pos1.j = state->pos1.j;

		pos2.i = -1;
		pos2.j = -1;

		if (possible.find(pos1) != possible.end())
		{
			state->pos1 = pos1;
			state->pos2 = pos2;
			return true;
		}

		return false;
	}

	return false;
}

bool left(shared_ptr<State> &state)
{
	if (state->pos2.i == -1 && state->pos2.j == -1)
	{
		Position pos1;
		Position pos2;

		pos1.i = state->pos1.i;
		pos1.j = state->pos1.j - 2;

		pos2.i = state->pos1.i;
		pos2.j = state->pos1.j - 1;

		if (possible.find(pos1) != possible.end() && possible.find(pos2) != possible.end())
		{
			state->pos1 = pos1;
			state->pos2 = pos2;
			return true;
		}

		return false;
	}

	if (state->pos1.i == state->pos2.i)
	{
		Position pos1;
		Position pos2;

		pos1.i = state->pos1.i;
		pos1.j = state->pos1.j - 1;

		pos2.i = -1;
		pos2.j = -1;

		if (possible.find(pos1) != possible.end())
		{
			state->pos1 = pos1;
			state->pos2 = pos2;
			return true;
		}

		return false;
	}

	if (state->pos1.j == state->pos2.j)
	{
		Position pos1;
		Position pos2;

		pos1.i = state->pos1.i;
		pos1.j = state->pos1.j - 1;

		pos2.i = state->pos2.i;
		pos2.j = state->pos2.j - 1;

		if (possible.find(pos1) != possible.end() && possible.find(pos2) != possible.end())
		{
			state->pos1 = pos1;
			state->pos2 = pos2;
			return true;
		}

		return false;
	}

	return false;
}

bool right(shared_ptr<State> &state)
{
	if (state->pos2.i == -1 && state->pos2.j == -1)
	{
		Position pos1;
		Position pos2;

		pos1.i = state->pos1.i;
		pos1.j = state->pos1.j + 1;

		pos2.i = state->pos1.i;
		pos2.j = state->pos1.j + 2;

		if (possible.find(pos1) != possible.end() && possible.find(pos2) != possible.end())
		{
			state->pos1 = pos1;
			state->pos2 = pos2;
			return true;
		}

		return false;
	}

	if (state->pos1.i == state->pos2.i)
	{
		Position pos1;
		Position pos2;

		pos1.i = state->pos1.i;
		pos1.j = state->pos2.j + 1;

		pos2.i = -1;
		pos2.j = -1;

		if (possible.find(pos1) != possible.end())
		{
			state->pos1 = pos1;
			state->pos2 = pos2;
			return true;
		}

		return false;
	}

	if (state->pos1.j == state->pos2.j)
	{
		Position pos1;
		Position pos2;

		pos1.i = state->pos1.i;
		pos1.j = state->pos1.j + 1;

		pos2.i = state->pos2.i;
		pos2.j = state->pos2.j + 1;

		if (possible.find(pos1) != possible.end() && possible.find(pos2) != possible.end())
		{
			state->pos1 = pos1;
			state->pos2 = pos2;
			return true;
		}

		return false;
	}

	return false;
}

bool down(shared_ptr<State> &state)
{
	if (state->pos2.i == -1 && state->pos2.j == -1)
	{
		Position pos1;
		Position pos2;

		pos1.i = state->pos1.i + 1;
		pos1.j = state->pos1.j;

		pos2.i = state->pos1.i + 2;
		pos2.j = state->pos1.j;

		if (possible.find(pos1) != possible.end() && possible.find(pos2) != possible.end())
		{
			state->pos1 = pos1;
			state->pos2 = pos2;
			return true;
		}

		return false;
	}

	if (state->pos1.i == state->pos2.i)
	{
		Position pos1;
		Position pos2;

		pos1.i = state->pos1.i + 1;
		pos1.j = state->pos1.j;

		pos2.i = state->pos2.i + 1;
		pos2.j = state->pos2.j;

		if (possible.find(pos1) != possible.end() && possible.find(pos2) != possible.end())
		{
			state->pos1 = pos1;
			state->pos2 = pos2;
			return true;
		}

		return false;
	}

	if (state->pos1.j == state->pos2.j)
	{
		Position pos1;
		Position pos2;

		pos1.i = state->pos2.i + 1;
		pos1.j = state->pos1.j;

		pos2.i = -1;
		pos2.j = -1;

		if (possible.find(pos1) != possible.end())
		{
			state->pos1 = pos1;
			state->pos2 = pos2;
			return true;
		}

		return false;
	}

	return false;
}

bool operator==(const shared_ptr<State> &lhs, const shared_ptr<State> &rhs)
{
	if (lhs == nullptr || rhs == nullptr)
		return false;

	return (*lhs) == (*rhs);
}

bool operator<(const shared_ptr<State> &lhs, const shared_ptr<State> &rhs)
{
	return (*lhs) < (*rhs);
}

vector<Operators> operators = {up, left, right, down};