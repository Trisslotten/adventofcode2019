#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

struct Wire
{
	char dir;
	int len;
};


void part1()
{
	std::vector<std::vector<Wire>> wires;
	wires.emplace_back();


	std::string line;
	std::ifstream data("data.txt");
	if (data.is_open())
	{
		while (getline(data, line))
		{
			while (line.size() > 0)
			{
				char dir = line[0];
				size_t next;
				line = line.substr(1);
				int number = std::stoi(line, &next);

				std::cout << dir << number << ", ";

				wires.back().push_back({ dir, number });

				if (next + 1 > line.size())
					break;
				line = line.substr(1 + next);
			}
			std::cout << "\n";
			wires.emplace_back();
		}
		data.close();
	}


	std::unordered_map<int64_t, int[2]> map;

	union
	{
		struct
		{
			int32_t x, y;
		} p;
		int64_t hash;
	} hash;

	for (int k = 0; k < wires.size(); k++)
	{

		auto& ws = wires[k];
		int32_t x = 0;
		int32_t y = 0;
		for (int i = 0; i < ws.size(); i++)
		{
			auto& wire = ws[i];
			for (int j = 0; j < wire.len; j++)
			{
				switch (wire.dir)
				{
				case 'U':
					y += 1;
					break;
				case 'R':
					x += 1;
					break;
				case 'D':
					y -= 1;
					break;
				case 'L':
					x -= 1;
					break;
				}

				hash.p.x = x;
				hash.p.y = y;

				if (map.count(hash.hash) > 0)
				{
					map[hash.hash][k] += 1;
				}
				else
				{
					map[hash.hash][0] = 0;
					map[hash.hash][1] = 0;

					map[hash.hash][k] = 1;
				}
			}
		}
	}

	int smallest = INT_MAX;

	for (auto& node : map)
	{
		hash.hash = node.first;
		if (node.second[0] > 0 && node.second[1] > 0)
		{
			if (hash.p.x < 0)
			{
				hash.p.x = -hash.p.x;
			}
			if (hash.p.y < 0)
			{
				hash.p.y = -hash.p.y;
			}

			int dist = hash.p.y + hash.p.x;
			if (dist < smallest)
			{
				smallest = dist;
			}
		}
	}

	std::cout << smallest << "\n";
}

void part2()
{
	std::vector<std::vector<Wire>> wires;
	wires.emplace_back();


	std::string line;
	std::ifstream data("data.txt");
	if (data.is_open())
	{
		while (getline(data, line))
		{
			while (line.size() > 0)
			{
				char dir = line[0];
				size_t next;
				line = line.substr(1);
				int number = std::stoi(line, &next);

				std::cout << dir << number << ", ";

				wires.back().push_back({ dir, number });

				if (next + 1 > line.size())
					break;
				line = line.substr(1 + next);
			}
			std::cout << "\n";
			wires.emplace_back();
		}
		data.close();
	}


	std::unordered_map<int64_t, int[2]> map;

	union
	{
		struct
		{
			int32_t x, y;
		} p;
		int64_t hash;
	} hash;

	for (int k = 0; k < wires.size(); k++)
	{
		int num_steps = 0;
		auto& ws = wires[k];
		int32_t x = 0;
		int32_t y = 0;
		for (int i = 0; i < ws.size(); i++)
		{
			auto& wire = ws[i];
			for (int j = 0; j < wire.len; j++)
			{
				switch (wire.dir)
				{
				case 'U':
					y += 1;
					break;
				case 'R':
					x += 1;
					break;
				case 'D':
					y -= 1;
					break;
				case 'L':
					x -= 1;
					break;
				}
				num_steps++;

				hash.p.x = x;
				hash.p.y = y;

				if (map.count(hash.hash) > 0)
				{
					map[hash.hash][k] = num_steps;
				}
				else
				{
					map[hash.hash][0] = 0;
					map[hash.hash][1] = 0;

					map[hash.hash][k] = num_steps;
				}
			}
		}
	}

	int smallest = INT_MAX;

	for (auto& node : map)
	{
		hash.hash = node.first;
		if (node.second[0] > 0 && node.second[1] > 0)
		{
			if (hash.p.x < 0)
			{
				hash.p.x = -hash.p.x;
			}
			if (hash.p.y < 0)
			{
				hash.p.y = -hash.p.y;
			}

			int dist = node.second[0] + node.second[1];
			if (dist < smallest)
			{
				smallest = dist;
			}
		}
	}

	std::cout << smallest << "\n";
}

int main()
{
	part2();

	return 0;
}