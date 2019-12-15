#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>

struct Requirement
{
	std::string element;
	long num_required = 0;
};

struct ReactionNode
{
	long num_from_reaction = 1;
	std::vector<Requirement> requirements;
};

std::unordered_map<std::string, ReactionNode> reactions;
std::unordered_map<std::string, long> temp_needed;
std::unordered_map<std::string, long> spare;
std::unordered_map<std::string, std::unordered_map<std::string, long>> total_needed;

void setTotalRequirements(const std::string& element, long num_needed, long depth = 0)
{
	auto reaction = reactions[element];

	long mult = num_needed / reaction.num_from_reaction;
	mult += (num_needed % reaction.num_from_reaction) > 0 ? 1 : 0;
	spare[element] += num_needed % reaction.num_from_reaction;

	for (auto& req : reaction.requirements)
	{
		temp_needed[req.element] += mult * req.num_required;
		for (int i = 0; i < depth; i++)
		{
			std::cout << "  ";
		}
		std::cout << req.element << ": " << mult * req.num_required << "\n";
		setTotalRequirements(req.element, mult * req.num_required, depth + 1);
	}
}

void main()
{
	std::string line;
	std::ifstream data("data.txt");
	if (data.is_open())
	{
		while (getline(data, line))
		{
			std::vector<Requirement> requirements;
			std::string result;

			auto i = line.find_first_of("=>");
			std::string req_str = line.substr(0, i - 1);
			std::string result_str = line.substr(i + 3);

			while (req_str.size() > 0)
			{
				size_t next;
				long num_required = std::stol(req_str, &next);

				std::string rest = req_str.substr(next + 1);
				next = rest.find_first_of(',');
				next = std::min(next, rest.size());
				requirements.push_back({ rest.substr(0, next), num_required });
				if (next + 1 > rest.size())
				{
					break;
				}
				req_str = rest.substr(next + 1);
			}

			size_t next;
			long num_from_reaction = std::stol(result_str, &next);
			result = result_str.substr(next + 1);

			reactions[result] = { num_from_reaction,requirements };

			//std::cout << result << ": " << num_from_reaction << "\n";
		}
		data.close();
	}
	setTotalRequirements("FUEL", 1);

	for (auto& reaction : reactions)
	{
		std::string element = reaction.first;

		long mult = temp_needed[element] / reaction.second.num_from_reaction;
		mult += (temp_needed[element] % reaction.second.num_from_reaction) > 0 ? 1 : 0;

		for (auto req : reaction.second.requirements)	
		{
			total_needed[req.element][element] = mult * req.num_required;
		}
	}
	

	int sum = 0;
	for (auto& i : total_needed["ORE"])
	{
		//std::cout << i.first << ": " << i.second << "\n";
		sum += i.second;
	}

	std::cout << sum << "\n";
}