#include <iostream>
#include <vector>
#include <chrono>

#define NOTHING ' '
#define STANDING '|'
#define LAYING '-'
#define GROUND 'g'
#define HOLE '_'
#define FINISH 'F'

using namespace std;
using namespace std::chrono;

int nodes = 0;

struct State
{
	vector<vector<char>> map;
	int lastOp = -1;
};

void findBlock(vector<vector<char>> &map, int &block_i, int &block_j)
{
	for (int i = 0; i < map.size(); ++i)
		for (int j = 0; j < map[i].size(); ++j)
			if (map[i][j] == STANDING)
			{
				block_i = i;
				block_j = j;
				return;
			}
}

bool up(vector<vector<char>> &map)
{
	int block_i, block_j;
	findBlock(map, block_i, block_j);

	if (block_i <= 0 || map[block_i - 1][block_j] == NOTHING)
		return false;

	map[block_i][block_j] = GROUND;

	if (map[block_i - 1][block_j] == HOLE)
		map[block_i - 1][block_j] = FINISH;

	else
		map[block_i - 1][block_j] = STANDING;

	return true;
}

bool left(vector<vector<char>> &map)
{
	int block_i, block_j;
	findBlock(map, block_i, block_j);

	if (block_j <= 0 || map[block_i][block_j - 1] == NOTHING)
		return false;

	map[block_i][block_j] = GROUND;

	if (map[block_i][block_j - 1] == HOLE)
		map[block_i][block_j - 1] = FINISH;

	else
		map[block_i][block_j - 1] = STANDING;

	return true;
}

bool right(vector<vector<char>> &map)
{
	int block_i, block_j;
	findBlock(map, block_i, block_j);

	if (block_j >= map[block_i].size() - 1 || map[block_i][block_j + 1] == NOTHING)
		return false;

	map[block_i][block_j] = GROUND;

	if (map[block_i][block_j + 1] == HOLE)
		map[block_i][block_j + 1] = FINISH;

	else
		map[block_i][block_j + 1] = STANDING;

	return true;
}

bool down(vector<vector<char>> &map)
{
	int block_i, block_j;
	findBlock(map, block_i, block_j);

	if (block_i >= map.size() - 1 || map[block_i + 1][block_j] == NOTHING)
		return false;

	map[block_i][block_j] = GROUND;

	if (map[block_i + 1][block_j] == HOLE)
		map[block_i + 1][block_j] = FINISH;

	else
		map[block_i + 1][block_j] = STANDING;

	return true;
}

typedef bool (*Operators)(vector<vector<char>> &map);

vector<Operators> operators = {up, left, right, down};

bool checkDone(const vector<vector<char>> &map)
{
	for (int i = 0; i < map.size(); ++i)
		for (int j = 0; j < map[i].size(); ++j)
			if (map[i][j] == FINISH)
				return true;

	return false;
}

void displayMap(const vector<vector<char>> &map)
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
					cout << ' ' << map[i / 2][j / 2] << ' ';
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

State breadthFirstSearch(vector<State> &states)
{
	State res;

	while (states.size() != 0)
	{
		if (checkDone(states[0].map))
		{
			res = states[0];
			break;
		}

		for (int i = 0; i < operators.size(); ++i)
		{
			if(states[0].lastOp == 0 && i == 3
			|| states[0].lastOp == 3 && i == 0
			|| states[0].lastOp == 2 && i == 1
			|| states[0].lastOp == 1 && i == 2)
				continue;
				
			vector<vector<char>> map_temp = states[0].map;

			if (operators[i](map_temp))
			{
				State new_state;
				new_state.map = map_temp;
				new_state.lastOp = i;
				states.push_back(new_state);
				++nodes;
			}
		}

		states.erase(states.begin());
	}

	return res;
}

int main()
{
	State start;
	start.map = {
		{'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'g', '|', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' '},
		{'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', ' '},
		{' ', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
		{' ', ' ', ' ', ' ', ' ', 'g', 'g', '_', 'g', 'g'},
		{' ', ' ', ' ', ' ', ' ', ' ', 'g', 'g', 'g', ' '}};

	vector<State> states;

	states.push_back(start);
	++nodes;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	start = breadthFirstSearch(states);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    // cout << duration << endl;

	cout << nodes << endl;
		
	displayMap(start.map);

	return 0;
}