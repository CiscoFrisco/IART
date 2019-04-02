#include "operators.h"


/* Finds if it is possible for the block to be in a given position */
bool find(const shared_ptr<State> &state, const Position &pos)
{
	return possible.find(pos) != possible.end() || (state->expandedCircle && expandableCircle.find(pos) != expandableCircle.end()) || (state->expandedCross && expandableCross.find(pos) != expandableCross.end());
}

/* Checks if the block is standing */
bool isStanding(const shared_ptr<State> &state)
{
	return state->pos2.i == -1 && state->pos2.j == -1;
}

/* Checks if the block is lying down/up */
bool isVertical(const shared_ptr<State> &state)
{
	return state->pos1.j == state->pos2.j;
}

/* Checks if the block is lying left/right */
bool isHorizontal(const shared_ptr<State> &state)
{
	return state->pos1.i == state->pos2.i;
}

/* Up Operator
 * Checks if it possible to aplly the operator, 
 * in which case applies it amd returns true, otherwise returns false */
bool up(shared_ptr<State> &state)
{
	if (isStanding(state))
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

	if (isHorizontal(state))
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

	if (isVertical(state))
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

/* Left Operator
 * Checks if it possible to aplly the operator, 
 * in which case applies it amd returns true, otherwise returns false */
bool left(shared_ptr<State> &state)
{
	if (isStanding(state))
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

	if (isHorizontal(state))
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

	if (isVertical(state))
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

/* Right Operator
 * Checks if it possible to aplly the operator, 
 * in which case applies it amd returns true, otherwise returns false */
bool right(shared_ptr<State> &state)
{
	if (isStanding(state))
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

	if (isHorizontal(state))
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

	if (isVertical(state))
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

/* Down Operator
 * Checks if it possible to aplly the operator, 
 * in which case applies it amd returns true, otherwise returns false */
bool down(shared_ptr<State> &state)
{
	if (isStanding(state))
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

	if (isHorizontal(state))
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

	if (isVertical(state))
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

/* Checks if two state pointers are equal by comparing the state they are pointing to */
bool operator==(const shared_ptr<State> &lhs, const shared_ptr<State> &rhs)
{
	if (lhs == nullptr || rhs == nullptr)
		return false;

	return (*lhs) == (*rhs);
}

/* Checks the order of two state pointers by comparing the order of the states they are pointing to */
bool operator<(const shared_ptr<State> &lhs, const shared_ptr<State> &rhs)
{
	return (*lhs) < (*rhs);
}

double calculateDistance(const State &state, const Position pos)
{
	double result = (abs(state.pos1.i - pos.i) / 1.5) + (abs(state.pos1.j - pos.j) / 1.5);

	if (state.pos2.i != -1)
	{
		double other = (abs(state.pos2.i - pos.i) / 1.5) + (abs(state.pos2.j - pos.j) / 1.5);

		return (other < result ? other : result);
	}

	return result;
}

void State::h()
{
	if (expandCircle.i != -1 && !expandedCircle)
	{
		if (expandCross.i != -1 && !expandedCross)
		{
			double h1 = calculateDistance(*this, expandCircle);
			double h2 = calculateDistance(*this, expandCross);

			if(h1 < h2) 
			{
				heuristic = h1;

				heuristic += (abs(expandCross.i - expandCircle.i) / 1.5) + (abs(expandCross.j - expandCircle.j) / 1.5);
				heuristic += (abs(expandCross.i - goal.i) / 1.5) + (abs(expandCross.j - goal.j) / 1.5);

				return;
			}

			heuristic = h2;
			heuristic += (abs(expandCircle.i - expandCross.i) / 1.5) + (abs(expandCircle.j - expandCross.j) / 1.5);
			heuristic += (abs(expandCircle.i - goal.i) / 1.5) + (abs(expandCircle.j - goal.j) / 1.5);

			return;
		}

		heuristic = calculateDistance(*this, expandCircle);

		heuristic += (abs(goal.i - expandCircle.i) / 1.5) + (abs(goal.j - expandCircle.j) / 1.5);

		return;
	}

	if (expandCross.i != -1 && !expandedCross)
	{
		heuristic = calculateDistance(*this, expandCross);

		heuristic += (abs(goal.i - expandCross.i) / 1.5) + (abs(goal.j - expandCross.j) / 1.5);

		return;
	}

	heuristic = calculateDistance(*this, goal);
}

vector<Operators> operators = {up, left, right, down};