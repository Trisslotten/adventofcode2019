#include "program.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include "adventotcode13.h"

static union
{
	struct
	{
		int32_t x, y;
	};
	uint64_t hash;
};

void part1(std::unordered_map<uint64_t, int>& map)
{

	int count = 0;
	for (auto& t : map)
	{
		if (t.second == 2)
			count++;
	}

	std::cout << count << "\n";
}

int64_t sign(int64_t i)
{
	if (i > 0)
		return 1;
	else if (i == 0)
		return 0;
	else
		return -1;
}

void main()
{
	Program program;
	program.setCode({});

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


	//std::unordered_map<uint64_t, int> map;

	const int size = 50;
	int map[size * size];
	for (int i = 0; i < size * size; i++)
	{
		map[i] = 0;
	}

	int score = 0;

	std::string buffer;
	buffer.resize(size * (size + 1), ' ');


	int ball = 0;
	int prev_ball = 0;
	int paddle = 0;

	bool running = true;
	while (running)
	{

		auto output = program.run();
		if (output == 99)
			break;
		x = output;

		output = program.run();
		if (output == 99)
			break;
		y = output;

		output = program.run();
		if (output == 99)
			break;
		int tile_id = output;

		if (x == -1 && y == 0)
		{
			score = tile_id;
		}
		else
		{
			//map[hash] = tile_id;
			map[x + y * size] = tile_id;
			if (tile_id == 4)
			{
				prev_ball = ball;
				ball = x;
			}
			else if (tile_id == 3)
			{
				paddle = x;
			}
		}
		program.setInput(sign(ball - paddle));
		
		/*
		system("cls");
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				char tile;
				switch (map[j + i * size])
				{
				case 0:
					tile = ' ';
					break;
				case 1:
					tile = '#';
					break;
				case 2:
					tile = '+';
					break;
				case 3:
					tile = '-';
					break;
				case 4:
					tile = 'o';
					break;
				}
				buffer[j + i * (size + 1)] = tile;
			}
			buffer[(i + 1) * (size + 1) - 1] = '\n';
		}
		std::cout << buffer << "\nscore: " << score<<"\n";
		//std::this_thread::sleep_for(std::chrono::milliseconds(200));
		*/
	}

	std::cout << score << "\n";

	//part1(map);
}