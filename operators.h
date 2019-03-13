#ifndef OPERATORS_H
#define OPERATORS_H

#include <memory>
#include <vector>
#include <set>

using namespace std;

struct Position
{
	int i = -1;
	int j = -1;

	bool operator==(const Position &other) const
	{
		return i == other.i && j == other.j;
	}

	bool operator<(const Position &other) const
	{
		if (i < other.i)
			return true;

		if (i > other.i)
			return false;

		return j < other.j;
	}
};

struct State
{
	Position pos1;
	Position pos2;
	bool expandedCircle = false;
	bool expandedCross = false;
	shared_ptr<State> parent;

	bool operator==(const State &other) const
	{
		return pos1 == other.pos1 && pos2 == other.pos2 && expandedCircle == other.expandedCircle && expandedCross == other.expandedCross;
	}

	bool operator<(const State &other) const
	{
		if (expandedCross && !other.expandedCross)
			return true;

		if (!expandedCross && other.expandedCross)
			return false;

		if (expandedCircle && !other.expandedCircle)
			return true;

		if (!expandedCircle && other.expandedCircle)
			return false;

		if (pos1 < other.pos1)
			return true;

		if (other.pos1 < pos1)
			return false;

		else
			return pos2 < other.pos2;
	}

	void clone(State &new_state)
	{
		new_state.pos1 = pos1;
		new_state.pos2 = pos2;
		new_state.expandedCircle = expandedCircle;
		new_state.expandedCross = expandedCross;
	}
};

typedef bool (*Operators)(shared_ptr<State> &state);
extern vector<Operators> operators;
extern vector<vector<char>> puzzle;
extern set<Position> possible;
extern set<Position> expandableCircle;
extern set<Position> expandableCross;
extern Position goal;
extern Position expandCircle;
extern Position expandCross;

bool up(shared_ptr<State> &state);
bool left(shared_ptr<State> &state);
bool right(shared_ptr<State> &state);
bool down(shared_ptr<State> &state);

bool operator==(const shared_ptr<State> &lhs, const shared_ptr<State> &rhs);
bool operator<(const shared_ptr<State> &lhs, const shared_ptr<State> &rhs);

#endif