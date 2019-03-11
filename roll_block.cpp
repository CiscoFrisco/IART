#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <chrono>

using namespace std;
using namespace std::chrono;

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
		if(i < other.i)
			return true;

		if(i > other.i)
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
		return pos1 == other.pos1;
	}

	bool operator<(const State &other) const
	{
		return pos1 < other.pos1;
	}
};

bool operator==( const shared_ptr<State>& lhs, const shared_ptr<State>& rhs )
{
	if(lhs == nullptr || rhs == nullptr)
		return false;

	return (*lhs) == (*rhs);
}

bool operator<( const shared_ptr<State>& lhs, const shared_ptr<State>& rhs )
{
	return (*lhs) < (*rhs);
}

int nodes = 0;
vector<vector<char>> map = {
	{'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{'g', '|', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' '},
	{'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', ' '},
	{' ', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
	{' ', ' ', ' ', ' ', ' ', 'g', 'g', '_', 'g', 'g'},
	{' ', ' ', ' ', ' ', ' ', ' ', 'g', 'g', 'g', ' '}};

set<Position> possible;
Position goal;

shared_ptr<State> analyzeMap()
{
	shared_ptr<State> start(new State);
	start->parent = nullptr;
	Position pos;

	for (int i = 0; i < map.size(); ++i)
		for (int j = 0; j < map[i].size(); ++j)
			switch (map[i][j])
			{
			case 'g':
				pos.i = i;
				pos.j = j;
				possible.insert(pos);
				break;
			case '|':
				start->pos1.i = i;
				start->pos1.j = j;
				pos.i = i;
				pos.j = j;
				possible.insert(pos);
				break;
			case '_':
				goal.i = i;
				goal.j = j;
				break;
			default:
				break;
			}

	return start;
}

void displayMap(const shared_ptr<State> &state)
{
	cout << endl;
	cout << " ";
	int i = 1, j;
	for (j = 0; j <= 4 * map[0].size(); j++)
	{
		if (j % 4 == 2)
			cout << i++;
		else
			cout << " ";
	}
	cout << endl;
	for (i = 0; i <= 2 * map.size(); i++)
	{
		if (i % 2 != 0)
			cout << (char)(i / 2 + 'A');
		for (j = 0; j <= 2 * map[0].size(); j++)
		{
			if (i % 2 == 0)
			{
				if (j == 0)
					cout << " ";
				if (j % 2 == 0)
					cout << " ";
				else
					cout << "---";
			}
			else
			{
				if (j % 2 == 0)
					cout << "|";
				else
				{
					if (state->pos1.i == i / 2 && state->pos1.j == j / 2)
						cout << " | ";

					else if (map[i / 2][j / 2] == '|')
						cout << " g ";

					else
						cout << ' ' << map[i / 2][j / 2] << ' ';
				}
			}
		}
		if (i % 2 != 0)
			cout << (char)(i / 2 + 'A');
		cout << endl;
	}
	cout << " ";
	for (j = 0, i = 1; j <= 4 * map[0].size(); j++)
	{
		if (j % 4 == 2)
			cout << i++;
		else
			cout << " ";
	}
	cout << endl;
}

bool up(shared_ptr<State> &state)
{
	Position pos;
	pos.i = state->pos1.i - 1;
	pos.j = state->pos1.j;

	if (goal == pos || possible.find(pos) != possible.end())
	{
		state->pos1 = pos;
		return true;
	}

	return false;
}

bool left(shared_ptr<State> &state)
{
	Position pos;
	pos.i = state->pos1.i;
	pos.j = state->pos1.j - 1;

	if (goal == pos || possible.find(pos) != possible.end())
	{
		state->pos1 = pos;
		return true;
	}

	return false;
}

bool right(shared_ptr<State> &state)
{
	Position pos;
	pos.i = state->pos1.i;
	pos.j = state->pos1.j + 1;

	if (goal == pos || possible.find(pos) != possible.end())
	{
		state->pos1 = pos;
		return true;
	}

	return false;
}

bool down(shared_ptr<State> &state)
{
	Position pos;
	pos.i = state->pos1.i + 1;
	pos.j = state->pos1.j;

	if (goal == pos || possible.find(pos) != possible.end())
	{
		state->pos1 = pos;
		return true;
	}

	return false;
}

typedef bool (*Operators)(shared_ptr<State> &state);

vector<Operators> operators = {up, left, right, down};

bool checkDone(const shared_ptr<State> &state)
{
	return state->pos1 == goal;
}

bool findDuplicate(shared_ptr<State> parent, shared_ptr<State> child)
{
	while(parent != nullptr)
	{
		if(parent == child)
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
			new_state->pos1 = states[0]->pos1;
			new_state->parent = states[0];
			

			if (operators[i](new_state) && !findDuplicate(states[0],new_state))
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
			new_state->pos1 = states[0]->pos1;
			new_state->parent = states[0];
			

			if (operators[i](new_state) && !findDuplicate(states[0],new_state))
			{
				states.insert(states.begin()+1, new_state);
				++nodes;
			}
		}

		states.erase(states.begin());
	}

	return res;
}

int main()
{
	shared_ptr<State> start = analyzeMap();

	vector<shared_ptr<State>> states;

	states.push_back(start);
	++nodes;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	shared_ptr<State> end = breadthFirstSearch(states);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(t2 - t1).count();
	
	cout << "Duration: " << (float) duration / 1000000 << " seconds.\n";
	cout << "Nodes: " << nodes << ".\n";

	displayMap(end);

	return 0;
}