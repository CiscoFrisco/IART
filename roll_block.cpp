#include <iostream>
#include <stack>
#include <chrono>

#include "operators.h"

using namespace std::chrono;

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
	bool lying = false;

	for (int i = 0; i < map.size(); ++i)
		for (int j = 0; j < map[i].size(); ++j)
			switch (map[i][j])
			{
			case 'g':
				pos.i = i;
				pos.j = j;
				possible.insert(pos);
				break;
			case '-':
				if (lying)
				{
					start->pos2.i = i;
					start->pos2.j = j;
				}
				else
				{
					start->pos1.i = i;
					start->pos1.j = j;
					lying = true;
				}
				pos.i = i;
				pos.j = j;
				possible.insert(pos);
				break;
			case '|':
				start->pos1.i = i;
				start->pos1.j = j;
				start->pos2.i = -1;
				start->pos2.j = -1;
				pos.i = i;
				pos.j = j;
				possible.insert(pos);
				break;
			case '_':
				goal.i = i;
				goal.j = j;
				pos.i = i;
				pos.j = j;
				possible.insert(pos);
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
					{
						if (state->pos2.i == -1 && state->pos2.j == -1)
							cout << " | ";

						else
							cout << " - ";
					}

					else if (state->pos2.i == i / 2 && state->pos2.j == j / 2)
						cout << " - ";

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

bool checkDone(const shared_ptr<State> &state)
{
	return state->pos1 == goal && state->pos2.i == -1 && state->pos2.j == -1;
}

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
			new_state->pos1 = states[0]->pos1;
			new_state->pos2 = states[0]->pos2;
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
			new_state->pos1 = states[0]->pos1;
			new_state->pos2 = states[0]->pos2;
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

void displaySolution(shared_ptr<State> state)
{
	stack<shared_ptr<State>> way;

	while (state != nullptr)
	{
		way.push(state);
		state = state->parent;
	}

	getchar();

	while (!way.empty())
	{
		cout << "\n\n\n\n\n";
		displayMap(way.top());
		way.pop();
		getchar();
	}
}

int main()
{
	shared_ptr<State> start = analyzeMap();

	vector<shared_ptr<State>> states;

	states.push_back(start);
	++nodes;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	shared_ptr<State> end = depthFirstSearch(states);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "Duration: " << (float)duration / 1000000 << " seconds.\n";
	cout << "Nodes: " << nodes << ".\n";

	displaySolution(end);

	return 0;
}