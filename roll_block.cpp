#include <iostream>
#include <stack>
#include <chrono>
#include <fstream>
#include <string>
#include <conio.h>

// #include <SFML/Graphics.hpp>

#include "operators.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std::chrono;

int nodes = 0;
vector<vector<char>> puzzle;

// {'g', 'g', 'g', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
// {'g', '|', 'g', 'g', 'g', 'g', ' ', ' ', ' ', ' '},
// {'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', ' '},
// {' ', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
// {' ', ' ', ' ', ' ', ' ', 'g', 'g', '_', 'g', 'g'},
// {' ', ' ', ' ', ' ', ' ', ' ', 'g', 'g', 'g', ' '};

set<Position> possible;
Position goal;

shared_ptr<State> analyzepuzzle()
{
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
		displaypuzzle(way.top());
		way.pop();
		getchar();
	}
}

void solve(int level)
{
	possible.clear();
	nodes = 0;

	ifstream mapFile("levels/" + to_string(level) + ".txt");

	puzzle.clear();
	string temp;

	while (getline(mapFile, temp))
	{
		vector<char> line(temp.begin(), temp.end());
		puzzle.push_back(line);
	}

	shared_ptr<State> start = analyzepuzzle();

	vector<shared_ptr<State>> states;

	states.push_back(start);
	++nodes;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	shared_ptr<State> end = breadthFirstSearch(states);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "Duration: " << (float)duration / 1000000 << " seconds.\n";
	cout << "Nodes: " << nodes << ".\n";

	cout << end->pos1.i << endl;

	displaySolution(end);
}

// void gui()
// {
// 	sf::RenderWindow window(sf::VideoMode(800, 600), "Roll Block", sf::Style::Default);
// 	sf::Image img;

// 	img.loadFromFile("roll_block.png");
// 	window.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());

// 	sf::RectangleShape rectangle(sf::Vector2f(50.f, 50.f));

// 	while (window.isOpen())
// 	{
// 		sf::Event event;
// 		while (window.pollEvent(event))
// 		{
// 			switch (event.type)
// 			{
// 			case sf::Event::Closed:
// 				window.close();
// 				break;

// 			case sf::Event::KeyReleased:
// 				if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
// 				{
// 					rectangle.move(sf::Vector2f(0.f, -5.f));
// 				}
// 				if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
// 				{
// 					rectangle.move(sf::Vector2f(-5.f, 0.f));
// 				}
// 				if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
// 				{
// 					rectangle.move(sf::Vector2f(5.f, 0.f));
// 				}
// 				if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
// 				{
// 					rectangle.move(sf::Vector2f(0.f, 5.f));
// 				}
// 				break;

// 			default:
// 				break;
// 			}
// 		}

// 		window.clear(sf::Color::Black);

// 		window.draw(rectangle);

// 		window.display();
// 	}
// }

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

void menu(int level)
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

		cout << "\n1. Play.\n2. Solve\n0. Exit\n\n\n";

		temp = getch();

		if (temp == '1')
			play();

		else if (temp == '2')
			solve(level);
	}
}

int main(int argc, char **argv)
{
	cout << "Enter your preference:\n1. Graphics\n2. Text\n";

	int input;
	cin >> input;

	if (input == 1)
	{
		//gui();
		cout << "Graphics" << endl;
	}
	else if (input == 2)
		menu(atoi(argv[1]));
	else
		cout << "Go home you're drunk!\n";

	return 0;
}