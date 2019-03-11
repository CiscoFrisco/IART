#ifndef OPERATORS_H
#define OPERATORS_H

#include <memory>
#include <vector>
#include <set>

using namespace std;

struct Position
{
	int i;
	int j;

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
	shared_ptr<State> parent;

	bool operator==(const State &other) const
	{
		return pos1 == other.pos1 && pos2 == other.pos2;
	}

	bool operator<(const State &other) const
	{
		if (pos1 < other.pos1)
			return true;

		if (other.pos1 < pos1)
			return false;

		else
			return pos2 < other.pos2;
	}
};

typedef bool (*Operators)(shared_ptr<State> &state);
extern vector<Operators> operators;
extern vector<vector<char>> map;
extern set<Position> possible;
extern Position goal;

bool up(shared_ptr<State> &state);
bool left(shared_ptr<State> &state);
bool right(shared_ptr<State> &state);
bool down(shared_ptr<State> &state);

bool operator==(const shared_ptr<State> &lhs, const shared_ptr<State> &rhs);
bool operator<(const shared_ptr<State> &lhs, const shared_ptr<State> &rhs);

#endif