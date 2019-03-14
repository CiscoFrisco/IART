#include <iostream>
#include <stack>
#include <chrono>
#include <fstream>
#include <string>
#include <conio.h>

#include "operators.h"
#include "algorithms.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std::chrono;

int nodes = 0;

Position goal;
Position expandCircle;
Position expandCross;
vector<vector<char>> puzzle;
set<Position> possible;
set<Position> expandableCircle;
set<Position> expandableCross;

bool checkDone(const shared_ptr<State> &state)
{
	return state->pos1 == goal && state->pos2.i == -1 && state->pos2.j == -1;
}

shared_ptr<State> analyzepuzzle()
{
	possible.clear();
	expandableCircle.clear();
	expandableCross.clear();

	shared_ptr<State> start(new State);
	start->parent = nullptr;
	Position pos;
	bool lying = false;

	for (int i = 0; i < puzzle.size(); ++i)
		for (int j = 0; j < puzzle[i].size(); ++j)
			switch (puzzle[i][j])
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
			case 'X':
				expandCross.i = i;
				expandCross.j = j;
				pos.i = i;
				pos.j = j;
				possible.insert(pos);
				break;
			case 'x':
				pos.i = i;
				pos.j = j;
				expandableCross.insert(pos);
				break;
			case 'C':
				expandCircle.i = i;
				expandCircle.j = j;
				pos.i = i;
				pos.j = j;
				possible.insert(pos);
				break;
			case 'c':
				pos.i = i;
				pos.j = j;
				expandableCircle.insert(pos);
				break;
			default:
				break;
			}

	return start;
}

void displaypuzzle(const shared_ptr<State> &state)
{
	cout << endl;
	cout << " ";
	int i = 1, j;
	for (j = 0; j <= 4 * puzzle[0].size(); j++)
	{
		if (j % 4 == 2)
			cout << i++;
		else
			cout << " ";
	}
	cout << endl;
	for (i = 0; i <= 2 * puzzle.size(); i++)
	{
		if (i % 2 != 0)
			cout << (char)(i / 2 + 'A');
		for (j = 0; j <= 2 * puzzle[0].size(); j++)
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

					else if (puzzle[i / 2][j / 2] == '|')
						cout << " g ";

					else if (puzzle[i / 2][j / 2] == 'x' && !state->expandedCross)
						cout << "   ";

					else if (puzzle[i / 2][j / 2] == 'c' && !state->expandedCircle)
						cout << "   ";

					else
						cout << ' ' << puzzle[i / 2][j / 2] << ' ';
				}
			}
		}
		if (i % 2 != 0)
			cout << (char)(i / 2 + 'A');
		cout << endl;
	}
	cout << " ";
	for (j = 0, i = 1; j <= 4 * puzzle[0].size(); j++)
	{
		if (j % 4 == 2)
			cout << i++;
		else
			cout << " ";
	}
	cout << endl;
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
		displaypuzzle(way.top());
		way.pop();
		getchar();
	}
}

void solve(char mode)
{
	nodes = 0;
	shared_ptr<State> start = analyzepuzzle();
	shared_ptr<State> end;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	if (mode == '2')
		end = breadthFirstSearch(start);

	else if(mode == '3')
		end = depthFirstSearch(start);

	else end = greedySearch(start);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "Duration: " << (float)duration / 1000000 << " seconds.\n";
	cout << "Nodes: " << nodes << ".\n";

	displaySolution(end);
}

void readLevel(char *level)
{
	ifstream mapFile("levels/" + string(level) + ".txt");

	puzzle.clear();
	string temp;

	while (getline(mapFile, temp))
	{
		vector<char> line(temp.begin(), temp.end());
		puzzle.push_back(line);
	}
}

void play()
{
	shared_ptr<State> game_info = analyzepuzzle();
	bool lost = false;
	char c;

	while (!lost)
	{
		displaypuzzle(game_info);

		if (checkDone(game_info))
			break;

		switch ((c = getch()))
		{
		case KEY_UP:
			if (!operators[0](game_info))
				lost = true;
			break;
		case KEY_LEFT:
			if (!operators[1](game_info))
				lost = true;
			break;
		case KEY_RIGHT:
			if (!operators[2](game_info))
				lost = true;
			break;
		case KEY_DOWN:
			if (!operators[3](game_info))
				lost = true;
			break;
		default:
			break;
		}
	}

	if (lost)
	{
		cout << "\n\nOoops! You lost!\n\n\n";
	}
	else
	{
		cout << "\n\nCongratulation! You won!\n\n\n";
	}

	return;
}

void menu()
{
	char temp = '\n';
	while (temp != '0')
	{
		cout << "  _____       _ _   ____  _            _     \n"
			 << " |  __ \\     | | | |  _ \\| |          | |    \n"
			 << " | |__) |___ | | | | |_) | | ___   ___| | __ \n"
			 << " |  _  // _ \\| | | |  _ <| |/ _ \\ / __| |/ / \n"
			 << " | | \\ \\ (_) | | | | |_) | | (_) | (__|   <  \n"
			 << " |_|  \\_\\___/|_|_| |____/|_|\\___/ \\___|_|\\_\\ \n";

		cout << "\n1. Play.\n2. Breadth-First.\n3. Depth-First.\n4. Greedy.\n0. Exit.\n\n\n";

		temp = getch();

		if (temp == '1')
			play();

		else if (temp == '2' || temp == '3' || temp == '4')
			solve(temp);
	}
}

int main(int argc, char **argv)
{
	readLevel(argv[1]);
	cout << "Enter your preference:\n1. Graphics\n2. Text\n";

	char input = getch();

	if (input == '1')
	{
		//gui();
		cout << "Graphics" << endl;
	}
	else if (input == '2')
		menu();
	else
		cout << "Go home you're drunk!\n";

	return 0;
}