#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#include "program.hpp"
#include "adventofcode15.h"
#include <set>
#include <queue>
#include <thread>

static union
{
	struct
	{
		int32_t x, y;
	};
	uint64_t hash;
};

const int NORTH = 1;
const int SOUTH = 2;
const int WEST = 3;
const int EAST = 4;

const int dirs[] = { NORTH, WEST, SOUTH, EAST };

std::unordered_map<uint64_t, int> map;

void main()
{
	Program program;
	std::vector<int64_t> code;
	std::string line;
	std::ifstream data("data.txt");
	if (data.is_open())
	{
		while (getline(data, line))
		{
			while (line.size() > 0)
			{
				size_t next;
				long long number = std::stoll(line, &next);

				code.push_back(number);

				if (next + 1 > line.size())
					break;
				line = line.substr(1 + next);
			}
		}
		data.close();
	}
	program.setCode(code);

	x = 0;
	y = 0;
	map[hash] = 1;

	int moves = 0;
	int px = 0;
	int py = 0;
	int move_dir = 0;
	int state = 0;
	bool running = true;
	while (running)
	{
		if (state == 0)
		{
			move_dir = dirNextEmpty(px, py);
		}
		else if (state == 1)
		{
			move_dir = dirCenter(px, py);
		}
		else if(state == 2)
		{
			move_dir = dirOxygen(px, py);
			moves++;
		}
		if (move_dir == 10000)
		{
			if (state == 0)
			{
				state++;
				continue;
			}
			else if(state == 2)
			{
				break;
			}
		}

		program.setInput(dirs[move_dir]);
		auto output = program.run();

		x = px;
		y = py;
		switch (dirs[move_dir])
		{
		case NORTH: y -= 1; break;
		case SOUTH: y += 1; break;
		case WEST:  x -= 1; break;
		case EAST:  x += 1; break;
		}

		if (output == 0)
		{
			// wall
			map[hash] = 0;
		}
		else if (output == 1)
		{
			// empty space
			map[hash] = 1;
			px = x;
			py = y;
		}
		else if (output == 2)
		{
			// oxygen system
			map[hash] = 2;
			px = x;
			py = y;
		}

		if (px == 0 && py == 0 && state == 1)
		{
			state++;
		}
	}
	printMap(px, py, 0, 0);

	std::cout << moves-1 << "\n";
}

int dirOxygen(int px, int py)
{
	std::set<uint64_t> looked_at;

	std::queue<std::pair<uint64_t, int>> to_look_from;

	x = px;
	y = py;
	looked_at.insert(hash);

	int cx = px;
	int cy = py;
	int curr_first_dir = 0;
	bool starting = true;
	bool found = false;
	while (!found)
	{
		int rx = 0;
		int ry = -1;
		for (int i = 0; i < 4; i++)
		{
			int nx = cx + rx;
			int ny = cy + ry;

			x = nx;
			y = ny;

			if (starting)
			{
				curr_first_dir = i;
			}

			if (looked_at.count(hash) == 0)
			{
				looked_at.insert(hash);
				auto iter = map.find(hash);
				if (iter == map.end())
				{
					return 10000;
				}
				else
				{
					if (iter->second == 2)
					{
						return curr_first_dir;
					}

					if (iter->second == 1 || iter->second == 2)
					{
						x = nx;
						y = ny;
						to_look_from.push(std::make_pair(hash, curr_first_dir));
					}
				}
			}

			std::swap(rx, ry);
			ry = -ry;
		}
		starting = false;
		if (to_look_from.empty())
		{
			return 10000;
		}
		std::tie(hash, curr_first_dir) = to_look_from.front();
		to_look_from.pop();
		cx = x;
		cy = y;
	}
}

