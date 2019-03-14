#include "operators.h"

bool find(const shared_ptr<State> &state, const Position &pos)
{
	return possible.find(pos) != possible.end() || (state->expandedCircle && expandableCircle.find(pos) != expandableCircle.end()) || (state->expandedCross && expandableCross.find(pos) != expandableCross.end());
}

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

		if (find(state, pos1) && find(state, pos2))
		{
			if (pos1 == expandCircle || pos2 == expandCircle)
				state->expandedCircle = !state->expandedCircle;

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

		if (find(state, pos1) && find(state, pos2))
		{
			if (pos1 == expandCircle || pos2 == expandCircle)
				state->expandedCircle = !state->expandedCircle;

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

		if (find(state, pos1))
		{
			if (pos1 == expandCircle)
				state->expandedCircle = !state->expandedCircle;

			if (pos1 == expandCross)
				state->expandedCross = !state->expandedCross;

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

		if (find(state, pos1) && find(state, pos2))
		{
			if (pos1 == expandCircle || pos2 == expandCircle)
				state->expandedCircle = !state->expandedCircle;

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

		if (find(state, pos1))
		{
			if (pos1 == expandCircle)
				state->expandedCircle = !state->expandedCircle;

			if (pos1 == expandCross)
				state->expandedCross = !state->expandedCross;

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

		if (find(state, pos1) && find(state, pos2))
		{
			if (pos1 == expandCircle || pos2 == expandCircle)
				state->expandedCircle = !state->expandedCircle;

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

		if (find(state, pos1) && find(state, pos2))
		{
			if (pos1 == expandCircle || pos2 == expandCircle)
				state->expandedCircle = !state->expandedCircle;

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

		if (find(state, pos1))
		{
			if (pos1 == expandCircle)
				state->expandedCircle = !state->expandedCircle;

			if (pos1 == expandCross)
				state->expandedCross = !state->expandedCross;

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

		if (find(state, pos1) && find(state, pos2))
		{
			if (pos1 == expandCircle || pos2 == expandCircle)
				state->expandedCircle = !state->expandedCircle;

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

		if (find(state, pos1) && find(state, pos2))
		{
			if (pos1 == expandCircle || pos2 == expandCircle)
				state->expandedCircle = !state->expandedCircle;

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

		if (find(state, pos1) && find(state, pos2))
		{
			if (pos1 == expandCircle || pos2 == expandCircle)
				state->expandedCircle = !state->expandedCircle;

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

		if (find(state, pos1))
		{
			if (pos1 == expandCircle)
				state->expandedCircle = !state->expandedCircle;

			if (pos1 == expandCross)
				state->expandedCross = !state->expandedCross;

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

void State::h()
{
	heuristic = abs(pos1.i - goal.i) + abs(pos1.j - pos2.i);
}

vector<Operators> operators = {up, left, right, down};