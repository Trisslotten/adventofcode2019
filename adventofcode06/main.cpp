
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <set>
#include <queue>

struct Node
{
	std::vector<std::string> children;
	std::string parent = "";
};

void part1()
{
	std::unordered_map<std::string, Node> nodes;

	std::string line;
	std::ifstream data("data.txt");
	size_t sum = 0;
	if (data.is_open())
	{
		while (getline(data, line))
		{
			size_t offset = line.find(')');
			std::string parent = line.substr(0, offset);
			std::string child = line.substr(offset + 1);

			nodes[parent].children.push_back(child);
			nodes[child].parent = parent;
		}
		data.close();
	}
	int num_orbits = 0;

	for (auto& node : nodes)
	{
		bool running = true;
		std::string current = node.first;
		while (running)
		{
			Node curr_node = nodes[current];
			if (curr_node.parent == "")
			{
				running = false;
			}
			else
			{
				num_orbits++;
				current = curr_node.parent;
			}
		}
	}

	std::cout << num_orbits << "\n";
}

struct Node2
{
	std::vector<std::string> connections;
	int length = 0;
};

void part2()
{
	std::unordered_map<std::string, Node2> nodes;

	std::string line;
	std::ifstream data("data.txt");
	size_t sum = 0;
	if (data.is_open())
	{
		while (getline(data, line))
		{
			size_t offset = line.find(')');
			std::string parent = line.substr(0, offset);
			std::string child = line.substr(offset + 1);

			nodes[parent].connections.push_back(child);
			nodes[child].connections.push_back(parent);
		}
		data.close();
	}

	Node2 you = nodes["YOU"];
	std::set<std::string> visited;
	std::queue<std::string> to_visit;

	visited.insert("YOU");

	Node2 current = you;
	bool found = false;
	while (!found)
	{
		for (auto& c : current.connections)
		{
			if (visited.count(c) == 0)
			{
				to_visit.push(c);
				nodes[c].length = current.length + 1;
			}
		}
		if (to_visit.empty())
		{
			found = true;
		}
		else
		{
			current = nodes[to_visit.front()];
			visited.insert(to_visit.front());
			to_visit.pop();
		}
	}

	for (auto& node : nodes)
	{
		std::cout << node.first << ": " << node.second.length << "\n";
	}

	std::cout << nodes["SAN"].length - 2 << "\n";
}

int main()
{
	part2();
}