int dirCenter(int px, int py)
{
	std::set<uint64_t> looked_at;

	std::queue<std::pair<uint64_t, int>> to_look_from;

	x = px;
	y = py;
	looked_at.insert(hash);

	int cx = px;
	int cy = py;
	int curr_first_dir = 0;
	bool starting = true;
	bool found = false;
	while (!found)
	{
		int rx = 0;
		int ry = -1;
		for (int i = 0; i < 4; i++)
		{
			int nx = cx + rx;
			int ny = cy + ry;

			x = nx;
			y = ny;

			if (starting)
			{
				curr_first_dir = i;
			}

			if (nx == 0 && ny == 0)
			{
				return curr_first_dir;
			}

			if (looked_at.count(hash) == 0)
			{
				looked_at.insert(hash);
				auto iter = map.find(hash);
				if (iter == map.end())
				{
					return 10000;
				}
				else
				{
					if (iter->second == 1 || iter->second == 2)
					{
						x = nx;
						y = ny;
						to_look_from.push(std::make_pair(hash, curr_first_dir));
					}
				}
			}

			std::swap(rx, ry);
			ry = -ry;
		}
		starting = false;
		if (to_look_from.empty())
		{
			return 10000;
		}
		std::tie(hash, curr_first_dir) = to_look_from.front();
		to_look_from.pop();
		cx = x;
		cy = y;
	}
}

int dirNextEmpty(int px, int py)
{
	std::set<uint64_t> looked_at;

	std::queue<std::pair<uint64_t, int>> to_look_from;

	x = px;
	y = py;
	looked_at.insert(hash);

	int cx = px;
	int cy = py;
	int curr_first_dir = 0;
	bool starting = true;
	bool found = false;
	while (!found)
	{
		int rx = 0;
		int ry = -1;
		for (int i = 0; i < 4; i++)
		{
			int nx = cx + rx;
			int ny = cy + ry;

			x = nx;
			y = ny;

			if (starting)
			{
				curr_first_dir = i;
			}
			
			if (looked_at.count(hash) == 0)
			{
				looked_at.insert(hash);
				auto iter = map.find(hash);
				if (iter == map.end())
				{
					return curr_first_dir;
				}
				else
				{
					if (iter->second == 1 || iter->second == 2)
					{
						x = nx;
						y = ny;
						to_look_from.push(std::make_pair(hash, curr_first_dir));
					}
				}
			}

			std::swap(rx, ry);
			ry = -ry;
		}
		starting = false;
		if (to_look_from.empty())
		{
			return 10000;
		}
		std::tie(hash, curr_first_dir) = to_look_from.front();
		to_look_from.pop();
		cx = x;
		cy = y;
	}
}

void printMap2(int px, int py, int lx, int ly, int tx, int ty)
{
	system("cls");
	int range = 40;
	for (int i = -range; i <= range; i++)
	{
		for (int j = -range; j <= range; j++)
		{
			x = j;
			y = i;
			if (px == j && py == i)
			{
				std::cout << "@";
			}
			else if (tx == j && ty == i)
			{
				std::cout << "X";
			}
			else if (lx == j && ly == i)
			{
				std::cout << "?";
			}
			else
			{
				auto iter = map.find(hash);
				if (iter != map.end())
				{
					switch (iter->second)
					{
					case 0:
						std::cout << '#';
						break;
					case 1:
						std::cout << '.';
						break;
					case 2:
						std::cout << 'O';
						break;
					}
				}
				else
				{
					std::cout << ' ';
				}
			}
		}
		std::cout << "\n";
	}
}

void printMap(int px, int py, int tx, int ty)
{
	system("cls");
	int range = 40;
	for (int i = -range; i <= range; i++)
	{
		for (int j = -range; j <= range; j++)
		{
			x = j;
			y = i;
			if (px == j && py == i)
			{
				std::cout << "@";
			}
			else if (tx == j && ty == i)
			{
				std::cout << "X";
			}
			else
			{
				auto iter = map.find(hash);
				if (iter != map.end())
				{
					switch (iter->second)
					{
					case 0:
						std::cout << '#';
						break;
					case 1:
						std::cout << '.';
						break;
					case 2:
						std::cout << 'O';
						break;
					}
				}
				else
				{
					std::cout << ' ';
				}
			}
		}
		std::cout << "\n";
	}
}
